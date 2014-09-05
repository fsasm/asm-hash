/*
 * hash_test.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-05-30
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "test.h"

#ifdef HASH_MD5

#define MD5_ENABLE_ASM
#include "md5.h"
#define HASH_TYPE uint32_t
#define HASH_SIZE 4
#define HASH_INIT md5_init_hash
#define PROCESS_BLOCKS(hash) md5_process_blocks (test_block_128, hash, 2)
#define PROCESS_BLOCKS_ASM(hash) md5_process_blocks_asm (test_block_128, hash, 2)

#elif HASH_SHA1

#define SHA1_ENABLE_ASM
#include "sha1.h"
#define HASH_TYPE uint32_t
#define HASH_SIZE 5
#define HASH_INIT sha1_init_hash
#define PROCESS_BLOCKS(hash) sha1_process_blocks (test_block_128, hash, 2)
#define PROCESS_BLOCKS_ASM(hash) sha1_process_blocks_asm (test_block_128, hash, 2)

#elif HASH_SHA256

#define SHA256_ENABLE_ASM
#include "sha256.h"
#define HASH_TYPE uint32_t
#define HASH_SIZE 8
#define HASH_INIT sha256_init_hash
#define PROCESS_BLOCKS(hash) sha256_process_blocks (test_block_64, hash, 1)
#define PROCESS_BLOCKS_ASM(hash) sha256_process_block_asm (test_block_64, hash)

#endif

int main (void) {
	HASH_TYPE hash_asm[HASH_SIZE];
	HASH_TYPE hash_ref[HASH_SIZE];
	
	HASH_INIT (hash_asm);
	HASH_INIT (hash_ref);
	
	PROCESS_BLOCKS (hash_ref);
	PROCESS_BLOCKS_ASM (hash_asm);
	
	printf ("asm: ");
	for (int i = 0; i < HASH_SIZE; i++) {
		printf ("%X ", hash_asm[i]);
	}
	
	printf ("\nref: ");
	for (int i = 0; i < HASH_SIZE; i++) {
		printf ("%X ", hash_ref[i]);
	}
	
	bool identical = true;
	for (int i = 0; i < HASH_SIZE; i++) {
		identical &= (hash_asm[i] == hash_ref[i]);
	}
	
	if (identical) 
		printf ("\nidentical\n");
	else 
		printf ("\ndifferent\n");
	
	return 0;
}