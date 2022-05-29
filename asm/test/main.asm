.stack
    word 0x001
    half 0x10
    little 0x100


.code
    ld R0, 0
    ldh R1, 8
    add R0, R1, R0
    printi R0
    exit




