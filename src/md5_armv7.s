/*
 * md5_armv7.s
 * Author: Fabjan Sukalia (fsukalia@gmail.com)
 * Date: 2014-12-25
 */

/* optimized for Cortex-A7 as found on Raspberry Pi 2 */
.arch armv7-a

.text
.arm
.global md5_process_blocks_asm
.type md5_process_blocks_asm, %function
md5_process_blocks_asm: /* (uint8_t block[64], uint32_t hash[4], uint n) */
	push {r4 - r10}
	cmp r2, #0
	beq .Lend
	
	/* r4 = h0; r5 = h1; r6 = h2; r7 = h3 */
	ldmia  r1, {r4, r5, r6, r7}
	
.Lstart:
	
.macro round a, b, c, d, offset_block, table_top, table_bot, shift
	ldr r10, [r0, +#\offset_block]
	movw r3, \table_bot
	add \b, \c, \b, ROR #\shift
	movt r3, \table_top
	bic r9, \d, \b
	and r8, \b, \c
	orr r8, r8, r9
	add \a, \a, r8
	add r10, r10, r3
	add \a, \a, r10
.endm

	/* first loop */
	ldr r10, [r0, +#0]
	movw r3, 0xA478
	bic r9, r7, r5
	movt r3, 0xD76A
	and r8, r5, r6
	orr r8, r8, r9
	add r4, r4, r8
	add r10, r10, r3
	add r4, r4, r10

	round r7, r4, r5, r6,  4, 0xE8C7, 0xB756, 25
	round r6, r7, r4, r5,  8, 0x2420, 0x70DB, 20
	round r5, r6, r7, r4, 12, 0xC1BD, 0xCEEE, 15
	
	round r4, r5, r6, r7, 16, 0xF57C, 0x0FAF, 10
	round r7, r4, r5, r6, 20, 0x4787, 0xC62A, 25
	round r6, r7, r4, r5, 24, 0xA830, 0x4613, 20
	round r5, r6, r7, r4, 28, 0xFD46, 0x9501, 15
 
	round r4, r5, r6, r7, 32, 0x6980, 0x98D8, 10
	round r7, r4, r5, r6, 36, 0x8B44, 0xF7AF, 25
	round r6, r7, r4, r5, 40, 0xFFFF, 0x5BB1, 20
	round r5, r6, r7, r4, 44, 0x895C, 0xD7BE, 15

	round r4, r5, r6, r7, 48, 0x6B90, 0x1122, 10
	round r7, r4, r5, r6, 52, 0xFD98, 0x7193, 25
	round r6, r7, r4, r5, 56, 0xA679, 0x438E, 20
	round r5, r6, r7, r4, 60, 0x49B4, 0x0821, 15
	
	/* second loop */
.purgem round
.macro round a, b, c, d, offset_block, table_top, table_bot,  shift
	ldr r10, [r0, +#\offset_block]
	movw r3, \table_bot
	add \b, \c, \b, ROR #\shift
	movt r3, \table_top
	bic r9, \c, \d
	and r8, \d, \b
	orr r8, r8, r9
	add r10, r10, r3
	add \a, \a, r8
	add \a, \a, r10
.endm
 
	round r4, r5, r6, r7,  4, 0xF61E, 0x2562, 10
	round r7, r4, r5, r6, 24, 0xC040, 0xB340, 27
	round r6, r7, r4, r5, 44, 0x265E, 0x5A51, 23
	round r5, r6, r7, r4,  0, 0xE9B6, 0xC7AA, 18
	
	round r4, r5, r6, r7, 20, 0xD62F, 0x105D, 12
	round r7, r4, r5, r6, 40, 0x0244, 0x1453, 27
	round r6, r7, r4, r5, 60, 0xD8A1, 0xE681, 23
	round r5, r6, r7, r4, 16, 0xE7D3, 0xFBC8, 18

	round r4, r5, r6, r7, 36, 0x21E1, 0xCDE6, 12
	round r7, r4, r5, r6, 56, 0xC337, 0x07D6, 27
	round r6, r7, r4, r5, 12, 0xF4D5, 0x0D87, 23
	round r5, r6, r7, r4, 32, 0x455A, 0x14ED, 18

	round r4, r5, r6, r7, 52, 0xA9E3, 0xE905, 12
	round r7, r4, r5, r6,  8, 0xFCEF, 0xA3F8, 27
	round r6, r7, r4, r5, 28, 0x676F, 0x02D9, 23
	round r5, r6, r7, r4, 48, 0x8D2A, 0x4C8A, 18

	/* third loop */
.purgem round
.macro round a, b, c, d, offset_block, table_top, table_bot,  shift
	ldr r10, [r0, +#\offset_block]
	movw r3, \table_bot
	add \b, \c, \b, ROR #\shift
	movt r3, \table_top
	eor r8, \d, \c
	eor r8, r8, \b
	add \a, \a, r8
	add r10, r10, r3
	add \a, \a, r10
.endm
 
	round r4, r5, r6, r7, 20, 0xFFFA, 0x3942, 12
	round r7, r4, r5, r6, 32, 0x8771, 0xF681, 28
	round r6, r7, r4, r5, 44, 0x6D9D, 0x6122, 21
	round r5, r6, r7, r4, 56, 0xFDE5, 0x380C, 16
	
	round r4, r5, r6, r7,  4, 0xA4BE, 0xEA44,  9
	round r7, r4, r5, r6, 16, 0x4BDE, 0xCFA9, 28
	round r6, r7, r4, r5, 28, 0xF6BB, 0x4B60, 21
	round r5, r6, r7, r4, 40, 0xBEBF, 0xBC70, 16

	round r4, r5, r6, r7, 52, 0x289B, 0x7EC6,  9
	round r7, r4, r5, r6,  0, 0xEAA1, 0x27FA, 28
	round r6, r7, r4, r5, 12, 0xD4EF, 0x3085, 21
	round r5, r6, r7, r4, 24, 0x0488, 0x1D05, 16

	round r4, r5, r6, r7, 36, 0xD9D4, 0xD039,  9
	round r7, r4, r5, r6, 48, 0xE6DB, 0x99E5, 28
	round r6, r7, r4, r5, 60, 0x1FA2, 0x7CF8, 21
	round r5, r6, r7, r4,  8, 0xC4AC, 0x5665, 16

	/* fourth loop */
.purgem round
.macro round a, b, c, d, offset_block, table_top, table_bot,  shift
	ldr r10, [r0, +#\offset_block]
	movw r3, \table_bot
	add \b, \c, \b, ROR #\shift
	movt r3, \table_top
	mvn r8, \d
	orr r8, r8, \b
	eor r8, r8, \c
	add \a, \a, r8
	add r10, r10, r3
	add \a, \a, r10
.endm
 
	round r4, r5, r6, r7,  0, 0xF429, 0x2244,  9
	round r7, r4, r5, r6, 28, 0x432A, 0xFF97, 26
	round r6, r7, r4, r5, 56, 0xAB94, 0x23A7, 22
	round r5, r6, r7, r4, 20, 0xFC93, 0xA039, 17

	round r4, r5, r6, r7, 48, 0x655B, 0x59C3, 11
	round r7, r4, r5, r6, 12, 0x8F0C, 0xCC92, 26
	round r6, r7, r4, r5, 40, 0xFFEF, 0xF47D, 22
	round r5, r6, r7, r4,  4, 0x8584, 0x5DD1, 17

	round r4, r5, r6, r7, 32, 0x6FA8, 0x7E4F, 11
	round r7, r4, r5, r6, 60, 0xFE2C, 0xE6E0, 26
	round r6, r7, r4, r5, 24, 0xA301, 0x4314, 22
	round r5, r6, r7, r4, 52, 0x4E08, 0x11A1, 17

	round r4, r5, r6, r7, 16, 0xF753, 0x7E82, 11
	round r7, r4, r5, r6, 44, 0xBD3A, 0xF235, 26
	round r6, r7, r4, r5,  8, 0x2AD7, 0xD2BB, 22
	round r5, r6, r7, r4, 36, 0xEB86, 0xD391, 17
	
	ldmia r1, {r3, r8, r9, r10}
	
	subs r2, r2, #1
	addne r0, r0, #64
	
	add r5, r6, r5, ROR #11
	add r4, r4, r3
	add r5, r5, r8
	add r6, r6, r9
	add r7, r7, r10
	stmia r1, {r4, r5, r6, r7}
	
	bne .Lstart
	
.Lend:
	pop {r4 - r10}
	bx lr

