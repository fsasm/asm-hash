/*
 * md5.c
 * Author: Fabjan Sukalia(fsukalia@gmail.com)
 * Date: 2014-04-04
 */

#include "md5.h"

void process_block(block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	(void)data_bits;
#ifdef MD5_USE_ASM
	md5_process_blocks_asm(block, (uint32_t*)(b->func_data), n);
#else
	md5_process_blocks(block, (uint32_t*)(b->func_data), n);
#endif
}

void md5_init(md5_context* ctxt) {
	if (ctxt == NULL)
		return;

	md5_init_hash(ctxt->hash);
	block_init(&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_block, ctxt->hash);
}

void md5_add(md5_context* ctxt, const uint8_t data[], size_t length) {
	block_add(&ctxt->b, length, data);
}

void md5_finalize(md5_context* ctxt) {
	block_util_finalize(&ctxt->b, BLOCK_LENGTH_64 | BLOCK_LITTLE_ENDIAN | BLOCK_SIMPLE_PADDING);
}

void md5_get_digest(md5_context* ctxt, uint8_t digest[MD5_DIGEST_SIZE]) {
	md5_hash_to_digest(ctxt->hash, digest);
}

