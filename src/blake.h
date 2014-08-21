/*
 * blake.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-07-09 
 */

#ifndef BLAKE_H
#define BLAKE_H

#include <stdint.h>
#include "block.h"

/* BLAKE-256 */
#define BLAKE256_BLOCK_SIZE 64
#define BLAKE256_DIGEST_SIZE 32
#define BLAKE256_HASH_SIZE 32
#define BLAKE256_SALT_SIZE 16

typedef struct {
	uint8_t buffer[64];
	uint32_t hash[8];
	uint8_t salt[16]; 
	block b;
} blake256_context;

void blake256_init (blake256_context* ctxt); 
void blake256_init_with_salt (blake256_context* ctxt, uint8_t salt[16]);
void blake256_init_hash (uint32_t hash[8]);
void blake256_add (blake256_context* ctxt, const uint8_t data[], size_t length);
void blake256_finalize (blake256_context* ctxt);
void blake256_get_digest (blake256_context* ctxt, uint8_t digest[BLAKE256_DIGEST_SIZE]);

void blake256_process_block (const uint8_t block[64], uint32_t hash[8], const uint32_t salt[4], uint64_t counter);
void blake256_process_block_with_salt (/* TODO */);

#endif
