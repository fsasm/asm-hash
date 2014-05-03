/*
 * md5_block.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-03-28
 */

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
.global md5_process_block_asm
md5_process_block_asm: /* (uint32_t hash[4], uint8_t block[64]) */
	push {r4, r5, r6, r7, r8, r9, r10, r11, r12}
	ldr r2, addr_table
	mov r3, #0 /* loop counter */
	mov r12, #0 /* block index */
	/* r4 = h0; r5 = h1; r6 = h2; r7 = h3 */
	ldmia  r0, {r4, r5, r6, r7}

loop0_start:
	/* 1. iteration */
	ldr r10, [r1, r3, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	bic r9, r7, r5
	and r8, r5, r6
	orr r8, r8, r9
	add r4, r4, r8
	add r10, r10, r11
	add r4, r4, r10
	add r3, r3, #1
	add r4, r5, r4, ROR #25

	/* 2. iteration */
	ldr r10, [r1, r3, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	bic r9, r6, r4
	and r8, r4, r5
	orr r8, r8, r9
	add r7, r7, r8
	add r10, r10, r11
	add r7, r7, r10
	add r3, r3, #1
	add r7, r4, r7, ROR #20

	/* 3. iteration */
	ldr r10, [r1, r3, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	bic r9, r5, r7
	and r8, r7, r4
	orr r8, r8, r9
	add r6, r6, r8
	add r10, r10, r11
	add r6, r6, r10
	add r3, r3, #1
	add r6, r7, r6, ROR #15

	/* 4. iteration */
	ldr r10, [r1, r3, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	bic r9, r4, r6
	and r8, r6, r7
	orr r8, r8, r9
	add r5, r5, r8
	add r10, r10, r11
	add r5, r5, r10
	add r3, r3, #1
	add r5, r6, r5, ROR #10

loop0_check:
	cmp r3, #16
	blt loop0_start
	mov r12, #1

loop1_start:
	/* 1. iteration */
	ldr r11, [r2, r3, LSL #2]
	ldr r10, [r1, r12, LSL #2]
	bic r9, r6, r7
	and r8, r7, r5
	orr r9, r8, r9

	add r3, r3, #1
	add r10, r10, r11
	add r4, r4, r9
	add r12, r12, #5
	add r4, r4, r10
	and r12, r12, #0x0F
	add r4, r5, r4, ROR #27 /* 5, 9, 14, 20 */

	/* 2. iteration */
	ldr r11, [r2, r3, LSL #2]
	ldr r10, [r1, r12, LSL #2]
	bic r9, r5, r6
	and r8, r6, r4
	orr r9, r8, r9

	add r3, r3, #1
	add r10, r10, r11
	add r7, r7, r9
	add r12, r12, #5
	add r7, r7, r10
	and r12, r12, #0x0F
	add r7, r4, r7, ROR #23

	/* 3. iteration */
	ldr r11, [r2, r3, LSL #2]
	ldr r10, [r1, r12, LSL #2]
	bic r9, r4, r5
	and r8, r5, r7
	orr r9, r8, r9

	add r3, r3, #1
	add r10, r10, r11
	add r6, r6, r9
	add r12, r12, #5
	add r6, r6, r10
	and r12, r12, #0x0F
	add r6, r7, r6, ROR #18

	/* 4. iteration */
	ldr r10, [r1, r12, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	bic r9, r7, r4
	and r8, r4, r6
	orr r9, r8, r9

	add r3, r3, #1
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10
	add r12, r12, #5
	add r5, r6, r5, ROR #12
loop1_check:
	cmp r3, #32
	blt loop1_start
	mov r12, #5

loop2_start:
	/* 1. iteration */
	ldr r11, [r2, r3, LSL #2]
	ldr r10, [r1, r12, LSL #2]
	eor r8, r5, r6
	add r12, r12, #3
	eor r9, r8, r7
	add r10, r10, r11
	add r4, r4, r9
	and r12, r12, #0x0F
	add r4, r4, r10
	add r3, r3, #1
	add r4, r5, r4, ROR #28 /* 4, 11, 16, 23 */

	/* 2. iteration */
	ldr r10, [r1, r12, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	eor r8, r4, r5
	add r12, r12, #3
	eor r9, r8, r6
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10
	add r3, r3, #1
	add r7, r4, r7, ROR #21

	/* 3. iteration */
	ldr r10, [r1, r12, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	eor r8, r7, r4
	add r12, r12, #3
	eor r9, r8, r5
	add r10, r10, r11
	add r6, r6, r9
	and r12, r12, #0x0F
	add r6, r6, r10
	add r3, r3, #1
	add r6, r7, r6, ROR #16

	/* 4. iteration */
	ldr r10, [r1, r12, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	eor r8, r6, r7
	add r12, r12, #3
	eor r9, r8, r4
	add r10, r10, r11
	add r5, r5, r9
	and r12, r12, #0x0F
	add r5, r5, r10
	add r3, r3, #1
	add r5, r6, r5, ROR #9

loop2_check:
	cmp r3, #48
	blt loop2_start
	mov r12, #0

loop3_start:
	/* 1. iteration */
	ldr r11, [r2, r3, LSL #2]
	ldr r10, [r1, r12, LSL #2]
	mvn r8, r7
	add r12, r12, #7
	orr r8, r5, r8
	and r12, r12, #0x0F
	eor r9, r8, r6
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10
	add r3, r3, #1
	add r4, r5, r4, ROR #26 /* 6, 10, 15, 21 */


	/* 2. iteration */
	ldr r10, [r1, r12, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	mvn r8, r6
	add r12, r12, #7
	orr r8, r8, r4
	and r12, r12, #0x0F
	eor r9, r8, r5
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10
	add r3, r3, #1
	add r7, r4, r7, ROR #22

	/* 3. iteration */
	ldr r10, [r1, r12, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	mvn r8, r5
	add r12, r12, #7
	orr r8, r8, r7
	and r12, r12, #0x0F
	eor r9, r8, r4
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10
	add r3, r3, #1
	add r6, r7, r6, ROR #17

	/* 4. iteration */
	ldr r10, [r1, r12, LSL #2]
	ldr r11, [r2, r3, LSL #2]
	mvn r8, r4
	add r12, r12, #7
	orr r8, r8, r6
	and r12, r12, #0x0F
	eor r9, r8, r7
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10
	add r3, r3, #1
	add r5, r6, r5, ROR #11

loop3_check:
	cmp r3, #64
	blt loop3_start

	ldmia r0, {r8, r9, r10, r11}
	add r4, r4, r8
	add r5, r5, r9
	add r6, r6, r10
	add r7, r7, r11
	stmia r0, {r4, r5, r6, r7}

	pop {r4, r5, r6, r7, r8, r9, r10, r11, r12}
	bx lr

addr_table:
	.word md5_table
