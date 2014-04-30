/*
 * sha224.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-28
 */

#ifndef SHA224_H
#define SHA224_H

#include <stdint.h>
#include "sha256.h"

#define SHA224_BLOCK_SIZE 64
#define SHA224_HASH_SIZE 32
#define SHA224_DIGEST_SIZE 28

typedef sha256_context sha224_context;

void sha224_init (sha224_context* ctxt);
void sha224_add (sha224_context* ctxt, uint8_t data[], uint64_t length);
void sha224_finalize (sha224_context* ctxt);
void sha224_get_digest (sha224_context* ctxt, uint8_t digest[SHA224_DIGEST_SIZE]);

#endif
