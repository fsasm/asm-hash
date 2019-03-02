CC=gcc
CFLAGS=
INCLUDE_PATH=-I.

.PHONY: all clean all_c all_armv6 all_armv7 all_x64 test


all: all_c all_armv6 all_armv7 all_x64

clean:
	rm -rf md5sum sha1sum sha224sum sha256sum sha384sum sha512sum sha512_224sum sha512_256sum blake224sum blake256sum blake384sum blake512sum groestl224sum groestl256sum groestl384sum groestl512sum whirlpoolsum whirlpoolsum_x64
	rm -rf md5sum.exe sha1sum.exe sha224sum.exe sha256sum.exe sha384sum.exe sha512sum.exe sha512_224sum.exe sha512_256sum.exe blake224sum.exe blake256sum.exe blake384sum.exe blake512sum.exe groestl224sum.exe groestl256sum.exe groestl384sum.exe groestl512sum.exe whirlpoolsum.exe whirlpoolsum_x64.exe

TEST_FLAGS=-I. `pkg-config --cflags --libs cmocka `
int_util_test: test/int_util_test.c int_util.c
	$(CC) -std=c99 -o $@ $^ $(TEST_FLAGS)

test: int_util_test
	./int_util_test

# C versions
all_c: md5sum sha1sum sha2 whirlpoolsum blake groestl

sha2: sha224sum sha256sum sha384sum sha512sum sha512_224sum sha512_256sum

blake: blake224sum blake256sum blake384sum blake512sum

groestl: groestl224sum groestl256sum groestl384sum groestl512sum

# Assembly versions
all_x64: md5sum_x64

all_armv6: md5sum_armv6 sha1sum_armv6 sha2_armv6 blake_armv6

all_armv7: md5sum_armv7 sha1sum_armv7

sha2_armv6: sha224sum_armv6 sha256sum_armv6 sha384sum_armv6 sha512sum_armv6 sha512_224sum_armv6 sha512_256sum_armv6

blake_armv6: blake224sum_armv6 blake256sum_armv6 blake384sum_armv6 blake512sum_armv6

# MD5
md5sum:
	$(CC) -std=c99 -DHASH_MD5 -o $@  md5.c md5_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

md5sum_x64:
	$(CC) -std=c99 -DHASH_MD5 -DMD5_USE_ASM -o $@  md5.c md5_core.c md5_x64.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

md5sum_armv6:
	$(CC) -std=c99 -DHASH_MD5 -DMD5_USE_ASM -o $@  md5.c md5_core.c md5_armv6.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

md5sum_armv7:
	$(CC) -std=c99 -DHASH_MD5 -DMD5_USE_ASM -o $@  md5.c md5_core.c md5_armv7.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

# SHA-1
sha1sum:
	$(CC) -std=c99 -DHASH_SHA1 -o $@ sha1.c sha1_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)
	
sha1sum_armv6: 
	$(CC) -std=c99 -DHASH_SHA1 -DSHA1_USE_ASM -o $@ sha1.c sha1_core.c sha1_armv6.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)
	
sha1sum_armv7: 
	$(CC) -std=c99 -DHASH_SHA1 -DSHA1_USE_ASM -o $@ sha1.c sha1_core.c sha1_armv7.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)
	
# SHA-2
sha224sum:
	$(CC) -std=c99 -DHASH_SHA224 -o $@ sha256.c sha256_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)
	
sha224sum_armv6:
	$(CC) -std=c99 -DHASH_SHA224 -DSHA256_USE_ASM -o $@ sha256.c sha256_core.c sha256_armv6.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

sha256sum:
	$(CC) -std=c99 -DHASH_SHA256 -o $@ sha256.c sha256_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

sha256sum_armv6:
	$(CC) -std=c99 -DHASH_SHA256 -DSHA256_USE_ASM -o $@ sha256.c sha256_core.c sha256_armv6.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

sha384sum:
	$(CC) -std=c99 -DHASH_SHA384 -o $@ sha512.c sha512_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

sha384sum_armv6:
	$(CC) -std=c99 -DHASH_SHA384 -DSHA512_USE_ASM -o $@ sha512.c sha512_core.c sha512_armv6.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

sha512sum:
	$(CC) -std=c99 -DHASH_SHA512 -o $@ sha512.c sha512_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

sha512sum_armv6:
	$(CC) -std=c99 -DHASH_SHA512 -DSHA512_USE_ASM -o $@ sha512.c sha512_core.c sha512_armv6.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

sha512_224sum:
	$(CC) -std=c99 -DHASH_SHA512_224 -o $@ sha512.c sha512_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

