/*
 * sha1.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-25
 */

#ifndef SHA1_H
#define SHA1_H

#include "block.h"
#include "sha1_core.h"

typedef struct {
	uint8_t buffer[SHA1_BLOCK_SIZE];
	uint32_t hash[5];
	block b;
} sha1_context;

void sha1_init(sha1_context* ctxt);
void sha1_add(sha1_context* ctxt, const uint8_t data[], size_t length);
void sha1_finalize(sha1_context* ctxt);
void sha1_get_digest(sha1_context* ctxt, uint8_t digest[SHA1_DIGEST_SIZE]);

#endif

