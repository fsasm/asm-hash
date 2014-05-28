#include <stdio.h>
#include <stdint.h>
#include <time.h>
#define MD5_USE_ASM
#include "md5.h"
#include "test.h"

int main (void) {
	uint32_t hash_asm[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
	uint32_t hash_ref[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};

	md5_process_blocks (test_block_128, hash_ref, 2);
	md5_process_blocks_asm (test_block_128, hash_asm, 2);

	printf ("asm: %X %X %X %X\n", hash_asm[0], hash_asm[1], hash_asm[2], hash_asm[3]);
	printf ("ref: %X %X %X %X\n", hash_ref[0], hash_ref[1], hash_ref[2], hash_ref[3]);
	if (hash_asm[0] == hash_ref[0] && hash_asm[1] == hash_ref[1] &&
		hash_asm[2] == hash_ref[2] && hash_asm[3] == hash_ref[3])
		printf ("identical\n");
	else
		printf ("different\n");

	return 0;
}
