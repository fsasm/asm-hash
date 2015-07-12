/*
 * sha256.h
 * Author: Fabjan Sukalia(fsukalia@gmail.com)
 * Date: 2014-04-28
 */

#ifndef SHA256_H
#define SHA256_H

#include "block.h"
#include "sha256_core.h"

/* SHA-256 */
typedef struct {
	uint8_t buffer[SHA256_BLOCK_SIZE];
	uint32_t hash[8];
	block b;
} sha256_context;

void sha256_init(sha256_context* ctxt);
void sha256_add(sha256_context* ctxt, const uint8_t data[], size_t length);
void sha256_finalize(sha256_context* ctxt);
void sha256_get_digest(sha256_context* ctxt, uint8_t digest[SHA256_DIGEST_SIZE]);

/* SHA-224 */
typedef sha256_context sha224_context;

void sha224_init(sha224_context* ctxt);
void sha224_add(sha224_context* ctxt, const uint8_t data[], uint64_t length);
void sha224_finalize(sha224_context* ctxt);
void sha224_get_digest(sha224_context* ctxt, uint8_t digest[SHA224_DIGEST_SIZE]);

#endif

