/*
 * sha512_block.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-05-09
 */

.arch armv6

.section .rodata
.align 4
sha512_table: /* uint64_t[80] (little endian) */
	.word 0xD728AE22
	.word 0x428A2F98
	.word 0x23EF65CD
	.word 0x71374491
	.word 0xEC4D3B2F
	.word 0xB5C0FBCF
	.word 0x8189DBBC
	.word 0xE9B5DBA5 /*  4 */
	.word 0xF348B538
	.word 0x3956C25B
	.word 0xB605D019
	.word 0x59F111F1
	.word 0xAF194F9B
	.word 0x923F82A4
	.word 0xDA6D8118
	.word 0xAB1C5ED5 /*  8 */
	.word 0xA3030242
	.word 0xD807AA98
	.word 0x45706FBE
	.word 0x12835B01
	.word 0x4EE4B28C
	.word 0x243185BE
	.word 0xD5FFB4E2
	.word 0x550C7DC3 /* 12 */
	.word 0xF27B896F
	.word 0x72BE5D74
	.word 0x3B1696B1
	.word 0x80DEB1FE
	.word 0x25C71235
	.word 0x9BDC06A7
	.word 0xCF692694
	.word 0xC19BF174 /* 16 */
	.word 0x9EF14AD2
	.word 0xE49B69C1
	.word 0x384F25E3
	.word 0xEFBE4786
	.word 0x8B8CD5B5
	.word 0x0FC19DC6
	.word 0x77AC9C65
	.word 0x240CA1CC /* 20 */
	.word 0x592B0275
	.word 0x2DE92C6F
	.word 0x6EA6E483
	.word 0x4A7484AA
	.word 0xBD41FBD4
	.word 0x5CB0A9DC
	.word 0x831153B5
	.word 0x76F988DA /* 24 */
	.word 0xEE66DFAB
	.word 0x983E5152
	.word 0x2DB43210
	.word 0xA831C66D
	.word 0x98FB213F
	.word 0xB00327C8
	.word 0xBEEF0EE4
	.word 0xBF597FC7 /* 28 */
	.word 0x3DA88FC2
	.word 0xC6E00BF3
	.word 0x930AA725
	.word 0xD5A79147
	.word 0xE003826F
	.word 0x06CA6351
	.word 0x0A0E6E70
	.word 0x14292967 /* 32 */
	.word 0x46D22FFC
	.word 0x27B70A85
	.word 0x5C26C926
	.word 0x2E1B2138
	.word 0x5AC42AED
	.word 0x4D2C6DFC
	.word 0x9D95B3DF
	.word 0x53380D13 /* 36 */
	.word 0x8BAF63DE
	.word 0x650A7354
	.word 0x3C77B2A8
	.word 0x766A0ABB
	.word 0x47EDAEE6
	.word 0x81C2C92E
	.word 0x1482353B
	.word 0x92722C85 /* 40 */
	.word 0x4CF10364
	.word 0xA2BFE8A1
	.word 0xBC423001
	.word 0xA81A664B
	.word 0xD0F89791
	.word 0xC24B8B70
	.word 0x0654BE30
	.word 0xC76C51A3 /* 44 */
	.word 0xD6EF5218
	.word 0xD192E819
	.word 0x5565A910
	.word 0xD6990624
	.word 0x5771202A
	.word 0xF40E3585
	.word 0x32BBD1B8
	.word 0x106AA070 /* 48 */
	.word 0xB8D2D0C8
	.word 0x19A4C116
	.word 0x5141AB53
	.word 0x1E376C08
	.word 0xDF8EEB99
	.word 0x2748774C
	.word 0xE19B48A8
	.word 0x34B0BCB5 /* 52 */
	.word 0xC5C95A63
	.word 0x391C0CB3
	.word 0xE3418ACB
	.word 0x4ED8AA4A
	.word 0x7763E373
	.word 0x5B9CCA4F
	.word 0xD6B2B8A3
	.word 0x682E6FF3 /* 56 */
	.word 0x5DEFB2FC
	.word 0x748F82EE
	.word 0x43172F60
	.word 0x78A5636F
	.word 0xA1F0AB72
	.word 0x84C87814
	.word 0x1A6439EC
	.word 0x8CC70208 /* 60 */
	.word 0x23631E28
	.word 0x90BEFFFA
	.word 0xDE82BDE9
	.word 0xA4506CEB
	.word 0xB2C67915
	.word 0xBEF9A3F7
	.word 0xE372532B
	.word 0xC67178F2 /* 64 */
	.word 0xEA26619C
	.word 0xCA273ECE
	.word 0x21C0C207
	.word 0xD186B8C7
	.word 0xCDE0EB1E
	.word 0xEADA7DD6
	.word 0xEE6ED178
	.word 0xF57D4F7F /* 68 */
	.word 0x72176FBA
	.word 0x06F067AA
	.word 0xA2C898A6
	.word 0x0A637DC5
	.word 0xBEF90DAE
	.word 0x113F9804
	.word 0x131C471B
	.word 0x1B710B35 /* 72 */
	.word 0x23047D84
	.word 0x28DB77F5
	.word 0x40C72493
	.word 0x32CAAB7B
	.word 0x15C9BEBC
	.word 0x3C9EBE0A
	.word 0x9C100D4C
	.word 0x431D67C4 /* 76 */
	.word 0xCB3E42B6
	.word 0x4CC5D4BE
	.word 0xFC657E2A
	.word 0x597F299C
	.word 0x3AD6FAEC
	.word 0x5FCB6FAB
	.word 0x4A475817
	.word 0x6C44198C /* 80 */
	
