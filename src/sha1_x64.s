/*
 * sha1_x64.s
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-10-13
 */

.intel_syntax noprefix

.text
.global sha1_process_blocks_asm
.type sha1_process_blocks_asm, %function
sha1_process_blocks_asm: /* (uint8_t block[64], uint32_t hash[5], uint n) */
	/* block: rdi; hash: rsi; n: rdx */
	push rbp
	mov rbp, rsp

	cmp rdx, 0
	je .Lend

	push r12
	push r13
	sub rsp, 64
	
	/* free regs: rcx, eax, */
	/* hash[5]: r8d, r9d, r10d, r11d, r12d,
	   temp: r13d
	   loop counter: rcx maybe unnecassery
	   temp2: eax */
	
.Lstart:

	mov r8d,  [rsi + 0]
	mov r9d,  [rsi + 4]
	mov r10d, [rsi + 8]
	mov r11d, [rsi + 12]
	mov r12d, [rsi + 16]
	
	/* loop 1a */
.macro round a, b, c, d, e, temp, offset_block
	/* f */
	mov \temp, \b
	and \temp, \c
	mov eax, \b
	not eax
	and eax, \d
	or  \temp, eax

	/* temp */
	add \temp, \e
	add \temp, 0x5A827999
	mov eax, [rdi + \offset_block]
	bswap eax
	mov [rsp + \offset_block], eax
	add \temp, eax
	mov eax, \a
	rol eax, 5
	add \temp, eax
	
	ror \b, 2
.endm

	round r8d, r9d, r10d, r11d, r12d, r13d,  0
	round r13d, r8d, r9d, r10d, r11d, r12d,  4
	round r12d, r13d, r8d, r9d, r10d, r11d,  8
	round r11d, r12d, r13d, r8d, r9d, r10d, 12
	round r10d, r11d, r12d, r13d, r8d, r9d, 16
	round r9d, r10d, r11d, r12d, r13d, r8d, 20

	round r8d, r9d, r10d, r11d, r12d, r13d, 24
	round r13d, r8d, r9d, r10d, r11d, r12d, 28
	round r12d, r13d, r8d, r9d, r10d, r11d, 32
	round r11d, r12d, r13d, r8d, r9d, r10d, 36
	round r10d, r11d, r12d, r13d, r8d, r9d, 40
	round r9d, r10d, r11d, r12d, r13d, r8d, 44
	
	round r8d, r9d, r10d, r11d, r12d, r13d, 48
	round r13d, r8d, r9d, r10d, r11d, r12d, 52
	round r12d, r13d, r8d, r9d, r10d, r11d, 56
	round r11d, r12d, r13d, r8d, r9d, r10d, 60
	
	/* loop 1b */
	.purgem round
.macro round a, b, c, d, e, temp, offset_block
	/* f */
	mov \temp, \b
	and \temp, \c
	mov eax, \b
	not eax
	and eax, \d
	or  \temp, eax

	/* W[i] */
	mov eax, [rsp + ((\offset_block + 52) & 63)]
	xor eax, [rsp + ((\offset_block + 32) & 63)]
	xor eax, [rsp + ((\offset_block +  8) & 63)]
	xor eax, [rsp + ((\offset_block +  0) & 63)]
	rol eax, 1
	mov [rsp + (\offset_block & 63)], eax

	/* temp */
	add \temp, \e
	add \temp, 0x5A827999
	add \temp, eax
	mov eax, \a
	rol eax, 5
	add \temp, eax
	
	ror \b, 2
.endm

	round r10d, r11d, r12d, r13d, r8d,  r9d,  64
	round r9d,  r10d, r11d, r12d, r13d, r8d,  68
	round r8d,  r9d,  r10d, r11d, r12d, r13d, 72
	round r13d, r8d,  r9d,  r10d, r11d, r12d, 76
	
	/* loop 2 */
	.purgem round
.macro round a, b, c, d, e, temp, offset_block
	/* f */
	mov \temp, \b
	xor \temp, \c
	xor \temp, \d

	/* W[i] */
	mov eax, [rsp + ((\offset_block + 52) & 63)]
	xor eax, [rsp + ((\offset_block + 32) & 63)]
	xor eax, [rsp + ((\offset_block +  8) & 63)]
	xor eax, [rsp + ((\offset_block +  0) & 63)]
	rol eax, 1
	mov [rsp + (\offset_block & 63)], eax

	/* temp */
	add \temp, \e
	add \temp, 0x6ED9EBA1
	add \temp, eax
	mov eax, \a
	rol eax, 5
	add \temp, eax
	
	ror \b, 2
.endm

	round r12d, r13d, r8d, r9d, r10d, r11d,  80
	round r11d, r12d, r13d, r8d, r9d, r10d,  84
	round r10d, r11d, r12d, r13d, r8d, r9d,  88
	round r9d, r10d, r11d, r12d, r13d, r8d,  92
	
	round r8d, r9d, r10d, r11d, r12d, r13d,  96
	round r13d, r8d, r9d, r10d, r11d, r12d, 100
	round r12d, r13d, r8d, r9d, r10d, r11d, 104
	round r11d, r12d, r13d, r8d, r9d, r10d, 108
	round r10d, r11d, r12d, r13d, r8d, r9d, 112
	round r9d, r10d, r11d, r12d, r13d, r8d, 116

	round r8d, r9d, r10d, r11d, r12d, r13d, 120
	round r13d, r8d, r9d, r10d, r11d, r12d, 124
	round r12d, r13d, r8d, r9d, r10d, r11d, 128
	round r11d, r12d, r13d, r8d, r9d, r10d, 132
	round r10d, r11d, r12d, r13d, r8d, r9d, 136
	round r9d, r10d, r11d, r12d, r13d, r8d, 140

	round r8d, r9d, r10d, r11d, r12d, r13d, 144
	round r13d, r8d, r9d, r10d, r11d, r12d, 148
	round r12d, r13d, r8d, r9d, r10d, r11d, 152
	round r11d, r12d, r13d, r8d, r9d, r10d, 156
	
	/* loop 3 */
	.purgem round
