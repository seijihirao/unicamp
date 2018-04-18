.org 0x0
.section .iv,"a"

_start:		

interrupt_vector:

    b RESET_HANDLER
.org 0x18
    b IRQ_HANDLER
