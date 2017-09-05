.org 0x000

init:
    LOAD MQ,M(GRAVITY)

    MUL M(x)
    LOAD MQ
    STOR M(y)
 
    RSH
    STOR M(k)

loop:
    LOAD M(cont)
    SUB M(UNIT)
    STOR M(cont)

    LOAD M(y)
    DIV M(k)
    LOAD MQ
    ADD M(k)
    RSH
    STOR M(k)
    LOAD M(cont)

    JUMP+ M(loop)

    LOAD M(k)
    JUMP M(0x400)

.org 0x105

x:
    .word 0xDAC
cont:
    .word 0xA
k:
    .word 0x0
y:
    .word 0x0

GRAVITY:
    .word 0xA
UNIT:
    .word 0x1
