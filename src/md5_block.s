/*
 * md5_block.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-03-28
 */

.arch armv6

.section .rodata
.align 4
md5_table:
	.word 0xD76AA478
	.word 0xE8C7B756
	.word 0x242070DB
	.word 0xC1BDCEEE
	.word 0xF57C0FAF
	.word 0x4787C62A
	.word 0xA8304613
	.word 0xFD469501 /*  8 */
	.word 0x698098D8
	.word 0x8B44F7AF
	.word 0xFFFF5BB1
	.word 0x895CD7BE
	.word 0x6B901122
	.word 0xFD987193
	.word 0xA679438E
	.word 0x49B40821 /* 16 */
	.word 0xF61E2562
	.word 0xC040B340
	.word 0x265E5A51
	.word 0xE9B6C7AA
	.word 0xD62F105D
	.word 0x02441453
	.word 0xD8A1E681
	.word 0xE7D3FBC8 /* 24 */
	.word 0x21E1CDE6
	.word 0xC33707D6
	.word 0xF4D50D87
	.word 0x455A14ED
	.word 0xA9E3E905
	.word 0xFCEFA3F8
	.word 0x676F02D9
	.word 0x8D2A4C8A /* 32 */
	.word 0xFFFA3942
	.word 0x8771F681
	.word 0x6D9D6122
	.word 0xFDE5380C
	.word 0xA4BEEA44
	.word 0x4BDECFA9
	.word 0xF6BB4B60
	.word 0xBEBFBC70 /* 40 */
	.word 0x289B7EC6
	.word 0xEAA127FA
	.word 0xD4EF3085
	.word 0x04881D05
	.word 0xD9D4D039
	.word 0xE6DB99E5
	.word 0x1FA27CF8
	.word 0xC4AC5665 /* 48 */
	.word 0xF4292244
	.word 0x432AFF97
	.word 0xAB9423A7
	.word 0xFC93A039
	.word 0x655B59C3
	.word 0x8F0CCC92
	.word 0xFFEFF47D
	.word 0x85845DD1 /* 56 */
	.word 0x6FA87E4F
	.word 0xFE2CE6E0
	.word 0xA3014314
	.word 0x4E0811A1
	.word 0xF7537E82
	.word 0xBD3AF235
	.word 0x2AD7D2BB
	.word 0xEB86D391 /* 64 */

.text
.global md5_process_blocks_asm
md5_process_blocks_asm: /* (uint8_t block[64], uint32_t hash[4], uint n) */
	push {r4 - r11}
	cmp r2, #0
	beq .Lend
	
	mov r3, r2
	ldr r2, addr_table	
	
