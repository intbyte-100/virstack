section .text
global vrs_cp_addrr
global vrs_cp_subrr
global vrs_cp_mulrr
global vrs_interpret_code

vrs_cp_addrr:
    mov rax, [rdi]
    add rax, [rsi]
    mov [rcx], rax
    ret

vrs_cp_subrr:
    sub rdi, rsi
    mov rax, rdi
    ret

vrs_cp_mulrr:
    imul rdi, rsi
    mov rax, rdi
    ret

; register register
; register 16
; register 32
; register 32
; register
vrs_interpret_code:
    sub rsp, 8*7 ; prologue
    push rbp
    mov rbp, rsp

    mov [rbp - 8], rsi ; store the register values to the virtual registers
    mov [rbp - 16], rdx
    mov [rbp - 24], rcx
    mov [rbp - 32], r8
    mov [rbp - 40], r9

    pop rbp ; epilog
    add rsp, 8*7
