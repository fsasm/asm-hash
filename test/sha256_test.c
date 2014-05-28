#include <stdint.h>
#include <stdio.h>
#include "sha256.h"
#include "test.h"

int main (void) {
	uint32_t hash_asm[8] = {0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A, 0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19};
	uint32_t hash_ref[8] = {0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A, 0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19};

	sha256_process_blocks (test_block_64, hash_ref, 1);
	//sha256_process_block_asm (test_block_64, hash_asm);

	printf ("asm: %X %X %X %X %X %X %X %X\n", hash_asm[0], hash_asm[1], hash_asm[2], hash_asm[3], hash_asm[4], hash_asm[5], hash_asm[6], hash_asm[7]);
	printf ("ref: %X %X %X %X %X %X %X %X\n", hash_ref[0], hash_ref[1], hash_ref[2], hash_ref[3], hash_ref[4], hash_ref[5], hash_ref[6], hash_ref[7]);
	if (hash_asm[0] == hash_ref[0] && hash_asm[1] == hash_ref[1] &&
		hash_asm[2] == hash_ref[2] && hash_asm[3] == hash_ref[3] &&
		hash_asm[4] == hash_ref[4] && hash_asm[5] == hash_ref[5] &&
		hash_asm[6] == hash_ref[6] && hash_asm[7] == hash_ref[7])
		printf ("identical\n");
	else
		printf ("different\n");

	return 0;

}