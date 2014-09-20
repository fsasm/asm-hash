/*
 * blake256.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-07-09 
 */

#ifndef BLAKE256_H
#define BLAKE256_H

#include <stdint.h>
#include "block.h"

/* BLAKE-256 */
#define BLAKE256_BLOCK_SIZE 64
#define BLAKE256_DIGEST_SIZE 32
#define BLAKE256_HASH_SIZE 32
#define BLAKE256_SALT_SIZE 16

typedef struct {
	uint8_t buffer[64];
	uint32_t hash[8];
	uint8_t salt[16];
	block b;
} blake256_context;

void blake256_init (blake256_context* ctxt); 
void blake256_init_with_salt (blake256_context* ctxt, uint8_t salt[16]);
void blake256_init_hash (uint32_t hash[8]);
void blake256_add (blake256_context* ctxt, const uint8_t data[], size_t length);
void blake256_finalize (blake256_context* ctxt);
void blake256_get_digest (blake256_context* ctxt, uint8_t digest[BLAKE256_DIGEST_SIZE]);

void blake256_process_block (const uint8_t block[64], uint32_t hash[8], uint64_t counter);
void blake256_process_block_with_salt (const uint8_t block[64], uint32_t hash[8], const uint32_t salt[4], uint64_t counter);

#if defined (BLAKE256_USE_ASM) || defined (BLAKE256_ENABLE_ASM)
extern void blake256_process_block_asm (const uint8_t block[64], uint32_t hash[8], uint64_t counter);
#endif

/* BLAKE-224 */
#define BLAKE224_BLOCK_SIZE 64
#define BLAKE224_DIGEST_SIZE 28
#define BLAKE224_HASH_SIZE 32
#define BLAKE224_SALT_SIZE 16

typedef blake256_context blake224_context;

void blake224_init (blake224_context* ctxt); 
void blake224_init_with_salt (blake224_context* ctxt, uint8_t salt[16]);
void blake224_init_hash (uint32_t hash[8]);
void blake224_add (blake224_context* ctxt, const uint8_t data[], size_t length);
void blake224_finalize (blake224_context* ctxt);
void blake224_get_digest (blake224_context* ctxt, uint8_t digest[BLAKE224_DIGEST_SIZE]);

#endif
