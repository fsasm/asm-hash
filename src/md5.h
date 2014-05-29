/*
 * md5.h
 * Author Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-04
 */

#ifndef MD5_H
#define MD5_H

#include <stdint.h>
#include "block.h"

#define MD5_BLOCK_SIZE 64
#define MD5_HASH_SIZE 16
#define MD5_DIGEST_SIZE 16

typedef struct {
	uint8_t buffer[64];
	uint32_t hash[4];
	block b;
} md5_context;

void md5_init (md5_context* ctxt);
void md5_init_hash (uint32_t hash[4]);
void md5_add (md5_context* ctxt, uint8_t data[], size_t length);
void md5_finalize (md5_context* ctxt);
void md5_get_digest (md5_context* ctxt, uint8_t digest[MD5_DIGEST_SIZE]);

void md5_process_blocks (uint8_t block[], uint32_t hash[4], unsigned int n);

#if defined (MD5_USE_ASM) || defined (MD5_ENABLE_ASM)
extern void md5_process_blocks_asm (uint8_t* block, uint32_t* hash, unsigned int n);
#endif

#endif
