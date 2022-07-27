#pragma once

#include "config.h"
#include "util.h"

typedef struct {
    vrs_byte* stack;
    long registers[8];
    long retVal;
    int conditionFlag;
} vrs_vm;




vrs_vm* vrsInitVm(vrs_config* config);
void vrsDestroyVm(vrs_vm* vm);
void vrsExecute(vrs_vm* vm, vrs_byte *code);
void vrsInit(void);