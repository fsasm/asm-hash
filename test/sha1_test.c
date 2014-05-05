#include <stdint.h>
#include <stdio.h>
#include "sha1.h"

extern void sha1_process_block_asm (uint8_t block[64], uint32_t hash[5]);

uint8_t test_block[64] = {
	1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 52, 53, 54, 55, 56,
	57, 58, 59, 60, 61, 62, 63, 64
};

int main (void) {
	uint32_t hash_asm[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
	uint32_t hash_ref[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};

	sha1_process_block (test_block, hash_ref);
	sha1_process_block_asm (test_block, hash_asm);

	printf ("asm: %X %X %X %X %X\n", hash_asm[0], hash_asm[1], hash_asm[2], hash_asm[3], hash_asm[4]);
	printf ("ref: %X %X %X %X %X\n", hash_ref[0], hash_ref[1], hash_ref[2], hash_ref[3], hash_ref[4]);
	if (hash_asm[0] == hash_ref[0] && hash_asm[1] == hash_ref[1] &&
		hash_asm[2] == hash_ref[2] && hash_asm[3] == hash_ref[3] &&
		hash_asm[4] == hash_ref[4])
		printf ("identical\n");
	else
		printf ("different\n");

	return 0;

}