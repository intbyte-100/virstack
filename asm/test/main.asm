section .stack
a:
    word 1
b:
    word 2


section .code
    frame 20
    frame 12
    ld R0, a
    ld R1, b
    add R0, R0, R1
    fstr R0, 0
    fld R5, 0
    printi R5
    ret
    ret
    exit
