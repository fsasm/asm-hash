/*
 * blake256.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-07-09 
 */

#include "blake256.h"
#include <string.h>

void process_block(block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	void* data = b->func_data;
	uint64_t full_size = b->full_size - (n - 1) * 64;
	
	for (unsigned int i = 0; i < n; i++) {
#ifdef BLAKE256_USE_ASM
		blake256_process_block_asm(block, data, data_bits ? full_size : 0);
#else
		blake256_process_block(block, data, data_bits ? full_size : 0);
#endif
		block += 64;
		full_size += 64;
	}
}

void process_block_with_salt(block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	blake256_context* ctxt = (blake256_context*)b->func_data;
	uint64_t full_size = b->full_size - (n - 1) * 64;
	
	uint32_t* salt = (uint32_t*)ctxt->salt;
	uint32_t* hash = ctxt->hash;
	
	for (unsigned int i = 0; i < n; i++) {
		blake256_process_block_with_salt(block, hash, salt, data_bits ? full_size : 0);
		block += 64;
		full_size += 64;
	}
}

/* BLAKE-256 */
void blake256_init(blake256_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	blake256_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_block, ctxt->hash);
	memset(ctxt->salt, 0, sizeof(ctxt->salt));
}

void blake256_init_with_salt(blake256_context* ctxt, uint8_t salt[16]) {
	if (ctxt == NULL)
		return;
	
	blake256_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_block_with_salt, ctxt);
	memcpy(ctxt->salt, salt, sizeof(ctxt->salt));
}

void blake256_add(blake256_context* ctxt, const uint8_t data[], size_t length) {
	block_add(&ctxt->b, length, data);
}

void blake256_get_digest(blake256_context* ctxt, uint8_t digest[BLAKE256_DIGEST_SIZE]) {
	blake256_hash_to_digest(ctxt->hash, digest);
}

void blake256_finalize(blake256_context* ctxt) {
	block_util_finalize(&ctxt->b, BLOCK_LENGTH_64 | BLOCK_BIG_ENDIAN | BLOCK_EXTENDED_PADDING);
}

/* BLAKE-224 */
void blake224_init(blake224_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	blake224_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_block, ctxt->hash);
	memset(ctxt->salt, 0, sizeof(ctxt->salt));
}

void blake224_init_with_salt(blake224_context* ctxt, uint8_t salt[16]) {
	if (ctxt == NULL)
		return;
	
	blake224_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_block_with_salt, ctxt);
	memcpy(ctxt->salt, salt, sizeof(ctxt->salt));
}

void blake224_add(blake224_context* ctxt, const uint8_t data[], size_t length) {
	blake256_add(ctxt, data, length);
}

void blake224_get_digest(blake224_context* ctxt, uint8_t digest[BLAKE224_DIGEST_SIZE]) {
	blake224_hash_to_digest(ctxt->hash, digest);
}

void blake224_finalize(blake224_context* ctxt) {
	block_util_finalize(&ctxt->b, BLOCK_LENGTH_64 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING);
}

