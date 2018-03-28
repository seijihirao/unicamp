    .file   "main.c"
    .text
    .align  2
@ Função principal
@ :)
_start:
	@ args = 0, pretend = 0, frame = 12312
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #12288
	sub	sp, sp, #24
	ldr	r3, .L18
	sub	r2, fp, #4
	str	r0, [r2, r3]
	ldr	r3, .L18+4
	sub	ip, fp, #4
	str	r1, [ip, r3]
	ldr	r3, .L18+8
	sub	r0, fp, #4
	add	r2, r0, r3
	mov	r3, #12288
	mov	r0, r2
	mov	r1, #0
	mov	r2, r3
	bl	memset
	sub	r3, fp, #14
	mov	r0, r3
	bl	read
	ldrh	r3, [fp, #-14]
	cmp	r3, #0
	beq	.L17
.L10:
	ldr	r3, .L18+8
	mov	r2, #1
	sub	r1, fp, #4
	str	r2, [r1, r3]
	sub	r3, fp, #12288
	sub	r3, r3, #4
	sub	r3, r3, #12
	mov	r0, r3
	bl	print
	mov	r3, #1
	str	r3, [fp, #-12]
	b	.L12
.L15:
	ldr	r3, [fp, #-12]
	str	r3, [fp, #-8]
	b	.L13
.L14:
	ldr	r1, [fp, #-8]
	ldr	r2, [fp, #-8]
	ldr	r3, .L18+8
	mov	r2, r2, asl #2
	sub	ip, fp, #4
	add	r2, ip, r2
	add	r3, r2, r3
	ldr	r2, [r3, #0]
	ldr	r3, [fp, #-8]
	sub	r0, r3, #1
	ldr	r3, .L18+8
	mov	r0, r0, asl #2
	sub	ip, fp, #4
	add	r0, ip, r0
	add	r3, r0, r3
	ldr	r3, [r3, #0]
	add	r2, r2, r3
	ldr	r3, .L18+8
	mov	r1, r1, asl #2
	sub	r0, fp, #4
	add	r1, r0, r1
	add	r3, r1, r3
	str	r2, [r3, #0]
	ldr	r3, [fp, #-8]
	sub	r3, r3, #1
	str	r3, [fp, #-8]
.L13:
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bgt	.L14
	sub	r3, fp, #12288
	sub	r3, r3, #4
	sub	r3, r3, #12
	mov	r0, r3
	bl	print
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L12:
	ldrh	r3, [fp, #-14]
	mov	r3, r3, asl #16
	mov	r2, r3, asr #16
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	bge	.L15
	b	.L16
.L17:
	mov	r0, r0	@ nop
.L16:
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L19:
	.align	2
.L18:
	.word	-12308
	.word	-12312
	.word	-12300
	.size	_start, .-_start
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",%progbits

@ Le uma sequencia de bytes da entrada padrao.
@ parametros:
@  r0: endereco do buffer de memoria que recebera a sequencia de bytes.
@  r1: numero maximo de bytes que pode ser lido (tamanho do buffer).
@ retorno:
@  r0: numero de bytes lidos.
read:
    push {r4,r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, #0         @ stdin file descriptor = 0
    mov r1, r4         @ endereco do buffer
    mov r2, r5         @ tamanho maximo.
    mov r7, #3         @ read
    svc 0x0
    bl atoi
    pop {r4, r5, lr}
    mov pc, lr

@ Escreve uma sequencia de bytes na saida padrao.
@ parametros:
@  r0: endereco do buffer de memoria que contem a sequencia de bytes.
@  r1: numero de bytes a serem escritos
write:
    push {r4,r5, lr}
    bl itoa
    mov r4, r0
    mov r5, r1
    mov r0, #1         @ stdout file descriptor = 1
    mov r1, r4         @ endereco do buffer
    mov r2, r5         @ tamanho do buffer.
    mov r7, #4         @ write
    svc 0x0
    pop {r4, r5, lr}
    mov pc, lr

@ Converte uma sequencia de caracteres hex para um numero binario
@ parametros:

@  r0: endereco do buffer de memoria que armazena a sequencia de caracteres.
@  r1: numero de caracteres a ser considerado na conversao
@ retorno:
@  r0: numero hex
atoi:
    push {r4, r5, lr} 
    mov r4, r0         @ r4 == endereco do buffer de caracteres
    mov r5, r1         @ r5 == numero de caracteres a ser considerado 
    mov r0, #0         @ number = 0
    mov r1, #0         @ loop indice
atoi_loop:
    cmp r1, r5         @ se indice == tamanho maximo 
    beq atoi_end       @ finaliza conversao
    mov r0, r0, lsl #4
    ldrb r2, [r4, r1] 
    cmp r2, #'9'
    subls r2, r2, #'0'
    subhi r2, r2, #'A'
    addhi r2, r2, #10 
    orr r0, r0, r2
    add r1, r1, #1      @ indice++ 
    b atoi_loop
atoi_end:
    pop {r4, r5, lr} 
    mov pc, lr

@ Converte um numero hex em uma sequencia de caracteres
@ parametros:
@  r0: endereco do buffer de memoria que recebera a sequencia de caracteres.
@  r1: numero de caracteres a ser considerado na conversao
@  r2: numero hex
itoa:
    push {r4, r5, lr} 
    mov r4, r0              @ copia endereco do buffer para r4
itoa_loop:
    sub r1, r1, #1          @ decremento do indice
    cmp r1, #0              @ verifica se ainda ha bits a serem lidos
    beq itoa_end
    and r3, r2, #0b1111
    mov r2, r2 ,lsr #4
    cmp r3, #9
    addls r3, r3, #'0'
    addhi r3, r3, #'A'
    subhi r3, r3, #10
    strb r3, [r4, r1]       @ escreve caractere na memoria
    b itoa_loop
itoa_end:
    pop {r4, r5, lr}
    mov pc, lr


print:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L6
.L7:
	ldr	r3, [fp, #-8]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3, #0]
	mov	r0, r3
	bl	write
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L6:
	ldr	r3, [fp, #-8]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	ldr	r3, [r3, #0]
	cmp	r3, #0
	bne	.L7
	mov	r0, #10
	bl	write
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}

