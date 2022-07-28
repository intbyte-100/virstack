#include <string.h>
#include <stdbool.h>
#include "debug.h"


void printRegisters(vrs_vm *vm) {
    char argument[30];
    scanf("%s", argument);
    if (strcmp(argument, "all") == 0)
        for (int i = 0; i < 8; ++i)
            printf("R%i: %li\n", i, vm->registers[i]);

    else if (strcmp(argument, "r") == 0) {
        int registerIndex = 0;
        scanf("%i", &registerIndex);
        printf("R%i: %li\n", registerIndex, vm->registers[registerIndex]);
    }
}


void printStackFrame(vrs_vm *vm) {
    char argument[30];

    scanf("%s", argument);
    int stackIndex = 0;
    scanf("%i", &stackIndex);
    printf("stack frame at %i: ", stackIndex);
    printf(argument, vm->stack[vm->registers[7] - stackIndex]);
    printf("\n");
}

void vrsRunDebug(vrs_vm *vm, unsigned char *code) {
    char command[30];
    int index = 0;
    printf("\033[H\033[J");
    while (code[vm->registers[6]] != 255) {
        index++;
        while (true) {
            printf(">> ");
            scanf("%s", command);
            if (strcmp(command, "n") == 0) {
                break;
            }

            if (strcmp(command, "p") == 0) {
                printRegisters(vm);
            } else if (strcmp(command, "psf") == 0) {
                printStackFrame(vm);
            } else if (strcmp(command, "i") == 0) {
                printf("asm instruction: %i\nbyte code address: %li\n", index, vm->registers[6]);
            }
        }

        __vrs_instructions[code[vm->registers[6]++]](vm, code);

    }
}
