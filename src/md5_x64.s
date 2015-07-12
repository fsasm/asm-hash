/*
 * md5_x64.s
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2014-12-31
 */

.intel_syntax noprefix

.section .rodata
.align 4
md5_table:
	.long 0xD76AA478
	.long 0xE8C7B756
	.long 0x242070DB
	.long 0xC1BDCEEE
	.long 0xF57C0FAF
	.long 0x4787C62A
	.long 0xA8304613
	.long 0xFD469501 /*  8 */
	.long 0x698098D8
	.long 0x8B44F7AF
	.long 0xFFFF5BB1
	.long 0x895CD7BE
	.long 0x6B901122
	.long 0xFD987193
	.long 0xA679438E
	.long 0x49B40821 /* 16 */
	.long 0xF61E2562
	.long 0xC040B340
	.long 0x265E5A51
	.long 0xE9B6C7AA
	.long 0xD62F105D
	.long 0x02441453
	.long 0xD8A1E681
	.long 0xE7D3FBC8 /* 24 */
	.long 0x21E1CDE6
	.long 0xC33707D6
	.long 0xF4D50D87
	.long 0x455A14ED
	.long 0xA9E3E905
	.long 0xFCEFA3F8
	.long 0x676F02D9
	.long 0x8D2A4C8A /* 32 */
	.long 0xFFFA3942
	.long 0x8771F681
	.long 0x6D9D6122
	.long 0xFDE5380C
	.long 0xA4BEEA44
	.long 0x4BDECFA9
	.long 0xF6BB4B60
	.long 0xBEBFBC70 /* 40 */
	.long 0x289B7EC6
	.long 0xEAA127FA
	.long 0xD4EF3085
	.long 0x04881D05
	.long 0xD9D4D039
	.long 0xE6DB99E5
	.long 0x1FA27CF8
	.long 0xC4AC5665 /* 48 */
	.long 0xF4292244
	.long 0x432AFF97
	.long 0xAB9423A7
	.long 0xFC93A039
	.long 0x655B59C3
	.long 0x8F0CCC92
	.long 0xFFEFF47D
	.long 0x85845DD1 /* 56 */
	.long 0x6FA87E4F
	.long 0xFE2CE6E0
	.long 0xA3014314
	.long 0x4E0811A1
	.long 0xF7537E82
	.long 0xBD3AF235
	.long 0x2AD7D2BB
	.long 0xEB86D391 /* 64 */

.section .text
.global md5_process_blocks_asm
.type md5_process_blocks_asm, %function
md5_process_blocks_asm: /* (uint8_t block[64], uint32_t hash[4], uint n) */
	/* block: rdi; hash: rsi; n: rdx*/
	push rbp
	mov rbp, rsp
	
	cmp rdx, 0
	je .Lend
	
	mov rcx, rdx

	/* A=eax, B=edx, C=r8d, D=r9d, f=r10d */
	mov eax, [rsi + 0]
	mov edx, [rsi + 4]
	mov r8d, [rsi + 8]
	mov r9d, [rsi + 12]

.Lstart:

/* first loop */
.macro round a, b, c, d, offset_block, offset_table, shift
	mov r10d, \c
	xor r10d, \d
	and r10d, \b
	xor r10d, \d /* f */
	add \a, r10d
	add \a, md5_table[\offset_table]
	add \a, [rdi + \offset_block]
	rol \a, \shift
	add \a, \b
.endm

	round eax, edx, r8d, r9d,  0,  0,  7
	round r9d, eax, edx, r8d,  4,  4, 12
	round r8d, r9d, eax, edx,  8,  8, 17
	round edx, r8d, r9d, eax, 12, 12, 22
	
	round eax, edx, r8d, r9d, 16, 16,  7
	round r9d, eax, edx, r8d, 20, 20, 12
	round r8d, r9d, eax, edx, 24, 24, 17
	round edx, r8d, r9d, eax, 28, 28, 22
	
	round eax, edx, r8d, r9d, 32, 32,  7
	round r9d, eax, edx, r8d, 36, 36, 12
	round r8d, r9d, eax, edx, 40, 40, 17
	round edx, r8d, r9d, eax, 44, 44, 22
	
	round eax, edx, r8d, r9d, 48, 48,  7
	round r9d, eax, edx, r8d, 52, 52, 12
	round r8d, r9d, eax, edx, 56, 56, 17
	round edx, r8d, r9d, eax, 60, 60, 22
	