.macro round a, b, c, d, e, temp, offset_block
	/* f */
	mov \temp, \b
	and \temp, \c
	mov eax, \b
	and eax, \d
	or  \temp, eax
	mov eax, \c
	and eax, \d
	or  \temp, eax

	/* W[i] */
	mov eax, [rsp + ((\offset_block + 52) & 63)]
	xor eax, [rsp + ((\offset_block + 32) & 63)]
	xor eax, [rsp + ((\offset_block +  8) & 63)]
	xor eax, [rsp + ((\offset_block +  0) & 63)]
	rol eax, 1
	mov [rsp + (\offset_block & 63)], eax

	/* temp */
	add \temp, \e
	add \temp, 0x8F1BBCDC
	add \temp, eax
	mov eax, \a
	rol eax, 5
	add \temp, eax
	
	ror \b, 2
.endm

	round r10d, r11d, r12d, r13d, r8d, r9d, 160
	round r9d, r10d, r11d, r12d, r13d, r8d, 164

	round r8d, r9d, r10d, r11d, r12d, r13d, 168
	round r13d, r8d, r9d, r10d, r11d, r12d, 172
	round r12d, r13d, r8d, r9d, r10d, r11d, 176
	round r11d, r12d, r13d, r8d, r9d, r10d, 180
	round r10d, r11d, r12d, r13d, r8d, r9d, 184
	round r9d, r10d, r11d, r12d, r13d, r8d, 188

	round r8d, r9d, r10d, r11d, r12d, r13d, 192
	round r13d, r8d, r9d, r10d, r11d, r12d, 196
	round r12d, r13d, r8d, r9d, r10d, r11d, 200
	round r11d, r12d, r13d, r8d, r9d, r10d, 204
	round r10d, r11d, r12d, r13d, r8d, r9d, 208
	round r9d, r10d, r11d, r12d, r13d, r8d, 212

	round r8d, r9d, r10d, r11d, r12d, r13d, 216
	round r13d, r8d, r9d, r10d, r11d, r12d, 220
	round r12d, r13d, r8d, r9d, r10d, r11d, 224
	round r11d, r12d, r13d, r8d, r9d, r10d, 228
	round r10d, r11d, r12d, r13d, r8d, r9d, 232
	round r9d, r10d, r11d, r12d, r13d, r8d, 236
	
	/* loop 4 */
	.purgem round
.macro round a, b, c, d, e, temp, offset_block
	/* f */
	mov \temp, \b
	xor \temp, \c
	xor \temp, \d

	/* W[i] */
	mov eax, [rsp + ((\offset_block + 52) & 63)]
	xor eax, [rsp + ((\offset_block + 32) & 63)]
	xor eax, [rsp + ((\offset_block +  8) & 63)]
	xor eax, [rsp + ((\offset_block +  0) & 63)]
	rol eax, 1
	mov [rsp + (\offset_block & 63)], eax

	/* temp */
	add \temp, \e
	add \temp, 0xCA62C1D6
	add \temp, eax
	mov eax, \a
	rol eax, 5
	add \temp, eax
	
	ror \b, 2
.endm

	round r8d, r9d, r10d, r11d, r12d, r13d, 240
	round r13d, r8d, r9d, r10d, r11d, r12d, 244
	round r12d, r13d, r8d, r9d, r10d, r11d, 248
	round r11d, r12d, r13d, r8d, r9d, r10d, 252
	round r10d, r11d, r12d, r13d, r8d, r9d, 256
	round r9d, r10d, r11d, r12d, r13d, r8d, 260

	round r8d, r9d, r10d, r11d, r12d, r13d, 264
	round r13d, r8d, r9d, r10d, r11d, r12d, 268
	round r12d, r13d, r8d, r9d, r10d, r11d, 272
	round r11d, r12d, r13d, r8d, r9d, r10d, 276
	round r10d, r11d, r12d, r13d, r8d, r9d, 280
	round r9d, r10d, r11d, r12d, r13d, r8d, 284

	round r8d, r9d, r10d, r11d, r12d, r13d, 288
	round r13d, r8d, r9d, r10d, r11d, r12d, 292
	round r12d, r13d, r8d, r9d, r10d, r11d, 296
	round r11d, r12d, r13d, r8d, r9d, r10d, 300
	round r10d, r11d, r12d, r13d, r8d, r9d, 304
	round r9d, r10d, r11d, r12d, r13d, r8d, 308

	round r8d, r9d, r10d, r11d, r12d, r13d, 312
	round r13d, r8d, r9d, r10d, r11d, r12d, 316

.macro add_hash reg, offset
	add \reg, [rsi + \offset]
	mov [rsi + \offset], \reg
.endm

	add_hash r12d,  0
	add_hash r13d,  4
	add_hash r8d,   8
	add_hash r9d,  12
	add_hash r10d, 16

	add rdi, 64
	dec rdx
	jnz .Lstart

	add rsp, 64
	pop r13
	pop r12

.Lend:
	leave
	ret

