/*
 * sha256_block.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-05-09
 */

.arch armv6

.section .rodata
.align 4

sha256_table:
	.word 0x428A2F98
	.word 0x71374491
	.word 0xB5C0FBCF
	.word 0xE9B5DBA5
	.word 0x3956C25B
	.word 0x59F111F1
	.word 0x923F82A4
	.word 0xAB1C5ED5 /*  8 */
	.word 0xD807AA98
	.word 0x12835B01
	.word 0x243185BE
	.word 0x550C7DC3
	.word 0x72BE5D74
	.word 0x80DEB1FE
	.word 0x9BDC06A7
	.word 0xC19BF174 /* 16 */
	.word 0xE49B69C1
	.word 0xEFBE4786
	.word 0x0FC19DC6
	.word 0x240CA1CC
	.word 0x2DE92C6F
	.word 0x4A7484AA
	.word 0x5CB0A9DC
	.word 0x76F988DA /* 24 */
	.word 0x983E5152
	.word 0xA831C66D
	.word 0xB00327C8
	.word 0xBF597FC7
	.word 0xC6E00BF3
	.word 0xD5A79147
	.word 0x06CA6351
	.word 0x14292967 /* 32 */
	.word 0x27B70A85
	.word 0x2E1B2138
	.word 0x4D2C6DFC
	.word 0x53380D13
	.word 0x650A7354
	.word 0x766A0ABB
	.word 0x81C2C92E
	.word 0x92722C85 /* 40 */
	.word 0xA2BFE8A1
	.word 0xA81A664B
	.word 0xC24B8B70
	.word 0xC76C51A3
	.word 0xD192E819
	.word 0xD6990624
	.word 0xF40E3585
	.word 0x106AA070 /* 48 */
	.word 0x19A4C116
	.word 0x1E376C08
	.word 0x2748774C
	.word 0x34B0BCB5
	.word 0x391C0CB3
	.word 0x4ED8AA4A
	.word 0x5B9CCA4F
	.word 0x682E6FF3 /* 56 */
	.word 0x748F82EE
	.word 0x78A5636F
	.word 0x84C87814
	.word 0x8CC70208
	.word 0x90BEFFFA
	.word 0xA4506CEB
	.word 0xBEF9A3F7
	.word 0xC67178F2 /* 64 */

.text
.global sha256_process_block_asm
sha256_process_block_asm: /* (uint8_t block[64], uint32_t hash[8]) */
	push {r4 - r12, lr}
	sub sp, sp, #256 /* 4 * 64 = 256 */
	mov r2, #0
	
.Lloop0_start:
	ldr r3, [r0, r2, LSL #2]
	rev r3, r3
	str r3, [sp, r2, LSL #2]
	
	add r2, r2, #1
.Lloop0_end:
	cmp r2, #16
	blt .Lloop0_start
	
.Lloop1_start:
	sub r4, r2, #7
	ldr r3, [sp, r4, LSL #2]
	sub r4, r2, #16
	ldr r5, [sp, r4, LSL #2]
	add r3, r3, r5
	/* f6 */
	sub r4, r2, #2
	ldr r5, [sp, r4, LSL #2]
	ror r4, r5, #17
	ror r6, r5, #19
	eor r4, r4, r6
	lsr r6, r5, #10
	eor r4, r4, r6
	add r3, r3, r4
	
	/* f5 */
	sub r4, r2, #15
	ldr r5, [sp, r4, LSL #2]
	ror r4, r5, #7
	ror r6, r5, #18
	eor r4, r4, r6
	lsr r6, r5, #3
	eor r4, r4, r6
	add r3, r3, r4
	str r3, [sp, r2, LSL #2]
	
	add r2, r2, #1
.Lloop1_end:
	cmp r2, #64
	blt .Lloop1_start

	mov r10, #0 /* counter */
	ldr r0, addr_table
	ldmia r1, {r2 - r9} /* hash */

.Lloop2_start:
	/* h = temp1 */
	ldr r11, [r0, r10, LSL #2]
	add r9, r9, r11
	ldr r11, [sp, r10, LSL #2]
	add r9, r9, r11
	
	/* f4 (e) */
	ror r11, r6, #6
	ror r12, r6, #11
	eor r11, r11, r12
	ror r12, r6, #25
	eor r11, r11, r12
	add r9, r9, r11
	
	/* f1 (e, f, g) */
	and r11, r6, r7
	bic r12, r8, r6
	eor r11, r11, r12
	add r9, r9, r11
	
	/* r11 = temp2 */
	ror r11, r2, #2
	ror r12, r2, #13
	eor r11, r11, r12
	ror r12, r2, #22
	eor r11, r11, r12
	
	/* f2 (a, b, c) */
	and r12, r2, r3
	and lr, r3, r4
	eor r12, r12, lr
	and lr, r2, r4
	eor r12, r12, lr
	add r11, r11, r12
	
	/* permutation */
	mov r12, r9	
	mov r9, r8
	mov r8, r7
	mov r7, r6
	add r6, r5, r12
	mov r5, r4
	mov r4, r3
	mov r3, r2
	add r2, r11, r12
	
	add r10, r10, #1
.Lloop2_end:
	cmp r10, #64
	blt .Lloop2_start
	add sp, sp, #256
	/* end */
	ldmia r1, {r0, r10 - r12}
	add r2, r2, r0
	add r3, r3, r10
	add r4, r4, r11
	add r5, r5, r12
	stmia r1, {r2 - r5}
	add r1, r1, #16
	
	ldmia r1, {r0, r10 - r12}
	add r2, r6, r0
	add r3, r7, r10
	add r4, r8, r11
	add r5, r9, r12
	stmia r1, {r2 - r5}
	
	pop {r4 - r12, lr}
	bx lr

addr_table:
	.word sha256_table
	