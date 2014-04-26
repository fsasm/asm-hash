CC=gcc
CFLAGS=-I.

md5sum: md5.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o md5sum md5.c block.c int_util.c hashsum.c -DHASH_MD5 $(CFLAGS)

sha1sum: sha1.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha1sum sha1.c block.c int_util.c hashsum.c -DHASH_SHA1 $(CFLAGS)