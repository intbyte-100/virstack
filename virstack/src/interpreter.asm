section .text
global vrs_cp_addrr
global vrs_cp_subrr
global vrs_cp_mulrr

vrs_cp_addrr:
    add rdi, rsi
    mov rax, rdi
    ret

vrs_cp_subrr:
    sub rdi, rsi
    mov rax, rdi
    ret

vrs_cp_mulrr:
    imul rdi, rsi
    mov rax, rdi
    ret

