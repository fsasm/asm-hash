/*
 * jh.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-10-12
 */

#include "jh.h"
#include "int_util.h"
#include <string.h>

void process_blocks (block* b, const uint8_t block[], unsigned int n, bool data_bits) {
	for (unsigned int i = 0; i < n; i++) {
		jh_process_block (block, b->func_data);
		
		block += 64;
	}
}

/* JH-256 */
void jh256_init (jh256_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init (&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_blocks, ctxt->hash);
	jh256_init_hash (ctxt->hash);
}

void jh256_init_hash (uint64_t hash[8][2]) {
	hash[0][0] = UINT64_C (0xEBD3202C41A398EB);
	hash[0][1] = UINT64_C (0xC145B29C7BBECD92);
	hash[1][0] = UINT64_C (0xFAC7D4609151931C);
	hash[1][1] = UINT64_C (0x038A507ED6820026);
	hash[2][0] = UINT64_C (0x45B92677269E23A4);
	hash[2][1] = UINT64_C (0x77941AD4481AFBE0);
	hash[3][0] = UINT64_C (0x7A176B0226ABB5CD);
	hash[3][1] = UINT64_C (0xA82FFF0F4224F056);
	hash[4][0] = UINT64_C (0x754D2E7F8996A371);
	hash[4][1] = UINT64_C (0x62E27DF70849141D);
	hash[5][0] = UINT64_C (0x948F2476F7957627);
	hash[5][1] = UINT64_C (0x6C29804757B6D587);
	hash[6][0] = UINT64_C (0x6C0D8EAC2D275E5C);
	hash[6][1] = UINT64_C (0x0F7A0557C6508451);
	hash[7][0] = UINT64_C (0xEA12247067D3E47B);
	hash[7][1] = UINT64_C (0x69D71CD313ABE389);

}

void jh256_add (jh256_context* ctxt, const uint8_t data[], size_t length) {
	block_add (&ctxt->b, length, data);
}

void jh256_finalize (jh256_context* ctxt) {
	block_util_finalize (
		&ctxt->b,
		BLOCK_LENGTH_128 | BLOCK_BIG_ENDIAN | BLOCK_SIMPLE_PADDING | BLOCK_EXTRA_PADDING 
	);
}

void jh256_get_digest (jh256_context* ctxt, uint8_t digest[JH256_DIGEST_SIZE]) {
	u64_to_u8_le (ctxt->hash[6][0], &digest[0]);
	u64_to_u8_le (ctxt->hash[6][1], &digest[8]);
	u64_to_u8_le (ctxt->hash[7][0], &digest[16]);
	u64_to_u8_le (ctxt->hash[7][1], &digest[24]);
}

/* JH-224 */
void jh224_init (jh224_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init (&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_blocks, ctxt->hash);
	jh224_init_hash (ctxt->hash);
}

void jh224_init_hash (uint64_t hash[8][2]) {
	hash[0][0] = UINT64_C (0xAC989AF962DDFE2D);
	hash[0][1] = UINT64_C (0xE734D619D6AC7CAE);
	hash[1][0] = UINT64_C (0x161230BC051083A4);
	hash[1][1] = UINT64_C (0x941466C9C63860B8);
	hash[2][0] = UINT64_C (0x6F7080259F89D966);
	hash[2][1] = UINT64_C (0xDC1A9B1D1BA39ECE);
	hash[3][0] = UINT64_C (0x106E367B5F32E811);
	hash[3][1] = UINT64_C (0xC106FA027F8594F9);
	hash[4][0] = UINT64_C (0xB340C8D85C1B4F1B);
	hash[4][1] = UINT64_C (0x9980736E7FA1F697);
	hash[5][0] = UINT64_C (0xD3A3EAADA593DFDC);
	hash[5][1] = UINT64_C (0x689A53C9DEE831A4);
	hash[6][0] = UINT64_C (0xE4A186EC8AA9B422);
	hash[6][1] = UINT64_C (0xF06CE59C95AC74D5);
	hash[7][0] = UINT64_C (0xBF2BABB5EA0D9615);
	hash[7][1] = UINT64_C (0x6EEA64DDF0DC1196);
}

