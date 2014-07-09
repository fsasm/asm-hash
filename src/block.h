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

typedef void (*process_func)(const uint8_t buffer[], void* data, unsigned int n);

typedef struct {
	uint8_t* buffer;
	size_t size;
	size_t max_size;
	uint64_t full_size;
	process_func func;
	void* func_data;
} block;

void block_init (block* b, size_t max_size, uint8_t buffer[], process_func func, void* func_data);
void block_add (block* b, size_t size, const uint8_t data[]);

/* size in bits */
typedef enum {
	BLOCK_LENGTH_64,
	BLOCK_LENGTH_128,
	BLOCK_LENGTH_256
} block_length;

void block_util_finalize (block* b, bool little_endian, block_length length);

#endif