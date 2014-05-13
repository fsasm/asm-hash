#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "md5.h"

extern void md5_process_block_asm (uint32_t* hash, uint8_t* block);
#define NUM_SAMPLES 128
#define N 100000u

uint8_t test_block[] = {
	1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 52, 53, 54, 55, 56,
	57, 58, 59, 60, 61, 62, 63, 64
};

uint64_t samples[NUM_SAMPLES] = {0};

void benchmark (void) {
	uint32_t hash[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
	for (int i = 0; i < NUM_SAMPLES; i++) {
		struct timespec start_time;
		clock_gettime (CLOCK_REALTIME, &start_time);

		for (uint_fast32_t i = 0; i < N; i++) {
			md5_process_block_asm (test_block, hash);
		}

		struct timespec stop_time;
		clock_gettime (CLOCK_REALTIME, &stop_time);

		uint64_t start_ns = start_time.tv_sec * 1000000000u + start_time.tv_nsec;
		uint64_t stop_ns = stop_time.tv_sec * 1000000000u + stop_time.tv_nsec;

		uint64_t duration_us = (stop_ns - start_ns) / 1000u ;
		samples[i] = duration_us;
	}
}

int compare (const void* a, const void* b) {
	if (*(uint64_t*)a < *(uint64_t*)b)
		return -1;
	if (*(uint64_t*)a == *(uint64_t*)b)
		return 0;
	return +1;
}

int main (void) {
	for (int i = 0; i < 3; i++) {
		benchmark ();
		qsort (samples, NUM_SAMPLES, sizeof (uint64_t), compare);
		printf ("min:    %llu µs\n", samples[0]);
		uint64_t median = samples[(NUM_SAMPLES - 1) / 2] / 2;
		median += samples[NUM_SAMPLES / 2] / 2;
		printf ("median: %llu µs\n", median);
	}
	return 0;
}
