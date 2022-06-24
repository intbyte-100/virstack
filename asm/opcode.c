#include "opcode.h"
#include "string.h"

vrs_linked_list *opcodes;

#define addOpcode(string, number, argCount, ...) { \
    char __vrs_args[] = {__VA_ARGS__, '\0'};               \
    opcode *__vrs_opcode = malloc(sizeof(opcode) - 1 + sizeof(__vrs_args)); \
    __vrs_opcode->name = string;                   \
    __vrs_opcode->opcode = number;                 \
    __vrs_opcode->argc = argCount;                 \
    memcpy(&__vrs_opcode->operands, &__vrs_args, argCount);                                               \
    vrsAddLinkedElement(opcodes, __vrs_opcode);\
}

void initOpcodes() {
    opcodes = vrsLinkedList();

    addOpcode("mov", mov, 2, REGISTER, REGISTER);
    addOpcode("ld", ld, 2, REGISTER, I32);
    addOpcode("ldh", ldh, 2, REGISTER, I32);
    addOpcode("ldb", ldb, 2, REGISTER, I32);
    addOpcode("str", str, 2, REGISTER, I32);
    addOpcode("strh", strh, 2, REGISTER, I32);
    addOpcode("strb", strb, 2, REGISTER, I32);

    addOpcode("add", add, 3, REGISTER, REGISTER, REGISTER);
    addOpcode("sub", sub, 3, REGISTER, REGISTER, REGISTER);
    addOpcode("mul", mul, 3, REGISTER, REGISTER, REGISTER);
    addOpcode("div", div_inst, 3, REGISTER, REGISTER, REGISTER);

    addOpcode("printi", printi, 1, REGISTER);
    addOpcode("cmp", cmp, 3, REGISTER, REGISTER, REGISTER);
    addOpcode("cmpl", cmpl, 3, REGISTER, REGISTER, REGISTER);
    addOpcode("cmpb", cmpb, 3, REGISTER, REGISTER, REGISTER);

    addOpcode("not", not, 1, REGISTER);
    addOpcode("jmp", jmp, 2, REGISTER, I32);
    addOpcode("or", or, 3, REGISTER, REGISTER, REGISTER);
    addOpcode("and", and, 3, REGISTER, REGISTER, REGISTER);
    addOpcode("exit", exit_inst, 0, '\0')
}
