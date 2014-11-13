/*
 * block.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-17
 */

#include "block.h"
#include "int_util.h"
#include <string.h>

static uint_fast8_t mask_from_size (block_size size); /* should work till block size 2048 bits (256 Bytes) */
static uint_fast8_t shift_from_size (block_size size);
static uint_fast8_t length_from_flags (block_flag flag);

#define FLAG_LENGTH_MASK (0x03)

void block_init (block* b, block_size max_size, uint8_t* buffer, process_func func, void* func_data) {
	if (b == NULL || buffer == NULL || func == NULL)
		return;
	
	if (max_size != BLOCK_SIZE_512 && max_size != BLOCK_SIZE_1024)
		return;
	
	b->buffer = buffer;
	b->max_size = max_size;
	b->full_size = 0;
	b->pfunc = func;
	b->efunc = NULL;
	b->func_data = func_data;
}

void block_init_with_end (block* b, block_size max_size, uint8_t* buffer, process_func pfunc, end_func efunc, void* func_data) {
	if (b == NULL || buffer == NULL || pfunc == NULL)
		return;
	
	if (max_size != BLOCK_SIZE_512 && max_size != BLOCK_SIZE_1024)
		return;
	
	b->buffer = buffer;
	b->max_size = max_size;
	b->full_size = 0;
	b->pfunc = pfunc;
	b->efunc = efunc;
	b->func_data = func_data;
}

void block_add (block* b, size_t size, const uint8_t data[]) {
	if (b == NULL)
		return;
	
	if (size == 0 || data == NULL)
		return;
		
	uint_fast8_t size_mask = mask_from_size (b->max_size);
	uint_fast8_t block_size = b->full_size & size_mask; /* how full is the buffer */
	uint8_t* buffer = b->buffer;
	
	if (block_size + size <= size_mask) { /* small amount; just copy */
		memcpy (&buffer[block_size], data, size);
		b->full_size += size;
		return;
	}

	if (block_size > 0) { /* fill the buffer and process */
		size_t trailing_size = (size_mask + 1) - block_size;
		memcpy (&buffer[block_size], data, trailing_size);
		b->full_size += trailing_size;
		b->pfunc (b, buffer, 1, true);
		data += trailing_size;
		size -= trailing_size;
	}
	
	/* process large amount of data */
	size_t size_full_blocks = size - (size & size_mask);
	b->full_size += size_full_blocks;
	size_t times = size >> shift_from_size (b->max_size);
	b->pfunc (b, data, times, true);
	data += size_full_blocks;
	
	/* copy the remaining data */
	size &= size_mask;
	memcpy (b->buffer, data, size);
	b->full_size += size;
}

void block_util_finalize (block* b, block_flag flags) {
	if (b == NULL)
		return;
		
	uint8_t* buffer = b->buffer;
	uint_fast8_t size_mask = mask_from_size (b->max_size);
	uint_fast8_t max_block_size = size_mask + 1;
	uint_fast8_t block_size = b->full_size & size_mask;
	bool data_bytes = true;	
	uint_fast8_t length_index = max_block_size - length_from_flags (flags);
	uint64_t length_field = (flags & BLOCK_COUNT) != 0 ?
		(b->full_size >> shift_from_size (b->max_size)) + 1 : b->full_size * 8;
	
	if (
		(flags & BLOCK_EXTENDED_PADDING) != 0 && 
		(flags & BLOCK_EXTRA_PADDING) == 0 &&
		block_size == length_index
	) {
		buffer[block_size] = 0x81;
		block_size++;
		
		if ((flags & BLOCK_LITTLE_ENDIAN) != 0) {
			u64_to_u8_le (length_field, &buffer[block_size]);
			block_size += 8;
			memset (&buffer[block_size], 0, max_block_size - block_size);
		} else {
			uint_fast8_t trailing_size = max_block_size - 8 - length_index;
			memset (&buffer[block_size], 0, trailing_size);
			block_size += trailing_size;
			u64_to_u8_be (length_field, &buffer[block_size]);
		}
		
		b->pfunc (b, buffer, 1, true);
		return;
	}
	
	if (block_size == 0)
		data_bytes = false;
	
	buffer[block_size] = 0x80;
	block_size++;
	
	if (block_size > length_index) {
		memset (&buffer[block_size], 0, max_block_size - block_size);
		b->pfunc (b, buffer, 1, true);
		data_bytes = false;
		block_size = 0;
		flags = flags & ~BLOCK_EXTRA_PADDING;
		if ((flags & BLOCK_COUNT) != 0)
			length_field++;
	}
	
	if ((flags & BLOCK_EXTENDED_PADDING) != 0) {
		if ((flags & BLOCK_EXTRA_PADDING) != 0) {
			memset (&buffer[block_size], 0, max_block_size - block_size);
			b->pfunc (b, buffer, 1, data_bytes);
			data_bytes = false;
			memset (buffer, 0, length_index - 1);
			buffer[length_index - 1] = 0x01;
		} else {
			memset (&buffer[block_size], 0, length_index - block_size - 1);
			buffer[length_index - 1] = 0x01;
		}
	} else {
		if ((flags & BLOCK_EXTRA_PADDING) != 0) {
			memset (&buffer[block_size], 0, max_block_size - block_size);
			b->pfunc (b, buffer, 1, data_bytes);
			data_bytes = false;
			memset (buffer, 0, length_index);
		} else {
			memset (&buffer[block_size], 0, length_index - block_size);
		}
	}
	
	block_size = length_index;
	
	if ((flags & BLOCK_LITTLE_ENDIAN) != 0) {
		u64_to_u8_le (length_field, &buffer[block_size]);
		block_size += 8;
		memset (&buffer[block_size], 0, max_block_size - block_size);
	} else {
		uint_fast8_t trailing_size = max_block_size - 8 - length_index;
		memset (&buffer[block_size], 0, trailing_size);
		block_size += trailing_size;
		u64_to_u8_be (length_field, &buffer[block_size]);
	}
	b->pfunc (b, buffer, 1, data_bytes);
	
	if (b->efunc != NULL)
		b->efunc (b);
}

static uint_fast8_t mask_from_size (block_size size) {
	switch (size) {
		case BLOCK_SIZE_512:
			return 0x3F;
		
		case BLOCK_SIZE_1024:
			return 0x7F;
			
		default:
			return 0;
	}
}

static uint_fast8_t shift_from_size (block_size size) {
	switch (size) {
		case BLOCK_SIZE_512:
			return 6u;
			
		case BLOCK_SIZE_1024:
			return 7u;
			
		default:
			return 0;
	}
}

static uint_fast8_t length_from_flags (block_flag flag) { /* in bytes */
	switch (flag & FLAG_LENGTH_MASK) {
		case BLOCK_LENGTH_64:
			return 8u;
			
		case BLOCK_LENGTH_128:
			return 16u;
		
		case BLOCK_LENGTH_256:
			return 32u;
			
		default:
			return 0;
	}
}
