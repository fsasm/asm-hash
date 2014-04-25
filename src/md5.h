/*
 * md5_2.h
 * Author Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-04-04
 */

#ifndef MD5_H
#define MD5_H

#include <stdint.h>
#include "block.h"

#define MD5_DIGEST_SIZE 16

typedef struct {
	uint8_t buffer[64];
	uint32_t hash[4];
	block b;
} md5_context;

void md5_init (md5_context* ctxt);
void md5_update (md5_context* ctxt, uint8_t data[], uint64_t length);
void md5_finalize (md5_context* ctxt);
void md5_get_digest (md5_context* ctxt, uint8_t digest[MD5_DIGEST_SIZE]);

void md5_process_block (uint8_t block[64], uint32_t hash[4]);

#endif