void jh224_add (jh224_context* ctxt, const uint8_t data[], size_t length) {
	jh256_add (ctxt, data, length);
}

void jh224_finalize (jh256_context* ctxt) {
	jh256_finalize (ctxt);
}

void jh224_get_digest (jh224_context* ctxt, uint8_t digest[JH224_DIGEST_SIZE]) {
	u32_to_u8_le ((uint32_t)(ctxt->hash[6][0] >> 32), &digest[0]);
	u64_to_u8_le (ctxt->hash[6][1], &digest[4]);
	u64_to_u8_le (ctxt->hash[7][0], &digest[12]);
	u64_to_u8_le (ctxt->hash[7][1], &digest[20]);
}

/* JH-384 */
void jh384_init (jh384_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init (&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_blocks, ctxt->hash);
	jh384_init_hash (ctxt->hash);
}

void jh384_init_hash (uint64_t hash[8][2]) {
	hash[0][0] = UINT64_C (0x8A3913D8C63B1E48);
	hash[0][1] = UINT64_C (0x9B87DE4A895E3B6D);
	hash[1][0] = UINT64_C (0x2EAD80D468EAFA63);
	hash[1][1] = UINT64_C (0x67820F4821CB2C33);
	hash[2][0] = UINT64_C (0x28B982904DC8AE98);
	hash[2][1] = UINT64_C (0x4942114130EA55D4);
	hash[3][0] = UINT64_C (0xEC474892B255F536);
	hash[3][1] = UINT64_C (0xE13CF4BA930A25C7);
	hash[4][0] = UINT64_C (0x4C45DB278A7F9B56);
	hash[4][1] = UINT64_C (0x0EAF976349BDFC9E);
	hash[5][0] = UINT64_C (0xCD80AA267DC29F58);
	hash[5][1] = UINT64_C (0xDA2EEB9D8C8BC080);
	hash[6][0] = UINT64_C (0x3A37D5F8E881798A);
	hash[6][1] = UINT64_C (0x717AD1DDAD6739F4);
	hash[7][0] = UINT64_C (0x94D375A4BDD3B4A9);
	hash[7][1] = UINT64_C (0x7F734298BA3F6C97);
}

void jh384_add (jh384_context* ctxt, const uint8_t data[], size_t length) {
	jh256_add (ctxt, data, length);
}

void jh384_finalize (jh384_context* ctxt) {
	jh256_finalize (ctxt);
}

void jh384_get_digest (jh384_context* ctxt, uint8_t digest[JH384_DIGEST_SIZE]) {
	u64_to_u8_le (ctxt->hash[5][0], &digest[0]);
	u64_to_u8_le (ctxt->hash[5][1], &digest[8]);
	u64_to_u8_le (ctxt->hash[6][0], &digest[16]);
	u64_to_u8_le (ctxt->hash[6][1], &digest[24]);
	u64_to_u8_le (ctxt->hash[7][0], &digest[32]);
	u64_to_u8_le (ctxt->hash[7][1], &digest[40]);
}

/* JH-512 */
void jh512_init (jh512_context* ctxt) {
	if (ctxt == NULL)
		return;
	
	block_init (&ctxt->b, BLOCK_SIZE_512, ctxt->buffer, process_blocks, ctxt->hash);
	jh512_init_hash (ctxt->hash);
}

void jh512_init_hash (uint64_t hash[8][2]) {
	hash[0][0] = UINT64_C (0x17AA003E964BD16F);
	hash[0][1] = UINT64_C (0x43D5157A052E6A63);
	hash[1][0] = UINT64_C (0x0BEF970C8D5E228A);
	hash[1][1] = UINT64_C (0x61C3B3F2591234E9);
	hash[2][0] = UINT64_C (0x1E806F53C1A01D89);
	hash[2][1] = UINT64_C (0x806D2BEA6B05A92A);
	hash[3][0] = UINT64_C (0xA6BA7520DBCC8E58);
	hash[3][1] = UINT64_C (0xF73BF8BA763A0FA9);
	hash[4][0] = UINT64_C (0x694AE34105E66901);
	hash[4][1] = UINT64_C (0x5AE66F2E8E8AB546);
	hash[5][0] = UINT64_C (0x243C84C1D0A74710);
	hash[5][1] = UINT64_C (0x99C15A2DB1716E3B);
	hash[6][0] = UINT64_C (0x56F8B19DECF657CF);
	hash[6][1] = UINT64_C (0x56B116577C8806A7);
	hash[7][0] = UINT64_C (0xFB1785E6DFFCC2E3);
	hash[7][1] = UINT64_C (0x4BDD8CCC78465A54);
}

