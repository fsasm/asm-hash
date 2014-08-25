/*
 * blake.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-07-09 
 */

#include "blake256.h"
#include "int_util.h"
#include <string.h>
#include <stdio.h>

static const uint32_t table[16] = {
	0x243F6A88, 0x85A308D3, 0x13198A2E, 0x03707344,
	0xA4093822, 0x299F31D0, 0x082EFA98, 0xEC4E6C89, /*  8 */
	0x452821E6, 0x38D01377,	0xBE5466CF, 0x34E90C6C, 
	0xC0AC29B7, 0xC97C50DD, 0x3F84D5B5, 0xB5470917  /* 16 */
};

static const unsigned int permutations[10][16] = {
	{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15},
	{14, 10,  4,  8,  9, 15, 13,  6,  1, 12,  0,  2, 11,  7,  5,  3},
	{11,  8, 12,  0,  5,  2, 15, 13, 10, 14,  3,  6,  7,  1,  9,  4},
	{ 7,  9,  3,  1, 13, 12, 11, 14,  2,  6,  5, 10,  4,  0, 15,  8},
	{ 9,  0,  5,  7,  2,  4, 10, 15, 14,  1, 11, 12,  6,  8,  3, 13},
	{ 2, 12,  6, 10,  0, 11,  8,  3,  4, 13,  7,  5, 15, 14,  1,  9},
	{12,  5,  1, 15, 14, 13,  4, 10,  0,  7,  6,  3,  9,  2,  8, 11},
	{13, 11,  7, 14, 12,  1,  3,  9,  5,  0, 15,  4,  8,  6,  2, 10},
	{ 6, 15, 14,  9, 11,  3,  0,  8, 12,  2, 13,  7,  1,  4, 10,  5}, 
	{10,  2,  8,  4,  7,  6,  1,  5, 15, 11,  9, 14,  3, 12, 13,  0}
};

void process_block (block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	void* data = b->func_data;
	uint64_t full_size = b->full_size - (n - 1) * 64;
	
	for (unsigned int i = 0; i < n; i++) {
		blake256_process_block (block, data, data_bits ? full_size : 0);
		block += 64;
		full_size += 64;
	}
}

void process_block_with_salt (block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	blake256_context* ctxt = (blake256_context*)b->func_data;
	uint64_t full_size = b->full_size - (n - 1) * 64;
	
	uint32_t* salt = (uint32_t*)ctxt->salt;
	uint32_t* hash = ctxt->hash;
	
	for (unsigned int i = 0; i < n; i++) {
		blake256_process_block_with_salt (block, hash, salt, data_bits ? full_size : 0);
		block += 64;
		full_size += 64;
	}
}

/* BLAKE-256 */
void blake256_init (blake256_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	blake256_init_hash (ctxt->hash);
	block_init (&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_block, ctxt->hash);
	memset (ctxt->salt, 0, sizeof (ctxt->salt));
}

void blake256_init_hash (uint32_t hash[8]) {
	hash[0] = UINT32_C (0x6A09E667);
	hash[1] = UINT32_C (0xBB67AE85);
	hash[2] = UINT32_C (0x3C6EF372);
	hash[3] = UINT32_C (0xA54FF53A);
	hash[4] = UINT32_C (0x510E527F);
	hash[5] = UINT32_C (0x9B05688C);
	hash[6] = UINT32_C (0x1F83D9AB);
	hash[7] = UINT32_C (0x5BE0CD19);
}

void blake256_init_with_salt (blake256_context* ctxt, uint8_t salt[16]) {
	if (ctxt == NULL)
		return;
	
	blake256_init_hash (ctxt->hash);
	block_init (&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_block_with_salt, ctxt);
	memcpy (ctxt->salt, salt, sizeof (ctxt->salt));
}

void blake256_add (blake256_context* ctxt, const uint8_t data[], size_t length) {
	block_add (&ctxt->b, length, data);
}

void blake256_get_digest (blake256_context* ctxt, uint8_t digest[BLAKE256_DIGEST_SIZE]) {
	for (int i = 0; i < 8; i++) {
		u32_to_u8_be (ctxt->hash[i], &digest[i * 4]);
	}
}

