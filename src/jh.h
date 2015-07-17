/*
 * jh.h
 * Author: Fabjan Sukalia(fsukalia@gmail.com)
 * Date: 2014-10-09
 */
 
#ifndef JH256_H
#define JH256_H

#include "block.h"
#include "jh_core.h"

/* JH-256 */
typedef struct {
	uint8_t buffer[JH256_BLOCK_SIZE];
	uint64_t hash[8][2];
	block b;
} jh256_context;

void jh256_init(jh256_context* ctxt);
void jh256_add(jh256_context* ctxt, const uint8_t data[], size_t length);
void jh256_finalize(jh256_context* ctxt);
void jh256_get_digest(jh256_context* ctxt, uint8_t digest[JH256_DIGEST_SIZE]);

/* JH-224 */
typedef jh256_context jh224_context;

void jh224_init(jh224_context* ctxt);
void jh224_add(jh224_context* ctxt, const uint8_t data[], size_t length);
void jh224_finalize(jh224_context* ctxt);
void jh224_get_digest(jh224_context* ctxt, uint8_t digest[JH224_DIGEST_SIZE]);

/* JH-384 */
typedef jh256_context jh384_context;

void jh384_init(jh384_context* ctxt);
void jh384_add(jh384_context* ctxt, const uint8_t data[], size_t length);
void jh384_finalize(jh384_context* ctxt);
void jh384_get_digest(jh384_context* ctxt, uint8_t digest[JH384_DIGEST_SIZE]);

/* JH-512 */
typedef jh256_context jh512_context;

void jh512_init(jh512_context* ctxt);
void jh512_add(jh512_context* ctxt, const uint8_t data[], size_t length);
void jh512_finalize(jh512_context* ctxt);
void jh512_get_digest(jh512_context* ctxt, uint8_t digest[JH512_DIGEST_SIZE]);

#endif

