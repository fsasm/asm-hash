/*
 * sha1.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-25
 */

#include "sha1.h"
#include "int_util.h"

void process_block(block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	(void)data_bits;
#ifdef SHA1_USE_ASM
	sha1_process_blocks_asm(block, (uint32_t*)(b->func_data), n);
#else
	sha1_process_blocks(block, (uint32_t*)(b->func_data), n);
#endif
}

void sha1_init(sha1_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	sha1_init_hash(ctxt->hash);	
	block_init(&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_block, ctxt->hash);
}

void sha1_add(sha1_context* ctxt, const uint8_t data[], size_t length) {
	block_add(&ctxt->b, length, data);
}

void sha1_finalize(sha1_context* ctxt) {
	block_util_finalize(&ctxt->b, BLOCK_LENGTH_64 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING);
}

void sha1_get_digest(sha1_context* ctxt, uint8_t digest[SHA1_DIGEST_SIZE]) {
	for (size_t i = 0; i < 5; i++) {
		u32_to_u8_be(ctxt->hash[i], &digest[i * 4]);
	}
}

