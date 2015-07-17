/*
 * whirlpool.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-06-26
 */

#include "whirlpool.h"
#include "int_util.h"
#include <string.h>

void process_blocks (block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	(void)data_bits;
#ifdef WHIRLPOOL_USE_ASM
	whirlpool_process_blocks_asm (block, (uint64_t(*))(b->func_data), n);
#else
	whirlpool_process_blocks (block, (uint64_t(*))(b->func_data), n);
#endif
}

void whirlpool_init (whirlpool_context* ctxt) {
	if(ctxt == NULL)
		return;
	
	block_init (&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_blocks, ctxt->hash);
	whirlpool_init_hash(ctxt->hash);
}

void whirlpool_finalize (whirlpool_context* ctxt) {
	block_util_finalize (&ctxt->b, BLOCK_LENGTH_256 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING);
}

void whirlpool_add (whirlpool_context* ctxt, const uint8_t data[], size_t length) {
	block_add (&ctxt->b, length, data);
}

void whirlpool_get_digest (whirlpool_context* ctxt, uint8_t digest[WHIRLPOOL_DIGEST_SIZE]) {
#ifdef WHIRLPOOL_NAIVE
	memcpy (digest, ctxt->hash, WHIRLPOOL_DIGEST_SIZE);
#else
	uint8_t (*h)[8] = (uint8_t (*)[8])ctxt->hash;
	for (uint_fast8_t x = 0; x < 8; x++) {
		for (uint_fast8_t y = 0; y < 8; y++) {
			digest[x * 8 + y] = h[x][7 - y];
		}
	}
#endif
}

