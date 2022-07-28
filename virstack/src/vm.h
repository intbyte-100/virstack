#pragma once

#include "config.h"
#include "util.h"

typedef struct {
    vrs_byte* stack;
    long registers[8];
    long retVal;
    int conditionFlag;
} vrs_vm;

extern void (*__vrs_instructions[255])(vrs_vm *vm, const vrs_byte *code);


vrs_vm* vrsInitVm(vrs_config* config);
void vrsDestroyVm(vrs_vm* vm);
void vrsExecute(vrs_vm* vm, vrs_byte *code);
void vrsInit(void);