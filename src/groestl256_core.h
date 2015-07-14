/*
 * groestl256_core.h
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-14
 */

#ifndef GROESTL256_CORE_H
#define GROESTL256_CORE_H

#include <stdint.h>

/* GROESTL-256 */
#define GROESTL256_BLOCK_SIZE	(64)
#define GROESTL256_DIGEST_SIZE	(32)
#define GROESTL256_HASH_SIZE	(64)

void groestl256_init_hash(uint8_t hash[8][8]);
void groestl256_process_block(const uint8_t block[64], uint8_t hash[8][8], unsigned int n);
void groestl256_finalize_hash(uint8_t hash[8][8]);

/* GROESTL-224 */
#define GROESTL224_BLOCK_SIZE	(64)
#define GROESTL224_DIGEST_SIZE	(28)
#define GROESTL224_HASH_SIZE	(64)

void groestl224_init_hash(uint8_t hash[8][8]);

#endif

