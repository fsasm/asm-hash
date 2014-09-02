/*
 * md5_block.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-03-28
 */

/* optimized for a ARM1176 as found on an Raspberry Pi */
.arch armv6

.section .rodata
.align 4
md5_table:
	.word 0xD76AA478
	.word 0xE8C7B756
	.word 0x242070DB
	.word 0xC1BDCEEE
	.word 0xF57C0FAF
	.word 0x4787C62A
	.word 0xA8304613
	.word 0xFD469501 /*  8 */
	.word 0x698098D8
	.word 0x8B44F7AF
	.word 0xFFFF5BB1
	.word 0x895CD7BE
	.word 0x6B901122
	.word 0xFD987193
	.word 0xA679438E
	.word 0x49B40821 /* 16 */
	.word 0xF61E2562
	.word 0xC040B340
	.word 0x265E5A51
	.word 0xE9B6C7AA
	.word 0xD62F105D
	.word 0x02441453
	.word 0xD8A1E681
	.word 0xE7D3FBC8 /* 24 */
	.word 0x21E1CDE6
	.word 0xC33707D6
	.word 0xF4D50D87
	.word 0x455A14ED
	.word 0xA9E3E905
	.word 0xFCEFA3F8
	.word 0x676F02D9
	.word 0x8D2A4C8A /* 32 */
	.word 0xFFFA3942
	.word 0x8771F681
	.word 0x6D9D6122
	.word 0xFDE5380C
	.word 0xA4BEEA44
	.word 0x4BDECFA9
	.word 0xF6BB4B60
	.word 0xBEBFBC70 /* 40 */
	.word 0x289B7EC6
	.word 0xEAA127FA
	.word 0xD4EF3085
	.word 0x04881D05
	.word 0xD9D4D039
	.word 0xE6DB99E5
	.word 0x1FA27CF8
	.word 0xC4AC5665 /* 48 */
	.word 0xF4292244
	.word 0x432AFF97
	.word 0xAB9423A7
	.word 0xFC93A039
	.word 0x655B59C3
	.word 0x8F0CCC92
	.word 0xFFEFF47D
	.word 0x85845DD1 /* 56 */
	.word 0x6FA87E4F
	.word 0xFE2CE6E0
	.word 0xA3014314
	.word 0x4E0811A1
	.word 0xF7537E82
	.word 0xBD3AF235
	.word 0x2AD7D2BB
	.word 0xEB86D391 /* 64 */

.text
.arm
.global md5_process_blocks_asm
md5_process_blocks_asm: /* (uint8_t block[64], uint32_t hash[4], uint n) */
	push {r4 - r11}
	cmp r2, #0
	beq .Lend
	
	ldr r3, addr_table
	/* r4 = h0; r5 = h1; r6 = h2; r7 = h3 */
	ldmia  r1, {r4, r5, r6, r7}
	
.Lstart:
	
