/*
 * sha256_core.h
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-12
 */

#ifndef SHA256_CORE_H
#define SHA256_CORE_H

#include <stdint.h>

/* SHA-256 */
#define SHA256_BLOCK_SIZE	(64)
#define SHA256_DIGEST_SIZE	(32)
#define SHA256_HASH_SIZE	(32)

void sha256_init_hash(uint32_t hash[8]);
void sha256_process_blocks(const uint8_t block[], uint32_t hash[8], unsigned int n);

#if defined(SHA256_USE_ASM) || defined(SHA256_ENABLE_ASM)
#if __x86_64__
__attribute__((sysv_abi))
#endif
extern void sha256_process_blocks_asm(const uint8_t block[], uint32_t hash[8], unsigned int n);
#endif

/* SHA-224 */
#define SHA224_BLOCK_SIZE	(64)
#define SHA224_HASH_SIZE	(32)
#define SHA224_DIGEST_SIZE	(28)

void sha224_init_hash(uint32_t hash[8]);

#endif

