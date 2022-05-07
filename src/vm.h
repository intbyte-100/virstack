#pragma once

#include "config.h"
#include "util.h"

typedef struct {
    vrs_byte* stack;
    long registers[16];
    int conditionFlag;
} vrs_vm;




vrs_vm* vrsInitVm(vrs_config* config);
void vrsDestroyVm(vrs_vm* vm);