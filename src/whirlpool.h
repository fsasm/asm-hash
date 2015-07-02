/*
 * whirlpool.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-06-13
 */

#ifndef WHIRLPOOL_H
#define WHIRLPOOL_H

#include <stdint.h>
#include "block.h"

#define WHIRLPOOL_BLOCK_SIZE 64
#define WHIRLPOOL_DIGEST_SIZE 64
#define WHIRLPOOL_HASH_SIZE 64

typedef struct {
	uint8_t buffer[64];
	uint64_t hash[8];
	block b;
} whirlpool_context;

void whirlpool_init (whirlpool_context* ctxt);
void whirlpool_init_hash (uint64_t hash[8]);
void whirlpool_add (whirlpool_context* ctxt, const uint8_t data[], size_t length);
void whirlpool_finalize (whirlpool_context* ctxt);
void whirlpool_get_digest (whirlpool_context* ctxt, uint8_t digest[WHIRLPOOL_DIGEST_SIZE]);

void whirlpool_process_blocks (const uint8_t block[], uint64_t hash[8], unsigned int n);

#if defined (WHIRLPOOL_USE_ASM) || defined (WHIRLPOOL_ENABLE_ASM)
#if __x86_64__
__attribute__((sysv_abi))
#endif
extern void whirlpool_process_blocks_asm (const uint8_t block[], uint64_t hash[8], unsigned int n);
#endif

#endif
