.org 0x000

init:
    LOAD M(INDEX1)

    STA M(array1)
    JUMP M(array1)

array1:
    LOAD MQ,M(000)

    LOAD M(INDEX2)

    STA M(array2)
    JUMP M(array2)

array2:
    MUL M(000)

    LOAD MQ
    ADD M(result)
    STOR M(result)

    LOAD M(INDEX1)
    ADD M(UNIT)
    STOR M(INDEX1)

    LOAD M(INDEX2)
    ADD M(UNIT)
    STOR M(INDEX2)

    LOAD M(SIZE)
    SUB M(UNIT)
    STOR M(SIZE)

    JUMP+ M(init)

    LOAD M(result)
    JUMP M(0x400)
    


.org 0x050

UNIT:
    .word 0x1
result:
    .word 0x0

.org 0x3FD

INDEX1:
    .word 0x100
INDEX2:
    .word 0x150
SIZE:
    .word 0x5