.text
.global sha512_process_blocks_asm
.type sha512_process_blocks_asm, %function
sha512_process_blocks_asm: /* (uint8_t block[128], uint64_t hash[8], uint n) */
	push {r4 - r12, lr}
	cmp r2, #0
	beq .Lend
	sub sp, sp, #640 /* 8 * 80 = 640 */
	
.Lstart:
	/* loop 1a */
.macro rev_64 low, high
	rev r11, \low
	rev \low, \high
	mov \high, r11
.endm

	ldmia r0!, {r3 - r10}
	rev_64 r3, r4
	rev_64 r5, r6
	rev_64 r7, r8
	rev_64 r9, r10
	stmia sp!, {r3 - r10}
	
	ldmia r0!, {r3 - r10}
	rev_64 r3, r4
	rev_64 r5, r6
	rev_64 r7, r8
	rev_64 r9, r10
	stmia sp!, {r3 - r10}
	
	ldmia r0!, {r3 - r10}
	rev_64 r3, r4
	rev_64 r5, r6
	rev_64 r7, r8
	rev_64 r9, r10
	stmia sp!, {r3 - r10}
	
	ldmia r0!, {r3 - r10}
	rev_64 r3, r4
	rev_64 r5, r6
	rev_64 r7, r8
	rev_64 r9, r10
	stmia sp!, {r3 - r10}
	
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
.endif /* FIXME add cases for 33 */
.endm
	
.macro ror_xor_64 dst_low, dst_high, src_low, src_high, times
.if \times < 32
	eor \dst_high, \dst_high, \src_high, LSR #\times
	eor \dst_low, \dst_low, \src_low, LSR#\times
	eor \dst_high, \dst_high, \src_low, LSL #(32 - \times)
	eor \dst_low, \dst_low, \src_high, LSL #(32 - \times)
.else
	eor \dst_low, \dst_low, \src_high, LSR #(\times - 32)
	eor \dst_low, \dst_low, \src_low, LSL #(64 - \times)
	eor \dst_high, \dst_high, \src_high, LSL #(64 - \times)
	eor \dst_high, \dst_high, \src_low, LSR #(\times - 32)
.endif
.endm

.macro lsr_64 dst_low, dst_high, src_low, src_high, times
.if \times < 32
	lsr \dst_low, \src_low, #\times
	orr \dst_low, \dst_low, \src_high, LSL #(32 - \times)
	lsr \dst_high, \src_high, #\times
.else
	lsr \dst_low, \src_high, #(\times - 32)
	eor \dst_high, \dst_high, \dst_high /* zero the high part */
.endif
.endm
	/* loop 1b */
	mov r3, #64
	mov r11, sp
	sub sp, sp, #128
	
