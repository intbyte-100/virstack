#include "vm.h"
#include "malloc.h"
#include "instruction_set.h"

void (*__vrs_instructions[exit])(vrs_vm *vm, const vrs_byte *code);

void _mov(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6] + 1]];
    vm->registers[6] += 2;
}

void _ld(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] =
            vrsForceCast(long, vm->stack[vrsForceCast(int, code[vm->registers[6]+1])]);
    vm->registers[6] += 5;
}

void _ldh(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vrsForceCast(int, vm->stack[vrsForceCast(int, code[vm->registers[6]+1])]);
    vm->registers[6] += 5;
}

void _ldb(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->stack[vrsForceCast(int, code[vm->registers[6] + 1])];
    vm->registers[6] += 5;
}


void _str(vrs_vm *vm, const vrs_byte *code) {
    *(long *) &vm->stack[vrsForceCast(int, code[vm->registers[6] + 1])] = vm->registers[code[vm->registers[6]]];
    vm->registers[6] += 5;
}

void _strh(vrs_vm *vm, const vrs_byte *code) {
    *(int *) &vm->stack[vrsForceCast(int, code[vm->registers[6] + 1])] = vm->registers[code[vm->registers[6]]];
    vm->registers[6] += 5;
}

void _strb(vrs_vm *vm, const vrs_byte *code) {
    *(vrs_byte *) &vm->stack[vrsForceCast(int, code[vm->registers[6] + 1])] = vm->registers[code[vm->registers[6]]];
    vm->registers[6] += 5;
}

void _add(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6] + 1]] + vm->registers[code[vm->registers[6] + 2]];
    vm->registers[6] += 3;
}

void _sub(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6] + 1]] - vm->registers[code[vm->registers[6] + 2]];
    vm->registers[6] += 3;
}

void _mul(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6] + 1]] * vm->registers[code[vm->registers[6] + 2]];
    vm->registers[6] += 3;
}

void _div(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6] + 1]] / vm->registers[code[vm->registers[6] + 2]];
    vm->registers[6] += 3;
}

void vrsInit(void) {
    __vrs_instructions[mov] = &_mov;
    __vrs_instructions[ld] = &_ld;
    __vrs_instructions[ldh] = &_ldh;
    __vrs_instructions[ldb] = &_ldb;
    __vrs_instructions[str] = &_str;
    __vrs_instructions[strh] = &_strh;
    __vrs_instructions[strb] = &_strb;
    __vrs_instructions[add] = &_add;
    __vrs_instructions[sub] = &_sub;
    __vrs_instructions[mul] = &_mul;
    __vrs_instructions[div] = &_div;
}


vrs_vm *vrsInitVm(vrs_config *config) {
    vrs_vm *vm = vrsMalloc(vrs_vm);
    vm->stack = malloc(config->stackSize);
    return vm;
}

void vrsDestroyVm(vrs_vm *vm) {
    free(vm->stack);
    free(vm);
}

void vrsExecute(vrs_vm *vm, unsigned char *code) {
    while (code[vm->registers[6]] != exit) {
        __vrs_instructions[code[vm->registers[6]++]](vm, code);
    }
}
