/*
 * int_util.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-26
 */

#include "int_util.h"

void u64_to_u8_le (uint64_t from, uint8_t to[8]) {
	for (int i = 0; i < 8; i++) {
		to[i] = (uint8_t)(from & 0xFFu);
		from = from >> 8;
	}
}

void u64_to_u8_be (uint64_t from, uint8_t to[8]) {
	for (int i = 0; i < 8; i++) {
		to[7 - i] = (uint8_t)(from & 0xFFu);
		from = from >> 8;
	}
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

uint32_t u8_to_u32_le (uint8_t from[4]) {
	uint32_t to = 0;
	for (int i = 0; i < 4; i++) {
		to = (to << 8) | from[3 - i];
	}
	return to;
}

uint32_t u8_to_u32_be (uint8_t from[4]) {
	uint32_t to = 0;
	for (int i = 0; i < 4; i++) {
		to = (to << 8) | from[i];
	}
	return to;
}

uint32_t rotate_left_32 (uint32_t value, unsigned int times) {
	times %= 32;
	if (times == 0)
		return value;
	
	return (value << times) | (value >> (32 - times));
}

uint32_t rotate_right_32 (uint32_t value, unsigned int times) {
	times %= 32;
	if (times == 0)
		return value;
	
	return (value >> times) | (value << (32 - times));
}