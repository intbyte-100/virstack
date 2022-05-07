#include "vm.h"
#include "malloc.h"


vrs_vm *vrsInitVm(vrs_config *config) {
    vrs_vm* vm = vrsMalloc(vrs_vm);
    vm->stack = malloc(config->stackSize);
    return vm;
}

void vrsDestroyVm(vrs_vm *vm) {
    free(vm->stack);
    free(vm);
}