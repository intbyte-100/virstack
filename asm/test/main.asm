section .stack
a:
        half 0
var0:
        half 0
var1:
        half 1
var2:
        half 2
var3:
        half 3
var4:
        half 4
var5:
        half 5
var6:
        half 6
var7:
        half 7
var8:
        half 8
var9:
        half 9
var10:
        half 10
var11:
        half 11
var12:
        half 12
var13:
        half 13
var14:
        half 14
var15:
        half 15
var16:
        half 16
var17:
        half 17
var18:
        half 18
var19:
        half 19
section .code
        ldh R5, a
        ldh R4, var0
        add R5, R5, R4
        ldh R3, var1
        add R5, R5, R3
        ldh R2, var2
        add R5, R5, R2
        ldh R1, var3
        add R5, R5, R1
        ldh R0, var4
        add R5, R5, R0
        strh R0, var4
        ldh R0, var5
        add R5, R5, R0
        strh R0, var5
        ldh R0, var6
        add R5, R5, R0
        strh R0, var6
        ldh R0, var7
        add R5, R5, R0
        strh R0, var7
        ldh R0, var8
        add R5, R5, R0
        strh R0, var8
        ldh R0, var9
        add R5, R5, R0
        strh R0, var9
        ldh R0, var10
        add R5, R5, R0
        strh R0, var10
        ldh R0, var11
        add R5, R5, R0
        strh R0, var11
        ldh R0, var12
        add R5, R5, R0
        strh R0, var12
        ldh R0, var13
        add R5, R5, R0
        strh R0, var13
        ldh R0, var14
        add R5, R5, R0
        strh R0, var14
        ldh R0, var15
        add R5, R5, R0
        strh R0, var15
        ldh R0, var16
        add R5, R5, R0
        strh R0, var16
        ldh R0, var17
        add R5, R5, R0
        strh R0, var17
        ldh R0, var18
        add R5, R5, R0
        strh R0, var18
        ldh R0, var19
        add R5, R5, R0
        add R5, R5, R4
        add R5, R5, R3
        add R5, R5, R2
        add R5, R5, R1
        ldh R1, var4
        add R5, R5, R1
        ldh R1, var5
        add R5, R5, R1
        ldh R1, var6
        add R5, R5, R1
        ldh R1, var7
        add R5, R5, R1
        ldh R1, var8
        add R5, R5, R1
        ldh R1, var9
        add R5, R5, R1
        ldh R1, var10
        add R5, R5, R1
        ldh R1, var11
        add R5, R5, R1
        ldh R1, var12
        add R5, R5, R1
        ldh R1, var13
        add R5, R5, R1
        ldh R1, var14
        add R5, R5, R1
        ldh R1, var15
        add R5, R5, R1
        ldh R1, var16
        add R5, R5, R1
        ldh R1, var17
        add R5, R5, R1
        ldh R1, var18
        add R5, R5, R1
        add R5, R5, R0
        printi R5
        exit_inst
