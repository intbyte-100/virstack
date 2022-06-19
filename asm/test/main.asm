.stack
        init: half 1000
        seven: half 7
        zero: half 0
        word 24
.code
        ldh R0, 0
        ldh R1, 4
        ldh R2, 8
        ld R4, 12
        ld R1, %num:100
        printi R0
        sub R0, R0, R1 ; R0 = R0 - R1
        cmpb R3, R0, R2 ; R3 = R0 < R2
        jmp R3, 24
        exit



