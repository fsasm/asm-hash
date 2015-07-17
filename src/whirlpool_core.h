/*
 * whirlpool_core.h
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-17
 */

#ifndef WHIRLPOOL_CORE_H
#define WHIRLPOOL_CORE_H

#include <stdint.h>

#define WHIRLPOOL_BLOCK_SIZE	(64)
#define WHIRLPOOL_DIGEST_SIZE	(64)
#define WHIRLPOOL_HASH_SIZE		(64)

void whirlpool_init_hash(uint64_t hash[8]);
void whirlpool_process_blocks(const uint8_t block[], uint64_t hash[8], unsigned int n);

#if defined(WHIRLPOOL_USE_ASM) || defined (WHIRLPOOL_ENABLE_ASM)
#if __x86_64__
__attribute__((sysv_abi))
#endif
extern void whirlpool_process_blocks_asm(const uint8_t block[], uint64_t hash[8], unsigned int n);
#endif

#endif

