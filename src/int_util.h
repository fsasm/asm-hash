/*
 * int_util.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-25
 */

#include <stdint.h>

#ifndef INT_UTIL_H
#define INT_UTIL_H

void u64_to_u8_le (uint64_t from, uint8_t to[8]);
void u64_to_u8_be (uint64_t from, uint8_t to[8]);

void u32_to_u8_le (uint32_t from, uint8_t to[4]);
void u32_to_u8_be (uint32_t from, uint8_t to[4]);

uint32_t u8_to_u32_le (const uint8_t from[4]);
uint32_t u8_to_u32_be (const uint8_t from[4]);

uint64_t u8_to_u64_le (const uint8_t from[8]);
uint64_t u8_to_u64_be (const uint8_t from[8]);

uint8_t rotate_left_8 (uint8_t value, unsigned int times);
uint8_t rotate_right_8 (uint8_t value, unsigned int times);

uint16_t rotate_left_16 (uint16_t value, unsigned int times);
uint16_t rotate_right_16 (uint16_t value, unsigned int times);

uint32_t rotate_left_32 (uint32_t value, unsigned int times);
uint32_t rotate_right_32 (uint32_t value, unsigned int times);

uint64_t rotate_left_64 (uint64_t value, unsigned int times);
uint64_t rotate_right_64 (uint64_t value, unsigned int times);

#endif
