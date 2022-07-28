section .stack
a:
    word 1
b:
    word 2


section .code
    frame 16
    frame 8
    ld R0, a
    ld R1, b
    add R0, R0, R1
    fstr R0, 12
    fld R5, 12
    printi R5
    ret
    exit
