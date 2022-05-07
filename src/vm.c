#include "vm.h"
#include "malloc.h"
#include "ir_set.h"

void (*__vrs_instructions[ir_count]) (vrs_vm* vm, const vrs_byte* code);

void mov_ir(vrs_vm* vm, const vrs_byte* code){
    vm->registers[code[vm->registers[15]]] = vm->registers[code[vm->registers[15]+1]];
    vm->registers[15]+=2;
}

void ld_ir(vrs_vm* vm, const vrs_byte* code){
    vm->registers[code[vm->registers[15]]] = *((long*) &code[vm->registers[15]+1]);
    vm->registers[15]+=5;
}

void ldh_ir(vrs_vm* vm, const vrs_byte* code){
    vm->registers[code[vm->registers[15]]] = *((int*) &code[vm->registers[15]+1]);
    vm->registers[15]+=5;
}

void ldb_ir(vrs_vm* vm, const vrs_byte* code){
    vm->registers[code[vm->registers[15]]] = code[vm->registers[15]+1];
    vm->registers[15]+=5;
}


void vrsInit(void){
    __vrs_instructions[mov] = &mov_ir;
    __vrs_instructions[ld] = &ld_ir;
    __vrs_instructions[ldh] = &ldh_ir;
    __vrs_instructions[ldb] = &ldb_ir;
}



vrs_vm *vrsInitVm(vrs_config *config) {
    vrs_vm* vm = vrsMalloc(vrs_vm);
    vm->stack = malloc(config->stackSize);
    return vm;
}

void vrsDestroyVm(vrs_vm *vm) {
    free(vm->stack);
    free(vm);
}