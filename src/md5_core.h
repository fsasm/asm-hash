/*
 * md5_core.h
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-03
 */

#ifndef MD5_CORE_H
#define MD5_CORE_H

#include <stdint.h>

#define MD5_BLOCK_SIZE	(64)
#define MD5_HASH_SIZE	(16)
#define MD5_DIGEST_SIZE	(16)

void md5_init_hash(uint32_t hash[4]);
void md5_hash_to_digest(uint32_t hash[4], uint8_t digest[MD5_DIGEST_SIZE]);
void md5_process_blocks(const uint8_t block[], uint32_t hash[4], unsigned int n);

#if defined(MD5_USE_ASM) || defined(MD5_ENABLE_ASM)
#if __x86_64__
__attribute__((sysv_abi))
#endif
extern void md5_process_blocks_asm(const uint8_t block[], uint32_t hash[4], unsigned int n);
#endif

#endif

