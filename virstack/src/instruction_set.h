#pragma once

enum inst_set{
    mov,

    ld,
    ldh,
    ldb,

    str,
    strh,
    strb,

    add,
    sub,
    mul,
    div,

    printi,

    cmp,
    cmpl,
    cmpb,
    not,
    jmp,

    or,
    and,

    exit = 255
};


