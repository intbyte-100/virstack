#include <error.h>
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "vistack.h"
#include "loader.h"

int main(int argc, char **argv){
    if(argc == 1) {
        printf("virstack virtual machine v0.1\n");
    } else if (strcmp(argv[1], "--load") == 0) {
        if (argv[2] == 0)
            printf("Error: --load requires vpe file specification\n");
        vrsInit();
        vrs_scope *scope = vrsMalloc(vrs_scope);
        vrs_loadVpe(fopen(argv[2], "r"), scope);
        vrs_config config = {
            .stackSize = 1024 * 64
        };
        vrs_vm *vm = vrsInitVm(&config);
        if (config.stackSize < scope->stackSize) {
            fprintf(stderr, "StackoverflowException: vm stack size is %i bytes, when required stack size for code execution is %i bytes\n\tat virstack/main.c (22 line)\n", config.stackSize,
                   scope->stackSize);
            exit(1);
        }
        memcpy(vm->stack, scope->stack, scope->stackSize);
        vrsExecute(vm, scope->code);
        vrsDispose(vm);
        vrsDispose(scope);
    }
}