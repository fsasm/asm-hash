/*
 * sha1_core.h
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-12
 */

#ifndef SHA1_CORE_H
#define SHA1_CORE_H

#include <stdint.h>

#define SHA1_BLOCK_SIZE		(64)
#define SHA1_DIGEST_SIZE	(20)
#define SHA1_HASH_SIZE		(20)

void sha1_init_hash(uint32_t hash[5]);
void sha1_process_blocks(const uint8_t block[], uint32_t hash[5], unsigned int n);

#if defined(SHA1_USE_ASM) || defined(SHA1_ENABLE_ASM)
#if __x86_x64__
__attribute__((sysv_abi))
#endif
extern void sha1_process_blocks_asm(const uint8_t block[], uint32_t hash[5], unsigned int n);
#endif

#endif

