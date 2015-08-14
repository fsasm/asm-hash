/*
 * sha512_core.c
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-12
 */

#include "sha512_core.h"
#include "int_util.h"

/* table for SHA-384, SHA-512, SHA-512/224, SHA-512/256 */
static const uint64_t sha512_table[80] = {
	0x428A2f98D728AE22, 0x7137449123EF65CD, 0xB5C0FBCFEC4D3B2F, 0xE9B5DBA58189DBBC,
	0x3956C25BF348B538, 0x59F111F1B605D019, 0x923F82A4AF194F9B, 0xAB1C5ED5DA6D8118, /*  8 */
	0xD807AA98A3030242, 0x12835B0145706FBE, 0x243185BE4EE4B28C, 0x550C7DC3D5FFB4E2,
	0x72BE5D74F27B896F, 0x80DEB1FE3B1696B1, 0x9BDC06A725C71235, 0xC19BF174CF692694, /* 16 */
	0xE49B69C19EF14AD2, 0xEFBE4786384F25E3, 0x0FC19DC68B8CD5B5, 0x240CA1CC77AC9C65,
	0x2DE92C6F592B0275, 0x4A7484AA6EA6E483, 0x5CB0A9DCBD41FBD4, 0x76F988DA831153B5, /* 24 */
	0x983E5152EE66DFAB, 0xA831C66D2DB43210, 0xB00327C898FB213F, 0xBF597FC7BEEF0EE4,
	0xC6E00BF33DA88FC2, 0xD5A79147930AA725, 0x06CA6351E003826F, 0x142929670A0E6E70, /* 32 */
	0x27B70A8546D22FFC, 0x2E1B21385C26C926, 0x4D2C6DFC5AC42AED, 0x53380D139D95B3DF,
	0x650A73548BAF63DE, 0x766A0ABB3C77B2A8, 0x81C2C92E47EDAEE6, 0x92722C851482353B, /* 40 */
	0xA2BFE8A14CF10364, 0xA81A664BBC423001, 0xC24B8B70D0F89791, 0xC76C51A30654BE30,
	0xD192E819D6EF5218, 0xD69906245565A910, 0xF40E35855771202A, 0x106AA07032BBD1B8, /* 48 */
	0x19A4C116B8D2D0C8, 0x1E376C085141AB53, 0x2748774CDF8EEB99, 0x34B0BCB5E19B48A8,
	0x391C0CB3C5C95A63, 0x4ED8AA4AE3418ACB, 0x5B9CCA4F7763E373, 0x682E6FF3D6B2B8A3, /* 56 */
	0x748F82EE5DEFB2FC, 0x78A5636F43172F60, 0x84C87814A1F0AB72, 0x8CC702081A6439EC,
	0x90BEFFFA23631E28, 0xA4506CEBDE82BDE9, 0xBEF9A3F7B2C67915, 0xC67178F2E372532B, /* 64 */
	0xCA273ECEEA26619C, 0xD186B8C721C0C207, 0xEADA7DD6CDE0EB1E, 0xF57D4F7FEE6ED178,
	0x06F067AA72176FBA, 0x0A637DC5A2C898A6, 0x113F9804BEF90DAE, 0x1B710B35131C471B, /* 72 */
	0x28DB77F523047D84, 0x32CAAB7B40C72493, 0x3C9EBE0A15C9BEBC, 0x431D67C49C100D4C,
	0x4CC5D4BECB3E42B6, 0x597F299CFC657E2A, 0x5FCB6FAB3AD6FAEC, 0x6C44198C4A475817  /* 80 */
};

void sha512_init_hash(uint64_t hash[8]) {
	hash[0] = UINT64_C(0x6A09E667F3BCC908);
	hash[1] = UINT64_C(0xBB67AE8584CAA73B);
	hash[2] = UINT64_C(0x3C6EF372FE94F82B);
	hash[3] = UINT64_C(0xA54FF53A5F1D36F1);
	hash[4] = UINT64_C(0x510E527FADE682D1);
	hash[5] = UINT64_C(0x9B05688C2B3E6C1F);
	hash[6] = UINT64_C(0x1F83D9ABFB41BD6B);
	hash[7] = UINT64_C(0x5BE0CD19137E2179);
}

void sha512_224_init_hash(uint64_t hash[8]) {
	hash[0] = UINT64_C(0x8C3D37C819544DA2);
	hash[1] = UINT64_C(0x73E1996689DCD4D6);
	hash[2] = UINT64_C(0x1DFAB7AE32FF9C82);
	hash[3] = UINT64_C(0x679DD514582F9FCF);
	hash[4] = UINT64_C(0x0F6D2B697BD44DA8);
	hash[5] = UINT64_C(0x77E36F7304C48942);
	hash[6] = UINT64_C(0x3F9D85A86A1D36C8);
	hash[7] = UINT64_C(0x1112E6AD91D692A1);
}

