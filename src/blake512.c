/*
 * blake512.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-08-26
 */
 
#include "blake512.h"
#include "int_util.h"
#include <string.h>

static const uint64_t table[16] = {
	0x243F6A8885A308D3, 0x13198A2E03707344, 0xA4093822299F31D0, 0x082EFA98EC4E6C89,
	0x452821E638D01377, 0xBE5466CF34E90C6C, 0xC0AC29B7C97C50DD, 0x3F84D5B5B5470917, /*  8 */
	0x9216D5D98979FB1B, 0xD1310BA698DFB5AC, 0x2FFD72DBD01ADFB7, 0xB8E1AFED6A267E96,
	0xBA7C9045F12C7F99, 0x24A19947B3916CF7, 0x0801F2E2858EFC16, 0x636920D871574E69  /* 16 */
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
	uint64_t full_size = b->full_size - (n - 1) * 128;
	
	for (unsigned int i = 0; i < n; i++) {
#ifdef BLAKE512_USE_ASM
		blake512_process_block_asm (block, data, data_bits ? full_size : 0);
#else
		blake512_process_block (block, data, data_bits ? full_size : 0);
#endif
		block += 128;
		full_size += 128;
	}
}

void process_block_with_salt (block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	blake512_context* ctxt = (blake512_context*)b->func_data;
	uint64_t full_size = b->full_size - (n - 1) * 128;
	
	uint64_t* salt = (uint64_t*)ctxt->salt;
	uint64_t* hash = ctxt->hash;
	
	for (unsigned int i = 0; i < n; i++) {
		blake512_process_block_with_salt (block, hash, salt, data_bits ? full_size : 0);
		block += 128;
		full_size += 128;
	}
}

void blake512_init (blake512_context* ctxt) {
	if (ctxt == NULL)
		return;
		
	blake512_init_hash (ctxt->hash);
	block_init (&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block, ctxt->hash);
	memset (ctxt->salt, 0, sizeof (ctxt->salt));
}

void blake512_init_hash (uint64_t hash[8]) {
	hash[0] = UINT64_C (0x6A09E667F3BCC908);
	hash[1] = UINT64_C (0xBB67AE8584CAA73B);
	hash[2] = UINT64_C (0x3C6EF372FE94F82B);
	hash[3] = UINT64_C (0xA54FF53A5F1D36F1);
	hash[4] = UINT64_C (0x510E527FADE682D1);
	hash[5] = UINT64_C (0x9B05688C2B3E6C1F);
	hash[6] = UINT64_C (0x1F83D9ABFB41BD6B);
	hash[7] = UINT64_C (0x5BE0CD19137E2179);
}

void blake512_init_with_salt (blake512_context* ctxt, uint8_t salt[32]) {
	if (ctxt == NULL)
		return;
	
	blake512_init_hash (ctxt->hash);
	block_init (&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block_with_salt, ctxt);
	memcpy (ctxt->salt, salt, sizeof (ctxt->salt));
}

void blake512_add (blake512_context* ctxt, const uint8_t data[], size_t length) {
	block_add (&ctxt->b, length, data);
}

void blake512_get_digest (blake512_context* ctxt, uint8_t digest[BLAKE512_DIGEST_SIZE]) {
	for (int i = 0; i < 8; i++) {
		u64_to_u8_be (ctxt->hash[i], &digest[i * 8]);
	}
}

void blake512_finalize (blake512_context* ctxt) {
	block_util_finalize (&ctxt->b, BLOCK_LENGTH_128 | BLOCK_BIG_ENDIAN | BLOCK_EXTENDED_PADDING);
}

static void compress (uint64_t* v1, uint64_t* v2, uint64_t* v3, uint64_t* v4, uint64_t mc1, uint64_t mc2) {
	uint64_t a = *v1;
	uint64_t b = *v2;
	uint64_t c = *v3;
	uint64_t d = *v4;
	
	a = a + b + mc1;
	d = rotate_right_64 (d ^ a, 32);
	c = c + d;
	b = rotate_right_64 (b ^ c, 25);
	a = a + b + mc2;
	d = rotate_right_64 (d ^ a, 16);
	c = c + d;
	b = rotate_right_64 (b ^ c, 11);
	
	*v1 = a;
	*v2 = b;
	*v3 = c;
	*v4 = d;
}

