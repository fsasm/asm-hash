CC=gcc
CFLAGS=
INCLUDE_PATH=-I.

md5sum: md5.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o md5sum md5.c block.c int_util.c hashsum.c -DHASH_MD5 $(INCLUDE_PATH) $(CFLAGS)

sha1sum: sha1.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha1sum sha1.c block.c int_util.c hashsum.c -DHASH_SHA1 $(INCLUDE_PATH) $(CFLAGS)
	
sha224sum: sha224.c sha256.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha224sum sha224.c sha256.c block.c int_util.c hashsum.c -DHASH_SHA224 $(INCLUDE_PATH) $(CFLAGS)
	
sha256sum: sha256.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha256sum sha256.c block.c int_util.c hashsum.c -DHASH_SHA256 $(INCLUDE_PATH) $(CFLAGS)
	