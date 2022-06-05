#pragma once

typedef struct {
    int stackSize;
    int codeSectionSize;
    unsigned char *code;
    unsigned char *stack;
} vrs_scope;


void vrsDestroyScope(vrs_scope* scope);