static void process_state (const uint8_t block[128], uint64_t state[16]) {
	for (uint_fast8_t round = 0; round < 16; round++) {
		uint_fast8_t r = round % 10;
		
		const unsigned int* permutation = permutations[r];
		
		for (uint_fast8_t i = 0; i < 4; i++) {
			unsigned int index0 = permutation[2 * i];
			unsigned int index1 = permutation[2 * i + 1];
			
			uint64_t mc1 = table[index1] ^ u8_to_u64_be (&block[index0 * 8]);
			uint64_t mc2 = table[index0] ^ u8_to_u64_be (&block[index1 * 8]);
			
			compress (&state[i], &state[4 + i], &state[8 + i], &state[12 + i], mc1 , mc2);
		}
		
		for (uint_fast8_t i = 0; i < 4; i++) {
			unsigned int index0 = permutation[2 * i + 8];
			unsigned int index1 = permutation[2 * i + 9];
			
			uint64_t mc1 = table[index1] ^ u8_to_u64_be (&block[index0 * 8]);
			uint64_t mc2 = table[index0] ^ u8_to_u64_be (&block[index1 * 8]);
			
			compress (&state[i], &state[4 + (i + 1) % 4], &state[8 + (i + 2) % 4], &state[12 + (i + 3) % 4], mc1, mc2);
		}
	}
}

void blake512_process_block (const uint8_t block[128], uint64_t hash[8], uint64_t counter) {
	uint64_t counter1 = (uint64_t)((counter >> 61) & UINT64_MAX);
	uint64_t counter0 = (uint64_t)((counter <<  3) & UINT64_MAX);
	
	uint64_t state[16] = {
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

void blake512_process_block_with_salt (const uint8_t block[128], uint64_t hash[8], const uint64_t salt[4], uint64_t counter) {
	uint64_t counter1 = (uint64_t)((counter >> 61) & UINT64_MAX);
	uint64_t counter0 = (uint64_t)((counter <<  3) & UINT64_MAX);
	
	uint64_t state[16] = {
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

/* BLAKE-384 */
void blake384_init (blake384_context* ctxt) {
	if (ctxt == NULL)
		return;
		
	blake384_init_hash (ctxt->hash);
	block_init (&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block, ctxt->hash);
	memset (ctxt->salt, 0, sizeof (ctxt->salt));
}

void blake384_init_hash (uint64_t hash[8]) {
	hash[0] = UINT64_C (0xCBBB9D5DC1059ED8);
	hash[1] = UINT64_C (0x629A292A367CD507);
	hash[2] = UINT64_C (0x9159015A3070DD17);
	hash[3] = UINT64_C (0x152FECD8F70E5939);
	hash[4] = UINT64_C (0x67332667FFC00B31);
	hash[5] = UINT64_C (0x8EB44A8768581511);
	hash[6] = UINT64_C (0xDB0C2E0D64F98FA7);
	hash[7] = UINT64_C (0x47B5481DBEFA4FA4);
}

void blake384_init_with_salt (blake384_context* ctxt, uint8_t salt[32]) {
	if (ctxt == NULL)
		return;
	
	blake384_init_hash (ctxt->hash);
	block_init (&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block_with_salt, ctxt);
	memcpy (ctxt->salt, salt, sizeof (ctxt->salt));
}

void blake384_add (blake384_context* ctxt, const uint8_t data[], size_t length) {
	block_add (&ctxt->b, length, data);
}

void blake384_get_digest (blake384_context* ctxt, uint8_t digest[BLAKE384_DIGEST_SIZE]) {
	for (int i = 0; i < 6; i++) {
		u64_to_u8_be (ctxt->hash[i], &digest[i * 8]);
	}
}

void blake384_finalize (blake384_context* ctxt) {
	block_util_finalize (&ctxt->b, BLOCK_LENGTH_128 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING);
}

