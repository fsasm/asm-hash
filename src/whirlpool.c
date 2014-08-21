/*
 * whirlpool.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-06-26
 */

#include "whirlpool.h"
#include <string.h>

void process_blocks (block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	(void)data_bits;
	for (unsigned int i = 0; i < n; i++) {
		whirlpool_process_blocks (&block[i * 64], (uint8_t(*)[8])(b->func_data), n);
	}
}

void whirlpool_init (whirlpool_context* ctxt) {
	if(ctxt == NULL)
		return;
	
	block_init (&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_blocks, ctxt->hash);
	whirlpool_init_hash(ctxt->hash);
}

void whirlpool_init_hash (uint8_t hash[8][8]) {
	memset (hash, 0, WHIRLPOOL_HASH_SIZE);
}

void whirlpool_finalize (whirlpool_context* ctxt) {
	block_util_finalize (&ctxt->b, BLOCK_LENGTH_256 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING);
}

void whirlpool_add (whirlpool_context* ctxt, const uint8_t data[], size_t length) {
	block_add (&ctxt->b, length, data);
}

void whirlpool_get_digest (whirlpool_context* ctxt, uint8_t digest[WHIRLPOOL_DIGEST_SIZE]) {
	memcpy (digest, ctxt->hash, WHIRLPOOL_DIGEST_SIZE);
}

static const uint8_t s_box[256] = {
	0x18, 0x23, 0xC6, 0xE8, 0x87, 0xB8, 0x01, 0x4F,
	0x36, 0xA6, 0xD2, 0xF5, 0x79, 0x6F, 0x91, 0x52, /*   8 */
	0x60, 0xBC, 0x9B, 0x8E, 0xA3, 0x0C, 0x7B, 0x35,
	0x1D, 0xE0, 0xD7, 0xC2, 0x2E, 0x4B, 0xFE, 0x57, /*  16 */
	0x15, 0x77, 0x37, 0xE5, 0x9F, 0xF0, 0x4A, 0xDA,
	0x58, 0xC9, 0x29, 0x0A, 0xB1, 0xA0, 0x6B, 0x85, /*  24 */
	0xBD, 0x5D, 0x10, 0xF4, 0xCB, 0x3E, 0x05, 0x67,
	0xE4, 0x27, 0x41, 0x8B, 0xA7, 0x7D, 0x95, 0xD8, /*  32 */
	0xFB, 0xEE, 0x7C, 0x66, 0xDD, 0x17, 0x47, 0x9E,
	0xCA, 0x2D, 0xBF, 0x07, 0xAD, 0x5A, 0x83, 0x33, /*  40 */
	0x63, 0x02, 0xAA, 0x71, 0xC8, 0x19, 0x49, 0xD9,
	0xF2, 0xE3, 0x5B, 0x88, 0x9A, 0x26, 0x32, 0xB0, /*  48 */
	0xE9, 0x0F, 0xD5, 0x80, 0xBE, 0xCD, 0x34, 0x48, 
	0xFF, 0x7A, 0x90, 0x5F, 0x20, 0x68, 0x1A, 0xAE, /*  56 */
	0xB4, 0x54, 0x93, 0x22, 0x64, 0xF1, 0x73, 0x12,
	0x40, 0x08, 0xC3, 0xEC, 0xDB, 0xA1, 0x8D, 0x3D, /*  64 */
	0x97, 0x00, 0xCF, 0x2B, 0x76, 0x82, 0xD6, 0x1B,
	0xB5, 0xAF, 0x6A, 0x50, 0x45, 0xF3, 0x30, 0xEF, /*  72 */
	0x3F, 0x55, 0xA2, 0xEA, 0x65, 0xBA, 0x2F, 0xC0, 
	0xDE, 0x1C, 0xFD, 0x4D, 0x92, 0x75, 0x06, 0x8A, /*  80 */
	0xB2, 0xE6, 0x0E, 0x1F, 0x62, 0xD4, 0xA8, 0x96, 
	0xF9, 0xC5, 0x25, 0x59, 0x84, 0x72, 0x39, 0x4C, /*  88 */
	0x5E, 0x78, 0x38, 0x8C, 0xD1, 0xA5, 0xE2, 0x61,
	0xB3, 0x21, 0x9C, 0x1E, 0x43, 0xC7, 0xFC, 0x04, /*  96 */
	0x51, 0x99, 0x6D, 0x0D, 0xFA, 0xDF, 0x7E, 0x24, 
	0x3B, 0xAB, 0xCE, 0x11, 0x8F, 0x4E, 0xB7, 0xEB, /* 104 */
	0x3C, 0x81, 0x94, 0xF7, 0xB9, 0x13, 0x2C, 0xD3,
	0xE7, 0x6E, 0xC4, 0x03, 0x56, 0x44, 0x7F, 0xA9, /* 112 */
	0x2A, 0xBB, 0xC1, 0x53, 0xDC, 0x0B, 0x9D, 0x6C,
	0x31, 0x74, 0xF6, 0x46, 0xAC, 0x89, 0x14, 0xE1, /* 120 */
	0x16, 0x3A, 0x69, 0x09, 0x70, 0xB6, 0xD0, 0xED,
	0xCC, 0x42, 0x98, 0xA4, 0x28, 0x5C, 0xF8, 0x86  /* 128 */
};

