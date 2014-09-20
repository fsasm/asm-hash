/*
 * blake256_block.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-09-19
 */

.arch armv6

.section .rodata
.align 4
blake256_table:
	.word 0x243F6A88
	.word 0x85A308D3
	.word 0x13198A2E
	.word 0x03707344
	.word 0xA4093822
	.word 0x299F31D0
	.word 0x082EFA98
	.word 0xEC4E6C89 /*  8 */
	.word 0x452821E6
	.word 0x38D01377
	.word 0xBE5466CF
	.word 0x34E90C6C
	.word 0xC0AC29B7
	.word 0xC97C50DD
	.word 0x3F84D5B5
	.word 0xB5470917 /* 16 */

blake256_permutations: /* 8 digits packed in 32 bit */
	.word 0x76543210
	.word 0xFEDCBA98 /* 0 */
	.word 0x6DF984AE
	.word 0x357B20C1 /* 1 */
	.word 0xDF250C8B
	.word 0x491763EA /* 2 */
	.word 0xEBCD1397
	.word 0x8F04A562 /* 3 */
	.word 0xFA427509
	.word 0xD386CB1E /* 4 */
	.word 0x38B0A6C2
	.word 0x91EF57D4 /* 5 */
	.word 0xA4DEF15C
	.word 0xB8293670 /* 6 */
	.word 0x931CE7BD
	.word 0xA2684F05 /* 7 */
	.word 0x803B9EF6
	.word 0x5A417D2C /* 8 */
	.word 0x5167482A
	.word 0x0DC3E9BF /* 9 */

.text
.global blake256_process_block_asm
blake256_process_block_asm: /* (uint8_t block[64], uint32_t hash[8], uint64_t counter) */
	push {r4 - r12, lr}
	sub sp, sp, #64
	
	ldr r12, addr_table
	ldmia r1, {r4 - r11}	
	stmia sp!, {r4 - r11}
	ldmia r12, {r4 - r11}
	eor r8, r8, r2, LSL #3
	eor r9, r9, r2, LSL #3
	eor r10, r10, r2, LSR #29
	eor r10, r10, r3, LSL #3
	eor r11, r11, r2, LSR #29
	eor r11, r11, r3, LSL #3
	stmia sp, {r4 - r11}
	sub sp, sp, #32
	
	mov r3, #10
	ldr r4, addr_permutations
	ldr r5, addr_table
.Lloop1:

.macro round a, b, c, d
	ldrb r6, [r4], #1
	lsr r7, r6, #4
	and r6, r6, #15
	
	ldr r9, [r0, +r7, LSL #2]
	ldr r8, [r0, +r6, LSL #2]
	ldr r11, [r5, +r7, LSL #2]
	ldr r10, [r5, +r6, LSL #2]
	rev r6, r8
	rev r7, r9	
	ldr r8, [sp, #(\a)]
	ldr r9, [sp, #(\b)]
	eor r6, r6, r11
	eor r7, r7, r10
	ldr r11, [sp, #(\d)]
	ldr r10, [sp, #(\c)]
	
	add r8, r8, r9
	add r8, r8, r6
	eor r11, r11, r8
	ror r11, r11, #16
	add r10, r10, r11
	eor r9, r9, r10
	ror r9, r9, #12
	add r8, r8, r9
	add r8, r8, r7
	eor r11, r11, r8
	ror r11, r11, #8
	add r10, r10, r11
	eor r9, r9, r10
	ror r9, r9, #7
	
	str r8, [sp, #(\a)]
	str r9, [sp, #(\b)]	
	str r10, [sp, #(\c)]
	str r11, [sp, #(\d)]
.endm

	round  0, 16, 32, 48
	round  4, 20, 36, 52
	round  8, 24, 40, 56
	round 12, 28, 44, 60
	
	round  0, 20, 40, 60
	round  4, 24, 44, 48
	round  8, 28, 32, 52
	round 12, 16, 36, 56
	
	subs r3, r3, #1
	bne .Lloop1
	
	ldr r4, addr_permutations
	mov r3, #4
	
.Lloop2:
	round  0, 16, 32, 48
	round  4, 20, 36, 52
	round  8, 24, 40, 56
	round 12, 28, 44, 60
	
	round  0, 20, 40, 60
	round  4, 24, 44, 48
	round  8, 28, 32, 52
	round 12, 16, 36, 56
	
	subs r3, r3, #1
	bne .Lloop2

.macro process_hash
	ldmia r1, {r3 - r6}
	ldmia sp, {r7 - r10}
	add sp, sp, #32
	eor r3, r3, r7
	eor r4, r4, r8
	eor r5, r5, r9
	eor r6, r6, r10
	ldmia sp, {r7 - r10}
	sub sp, sp, #16
	eor r3, r3, r7
	eor r4, r4, r8
	eor r5, r5, r9
	eor r6, r6, r10
	stmia r1!, {r3 - r6}
.endm

	process_hash /* 0 - 3 */
	process_hash /* 4 - 7 */
	add sp, sp, #32
.Lend:
	pop {r4 - r12, lr}
	bx lr

addr_table:
	.word blake256_table
	
addr_permutations:
	.word blake256_permutations