void blake256_finalize (blake256_context* ctxt) {
	block_util_finalize (&ctxt->b, BLOCK_LENGTH_64 | BLOCK_BIG_ENDIAN | BLOCK_EXTENDED_PADDING);
}

static void blake256_g (uint32_t* v1, uint32_t* v2, uint32_t* v3, uint32_t* v4, uint32_t mc1, uint32_t mc2) {
	uint32_t a = *v1;
	uint32_t b = *v2;
	uint32_t c = *v3;
	uint32_t d = *v4;
	
	a = a + b + mc1;
	d = rotate_right_32 (d ^ a, 16);
	c = c + d;
	b = rotate_right_32 (b ^ c, 12);
	a = a + b + mc2;
	d = rotate_right_32 (d ^ a, 8);
	c = c + d;
	b = rotate_right_32 (b ^ c, 7);
	
	*v1 = a;
	*v2 = b;
	*v3 = c;
	*v4 = d;
}

static void process_state (const uint8_t block[64], uint32_t state[16]) {
	for (uint_fast8_t round = 0; round < 14; round++) {
		uint_fast8_t r = round % 10;
		
		const unsigned int* permutation = permutations[r];
		
		for (uint_fast8_t i = 0; i < 4; i++) {
			unsigned int index0 = permutation[2 * i];
			unsigned int index1 = permutation[2 * i + 1];
			
			uint32_t mc1 = table[index1] ^ u8_to_u32_be (&block[index0 * 4]);
			uint32_t mc2 = table[index0] ^ u8_to_u32_be (&block[index1 * 4]);
			
			blake256_g (&state[i], &state[4 + i], &state[8 + i], &state[12 + i], mc1 , mc2);
		}
		
		for (uint_fast8_t i = 0; i < 4; i++) {
			unsigned int index0 = permutation[2 * i + 8];
			unsigned int index1 = permutation[2 * i + 9];
			
			uint32_t mc1 = table[index1] ^ u8_to_u32_be (&block[index0 * 4]);
			uint32_t mc2 = table[index0] ^ u8_to_u32_be (&block[index1 * 4]);
			
			blake256_g (&state[i], &state[4 + (i + 1) % 4], &state[8 + (i + 2) % 4], &state[12 + (i + 3) % 4], mc1, mc2);
		}
	}
}

void blake256_process_block (const uint8_t block[64], uint32_t hash[8], uint64_t counter) {
	uint32_t counter1 = (uint32_t)((counter >> 29) & UINT32_MAX);
	uint32_t counter0 = (uint32_t)((counter <<  3) & UINT32_MAX);
	
	uint32_t state[16] = {
		hash[0], hash[1], hash[2], hash[3],
		hash[4], hash[5], hash[6], hash[7],
		table[0], table[1], table[2], table[3],
		counter0 ^ table[4], counter0 ^ table[5], counter1 ^ table[6], counter1 ^ table[7]
	};
	
	process_state (block, state);
	
	for (uint_fast8_t i = 0; i < 8; i++) {
		hash[i] ^= state[i] ^ state[i + 8];
	}
}

void blake256_process_block_with_salt (const uint8_t block[64], uint32_t hash[8], const uint32_t salt[4], uint64_t counter) {
	uint32_t counter1 = (uint32_t)((counter >> 29) & UINT32_MAX);
	uint32_t counter0 = (uint32_t)((counter <<  3) & UINT32_MAX);
	
	uint32_t state[16] = {
		hash[0], hash[1], hash[2], hash[3],
		hash[4], hash[5], hash[6], hash[7],
		salt[0] ^ table[0], salt[1] ^ table[1], salt[2] ^ table[2], salt[3] ^ table[3],
		counter0 ^ table[4], counter0 ^ table[5], counter1 ^ table[6], counter1 ^ table[7]
	};
	
	process_state (block, state);
	
	for (uint_fast8_t i = 0; i < 8; i++) {
		hash[i] ^= salt[i % 4] ^ state[i] ^ state[i + 8];
	}
}
