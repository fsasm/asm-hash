/*
 * sha512.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-05-01
 */

#include "sha512.h"
#include "int_util.h"

void process_block(block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	(void)data_bits;
#ifdef SHA512_USE_ASM
	sha512_process_blocks_asm(block, (uint64_t*)(b->func_data), n);
#else
	sha512_process_blocks(block, (uint64_t*)(b->func_data), n);
#endif
}

void sha512_init(sha512_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	sha512_init_hash(ctxt->hash);	
	block_init(&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block, ctxt->hash);
}

void sha512_224_init(sha512_context* ctxt) {
	if (ctxt == NULL)
		return;
		
	sha512_224_init_hash(ctxt->hash);	
	block_init(&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block, ctxt->hash);
}

void sha512_256_init(sha512_context* ctxt) {
	if (ctxt == NULL)
		return;
		
	sha512_256_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block, ctxt->hash);
}

void sha512_add(sha512_context* ctxt, const uint8_t data[], size_t length) {
	block_add(&ctxt->b, length, data);
}

void sha512_finalize(sha512_context* ctxt) {
	block_util_finalize(&ctxt->b, BLOCK_LENGTH_128 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING);
}

void sha512_get_digest(sha512_context* ctxt, uint8_t digest[SHA512_DIGEST_SIZE]) {
	sha512_hash_to_digest(ctxt->hash, digest);
}

void sha512_224_get_digest(sha512_context* ctxt, uint8_t digest[SHA512_224_DIGEST_SIZE]) {
	sha512_224_hash_to_digest(ctxt->hash, digest);
}

void sha512_256_get_digest(sha512_context* ctxt, uint8_t digest[SHA512_256_DIGEST_SIZE]) {
	sha512_256_hash_to_digest(ctxt->hash, digest);
}

/* SHA-384 */
void sha384_init(sha384_context* ctxt) {
	if (ctxt == NULL)
		return;

	sha384_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_1024, ctxt->buffer, process_block, ctxt->hash);
}

void sha384_add(sha384_context* ctxt, const uint8_t data[], size_t length) {
	sha512_add(ctxt, data, length);
}

void sha384_finalize(sha384_context* ctxt) {
	sha512_finalize(ctxt);
}

void sha384_get_digest(sha384_context* ctxt, uint8_t digest[SHA384_DIGEST_SIZE]) {
	sha384_hash_to_digest(ctxt->hash, digest);
}

