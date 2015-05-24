/*
 * whirlpool.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-06-26
 */

#include "whirlpool.h"
#include "int_util.h"
#include <string.h>

#ifndef WHIRLPOOL_PRINT_TABLES
void process_blocks (block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	(void)data_bits;
	for (unsigned int i = 0; i < n; i++) {
		whirlpool_process_blocks (&block[i * 64], (uint8_t(*)[8])(b->func_data), 0);
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
#ifdef WHIRLPOOL_NAIVE
	memcpy (digest, ctxt->hash, WHIRLPOOL_DIGEST_SIZE);
#else
	for (uint_fast8_t x = 0; x < 8; x++) {
		for (uint_fast8_t y = 0; y < 8; y++) {
			digest[x * 8 + y] = ctxt->hash[x][7 - y];
		}
	}
#endif
}
#endif

#if defined (WHIRLPOOL_NAIVE) || defined (WHIRLPOOL_PRINT_TABLES)
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
#else

#include "whirlpool_table.h"

#endif

#if WHIRLPOOL_PRINT_TABLES

#include <stdio.h>
#include <inttypes.h>

static uint64_t t[8][256];

void build_tables (void) {
	uint8_t temp[8];
	
	for (uint_fast16_t i = 0; i < 256; i++) {
		uint8_t s = s_box[i];
		for (uint_fast8_t n = 0; n < 8; n++) {
			for (uint_fast8_t x = 0; x < 8; x++) {
				temp[x] = gf_mult (s, diffusion_matrix[n][x]);
			}
			t[n][i] = u8_to_u64_be (temp);
		}
	}
}

int main (void) {
	build_tables ();
	/* TODO WHIRLPOOL_SINGLE_TABLE */
	#ifdef WHIRLPOOL_ASM_TABLES_32
	/* WHIRLPOOL_ASM_TABLES_32 */
	printf ("whirlpool_tables:\n");
	for (uint_fast8_t table = 0; table < 8; table++) {
		printf ("\nwhirlpool_table%d:\t/* table %d */\n", table, (table + 1));
		for (uint_fast16_t i = 0; i < 256; i++) {
			uint64_t entry = t[table][i];
			uint32_t low = (uint32_t)entry;
			uint32_t high = (uint32_t)(entry >> 32);
			printf ("\t.long 0x%8.8" PRIX32 "\n", low); /* little endian */
			printf ("\t.long 0x%8.8" PRIX32, high);
			
			if ((i + 1) % 4 == 0) {
				printf (" /* %d */\n", i + 1);
			} else {
				printf ("\n");
			}
		}
	}
	#elif defined(WHIRLPOOL_ASM_TABLES_64)
	/* WHIRLPOOL_ASM_TABLES32 */
	printf ("whirlpool_tables:\n");
	for (uint_fast8_t table = 0; table < 8; table++) {
		printf ("\nwhirlpool_table%d:\t/* table %d */\n", table, (table + 1));
		for (uint_fast16_t i = 0; i < 256; i++) {
			uint64_t entry = t[table][i];
			printf ("\t.quad 0x%16.16" PRIX64, entry);
			
			if ((i + 1) % 8 == 0) {
				printf (" /* %d */\n", i + 1);
			} else {
				printf ("\n");
			}
		}
	}
	#else
	/* WHIRLPOOL_C_TABLES */
	/* print tables to copy in a c source file */
	for (uint_fast8_t table = 0; table < 8; table++) {
		printf ("{\n");
		
		for (uint_fast16_t i = 0; i < 256; i++) {
			if (i % 4 == 0)
				printf ("\t");
			if (i == 255)
				printf ("0x%16.16" PRIX64 "", t[table][i]);
			else 
				printf ("0x%16.16" PRIX64 ", ", t[table][i]);
			if (i % 4 == 3)
				printf ("\n");
		}
		if (table == 7)
			printf ("}\n");
		else
			printf ("},\n");
	}	
	#endif
	
}

#else

void whirlpool_process_blocks (const uint8_t block[], uint8_t hash[8][8], unsigned int n) {
	(void)n;
#ifdef WHIRLPOOL_NAIVE
	uint8_t state[8][8];
	uint8_t key[8][8];

	memcpy (key, hash, 64);
	
	for (uint_fast8_t x = 0; x < 8; x++) {
		for (uint_fast8_t y = 0; y < 8; y++) {
			state[x][y] = block[x * 8 + y] ^ hash[x][y];
		}
	}
	
	for (uint_fast8_t r = 0; r < 10; r++) {
		/* substitution */
		for (uint_fast8_t x = 0; x < 8; x++) {
			for (uint_fast8_t y = 0; y < 8; y++) {
				state[x][y] = s_box[state[x][y]];
				key[x][y] = s_box[key[x][y]];
			}
		};
		
		permute (state);
		permute (key);
		
		diffuse (state);
		diffuse (key);
		
		/* add round key */
		for (uint_fast8_t y = 0; y < 8; y++) {
			key[0][y] ^= s_box[8 * r + y];
		}
		
		for (uint_fast8_t x = 0; x < 8; x++) {
			for (uint_fast8_t y = 0; y < 8; y++) {
				state[x][y] ^= key[x][y];
			}
		}
	}
	
	for (uint_fast8_t x = 0; x < 8; x++) {
		for (uint_fast8_t y = 0; y < 8; y++) {
			hash[x][y] ^= state[x][y] ^ block[x * 8 + y];
		}
	}
#else
	uint64_t state[8];
	uint64_t key[8];
	uint64_t tmp [8];

	memcpy (key, hash, 64);
	memset (tmp, 0, sizeof (tmp));

	for (uint_fast8_t x = 0; x < 8; x++) {
		state[x] = u8_to_u64_be (&block[x * 8]) ^ key[x];
	}

#ifdef WHIRLPOOL_SINGLE_TABLE

#define TABLE0(index) (tables[((index) >> 56) & 0xFF])
#define TABLE1(index) (rotate_right_64 (tables[((index) >> 48) & 0xFF],  8))
#define TABLE2(index) (rotate_right_64 (tables[((index) >> 40) & 0xFF], 16))
#define TABLE3(index) (rotate_right_64 (tables[((index) >> 32) & 0xFF], 24))
#define TABLE4(index) (rotate_right_64 (tables[((index) >> 24) & 0xFF], 32))
#define TABLE5(index) (rotate_right_64 (tables[((index) >> 16) & 0xFF], 40))
#define TABLE6(index) (rotate_right_64 (tables[((index) >>  8) & 0xFF], 48))
#define TABLE7(index) (rotate_right_64 (tables[(index) & 0xFF], 56))

#else

#define TABLE0(index) (tables[0][((index) >> 56) & 0xFF])
#define TABLE1(index) (tables[1][((index) >> 48) & 0xFF])
#define TABLE2(index) (tables[2][((index) >> 40) & 0xFF])
#define TABLE3(index) (tables[3][((index) >> 32) & 0xFF])
#define TABLE4(index) (tables[4][((index) >> 24) & 0xFF])
#define TABLE5(index) (tables[5][((index) >> 16) & 0xFF])
#define TABLE6(index) (tables[6][((index) >>  8) & 0xFF])
#define TABLE7(index) (tables[7][(index) & 0xFF])

#endif
	for (uint_fast8_t r = 0; r < 10; r++) {
		/* key */
		tmp[0] = 
			TABLE0(key[0]) ^ TABLE1(key[7]) ^ TABLE2(key[6]) ^ TABLE3(key[5]) ^
			TABLE4(key[4]) ^ TABLE5(key[3]) ^ TABLE6(key[2]) ^ TABLE7(key[1]) ^
			round_constants[r];
			
		tmp[1] = 
			TABLE0(key[1]) ^ TABLE1(key[0]) ^ TABLE2(key[7]) ^ TABLE3(key[6]) ^
			TABLE4(key[5]) ^ TABLE5(key[4]) ^ TABLE6(key[3]) ^ TABLE7(key[2]);
			
		tmp[2] = 
			TABLE0(key[2]) ^ TABLE1(key[1]) ^ TABLE2(key[0]) ^ TABLE3(key[7]) ^
			TABLE4(key[6]) ^ TABLE5(key[5]) ^ TABLE6(key[4]) ^ TABLE7(key[3]);
			
		tmp[3] = 
			TABLE0(key[3]) ^ TABLE1(key[2]) ^ TABLE2(key[1]) ^ TABLE3(key[0]) ^
			TABLE4(key[7]) ^ TABLE5(key[6]) ^ TABLE6(key[5]) ^ TABLE7(key[4]);
			
		tmp[4] = 
			TABLE0(key[4]) ^ TABLE1(key[3]) ^ TABLE2(key[2]) ^ TABLE3(key[1]) ^
			TABLE4(key[0]) ^ TABLE5(key[7]) ^ TABLE6(key[6]) ^ TABLE7(key[5]);
			
		tmp[5] = 
			TABLE0(key[5]) ^ TABLE1(key[4]) ^ TABLE2(key[3]) ^ TABLE3(key[2]) ^
			TABLE4(key[1]) ^ TABLE5(key[0]) ^ TABLE6(key[7]) ^ TABLE7(key[6]);
			
		tmp[6] = 
			TABLE0(key[6]) ^ TABLE1(key[5]) ^ TABLE2(key[4]) ^ TABLE3(key[3]) ^
			TABLE4(key[2]) ^ TABLE5(key[1]) ^ TABLE6(key[0]) ^ TABLE7(key[7]);
			
		tmp[7] = 		
			TABLE0(key[7]) ^ TABLE1(key[6]) ^ TABLE2(key[5]) ^ TABLE3(key[4]) ^
			TABLE4(key[3]) ^ TABLE5(key[2]) ^ TABLE6(key[1]) ^ TABLE7(key[0]);
			
		memcpy (key, tmp, sizeof (tmp));
		
		/* state */
		tmp[0] ^= 
			TABLE0(state[0]) ^ TABLE1(state[7]) ^ TABLE2(state[6]) ^ TABLE3(state[5]) ^
			TABLE4(state[4]) ^ TABLE5(state[3]) ^ TABLE6(state[2]) ^ TABLE7(state[1]);
			
		tmp[1] ^= 
			TABLE0(state[1]) ^ TABLE1(state[0]) ^ TABLE2(state[7]) ^ TABLE3(state[6]) ^
			TABLE4(state[5]) ^ TABLE5(state[4]) ^ TABLE6(state[3]) ^ TABLE7(state[2]);
			
		tmp[2] ^= 
			TABLE0(state[2]) ^ TABLE1(state[1]) ^ TABLE2(state[0]) ^ TABLE3(state[7]) ^
			TABLE4(state[6]) ^ TABLE5(state[5]) ^ TABLE6(state[4]) ^ TABLE7(state[3]);
			
		tmp[3] ^= 
			TABLE0(state[3]) ^ TABLE1(state[2]) ^ TABLE2(state[1]) ^ TABLE3(state[0]) ^
			TABLE4(state[7]) ^ TABLE5(state[6]) ^ TABLE6(state[5]) ^ TABLE7(state[4]);
			
		tmp[4] ^= 
			TABLE0(state[4]) ^ TABLE1(state[3]) ^ TABLE2(state[2]) ^ TABLE3(state[1]) ^
			TABLE4(state[0]) ^ TABLE5(state[7]) ^ TABLE6(state[6]) ^ TABLE7(state[5]);
			
		tmp[5] ^= 
			TABLE0(state[5]) ^ TABLE1(state[4]) ^ TABLE2(state[3]) ^ TABLE3(state[2]) ^
			TABLE4(state[1]) ^ TABLE5(state[0]) ^ TABLE6(state[7]) ^ TABLE7(state[6]);
			
		tmp[6] ^= 
			TABLE0(state[6]) ^ TABLE1(state[5]) ^ TABLE2(state[4]) ^ TABLE3(state[3]) ^
			TABLE4(state[2]) ^ TABLE5(state[1]) ^ TABLE6(state[0]) ^ TABLE7(state[7]);
			
		tmp[7] ^= 		
			TABLE0(state[7]) ^ TABLE1(state[6]) ^ TABLE2(state[5]) ^ TABLE3(state[4]) ^
			TABLE4(state[3]) ^ TABLE5(state[2]) ^ TABLE6(state[1]) ^ TABLE7(state[0]);
			
		memcpy (state, tmp, sizeof (tmp));
	}
	
	memcpy (tmp, hash, sizeof (tmp));
	for (uint_fast8_t x = 0; x < 8; x++) {
		tmp[x] ^= state[x] ^ u8_to_u64_be (&block[x * 8]);
	}
	memcpy (hash, tmp, sizeof (tmp));
#endif
}

#endif