.L1:
	ldrd r4, r5, [r11, #-128]
	ldrd r6, r7, [r11, #-56]
	adds r4, r4, r6
	adc r5, r5, r7
	ldrd r6, r7, [r11, #-16]
	lsr_64 r8, r9, r6, r7, 6
	ror_xor_64 r8, r9, r6, r7, 61
	ror_xor_64 r8, r9, r6, r7, 19
	adds r4, r4, r8
	adc r5, r5, r9
	ldrd r6, r7, [r11, #-120]
	lsr_64 r8, r9, r6, r7, 7
	ror_xor_64 r8, r9, r6, r7, 8
	ror_xor_64 r8, r9, r6, r7, 1
	adds r4, r4, r8	
	adc r5, r5, r9
	strd r4, r5, [r11], +#8
	
	subs r3, r3, #1
	bne .L1
	
	/* loop 2 */
	sub sp, sp, #64
	
	ldmia r1!, {r3 - r10}
	stmia sp!, {r3 - r10}
	ldmia r1,  {r3 - r10}
	stmia sp,  {r3 - r10}
	sub r1, r1, #32
	sub sp, sp, #32

	add r11, sp, #64 /* r11: pointer to W[] */
	mov r12, #10
	ldr r3, addr_table
	
.L2:
.macro round a, b, c, d, e, f, g, h
	ldrd r4, r5, [sp, #\h]
	ldrd r6, r7, [r3], #+8
	adds r4, r4, r6
	adc r5, r5, r7
	ldrd r6, r7, [r11], #+8
	adds r4, r4, r6
	adc r5, r5, r7
	ldrd r6, r7, [sp, #\e]
	ror_64 r8, r9, r6, r7, 41
	ror_xor_64 r8, r9, r6, r7, 18
	ror_xor_64 r8, r9, r6, r7, 14
	adds r4, r4, r8
	adc r5, r5, r9
	ldr r8, [sp, #\f] /* low word */
	ldr r9, [sp, #\g]
	and r8, r8, r6
	bic r9, r9, r6
	eor r6, r8, r9
	ldr r8, [sp, #(\f + 4)] /* high word */
	ldr r9, [sp, #(\g + 4)]
	and r8, r8, r7
	bic r9, r9, r7
	eor r7, r8, r9
	adds r4, r4, r6
	adc r5, r5, r7
	ldrd r6, r7, [sp, #\d]
	adds r6, r4, r6
	adc r7, r5, r7
	strd r6, r7, [sp, #\d]
	ldrd r6, r7, [sp, #\a]
	ror_64 r8, r9, r6, r7, 39
	ror_xor_64 r8, r9, r6, r7, 34
	ror_xor_64 r8, r9, r6, r7, 28
	adds r4, r4, r8
	adc r5, r5, r9
	ldr r8, [sp, #\b]
	ldr r9, [sp, #\c]
	and r10, r6, r8
	and r8, r8, r9
	eor r8, r8, r10
	and r10, r6, r9
	eor r6, r8, r10
	ldr r8, [sp, #(\b + 4)]
	ldr r9, [sp, #(\c + 4)]
	and r10, r7, r8
	and r8, r8, r9
	eor r8, r8, r10
	and r10, r7, r9
	eor r7, r8, r10
	adds r4, r4, r6
	adc r5, r5, r7
	strd r4, r5, [sp, #\h]
.endm
	round 0, 8, 16, 24, 32, 40, 48, 56
	round 56, 0, 8, 16, 24, 32, 40, 48
	round 48, 56, 0, 8, 16, 24, 32, 40
	round 40, 48, 56, 0, 8, 16, 24, 32
	round 32, 40, 48, 56, 0, 8, 16, 24
	round 24, 32, 40, 48, 56, 0, 8, 16
	round 16, 24, 32, 40, 48, 56, 0, 8
	round 8, 16, 24, 32, 40, 48, 56, 0
	
	subs r12, r12, #1
	bne .L2

.macro add_hash2
	ldmia sp!, {r7 - r10}
	ldmia r1,  {r3 - r6}
	adds r3, r3, r7
	adc  r4, r4, r8
	adds r5, r5, r9
	adc  r6, r6, r10
	stmia r1!, {r3 - r6}
.endm
	
	add_hash2
	add_hash2
	add_hash2
	add_hash2
	
	subs r2, r2, #1
	sub r1, r1, #64
	bne .Lstart
	
	add sp, sp, #640

.Lend:
	pop {r4 - r12, lr}
	bx lr

addr_table:
	.word sha512_table