sha512_224sum_armv6:
	$(CC) -std=c99 -DHASH_SHA512_224 -DSHA512_USE_ASM -o $@ sha512.c sha512_core.c sha512_armv6.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

sha512_256sum:
	$(CC) -std=c99 -DHASH_SHA512_256 -o $@ sha512.c sha512_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

sha512_256sum_armv6:
	$(CC) -std=c99 -DHASH_SHA512_256 -DSHA512_USE_ASM -o $@ sha512.c sha512_core.c sha512_armv6.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

# Whirlpool
whirlpoolsum:
	$(CC) -std=c99 -DHASH_WHIRLPOOL -o $@ whirlpool.c whirlpool_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

whirlpoolsum_single:
	$(CC) -std=c99 -DHASH_WHIRLPOOL -DWHIRLPOOL_SINGLE_TABLE -o $@ whirlpool.c whirlpool_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

whirlpoolsum_naive:
	$(CC) -std=c99 -DHASH_WHIRLPOOL -DWHIRLPOOL_NAIVE -o $@ whirlpool.c whirlpool_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

whirlpoolsum_x64:
	$(CC) -std=c99 -DHASH_WHIRLPOOL -DWHIRLPOOL_USE_ASM -o $@ whirlpool.c whirlpool_core.c whirlpool_x64.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

whirlpoolsum_single_x64:
	$(CC) -std=c99 -DHASH_WHIRLPOOL -DWHIRLPOOL_USE_ASM -o $@ whirlpool.c whirlpool_core.c whirlpool_single_x64.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

whirlpool_ctable_gen:
	$(CC) -std=c99 -o $@ whirlpool_table_gen.c int_util.c $(INCLUDE_PATH) $(CLFAGS) 

whirlpool_asm32_table_gen:
	$(CC) -std=c99 -DWHIRLPOOL_ASM_TABLES_32 -o $@ whirlpool_table_gen.c int_util.c $(INCLUDE_PATH) $(CLFAGS) 

whirlpool_asm64_table_gen:
	$(CC) -std=c99 -DWHIRLPOOL_ASM_TABLES_64 -o $@ whirlpool_table_gen.c int_util.c $(INCLUDE_PATH) $(CLFAGS) 

# BLAKE
blake224sum:
	$(CC) -std=c99 -DHASH_BLAKE224 -o $@ blake256.c blake256_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

blake224sum_armv6:
	$(CC) -std=c99 -DHASH_BLAKE224 -DBLAKE256_USE_ASM -o $@ blake256.c blake256_core.c blake256_armv6.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

blake256sum:
	$(CC) -std=c99 -DHASH_BLAKE256 -o $@ blake256.c blake256_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

blake256sum_armv6:
	$(CC) -std=c99 -DHASH_BLAKE256 -DBLAKE256_USE_ASM -o $@ blake256.c blake256_core.c blake256_armv6.s block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

blake512sum:
	$(CC) -std=c99 -DHASH_BLAKE512 -o $@ blake512.c blake512_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

blake512sum_armv6:
	$(CC) -std=c99 -DHASH_BLAKE512 -DBLAKE512_USE_ASM -o $@ blake512.c blake512_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

blake384sum:
	$(CC) -std=c99 -DHASH_BLAKE384 -o $@ blake512.c blake512_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

blake384sum_armv6:
	$(CC) -std=c99 -DHASH_BLAKE384 -DBLAKE512_USE_ASM -o $@ blake512.c blake512_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

# Groestl
groestl256sum:
	$(CC) -std=c99 -DHASH_GROESTL256 -o $@ groestl256.c groestl256_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

groestl224sum:
	$(CC) -std=c99 -DHASH_GROESTL224 -o $@ groestl256.c groestl256_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

groestl512sum:
	$(CC) -std=c99 -DHASH_GROESTL512 -o $@ groestl512.c groestl512_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

groestl384sum:
	$(CC) -std=c99 -DHASH_GROESTL384 -o $@ groestl512.c groestl512_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

# JH	
jh256sum: 
	$(CC) -std=c99 -DHASH_JH256 -o $@ jh.c jh_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

jh224sum:
	$(CC) -std=c99 -DHASH_JH224 -o $@ jh.c jh_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

jh512sum:
	$(CC) -std=c99 -DHASH_JH512 -o $@ jh.c jh_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

jh384sum:
	$(CC) -std=c99 -DHASH_JH384 -o $@ jh.c jh_core.c block.c int_util.c hashsum.c $(INCLUDE_PATH) $(CFLAGS)

