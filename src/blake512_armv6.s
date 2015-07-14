/*
 * blake512_armv6.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-09-21
 */
 
.arch armv6

.section .rodata
.align 4
blake512_table:
	.word 0x85A308D3
	.word 0x243F6A88 
	.word 0x03707344
	.word 0x13198A2E
	.word 0x299F31D0
	.word 0xA4093822
	.word 0xEC4E6C89
	.word 0x082EFA98 /*  4 */
	.word 0x38D01377
	.word 0x452821E6
	.word 0x34E90C6C
	.word 0xBE5466CF
	.word 0xC97C50DD
	.word 0xC0AC29B7
	.word 0xB5470917
	.word 0x3F84D5B5 /*  8 */
	.word 0x8979FB1B
	.word 0x9216D5D9
	.word 0x98DFB5AC
	.word 0xD1310BA6
	.word 0xD01ADFB7
	.word 0x2FFD72DB
	.word 0x6A267E96
	.word 0xB8E1AFED /* 12 */
	.word 0xF12C7F99
	.word 0xBA7C9045
	.word 0xB3916CF7
	.word 0x24A19947
	.word 0x858EFC16
	.word 0x0801F2E2
	.word 0x71574E69
	.word 0x636920D8  /* 16 */

blake512_permutations: /* 8 digits packed in 32 bit */
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

.macro ror_64 dst_low, dst_high, src_low, src_high, times
.if \times == 1
	movs \dst_low, \src_low, LSR #1
	mov \dst_high, \src_high, RRX
	orr \dst_low, \dst_low, \src_high, LSR #31
.elseif \times < 32
	lsr \dst_high, \src_high, #\times
	lsr \dst_low, \src_low, #\times
	orr \dst_high, \dst_high, \src_low, LSL #(32 - \times)
	orr \dst_low, \dst_low, \src_high, LSL #(32 - \times)
.elseif \times == 32
	mov \dst_low, \src_high
	mov \dst_high, \src_low
.elseif \times == 33
	movs \dst_high, \src_low, LSR #1
	mov \dst_low, \src_high, RRX
	orr \dst_high, \dst_high, \src_high, LSR #31
.else
	lsr \dst_low, \src_high, #(\times - 32)
	orr \dst_low, \dst_low, \src_low, LSL #(64 - \times)
	lsl \dst_high, \src_high, #(64 - \times)
	orr \dst_high, \dst_high, \src_low, LSR #(\times - 32)
.endif
.endm

.text

.global blake512_process_block_asm
.type blake512_process_block_asm, %function
blake512_process_block_asm: /* (uint8_t block[128], uint64_t hash[8], uint64_t counter) */
	push {r4 - r12, lr}
	sub sp, sp, #128
	
	ldr r12, addr_table
	ldmia r1!,  {r4 - r11}
	stmia sp!,  {r4 - r11} /* 0 - 3 */
	ldmia r1,  {r4 - r11}
	sub r1, r1, #32
	stmia sp!,  {r4 - r11} /* 4 - 7 */
	ldmia r12!, {r4 - r11}
	stmia sp!,  {r4 - r11} /* 8 - 11 */
	ldmia r12,  {r4 - r11}
	
	eor r4, r4, r2, LSL #3
	eor r5, r5, r3, LSL #3
	eor r5, r5, r2, LSR #29
	eor r6, r6, r2, LSL #3
	eor r7, r7, r3, LSL #3
	eor r7, r7, r2, LSR #29
	eor r8, r8, r3, LSR #29
	eor r10, r10, r3, LSR #29
	
	stmia sp,  {r4 - r11} /* 12 - 15 */
	sub sp, sp, #96
	
	mov r2, #16
	ldr r3, addr_table
	ldr r4, addr_permutations
	
.Lloop1:
.macro round a, b, c, d
	and r6, r5, #0x0F
	and r7, r5, #0xF0
	lsl r6, r6, #3 /* index0 */
	lsr r7, r7, #1 /* index1 */
	
	ldrd r10, r11, [r0, +r6]
	ldrd r8, r9, [r3, +r7]
	ldrd r6, r7, [sp, #\a]
	rev r10, r10
	rev r11, r11
	eor r8, r8, r11
	eor r9, r9, r10
	ldrd r10, r11, [sp, #\b]
	adds r6, r6, r8
	adc r7, r7, r9
	adds r6, r6, r10
	adc r7, r7, r11 /* a = a + b + mc1 */
	ldrd r8, r9, [sp, #\d]
	ldrd r10, r11, [sp, #\c]
	strd r6, r7, [sp, #\a] /* spilling :( */
	eor r8, r8, r6
	eor r9, r9, r7 /* a ^ d */
	ror_64 r6, r7, r8, r9, 32
	ldrd r8, r9, [sp, #\b]
	strd r6, r7, [sp, #\d] /* spilling :( */
	adds r10, r10, r6
	adc r11, r11, r7 /* c = c + d */
	strd r10, r11, [sp, #\c] /* spilling :( */
	eor r8, r8, r10
	eor r9, r9, r11
	ror_64 r6, r7, r8, r9, 25
	ldrd r10, r11, [sp, #\a]
	strd r6, r7, [sp, #\b] /* spilling :( */
	adds r6, r6, r10
	adc r7, r7, r11 /* a = a + b */
	and r8, r5, #0x0F
	and r12, r5, #0xF0
	lsl r8, r8, #3
	lsr r12, r12, #1
	ldrd r10, r11, [r3, +r8]
	ldrd r8, r9, [r0, +r12]
	rev r8, r8
	rev r9, r9
	eor r8, r8, r11
	eor r9, r9, r10
	adds r6, r6, r9
	adc r7, r7, r8 /* a = a + b + mc2 */
	ldrd r8, r9, [sp, #\d]
	ldrd r10, r11, [sp, #\c]
	strd r6, r7, [sp, #\a]
	eor r6, r6, r8
	eor r7, r7, r9
	ror_64 r8, r9, r6, r7, 16
	ldrd r6, r7, [sp, #\b]
	strd r8, r9, [sp, #\d]
	adds r10, r10, r8
	adc r11, r11, r9
	strd r10, r11, [sp, #\c]
	eor r10, r10, r6
	eor r11, r11, r7
	ror_64 r8, r9, r10, r11, 11
	strd r8, r9, [sp, #\b]
	
	lsr r5, r5, #8
.endm

	ldr r5, [r4], #+4
	round  0, 32, 64,  96
	round  8, 40, 72, 104
	round 16, 48, 80, 112
	round 24, 56, 88, 120

	ldr r5, [r4], #+4
	round  0, 40, 80, 120
	round  8, 48, 88,  96
	round 16, 56, 64, 104
	round 24, 32, 72, 112
	
	subs r2, r2, #1
	bne .Lloop1
	
	mov r0, r1
	
.macro process_hash
	ldmia r0, {r1 - r4}
	ldmia sp, {r5 - r8}
	add sp, sp, #64
	ldmia sp, {r9 - r12}
	sub sp, sp, #48
	eor r1, r1, r5
	eor r2, r2, r6
	eor r3, r3, r7
	eor r4, r4, r8
	eor r1, r1, r9
	eor r2, r2, r10
	eor r3, r3, r11
	eor r4, r4, r12
	stmia r0!, {r1 - r4}
.endm

	process_hash
	process_hash
	process_hash
	process_hash
	
	add sp, sp, #64
	pop {r4 - r12, lr}
	bx lr

addr_table:
	.word blake512_table
	
addr_permutations:
	.word blake512_permutations
