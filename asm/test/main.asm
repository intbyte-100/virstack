section .stack
        a:
        half 100
        seven:
        half 7
        zero:
        half 0
        word 24
section .code
        ldh R0, a
        ldh R1, seven
        ldh R2, zero

        lol:
        printi R0
        sub R0, R0, R1 ; R0 = R0 - R1
        cmpb R3, R0, R2 ; R3 = R0 < R2
        cmp R4, R0, R2
        jmp R3, lol
        exit




