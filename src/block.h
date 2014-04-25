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

typedef void (*process_func)(uint8_t buffer[], void* data);

typedef struct {
	uint8_t* buffer;
	size_t size;
	size_t max_size;
	uint64_t full_size;
	process_func func;
	void* func_data;
} block;

void block_init (block* b, size_t max_size, uint8_t buffer[], process_func func, void* func_data);
void block_add (block* b, size_t size, uint8_t data[]);

void block_util_finalize (block* b, bool little_endian, bool length_128);

#endif