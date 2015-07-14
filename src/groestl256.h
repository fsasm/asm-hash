/*
 * groestl256.h
 * Author: Fabjan Sukalia(fsukalia@gmail.com)
 * Date: 2014-09-24
 */

#ifndef GROESTL256_H
#define GROESTL256_H

#include "block.h"
#include "groestl256_core.h"

/* GROESTL-256 */
typedef struct {
	uint8_t buffer[GROESTL256_BLOCK_SIZE];
	uint8_t hash[8][8];
	block b;
} groestl256_context;

void groestl256_init(groestl256_context* ctxt); 
void groestl256_add(groestl256_context* ctxt, const uint8_t data[], size_t length);
void groestl256_finalize(groestl256_context* ctxt);
void groestl256_get_digest(groestl256_context* ctxt, uint8_t digest[GROESTL256_DIGEST_SIZE]);

/* GROESTL-224 */
typedef groestl256_context groestl224_context;

void groestl224_init(groestl224_context* ctxt); 
void groestl224_add(groestl224_context* ctxt, const uint8_t data[], size_t length);
void groestl224_finalize(groestl224_context* ctxt);
void groestl224_get_digest(groestl224_context* ctxt, uint8_t digest[GROESTL224_DIGEST_SIZE]);

#endif

