CC=gcc
CFLAGS=-I.

md5sum: md5.c block.c hashsum.c
	$(CC) -std=c99 -o md5sum.exe md5.c block.c int_util.c hashsum.c -DHASH_MD5
