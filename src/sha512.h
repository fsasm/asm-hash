/*
 * sha512.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-05-01
 */
#ifndef SHA512_H
#define SHA512_H

#include <stdint.h>
#include "block.h"

#define SHA512_BLOCK_SIZE 128
#define SHA512_DIGEST_SIZE 64
#define SHA512_224_DIGEST_SIZE 28
#define SHA512_256_DIGEST_SIZE 32
#define SHA512_HASH_SIZE 64

typedef struct {
	uint8_t buffer[128];
	uint64_t hash[8];
	block b;
} sha512_context;

void sha512_init (sha512_context* ctxt);
void sha512_224_init (sha512_context* ctxt);
void sha512_256_init (sha512_context* ctxt);

void sha512_add (sha512_context* ctxt, uint8_t data[], size_t length);
void sha512_finalize (sha512_context* ctxt);
void sha512_get_digest (sha512_context* ctxt, uint8_t digest[SHA512_DIGEST_SIZE]);
void sha512_224_get_digest (sha512_context* ctxt, uint8_t digest[SHA512_224_DIGEST_SIZE]);
void sha512_256_get_digest (sha512_context* ctxt, uint8_t digest[SHA512_256_DIGEST_SIZE]);

void sha512_process_blocks (uint8_t block[], uint64_t hash[8], unsigned int n);
#endif

