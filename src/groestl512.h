/*
 * groestl512.h
 * Author: Fabjan Sukalia(fsukalia@gmail.com)
 * Date: 2014-10-02
 */

#ifndef GROESTL512_H
#define GROESTL512_H

#include "block.h"
#include "groestl512_core.h"

/* GROESTL-512 */
typedef struct {
	uint8_t buffer[GROESTL512_BLOCK_SIZE];
	uint8_t hash[8][16];
	block b;
} groestl512_context;

void groestl512_init(groestl512_context* ctxt); 
void groestl512_add(groestl512_context* ctxt, const uint8_t data[], size_t length);
void groestl512_finalize(groestl512_context* ctxt);
void groestl512_get_digest(groestl512_context* ctxt, uint8_t digest[GROESTL512_DIGEST_SIZE]);

/* GROESTL-384 */
typedef groestl512_context groestl384_context;

void groestl384_init(groestl384_context* ctxt); 
void groestl384_add(groestl384_context* ctxt, const uint8_t data[], size_t length);
void groestl384_finalize(groestl384_context* ctxt);
void groestl384_get_digest(groestl384_context* ctxt, uint8_t digest[GROESTL384_DIGEST_SIZE]);

#endif

