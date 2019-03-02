/*
 * int_util.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-26
 */

#include "int_util.h"

#define ROT_LOOP_LE(n) \
	for (int i = 0; i < n; i++) { \
		to[i] = (uint8_t)(from & 0xFFu); \
		from = from >> 8; \
	}

#define ROT_LOOP_BE(n) \
	for (int i = 0; i < n; i++) { \
		to[n - 1 - i] = (uint8_t)(from & 0xFFu); \
		from = from >> 8; \
	}

void u64_to_u8_le (uint64_t from, uint8_t to[8]) {
	ROT_LOOP_LE(8)
}

void u64_to_u8_be (uint64_t from, uint8_t to[8]) {
	ROT_LOOP_BE(8)
}

void u32_to_u8_le (uint32_t from, uint8_t to[4]) {
	for (int i = 0; i < 4; i++) {
		to[i] = (uint8_t)(from & 0xFFu);
		from = from >> 8;
	}
}

void u32_to_u8_be (uint32_t from, uint8_t to[4]) {
	for (int i = 0; i < 4; i++) {
		to[3 - i] = (uint8_t)(from & 0xFFu);
		from = from >> 8;
	}
}

uint32_t u8_to_u32_le (const uint8_t from[4]) {
	uint32_t to = 0;
	for (int i = 0; i < 4; i++) {
		to = (to << 8) | from[3 - i];
	}
	return to;
}

uint32_t u8_to_u32_be (const uint8_t from[4]) {
	uint32_t to = 0;
	for (int i = 0; i < 4; i++) {
		to = (to << 8) | from[i];
	}
	return to;
}

uint64_t u8_to_u64_le (const uint8_t from[8]) {
	uint64_t to = 0;
	for (int i = 0; i < 8; i++) {
		to = (to << 8) | from[7 - i];
	}
	return to;
}

uint64_t u8_to_u64_be (const uint8_t from[8]) {
	uint64_t to = 0;
	for (int i = 0; i < 8; i++) {
		to = (to << 8) | from[i];
	}
	return to;
}

#define ROT_UINT(n) uint ## n ## _t
#define ROL_NAME(n) rol ## n
#define ROR_NAME(n) ror ## n

#define ROL_FUNC_PROTO(n) \
	ROT_UINT(n) ROL_NAME(n) (ROT_UINT(n) value, unsigned int times)

#define ROR_FUNC_PROTO(n) \
	ROT_UINT(n) ROR_NAME(n) (ROT_UINT(n) value, unsigned int times)

#define ROL_FUNC(n) \
	ROL_FUNC_PROTO(n) \
	{ \
		times %= n; \
		if (times == 0) \
			return value; \
		return (value << times) | (value >> (n - times)); \
	}

#define ROR_FUNC(n) \
	ROR_FUNC_PROTO(n) \
	{ \
		times %= n; \
		if (times == 0) \
			return value; \
		return (value >> times) | (value << (n - times)); \
	}

ROL_FUNC( 8)
ROL_FUNC(16)
ROL_FUNC(32)
ROL_FUNC(64)

ROR_FUNC( 8)
ROR_FUNC(16)
ROR_FUNC(32)
ROR_FUNC(64)

