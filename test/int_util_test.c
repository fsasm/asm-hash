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
	/* rotate_left_32 */
	{
		printf ("rotate_left_32:  ");
		uint32_t value = UINT32_C(0x55555555);
		uint32_t expected = UINT32_C(0xAAAAAAAA);
		bool passed = true;
		
		for (uint_fast8_t i = 0; i < 64; i += 2) {
			passed = passed && (value == rotate_left_32 (value, i));
			passed = passed && (expected == rotate_left_32 (value, i + 1));
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* rotate_right_32 */
	{
		printf ("rotate_right_32: ");
		uint32_t expected = UINT32_C(0x55555555);
		uint32_t value = UINT32_C(0xAAAAAAAA);
		bool passed = true;
		
		for (uint_fast8_t i = 0; i < 64; i += 2) {
			passed = passed && (value == rotate_right_32 (value, i));
			passed = passed && (expected == rotate_right_32 (value, i + 1));
		}
		
		if (passed) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	
	/* TODO tests for u64_to_u8_le/be */
	
	/* u32_to_u8_le */
	{
		printf ("u32_to_u8_le:    ");
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
		printf ("u32_to_u8_be:    ");
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
	
	/* u8_to_u32_le */
	{
		printf ("u8_to_u32_le:    ");
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
		printf ("u8_to_u32_be:    ");
		uint8_t value[4] = {0x12, 0x34, 0x56, 0x78};
		uint32_t expected = UINT32_C(0x12345678);
		
		if (expected == u8_to_u32_be (value)) {
			printf ("test passed\n");
		} else {
			printf ("test failed\n");
		}
	}
	return 0;
}