/* second loop */
.purgem round
.macro round a, b, c, d, offset_block, offset_table, shift
	mov r10d, \d
	and r10d, \b
	mov r11d, \d
	not r11d
	and r11d, \c
	or  r10d, r11d /* f */
	add \a, r10d
	add \a, md5_table[\offset_table]
	add \a, [rdi + \offset_block]
	rol \a, \shift
	add \a, \b
.endm

	round eax, edx, r8d, r9d,  4,  64,  5
	round r9d, eax, edx, r8d, 24,  68,  9
	round r8d, r9d, eax, edx, 44,  72, 14
	round edx, r8d, r9d, eax,  0,  76, 20

	round eax, edx, r8d, r9d, 20,  80,  5
	round r9d, eax, edx, r8d, 40,  84,  9
	round r8d, r9d, eax, edx, 60,  88, 14
	round edx, r8d, r9d, eax, 16,  92, 20

	round eax, edx, r8d, r9d, 36,  96,  5
	round r9d, eax, edx, r8d, 56, 100,  9
	round r8d, r9d, eax, edx, 12, 104, 14
	round edx, r8d, r9d, eax, 32, 108, 20

	round eax, edx, r8d, r9d, 52, 112,  5
	round r9d, eax, edx, r8d,  8, 116,  9
	round r8d, r9d, eax, edx, 28, 120, 14
	round edx, r8d, r9d, eax, 48, 124, 20
	
/* third loop */
.purgem round
.macro round a, b, c, d, offset_block, offset_table, shift
	mov r10d, \b
	xor r10d, \c
	xor r10d, \d  /* f */
	add \a, r10d
	add \a, md5_table[\offset_table]
	add \a, [rdi + \offset_block]
	rol \a, \shift
	add \a, \b
.endm

	round eax, edx, r8d, r9d, 20, 128,  4
	round r9d, eax, edx, r8d, 32, 132, 11
	round r8d, r9d, eax, edx, 44, 136, 16
	round edx, r8d, r9d, eax, 56, 140, 23
	
	round eax, edx, r8d, r9d,  4, 144,  4
	round r9d, eax, edx, r8d, 16, 148, 11
	round r8d, r9d, eax, edx, 28, 152, 16
	round edx, r8d, r9d, eax, 40, 156, 23
	
	round eax, edx, r8d, r9d, 52, 160,  4
	round r9d, eax, edx, r8d,  0, 164, 11
	round r8d, r9d, eax, edx, 12, 168, 16
	round edx, r8d, r9d, eax, 24, 172, 23
	
	round eax, edx, r8d, r9d, 36, 176,  4
	round r9d, eax, edx, r8d, 48, 180, 11
	round r8d, r9d, eax, edx, 60, 184, 16
	round edx, r8d, r9d, eax,  8, 188, 23

/* fourth loop */
.purgem round
.macro round a, b, c, d, offset_block, offset_table, shift
	mov r10d, \d
	not r10d
	or  r10d, \b
	xor r10d, \c  /* f */
	add \a, r10d
	add \a, md5_table[\offset_table]
	add \a, [rdi + \offset_block]
	rol \a, \shift
	add \a, \b
.endm

	round eax, edx, r8d, r9d,  0, 192,  6
	round r9d, eax, edx, r8d, 28, 196, 10
	round r8d, r9d, eax, edx, 56, 200, 15
	round edx, r8d, r9d, eax, 20, 204, 21
	
	round eax, edx, r8d, r9d, 48, 208,  6
	round r9d, eax, edx, r8d, 12, 212, 10
	round r8d, r9d, eax, edx, 40, 216, 15
	round edx, r8d, r9d, eax,  4, 220, 21
	
	round eax, edx, r8d, r9d, 32, 224,  6
	round r9d, eax, edx, r8d, 60, 228, 10
	round r8d, r9d, eax, edx, 24, 232, 15
	round edx, r8d, r9d, eax, 52, 236, 21
	
	round eax, edx, r8d, r9d, 16, 240,  6
	round r9d, eax, edx, r8d, 44, 244, 10
	round r8d, r9d, eax, edx,  8, 248, 15
	round edx, r8d, r9d, eax, 36, 252, 21

	add eax, [rsi + 0]
	mov [rsi + 0], eax
	add edx, [rsi + 4]
	mov [rsi + 4], edx
	add r8d, [rsi + 8]
	mov [rsi + 8], r8d
	add r9d, [rsi + 12]
	mov [rsi + 12], r9d
	
	add rdi, 64
	sub rcx, 1
	jnz .Lstart
	
.Lend:
	leave
	ret
