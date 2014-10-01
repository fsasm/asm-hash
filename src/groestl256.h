/*
 * groestl256.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-09-24
 */

#ifndef GROESTL256_H
#define GROESTL256_H

#include <stdint.h>
#include "block.h"

/* GROESTL-256 */
#define GROESTL256_BLOCK_SIZE 64
#define GROESTL256_DIGEST_SIZE 32
#define GROESTL256_HASH_SIZE 64

typedef struct {
	uint8_t buffer[64];
	uint8_t hash[8][8];
	block b;
} groestl256_context;

void groestl256_init (groestl256_context* ctxt); 
void groestl256_init_hash (uint8_t hash[8][8]);
void groestl256_add (groestl256_context* ctxt, const uint8_t data[], size_t length);
void groestl256_finalize (groestl256_context* ctxt);
void groestl256_get_digest (groestl256_context* ctxt, uint8_t digest[GROESTL256_DIGEST_SIZE]);

void groestl256_process_block (const uint8_t block[64], uint8_t hash[8][8], unsigned int n);

/* GROESTL-224 */
#define GROESTL224_BLOCK_SIZE 64
#define GROESTL224_DIGEST_SIZE 28
#define GROESTL224_HASH_SIZE 64

typedef groestl256_context groestl224_context;

void groestl224_init (groestl224_context* ctxt); 
void groestl224_init_hash (uint8_t hash[8][8]);
void groestl224_add (groestl224_context* ctxt, const uint8_t data[], size_t length);
void groestl224_finalize (groestl224_context* ctxt);
void groestl224_get_digest (groestl224_context* ctxt, uint8_t digest[GROESTL224_DIGEST_SIZE]);

#endif
