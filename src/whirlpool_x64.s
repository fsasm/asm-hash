/*
 * whirlpool_x64.s
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-01
 */

.intel_syntax noprefix

.include "whirlpool_tables64.s"

.text

.global whirlpool_process_blocks_asm
.type whirlpool_process_blocks_asm, %function
whirlpool_process_blocks_asm: /* (rdi: uint8_t block[], rsi: uint8_t hash[8][8], rdx: unsigned int n) */
	cmp rdx, 0
	je .Lend

	push rbx
	push rbp
	push r12
	push r13
	push r14
	push r15

	sub rsp, 128 /* [0:63]key + [64:127]state */
	
	/* single table approach */
.Lstart:

	/* memcpy(key, hash), state = rev(block) ^ key; */
	mov rcx, 8
.Lsetup:
	mov rbx, [rsi + rcx * 8 - 8] 
	mov [rsp + rcx * 8 - 8], rbx /* key[i] = hash[i] */
	mov r8, [rdi + rcx * 8 - 8]
	bswap r8
	xor r8, rbx
	mov [rsp + rcx * 8 + 56], r8 /* state[i] = rev(block[i]) ^ key[i] */
	loop .Lsetup

	mov rcx, 10
.Lloop:
	/*
	 * rax:
	 * rbx: t1
	 * rcx: loop counter 
	 * rdx: block counter
	 * rsp: stack pointer
	 * rbp:
	 * rsi: hash
	 * rdi: block
	 * r8 : tmp[0]
	 * r9 : tmp[1]
	 * r10: tmp[2]
	 * r11: tmp[3]
	 * r12: tmp[4]
	 * r13: tmp[5]
	 * r14: tmp[6]
	 * r15: tmp[7]
	 */

.macro key0 reg, shift, rot
	mov rbx, rax
.if \shift == 0
	and rbx, 0xFF
	mov \reg, whirlpool_tables[8 * rbx]
.else
	shr rbx, (\shift - 3)
	and rbx, 0x07F8
	mov \reg, whirlpool_tables[rbx]
.endif
.if \rot > 0
	ror \reg, \rot
.endif
.endm

.macro keyX reg, shift, rot
	mov rbx, rax
.if \shift == 0
	and rbx, 0xFF
	mov rbx, whirlpool_tables[8 * rbx]
.else
	shr rbx, (\shift - 3)
	and rbx, 0x07F8
	mov rbx, whirlpool_tables[rbx]
.endif
.if \rot > 0
	ror rbx, \rot
.endif
	xor \reg, rbx
.endm

	mov rax, [rsp + 0] /* key[0] */
	key0 r8,  56,  0
	key0 r9,  48,  8
	key0 r10, 40, 16
	key0 r11, 32, 24
	key0 r12, 24, 32
	key0 r13, 16, 40
	key0 r14,  8, 48
	key0 r15,  0, 56

	mov rax, [rsp + 8] /* key[1] */
	keyX r8,   0, 56
	keyX r9,  56,  0
	keyX r10, 48,  8
	keyX r11, 40, 16
	keyX r12, 32, 24
	keyX r13, 24, 32
	keyX r14, 16, 40
	keyX r15,  8, 48
	
	mov rax, [rsp + 16] /* key[2] */
	keyX r8,   8, 48
	keyX r9,   0, 56
	keyX r10, 56,  0
	keyX r11, 48,  8
	keyX r12, 40, 16
	keyX r13, 32, 24
	keyX r14, 24, 32
	keyX r15, 16, 40

	mov rax, [rsp + 24] /* key[3] */
	keyX r8,  16, 40
	keyX r9,   8, 48
	keyX r10,  0, 56
	keyX r11, 56,  0
	keyX r12, 48,  8
	keyX r13, 40, 16
	keyX r14, 32, 24
	keyX r15, 24, 32
	
	mov rax, [rsp + 32] /* key[4] */
	keyX r8,  24, 32
	keyX r9,  16, 40
	keyX r10,  8, 48
	keyX r11,  0, 56
	keyX r12, 56,  0
	keyX r13, 48,  8
	keyX r14, 40, 16
	keyX r15, 32, 24
	
	mov rax, [rsp + 40] /* key[5] */
	keyX r8,  32, 24
	keyX r9,  24, 32
	keyX r10, 16, 40
	keyX r11,  8, 48
	keyX r12,  0, 56
	keyX r13, 56,  0
	keyX r14, 48,  8
	keyX r15, 40, 16

	mov rax, [rsp + 48] /* key[6] */
	keyX r8,  40, 16
	keyX r9,  32, 24
	keyX r10, 24, 32
	keyX r11, 16, 40
	keyX r12,  8, 48
	keyX r13,  0, 56
	keyX r14, 56,  0
	keyX r15, 48,  8
	
	mov rax, [rsp + 56] /* key[7] */
	keyX r8,  48,  8
	keyX r9,  40, 16
	keyX r10, 32, 24
	keyX r11, 24, 32
	keyX r12, 16, 40
	keyX r13,  8, 48
	keyX r14,  0, 56
	keyX r15, 56,  0

	/* round constant */
	mov rbx, 10
	sub rbx, rcx
	mov rbx, whirlpool_round_const[rbx * 8]
	xor r8, rbx

	mov [rsp + 0], r8
	mov [rsp + 8], r9
	mov [rsp + 16], r10
	mov [rsp + 24], r11
	mov [rsp + 32], r12
	mov [rsp + 40], r13
	mov [rsp + 48], r14
	mov [rsp + 56], r15

	/* state */
