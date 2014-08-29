/*
 * sha1_block.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-05-01
 */

.arch armv6

.text
/* FIXME: without this hack the assembler throws errors because the pool is too far */
k1:
	.word 0x5A827999
k2:
	.word 0x6ED9EBA1
	
.global sha1_process_blocks_asm
sha1_process_blocks_asm: /* (uint8_t block[], uint32_t hash[5], uint n) */
	push {r4 - r12}
	cmp r2, #0
	beq .Lend
	sub sp, sp, #320
	
	ldmia r1, {r3 - r7}	
.Lstart:

	ldr r8, k1
	/* loop 1a */
	and r9, r4, r5
	bic r10, r6, r4
	orr r9, r9, r10
	ldr r10, [r0, +#0]
	add r9, r9, r8
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	rev r10, r10
	add r9, r9, r10
	str r10, [sp, +#0]
	ror r4, r4, #2
	
	and r7, r3, r4
	bic r10, r5, r3
	orr r7, r7, r10
	ldr r10, [r0, +#4]
	add r7, r7, r8
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	rev r10, r10
	add r7, r7, r10
	str r10, [sp, +#4]
	mov r3, r3, ROR #2
	
	and r6, r9, r3
	bic r10, r4, r9
	orr r6, r6, r10
	ldr r10, [r0, +#8]
	add r6, r6, r8
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	rev r10, r10
	add r6, r6, r10
	str r10, [sp, +#8]
	mov r9, r9, ROR #2
	
	and r5, r7, r9
	bic r10, r3, r7
	orr r5, r5, r10
	ldr r10, [r0, +#12]
	add r5, r5, r8
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	rev r10, r10
	add r5, r5, r10
	str r10, [sp, +#12]
	mov r7, r7, ROR #2
	
	and r4, r6, r7
	bic r10, r9, r6
	orr r4, r4, r10
	ldr r10, [r0, +#16]
	add r4, r4, r8
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	rev r10, r10
	add r4, r4, r10
	str r10, [sp, +#16]
	mov r6, r6, ROR #2
	
	and r3, r5, r6
	bic r10, r7, r5
	orr r3, r3, r10
	ldr r10, [r0, +#20]
	add r3, r3, r8
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	rev r10, r10
	add r3, r3, r10
	str r10, [sp, +#20]
	mov r5, r5, ROR #2
	
	and r9, r4, r5
	bic r10, r6, r4
	orr r9, r9, r10
	ldr r10, [r0, +#24]
	add r9, r9, r8
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	rev r10, r10
	add r9, r9, r10
	str r10, [sp, +#24]
	ror r4, r4, #2
	
	and r7, r3, r4
	bic r10, r5, r3
	orr r7, r7, r10
	ldr r10, [r0, +#28]
	add r7, r7, r8
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	rev r10, r10
	add r7, r7, r10
	str r10, [sp, +#28]
	mov r3, r3, ROR #2
	
	and r6, r9, r3
	bic r10, r4, r9
	orr r6, r6, r10
	ldr r10, [r0, +#32]
	add r6, r6, r8
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	rev r10, r10
	add r6, r6, r10
	str r10, [sp, +#32]
	mov r9, r9, ROR #2
	
	and r5, r7, r9
	bic r10, r3, r7
	orr r5, r5, r10
	ldr r10, [r0, +#36]
	add r5, r5, r8
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	rev r10, r10
	add r5, r5, r10
	str r10, [sp, +#36]
	mov r7, r7, ROR #2
	
	and r4, r6, r7
	bic r10, r9, r6
	orr r4, r4, r10
	ldr r10, [r0, +#40]
	add r4, r4, r8
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	rev r10, r10
	add r4, r4, r10
	str r10, [sp, +#40]
	mov r6, r6, ROR #2
	
	and r3, r5, r6
	bic r10, r7, r5
	orr r3, r3, r10
	ldr r10, [r0, +#44]
	add r3, r3, r8
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	rev r10, r10
	add r3, r3, r10
	str r10, [sp, +#44]
	mov r5, r5, ROR #2
	
	and r9, r4, r5
	bic r10, r6, r4
	orr r9, r9, r10
	ldr r10, [r0, +#48]
	add r9, r9, r8
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	rev r10, r10
	add r9, r9, r10
	str r10, [sp, +#48]
	ror r4, r4, #2
	
	and r7, r3, r4
	bic r10, r5, r3
	orr r7, r7, r10
	ldr r10, [r0, +#52]
	add r7, r7, r8
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	rev r10, r10
	add r7, r7, r10
	str r10, [sp, +#52]
	mov r3, r3, ROR #2
	
	and r6, r9, r3
	bic r10, r4, r9
	orr r6, r6, r10
	ldr r10, [r0, +#56]
	add r6, r6, r8
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	rev r10, r10
	add r6, r6, r10
	str r10, [sp, +#56]
	mov r9, r9, ROR #2
	
	and r5, r7, r9
	bic r10, r3, r7
	orr r5, r5, r10
	ldr r10, [r0, +#60]
	add r5, r5, r8
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	rev r10, r10
	add r5, r5, r10
	str r10, [sp, +#60]
	mov r7, r7, ROR #2

	/* loop 1b */
	ldr r4, [sp, +#52]
	ldr r10, [sp, +#32]
	ldr r11, [sp, +#8]
	ldr r12, [sp, +#0]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#64]
	and r4, r6, r7
	bic r10, r9, r6
	orr r4, r4, r10
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#56]
	ldr r10, [sp, +#36]
	ldr r11, [sp, +#12]
	ldr r12, [sp, +#4]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#68]
	and r3, r5, r6
	bic r10, r7, r5
	orr r3, r3, r10
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2
	
	ldr r9, [sp, +#60]
	ldr r10, [sp, +#40]
	ldr r11, [sp, +#16]
	ldr r12, [sp, +#8]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#72]
	and r9, r4, r5
	bic r10, r6, r4
	orr r9, r9, r10
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#64]
	ldr r10, [sp, +#44]
	ldr r11, [sp, +#20]
	ldr r12, [sp, +#12]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#76]
	and r7, r3, r4
	bic r10, r5, r3
	orr r7, r7, r10
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2
	
	/* loop 2 */
	ldr r8, k2
	ldr r6, [sp, +#68]
	ldr r10, [sp, +#48]
	ldr r11, [sp, +#24]
	ldr r12, [sp, +#16]
	eor r10, r10, r6
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#80]
	eor r6, r9, r3
	eor r6, r6, r4
	add r6, r6, r8
	add r6, r6, r11
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	ror r9, r9, #2
	
	ldr r5, [sp, +#72]
	ldr r10, [sp, +#52]
	ldr r11, [sp, +#28]
	ldr r12, [sp, +#20]
	eor r10, r10, r5
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#84]
	eor r5, r7, r9
	eor r5, r5, r3
	add r5, r5, r8
	add r5, r5, r11
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	ror r7, r7, #2
	
	ldr r4, [sp, +#76]
	ldr r10, [sp, +#56]
	ldr r11, [sp, +#32]
	ldr r12, [sp, +#24]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#88]
	eor r4, r6, r7
	eor r4, r4, r9
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#80]
	ldr r10, [sp, +#60]
	ldr r11, [sp, +#36]
	ldr r12, [sp, +#28]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#92]
	eor r3, r5, r6
	eor r3, r3, r7
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2
	
	ldr r9, [sp, +#84]
	ldr r10, [sp, +#64]
	ldr r11, [sp, +#40]
	ldr r12, [sp, +#32]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#96]
	eor r9, r4, r5
	eor r9, r9, r6
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#88]
	ldr r10, [sp, +#68]
	ldr r11, [sp, +#44]
	ldr r12, [sp, +#36]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#100]
	eor r7, r3, r4
	eor r7, r7, r5
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2
	
	ldr r6, [sp, +#92]
	ldr r10, [sp, +#72]
	ldr r11, [sp, +#48]
	ldr r12, [sp, +#40]
	eor r10, r10, r6
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#104]
	eor r6, r9, r3
	eor r6, r6, r4
	add r6, r6, r8
	add r6, r6, r11
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	ror r9, r9, #2
	
	ldr r5, [sp, +#96]
	ldr r10, [sp, +#76]
	ldr r11, [sp, +#52]
	ldr r12, [sp, +#44]
	eor r10, r10, r5
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#108]
	eor r5, r7, r9
	eor r5, r5, r3
	add r5, r5, r8
	add r5, r5, r11
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	ror r7, r7, #2
	
	ldr r4, [sp, +#100]
	ldr r10, [sp, +#80]
	ldr r11, [sp, +#56]
	ldr r12, [sp, +#48]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#112]
	eor r4, r6, r7
	eor r4, r4, r9
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#104]
	ldr r10, [sp, +#84]
	ldr r11, [sp, +#60]
	ldr r12, [sp, +#52]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#116]
	eor r3, r5, r6
	eor r3, r3, r7
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2
	
	ldr r9, [sp, +#108]
	ldr r10, [sp, +#88]
	ldr r11, [sp, +#64]
	ldr r12, [sp, +#56]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#120]
	eor r9, r4, r5
	eor r9, r9, r6
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#112]
	ldr r10, [sp, +#92]
	ldr r11, [sp, +#68]
	ldr r12, [sp, +#60]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#124]
	eor r7, r3, r4
	eor r7, r7, r5
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2
	
	ldr r6, [sp, +#116]
	ldr r10, [sp, +#96]
	ldr r11, [sp, +#72]
	ldr r12, [sp, +#64]
	eor r10, r10, r6
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#128]
	eor r6, r9, r3
	eor r6, r6, r4
	add r6, r6, r8
	add r6, r6, r11
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	ror r9, r9, #2
	
	ldr r5, [sp, +#120]
	ldr r10, [sp, +#100]
	ldr r11, [sp, +#76]
	ldr r12, [sp, +#68]
	eor r10, r10, r5
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#132]
	eor r5, r7, r9
	eor r5, r5, r3
	add r5, r5, r8
	add r5, r5, r11
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	ror r7, r7, #2
	
	ldr r4, [sp, +#124]
	ldr r10, [sp, +#104]
	ldr r11, [sp, +#80]
	ldr r12, [sp, +#72]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#136]
	eor r4, r6, r7
	eor r4, r4, r9
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#128]
	ldr r10, [sp, +#108]
	ldr r11, [sp, +#84]
	ldr r12, [sp, +#76]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#140]
	eor r3, r5, r6
	eor r3, r3, r7
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2
	
	ldr r9, [sp, +#132]
	ldr r10, [sp, +#112]
	ldr r11, [sp, +#88]
	ldr r12, [sp, +#80]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#144]
	eor r9, r4, r5
	eor r9, r9, r6
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#136]
	ldr r10, [sp, +#116]
	ldr r11, [sp, +#92]
	ldr r12, [sp, +#84]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#148]
	eor r7, r3, r4
	eor r7, r7, r5
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2
	
	ldr r6, [sp, +#140]
	ldr r10, [sp, +#120]
	ldr r11, [sp, +#96]
	ldr r12, [sp, +#88]
	eor r10, r10, r6
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#152]
	eor r6, r9, r3
	eor r6, r6, r4
	add r6, r6, r8
	add r6, r6, r11
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	ror r9, r9, #2
	
	ldr r5, [sp, +#144]
	ldr r10, [sp, +#124]
	ldr r11, [sp, +#100]
	ldr r12, [sp, +#92]
	eor r10, r10, r5
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#156]
	eor r5, r7, r9
	eor r5, r5, r3
	add r5, r5, r8
	add r5, r5, r11
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	ror r7, r7, #2

	/* loop 3 */
	ldr r8, =0x8F1BBCDC
.Lloop3_start:
	ldr r4, [sp, +#148]
	ldr r10, [sp, +#128]
	ldr r11, [sp, +#104]
	ldr r12, [sp, +#96]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#160]
	and r4, r6, r7
	and r10, r6, r9
	and r12, r7, r9
	orr r10, r10, r12
	orr r4, r4, r10
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#152]
	ldr r10, [sp, +#132]
	ldr r11, [sp, +#108]
	ldr r12, [sp, +#100]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#164]
	and r3, r5, r6
	and r10, r5, r7
	and r12, r6, r7
	orr r10, r10, r12
	orr r3, r3, r10
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2
	
	ldr r9, [sp, +#156]
	ldr r10, [sp, +#136]
	ldr r11, [sp, +#112]
	ldr r12, [sp, +#104]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#168]
	and r9, r4, r5
	and r10, r4, r6
	and r12, r5, r6
	orr r10, r10, r12
	orr r9, r9, r10
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#160]
	ldr r10, [sp, +#140]
	ldr r11, [sp, +#116]
	ldr r12, [sp, +#108]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#172]
	and r7, r3, r4
	and r10, r3, r5
	and r12, r4, r5
	orr r10, r10, r12
	orr r7, r7, r10
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2
	
	ldr r6, [sp, +#164]
	ldr r10, [sp, +#144]
	ldr r11, [sp, +#120]
	ldr r12, [sp, +#112]
	eor r10, r10, r6
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#176]
	and r6, r9, r3
	and r10, r9, r4
	and r12, r3, r4
	orr r10, r10, r12
	orr r6, r6, r10
	add r6, r6, r8
	add r6, r6, r11
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	ror r9, r9, #2
	
	ldr r5, [sp, +#168]
	ldr r10, [sp, +#148]
	ldr r11, [sp, +#124]
	ldr r12, [sp, +#116]
	eor r10, r10, r5
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#180]
	and r5, r7, r9
	and r10, r7, r3
	and r12, r9, r3
	orr r10, r10, r12
	orr r5, r5, r10
	add r5, r5, r8
	add r5, r5, r11
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	ror r7, r7, #2
	
	ldr r4, [sp, +#172]
	ldr r10, [sp, +#152]
	ldr r11, [sp, +#128]
	ldr r12, [sp, +#120]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#184]
	and r4, r6, r7
	and r10, r6, r9
	and r12, r7, r9
	orr r10, r10, r12
	orr r4, r4, r10
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#176]
	ldr r10, [sp, +#156]
	ldr r11, [sp, +#132]
	ldr r12, [sp, +#124]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#188]
	and r3, r5, r6
	and r10, r5, r7
	and r12, r6, r7
	orr r10, r10, r12
	orr r3, r3, r10
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2
	
	ldr r9, [sp, +#180]
	ldr r10, [sp, +#160]
	ldr r11, [sp, +#136]
	ldr r12, [sp, +#128]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#192]
	and r9, r4, r5
	and r10, r4, r6
	and r12, r5, r6
	orr r10, r10, r12
	orr r9, r9, r10
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#184]
	ldr r10, [sp, +#164]
	ldr r11, [sp, +#140]
	ldr r12, [sp, +#132]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#196]
	and r7, r3, r4
	and r10, r3, r5
	and r12, r4, r5
	orr r10, r10, r12
	orr r7, r7, r10
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2
	
	ldr r6, [sp, +#188]
	ldr r10, [sp, +#168]
	ldr r11, [sp, +#144]
	ldr r12, [sp, +#136]
	eor r10, r10, r6
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#200]
	and r6, r9, r3
	and r10, r9, r4
	and r12, r3, r4
	orr r10, r10, r12
	orr r6, r6, r10
	add r6, r6, r8
	add r6, r6, r11
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	ror r9, r9, #2
	
	ldr r5, [sp, +#192]
	ldr r10, [sp, +#172]
	ldr r11, [sp, +#148]
	ldr r12, [sp, +#140]
	eor r10, r10, r5
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#204]
	and r5, r7, r9
	and r10, r7, r3
	and r12, r9, r3
	orr r10, r10, r12
	orr r5, r5, r10
	add r5, r5, r8
	add r5, r5, r11
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	ror r7, r7, #2
	
	ldr r4, [sp, +#196]
	ldr r10, [sp, +#176]
	ldr r11, [sp, +#152]
	ldr r12, [sp, +#144]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#208]
	and r4, r6, r7
	and r10, r6, r9
	and r12, r7, r9
	orr r10, r10, r12
	orr r4, r4, r10
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#200]
	ldr r10, [sp, +#180]
	ldr r11, [sp, +#156]
	ldr r12, [sp, +#148]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#212]
	and r3, r5, r6
	and r10, r5, r7
	and r12, r6, r7
	orr r10, r10, r12
	orr r3, r3, r10
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2
	
	ldr r9, [sp, +#204]
	ldr r10, [sp, +#184]
	ldr r11, [sp, +#160]
	ldr r12, [sp, +#152]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#216]
	and r9, r4, r5
	and r10, r4, r6
	and r12, r5, r6
	orr r10, r10, r12
	orr r9, r9, r10
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#208]
	ldr r10, [sp, +#188]
	ldr r11, [sp, +#164]
	ldr r12, [sp, +#156]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#220]
	and r7, r3, r4
	and r10, r3, r5
	and r12, r4, r5
	orr r10, r10, r12
	orr r7, r7, r10
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2
	
	ldr r6, [sp, +#212]
	ldr r10, [sp, +#192]
	ldr r11, [sp, +#168]
	ldr r12, [sp, +#160]
	eor r10, r10, r6
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#224]
	and r6, r9, r3
	and r10, r9, r4
	and r12, r3, r4
	orr r10, r10, r12
	orr r6, r6, r10
	add r6, r6, r8
	add r6, r6, r11
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	ror r9, r9, #2
	
	ldr r5, [sp, +#216]
	ldr r10, [sp, +#196]
	ldr r11, [sp, +#172]
	ldr r12, [sp, +#164]
	eor r10, r10, r5
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#228]
	and r5, r7, r9
	and r10, r7, r3
	and r12, r9, r3
	orr r10, r10, r12
	orr r5, r5, r10
	add r5, r5, r8
	add r5, r5, r11
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	ror r7, r7, #2
	
	ldr r4, [sp, +#220]
	ldr r10, [sp, +#200]
	ldr r11, [sp, +#176]
	ldr r12, [sp, +#168]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#232]
	and r4, r6, r7
	and r10, r6, r9
	and r12, r7, r9
	orr r10, r10, r12
	orr r4, r4, r10
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#224]
	ldr r10, [sp, +#204]
	ldr r11, [sp, +#180]
	ldr r12, [sp, +#172]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#236]
	and r3, r5, r6
	and r10, r5, r7
	and r12, r6, r7
	orr r10, r10, r12
	orr r3, r3, r10
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2

	/* loop 4 */
	ldr r8, =0xCA62C1D6
	ldr r9, [sp, +#228]
	ldr r10, [sp, +#208]
	ldr r11, [sp, +#184]
	ldr r12, [sp, +#176]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#240]
	eor r9, r4, r5
	eor r9, r9, r6
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#232]
	ldr r10, [sp, +#212]
	ldr r11, [sp, +#188]
	ldr r12, [sp, +#180]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#244]
	eor r7, r3, r4
	eor r7, r7, r5
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2
	
	ldr r6, [sp, +#236]
	ldr r10, [sp, +#216]
	ldr r11, [sp, +#192]
	ldr r12, [sp, +#184]
	eor r10, r10, r6
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#248]
	eor r6, r9, r3
	eor r6, r6, r4
	add r6, r6, r8
	add r6, r6, r11
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	ror r9, r9, #2
	
	ldr r5, [sp, +#240]
	ldr r10, [sp, +#220]
	ldr r11, [sp, +#196]
	ldr r12, [sp, +#188]
	eor r10, r10, r5
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#252]
	eor r5, r7, r9
	eor r5, r5, r3
	add r5, r5, r8
	add r5, r5, r11
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	ror r7, r7, #2
	
	ldr r4, [sp, +#244]
	ldr r10, [sp, +#224]
	ldr r11, [sp, +#200]
	ldr r12, [sp, +#192]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#256]
	eor r4, r6, r7
	eor r4, r4, r9
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#248]
	ldr r10, [sp, +#228]
	ldr r11, [sp, +#204]
	ldr r12, [sp, +#196]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#260]
	eor r3, r5, r6
	eor r3, r3, r7
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2
	
	ldr r9, [sp, +#252]
	ldr r10, [sp, +#232]
	ldr r11, [sp, +#208]
	ldr r12, [sp, +#200]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#264]
	eor r9, r4, r5
	eor r9, r9, r6
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#256]
	ldr r10, [sp, +#236]
	ldr r11, [sp, +#212]
	ldr r12, [sp, +#204]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#268]
	eor r7, r3, r4
	eor r7, r7, r5
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2
	
	ldr r6, [sp, +#260]
	ldr r10, [sp, +#240]
	ldr r11, [sp, +#216]
	ldr r12, [sp, +#208]
	eor r10, r10, r6
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#272]
	eor r6, r9, r3
	eor r6, r6, r4
	add r6, r6, r8
	add r6, r6, r11
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	ror r9, r9, #2
	
	ldr r5, [sp, +#264]
	ldr r10, [sp, +#244]
	ldr r11, [sp, +#220]
	ldr r12, [sp, +#212]
	eor r10, r10, r5
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#276]
	eor r5, r7, r9
	eor r5, r5, r3
	add r5, r5, r8
	add r5, r5, r11
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	ror r7, r7, #2
	
	ldr r4, [sp, +#268]
	ldr r10, [sp, +#248]
	ldr r11, [sp, +#224]
	ldr r12, [sp, +#216]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#280]
	eor r4, r6, r7
	eor r4, r4, r9
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#272]
	ldr r10, [sp, +#252]
	ldr r11, [sp, +#228]
	ldr r12, [sp, +#220]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#284]
	eor r3, r5, r6
	eor r3, r3, r7
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2
	
	ldr r9, [sp, +#276]
	ldr r10, [sp, +#256]
	ldr r11, [sp, +#232]
	ldr r12, [sp, +#224]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#288]
	eor r9, r4, r5
	eor r9, r9, r6
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#280]
	ldr r10, [sp, +#260]
	ldr r11, [sp, +#236]
	ldr r12, [sp, +#228]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#292]
	eor r7, r3, r4
	eor r7, r7, r5
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2
	
	ldr r6, [sp, +#284]
	ldr r10, [sp, +#264]
	ldr r11, [sp, +#240]
	ldr r12, [sp, +#232]
	eor r10, r10, r6
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#296]
	eor r6, r9, r3
	eor r6, r6, r4
	add r6, r6, r8
	add r6, r6, r11
	add r6, r6, r7, ROR #27
	add r6, r6, r5
	ror r9, r9, #2
	
	ldr r5, [sp, +#288]
	ldr r10, [sp, +#268]
	ldr r11, [sp, +#244]
	ldr r12, [sp, +#236]
	eor r10, r10, r5
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#300]
	eor r5, r7, r9
	eor r5, r5, r3
	add r5, r5, r8
	add r5, r5, r11
	add r5, r5, r6, ROR #27
	add r5, r5, r4
	ror r7, r7, #2
	
	ldr r4, [sp, +#292]
	ldr r10, [sp, +#272]
	ldr r11, [sp, +#248]
	ldr r12, [sp, +#240]
	eor r10, r10, r4
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#304]
	eor r4, r6, r7
	eor r4, r4, r9
	add r4, r4, r8
	add r4, r4, r11
	add r4, r4, r5, ROR #27
	add r4, r4, r3
	ror r6, r6, #2
	
	ldr r3, [sp, +#296]
	ldr r10, [sp, +#276]
	ldr r11, [sp, +#252]
	ldr r12, [sp, +#244]
	eor r10, r10, r3
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#308]
	eor r3, r5, r6
	eor r3, r3, r7
	add r3, r3, r8
	add r3, r3, r11
	add r3, r3, r4, ROR #27
	add r3, r3, r9
	ror r5, r5, #2
	
	ldr r9, [sp, +#300]
	ldr r10, [sp, +#280]
	ldr r11, [sp, +#256]
	ldr r12, [sp, +#248]
	eor r10, r10, r9
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#312]
	eor r9, r4, r5
	eor r9, r9, r6
	add r9, r9, r8
	add r9, r9, r11
	add r9, r9, r3, ROR #27
	add r9, r9, r7
	ror r4, r4, #2
	
	ldr r7, [sp, +#304]
	ldr r10, [sp, +#284]
	ldr r11, [sp, +#260]
	ldr r12, [sp, +#252]
	eor r10, r10, r7
	eor r11, r11, r12
	eor r11, r11, r10
	ror r11, r11, #31
	str r11, [sp, +#316]
	eor r7, r3, r4
	eor r7, r7, r5
	add r7, r7, r8
	add r7, r7, r11
	add r7, r7, r9, ROR #27
	add r7, r7, r6
	ror r3, r3, #2	

	/* FIXME: merge this mov block with the add block below */
	mov r6, r4
	mov r4, r9
	mov r9, r7
	mov r7, r5
	mov r5, r3
	mov r3, r9

	ldmia r1, {r8 - r12}
	add r3, r3, r8
	add r4, r4, r9
	add r5, r5, r10
	add r6, r6, r11
	add r7, r7, r12
	stmia r1, {r3 - r7}
	
	subs r2, r2, #1
	addne r0, r0, #64
	bne .Lstart
	
	add sp, sp, #320
.Lend:	
	pop {r4 - r12}
	bx lr
