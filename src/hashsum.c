
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

#include "sha224.h"
#define DIGEST_SIZE SHA224_DIGEST_SIZE
#define CONTEXT sha224_context
#define INIT sha224_init
#define UPDATE sha224_add
#define FINALIZE sha224_finalize
#define GET_DIGEST sha224_get_digest

#elif HASH_SHA384

#include "sha384.h"
#define DIGEST_SIZE SHA384_DIGEST_SIZE
#define CONTEXT sha384_context
#define INIT sha384_init
#define UPDATE sha384_update
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
