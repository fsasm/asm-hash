CC=gcc
CFLAGS=
INCLUDE_PATH=-I../src/

md5_test: md5_test.c
	$(CC) -std=c99 -o md5_test md5_test.c ../src/md5.c ../src/md5_block.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

sha1_test: sha1_test.c
	$(CC) -std=c99 -o sha1_test sha1_test.c ../src/sha1.c ../src/sha1_block.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

sha256_test: sha256_test.c
	$(CC) -std=c99 -o sha256_test sha256_test.c ../src/sha256.c ../src/sha256_block.s ../src/block.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

int_util_test: int_util_test.c
	$(CC) -std=c99 -o int_util_test int_util_test.c ../src/int_util.c $(INCLUDE_PATH) $(CFLAGS)

md5_bench: md5_bench.c
	$(CC) -std=gnu99 -lrt -o md5_bench md5_bench.c ../src/md5.c ../src/md5_block.s ../src/block.c ../src/int_util.c $(CFLAGS) $(INCLUDE_PATH)
