/*
 * md5.h
 * Author Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-04
 */

#ifndef MD5_H
#define MD5_H

#include "block.h"
#include "md5_core.h"

typedef struct {
	uint8_t buffer[MD5_BLOCK_SIZE];
	uint32_t hash[4];
	block b;
} md5_context;

void md5_init (md5_context* ctxt);
void md5_add (md5_context* ctxt, const uint8_t data[], size_t length);
void md5_finalize (md5_context* ctxt);
void md5_get_digest (md5_context* ctxt, uint8_t digest[MD5_DIGEST_SIZE]);

#endif