.Lstart:
	/* r4 = h0; r5 = h1; r6 = h2; r7 = h3 */
	ldmia  r1, {r4, r5, r6, r7}
	/* first loop */
	ldr r10, [r0, +#0]
	ldr r11, [r2, +#0]
	bic r9, r7, r5
	and r8, r5, r6
	orr r8, r8, r9
	add r4, r4, r8
	add r10, r10, r11
	add r4, r4, r10
	
	ldr r10, [r0, +#4]
	ldr r11, [r2, +#4]
	add r4, r5, r4, ROR #25
	bic r9, r6, r4
	and r8, r4, r5
	orr r8, r8, r9
	add r7, r7, r8
	add r10, r10, r11
	add r7, r7, r10

	ldr r10, [r0, +#8]
	ldr r11, [r2, +#8]
	add r7, r4, r7, ROR #20
	bic r9, r5, r7
	and r8, r7, r4
	orr r8, r8, r9
	add r6, r6, r8
	add r10, r10, r11
	add r6, r6, r10

	ldr r10, [r0, +#12]
	ldr r11, [r2, +#12]
	add r6, r7, r6, ROR #15
	bic r9, r4, r6
	and r8, r6, r7
	orr r8, r8, r9
	add r5, r5, r8
	add r10, r10, r11
	add r5, r5, r10
	
	ldr r10, [r0, +#16]
	ldr r11, [r2, +#16]
	add r5, r6, r5, ROR #10
	bic r9, r7, r5
	and r8, r5, r6
	orr r8, r8, r9
	add r4, r4, r8
	add r10, r10, r11
	add r4, r4, r10

	ldr r10, [r0, +#20]
	ldr r11, [r2, +#20]
	add r4, r5, r4, ROR #25
	bic r9, r6, r4
	and r8, r4, r5
	orr r8, r8, r9
	add r7, r7, r8
	add r10, r10, r11
	add r7, r7, r10

	ldr r10, [r0, +#24]
	ldr r11, [r2, +#24]
	add r7, r4, r7, ROR #20
	bic r9, r5, r7
	and r8, r7, r4
	orr r8, r8, r9
	add r6, r6, r8
	add r10, r10, r11
	add r6, r6, r10

	ldr r10, [r0, +#28]
	ldr r11, [r2, +#28]
	add r6, r7, r6, ROR #15
	bic r9, r4, r6
	and r8, r6, r7
	orr r8, r8, r9
	add r5, r5, r8
	add r10, r10, r11
	add r5, r5, r10
	
	ldr r10, [r0, +#32]
	ldr r11, [r2, +#32]
	add r5, r6, r5, ROR #10
	bic r9, r7, r5
	and r8, r5, r6
	orr r8, r8, r9
	add r4, r4, r8
	add r10, r10, r11
	add r4, r4, r10

	ldr r10, [r0, +#36]
	ldr r11, [r2, +#36]
	add r4, r5, r4, ROR #25
	bic r9, r6, r4
	and r8, r4, r5
	orr r8, r8, r9
	add r7, r7, r8
	add r10, r10, r11
	add r7, r7, r10

	ldr r10, [r0, +#40]
	ldr r11, [r2, +#40]
	add r7, r4, r7, ROR #20
	bic r9, r5, r7
	and r8, r7, r4
	orr r8, r8, r9
	add r6, r6, r8
	add r10, r10, r11
	add r6, r6, r10

	ldr r10, [r0, +#44]
	ldr r11, [r2, +#44]
	add r6, r7, r6, ROR #15
	bic r9, r4, r6
	and r8, r6, r7
	orr r8, r8, r9
	add r5, r5, r8
	add r10, r10, r11
	add r5, r5, r10
	
	ldr r10, [r0, +#48]
	ldr r11, [r2, +#48]
	add r5, r6, r5, ROR #10
	bic r9, r7, r5
	and r8, r5, r6
	orr r8, r8, r9
	add r4, r4, r8
	add r10, r10, r11
	add r4, r4, r10

	ldr r10, [r0, +#52]
	ldr r11, [r2, +#52]
	add r4, r5, r4, ROR #25
	bic r9, r6, r4
	and r8, r4, r5
	orr r8, r8, r9
	add r7, r7, r8
	add r10, r10, r11
	add r7, r7, r10

	ldr r10, [r0, +#56]
	ldr r11, [r2, +#56]
	add r7, r4, r7, ROR #20
	bic r9, r5, r7
	and r8, r7, r4
	orr r8, r8, r9
	add r6, r6, r8
	add r10, r10, r11
	add r6, r6, r10

	ldr r10, [r0, +#60]
	ldr r11, [r2, +#60]
	add r6, r7, r6, ROR #15
	bic r9, r4, r6
	and r8, r6, r7
	orr r8, r8, r9
	add r5, r5, r8
	add r10, r10, r11
	add r5, r5, r10
	
	/* second loop */
	ldr r11, [r2, +#64]
	ldr r10, [r0, +#4]
	add r5, r6, r5, ROR #10
	bic r9, r6, r7
	and r8, r7, r5
	orr r9, r8, r9
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10

	ldr r11, [r2, +#68]
	ldr r10, [r0, +#24]
	add r4, r5, r4, ROR #27
	bic r9, r5, r6
	and r8, r6, r4
	orr r9, r8, r9
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r11, [r2, +#72]
	ldr r10, [r0, +#44]
	add r7, r4, r7, ROR #23
	bic r9, r4, r5
	and r8, r5, r7
	orr r9, r8, r9
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#76]
	ldr r11, [r0, +#0]
	add r6, r7, r6, ROR #18
	bic r9, r7, r4
	and r8, r4, r6
	orr r9, r8, r9
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10
	
	ldr r11, [r2, +#80]
	ldr r10, [r0, +#20]
	add r5, r6, r5, ROR #12
	bic r9, r6, r7
	and r8, r7, r5
	orr r9, r8, r9
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10

	ldr r11, [r2, +#84]
	ldr r10, [r0, +#40]
	add r4, r5, r4, ROR #27
	bic r9, r5, r6
	and r8, r6, r4
	orr r9, r8, r9
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r11, [r2, +#88]
	ldr r10, [r0, +#60]
	add r7, r4, r7, ROR #23
	bic r9, r4, r5
	and r8, r5, r7
	orr r9, r8, r9
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#92]
	ldr r11, [r0, +#16]
	add r6, r7, r6, ROR #18
	bic r9, r7, r4
	and r8, r4, r6
	orr r9, r8, r9
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10
	
	ldr r11, [r2, +#96]
	ldr r10, [r0, +#36]
	add r5, r6, r5, ROR #12
	bic r9, r6, r7
	and r8, r7, r5
	orr r9, r8, r9
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10

	ldr r11, [r2, +#100]
	ldr r10, [r0, +#56]
	add r4, r5, r4, ROR #27
	bic r9, r5, r6
	and r8, r6, r4
	orr r9, r8, r9
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r11, [r2, +#104]
	ldr r10, [r0, +#12]
	add r7, r4, r7, ROR #23
	bic r9, r4, r5
	and r8, r5, r7
	orr r9, r8, r9
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#108]
	ldr r11, [r0, +#32]
	add r6, r7, r6, ROR #18
	bic r9, r7, r4
	and r8, r4, r6
	orr r9, r8, r9
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10
	
	ldr r11, [r2, +#112]
	ldr r10, [r0, +#52]
	add r5, r6, r5, ROR #12
	bic r9, r6, r7
	and r8, r7, r5
	orr r9, r8, r9
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10

	ldr r11, [r2, +#116]
	ldr r10, [r0, +#8]
	add r4, r5, r4, ROR #27
	bic r9, r5, r6
	and r8, r6, r4
	orr r9, r8, r9
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r11, [r2, +#120]
	ldr r10, [r0, +#28]
	add r7, r4, r7, ROR #23
	bic r9, r4, r5
	and r8, r5, r7
	orr r9, r8, r9
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#124]
	ldr r11, [r0, +#48]
	add r6, r7, r6, ROR #18
	bic r9, r7, r4
	and r8, r4, r6
	orr r9, r8, r9
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10

	/* third loop */
	ldr r11, [r2, +#128]
	ldr r10, [r0, +#20]
	add r5, r6, r5, ROR #12
	eor r8, r5, r6
	eor r9, r8, r7
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10

	ldr r10, [r2, +#132]
	ldr r11, [r0, +#32]
	add r4, r5, r4, ROR #28
	eor r8, r4, r5
	eor r9, r8, r6
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r10, [r2, +#136]
	ldr r11, [r0, +#44]
	add r7, r4, r7, ROR #21
	eor r8, r7, r4
	eor r9, r8, r5
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#140]
	ldr r11, [r0, +#56]
	add r6, r7, r6, ROR #16
	eor r8, r6, r7
	eor r9, r8, r4
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10

	ldr r11, [r2, +#144]
	ldr r10, [r0, +#4]
	add r5, r6, r5, ROR #9
	eor r8, r5, r6
	eor r9, r8, r7
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10

	ldr r10, [r2, +#148]
	ldr r11, [r0, +#16]
	add r4, r5, r4, ROR #28
	eor r8, r4, r5
	eor r9, r8, r6
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r10, [r2, +#152]
	ldr r11, [r0, +#28]
	add r7, r4, r7, ROR #21
	eor r8, r7, r4
	eor r9, r8, r5
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#156]
	ldr r11, [r0, +#40]
	add r6, r7, r6, ROR #16
	eor r8, r6, r7
	eor r9, r8, r4
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10
	
	ldr r11, [r2, +#160]
	ldr r10, [r0, +#52]
	add r5, r6, r5, ROR #9
	eor r8, r5, r6
	eor r9, r8, r7
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10

	ldr r10, [r2, +#164]
	ldr r11, [r0, +#0]
	add r4, r5, r4, ROR #28
	eor r8, r4, r5
	eor r9, r8, r6
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r10, [r2, +#168]
	ldr r11, [r0, +#12]
	add r7, r4, r7, ROR #21
	eor r8, r7, r4
	eor r9, r8, r5
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#172]
	ldr r11, [r0, +#24]
	add r6, r7, r6, ROR #16
	eor r8, r6, r7
	eor r9, r8, r4
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10

	ldr r11, [r2, +#176]
	ldr r10, [r0, +#36]
	add r5, r6, r5, ROR #9
	eor r8, r5, r6
	eor r9, r8, r7
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10

	ldr r10, [r2, +#180]
	ldr r11, [r0, +#48]
	add r4, r5, r4, ROR #28
	eor r8, r4, r5
	eor r9, r8, r6
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r10, [r2, +#184]
	ldr r11, [r0, +#60]
	add r7, r4, r7, ROR #21
	eor r8, r7, r4
	eor r9, r8, r5
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#188]
	ldr r11, [r0, +#8]
	add r6, r7, r6, ROR #16
	eor r8, r6, r7
	eor r9, r8, r4
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10

	/* fourth loop */
	ldr r11, [r2, +#192]
	ldr r10, [r0, +#0]
	add r5, r6, r5, ROR #9
	mvn r8, r7
	orr r8, r5, r8
	eor r9, r8, r6
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10
	
	ldr r10, [r2, +#196]
	ldr r11, [r0, +#28]
	add r4, r5, r4, ROR #26 
	mvn r8, r6
	orr r8, r8, r4
	eor r9, r8, r5
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r10, [r2, +#200]
	ldr r11, [r0, +#56]
	add r7, r4, r7, ROR #22
	mvn r8, r5
	orr r8, r8, r7
	eor r9, r8, r4
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#204]
	ldr r11, [r0, +#20]
	add r6, r7, r6, ROR #17
	mvn r8, r4
	orr r8, r8, r6
	eor r9, r8, r7
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10
	
	ldr r11, [r2, +#208]
	ldr r10, [r0, +#48]
	add r5, r6, r5, ROR #11
	mvn r8, r7
	orr r8, r5, r8
	eor r9, r8, r6
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10
	
	ldr r10, [r2, +#212]
	ldr r11, [r0, +#12]
	add r4, r5, r4, ROR #26 
	mvn r8, r6
	orr r8, r8, r4
	eor r9, r8, r5
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r10, [r2, +#216]
	ldr r11, [r0, +#40]
	add r7, r4, r7, ROR #22
	mvn r8, r5
	orr r8, r8, r7
	eor r9, r8, r4
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#220]
	ldr r11, [r0, +#4]
	add r6, r7, r6, ROR #17
	mvn r8, r4
	orr r8, r8, r6
	eor r9, r8, r7
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10
	
	ldr r11, [r2, +#224]
	ldr r10, [r0, +#32]
	add r5, r6, r5, ROR #11
	mvn r8, r7
	orr r8, r5, r8
	eor r9, r8, r6
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10
	
	ldr r10, [r2, +#228]
	ldr r11, [r0, +#60]
	add r4, r5, r4, ROR #26 
	mvn r8, r6
	orr r8, r8, r4
	eor r9, r8, r5
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r10, [r2, +#232]
	ldr r11, [r0, +#24]
	add r7, r4, r7, ROR #22
	mvn r8, r5
	orr r8, r8, r7
	eor r9, r8, r4
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#236]
	ldr r11, [r0, +#52]
	add r6, r7, r6, ROR #17
	mvn r8, r4
	orr r8, r8, r6
	eor r9, r8, r7
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10
	
	ldr r11, [r2, +#240]
	ldr r10, [r0, +#16]
	add r5, r6, r5, ROR #11
	mvn r8, r7
	orr r8, r5, r8
	eor r9, r8, r6
	add r10, r10, r11
	add r4, r4, r9
	add r4, r4, r10
	
	ldr r10, [r2, +#244]
	ldr r11, [r0, +#44]
	add r4, r5, r4, ROR #26 
	mvn r8, r6
	orr r8, r8, r4
	eor r9, r8, r5
	add r10, r10, r11
	add r7, r7, r9
	add r7, r7, r10

	ldr r10, [r2, +#248]
	ldr r11, [r0, +#8]
	add r7, r4, r7, ROR #22
	mvn r8, r5
	orr r8, r8, r7
	eor r9, r8, r4
	add r10, r10, r11
	add r6, r6, r9
	add r6, r6, r10

	ldr r10, [r2, +#252]
	ldr r11, [r0, +#36]
	add r6, r7, r6, ROR #17
	mvn r8, r4
	orr r8, r8, r6
	eor r9, r8, r7
	add r10, r10, r11
	add r5, r5, r9
	add r5, r5, r10

	ldmia r1, {r8, r9, r10, r11}
	add r5, r6, r5, ROR #11
	add r4, r4, r8
	add r5, r5, r9
	add r6, r6, r10
	add r7, r7, r11
	stmia r1, {r4, r5, r6, r7}
	
	subs r3, r3, #1
	addne r0, r0, #64
	bne .Lstart
.Lend:

	pop {r4 - r11}
	bx lr

addr_table:
	.word md5_table
