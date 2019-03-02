/*
 * int_util_test.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-26
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "int_util.h"

int main (void) {
	/* rol8 */
	{
		printf ("rol8:  ");
		uint8_t value = UINT8_C(0x55);
		uint8_t expected = UINT8_C(0xAA);
		bool passed = true;
		
		for (uint_fast8_t i = 0; i < 16; i += 2) {
			passed = passed && (value == rol8 (value, i));
			passed = passed && (expected == rol8 (value, i + 1));
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* ror8 */
	{
		printf ("ror8:  ");
		uint8_t expected = UINT8_C(0x55);
		uint8_t value = UINT8_C(0xAA);
		bool passed = true;
		
		for (uint_fast8_t i = 0; i < 16; i += 2) {
			passed = passed && (value == ror8 (value, i));
			passed = passed && (expected == ror8 (value, i + 1));
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* rol16 */
	{
		printf ("rol16: ");
		uint16_t value = UINT16_C(0x5555);
		uint16_t expected = UINT16_C(0xAAAA);
		bool passed = true;
		
		for (uint_fast8_t i = 0; i < 32; i += 2) {
			passed = passed && (value == rol16 (value, i));
			passed = passed && (expected == rol16 (value, i + 1));
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* ror16 */
	{
		printf ("ror16: ");
		uint16_t expected = UINT16_C(0x5555);
		uint16_t value = UINT16_C(0xAAAA);
		bool passed = true;
		
		for (uint_fast8_t i = 0; i < 32; i += 2) {
			passed = passed && (value == ror16 (value, i));
			passed = passed && (expected == ror16 (value, i + 1));
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* rol32 */
	{
		printf ("rol32: ");
		uint32_t value = UINT32_C(0x55555555);
		uint32_t expected = UINT32_C(0xAAAAAAAA);
		bool passed = true;
		
		for (uint_fast8_t i = 0; i < 64; i += 2) {
			passed = passed && (value == rol32 (value, i));
			passed = passed && (expected == rol32 (value, i + 1));
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* ror32 */
	{
		printf ("ror32: ");
		uint32_t expected = UINT32_C(0x55555555);
		uint32_t value = UINT32_C(0xAAAAAAAA);
		bool passed = true;
		
		for (uint_fast8_t i = 0; i < 64; i += 2) {
			passed = passed && (value == ror32 (value, i));
			passed = passed && (expected == ror32 (value, i + 1));
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* rol64 */
	{
		printf ("rol64: ");
		uint64_t value = UINT64_C(0x5555555555555555);
		uint64_t expected = UINT64_C(0xAAAAAAAAAAAAAAAA);
		bool passed = true;
		
		for (uint_fast8_t i = 0; i < 128; i += 2) {
			passed = passed && (value == rol64 (value, i));
			passed = passed && (expected == rol64 (value, i + 1));
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* ror64 */
	{
		printf ("ror64: ");
		uint64_t expected = UINT64_C(0x5555555555555555);
		uint64_t value = UINT64_C(0xAAAAAAAAAAAAAAAA);
		bool passed = true;
		
		for (uint_fast8_t i = 0; i < 128; i += 2) {
			passed = passed && (value == ror64 (value, i));
			passed = passed && (expected == ror64 (value, i + 1));
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* u32_to_u8_le */
	{
		printf ("u32_to_u8_le: ");
		uint32_t value = UINT32_C(0x78563412);
		uint8_t expected[4] = {0x12, 0x34, 0x56, 0x78};
		uint8_t value2[4];
		bool passed = true;
		
		u32_to_u8_le (value, value2);
		
		for (uint_fast8_t i = 0; i < 4; i++) {
			passed = passed && (expected[i] == value2[i]);
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* u32_to_u8_be */
	{
		printf ("u32_to_u8_be: ");
		uint32_t value = UINT32_C(0x12345678);
		uint8_t expected[4] = {0x12, 0x34, 0x56, 0x78};
		uint8_t value2[4];
		bool passed = true;
		
		u32_to_u8_be (value, value2);
		
		for (uint_fast8_t i = 0; i < 4; i++) {
			passed = passed && (expected[i] == value2[i]);
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* u64_to_u8_le */
	{
		printf ("u64_to_u8_le: ");
		uint64_t value = UINT64_C(0xF0DEBC9A78563412);
		uint8_t expected[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		uint8_t value2[8];
		bool passed = true;
		
		u64_to_u8_le (value, value2);
		
		for (uint_fast8_t i = 0; i < 8; i++) {
			passed = passed && (expected[i] == value2[i]);
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* u64_to_u8_be */
	{
		printf ("u64_to_u8_be: ");
		uint64_t value = UINT64_C(0x123456789ABCDEF0);
		uint8_t expected[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		uint8_t value2[8];
		bool passed = true;
		
		u64_to_u8_be (value, value2);
		
		for (uint_fast8_t i = 0; i < 8; i++) {
			passed = passed && (expected[i] == value2[i]);
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* u8_to_u32_le */
	{
		printf ("u8_to_u32_le: ");
		uint8_t value[4] = {0x12, 0x34, 0x56, 0x78};
		uint32_t expected = UINT32_C(0x78563412);
		
		if (expected == u8_to_u32_le (value)) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* u8_to_u32_le */
	{
		printf ("u8_to_u32_be: ");
		uint8_t value[4] = {0x12, 0x34, 0x56, 0x78};
		uint32_t expected = UINT32_C(0x12345678);
		
		if (expected == u8_to_u32_be (value)) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* u8_to_u64_le */
	{
		printf ("u8_to_u64_le: ");
		uint8_t value[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		uint64_t expected = UINT64_C(0xF0DEBC9A78563412);
		
		if (expected == u8_to_u64_le (value)) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* u8_to_u64_le */
	{
		printf ("u8_to_u64_be: ");
		uint8_t value[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		uint64_t expected = UINT64_C(0x123456789ABCDEF0);
		
		if (expected == u8_to_u64_be (value)) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	return 0;
}
