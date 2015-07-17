CC=gcc
CFLAGS=
INCLUDE_PATH=-I../src/

md5_test_armv6:
	$(CC) -std=c99 -DHASH_MD5 -o $@ hash_test.c ../src/md5_core.c ../src/md5_armv6.s ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)
	
md5_test_armv7:
	$(CC) -std=c99 -DHASH_MD5 -o $@ hash_test.c ../src/md5_core.c ../src/md5_armv7.s ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

md5_test_x64:
	$(CC) -std=c99 -DHASH_MD5 -o $@ hash_test.c ../src/md5_core.c ../src/md5_x64.s ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)
	
sha1_test_armv6:
	$(CC) -std=c99 -DHASH_SHA1 -o $@ hash_test.c ../src/sha1_core.c ../src/sha1_armv6.s ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

sha1_test_armv7:
	$(CC) -std=c99 -DHASH_SHA1 -o $@ hash_test.c ../src/sha1_core.c ../src/sha1_armv7.s ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

sha256_test_armv6:
	$(CC) -std=c99 -DHASH_SHA256 -o $@ hash_test.c ../src/sha256_core.c ../src/sha256_armv6.s ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

sha512_test_armv6:
	$(CC) -std=c99 -DHASH_SHA512 -o $@ hash_test.c ../src/sha512_core.c ../src/sha512_armv6.s ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

blake256_test:
	$(CC) -std=c99 -DHASH_BLAKE256 -o $@ hash_test.c ../src/blake256_core.c ../src/blake256_armv6.s ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

blake512_test:
	$(CC) -std=c99 -o blake512_test hash_test.c -DHASH_BLAKE512 ../src/blake512.c ../src/blake512_armv6.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

int_util_test: int_util_test.c
	$(CC) -std=c99 -o int_util_test int_util_test.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

md5_bench:
	$(CC) -std=gnu99 -DHASH_MD5 -lrt -o $@ hash_benchmark.c ../src/md5_core.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

md5_bench_armv6:
	$(CC) -std=gnu99 -DHASH_MD5_ASM -lrt -o $@ hash_benchmark.c ../src/md5_core.c ../src/md5_armv6.s ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

md5_bench_armv7:
	$(CC) -std=gnu99 -march=armv7-a -DHASH_MD5_ASM -lrt -o $@ hash_benchmark.c ../src/md5_core.c ../src/md5_armv7.s ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

md5_bench_x64:
	$(CC) -std=gnu99 -DHASH_MD5_ASM -lrt -o $@ hash_benchmark.c ../src/md5_core.c ../src/md5_x64.s ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

sha1_bench:
	$(CC) -std=gnu99 -DHASH_SHA1 -lrt -o $@ hash_benchmark.c ../src/sha1_core.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

sha1_bench_armv6:
	$(CC) -std=gnu99 -DHASH_SHA1_ASM -lrt -o $@ hash_benchmark.c ../src/sha1_core.c ../src/sha1_armv6.s ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

sha1_bench_armv7:
	$(CC) -std=gnu99 -DHASH_SHA1_ASM -lrt -o $@ hash_benchmark.c ../src/sha1_core.c ../src/sha1_armv7.s ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

sha256_bench:
	$(CC) -std=gnu99 -DHASH_SHA256 -lrt -o $@ hash_benchmark.c ../src/sha256_core.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

sha256_bench_armv6:
	$(CC) -std=gnu99 -DHASH_SHA256_ASM -lrt -o $@ hash_benchmark.c ../src/sha256_core.c ../src/sha256_armv6.s ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

sha512_bench:
	$(CC) -std=gnu99 -DHASH_SHA512 -lrt -o $@ hash_benchmark.c ../src/sha512_core.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

sha512_bench_armv6:
	$(CC) -std=gnu99 -DHASH_SHA512_ASM -lrt -o $@ hash_benchmark.c ../src/sha512_core.c ../src/sha512_armv6.s ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

blake256_bench:
	$(CC) -std=gnu99 -DHASH_BLAKE256 -lrt -o $@ hash_benchmark.c ../src/blake256_core.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

blake256_bench_armv6:
	$(CC) -std=gnu99 -DHASH_BLAKE256_ASM -lrt -o $@ hash_benchmark.c ../src/blake256_core.c ../src/blake256_armv6.s ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

blake512_bench:
	$(CC) -std=gnu99 -DHASH_BLAKE512 -lrt -o $@ hash_benchmark.c ../src/blake512_core.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

blake512_bench_armv6:
	$(CC) -std=gnu99 -DHASH_BLAKE512_ASM -lrt -o $@ hash_benchmark.c ../src/blake512_core.c ../src/blake512_armv6.s ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

whirlpool_test_single_x64:
	$(CC) -std=c99 -DHASH_WHIRLPOOL -o $@ hash_test.c ../src/whirlpool_core.c ../src/whirlpool_single_x64.s ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

whirlpool_bench:
	$(CC) -std=gnu99 -DHASH_WHIRLPOOL -lrt -o $@ hash_benchmark.c ../src/whirlpool_core.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

whirlpool_bench_single:
	$(CC) -std=gnu99 -DHASH_WHIRLPOOL -DWHIRLPOOL_SINGLE_TABLE -lrt -o $@ hash_benchmark.c ../src/whirlpool_core.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

whirlpool_bench_naive:
	$(CC) -std=gnu99 -DHASH_WHIRLPOOL -DWHIRLPOOL_NAIVE -lrt -o $@ hash_benchmark.c ../src/whirlpool_core.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

whirlpool_bench_single_x64:
	$(CC) -std=gnu99 -DHASH_WHIRLPOOL_ASM -lrt -o $@ hash_benchmark.c ../src/whirlpool_core.c ../src/whirlpool_single_x64.s ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)
