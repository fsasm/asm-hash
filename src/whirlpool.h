/*
 * whirlpool.h
 * Author: Fabjan Sukalia(fsukalia@gmail.com)
 * Date: 2014-06-13
 */

#ifndef WHIRLPOOL_H
#define WHIRLPOOL_H

#include "block.h"
#include "whirlpool_core.h"

typedef struct {
	uint8_t buffer[WHIRLPOOL_BLOCK_SIZE];
	uint64_t hash[8];
	block b;
} whirlpool_context;

void whirlpool_init(whirlpool_context* ctxt);
void whirlpool_add(whirlpool_context* ctxt, const uint8_t data[], size_t length);
void whirlpool_finalize(whirlpool_context* ctxt);
void whirlpool_get_digest(whirlpool_context* ctxt, uint8_t digest[WHIRLPOOL_DIGEST_SIZE]);

#endif

