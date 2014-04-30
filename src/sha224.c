/*
 * sha224.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-28
 */

#include "sha224.h"
#include "int_util.h"
#include <stdlib.h>

void sha224_init (sha256_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	sha256_init (ctxt);

	ctxt->hash[0] = 0xC1059ED8;
	ctxt->hash[1] = 0x367CD507;
	ctxt->hash[2] = 0x3070DD17;
	ctxt->hash[3] = 0xF70E5939;
	ctxt->hash[4] = 0xFFC00B31;
	ctxt->hash[5] = 0x68581511;
	ctxt->hash[6] = 0x64F98FA7;
	ctxt->hash[7] = 0xBEFA4FA4;	
}

void sha224_add (sha224_context* ctxt, uint8_t data[], uint64_t length) {
	sha256_add (ctxt, data, length);
}

void sha224_finalize (sha224_context* ctxt) {
	sha256_finalize (ctxt);
}

void sha224_get_digest (sha256_context* ctxt, uint8_t digest[SHA224_DIGEST_SIZE]) {
	if (ctxt == NULL)
		return;
		
	for (uint_fast8_t i = 0; i < 7; i++)
		u32_to_u8_be (ctxt->hash[i], &digest[i * 4]);
}

