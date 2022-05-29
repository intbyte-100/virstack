#pragma once

typedef struct {
    int stackSize;
    int codeSectionSize;
    unsigned char *code;
    unsigned char *stack;
} vrs_scope;