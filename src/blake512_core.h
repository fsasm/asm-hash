/*
 * blake512_core.h
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-14
 */

#ifndef BLAKE512_CORE_H
#define BLAKE512_CORE_H

#include <stdint.h>

/* BLAKE-512 */
#define BLAKE512_BLOCK_SIZE		(128)
#define BLAKE512_DIGEST_SIZE	(64)
#define BLAKE512_HASH_SIZE		(64)
#define BLAKE512_SALT_SIZE		(32)

void blake512_init_hash(uint64_t hash[8]);
void blake512_process_block(const uint8_t block[128], uint64_t hash[8], uint64_t counter);
void blake512_process_block_with_salt(const uint8_t block[128], uint64_t hash[8], const uint64_t salt[4], uint64_t counter);

#if defined(BLAKE512_USE_ASM) || defined (BLAKE512_ENABLE_ASM)
extern void blake512_process_block_asm(const uint8_t block[128], uint64_t hash[8], uint64_t counter);
#endif

/* BLAKE-384 */
#define BLAKE384_BLOCK_SIZE		(128)
#define BLAKE384_DIGEST_SIZE	(48)
#define BLAKE384_HASH_SIZE		(64)
#define BLAKE384_SALT_SIZE		(32)

void blake384_init_hash(uint64_t hash[8]);

#endif

