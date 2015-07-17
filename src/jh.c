/*
 * jh.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-10-12
 */

#include "jh.h"
#include "int_util.h"
#include <string.h>

void process_blocks(block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	for (unsigned int i = 0; i < n; i++) {
		jh_process_block(block, b->func_data);
		
		block += 64;
	}
}

/* JH-256 */
void jh256_init(jh256_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init(&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_blocks, ctxt->hash);
	jh256_init_hash(ctxt->hash);
}

void jh256_add(jh256_context* ctxt, const uint8_t data[], size_t length) {
	block_add(&ctxt->b, length, data);
}

void jh256_finalize(jh256_context* ctxt) {
	block_util_finalize(
		&ctxt->b,
		BLOCK_LENGTH_128 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING | BLOCK_EXTRA_PADDING 
	);
}

void jh256_get_digest(jh256_context* ctxt, uint8_t digest[JH256_DIGEST_SIZE]) {
	u64_to_u8_le(ctxt->hash[6][0], &digest[0]);
	u64_to_u8_le(ctxt->hash[6][1], &digest[8]);
	u64_to_u8_le(ctxt->hash[7][0], &digest[16]);
	u64_to_u8_le(ctxt->hash[7][1], &digest[24]);
}

/* JH-224 */
void jh224_init(jh224_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init(&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_blocks, ctxt->hash);
	jh224_init_hash(ctxt->hash);
}

void jh224_add(jh224_context* ctxt, const uint8_t data[], size_t length) {
	jh256_add(ctxt, data, length);
}

void jh224_finalize(jh256_context* ctxt) {
	jh256_finalize(ctxt);
}

void jh224_get_digest(jh224_context* ctxt, uint8_t digest[JH224_DIGEST_SIZE]) {
	u32_to_u8_le((uint32_t)(ctxt->hash[6][0] >> 32), &digest[0]);
	u64_to_u8_le(ctxt->hash[6][1], &digest[4]);
	u64_to_u8_le(ctxt->hash[7][0], &digest[12]);
	u64_to_u8_le(ctxt->hash[7][1], &digest[20]);
}

/* JH-384 */
void jh384_init(jh384_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init(&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_blocks, ctxt->hash);
	jh384_init_hash(ctxt->hash);
}

void jh384_add(jh384_context* ctxt, const uint8_t data[], size_t length) {
	jh256_add(ctxt, data, length);
}

void jh384_finalize(jh384_context* ctxt) {
	jh256_finalize(ctxt);
}

void jh384_get_digest(jh384_context* ctxt, uint8_t digest[JH384_DIGEST_SIZE]) {
	u64_to_u8_le(ctxt->hash[5][0], &digest[0]);
	u64_to_u8_le(ctxt->hash[5][1], &digest[8]);
	u64_to_u8_le(ctxt->hash[6][0], &digest[16]);
	u64_to_u8_le(ctxt->hash[6][1], &digest[24]);
	u64_to_u8_le(ctxt->hash[7][0], &digest[32]);
	u64_to_u8_le(ctxt->hash[7][1], &digest[40]);
}

/* JH-512 */
void jh512_init(jh512_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init(&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_blocks, ctxt->hash);
	jh512_init_hash(ctxt->hash);
}

void jh512_add(jh512_context* ctxt, const uint8_t data[], size_t length) {
	jh256_add(ctxt, data, length);
}

void jh512_finalize(jh512_context* ctxt) {
	jh256_finalize(ctxt);
}

void jh512_get_digest(jh512_context* ctxt, uint8_t digest[JH512_DIGEST_SIZE]) {
	u64_to_u8_le(ctxt->hash[4][0], &digest[0]);
	u64_to_u8_le(ctxt->hash[4][1], &digest[8]);
	u64_to_u8_le(ctxt->hash[5][0], &digest[16]);
	u64_to_u8_le(ctxt->hash[5][1], &digest[24]);
	u64_to_u8_le(ctxt->hash[6][0], &digest[32]);
	u64_to_u8_le(ctxt->hash[6][1], &digest[40]);
	u64_to_u8_le(ctxt->hash[7][0], &digest[48]);
	u64_to_u8_le(ctxt->hash[7][1], &digest[56]);
}

