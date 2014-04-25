CC=gcc
CFLAGS=-I../src/

md5_test: md5_test.c
	$(CC) -std=c99 -o md5_test md5_test.c ../src/md5.c ../src/md5_block.s ../src/block.c $(CFLAGS)
