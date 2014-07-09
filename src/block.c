/*
 * block.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-17
 */

#include "block.h"
#include "int_util.h"
#include <string.h>

void block_init (block* b, size_t max_size, uint8_t buffer[], process_func func, void* func_data) {
	if (b == NULL)
		return;
	
	/* FIXME: check the other arguments */
	
	b->buffer = buffer;
	b->size = 0;
	b->max_size = max_size;
	b->full_size = 0;
	b->func = func;
	b->func_data = func_data;
}

void block_add (block* b, size_t size, const uint8_t data[]) {
	if (b == NULL)
		return;
	
	if (size == 0)
		return;
		
	b->full_size += size;
	size_t max_size = b->max_size;
	size_t block_size = b->size;
	uint8_t* buffer = b->buffer;
	
	if (block_size + size < max_size) {
		memcpy (&buffer[block_size], data, size);
		b->size += size;
		return;
	}

	if (block_size > 0) {
		size_t trailing_size = max_size - block_size;
		memcpy (&buffer[block_size], data, trailing_size);
		b->func (buffer, b->func_data, 1);
		data += trailing_size;
		size -= trailing_size;
	}

	b->func (data, b->func_data, (size / max_size));
	data += max_size * (size / max_size);
	
	memcpy (b->buffer, data, size % max_size);
	b->size = size % max_size;
}

void block_util_finalize (block* b, bool little_endian, block_length length) {
	if (b == NULL)
		return;
	
	uint8_t* buffer = b->buffer;
	size_t size = b->size;
	size_t max_size = b->max_size;
	buffer[size] = 0x80;
	size++;

	size_t length_index;
	switch (length) {
		case BLOCK_LENGTH_64:
			length_index = max_size - 8;
			break;
		
		case BLOCK_LENGTH_128:
			length_index = max_size - 16;
			break;
			
		case BLOCK_LENGTH_256:
			length_index = max_size - 32;
			break;
	}
	
	if (size > length_index) {
		memset (&buffer[size], 0, max_size - size + 1);
		size = 0;
		b->func (buffer, b->func_data, 1);
	}
	
	memset (&buffer[size], 0, length_index - size + 1);
	size = length_index;
	
	uint64_t full_size = b->full_size * 8;
	if (little_endian) {
		u64_to_u8_le (full_size, &buffer[size]);
		
		switch (length) {
			case BLOCK_LENGTH_128:
				memset (&buffer[size + 8], 0, 8);
				break;
			
			case BLOCK_LENGTH_256:
				memset (&buffer[size + 8], 0, 24);
				break;
		}
	} else {
		switch (length) {
			case BLOCK_LENGTH_128:
				memset (&buffer[size], 0, 8);
				size += 8;
				break;
				
			case BLOCK_LENGTH_256:
				memset (&buffer[size], 0, 24);
				size += 24;
				break;
		}
		u64_to_u8_be (full_size, &buffer[size]);
	}
	
	b->func (buffer, b->func_data, 1);
}
