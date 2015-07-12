/*
 * blake256.h
 * Author: Fabjan Sukalia(fsukalia@gmail.com)
 * Date: 2014-07-09 
 */

#ifndef BLAKE256_H
#define BLAKE256_H

#include "block.h"
#include "blake256_core.h"

/* BLAKE-256 */
typedef struct {
	uint8_t buffer[BLAKE256_BLOCK_SIZE];
	uint32_t hash[8];
	uint8_t salt[BLAKE256_SALT_SIZE];
	block b;
} blake256_context;

void blake256_init(blake256_context* ctxt); 
void blake256_init_with_salt(blake256_context* ctxt, uint8_t salt[BLAKE256_SALT_SIZE]);
void blake256_add(blake256_context* ctxt, const uint8_t data[], size_t length);
void blake256_finalize(blake256_context* ctxt);
void blake256_get_digest(blake256_context* ctxt, uint8_t digest[BLAKE256_DIGEST_SIZE]);

/* BLAKE-224 */
typedef blake256_context blake224_context;

void blake224_init(blake224_context* ctxt); 
void blake224_init_with_salt(blake224_context* ctxt, uint8_t salt[BLAKE224_SALT_SIZE]);
void blake224_add(blake224_context* ctxt, const uint8_t data[], size_t length);
void blake224_finalize(blake224_context* ctxt);
void blake224_get_digest(blake224_context* ctxt, uint8_t digest[BLAKE224_DIGEST_SIZE]);

#endif
