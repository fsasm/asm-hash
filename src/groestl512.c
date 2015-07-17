/*
 * groestl512.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-10-02
 */
 
#include "groestl512.h"
#include "int_util.h"
#include <string.h>

void process_blocks(block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	(void)data_bits;
	for (unsigned int i = 0; i < n; i++) {
		groestl512_process_block(&block[i * 128], (uint8_t(*)[16])(b->func_data), n);
	}
}

void end_hash(block* b) {
	groestl512_finalize_hash((uint8_t(*)[16])(b->func_data));
}

/* GROESTL-512 */
void groestl512_init(groestl512_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init_with_end(
		&ctxt->b, 
		BLOCK_SIZE_1024, 
		ctxt->buffer, 
		process_blocks, 
		end_hash, 
		ctxt->hash
	);
	groestl512_init_hash(ctxt->hash);
}

void groestl512_add(groestl512_context* ctxt, const uint8_t data[], size_t length) {
	block_add(&ctxt->b, length, data);
}

void groestl512_finalize(groestl512_context* ctxt) {
	block_util_finalize(
		&ctxt->b, 
		BLOCK_LENGTH_64 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING | BLOCK_COUNT
	);
}

void groestl512_get_digest(groestl512_context* ctxt, uint8_t digest[GROESTL512_DIGEST_SIZE]) {
	for (uint_fast8_t row = 0; row < 8; row++) {
		for (uint_fast8_t column = 0; column < 8; column++) {
			digest[column * 8 + row] = ctxt->hash[row][column + 8];
		}
	}
}

/* GROESTL-224 */
void groestl384_init(groestl384_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init_with_end(
		&ctxt->b, 
		BLOCK_SIZE_1024, 
		ctxt->buffer, 
		process_blocks, 
		end_hash, 
		ctxt->hash
	);
	groestl384_init_hash(ctxt->hash);
}

void groestl384_add(groestl384_context* ctxt, const uint8_t data[], size_t length) {
	groestl512_add(ctxt, data, length);
}

void groestl384_finalize(groestl384_context* ctxt) {
	groestl512_finalize(ctxt);
}

void groestl384_get_digest(groestl384_context* ctxt, uint8_t digest[GROESTL384_DIGEST_SIZE]) {	
	for (uint_fast8_t column = 2; column < 8; column++) {
		for (uint_fast8_t row = 0; row < 8; row++) {
			digest[column * 8 + row - 16] = ctxt->hash[row][column + 8];
		}
	}
}

