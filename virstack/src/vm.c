#include "vm.h"
#include "malloc.h"
#include "instruction_set.h"

void (*__vrs_instructions[exit_inst])(vrs_vm *vm, const vrs_byte *code);

void _mov(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6] + 1]];
    vm->registers[6] += 2;
}

void _ld(vrs_vm *vm, const vrs_byte *code) {
    int address = vrsForceCast(int, code[vm->registers[6]+1]);
    vm->registers[code[vm->registers[6]]] = vrsForceCast(unsigned long , vm->stack[address]);
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
    *(int *) &vm->stack[vrsForceCast(int, code[vm->registers[6] + 1])] = (int) vm->registers[code[vm->registers[6]]];
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

void _cmp(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6] + 1]] == vm->registers[code[vm->registers[6] + 2]];
    vm->registers[6] += 3;
}

void _cmpl(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6] + 1]] < vm->registers[code[vm->registers[6] + 2]];
    vm->registers[6] += 3;
}

void _cmpb(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6] + 1]] > vm->registers[code[vm->registers[6] + 2]];
    vm->registers[6] += 3;
}

void _jmp(vrs_vm *vm, const vrs_byte *code) {
    if (vm->registers[code[vm->registers[6]]]) {
        vm->registers[6] = vrsForceCast(int, code[vm->registers[6]+1]);
        return;
    }
    vm->registers[6] += 2;
}

void _printi(vrs_vm *vm, const vrs_byte *code) {
    long val = vm->registers[code[vm->registers[6]]];
    printf("%li\n", val);
    vm->registers[6]++;
}

void _not(vrs_vm *vm, const vrs_byte *code){
    vm->registers[code[vm->registers[6]]] = !vm->registers[code[vm->registers[6]]];
    vm->registers[6]++;
}

void _or(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6]+1]] || vm->registers[code[vm->registers[6]+2]];
    vm->registers[6]+=3;
}

void _and(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->registers[code[vm->registers[6]+1]] && vm->registers[code[vm->registers[6]+2]];
    vm->registers[6]+=3;
}

void _frame(vrs_vm *vm, const vrs_byte *code) {
    short newFrame = vrsForceCast(short, code[vm->registers[6]]);
    *(int *) &vm->stack[vm->registers[7] + newFrame] = vm->registers[7];
    vm->registers[7] += newFrame + 4;
    vm->registers[6]+=2;
}

void _ret(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[7] = *(int *) &vm->stack[vm->registers[7]];
}

void _retr(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[7] = *(int *) &vm->stack[vm->registers[7]];
    vm->retVal = vm->registers[code[vm->registers[6] + 1]];
    vm->registers[6]++;
}

void _fld(vrs_vm *vm, const vrs_byte *code){
    vm->registers[code[vm->registers[6]]] =
            vrsForceCast(long, vm->stack[vm->registers[7] - vrsForceCast(int, code[vm->registers[6]+1])]);
    vm->registers[6] += 5;
}

void _fldh(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vrsForceCast(int, vm->stack[vm->registers[7] - vrsForceCast(int, code[vm->registers[6]+1])]);
    vm->registers[6] += 5;
}

void _fldb(vrs_vm *vm, const vrs_byte *code) {
    vm->registers[code[vm->registers[6]]] = vm->stack[vm->registers[7] - vrsForceCast(int, code[vm->registers[6] + 1])];
    vm->registers[6] += 5;
}


void _fstr(vrs_vm *vm, const vrs_byte *code) {
    *(long *) &vm->stack[vm->registers[7] - vrsForceCast(int, code[vm->registers[6] + 1])] = vm->registers[code[vm->registers[6]]];
    vm->registers[6] += 5;
}

void _fstrh(vrs_vm *vm, const vrs_byte *code) {
    *(int *) &vm->stack[vm->registers[7] - vrsForceCast(int, code[vm->registers[6] + 1])] = (int) vm->registers[code[vm->registers[6]]];
    vm->registers[6] += 5;
}

void _fstrb(vrs_vm *vm, const vrs_byte *code) {
    *(vrs_byte *) &vm->stack[vm->registers[7] - vrsForceCast(int, code[vm->registers[6] + 1])] = vm->registers[code[vm->registers[6]]];
    vm->registers[6] += 5;
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
    __vrs_instructions[div_inst] = &_div;
    __vrs_instructions[cmp] = &_cmp;
    __vrs_instructions[cmpl] = &_cmpl;
    __vrs_instructions[cmpb] = &_cmpb;
    __vrs_instructions[jmp] = &_jmp;
    __vrs_instructions[printi] = &_printi;
    __vrs_instructions[not] = &_not;
    __vrs_instructions[and] = &_and;
    __vrs_instructions[or] = &_or;
    __vrs_instructions[frame] = &_frame;
    __vrs_instructions[ret] = &_ret;
    __vrs_instructions[retr] = &_retr;
    __vrs_instructions[fld] = &_fld;
    __vrs_instructions[fldh] = &_fldh;
    __vrs_instructions[fldb] = &_fldb;
    __vrs_instructions[fstr] = &_fstr;
    __vrs_instructions[fstrh] = &_fstrh;
    __vrs_instructions[fstrb] = &_fstrh;
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
    while (code[vm->registers[6]] != exit_inst) {
        __vrs_instructions[code[vm->registers[6]++]](vm, code);
    }
}
