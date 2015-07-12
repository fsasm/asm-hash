/*
 * blake256_core.h
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-12 
 */

#ifndef BLAKE256_CORE_H
#define BLAKE256_CORE_H

#include <stdint.h>

/* BLAKE-256 */
#define BLAKE256_BLOCK_SIZE		(64)
#define BLAKE256_DIGEST_SIZE	(32)
#define BLAKE256_HASH_SIZE		(32)
#define BLAKE256_SALT_SIZE		(16)

void blake256_init_hash(uint32_t hash[8]);
void blake256_process_block(const uint8_t block[64], uint32_t hash[8], uint64_t counter);
void blake256_process_block_with_salt(const uint8_t block[64], uint32_t hash[8], const uint32_t salt[4], uint64_t counter);

#if defined(BLAKE256_USE_ASM) || defined (BLAKE256_ENABLE_ASM)
extern void blake256_process_block_asm(const uint8_t block[64], uint32_t hash[8], uint64_t counter);
#endif

/* BLAKE-224 */
#define BLAKE224_BLOCK_SIZE		(64)
#define BLAKE224_DIGEST_SIZE	(28)
#define BLAKE224_HASH_SIZE		(32)
#define BLAKE224_SALT_SIZE		(16)

void blake224_init_hash(uint32_t hash[8]);

#endif