void sha512_256_init_hash(uint64_t hash[8]) {
	hash[0] = UINT64_C(0x22312194FC2BF72C);
	hash[1] = UINT64_C(0x9F555FA3C84C64C2);
	hash[2] = UINT64_C(0x2393B86B6F53B151);
	hash[3] = UINT64_C(0x963877195940EABD);
	hash[4] = UINT64_C(0x96283EE2A88EFFE3);
	hash[5] = UINT64_C(0xBE5E1E2553863992);
	hash[6] = UINT64_C(0x2B0199FC2C85B8AA);
	hash[7] = UINT64_C(0x0EB72DDC81C52CA2);
}

void sha512_hash_to_digest(uint64_t hash[8], uint8_t digest[SHA512_DIGEST_SIZE]) {
	for (int i = 0; i < 8; i++) {
		u64_to_u8_be(hash[i], &digest[i * 8]);
	}
}

void sha512_224_hash_to_digest(uint64_t hash[8], uint8_t digest[SHA512_224_DIGEST_SIZE]) {
	for (int i = 0; i < 3; i++) {
		u64_to_u8_be(hash[i], &digest[i * 8]);
	}
	
	uint32_t h4 = (uint32_t)(hash[3] >> 32);
	u32_to_u8_be(h4, &digest[24]);
}

void sha512_256_hash_to_digest(uint64_t hash[8], uint8_t digest[SHA512_256_DIGEST_SIZE]) {
	for (int i = 0; i < 4; i++) {
		u64_to_u8_be(hash[i], &digest[i * 8]);
	}
}

/* ch */
static uint64_t f1(uint64_t x, uint64_t y, uint64_t z) {
	return (x & y) ^ (~x & z);
}

/* maj */
static uint64_t f2(uint64_t x, uint64_t y, uint64_t z) {
	return (x & y) ^ (x & z) ^ (y & z);
}

/* e_0 */
static uint64_t f3(uint64_t x) {
	return rotate_right_64(x, 28) ^ rotate_right_64(x, 34) ^ rotate_right_64(x, 39);
}

/* e_1 */
static uint64_t f4(uint64_t x) {
	return rotate_right_64(x, 14) ^ rotate_right_64(x, 18) ^ rotate_right_64(x, 41);
}

static uint64_t f5(uint64_t x) {
	return rotate_right_64(x, 1) ^ rotate_right_64(x, 8) ^ (x >> 7);
}

static uint64_t f6(uint64_t x) {
	return rotate_right_64(x, 19) ^ rotate_right_64(x, 61) ^ (x >> 6);
}

void sha512_process_blocks(const uint8_t block[], uint64_t hash[8], unsigned int n) {
	for (unsigned int j = 0; j < n; j++) {
		const uint8_t* block1 = &block[j * 128];
		uint64_t a = hash[0];
		uint64_t b = hash[1];
		uint64_t c = hash[2];
		uint64_t d = hash[3];
		uint64_t e = hash[4];
		uint64_t f = hash[5];
		uint64_t g = hash[6];
		uint64_t h = hash[7];
		
		uint64_t temp1;
		uint64_t temp2;
		uint64_t W[80];
		
		for(uint_fast8_t i = 0; i < 16; i++) {
			W[i] = u8_to_u64_be(&block1[i * 8]);
		}
		
		for(uint_fast8_t i = 16; i < 80; i++) {
			W[i] = f6(W[i - 2]) + W[i - 7] + f5(W[i - 15]) + W[i - 16];
		}
		
		for(uint_fast8_t t = 0; t < 80; t++) {
			temp1 = h + f4(e) + f1(e, f, g) + sha512_table[t] + W[t];
			temp2 = f3(a) + f2(a, b, c);
			
			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}
		
		hash[0] += a;
		hash[1] += b;
		hash[2] += c;
		hash[3] += d;
		hash[4] += e;
		hash[5] += f;
		hash[6] += g;
		hash[7] += h;
	}
}

/* SHA-384 */
void sha384_init_hash(uint64_t hash[8]) {
	hash[0] = UINT64_C(0xCBBB9D5DC1059ED8);
	hash[1] = UINT64_C(0x629A292A367CD507);
	hash[2] = UINT64_C(0x9159015A3070DD17);
	hash[3] = UINT64_C(0x152FECD8F70E5939);
	hash[4] = UINT64_C(0x67332667FFC00B31);
	hash[5] = UINT64_C(0x8EB44A8768581511);
	hash[6] = UINT64_C(0xDB0C2E0D64F98FA7);
	hash[7] = UINT64_C(0x47B5481DBEFA4FA4);
}

void sha384_hash_to_digest(uint64_t hash[8], uint8_t digest[SHA384_DIGEST_SIZE]) {
	for (int i = 0; i < 6; i++)
		u64_to_u8_be(hash[i], &digest[i * 8]);
}

