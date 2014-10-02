/*
 * groestl512.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-10-02
 */

#ifndef GROESTL512_H
#define GROESTL512_H

#include <stdint.h>
#include "block.h"

/* GROESTL-512 */
#define GROESTL512_BLOCK_SIZE 128
#define GROESTL512_DIGEST_SIZE 64
#define GROESTL512_HASH_SIZE 128

typedef struct {
	uint8_t buffer[128];
	uint8_t hash[8][16];
	block b;
} groestl512_context;

void groestl512_init (groestl512_context* ctxt); 
void groestl512_init_hash (uint8_t hash[8][16]);
void groestl512_add (groestl512_context* ctxt, const uint8_t data[], size_t length);
void groestl512_finalize (groestl512_context* ctxt);
void groestl512_get_digest (groestl512_context* ctxt, uint8_t digest[GROESTL512_DIGEST_SIZE]);

void groestl512_process_block (const uint8_t block[128], uint8_t hash[8][16], unsigned int n);

/* GROESTL-384 */
#define GROESTL384_BLOCK_SIZE 128
#define GROESTL384_DIGEST_SIZE 48
#define GROESTL384_HASH_SIZE 128

typedef groestl512_context groestl384_context;

void groestl384_init (groestl384_context* ctxt); 
void groestl384_init_hash (uint8_t hash[8][16]);
void groestl384_add (groestl384_context* ctxt, const uint8_t data[], size_t length);
void groestl384_finalize (groestl384_context* ctxt);
void groestl384_get_digest (groestl384_context* ctxt, uint8_t digest[GROESTL384_DIGEST_SIZE]);

#endif
