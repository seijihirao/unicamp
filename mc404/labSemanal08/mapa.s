	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"mapa.c"
	.global	mapa
	.data
	.align	2
	.type	mapa, %object
	.size	mapa, 100
mapa:
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	88
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	95
	.byte	95
	.byte	95
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.byte	88
	.comm	visitados,400,4
	.comm	xRob,4,4
	.comm	yRob,4,4
	.comm	xLoc,4,4
	.comm	yLoc,4,4
	.text
	.align	2
	.global	_start
	.type	_start, %function
_start:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r3, .L3
	mov	r2, #3
	str	r2, [r3, #0]
	ldr	r3, .L3+4
	mov	r2, #1
	str	r2, [r3, #0]
	ldr	r3, .L3+8
	mov	r2, #8
	str	r2, [r3, #0]
	ldr	r3, .L3+12
	mov	r2, #3
	str	r2, [r3, #0]
	bl	ajudaORobinson
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L4:
	.align	2
.L3:
	.word	xRob
	.word	yRob
	.word	xLoc
	.word	yLoc
	.size	_start, .-_start
	.align	2
	.global	daParaPassar
	.type	daParaPassar, %function
daParaPassar:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	blt	.L6
	ldr	r3, [fp, #-8]
	cmp	r3, #9
	bgt	.L6
	ldr	r3, [fp, #-12]
	cmp	r3, #0
	blt	.L6
	ldr	r3, [fp, #-12]
	cmp	r3, #9
	ble	.L7
.L6:
	mov	r3, #0
	b	.L8
.L7:
	ldr	r2, [fp, #-8]
	ldr	r0, [fp, #-12]
	ldr	r1, .L10
	mov	r3, r2
	mov	r3, r3, asl #2
	add	r3, r3, r2
	mov	r3, r3, asl #1
	add	r3, r3, r0
	add	r3, r1, r3
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #88
	moveq	r3, #0
	movne	r3, #1
.L8:
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L11:
	.align	2
.L10:
	.word	mapa
	.size	daParaPassar, .-daParaPassar
	.align	2
	.global	posicaoXRobinson
	.type	posicaoXRobinson, %function
posicaoXRobinson:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L14
	ldr	r3, [r3, #0]
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L15:
	.align	2
.L14:
	.word	xRob
	.size	posicaoXRobinson, .-posicaoXRobinson
	.align	2
	.global	posicaoYRobinson
	.type	posicaoYRobinson, %function
posicaoYRobinson:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L18
	ldr	r3, [r3, #0]
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L19:
	.align	2
.L18:
	.word	yRob
	.size	posicaoYRobinson, .-posicaoYRobinson
	.align	2
	.global	posicaoXLocal
	.type	posicaoXLocal, %function
posicaoXLocal:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L22
	ldr	r3, [r3, #0]
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L23:
	.align	2
.L22:
	.word	xLoc
	.size	posicaoXLocal, .-posicaoXLocal
	.align	2
	.global	posicaoYLocal
	.type	posicaoYLocal, %function
posicaoYLocal:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L26
	ldr	r3, [r3, #0]
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L27:
	.align	2
.L26:
	.word	yLoc
	.size	posicaoYLocal, .-posicaoYLocal
	.align	2
	.global	inicializaVisitados
	.type	inicializaVisitados, %function
inicializaVisitados:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L29
.L32:
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L30
.L31:
	ldr	r2, [fp, #-12]
	ldr	r0, [fp, #-8]
	ldr	r1, .L34
	mov	r3, r2
	mov	r3, r3, asl #2
	add	r3, r3, r2
	mov	r3, r3, asl #1
	add	r3, r3, r0
	mov	r2, #0
	str	r2, [r1, r3, asl #2]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L30:
	ldr	r3, [fp, #-8]
	cmp	r3, #9
	ble	.L31
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L29:
	ldr	r3, [fp, #-12]
	cmp	r3, #9
	ble	.L32
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L35:
	.align	2
.L34:
	.word	visitados
	.size	inicializaVisitados, .-inicializaVisitados
	.align	2
	.global	foiVisitado
	.type	foiVisitado, %function
foiVisitado:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r2, [fp, #-8]
	ldr	r0, [fp, #-12]
	ldr	r1, .L38
	mov	r3, r2
	mov	r3, r3, asl #2
	add	r3, r3, r2
	mov	r3, r3, asl #1
	add	r3, r3, r0
	ldr	r3, [r1, r3, asl #2]
	cmp	r3, #1
	movne	r3, #0
	moveq	r3, #1
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L39:
	.align	2
.L38:
	.word	visitados
	.size	foiVisitado, .-foiVisitado
	.align	2
	.global	visitaCelula
	.type	visitaCelula, %function
visitaCelula:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r2, [fp, #-8]
	ldr	r0, [fp, #-12]
	ldr	r1, .L42
	mov	r3, r2
	mov	r3, r3, asl #2
	add	r3, r3, r2
	mov	r3, r3, asl #1
	add	r3, r3, r0
	mov	r2, #1
	str	r2, [r1, r3, asl #2]
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L43:
	.align	2
.L42:
	.word	visitados
	.size	visitaCelula, .-visitaCelula
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
