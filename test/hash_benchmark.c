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
#include "md5_core.h"

#define HASH_TYPE uint32_t
#define HASH_SIZE 4
#define DEFAULT_RUNS 10000
#define NUM_BYTES 128

#ifdef HASH_MD5
#define PROCESS_BLOCKS(hash) md5_process_blocks (test_block_128, hash, 2)
#else
#define PROCESS_BLOCKS(hash) md5_process_blocks_asm (test_block_128, hash, 2)
#endif

#elif defined(HASH_SHA1) || defined(HASH_SHA1_ASM)

#define SHA1_ENABLE_ASM
#include "sha1_core.h"

#define HASH_TYPE uint32_t
#define HASH_SIZE 5
#define DEFAULT_RUNS 3000
#define NUM_BYTES 128

#ifdef HASH_SHA1
#define PROCESS_BLOCKS(hash) sha1_process_blocks (test_block_128, hash, 2)
#else
#define PROCESS_BLOCKS(hash) sha1_process_blocks_asm (test_block_128, hash, 2)
#endif

#elif defined(HASH_SHA256) || defined(HASH_SHA256_ASM)

#define SHA256_ENABLE_ASM
#include "sha256_core.h"

#define HASH_TYPE uint32_t
#define HASH_SIZE 8
#define DEFAULT_RUNS 1000
#define NUM_BYTES (64 * 4)

#ifdef HASH_SHA256
#define PROCESS_BLOCKS(hash) sha256_process_blocks (test_block_256, hash, 4)
#else
#define PROCESS_BLOCKS(hash) sha256_process_blocks_asm (test_block_256, hash, 4)
#endif

#elif defined(HASH_SHA512) || defined(HASH_SHA512_ASM)

#define SHA512_ENABLE_ASM
#include "sha512.h"

#define HASH_TYPE uint64_t
#define HASH_SIZE 8
#define DEFAULT_RUNS 500
#define NUM_BYTES (128 * 2)

#ifdef HASH_SHA512
#define PROCESS_BLOCKS(hash) sha512_process_blocks (test_block_256, hash, 2)
#else
#define PROCESS_BLOCKS(hash) sha512_process_blocks_asm (test_block_256, hash, 2)
#endif

#elif defined(HASH_BLAKE256) || defined(HASH_BLAKE256_ASM)

#define BLAKE256_ENABLE_ASM
#include "blake256.h"

#define HASH_TYPE uint32_t
#define HASH_SIZE 8
#define DEFAULT_RUNS 1000
#define NUM_BYTES (64)

#ifdef HASH_BLAKE256
#define PROCESS_BLOCKS(hash) blake256_process_block (test_block_64, hash, UINT64_C (0x6A09E667BB67AE85))
#else
#define PROCESS_BLOCKS(hash) blake256_process_block_asm (test_block_64, hash, UINT64_C (0x6A09E667BB67AE85))
#endif

#elif defined(HASH_BLAKE512) || defined(HASH_BLAKE512_ASM)

#define BLAKE512_ENABLE_ASM
#include "blake512.h"

#define HASH_TYPE uint64_t
#define HASH_SIZE 8
#define DEFAULT_RUNS 1000
#define NUM_BYTES (128)

#ifdef HASH_BLAKE512
#define PROCESS_BLOCKS(hash) blake512_process_block (test_block_128, hash, UINT64_C (0x6A09E667BB67AE85))
#else
#define PROCESS_BLOCKS(hash) blake512_process_block_asm (test_block_128, hash, UINT64_C (0x6A09E667BB67AE85))
#endif

#elif defined(HASH_WHIRLPOOL) || defined(HASH_WHIRLPOOL_ASM)

#define WHIRLPOOL_ENABLE_ASM
#include "whirlpool.h"

#define HASH_TYPE uint64_t
#define HASH_SIZE 8
#define DEFAULT_RUNS 1000
#define NUM_BYTES (128)

#ifdef HASH_WHIRLPOOL
#define PROCESS_BLOCKS(hash) whirlpool_process_blocks(test_block_128, hash, 2)
#else
#define PROCESS_BLOCKS(hash) whirlpool_process_blocks_asm (test_block_128, hash, 2)
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
		
		double datarate_factor = (num_runs * NUM_BYTES * 1000000.0) / (1024.0 * 1024.0);
		
		qsort (samples, num_samples, sizeof (uint64_t), compare);
		uint64_t median = get_median (num_samples, samples);
		printf ("min:    %" PRIu64 " µs %.3f MiB/s\n", samples[0], datarate_factor / samples[0]);
		printf ("median: %" PRIu64 " µs %.3f MiB/s\n", median, datarate_factor / median);
	}

	return 0;
}

