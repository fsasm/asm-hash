/*
 * sha1.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-25
 */

#include "sha1.h"
#include "int_util.h"

void process_block (uint8_t block[], void* data, unsigned int n) {
#ifdef SHA1_USE_ASM
	sha1_process_block_asm (block, (uint32_t*)data);
#else
	sha1_process_blocks (block, (uint32_t*)data, n);
#endif
}

void sha1_init (sha1_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	ctxt->hash[0] = 0x67452301;
	ctxt->hash[1] = 0xEFCDAB89;
	ctxt->hash[2] = 0x98BADCFE;
	ctxt->hash[3] = 0x10325476;
	ctxt->hash[4] = 0xC3D2E1F0;
	
	block_init (&ctxt->b, 64, ctxt->buffer, process_block, ctxt->hash);
}

void sha1_add (sha1_context* ctxt, uint8_t data[], uint64_t length) {
	block_add (&ctxt->b, length, data);
}

void sha1_finalize (sha1_context* ctxt) {
	block_util_finalize (&ctxt->b, false, false);
}

void sha1_get_digest (sha1_context* ctxt, uint8_t digest[SHA1_DIGEST_SIZE]) {
	for (int i = 0; i < 5; i++) {
		u32_to_u8_be (ctxt->hash[i], &digest[i * 4]);
	}
}

void sha1_process_blocks (uint8_t block[], uint32_t hash[5], unsigned int n) {
	for (unsigned int j = 0; j < n; j++) {
		uint8_t* block1 = &block[j * 64];
		
		uint32_t a = hash[0];
		uint32_t b = hash[1];
		uint32_t c = hash[2];
		uint32_t d = hash[3];
		uint32_t e = hash[4];
		
		uint32_t temp;
		uint32_t k;
		uint32_t f;
		uint32_t W[80];
		
		for (uint_fast8_t i = 0; i < 16; i++) {
			W[i] = u8_to_u32_be (&block1[i * 4]);
		}
		
		for (uint_fast8_t i = 16; i < 80; i++) {
			W[i] = rotate_left_32 (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16], 1);
		}
		
		for (uint_fast8_t t = 0; t < 80; t++) {
			if (t < 20) {
				f = (b & c) | ((~b) & d);
				k = 0x5A827999;
			} else if (t < 40) {
				f = b ^ c ^ d; 
				k = 0x6ED9EBA1;
			} else if (t < 60) {
				f = (b & c) | (b & d) | (c & d);
				k = 0x8F1BBCDC;
			} else {
				f = b ^ c ^ d;
				k = 0xCA62C1D6;
			}
			
			temp = W[t] + f + k + rotate_left_32 (a, 5) + e;
			
			e = d;
			d = c;
			c = rotate_left_32 (b, 30);
			b = a;
			a = temp;
		}
		
		hash[0] += a;
		hash[1] += b;
		hash[2] += c;
		hash[3] += d;
		hash[4] += e;
	}
}
