/*
 * sha1_block.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-05-01
 */

.arch armv6

.text
.global sha1_process_block_asm
sha1_process_block_asm: /* (uint8_t block[64], uint32_t hash[5]) */
	push {r4, r5, r6, r7, r8, r9, r10, r11}
	ldmia r1, {r2 - r6}	
	mov r7, #0
	sub sp, sp, #320
	
.Lloop0_start:
	ldr r8, [r0, r7, LSL #2]
	rev r8, r8
	str r8, [sp, r7, LSL #2]
	add r7, r7, #1
.Lloop0_check:
	cmp r7, #16
	blt .Lloop0_start

.Lloop1_start:
	sub r8, r7, #3
	ldr r9, [sp, r8, LSL #2]
	sub r8, r7, #8
	ldr r10, [sp, r8, LSL #2]
	eor r9, r9, r10
	sub r8, r7, #14
	ldr r10, [sp, r8, LSL #2]
	eor r9, r9, r10
	sub r8, r7, #16
	ldr r10, [sp, r8, LSL #2]
	eor r9, r9, r10
	ror r9, r9, #31
	str r9, [sp, r7, LSL #2]
	
	add r7, r7, #1
	
.Lloop1_check:
	cmp r7, #80
	blt .Lloop1_start
	
	mov r7, #0
.Lloop2_start:
	/* r8 = f */
	and r8, r3, r4
	bic r9, r5, r3
	orr r8, r8, r9
	/* r9 = k (0x5A827999) */
	ldr r9, =0x5A827999
	add r8, r8, r9
	add r8, r8, r2, ROR #27
	add r8, r8, r6
	ldr r9, [sp, r7, LSL #2]
	add r8, r8, r9
	
	mov r6, r5
	mov r5, r4
	mov r4, r3, ROR #2
	mov r3, r2
	mov r2, r8
	
	add r7, r7, #1
	
.Lloop2_check:
	cmp r7, #20
	blt .Lloop2_start
	
.Lloop3_start:
	/* r8 = f */
	eor r8, r3, r4
	eor r8, r8, r5
	/* r9 = k (0x6ED9EBA1) */
	ldr r9, =0x6ED9EBA1
	add r8, r8, r9
	add r8, r8, r2, ROR #27
	add r8, r8, r6
	ldr r9, [sp, r7, LSL #2]
	add r8, r8, r9
	
	mov r6, r5
	mov r5, r4
	mov r4, r3, ROR #2
	mov r3, r2
	mov r2, r8
	
	add r7, r7, #1
.Lloop3_check:
	cmp r7, #40
	blt .Lloop3_start
	
.Lloop4_start:
	/* r8 = f */
	and r8, r3, r4
	and r9, r3, r5
	orr r8, r8, r9
	and r9, r4, r5
	orr r8, r8, r9
	
	/* r9 = k (0x8F1BBCDC) */
	ldr r9, =0x8F1BBCDC
	add r8, r8, r9
	add r8, r8, r2, ROR #27
	add r8, r8, r6
	ldr r9, [sp, r7, LSL #2]
	add r8, r8, r9
	
	mov r6, r5
	mov r5, r4
	mov r4, r3, ROR #2
	mov r3, r2
	mov r2, r8
	
	add r7, r7, #1
.Lloop4_check:
	cmp r7, #60
	blt .Lloop4_start
	
.Lloop5_start:
	/* r8 = f */
	eor r8, r3, r4
	eor r8, r8, r5
	
	/* r9 = k (0xCA62C1D6) */
	ldr r9, =0xCA62C1D6
	add r8, r8, r9
	add r8, r8, r2, ROR #27
	add r8, r8, r6
	ldr r9, [sp, r7, LSL #2]
	add r8, r8, r9
	
	mov r6, r5
	mov r5, r4
	mov r4, r3, ROR #2
	mov r3, r2
	mov r2, r8
	
	add r7, r7, #1
	
.Lloop5_check:
	cmp r7, #80
	blt .Lloop5_start	
	
	ldmia r1, {r7 - r11}
	add r2, r2, r7
	add r3, r3, r8
	add r4, r4, r9
	add r5, r5, r10
	add r6, r6, r11
	stmia r1, {r2 - r6}
	
	add sp, sp, #320
	
	pop {r4, r5, r6, r7, r8, r9, r10, r11}
	bx lr
