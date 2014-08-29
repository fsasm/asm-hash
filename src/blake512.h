/*
 * blake512.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-08-25
 */

#ifndef BLAKE512_H
#define BLAKE512_H

#include <stdint.h>
#include "block.h"

/* BLAKE-512 */
#define BLAKE512_BLOCK_SIZE 128
#define BLAKE512_DIGEST_SIZE 64
#define BLAKE512_HASH_SIZE 64
#define BLAKE512_SALT_SIZE 32

typedef struct {
	uint8_t buffer[128];
	uint64_t hash[8];
	uint8_t salt[32];
	block b;
} blake512_context;

void blake512_init (blake512_context* ctxt);
void blake512_init_with_salt (blake512_context* ctxt, uint8_t salt[32]);
void blake512_init_hash (uint64_t hash[8]);
void blake512_add (blake512_context* ctxt, const uint8_t data[], size_t length);
void blake512_finalize (blake512_context* ctxt);
void blake512_get_digest (blake512_context* ctxt, uint8_t digest[BLAKE512_DIGEST_SIZE]);

void blake512_process_block (const uint8_t block[128], uint64_t hash[8], uint64_t counter);
void blake512_process_block_with_salt (const uint8_t block[128], uint64_t hash[8], const uint64_t salt[4], uint64_t counter);

/* BLAKE-384 */
#define BLAKE384_BLOCK_SIZE 128
#define BLAKE384_DIGEST_SIZE 48
#define BLAKE384_HASH_SIZE 64
#define BLAKE384_SALT_SIZE 32

typedef blake512_context blake384_context;

void blake384_init (blake384_context* ctxt);
void blake384_init_with_salt (blake384_context* ctxt, uint8_t salt[32]);
void blake384_init_hash (uint64_t hash[8]);
void blake384_add (blake384_context* ctxt, const uint8_t data[], size_t length);
void blake384_finalize (blake384_context* ctxt);
void blake384_get_digest (blake384_context* ctxt, uint8_t digest[BLAKE384_DIGEST_SIZE]);


#endif
