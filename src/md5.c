/*
 * md5.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-04
 */

#include "md5.h"
#include "int_util.h"

static const uint32_t md5_table[64] = {
	0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE,
	0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501, /*  8 */
	0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE,
	0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821, /* 16 */
	0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA,
	0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8, /* 24 */
	0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED,
	0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A, /* 32 */
	0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C,
	0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70, /* 40 */
	0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05,
	0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665, /* 48 */
	0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039,
	0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1, /* 56 */
	0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1,
	0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391  /* 64 */
};

static const uint_fast8_t md5_shift[16] = {
	7, 12, 17, 22,
	5,  9, 14, 20,
	4, 11, 16, 23,
	6, 10, 15, 21
};

void process_block (block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	(void)data_bits;
#ifdef MD5_USE_ASM
	md5_process_blocks_asm (block, (uint32_t*)(b->func_data), n);
#else
	md5_process_blocks (block, (uint32_t*)(b->func_data), n);
#endif
}

void md5_init_hash (uint32_t hash[4]) {
	hash[0] = UINT32_C (0x67452301);
	hash[1] = UINT32_C (0xEFCDAB89);
	hash[2] = UINT32_C (0x98BADCFE);
	hash[3] = UINT32_C (0x10325476);
}

void md5_init (md5_context* ctxt) {
	if (ctxt == NULL)
		return;

	md5_init_hash (ctxt->hash);
	block_init (&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_block, ctxt->hash);
}

void md5_add (md5_context* ctxt, const uint8_t data[], size_t length) {
	block_add (&ctxt->b, length, data);
}

void md5_finalize (md5_context* ctxt) {
	block_util_finalize (&ctxt->b, BLOCK_LENGTH_64 | BLOCK_LITTLE_ENDIAN | BLOCK_SIMPLE_PADDING);
}

void md5_get_digest (md5_context* ctxt, uint8_t digest[MD5_DIGEST_SIZE]) {
	for (int i = 0; i < 4; i++) {
		u32_to_u8_le (ctxt->hash[i], &digest[i * 4]);
	}
}

void md5_process_blocks (const uint8_t block[], uint32_t hash[4], unsigned int n) {
	for (unsigned int j = 0; j < n; j++) {
		const uint8_t* block1 = &block[j * 64];
		
		uint32_t a = hash[0];
		uint32_t b = hash[1];
		uint32_t c = hash[2];
		uint32_t d = hash[3];
		
		for (int i = 0; i < 16; i++) {
			uint32_t f = ((c ^ d) & b) ^ d;
			a += f + md5_table[i] + u8_to_u32_le (&block1[i * 4]);
			uint_fast8_t shift = md5_shift[i & 0x03];
			a = b + rotate_left_32 (a, shift);

			uint32_t temp = a;
			a = d;
			d = c;
			c = b;
			b = temp;
		}

		for (int i = 16; i < 32; i++) {
			uint_fast8_t block_index = (i * 5 + 1) & 0x0F;
			uint32_t f = (d & b) | (~d & c);
			a += f + md5_table[i] + u8_to_u32_le (&block1[block_index * 4]);
			uint_fast8_t shift = md5_shift[(i & 0x03) + 4];
			a = b + rotate_left_32 (a, shift);

			uint32_t temp = a;
			a = d;
			d = c;
			c = b;
			b = temp;
		}

		for (int i = 32; i < 48; i++) {
			uint_fast8_t block_index = (i * 3 + 5) & 0x0F;
			uint32_t f = b ^ c ^ d;
			a += f + md5_table[i] + u8_to_u32_le (&block1[block_index * 4]);
			uint_fast8_t shift = md5_shift[(i & 0x03) + 8];
			a = b + rotate_left_32 (a, shift);

			uint32_t temp = a;
			a = d;
			d = c;
			c = b;
			b = temp;
		}
		for (int i = 48; i < 64; i++) {
			uint_fast8_t block_index = (i * 7) & 0x0F;
			uint32_t f = c ^ (b | ~d);
			a += f + md5_table[i] + u8_to_u32_le (&block1[block_index * 4]);
			uint_fast8_t shift = md5_shift[(i & 0x03) + 12];
			a = b + rotate_left_32 (a, shift);

			uint32_t temp = a;
			a = d;
			d = c;
			c = b;
			b = temp;
		}
		hash[0] += a;
		hash[1] += b;
		hash[2] += c;
		hash[3] += d;
	}
}