void jh512_add (jh512_context* ctxt, const uint8_t data[], size_t length) {
	jh256_add (ctxt, data, length);
}

void jh512_finalize (jh512_context* ctxt) {
	jh256_finalize (ctxt);
}

void jh512_get_digest (jh512_context* ctxt, uint8_t digest[JH512_DIGEST_SIZE]) {
	u64_to_u8_le (ctxt->hash[4][0], &digest[0]);
	u64_to_u8_le (ctxt->hash[4][1], &digest[8]);
	u64_to_u8_le (ctxt->hash[5][0], &digest[16]);
	u64_to_u8_le (ctxt->hash[5][1], &digest[24]);
	u64_to_u8_le (ctxt->hash[6][0], &digest[32]);
	u64_to_u8_le (ctxt->hash[6][1], &digest[40]);
	u64_to_u8_le (ctxt->hash[7][0], &digest[48]);
	u64_to_u8_le (ctxt->hash[7][1], &digest[56]);
}



static void sbox_64 (uint64_t* x0, uint64_t* x1, uint64_t* x2, uint64_t* x3, uint64_t c) {
	uint64_t y0 = *x0;
	uint64_t y1 = *x1;
	uint64_t y2 = *x2;
	uint64_t y3 = *x3;
	
	y3 = ~y3;
	y0 ^= c & (~y2);
	uint64_t temp = c ^ (y0 & y1);
	y0 ^= y2 & y3;
	y3 ^= y2 & (~y1);
	y1 ^= y0 & y2;
	y2 ^= y0 & (~y3);
	y0 ^= y1 | y3;
	y3 ^= y1 & y2;
	y1 ^= temp & y0;
	y2 ^= temp;
	
	*x0 = y0;
	*x1 = y1;
	*x2 = y2;
	*x3 = y3;
}

static void lin_64 (uint64_t* x0, uint64_t* x1, uint64_t* x2, uint64_t* x3,
					uint64_t* x4, uint64_t* x5, uint64_t* x6, uint64_t* x7) {
	uint64_t a0 = *x0;
	uint64_t a1 = *x1;
	uint64_t a2 = *x2;
	uint64_t a3 = *x3;
	uint64_t a4 = *x4;
	uint64_t a5 = *x5;
	uint64_t a6 = *x6;
	uint64_t a7 = *x7;
	
	a4 = a4 ^ a1;
	a5 = a5 ^ a2;
	a6 = a6 ^ a3 ^ a0;
	a7 = a7 ^ a0;
	
	a0 = a0 ^ a5;
	a1 = a1 ^ a6;
	a2 = a2 ^ a7 ^ a4;
	a3 = a3 ^ a4;
	
	*x0 = a0;
	*x1 = a1;
	*x2 = a2;
	*x3 = a3;
	*x4 = a4;
	*x5 = a5;
	*x6 = a6;
	*x7 = a7;
}

static uint64_t swap1_64 (uint64_t a) {
	uint64_t mask = UINT64_C (0x5555555555555555);
	return ((a & mask) << 1) | ((a & (~mask)) >> 1);
}

static uint64_t swap2_64 (uint64_t a) {
	uint64_t mask = UINT64_C (0x3333333333333333);
	return ((a & mask) << 2) | ((a & (~mask)) >> 2);
}

static uint64_t swap4_64 (uint64_t a) {
	uint64_t mask = UINT64_C (0x0F0F0F0F0F0F0F0F);
	return ((a & mask) << 4) | ((a & (~mask)) >> 4);
}

