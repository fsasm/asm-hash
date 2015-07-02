CC=gcc
CFLAGS=
INCLUDE_PATH=-I../src/

md5_test_armv6: hash_test.c
	$(CC) -std=c99 -o md5_test_armv6 hash_test.c -DHASH_MD5 ../src/md5.c ../src/md5_armv6.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)
	
md5_test_armv7: hash_test.c
	$(CC) -std=c99 -march=armv7-a -o md5_test_armv7 hash_test.c -DHASH_MD5 ../src/md5.c ../src/md5_armv7.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

md5_test_x64: hash_test.c
	$(CC) -std=c99 -o md5_test_x64 hash_test.c -DHASH_MD5 ../src/md5.c ../src/md5_x64.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)
	
sha1_test_armv6: hash_test.c
	$(CC) -std=c99 -o sha1_test_armv6 hash_test.c -DHASH_SHA1 ../src/sha1.c ../src/sha1_armv6.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

sha1_test_armv7: hash_test.c
	$(CC) -std=c99 -march=armv7-a -o sha1_test_armv7 hash_test.c -DHASH_SHA1 ../src/sha1.c ../src/sha1_armv7.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

sha256_test: hash_test.c
	$(CC) -std=c99 -o sha256_test hash_test.c -DHASH_SHA256 ../src/sha256.c ../src/sha256_armv6.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

sha512_test: hash_test.c
	$(CC) -std=c99 -o sha512_test hash_test.c -DHASH_SHA512 ../src/sha512.c ../src/sha512_armv6.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

blake256_test: hash_test.c
	$(CC) -std=c99 -o blake256_test hash_test.c -DHASH_BLAKE256 ../src/blake256.c ../src/blake256_armv6.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

blake512_test: hash_test.c
	$(CC) -std=c99 -o blake512_test hash_test.c -DHASH_BLAKE512 ../src/blake512.c ../src/blake512_armv6.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

int_util_test: int_util_test.c
	$(CC) -std=c99 -o int_util_test int_util_test.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

md5_bench: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o md5_bench hash_benchmark.c -DHASH_MD5 ../src/md5.c ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

md5_bench_armv6: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o md5_bench_armv6 hash_benchmark.c -DHASH_MD5_ASM ../src/md5.c ../src/md5_armv6.s ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

md5_bench_armv7: hash_benchmark.c
	$(CC) -std=gnu99 -march=armv7-a -lrt -o md5_bench_armv7 hash_benchmark.c -DHASH_MD5_ASM ../src/md5.c ../src/md5_armv7.s ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

md5_bench_x64: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o md5_bench_x64 hash_benchmark.c -DHASH_MD5_ASM ../src/md5.c ../src/md5_x64.s ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

sha1_bench: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o sha1_bench hash_benchmark.c -DHASH_SHA1 ../src/sha1.c ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

sha1_bench_armv6: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o sha1_bench_armv6 hash_benchmark.c -DHASH_SHA1_ASM ../src/sha1.c ../src/sha1_armv6.s ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

sha1_bench_armv7: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o sha1_bench_armv7 hash_benchmark.c -DHASH_SHA1_ASM ../src/sha1.c ../src/sha1_armv7.s ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)

sha256_bench: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o sha256_bench hash_benchmark.c -DHASH_SHA256 ../src/sha256.c ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

sha256_bench_armv6: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o sha256_bench_armv6 hash_benchmark.c -DHASH_SHA256_ASM ../src/sha256.c ../src/sha256_armv6.s ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

sha512_bench: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o sha512_bench hash_benchmark.c -DHASH_SHA512 ../src/sha512.c ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

sha512_bench_armv6: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o sha512_bench_armv6 hash_benchmark.c -DHASH_SHA512_ASM ../src/sha512.c ../src/sha512_armv6.s ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

blake256_bench: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o blake256_bench hash_benchmark.c -DHASH_BLAKE256 ../src/blake256.c ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

blake256_bench_armv6: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o blake256_bench_armv6 hash_benchmark.c -DHASH_BLAKE256_ASM ../src/blake256.c ../src/blake256_armv6.s ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

blake512_bench: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o blake512_bench hash_benchmark.c -DHASH_BLAKE512 ../src/blake512.c ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

blake512_bench_armv6: hash_benchmark.c
	$(CC) -std=gnu99 -lrt -o blake512_bench_armv6 hash_benchmark.c -DHASH_BLAKE512_ASM ../src/blake512.c ../src/blake512_armv6.s ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH) 

whirlpool_test_x64: hash_test.c
	$(CC) -std=c99 -o whirlpool_test_x64 hash_test.c -DHASH_WHIRLPOOL ../src/whirlpool.c ../src/whirlpool_x64.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)
