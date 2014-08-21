/*
 * block.h
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-17
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	BLOCK_SIZE_512,
	BLOCK_SIZE_1024
} block_size;

typedef enum {
	/* first three bits */
	BLOCK_LENGTH_64 = 0x00,
	BLOCK_LENGTH_128 = 0x01,
	BLOCK_LENGTH_256 = 0x02,
	
	BLOCK_LITTLE_ENDIAN = 0x08,
	BLOCK_BIG_ENDIAN = 0x00,
	
	BLOCK_SIMPLE_PADDING = 0x00,
	BLOCK_EXTENDED_PADDING = 0x10 /* adds 1 at the start and at the end of padding (blake256)*/
} block_flag;

struct block; 

typedef void (*process_func)(struct block* b, const uint8_t buffer[], unsigned int n, bool data_bits);

typedef struct block {
	uint8_t* buffer;
	block_size max_size;
	uint64_t full_size;
	process_func func;
	void* func_data;
} block;

void block_init (block* b, block_size max_size, uint8_t* buffer, process_func func, void* func_data);
void block_add (block* b, size_t size, const uint8_t data[]);

void block_util_finalize (block* b, block_flag flags);

#endif