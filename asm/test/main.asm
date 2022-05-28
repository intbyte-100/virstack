.stack
    word 0x100
    half 0x200
    little 0x100
    byte 0b10101

.code
    ldh R0, 44
    mov R0, R1
    ldb R3, 0x0b
    ld R3, 0x0b
    ldh R0, 44
    mov R0, R1
    ldb R3, 0x0b
    ld R3, 0x0b



