section .stack
        half 1000
        half 7
        half 0
        word 24
section .code
        ldh R0, 0
        ldh R1, 4
        ldh R2, 8
        ld R4, 12
        printi R0
        sub R0, R0, R1 ; R0 = R0 - R1
        cmpb R3, R0, R2 ; R3 = R0 < R2
        cmp R4, R0, R2
        jmp R3, 24
        exit