static const uint8_t diffusion_matrix[8][8] = {
	{1, 1, 4, 1, 8, 5, 2, 9},
	{9, 1, 1, 4, 1, 8, 5, 2},
	{2, 9, 1, 1, 4, 1, 8, 5},
	{5, 2, 9, 1, 1, 4, 1, 8},
	{8, 5, 2, 9, 1, 1, 4, 1},
	{1, 8, 5, 2, 9, 1, 1, 4},
	{4, 1, 8, 5, 2, 9, 1, 1},
	{1, 4, 1, 8, 5, 2, 9, 1}
};

static void permute (uint8_t block[8][8]) {
	uint8_t temp[8];
	for (uint_fast8_t i = 1; i < 8; i++) {
		for (uint_fast8_t k = 0; k < 8; k++) {
			temp[k] = block[k][i];
		}
		for (uint_fast8_t k = 0; k < 8; k++) {
			block[k][i] = temp[(8 - (i + 8 - k) % 8) % 8]; // FIXME this looks kinda ugly
		}
	}
}

static uint8_t gf_mult (uint8_t a, uint8_t b) {
	/* x^8 + x^4 + x^3 + x^2 + 1 = 0x11D */
	uint8_t result = 0;
	for (uint_fast8_t i = 0; i < 8; i++) {
		if ((b & 0x01) != 0) {
			result ^= a;
		}
		b = b >> 1;
		bool carry = (a & 0x80) != 0;
		a = a << 1;
		if (carry) {
			a ^= 0x1D;
		}
	}
	return result;
}

static void diffuse (uint8_t block[8][8]) {
	uint8_t temp[8][8];
	
	memset (temp, 0, sizeof (temp));
	
	for (uint_fast8_t i = 0; i < 8; i++) {
		for (uint_fast8_t j = 0; j < 8; j++) {
			for (uint_fast8_t k = 0; k < 8; k++) {
				temp[i][j] ^= gf_mult (block[i][k], diffusion_matrix[k][j]);
			}
		}
	}
	
	memcpy (block, temp, sizeof (temp));
}

void whirlpool_process_blocks (const uint8_t block[], uint8_t hash[8][8], unsigned int n) {
	uint8_t tmp[8][8];
	uint8_t key[8][8];

	memcpy (key, hash, 64);
	
	for (uint_fast8_t x = 0; x < 8; x++) {
		for (uint_fast8_t y = 0; y < 8; y++) {
			tmp[x][y] = block[x * 8 + y] ^ hash[x][y];
		}
	}
	
	for (uint_fast8_t r = 0; r < 10; r++) {
		/* substitution */
		for (uint_fast8_t x = 0; x < 8; x++) {
			for (uint_fast8_t y = 0; y < 8; y++) {
				tmp[x][y] = s_box[tmp[x][y]];
				key[x][y] = s_box[key[x][y]];
			}
		};
		
		permute (tmp);
		permute (key);
		
		diffuse (tmp);
		diffuse (key);
		
		/* add round key */
		for (uint_fast8_t y = 0; y < 8; y++) {
			key[0][y] ^= s_box[8 * r + y];
		}
		
		for (uint_fast8_t x = 0; x < 8; x++) {
			for (uint_fast8_t y = 0; y < 8; y++) {
				tmp[x][y] ^= key[x][y];
			}
		}
	}
	
	for (uint_fast8_t x = 0; x < 8; x++) {
		for (uint_fast8_t y = 0; y < 8; y++) {
			hash[x][y] ^= tmp[x][y] ^ block[x * 8 + y];
		}
	}
}