static uint64_t swap8_64 (uint64_t a) {
	uint64_t mask = UINT64_C (0x00FF00FF00FF00FF);
	return ((a & mask) << 8) | ((a & (~mask)) >> 8);
}

static uint64_t swap16_64 (uint64_t a) {
	uint64_t mask = UINT64_C (0x0000FFFF0000FFFF);
	return ((a & mask) << 16) | ((a & (~mask)) >> 16);
}

static uint64_t swap32_64 (uint64_t a) {
	return (a << 32) | (a >> 32);
}

static uint64_t round_constant[42][4] = {
	{0x67F815DFA2DED572, 0x571523B70A15847B, 0xF6875A4D90D6AB81, 0x402BD1C3C54F9F4E},
	{0x9CFA455CE03A98EA, 0x9A99B26699D2C503, 0x8A53BBF2B4960266, 0x31A2DB881A1456B5},
	{0xDB0E199A5C5AA303, 0x1044C1870AB23F40, 0x1D959E848019051C, 0xDCCDE75EADEB336F},
	{0x416BBF029213BA10, 0xD027BBF7156578DC, 0x5078AA3739812C0A, 0xD3910041D2BF1A3F},
	{0x907ECCF60D5A2D42, 0xCE97C0929C9F62DD, 0xAC442BC70BA75C18, 0x23FCC663D665DFD1},
	{0x1AB8E09E036C6E97, 0xA8EC6C447E450521, 0xFA618E5DBB03F1EE, 0x97818394B29796FD},
	{0x2F3003DB37858E4A, 0x956A9FFB2D8D672A, 0x6C69B8F88173FE8A, 0x14427FC04672C78A},
	{0xC45EC7BD8F15F4C5, 0x80BB118FA76F4475, 0xBC88E4AEB775DE52, 0xF4A3A6981E00B882},
	{0x1563A3A9338FF48E, 0x89F9B7D524565FAA, 0xFDE05A7C20EDF1B6, 0x362C42065AE9CA36},
	{0x3D98FE4E433529CE, 0xA74B9A7374F93A53, 0x86814E6F591FF5D0, 0x9F5AD8AF81AD9D0E},
	{0x6A6234EE670605A7, 0x2717B96EBE280B8B, 0x3F1080C626077447, 0x7B487EC66F7EA0E0},
	{0xC0A4F84AA50A550D, 0x9EF18E979FE7E391, 0xD48D605081727686, 0x62B0E5F3415A9E7E},
	{0x7A205440EC1F9FFC, 0x84C9F4CE001AE4E3, 0xD895FA9DF594D74F, 0xA554C324117E2E55},
	{0x286EFEBD2872DF5B, 0xB2C4A50FE27FF578, 0x2ED349EEEF7C8905, 0x7F5928EB85937E44},
	{0x4A3124B337695F70, 0x65E4D61DF128865E, 0xE720B95104771BC7, 0x8A87D423E843FE74},
	{0xF2947692A3E8297D, 0xC1D9309B097ACBDD, 0xE01BDC5BFB301B1D, 0xBF829CF24F4924DA},
	{0xFFBF70B431BAE7A4, 0x48BCF8DE0544320D, 0x39D3BB5332FCAE3B, 0xA08B29E0C1C39F45},
	{0x0F09AEF7FD05C9E5, 0x34F1904212347094, 0x95ED44E301B771A2, 0x4A982F4F368E3BE9},
	{0x15F66CA0631D4088, 0xFFAF52874B44C147, 0x30C60AE2F14ABB7E, 0xE68C6ECCC5B67046},
	{0x00CA4FBD56A4D5A4, 0xAE183EC84B849DDA, 0xADD1643045CE5773, 0x67255C1468CEA6E8},
	{0x16E10ECBF28CDAA3, 0x9A99949A5806E933, 0x7B846FC220B2601F, 0x1885D1A07FACCED1},
	{0xD319DD8DA15B5932, 0x46B4A5AAC01C9A50, 0xBA6B04E467633D9F, 0x7EEE560BAB19CAF6},
	{0x742128A9EA79B11F, 0xEE51363B35F7BDE9, 0x76D350755AAC571D, 0x01707DA3FEC2463A},
	{0x42D8A498AFC135F7, 0x79676B9E20ECED78, 0xA8DB3AEA15638341, 0x832C83324D3BC3FA},
	{0xF347271C1F3B40A7, 0x9A762DB734F04059, 0xFD4F21D26C4E3EE7, 0xEF5957DC398DFDB8},
	{0xDAEB492B490C9B8D, 0x0D70F36849D7A25B, 0x84558D7AD0AE3B7D, 0x658EF8E4F0E9A5F5},
	{0x533B1036F4A2B8A0, 0x5AEC3E759E07A80C, 0x4F88E85692946891, 0x4CBCBAF8555CB05B},
	{0x7B9487F3993BBBE3, 0x5D1C6B72D6F4DA75, 0x6DB334DC28ACAE64, 0x71DB28B850A5346C},
	{0x2A518D10F2E261F8, 0xFC75DD593364DBE3, 0xA23FCE43F1BCAC1C, 0xB043E8023CD1BB67},
	{0x75A12988CA5B0A33, 0x5C5316B44D19347F, 0x1E4D790EC3943B92, 0x3FAFEEB6D7757479},
	{0x21391ABEF7D4A8EA, 0x5127234C097EF45C, 0xD23C32BA5324A326, 0xADD5A66D4A17A344},
	{0x08C9F2AFA63E1DB5, 0x563C6B91983D5983, 0x4D608672A17CF84C, 0xF6C76E08CC3EE246},
	{0x5E76BCB1B333982F, 0x2AE6C4EFA566D62B, 0x36D4C1BEE8B6F406, 0x6321EFBC1582EE74},
	{0x69C953F40D4EC1FD, 0x26585806C45A7DA7, 0x16FAE0061614C17E, 0x3F9D63283DAF907E},
	{0x0CD29B00E3F2C9D2, 0x300CD4B730CEAA5F, 0x9832E0F216512A74, 0x9AF8CEE3D830EB0D},
	{0x9279F1B57B9EC54B, 0xD36886046EE651FF, 0x316796E6574D239B, 0x05750A17F3A6E6CC},
	{0xCE6C3213D98176B1, 0x62A205F88452173C, 0x47154778B3CB2BF4, 0x486A9323825446FF},
	{0x65655E4E0758DF38, 0x8E5086FC897CFCF2, 0x86CA0BD0442E7031, 0x4E477830A20940F0},
	{0x8338F7D139EEA065, 0xBD3A2CE437E95EF7, 0x6FF8130126B29721, 0xE7DE9FEFD1ED44A3},
	{0xD992257615DFA08B, 0xBE42DC12F6F7853C, 0x7EB027AB7CECA7D8, 0xDEA83EAADA7D8D53},
	{0xD86902BD93CE25AA, 0xF908731AFD43F65A, 0xA5194A17DAEF5FC0, 0x6A21FD4C33664D97},
	{0x701541DB3198B435, 0x9B54CDEDBB0F1EEA, 0x72409751A163D09A, 0xE26F4791BF9D75F6}
};

