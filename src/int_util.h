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

uint8_t rol8(uint8_t value, unsigned int times);
uint8_t ror8(uint8_t value, unsigned int times);

uint16_t rol16(uint16_t value, unsigned int times);
uint16_t ror16(uint16_t value, unsigned int times);

uint32_t rol32(uint32_t value, unsigned int times);
uint32_t ror32(uint32_t value, unsigned int times);

uint64_t rol64(uint64_t value, unsigned int times);
uint64_t ror64(uint64_t value, unsigned int times);

#endif
