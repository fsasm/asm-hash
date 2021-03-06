
#ifdef HASH_SHA1

#include "sha1.h"
#define DIGEST_SIZE SHA1_DIGEST_SIZE
#define CONTEXT sha1_context
#define INIT sha1_init
#define UPDATE sha1_add
#define FINALIZE sha1_finalize
#define GET_DIGEST sha1_get_digest

#elif HASH_MD5

#include "md5.h"
#define DIGEST_SIZE MD5_DIGEST_SIZE
#define CONTEXT md5_context
#define INIT md5_init
#define UPDATE md5_add
#define FINALIZE md5_finalize
#define GET_DIGEST md5_get_digest

#elif HASH_SHA256

#include "sha256.h"
#define DIGEST_SIZE SHA256_DIGEST_SIZE
#define CONTEXT sha256_context
#define INIT sha256_init
#define UPDATE sha256_add
#define FINALIZE sha256_finalize
#define GET_DIGEST sha256_get_digest

#elif HASH_SHA224

#include "sha256.h"
#define DIGEST_SIZE SHA224_DIGEST_SIZE
#define CONTEXT sha224_context
#define INIT sha224_init
#define UPDATE sha224_add
#define FINALIZE sha224_finalize
#define GET_DIGEST sha224_get_digest

#elif HASH_SHA384

#include "sha512.h"
#define DIGEST_SIZE SHA384_DIGEST_SIZE
#define CONTEXT sha384_context
#define INIT sha384_init
#define UPDATE sha384_add
#define FINALIZE sha384_finalize
#define GET_DIGEST sha384_get_digest

#elif HASH_SHA512

#include "sha512.h"
#define DIGEST_SIZE SHA512_DIGEST_SIZE
#define CONTEXT sha512_context
#define INIT sha512_init
#define UPDATE sha512_add
#define FINALIZE sha512_finalize
#define GET_DIGEST sha512_get_digest

#elif HASH_SHA512_224

#include "sha512.h"
#define DIGEST_SIZE SHA512_224_DIGEST_SIZE
#define CONTEXT sha512_context
#define INIT sha512_224_init
#define UPDATE sha512_add
#define FINALIZE sha512_finalize
#define GET_DIGEST sha512_224_get_digest

#elif HASH_SHA512_256

#include "sha512.h"
#define DIGEST_SIZE SHA512_256_DIGEST_SIZE
#define CONTEXT sha512_context
#define INIT sha512_256_init
#define UPDATE sha512_add
#define FINALIZE sha512_finalize
#define GET_DIGEST sha512_256_get_digest

#elif HASH_WHIRLPOOL

#include "whirlpool.h"
#define DIGEST_SIZE WHIRLPOOL_DIGEST_SIZE
#define CONTEXT whirlpool_context
#define INIT whirlpool_init
#define UPDATE whirlpool_add
#define FINALIZE whirlpool_finalize
#define GET_DIGEST whirlpool_get_digest

#elif HASH_BLAKE256

#include "blake256.h"
#define DIGEST_SIZE BLAKE256_DIGEST_SIZE
#define CONTEXT blake256_context
#define INIT blake256_init
#define UPDATE blake256_add
#define FINALIZE blake256_finalize
#define GET_DIGEST blake256_get_digest

#elif HASH_BLAKE224

#include "blake256.h"
#define DIGEST_SIZE BLAKE224_DIGEST_SIZE
#define CONTEXT blake224_context
#define INIT blake224_init
#define UPDATE blake224_add
#define FINALIZE blake224_finalize
#define GET_DIGEST blake224_get_digest

#elif HASH_BLAKE512

#include "blake512.h"
#define DIGEST_SIZE BLAKE512_DIGEST_SIZE
#define CONTEXT blake512_context
#define INIT blake512_init
#define UPDATE blake512_add
#define FINALIZE blake512_finalize
#define GET_DIGEST blake512_get_digest

#elif HASH_BLAKE384

#include "blake512.h"
#define DIGEST_SIZE BLAKE384_DIGEST_SIZE
#define CONTEXT blake384_context
#define INIT blake384_init
#define UPDATE blake384_add
#define FINALIZE blake384_finalize
#define GET_DIGEST blake384_get_digest

#elif HASH_GROESTL256

#include "groestl256.h"
#define DIGEST_SIZE GROESTL256_DIGEST_SIZE
#define CONTEXT groestl256_context
#define INIT groestl256_init
#define UPDATE groestl256_add
#define FINALIZE groestl256_finalize
#define GET_DIGEST groestl256_get_digest

#elif HASH_GROESTL224

#include "groestl256.h"
#define DIGEST_SIZE GROESTL224_DIGEST_SIZE
#define CONTEXT groestl224_context
#define INIT groestl224_init
#define UPDATE groestl224_add
#define FINALIZE groestl224_finalize
#define GET_DIGEST groestl224_get_digest

#elif HASH_GROESTL512

#include "groestl512.h"
#define DIGEST_SIZE GROESTL512_DIGEST_SIZE
#define CONTEXT groestl512_context
#define INIT groestl512_init
#define UPDATE groestl512_add
#define FINALIZE groestl512_finalize
#define GET_DIGEST groestl512_get_digest

#elif HASH_GROESTL384

#include "groestl512.h"
#define DIGEST_SIZE GROESTL384_DIGEST_SIZE
#define CONTEXT groestl384_context
#define INIT groestl384_init
#define UPDATE groestl384_add
#define FINALIZE groestl384_finalize
#define GET_DIGEST groestl384_get_digest

#elif HASH_JH256

#include "jh.h"
#define DIGEST_SIZE JH256_DIGEST_SIZE
#define CONTEXT jh256_context
#define INIT jh256_init
#define UPDATE jh256_add
#define FINALIZE jh256_finalize
#define GET_DIGEST jh256_get_digest

#elif HASH_JH224

#include "jh.h"
#define DIGEST_SIZE JH224_DIGEST_SIZE
#define CONTEXT jh224_context
#define INIT jh224_init
#define UPDATE jh224_add
#define FINALIZE jh224_finalize
#define GET_DIGEST jh224_get_digest

#elif HASH_JH384

#include "jh.h"
#define DIGEST_SIZE JH384_DIGEST_SIZE
#define CONTEXT jh384_context
#define INIT jh384_init
#define UPDATE jh384_add
#define FINALIZE jh384_finalize
#define GET_DIGEST jh384_get_digest

#elif HASH_JH512

#include "jh.h"
#define DIGEST_SIZE JH512_DIGEST_SIZE
#define CONTEXT jh512_context
#define INIT jh512_init
#define UPDATE jh512_add
#define FINALIZE jh512_finalize
#define GET_DIGEST jh512_get_digest

#endif

#define BUFFER_SIZE 4096

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
	CONTEXT ctxt;
	uint8_t result[DIGEST_SIZE];
	uint8_t buffer[BUFFER_SIZE];

	if (argc < 2) {
		fprintf (stderr, "Usage: %s FILE\n", argv[0]);
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		FILE* f = fopen (argv[i], "rb");
		if (f == NULL) {
			fprintf (stderr, "Couldn't open file\n");
			return 1;
		}

		INIT (&ctxt);

		int length = 0;
		do {
			length = fread (buffer, 1, BUFFER_SIZE, f);
			UPDATE (&ctxt, buffer, length);
		} while (length > 0);

		FINALIZE (&ctxt);
		GET_DIGEST (&ctxt, result);

		fclose (f);

		for (int j = 0; j < DIGEST_SIZE; j++)
			printf("%2.2x", result[j]);
		printf ("  %s\n", argv[i]);
	}
	return 0;
}
