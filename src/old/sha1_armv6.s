/*
 * sha1_armv6.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-05-01
 */

.arch armv6

.text
.arm
/* FIXME: without this hack the assembler throws errors because the pool is too far away */
k1:
	.word 0x5A827999
k2:
	.word 0x6ED9EBA1

.global sha1_process_blocks_asm
.type sha1_process_blocks_asm, %function
sha1_process_blocks_asm: /* (uint8_t block[], uint32_t hash[5], uint n) */
	push {r4 - r12}
	cmp r2, #0
	beq .Lend
	sub sp, sp, #64 /* alternative memory efficient SHA-1 algorithm */
	
	ldmia r1, {r3 - r7}	
	
.Lstart:
	ldr r8, k1
	/* loop 1a */
.macro round a, b, c, d, e, temp, offset_block
	and \temp, \c, \b
	bic r10, \d, \b
	orr \temp, \temp, r10
	ldr r10, [r0, +#\offset_block]
	add \temp, \temp, r8
	add \temp, \temp, \a, ROR #27
	add \temp, \temp, \e
	rev r10, r10
	add \temp, \temp, r10
	str r10, [sp, +#\offset_block]
	ror \b, \b, #2
.endm
	round r3, r4, r5, r6, r7, r9,  0
	round r9, r3, r4, r5, r6, r7,  4
	round r7, r9, r3, r4, r5, r6,  8
	round r6, r7, r9, r3, r4, r5, 12
	round r5, r6, r7, r9, r3, r4, 16
	round r4, r5, r6, r7, r9, r3, 20

	round r3, r4, r5, r6, r7, r9, 24
	round r9, r3, r4, r5, r6, r7, 28
	round r7, r9, r3, r4, r5, r6, 32
	round r6, r7, r9, r3, r4, r5, 36
	round r5, r6, r7, r9, r3, r4, 40
	round r4, r5, r6, r7, r9, r3, 44
	
	round r3, r4, r5, r6, r7, r9, 48
	round r9, r3, r4, r5, r6, r7, 52
	round r7, r9, r3, r4, r5, r6, 56
	round r6, r7, r9, r3, r4, r5, 60
	
	/* loop 1b */
.purgem round
.macro round a, b, c, d, e, temp, offset_stack
	ldr \temp, [sp, +#((\offset_stack + 52) & 63)]
	ldr r10, [sp, +#((\offset_stack + 32) & 63)]
	ldr r11, [sp, +#((\offset_stack + 8) & 63)]
	ldr r12, [sp, +#(\offset_stack & 63)]
	eor r10, r10, \temp
	eor r11, r11, r12
	eor r10, r10, r11
	ror r10, r10, #31
	str r10, [sp, +#(\offset_stack & 63)]
	and \temp, \b, \c
	bic r11, \d, \b
	orr \temp, \temp, r11
	add \temp, \temp, r8
	add \temp, \temp, r10
	add \temp, \temp, \a, ROR #27
	add \temp, \temp, \e
	ror \b, \b, #2
.endm
	round r5, r6, r7, r9, r3, r4, 64
	round r4, r5, r6, r7, r9, r3, 68
	round r3, r4, r5, r6, r7, r9, 72
	round r9, r3, r4, r5, r6, r7, 76
	
	/* loop 2 */
	ldr r8, k2
.purgem round
.macro round a, b, c, d, e, temp, offset_stack
	ldr \temp, [sp, +#((\offset_stack + 52) & 63)]
	ldr r10, [sp, +#((\offset_stack + 32) & 63)]
	ldr r11, [sp, +#((\offset_stack + 8) & 63)]
	ldr r12, [sp, +#(\offset_stack & 63)]
	eor r10, r10, \temp
	eor r11, r11, r12
	eor r10, r10, r11
	ror r10, r10, #31
	str r10, [sp, +#(\offset_stack & 63)]
	eor \temp, \b, \c
	eor \temp, \temp, \d
	add \temp, \temp, r8
	add \temp, \temp, r10
	add \temp, \temp, \a, ROR #27
	add \temp, \temp, \e
	ror \b, \b, #2
.endm

	round r7, r9, r3, r4, r5, r6,  80
	round r6, r7, r9, r3, r4, r5,  84
	round r5, r6, r7, r9, r3, r4,  88
	round r4, r5, r6, r7, r9, r3,  92
	round r3, r4, r5, r6, r7, r9,  96
	round r9, r3, r4, r5, r6, r7, 100

	round r7, r9, r3, r4, r5, r6, 104
	round r6, r7, r9, r3, r4, r5, 108
	round r5, r6, r7, r9, r3, r4, 112
	round r4, r5, r6, r7, r9, r3, 116
	round r3, r4, r5, r6, r7, r9, 120
	round r9, r3, r4, r5, r6, r7, 124
	
	round r7, r9, r3, r4, r5, r6, 128
	round r6, r7, r9, r3, r4, r5, 132
	round r5, r6, r7, r9, r3, r4, 136
	round r4, r5, r6, r7, r9, r3, 140
	round r3, r4, r5, r6, r7, r9, 144
	round r9, r3, r4, r5, r6, r7, 148
	
	round r7, r9, r3, r4, r5, r6, 152
	round r6, r7, r9, r3, r4, r5, 156

	/* loop 3 */
	ldr r8, =0x8F1BBCDC
.purgem round
.macro round a, b, c, d, e, temp, offset_stack
	ldr \temp, [sp, +#((\offset_stack + 52) & 63)]
	ldr r10, [sp, +#((\offset_stack + 32) & 63)]
	ldr r11, [sp, +#((\offset_stack + 8) & 63)]
	ldr r12, [sp, +#(\offset_stack & 63)]
	eor r10, r10, \temp
	eor r11, r11, r12
	eor r10, r10, r11
	ror r10, r10, #31
	str r10, [sp, +#(\offset_stack & 63)]
	and \temp, \b, \c
	and r11, \b, \d
	and r12, \c, \d
	orr \temp, \temp, r11
	orr \temp, \temp, r12
	add \temp, \temp, r8
	add \temp, \temp, r10
	add \temp, \temp, \a, ROR #27
	add \temp, \temp, \e
	ror \b, \b, #2
.endm

	round r5, r6, r7, r9, r3, r4, 160
	round r4, r5, r6, r7, r9, r3, 164
	round r3, r4, r5, r6, r7, r9, 168
	round r9, r3, r4, r5, r6, r7, 172
	round r7, r9, r3, r4, r5, r6, 176
	round r6, r7, r9, r3, r4, r5, 180
	
	round r5, r6, r7, r9, r3, r4, 184
	round r4, r5, r6, r7, r9, r3, 188
	round r3, r4, r5, r6, r7, r9, 192
	round r9, r3, r4, r5, r6, r7, 196
	round r7, r9, r3, r4, r5, r6, 200
	round r6, r7, r9, r3, r4, r5, 204
	
	round r5, r6, r7, r9, r3, r4, 208
	round r4, r5, r6, r7, r9, r3, 212
	round r3, r4, r5, r6, r7, r9, 216
	round r9, r3, r4, r5, r6, r7, 220
	round r7, r9, r3, r4, r5, r6, 224
	round r6, r7, r9, r3, r4, r5, 228
	
	round r5, r6, r7, r9, r3, r4, 232
	round r4, r5, r6, r7, r9, r3, 236

	/* loop 4 */
	ldr r8, =0xCA62C1D6
.purgem round
.macro round a, b, c, d, e, temp, offset_stack
	ldr \temp, [sp, +#((\offset_stack + 52) & 63)]
	ldr r10, [sp, +#((\offset_stack + 32) & 63)]
	ldr r11, [sp, +#((\offset_stack + 8) & 63)]
	ldr r12, [sp, +#(\offset_stack & 63)]
	eor r10, r10, \temp
	eor r11, r11, r12
	eor r10, r10, r11
	ror r10, r10, #31
	str r10, [sp, +#(\offset_stack & 63)]
	eor \temp, \b, \c
	eor \temp, \temp, \d
	add \temp, \temp, r8
	add \temp, \temp, r10
	add \temp, \temp, \a, ROR #27
	add \temp, \temp, \e
	ror \b, \b, #2
.endm

	round r3, r4, r5, r6, r7, r9, 240
	round r9, r3, r4, r5, r6, r7, 244
	round r7, r9, r3, r4, r5, r6, 248
	round r6, r7, r9, r3, r4, r5, 252
	round r5, r6, r7, r9, r3, r4, 256
	round r4, r5, r6, r7, r9, r3, 260
	
	round r3, r4, r5, r6, r7, r9, 264
	round r9, r3, r4, r5, r6, r7, 268
	round r7, r9, r3, r4, r5, r6, 272
	round r6, r7, r9, r3, r4, r5, 276
	round r5, r6, r7, r9, r3, r4, 280
	round r4, r5, r6, r7, r9, r3, 284
	
	round r3, r4, r5, r6, r7, r9, 288
	round r9, r3, r4, r5, r6, r7, 292
	round r7, r9, r3, r4, r5, r6, 296
	round r6, r7, r9, r3, r4, r5, 300
	round r5, r6, r7, r9, r3, r4, 304
	round r4, r5, r6, r7, r9, r3, 308
	
	round r3, r4, r5, r6, r7, r9, 312
	round r9, r3, r4, r5, r6, r7, 316

	mov r6, r4
	mov r4, r9
	mov r9, r7
	mov r7, r5
	mov r5, r3
	mov r3, r9

	ldmia r1, {r8 - r12}
	subs r2, r2, #1
	addne r0, r0, #64
	add r3, r3, r8
	add r4, r4, r9
	add r5, r5, r10
	add r6, r6, r11
	add r7, r7, r12
	stmia r1, {r3 - r7}

	bne .Lstart
	
	add sp, sp, #64
.Lend:	
	pop {r4 - r12}
	bx lr

