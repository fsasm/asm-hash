/*
 * sha384.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-05-01
 */

#ifndef SHA384_H
#define SHA384_H

#include "sha512.h"

#define SHA384_BLOCK_SIZE 128
#define SHA384_DIGEST_SIZE 48
#define SHA384_HASH_SIZE 64

typedef sha512_context sha384_context;

void sha384_init (sha384_context* ctxt);
void sha384_add (sha384_context* ctxt, uint8_t data[], size_t length);
void sha384_finalize (sha384_context* ctxt);
void sha384_get_digest (sha384_context* ctxt, uint8_t digest[SHA384_DIGEST_SIZE]);
#endif

