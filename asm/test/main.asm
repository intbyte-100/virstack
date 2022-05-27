.code
    ldh R0, 44
    mov R0, R1
    ldb R3, 0x0b
    ld R3, 0x0b


.stack
    word 100 ; eeeggggggggg
    half 0x100
    little 0b0100
    byte 1

.code
    mov R0, R1
    mov R1, R2
    mov R5, R3