.macro stateX reg, shift, rot
	mov rbx, rax
.if \shift == 0
	and rbx, 0xFF
	mov rbx, whirlpool_tables[8 * rbx]
.else
	shr rbx, (\shift - 3)
	and rbx, 0x07F8
	mov rbx, whirlpool_tables[rbx]
.endif
.if \rot > 0
	ror rbx, \rot
.endif
	xor \reg, rbx
.endm

	mov rax, [rsp + 64] /* state[0] */
	stateX r8,  56,  0
	stateX r9,  48,  8
	stateX r10, 40, 16
	stateX r11, 32, 24
	stateX r12, 24, 32
	stateX r13, 16, 40
	stateX r14,  8, 48
	stateX r15,  0, 56

	mov rax, [rsp + 72] /* state[1] */
	stateX r8,   0, 56
	stateX r9,  56,  0
	stateX r10, 48,  8
	stateX r11, 40, 16
	stateX r12, 32, 24
	stateX r13, 24, 32
	stateX r14, 16, 40
	stateX r15,  8, 48
	
	mov rax, [rsp + 80] /* state[2] */
	stateX r8,   8, 48
	stateX r9,   0, 56
	stateX r10, 56,  0
	stateX r11, 48,  8
	stateX r12, 40, 16
	stateX r13, 32, 24
	stateX r14, 24, 32
	stateX r15, 16, 40

	mov rax, [rsp + 88] /* state[3] */
	stateX r8,  16, 40
	stateX r9,   8, 48
	stateX r10,  0, 56
	stateX r11, 56,  0
	stateX r12, 48,  8
	stateX r13, 40, 16
	stateX r14, 32, 24
	stateX r15, 24, 32
	
	mov rax, [rsp + 96] /* state[4] */
	stateX r8,  24, 32
	stateX r9,  16, 40
	stateX r10,  8, 48
	stateX r11,  0, 56
	stateX r12, 56,  0
	stateX r13, 48,  8
	stateX r14, 40, 16
	stateX r15, 32, 24
	
	mov rax, [rsp + 104] /* state[5] */
	stateX r8,  32, 24
	stateX r9,  24, 32
	stateX r10, 16, 40
	stateX r11,  8, 48
	stateX r12,  0, 56
	stateX r13, 56,  0
	stateX r14, 48,  8
	stateX r15, 40, 16

	mov rax, [rsp + 112] /* state[6] */
	stateX r8,  40, 16
	stateX r9,  32, 24
	stateX r10, 24, 32
	stateX r11, 16, 40
	stateX r12,  8, 48
	stateX r13,  0, 56
	stateX r14, 56,  0
	stateX r15, 48,  8
	
	mov rax, [rsp + 120] /* state[7] */
	stateX r8,  48,  8
	stateX r9,  40, 16
	stateX r10, 32, 24
	stateX r11, 24, 32
	stateX r12, 16, 40
	stateX r13,  8, 48
	stateX r14,  0, 56
	stateX r15, 56,  0

	mov [rsp +  64], r8
	mov [rsp +  72], r9
	mov [rsp +  80], r10
	mov [rsp +  88], r11
	mov [rsp +  96], r12
	mov [rsp + 104], r13
	mov [rsp + 112], r14
	mov [rsp + 120], r15

	dec rcx
	jnz .Lloop

	/* after loop */
	/* hash[i] ^= state[x] ^ rev(block[i]); */
.macro wb reg, offset
	mov rbx, [rdi + \offset]
	bswap rbx
	xor \reg, rbx
	mov rbx, [rsi + \offset]
	xor \reg, rbx
	mov [rsi + \offset], \reg
.endm

	wb  r8,  0
	wb  r9,  8
	wb r10, 16
	wb r11, 24
	wb r12, 32
	wb r13, 40
	wb r14, 48
	wb r15, 56

	add rdi, 64
	dec rdx
	jnz .Lstart

	add rsp, 128
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	pop rbx

.Lend:
	ret