.macro round a, b, c, d, offset_block, offset_table, shift
	ldr r10, [r0, +#\offset_block]
	ldr r11, [r3, +#\offset_table]
	add \b, \c, \b, ROR #\shift
	bic r9, \d, \b
	and r8, \b, \c
	orr r8, r8, r9
	add \a, \a, r8
	add r10, r10, r11
	add \a, \a, r10
.endm

	/* first loop */
	ldr r10, [r0, +#0]
	ldr r11, [r3, +#0]
	bic r9, r7, r5
	and r8, r5, r6
	orr r8, r8, r9
	add r4, r4, r8
	add r10, r10, r11
	add r4, r4, r10

	round r7, r4, r5, r6,  4,   4, 25
	round r6, r7, r4, r5,  8,   8, 20
	round r5, r6, r7, r4, 12,  12, 15
	
	round r4, r5, r6, r7, 16,  16, 10
	round r7, r4, r5, r6, 20,  20, 25
	round r6, r7, r4, r5, 24,  24, 20
	round r5, r6, r7, r4, 28,  28, 15
	
	round r4, r5, r6, r7, 32,  32, 10
	round r7, r4, r5, r6, 36,  36, 25
	round r6, r7, r4, r5, 40,  40, 20
	round r5, r6, r7, r4, 44,  44, 15

	round r4, r5, r6, r7, 48,  48, 10
	round r7, r4, r5, r6, 52,  52, 25
	round r6, r7, r4, r5, 56,  56, 20
	round r5, r6, r7, r4, 60,  60, 15
	
	/* second loop */
.purgem round
.macro round a, b, c, d, offset_block, offset_table, shift
	ldr r10, [r0, +#\offset_block]
	ldr r11, [r3, +#\offset_table]
	add \b, \c, \b, ROR #\shift
	bic r9, \c, \d
	and r8, \d, \b
	orr r8, r8, r9
	add r10, r10, r11
	add \a, \a, r8
	add \a, \a, r10
.endm

	round r4, r5, r6, r7,  4,  64, 10
	round r7, r4, r5, r6, 24,  68, 27
	round r6, r7, r4, r5, 44,  72, 23
	round r5, r6, r7, r4,  0,  76, 18
	
	round r4, r5, r6, r7, 20,  80, 12
	round r7, r4, r5, r6, 40,  84, 27
	round r6, r7, r4, r5, 60,  88, 23
	round r5, r6, r7, r4, 16,  92, 18
	
	round r4, r5, r6, r7, 36,  96, 12
	round r7, r4, r5, r6, 56, 100, 27
	round r6, r7, r4, r5, 12, 104, 23
	round r5, r6, r7, r4, 32, 108, 18

	round r4, r5, r6, r7, 52, 112, 12
	round r7, r4, r5, r6,  8, 116, 27
	round r6, r7, r4, r5, 28, 120, 23
	round r5, r6, r7, r4, 48, 124, 18

	/* third loop */
.purgem round
.macro round a, b, c, d, offset_block, offset_table, shift
	ldr r10, [r0, +#\offset_block]
	ldr r11, [r3, +#\offset_table]
	add \b, \c, \b, ROR #\shift
	eor r8, \d, \c
	eor r8, r8, \b
	add \a, \a, r8
	add r10, r10, r11
	add \a, \a, r10
.endm

	round r4, r5, r6, r7, 20, 128, 12
	round r7, r4, r5, r6, 32, 132, 28
	round r6, r7, r4, r5, 44, 136, 21
	round r5, r6, r7, r4, 56, 140, 16
	
	round r4, r5, r6, r7,  4, 144,  9
	round r7, r4, r5, r6, 16, 148, 28
	round r6, r7, r4, r5, 28, 152, 21
	round r5, r6, r7, r4, 40, 156, 16
	
	round r4, r5, r6, r7, 52, 160,  9
	round r7, r4, r5, r6,  0, 164, 28
	round r6, r7, r4, r5, 12, 168, 21
	round r5, r6, r7, r4, 24, 172, 16

	round r4, r5, r6, r7, 36, 176,  9
	round r7, r4, r5, r6, 48, 180, 28
	round r6, r7, r4, r5, 60, 184, 21
	round r5, r6, r7, r4,  8, 188, 16

	/* fourth loop */
.purgem round
.macro round a, b, c, d, offset_block, offset_table, shift
	ldr r10, [r0, +#\offset_block]
	ldr r11, [r3, +#\offset_table]
	add \b, \c, \b, ROR #\shift
	mvn r8, \d
	orr r8, r8, \b
	eor r8, r8, \c
	add \a, \a, r8
	add r10, r10, r11
	add \a, \a, r10
.endm

	round r4, r5, r6, r7,  0, 192,  9
	round r7, r4, r5, r6, 28, 196, 26
	round r6, r7, r4, r5, 56, 200, 22
	round r5, r6, r7, r4, 20, 204, 17

	round r4, r5, r6, r7, 48, 208, 11
	round r7, r4, r5, r6, 12, 212, 26
	round r6, r7, r4, r5, 40, 216, 22
	round r5, r6, r7, r4,  4, 220, 17

	round r4, r5, r6, r7, 32, 224, 11
	round r7, r4, r5, r6, 60, 228, 26
	round r6, r7, r4, r5, 24, 232, 22
	round r5, r6, r7, r4, 52, 236, 17

	round r4, r5, r6, r7, 16, 240, 11
	round r7, r4, r5, r6, 44, 244, 26
	round r6, r7, r4, r5,  8, 248, 22
	round r5, r6, r7, r4, 36, 252, 17
	
	ldmia r1, {r8, r9, r10, r11}
	
	subs r2, r2, #1
	addne r0, r0, #64
	
	add r5, r6, r5, ROR #11
	add r4, r4, r8
	add r5, r5, r9
	add r6, r6, r10
	add r7, r7, r11
	stmia r1, {r4, r5, r6, r7}
	
	bne .Lstart
	
.Lend:
	pop {r4 - r11}
	bx lr

addr_table:
	.word md5_table
