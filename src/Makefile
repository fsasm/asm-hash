CC=gcc
CFLAGS=
INCLUDE_PATH=-I.

md5sum: md5.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o md5sum md5.c block.c int_util.c hashsum.c -DHASH_MD5 $(INCLUDE_PATH) $(CFLAGS)

md5sum_asm: md5.c md5_block.s block.c hashsum.c int_util.c
	$(CC) -std=c99 -o md5sum md5.c md5_block.s -DMD5_USE_ASM block.c int_util.c hashsum.c -DHASH_MD5 $(INCLUDE_PATH) $(CFLAGS)

sha1sum: sha1.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha1sum sha1.c block.c int_util.c hashsum.c -DHASH_SHA1 $(INCLUDE_PATH) $(CFLAGS)
	
sha1sum_asm: sha1.c sha1_block.s block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha1sum sha1.c sha1_block.s -DSHA1_USE_ASM block.c int_util.c hashsum.c -DHASH_SHA1 $(INCLUDE_PATH) $(CFLAGS)
	
sha224sum: sha256.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha224sum sha256.c block.c int_util.c hashsum.c -DHASH_SHA224 $(INCLUDE_PATH) $(CFLAGS)
	
sha256sum: sha256.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha256sum sha256.c block.c int_util.c hashsum.c -DHASH_SHA256 $(INCLUDE_PATH) $(CFLAGS)

sha384sum: sha512.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha384sum sha512.c block.c int_util.c hashsum.c -DHASH_SHA384 $(INCLUDE_PATH) $(CFLAGS)

sha512sum: sha512.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha512sum sha512.c block.c int_util.c hashsum.c -DHASH_SHA512 $(INCLUDE_PATH) $(CFLAGS)

sha512_224sum: sha512.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha512_224sum sha512.c block.c int_util.c hashsum.c -DHASH_SHA512_224 $(INCLUDE_PATH) $(CFLAGS)

sha512_256sum: sha512.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o sha512_256sum sha512.c block.c int_util.c hashsum.c -DHASH_SHA512_256 $(INCLUDE_PATH) $(CFLAGS)

whirlpoolsum: whirlpool.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o whirlpoolsum whirlpool.c block.c int_util.c hashsum.c -DHASH_WHIRLPOOL $(INCLUDE_PATH) $(CFLAGS)

blake256sum: blake.c block.c hashsum.c int_util.c
	$(CC) -std=c99 -o blake256sum blake.c block.c int_util.c hashsum.c -DHASH_BLAKE256 $(INCLUDE_PATH) $(CFLAGS)
	