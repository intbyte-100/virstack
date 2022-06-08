

.stack

.stack
    half 1
    half 0x001
    half 20
    half 1
    half 30


.code
    ldh R0, 4
    ldh R1, 0
    ldh R2, 8
    ldh R3, 16
    ldh R5, 12
    mul R1, R1, R0
    add R0, R0, R5
    cmpb R4, R0, R2
    not R4
    jmp R4, R3
    printi R1
    exit




