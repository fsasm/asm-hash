/*
 * groestl512_core.h
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-17
 */

#ifndef GROESTL512_CORE_H
#define GROESTL512_CORE_H

#include <stdint.h>

/* GROESTL-512 */
#define GROESTL512_BLOCK_SIZE	(128)
#define GROESTL512_DIGEST_SIZE	(64)
#define GROESTL512_HASH_SIZE	(128)

void groestl512_init_hash(uint8_t hash[8][16]);
void groestl512_process_block(const uint8_t block[128], uint8_t hash[8][16], unsigned int n);
void groestl512_finalize_hash(uint8_t hash[8][16]);

/* GROESTL-384 */
#define GROESTL384_BLOCK_SIZE	(128)
#define GROESTL384_DIGEST_SIZE	(48)
#define GROESTL384_HASH_SIZE	(128)

void groestl384_init_hash(uint8_t hash[8][16]);

#endif

