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
	push {r4 - r12}
	sub sp, sp, #256 /* 4 * 64 = 256 */
	
	/* loop 1a */
	ldmia r0!, {r3 - r10}
	rev r3, r3
	rev r4, r4
	rev r5, r5
	rev r6, r6
	rev r7, r7
	rev r8, r8
	rev r9, r9
	rev r10, r10
	stmia sp!, {r3 - r10}
	
	ldmia r0!, {r3 - r10}
	rev r3, r3
	rev r4, r4
	rev r5, r5
	rev r6, r6
	rev r7, r7
	rev r8, r8
	rev r9, r9
	rev r10, r10
	stmia sp, {r3 - r10}
	sub sp, sp, #32
	
	mov r2, #12
	/* loop 1b */
.Lloop1_start:
	ldr r3, [sp, +#56]
	ldr r6, [sp, +#36]
	ldrd r4, r5, [sp, +#0] 
	ror r7, r3, #17
	ror r8, r3, #19
	lsr r9, r3, #10
	eor r7, r7, r8
	eor r7, r7, r9
	add r3, r6, r7
	add r3, r3, r4
	ror r7, r5, #7
	ror r8, r5, #18
	lsr r9, r5, #3
	eor r7, r7, r8
	eor r7, r7, r9
	add r3, r3, r7
	str r3, [sp, +#64]

	ldr r3, [sp, +#60]
	ldr r6, [sp, +#40]
	ldrd r4, r5, [sp, +#4]
	ror r7, r3, #17
	ror r8, r3, #19
	lsr r9, r3, #10
	eor r7, r7, r8
	eor r7, r7, r9
	add r3, r6, r7
	add r3, r3, r4
	ror r7, r5, #7
	ror r8, r5, #18
	lsr r9, r5, #3
	eor r7, r7, r8
	eor r7, r7, r9
	add r3, r3, r7
	str r3, [sp, +#68]
	
	ldr r3, [sp, +#64]
	ldr r6, [sp, +#44]
	ldrd r4, r5, [sp, +#8]
	ror r7, r3, #17
	ror r8, r3, #19
	lsr r9, r3, #10
	eor r7, r7, r8
	eor r7, r7, r9
	add r3, r6, r7
	add r3, r3, r4
	ror r7, r5, #7
	ror r8, r5, #18
	lsr r9, r5, #3
	eor r7, r7, r8
	eor r7, r7, r9
	add r3, r3, r7
	str r3, [sp, +#72]

	ldr r3, [sp, +#68]
	ldr r6, [sp, +#48]
	ldrd r4, r5, [sp, +#12]
	ror r7, r3, #17
	ror r8, r3, #19
	lsr r9, r3, #10
	eor r7, r7, r8
	eor r7, r7, r9
	add r3, r6, r7
	add r3, r3, r4
	ror r7, r5, #7
	ror r8, r5, #18
	lsr r9, r5, #3
	eor r7, r7, r8
	eor r7, r7, r9
	add r3, r3, r7
	str r3, [sp, +#76]
	
	subs r2, r2, #1
	add sp, sp, #16
.Lloop1_check:
	bne .Lloop1_start
	sub sp, sp, #192
	
	mov r2, #8 /* counter */
	ldr r0, addr_table
	ldmia r1, {r3 - r10} /* hash */

.Lloop2_start:
	ldr r11, [r0], +#4
	ldr r12, [sp], +#4
	add r10, r10, r11
	ror r11, r7, #6
	add r10, r10, r12 	
	ror r12, r7, #11
	eor r11, r11, r12
	ror r12, r7, #25
	eor r11, r11, r12
	add r10, r10, r11
	and r11, r7, r8
	bic r12, r9, r7
	eor r11, r11, r12
	add r10, r10, r11
	add r6, r6, r10
	ror r11, r3, #2
	ror r12, r3, #13
	eor r11, r11, r12
	ror r12, r3, #22
	eor r11, r11, r12
	add r10, r10, r11
	and r11, r3, r4
	and r12, r3, r5
	eor r11, r11, r12
	and r12, r4, r5
	eor r11, r11, r12
	add r10, r10, r11
	
	ldr r11, [r0], +#4
	ldr r12, [sp], +#4
	add r9, r9, r11
	ror r11, r6, #6
	add r9, r9, r12 
	ror r12, r6, #11
	eor r11, r11, r12
	ror r12, r6, #25
	eor r11, r11, r12
	add r9, r9, r11
	and r11, r6, r7
	bic r12, r8, r6
	eor r11, r11, r12
	add r9, r9, r11
	add r5, r5, r9
	ror r11, r10, #2
	ror r12, r10, #13
	eor r11, r11, r12
	ror r12, r10, #22
	eor r11, r11, r12
	add r9, r9, r11
	and r11, r10, r3
	and r12, r10, r4
	eor r11, r11, r12
	and r12, r3, r4
	eor r11, r11, r12
	add r9, r9, r11
	
	ldr r11, [r0], +#4
	ldr r12, [sp], +#4
	add r8, r8, r11
	ror r11, r5, #6
	add r8, r8, r12 
	ror r12, r5, #11
	eor r11, r11, r12
	ror r12, r5, #25
	eor r11, r11, r12
	add r8, r8, r11
	and r11, r5, r6
	bic r12, r7, r5
	eor r11, r11, r12
	add r8, r8, r11
	add r4, r4, r8
	ror r11, r9, #2
	ror r12, r9, #13
	eor r11, r11, r12
	ror r12, r9, #22
	eor r11, r11, r12
	add r8, r8, r11
	and r11, r9, r10
	and r12, r9, r3
	eor r11, r11, r12
	and r12, r10, r3
	eor r11, r11, r12
	add r8, r8, r11
	
	ldr r11, [r0], +#4
	ldr r12, [sp], +#4
	add r7, r7, r11
	ror r11, r4, #6
	add r7, r7, r12 
	ror r12, r4, #11
	eor r11, r11, r12
	ror r12, r4, #25
	eor r11, r11, r12
	add r7, r7, r11
	and r11, r4, r5
	bic r12, r6, r4
	eor r11, r11, r12
	add r7, r7, r11
	add r3, r3, r7
	ror r11, r8, #2
	ror r12, r8, #13
	eor r11, r11, r12
	ror r12, r8, #22
	eor r11, r11, r12
	add r7, r7, r11
	and r11, r8, r9
	and r12, r8, r10
	eor r11, r11, r12
	and r12, r9, r10
	eor r11, r11, r12
	add r7, r7, r11
	
	ldr r11, [r0], +#4
	ldr r12, [sp], +#4
	add r6, r6, r11
	ror r11, r3, #6
	add r6, r6, r12 
	ror r12, r3, #11
	eor r11, r11, r12
	ror r12, r3, #25
	eor r11, r11, r12
	add r6, r6, r11
	and r11, r3, r4
	bic r12, r5, r3
	eor r11, r11, r12
	add r6, r6, r11
	add r10, r10, r6
	ror r11, r7, #2
	ror r12, r7, #13
	eor r11, r11, r12
	ror r12, r7, #22
	eor r11, r11, r12
	add r6, r6, r11
	and r11, r7, r8
	and r12, r7, r9
	eor r11, r11, r12
	and r12, r8, r9
	eor r11, r11, r12
	add r6, r6, r11

	ldr r11, [r0], +#4
	ldr r12, [sp], +#4
	add r5, r5, r11
	ror r11, r10, #6
	add r5, r5, r12 
	ror r12, r10, #11
	eor r11, r11, r12
	ror r12, r10, #25
	eor r11, r11, r12
	add r5, r5, r11
	and r11, r10, r3
	bic r12, r4, r10
	eor r11, r11, r12
	add r5, r5, r11
	add r9, r9, r5
	ror r11, r6, #2
	ror r12, r6, #13
	eor r11, r11, r12
	ror r12, r6, #22
	eor r11, r11, r12
	add r5, r5, r11
	and r11, r6, r7
	and r12, r6, r8
	eor r11, r11, r12
	and r12, r7, r8
	eor r11, r11, r12
	add r5, r5, r11
	
	ldr r11, [r0], +#4
	ldr r12, [sp], +#4
	add r4, r4, r11
	ror r11, r9, #6
	add r4, r4, r12 
	ror r12, r9, #11
	eor r11, r11, r12
	ror r12, r9, #25
	eor r11, r11, r12
	add r4, r4, r11
	and r11, r9, r10
	bic r12, r3, r9
	eor r11, r11, r12
	add r4, r4, r11
	add r8, r8, r4
	ror r11, r5, #2
	ror r12, r5, #13
	eor r11, r11, r12
	ror r12, r5, #22
	eor r11, r11, r12
	add r4, r4, r11
	and r11, r5, r6
	and r12, r5, r7
	eor r11, r11, r12
	and r12, r6, r7
	eor r11, r11, r12
	add r4, r4, r11
	
	ldr r11, [r0], +#4
	ldr r12, [sp], +#4
	add r3, r3, r11
	ror r11, r8, #6
	add r3, r3, r12 
	ror r12, r8, #11
	eor r11, r11, r12
	ror r12, r8, #25
	eor r11, r11, r12
	add r3, r3, r11
	and r11, r8, r9
	bic r12, r10, r8
	eor r11, r11, r12
	add r3, r3, r11
	add r7, r7, r3
	ror r11, r4, #2
	ror r12, r4, #13
	eor r11, r11, r12
	ror r12, r4, #22
	eor r11, r11, r12
	add r3, r3, r11
	and r11, r4, r5
	and r12, r4, r6
	eor r11, r11, r12
	and r12, r5, r6
	eor r11, r11, r12
	add r3, r3, r11

	subs r2, r2, #1
.Lloop2_end:
	bne .Lloop2_start

	/* end */
	ldmia r1, {r0, r2, r11, r12}
	add r3, r3, r0
	add r4, r4, r2
	add r5, r5, r11
	add r6, r6, r12
	stmia r1!, {r3 - r6}
	
	ldmia r1, {r3 - r6}
	add r7, r7, r3
	add r8, r8, r4
	add r9, r9, r5
	add r10, r10, r6
	stmia r1, {r7 - r10}
	
	pop {r4 - r12}
	bx lr

addr_table:
	.word sha256_table
	