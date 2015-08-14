/*
 * groestl256.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-09-26
 */
 
#include "groestl256.h"
#include <string.h>

void process_blocks(block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	(void)data_bits;
	for (unsigned int i = 0; i < n; i++) {
		groestl256_process_block(&block[i * 64], (uint8_t(*)[8])(b->func_data), n);
	}
}

void end_hash(block* b) {
	groestl256_finalize_hash((uint8_t(*)[8])(b->func_data));
}

/* GROESTL-256 */
void groestl256_init(groestl256_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init_with_end(
		&ctxt->b, 
		BLOCK_SIZE_512, 
		ctxt->buffer, 
		process_blocks, 
		end_hash, 
		ctxt->hash
	);
	groestl256_init_hash(ctxt->hash);
}

void groestl256_add(groestl256_context* ctxt, const uint8_t data[], size_t length) {
	block_add(&ctxt->b, length, data);
}

void groestl256_finalize(groestl256_context* ctxt) {
	block_util_finalize(
		&ctxt->b, 
		BLOCK_LENGTH_64 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING | BLOCK_COUNT
	);
}

void groestl256_get_digest(groestl256_context* ctxt, uint8_t digest[GROESTL256_DIGEST_SIZE]) {
	groestl256_hash_to_digest(ctxt->hash, digest);
}

/* GROESTL-224 */
void groestl224_init(groestl224_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init_with_end(
		&ctxt->b, 
		BLOCK_SIZE_512, 
		ctxt->buffer, 
		process_blocks, 
		end_hash, 
		ctxt->hash
	);
	groestl224_init_hash(ctxt->hash);
}

void groestl224_add(groestl224_context* ctxt, const uint8_t data[], size_t length) {
	groestl256_add(ctxt, data, length);
}

void groestl224_finalize(groestl224_context* ctxt) {
	groestl256_finalize(ctxt);
}

void groestl224_get_digest(groestl224_context* ctxt, uint8_t digest[GROESTL224_DIGEST_SIZE]) {
	groestl224_hash_to_digest(ctxt->hash, digest);
}

