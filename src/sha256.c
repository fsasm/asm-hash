/*
 * sha256.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-28
 */


#include "sha256.h"
#include "int_util.h"
#include <stdlib.h>
#include <string.h>

/* table for SHA-256 and SHA-224 */
uint32_t table[64] = {
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
	0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5, /*  8 */
	0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
	0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, /* 16 */
	0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
	0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA, /* 24 */
	0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
	0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967, /* 32 */
	0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
	0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85, /* 40 */
	0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 
	0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070, /* 48 */
	0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
	0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3, /* 56 */
	0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
	0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2  /* 64 */
};

void process_block (uint8_t block[], void* data, unsigned int n) {
#ifdef SHA256_USE_ASM
	for (unsigned int i = 0; i < n; i++) {
		sha256_process_block_asm (&block[i * 64], (uint32_t*)data);
	}
#else
	sha256_process_blocks (block, (uint32_t*)data, n);
#endif
}

/* SHA-256 */
void sha256_init (sha256_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	sha256_init_hash (ctxt->hash);	
	block_init (&ctxt->b, 64, ctxt->buffer, process_block, ctxt->hash);
}

void sha256_init_hash (uint32_t hash[8]) {
	hash[0] = UINT32_C (0x6A09E667);
	hash[1] = UINT32_C (0xBB67AE85);
	hash[2] = UINT32_C (0x3C6EF372);
	hash[3] = UINT32_C (0xA54FF53A);
	hash[4] = UINT32_C (0x510E527F);
	hash[5] = UINT32_C (0x9B05688C);
	hash[6] = UINT32_C (0x1F83D9AB);
	hash[7] = UINT32_C (0x5BE0CD19);
}

void sha256_finalize (sha256_context* ctxt) {
	block_util_finalize (&ctxt->b, false, false);
}

void sha256_add (sha256_context* ctxt, uint8_t data[], size_t length) {
	block_add (&ctxt->b, length, data);
}

void sha256_get_digest (sha256_context* ctxt, uint8_t digest[SHA256_DIGEST_SIZE]) {
	for (int i = 0; i < 8; i++) {
		u32_to_u8_be (ctxt->hash[i], &digest[i * 4]);
	}
}

static uint32_t f1 (uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) ^ (~x & z);
}

static uint32_t f2 (uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) ^ (x & z) ^ (y & z);
}

static uint32_t f3 (uint32_t x) {
	return rotate_right_32 (x, 2) ^ rotate_right_32 (x, 13) ^ rotate_right_32 (x, 22);
}

static uint32_t f4 (uint32_t x) {
	return rotate_right_32 (x, 6) ^ rotate_right_32 (x, 11) ^ rotate_right_32 (x, 25);
}

static uint32_t f5 (uint32_t x) {
	return rotate_right_32 (x, 7) ^ rotate_right_32 (x, 18) ^ (x >> 3);
}

static uint32_t f6 (uint32_t x) {
	return rotate_right_32 (x, 17) ^ rotate_right_32 (x, 19) ^ (x >> 10);
}

void sha256_process_blocks (uint8_t block[], uint32_t hash[5], unsigned int n) {
	for (unsigned int j = 0; j < n; j++) {
		uint8_t* block1 = &block[j * 64];
		uint32_t a = hash[0];
		uint32_t b = hash[1];
		uint32_t c = hash[2];
		uint32_t d = hash[3];
		uint32_t e = hash[4];
		uint32_t f = hash[5];
		uint32_t g = hash[6];
		uint32_t h = hash[7];
		
		uint32_t temp1;
		uint32_t temp2;
		uint32_t W[64];
		
		for (uint_fast8_t i = 0; i < 16; i++) {
			W[i] = u8_to_u32_be (&block1[i * 4]);
		}
		
		for (uint_fast8_t i = 16; i < 64; i++) {
			W[i] = f6 (W[i - 2]) + W[i - 7] + f5 (W[i - 15]) + W[i - 16];
		}
		
		for (uint_fast8_t t = 0; t < 64; t++) {
			temp1 = h + f4 (e) + f1 (e, f, g) + table[t] + W[t];
			temp2 = f3 (a) + f2 (a, b, c);
			
			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}
		
		hash[0] += a;
		hash[1] += b;
		hash[2] += c;
		hash[3] += d;
		hash[4] += e;
		hash[5] += f;
		hash[6] += g;
		hash[7] += h;
	}
}

/* SHA-224 */
void sha224_init (sha256_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init (&ctxt->b, 64, ctxt->buffer, process_block, ctxt->hash);
	sha224_init_hash (ctxt->hash);
}

void sha224_init_hash (uint32_t hash[8]) {
	hash[0] = UINT32_C (0xC1059ED8);
	hash[1] = UINT32_C (0x367CD507);
	hash[2] = UINT32_C (0x3070DD17);
	hash[3] = UINT32_C (0xF70E5939);
	hash[4] = UINT32_C (0xFFC00B31);
	hash[5] = UINT32_C (0x68581511);
	hash[6] = UINT32_C (0x64F98FA7);
	hash[7] = UINT32_C (0xBEFA4FA4);	
}

void sha224_add (sha224_context* ctxt, uint8_t data[], uint64_t length) {
	sha256_add (ctxt, data, length);
}

void sha224_finalize (sha224_context* ctxt) {
	sha256_finalize (ctxt);
}

void sha224_get_digest (sha256_context* ctxt, uint8_t digest[SHA224_DIGEST_SIZE]) {
	if (ctxt == NULL)
		return;
		
	for (uint_fast8_t i = 0; i < 7; i++)
		u32_to_u8_be (ctxt->hash[i], &digest[i * 4]);
}
