/*
 * whirlpool_x64.s
 * Author: Fabjan Sukalia <fsukalia@gmail.com>
 * Date: 2015-07-01
 */

.intel_syntax noprefix

/* multiple table method */
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
.macro table ti, reg
	mov rbx, rax
.if \ti == 7
	and rbx, 0xFF
	mov \reg, whirlpool_table\ti[8 * rbx]
.else
	shr rbx, (56 - (\ti * 8) - 3)
	and rbx, 0x07F8
	mov \reg, whirlpool_table\ti[rbx]
.endif
.endm

.macro tableX ti, reg
	mov rbx, rax
.if \ti == 7
	and rbx, 0xFF
	mov rbx, whirlpool_table\ti[8 * rbx]
.else
	shr rbx, (56 - (\ti * 8) - 3)
	and rbx, 0x07F8
	mov rbx, whirlpool_table\ti[rbx]
.endif
	xor \reg, rbx
.endm

	mov rax, [rsp + 0] /* key[0] */
	table 0, r8
	table 1, r9
	table 2, r10
	table 3, r11
	table 4, r12
	table 5, r13
	table 6, r14
	table 7, r15

	mov rax, [rsp + 8] /* key[1] */
	tableX 7, r8
	tableX 0, r9
	tableX 1, r10
	tableX 2, r11
	tableX 3, r12
	tableX 4, r13
	tableX 5, r14
	tableX 6, r15

	mov rax, [rsp + 16] /* key[2] */
	tableX 6, r8
	tableX 7, r9
	tableX 0, r10
	tableX 1, r11
	tableX 2, r12
	tableX 3, r13
	tableX 4, r14
	tableX 5, r15

	mov rax, [rsp + 24] /* key[3] */
	tableX 5, r8
	tableX 6, r9
	tableX 7, r10
	tableX 0, r11
	tableX 1, r12
	tableX 2, r13
	tableX 3, r14
	tableX 4, r15

	mov rax, [rsp + 32] /* key[4] */
	tableX 4, r8
	tableX 5, r9
	tableX 6, r10
	tableX 7, r11
	tableX 0, r12
	tableX 1, r13
	tableX 2, r14
	tableX 3, r15
	
	mov rax, [rsp + 40] /* key[5] */
	tableX 3, r8
	tableX 4, r9
	tableX 5, r10
	tableX 6, r11
	tableX 7, r12
	tableX 0, r13
	tableX 1, r14
	tableX 2, r15

	mov rax, [rsp + 48] /* key[6] */
	tableX 2, r8
	tableX 3, r9
	tableX 4, r10
	tableX 5, r11
	tableX 6, r12
	tableX 7, r13
	tableX 0, r14
	tableX 1, r15
	
	mov rax, [rsp + 56] /* key[7] */
	tableX 1, r8
	tableX 2, r9
	tableX 3, r10
	tableX 4, r11
	tableX 5, r12
	tableX 6, r13
	tableX 7, r14
	tableX 0, r15

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

	mov rax, [rsp + 64] /* state[0] */
	tableX 0, r8
	tableX 1, r9
	tableX 2, r10
	tableX 3, r11
	tableX 4, r12
	tableX 5, r13
	tableX 6, r14
	tableX 7, r15

	mov rax, [rsp + 72] /* state[1] */
	tableX 7, r8
	tableX 0, r9
	tableX 1, r10
	tableX 2, r11
	tableX 3, r12
	tableX 4, r13
	tableX 5, r14
	tableX 6, r15

	mov rax, [rsp + 80] /* state[2] */
	tableX 6, r8
	tableX 7, r9
	tableX 0, r10
	tableX 1, r11
	tableX 2, r12
	tableX 3, r13
	tableX 4, r14
	tableX 5, r15

	mov rax, [rsp + 88] /* state[3] */
	tableX 5, r8
	tableX 6, r9
	tableX 7, r10
	tableX 0, r11
	tableX 1, r12
	tableX 2, r13
	tableX 3, r14
	tableX 4, r15

	mov rax, [rsp + 96] /* state[4] */
	tableX 4, r8
	tableX 5, r9
	tableX 6, r10
	tableX 7, r11
	tableX 0, r12
	tableX 1, r13
	tableX 2, r14
	tableX 3, r15
	
	mov rax, [rsp + 104] /* state[5] */
	tableX 3, r8
	tableX 4, r9
	tableX 5, r10
	tableX 6, r11
	tableX 7, r12
	tableX 0, r13
	tableX 1, r14
	tableX 2, r15

	mov rax, [rsp + 112] /* state[6] */
	tableX 2, r8
	tableX 3, r9
	tableX 4, r10
	tableX 5, r11
	tableX 6, r12
	tableX 7, r13
	tableX 0, r14
	tableX 1, r15
	
	mov rax, [rsp + 120] /* state[7] */
	tableX 1, r8
	tableX 2, r9
	tableX 3, r10
	tableX 4, r11
	tableX 5, r12
	tableX 6, r13
	tableX 7, r14
	tableX 0, r15

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

