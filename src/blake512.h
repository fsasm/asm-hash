/*
 * blake512.h
 * Author: Fabjan Sukalia(fsukalia@gmail.com)
 * Date: 2014-08-25
 */

#ifndef BLAKE512_H
#define BLAKE512_H

#include "block.h"
#include "blake512_core.h"

/* BLAKE-512 */
typedef struct {
	uint8_t buffer[BLAKE512_BLOCK_SIZE];
	uint64_t hash[8];
	uint8_t salt[BLAKE512_SALT_SIZE];
	block b;
} blake512_context;

void blake512_init(blake512_context* ctxt);
void blake512_init_with_salt(blake512_context* ctxt, uint8_t salt[BLAKE512_SALT_SIZE]);
void blake512_add(blake512_context* ctxt, const uint8_t data[], size_t length);
void blake512_finalize(blake512_context* ctxt);
void blake512_get_digest(blake512_context* ctxt, uint8_t digest[BLAKE512_DIGEST_SIZE]);

/* BLAKE-384 */
typedef blake512_context blake384_context;

void blake384_init(blake384_context* ctxt);
void blake384_init_with_salt(blake384_context* ctxt, uint8_t salt[BLAKE384_SALT_SIZE]);
void blake384_add(blake384_context* ctxt, const uint8_t data[], size_t length);
void blake384_finalize(blake384_context* ctxt);
void blake384_get_digest(blake384_context* ctxt, uint8_t digest[BLAKE384_DIGEST_SIZE]);

#endif

