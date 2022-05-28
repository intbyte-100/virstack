.stack
    word 0x100
    half 0x200
    little 0x100


.code
    exit d
    ldh R0, 44
    mov R0, R1
    ldb R3, 0x0b
    ld R3, 0x0b
    ldh R0, 44
    mov R0, R1
    ldb R3, 0x0b
    ld R3, 0x0b
    strb R4, 0x1
    div R0, R1, R2



