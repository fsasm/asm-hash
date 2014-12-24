/*
 * jh.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-10-09
 */
 
#ifndef JH256_H
#define JH256_H

#include <stdint.h>
#include "block.h"

/* JH-256 */
#define JH256_BLOCK_SIZE 64
#define JH256_DIGEST_SIZE 32
#define JH256_HASH_SIZE 128

typedef struct {
	uint8_t buffer[64];
	uint64_t hash[8][2];
	block b;
} jh256_context;

void jh256_init (jh256_context* ctxt);
void jh256_init_hash (uint64_t hash[8][2]);
void jh256_add (jh256_context* ctxt, const uint8_t data[], size_t length);
void jh256_finalize (jh256_context* ctxt);
void jh256_get_digest (jh256_context* ctxt, uint8_t digest[JH256_DIGEST_SIZE]);

void jh_process_block (const uint8_t block[64], uint64_t hash[8][2]);

/* JH-224 */
#define JH224_BLOCK_SIZE 64
#define JH224_DIGEST_SIZE 28
#define JH224_HASH_SIZE 128

typedef jh256_context jh224_context;

void jh224_init (jh224_context* ctxt);
void jh224_init_hash (uint64_t hash[8][2]);
void jh224_add (jh224_context* ctxt, const uint8_t data[], size_t length);
void jh224_finalize (jh224_context* ctxt);
void jh224_get_digest (jh224_context* ctxt, uint8_t digest[JH224_DIGEST_SIZE]);

/* JH-384 */
#define JH384_BLOCK_SIZE 64
#define JH384_DIGEST_SIZE 48
#define JH384_HASH_SIZE 128

typedef jh256_context jh384_context;

void jh384_init (jh384_context* ctxt);
void jh384_init_hash (uint64_t hash[8][2]);
void jh384_add (jh384_context* ctxt, const uint8_t data[], size_t length);
void jh384_finalize (jh384_context* ctxt);
void jh384_get_digest (jh384_context* ctxt, uint8_t digest[JH384_DIGEST_SIZE]);

/* JH-512 */
#define JH512_BLOCK_SIZE 64
#define JH512_DIGEST_SIZE 64
#define JH512_HASH_SIZE 128

typedef jh256_context jh512_context;

void jh512_init (jh512_context* ctxt);
void jh512_init_hash (uint64_t hash[8][2]);
void jh512_add (jh512_context* ctxt, const uint8_t data[], size_t length);
void jh512_finalize (jh512_context* ctxt);
void jh512_get_digest (jh512_context* ctxt, uint8_t digest[JH512_DIGEST_SIZE]);

#endif
