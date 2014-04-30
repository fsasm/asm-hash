/*
 * sha256.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-28
 */

#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include "block.h"

#define SHA256_BLOCK_SIZE 64
#define SHA256_DIGEST_SIZE 32
#define SHA256_HASH_SIZE 32

typedef struct {
	uint8_t buffer[64];
	uint32_t hash[8];
	block b;
} sha256_context;

void sha256_init (sha256_context* ctxt);
void sha256_add (sha256_context* ctxt, uint8_t data[], uint64_t length);
void sha256_finalize (sha256_context* ctxt);
void sha256_get_digest (sha256_context* ctxt, uint8_t digest[SHA256_DIGEST_SIZE]);

void sha256_process_block (uint8_t block[64], uint32_t hash[5]);
#endif

