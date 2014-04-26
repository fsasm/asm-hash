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

uint32_t u8_to_u32_le (uint8_t from[4]);
uint32_t u8_to_u32_be (uint8_t from[4]);

uint32_t rotate_left_32 (uint32_t value, unsigned int times);
uint32_t rotate_right_32 (uint32_t value, unsigned int times);

#endif
