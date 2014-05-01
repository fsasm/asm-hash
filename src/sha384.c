/*
 * sha384.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2013-12-23
 */
 
#include "sha384.h"
#include "int_util.h"
#include <stdlib.h>

void sha384_init (sha384_context* ctxt) {
	sha512_init (ctxt);
	
	ctxt->hash[0] = 0xCBBB9D5DC1059ED8;
	ctxt->hash[1] = 0x629A292A367CD507;
	ctxt->hash[2] = 0x9159015A3070DD17;
	ctxt->hash[3] = 0x152FECD8F70E5939;
	ctxt->hash[4] = 0x67332667FFC00B31;
	ctxt->hash[5] = 0x8EB44A8768581511;
	ctxt->hash[6] = 0xDB0C2E0D64F98FA7;
	ctxt->hash[7] = 0x47B5481DBEFA4FA4;
}

void sha384_add (sha384_context* ctxt, uint8_t data[], size_t length) {
	sha512_add (ctxt, data, length);
}

void sha384_finalize (sha384_context* ctxt) {
	sha512_finalize (ctxt);
}

void sha384_get_digest (sha384_context* ctxt, uint8_t digest[SHA384_DIGEST_SIZE]) {
	if (ctxt == NULL)
		return;
		
	for (int i = 0; i < 6; i++)
		u64_to_u8_be (ctxt->hash[i], &digest[i * 8]);
}