void jh_process_block (const uint8_t block[64], uint64_t hash[8][2]) {
	for (uint_fast8_t i = 0; i < 4; i++) {
		hash[i][0] ^= u8_to_u64_le (&block[i * 16]);
		hash[i][1] ^= u8_to_u64_le (&block[i * 16 + 8]);
	}
	
	for (uint_fast8_t r = 0; r < 42; r++) {
		sbox_64 (&hash[0][0], &hash[2][0], &hash[4][0], &hash[6][0], round_constant[r][0]);
		sbox_64 (&hash[0][1], &hash[2][1], &hash[4][1], &hash[6][1], round_constant[r][1]);
		sbox_64 (&hash[1][0], &hash[3][0], &hash[5][0], &hash[7][0], round_constant[r][2]);
		sbox_64 (&hash[1][1], &hash[3][1], &hash[5][1], &hash[7][1], round_constant[r][3]);
		
		lin_64 (&hash[0][0], &hash[2][0], &hash[4][0], &hash[6][0], &hash[1][0], &hash[3][0], &hash[5][0], &hash[7][0]);
		lin_64 (&hash[0][1], &hash[2][1], &hash[4][1], &hash[6][1], &hash[1][1], &hash[3][1], &hash[5][1], &hash[7][1]);
		
		
		uint64_t temp;
		switch (r % 7) {
			case 0:
				hash[1][0] = swap1_64 (hash[1][0]);
				hash[1][1] = swap1_64 (hash[1][1]);
				hash[3][0] = swap1_64 (hash[3][0]);
				hash[3][1] = swap1_64 (hash[3][1]);
				hash[5][0] = swap1_64 (hash[5][0]);
				hash[5][1] = swap1_64 (hash[5][1]);
				hash[7][0] = swap1_64 (hash[7][0]);
				hash[7][1] = swap1_64 (hash[7][1]);
				break;
				
			case 1:
				hash[1][0] = swap2_64 (hash[1][0]);
				hash[1][1] = swap2_64 (hash[1][1]);
				hash[3][0] = swap2_64 (hash[3][0]);
				hash[3][1] = swap2_64 (hash[3][1]);
				hash[5][0] = swap2_64 (hash[5][0]);
				hash[5][1] = swap2_64 (hash[5][1]);
				hash[7][0] = swap2_64 (hash[7][0]);
				hash[7][1] = swap2_64 (hash[7][1]);
				break;
				
			case 2:
				hash[1][0] = swap4_64 (hash[1][0]);
				hash[1][1] = swap4_64 (hash[1][1]);
				hash[3][0] = swap4_64 (hash[3][0]);
				hash[3][1] = swap4_64 (hash[3][1]);
				hash[5][0] = swap4_64 (hash[5][0]);
				hash[5][1] = swap4_64 (hash[5][1]);
				hash[7][0] = swap4_64 (hash[7][0]);
				hash[7][1] = swap4_64 (hash[7][1]);
				break;
				
			case 3:
				hash[1][0] = swap8_64 (hash[1][0]);
				hash[1][1] = swap8_64 (hash[1][1]);
				hash[3][0] = swap8_64 (hash[3][0]);
				hash[3][1] = swap8_64 (hash[3][1]);
				hash[5][0] = swap8_64 (hash[5][0]);
				hash[5][1] = swap8_64 (hash[5][1]);
				hash[7][0] = swap8_64 (hash[7][0]);
				hash[7][1] = swap8_64 (hash[7][1]);
				break;
				
			case 4:
				hash[1][0] = swap16_64 (hash[1][0]);
				hash[1][1] = swap16_64 (hash[1][1]);
				hash[3][0] = swap16_64 (hash[3][0]);
				hash[3][1] = swap16_64 (hash[3][1]);
				hash[5][0] = swap16_64 (hash[5][0]);
				hash[5][1] = swap16_64 (hash[5][1]);
				hash[7][0] = swap16_64 (hash[7][0]);
				hash[7][1] = swap16_64 (hash[7][1]);
				break;
				
			case 5:
				hash[1][0] = swap32_64 (hash[1][0]);
				hash[1][1] = swap32_64 (hash[1][1]);
				hash[3][0] = swap32_64 (hash[3][0]);
				hash[3][1] = swap32_64 (hash[3][1]);
				hash[5][0] = swap32_64 (hash[5][0]);
				hash[5][1] = swap32_64 (hash[5][1]);
				hash[7][0] = swap32_64 (hash[7][0]);
				hash[7][1] = swap32_64 (hash[7][1]);
				break;
				
			case 6:
				temp = hash[1][0];
				hash[1][0] = hash[1][1];
				hash[1][1] = temp;
				
				temp = hash[3][0];
				hash[3][0] = hash[3][1];
				hash[3][1] = temp;
				
				temp = hash[5][0];
				hash[5][0] = hash[5][1];
				hash[5][1] = temp;
				
				temp = hash[7][0];
				hash[7][0] = hash[7][1];
				hash[7][1] = temp;
				break;
		}
	}
	
	for (uint_fast8_t i = 0; i < 4; i++) {
		hash[i + 4][0] ^= u8_to_u64_le (&block[i * 16]);
		hash[i + 4][1] ^= u8_to_u64_le (&block[i * 16 + 8]);
	}
}
