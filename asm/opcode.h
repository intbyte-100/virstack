#pragma once

#include "../container/container.h"
#include "malloc.h"

typedef struct {
    unsigned char opcode;
    char* name;
    int argc;
    char operands;
} opcode;

extern vrs_linked_list *opcodes;

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
    div_inst,

    printi,

    cmp,
    cmpl,
    cmpb,
    not,
    jmp,

    or,
    and,

    exit_inst = 255
};

#define REGISTER 127
#define I8 1
#define I16 2
#define I32 4
#define I64 8

void initOpcodes();
