/*
 * sha512_core.h
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-12
 */
#ifndef SHA512_CORE_H
#define SHA512_CORE_H

#include <stdint.h>

/* SHA-512, SHA-512/224 and SHA-512/256 */
#define SHA512_BLOCK_SIZE		(128)
#define SHA512_DIGEST_SIZE		(64)
#define SHA512_224_DIGEST_SIZE	(28)
#define SHA512_256_DIGEST_SIZE	(32)
#define SHA512_HASH_SIZE		(64)

void sha512_init_hash(uint64_t hash[8]);
void sha512_224_init_hash(uint64_t hash[8]);
void sha512_256_init_hash(uint64_t hash[8]);

void sha512_hash_to_digest(uint64_t hash[8], uint8_t digest[SHA512_DIGEST_SIZE]);
void sha512_224_hash_to_digest(uint64_t hash[8], uint8_t digest[SHA512_224_DIGEST_SIZE]);
void sha512_256_hash_to_digest(uint64_t hash[8], uint8_t digest[SHA512_256_DIGEST_SIZE]);

void sha512_process_blocks(const uint8_t block[], uint64_t hash[8], unsigned int n);

#if defined(SHA512_USE_ASM) || defined(SHA512_ENABLE_ASM)
#if __x86_64__
__attribute__((sysv_abi))
#endif
extern void sha512_process_blocks_asm(const uint8_t block[], uint64_t hash[8], unsigned int n);
#endif

/* SHA-384 */
#define SHA384_BLOCK_SIZE	(128)
#define SHA384_DIGEST_SIZE	(48)
#define SHA384_HASH_SIZE	(64)

void sha384_init_hash(uint64_t hash[8]);
void sha384_hash_to_digest(uint64_t hash[8], uint8_t digest[SHA384_DIGEST_SIZE]);

#endif

