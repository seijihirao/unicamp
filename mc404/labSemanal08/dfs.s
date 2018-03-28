.global ajudaORobinson

.data

output_buffer:  .skip 32

.text
.align 4
ajudaORobinson:
    push {lr}
    bl inicializaVisitados
    bl posicaoYRobinson
    mov r1, r0
    bl posicaoXRobinson
    bl dfs
    pop {pc}

.align 4
dfs:
    push {r4, r5, r6, r7, lr}
    mov r4, r0
    mov r5, r1
    mov r6, #-2
    mov r7, #-2
    loop_i:
        add r6, r6, #1
        loop_j:
            add r7, r7, #1
            
            add r0, r4, r6
            add r1, r5, r7
            bl foiVisitado
            cmp r0, #1
            beq out_j

            add r0, r4, r6
            add r1, r5, r7
            bl daParaPassar
            cmp r0, #0
            beq out_j

            add r0, r4, r6
            add r1, r5, r7
            bl visitaCelula            
            
            bl posicaoXLocal
            add r1, r4, r6
            cmp r0, r1
            bne recurse
            
            bl posicaoYLocal
            add r1, r5, r7
            cmp r0, r1
            bne recurse
            
            mov r8, #1
            beq out_loops            

            recurse:
            add r0, r4, r6
            add r1, r5, r7
            bl dfs
            cmp r8, #1
            ldr r0, =output_buffer
            mov r1, #0
            add r1, r4, r6
            add r1, r0, #'0'
            strb r1, [r0], #1
            mov r1, #' '
            strb r1, [r0], #1
            mov r1, #0
            add r1, r5, r7
            add r1, r0, #'0'
            strb r1, [r0], #1
            mov r1, #'\n'
            strb r1, [r0], #1
            mov r1, #4 
            
            bleq write
            beq out_loops

            out_j:
            cmp r7, #1
            blt loop_i
        out_i:
        cmp r6, #1
        blt out_loops
    out_loops:
    pop {r4, r5, r6, r7, lr}
    mov pc, lr

@ Escreve uma sequencia de bytes na saida padrao.
@ parametros:
@  r0: endereco do buffer de memoria que contem a sequencia de bytes.
@  r1: numero de bytes a serem escritos
.align 4
write:
    push {r4,r5, lr} 
    mov r4, r0
    mov r5, r1
    mov r0, #1         @ stdout file descriptor = 1
    mov r1, r4         @ endereco do buffer
    mov r2, r5         @ tamanho do buffer.
    mov r7, #4         @ write
    svc 0x0 
    pop {r4, r5, lr} 
    mov pc, lr
 
