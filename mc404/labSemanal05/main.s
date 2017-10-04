.text               @ seção de código
    .align 4        @ alinha ponto de montagem em endereços múltiplos de 4
    .globl _start   @ torna o símbolo main visivel fora do arquivo

_start:
    mov r0, #1      @ carrega o valor 1 em r0, indicando que a saída da
	                @ syscall write sera em stdout
    ldr r1, =string @ carrega em r1 o endereco da string
    mov r2, #19     @ carrega em r2 o tamanho da string. r0,r1 e r2 serão
	                @ os argumentos da syscall write
    mov r7, #4      @ carrega o valor 4 para r7, indica o tipo da syscall
    svc 0x0         @ realiza uma chamada de sistema (syscall)
    mov r0, #123    @ return = 123
    mov r7, #1      @ carrega o valor 1 em r7, indicando a escolha da
	                @ syscall exit
    svc 0x0         

.data               @ seção de dados

string:  .asciz "Rodrigo - ra186837\n"  @coloca a string na memoria
