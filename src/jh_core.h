/*
 * jh_core.h
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-17
 */
 
#ifndef JH256_CORE_H
#define JH256_CORE_H

#include <stdint.h>

/* JH-256 */
#define JH256_BLOCK_SIZE	(64)
#define JH256_DIGEST_SIZE	(32)
#define JH256_HASH_SIZE		(128)

void jh256_init_hash(uint64_t hash[8][2]);
void jh_process_block(const uint8_t block[64], uint64_t hash[8][2]);

/* JH-224 */
#define JH224_BLOCK_SIZE	(64)
#define JH224_DIGEST_SIZE	(28)
#define JH224_HASH_SIZE		(128)

void jh224_init_hash(uint64_t hash[8][2]);

/* JH-384 */
#define JH384_BLOCK_SIZE	(64)
#define JH384_DIGEST_SIZE	(48)
#define JH384_HASH_SIZE		(128)

void jh384_init_hash(uint64_t hash[8][2]);

/* JH-512 */
#define JH512_BLOCK_SIZE	(64)
#define JH512_DIGEST_SIZE	(64)
#define JH512_HASH_SIZE		(128)

void jh512_init_hash(uint64_t hash[8][2]);

#endif

