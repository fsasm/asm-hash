/*
 * int_util_test.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-26
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// required by cmocka
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "int_util.h"

/* test the function with some constant values. */
static void test_rol8_const(void **state)
{
	(void)state;

	/* zero should stay zero */
	assert_true(0x00 == rol8(0x00, 	 0));
	assert_true(0x00 == rol8(0x00, 	 9));
	assert_true(0x00 == rol8(0x00, 	31));
	assert_true(0x00 == rol8(0x00, 128));

	/* pass through */
	assert_true(0xA8 == rol8(0xA8,  0));
	assert_true(0xEB == rol8(0xEB, 16));
	assert_true(0xF0 == rol8(0xF0,  8));
	assert_true(0xF0 == rol8(0xF0, 96));

	/* rotate by one */
	assert_true(0xE1 == rol8(0xF0,  1));
	assert_true(0xAA == rol8(0x55,  9));
	assert_true(0x55 == rol8(0xAA, 17));

	/* rotate arbitrary */
	assert_true(0x49 == rol8(0x94,  4));
	assert_true(0x6C == rol8(0x1B,  2));
	assert_true(0xF1 == rol8(0xC7,  6));
	assert_true(0x9A == rol8(0x35,  7));
	assert_true(0x78 == rol8(0xC3,  5));
}

/* adapted from test_rol8_const */
static void test_ror8_const(void **state)
{
	(void)state;

	/* zero should stay zero */
	assert_true(0x00 == ror8(0x00, 	 0));
	assert_true(0x00 == ror8(0x00, 	 9));
	assert_true(0x00 == ror8(0x00, 	31));
	assert_true(0x00 == ror8(0x00, 128));

	/* pass through */
	assert_true(0xA8 == ror8(0xA8,  0));
	assert_true(0xEB == ror8(0xEB, 16));
	assert_true(0xF0 == ror8(0xF0,  8));
	assert_true(0xF0 == ror8(0xF0, 96));

	/* rotate by one */
	assert_true(0x78 == ror8(0xF0,  1));
	assert_true(0xAA == ror8(0x55,  9));
	assert_true(0x55 == ror8(0xAA, 17));

	/* rotate arbitrary */
	assert_true(0x49 == ror8(0x94,  4));
	assert_true(0x6C == ror8(0x1B,  6));
	assert_true(0xF1 == ror8(0xC7,  2));
	assert_true(0x9A == ror8(0x35,  1));
	assert_true(0x78 == ror8(0xC3,  3));
}

static void test_rol16_const(void **state)
{
	(void)state;

	/* zero should stay zero */
	assert_true(0x0000 == rol16(0x0000,   0));
	assert_true(0x0000 == rol16(0x0000,   9));
	assert_true(0x0000 == rol16(0x0000,  31));
	assert_true(0x0000 == rol16(0x0000, 128));

	/* pass through */
	assert_true(0x9C8B == rol16(0x9C8B,  0));
	assert_true(0xA6EB == rol16(0xA6EB, 16));
	assert_true(0xCA62 == rol16(0xCA62, 32));
	assert_true(0x793F == rol16(0x793F, 96));

	/* rotate by one */
	assert_true(0x8F69 == rol16(0xC7B4,  1));
	assert_true(0xBF2B == rol16(0xDF95, 33));
	assert_true(0x5A79 == rol16(0xAD3C, 17));

	/* rotate arbitrary */
	assert_true(0x9FC0 == rol16(0xE04F,  9));
	assert_true(0x669B == rol16(0x6CD3,  3));
	assert_true(0xECB5 == rol16(0x2D7B, 10));
	assert_true(0xBB8A == rol16(0x7157, 11));
	assert_true(0x50A6 == rol16(0x4CA1,  7));
}

static void test_ror16_const(void **state)
{
	(void)state;

	/* zero should stay zero */
	assert_true(0x0000 == ror16(0x0000,   0));
	assert_true(0x0000 == ror16(0x0000,   9));
	assert_true(0x0000 == ror16(0x0000,  31));
	assert_true(0x0000 == ror16(0x0000, 128));

	/* pass through */
	assert_true(0x9C8B == ror16(0x9C8B,  0));
	assert_true(0xA6EB == ror16(0xA6EB, 16));
	assert_true(0xCA62 == ror16(0xCA62, 32));
	assert_true(0x793F == ror16(0x793F, 96));

	/* rotate by one */
	assert_true(0x63DA == ror16(0xC7B4,  1));
	assert_true(0xEFCA == ror16(0xDF95, 33));
	assert_true(0x569E == ror16(0xAD3C, 17));

	/* rotate arbitrary */
	assert_true(0x9FC0 == ror16(0xE04F,  7));
	assert_true(0x669B == ror16(0x6CD3, 13));
	assert_true(0xECB5 == ror16(0x2D7B,  6));
	assert_true(0xBB8A == ror16(0x7157,  5));
	assert_true(0x50A6 == ror16(0x4CA1,  9));
}

int main (void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_rol8_const),
		cmocka_unit_test(test_ror8_const),
		cmocka_unit_test(test_rol16_const),
		cmocka_unit_test(test_ror16_const),
	};
	
	return cmocka_run_group_tests(tests, NULL, NULL);
	
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
