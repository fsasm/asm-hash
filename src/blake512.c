/*
 * blake512.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-08-26
 */
 
#include "blake512.h"
#include "int_util.h"
#include <string.h>

void process_block(block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	void* data = b->func_data;
	uint64_t full_size = b->full_size - (n - 1) * 128;
	
	for (unsigned int i = 0; i < n; i++) {
#ifdef BLAKE512_USE_ASM
		blake512_process_block_asm(block, data, data_bits ? full_size : 0);
#else
		blake512_process_block(block, data, data_bits ? full_size : 0);
#endif
		block += 128;
		full_size += 128;
	}
}

void process_block_with_salt(block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	blake512_context* ctxt = (blake512_context*)b->func_data;
	uint64_t full_size = b->full_size - (n - 1) * 128;
	
	uint64_t* salt = (uint64_t*)ctxt->salt;
	uint64_t* hash = ctxt->hash;
	
	for (unsigned int i = 0; i < n; i++) {
		blake512_process_block_with_salt(block, hash, salt, data_bits ? full_size : 0);
		block += 128;
		full_size += 128;
	}
}

void blake512_init(blake512_context* ctxt) {
	if (ctxt == NULL)
		return;
		
	blake512_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block, ctxt->hash);
	memset(ctxt->salt, 0, sizeof(ctxt->salt));
}

void blake512_init_with_salt(blake512_context* ctxt, uint8_t salt[32]) {
	if (ctxt == NULL)
		return;
	
	blake512_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block_with_salt, ctxt);
	memcpy(ctxt->salt, salt, sizeof(ctxt->salt));
}

void blake512_add(blake512_context* ctxt, const uint8_t data[], size_t length) {
	block_add(&ctxt->b, length, data);
}

void blake512_get_digest(blake512_context* ctxt, uint8_t digest[BLAKE512_DIGEST_SIZE]) {
	for (int i = 0; i < 8; i++) {
		u64_to_u8_be(ctxt->hash[i], &digest[i * 8]);
	}
}

void blake512_finalize(blake512_context* ctxt) {
	block_util_finalize(&ctxt->b, BLOCK_LENGTH_128 | BLOCK_BIG_ENDIAN | BLOCK_EXTENDED_PADDING);
}

/* BLAKE-384 */
void blake384_init(blake384_context* ctxt) {
	if (ctxt == NULL)
		return;
		
	blake384_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block, ctxt->hash);
	memset(ctxt->salt, 0, sizeof(ctxt->salt));
}

void blake384_init_with_salt(blake384_context* ctxt, uint8_t salt[32]) {
	if (ctxt == NULL)
		return;
	
	blake384_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block_with_salt, ctxt);
	memcpy(ctxt->salt, salt, sizeof(ctxt->salt));
}

void blake384_add(blake384_context* ctxt, const uint8_t data[], size_t length) {
	block_add(&ctxt->b, length, data);
}

void blake384_get_digest(blake384_context* ctxt, uint8_t digest[BLAKE384_DIGEST_SIZE]) {
	for (int i = 0; i < 6; i++) {
		u64_to_u8_be(ctxt->hash[i], &digest[i * 8]);
	}
}

void blake384_finalize(blake384_context* ctxt) {
	block_util_finalize(&ctxt->b, BLOCK_LENGTH_128 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING);
}

