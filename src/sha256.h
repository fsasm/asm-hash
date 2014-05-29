/*
 * sha256.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-28
 */

#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include "block.h"

/* SHA-256 */
#define SHA256_BLOCK_SIZE 64
#define SHA256_DIGEST_SIZE 32
#define SHA256_HASH_SIZE 32

typedef struct {
	uint8_t buffer[64];
	uint32_t hash[8];
	block b;
} sha256_context;

void sha256_init (sha256_context* ctxt);
void sha256_init_hash (uint32_t hash[8]);
void sha256_add (sha256_context* ctxt, const uint8_t data[], size_t length);
void sha256_finalize (sha256_context* ctxt);
void sha256_get_digest (sha256_context* ctxt, uint8_t digest[SHA256_DIGEST_SIZE]);

void sha256_process_blocks (const uint8_t block[], uint32_t hash[8], unsigned int n);

#if defined (SHA256_USE_ASM) || defined (SHA256_ENABLE_ASM)
extern void sha256_process_block_asm (const uint8_t block[64], uint32_t hash[8]);
#endif

/* SHA-224 */
#define SHA224_BLOCK_SIZE 64
#define SHA224_HASH_SIZE 32
#define SHA224_DIGEST_SIZE 28

typedef sha256_context sha224_context;

void sha224_init (sha224_context* ctxt);
void sha224_init_hash (uint32_t hash[8]);
void sha224_add (sha224_context* ctxt, const uint8_t data[], uint64_t length);
void sha224_finalize (sha224_context* ctxt);
void sha224_get_digest (sha224_context* ctxt, uint8_t digest[SHA224_DIGEST_SIZE]);

#endif

