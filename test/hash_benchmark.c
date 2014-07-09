/*
 * hash_benchmark.c
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-06-02
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include "test.h"

#if defined(HASH_MD5) || defined(HASH_MD5_ASM)

#define MD5_ENABLE_ASM
#include "md5.h"

#define HASH_TYPE uint32_t
#define HASH_SIZE 4
#define DEFAULT_RUNS 10000

#ifdef HASH_MD5
#define PROCESS_BLOCKS(hash) md5_process_blocks (test_block_128, hash, 2)
#else
#define PROCESS_BLOCKS(hash) md5_process_blocks_asm (test_block_128, hash, 2)
#endif

#elif defined(HASH_SHA1) || defined(HASH_SHA1_ASM)

#define SHA1_ENABLE_ASM
#include "sha1.h"

#define HASH_TYPE uint32_t
#define HASH_SIZE 5
#define DEFAULT_RUNS 3000

#ifdef HASH_SHA1
#define PROCESS_BLOCKS(hash) sha1_process_blocks (test_block_128, hash, 2)
#else
#define PROCESS_BLOCKS(hash) sha1_process_blocks_asm (test_block_128, hash, 2)
#endif

#elif defined(HASH_SHA256) || defined(HASH_SHA256_ASM)

#define SHA256_ENABLE_ASM
#include "sha256.h"

#define HASH_TYPE uint32_t
#define HASH_SIZE 8
#define DEFAULT_RUNS 1000

#ifdef HASH_SHA256
#define PROCESS_BLOCKS(hash) sha256_process_blocks (test_block_64, hash, 1)
#else
#define PROCESS_BLOCKS(hash) sha256_process_block_asm (test_block_64, hash)
#endif

#endif

/* for quicksort */
int compare (const void* a, const void* b) {
	uint64_t x = *(uint64_t*)a;
	uint64_t y = *(uint64_t*)b;
	if (x < y)
		return -1;
	if (x == y)
		return 0;
	return 1;
}

uint64_t get_median (size_t num_elements, uint64_t array[]) {
	if ((num_elements % 2) != 0)
		return array[num_elements / 2 + 1];
	
	return (array[num_elements / 2] + array[num_elements / 2 - 1]) / 2;
}

int main (int argc, char* argv[]) {
	size_t num_samples = 128;
	size_t num_runs = DEFAULT_RUNS;
	
	if (argc > 1)
		num_runs = atoi (argv[1]);
		
	if (argc > 2) 
		num_samples = atoi (argv[2]);
	
	HASH_TYPE hash[HASH_SIZE];
	
	uint64_t samples[num_samples];
	
	for (int_fast8_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < num_samples; j++) {
			struct timespec start_time;
			clock_gettime (CLOCK_REALTIME, &start_time);
			
			for (uint_fast32_t k = 0; k < num_runs; k++) {
				PROCESS_BLOCKS (hash);
			}
			
			struct timespec stop_time;
			clock_gettime (CLOCK_REALTIME, &stop_time);
			
			uint64_t start_ns = start_time.tv_sec * UINT64_C (1000000000) + start_time.tv_nsec;
			uint64_t stop_ns = stop_time.tv_sec * UINT64_C (1000000000) + stop_time.tv_nsec;
			
			uint64_t duration_us = (stop_ns - start_ns) / 1000u;
			samples[j] = duration_us;
		}
		
		qsort (samples, num_samples, sizeof (uint64_t), compare);
		uint64_t median = get_median (num_samples, samples);
		printf ("min:    %" PRIu64 " µs\n", samples[0]);
		printf ("median: %" PRIu64 " µs\n", median);
	}

	return 0;
}