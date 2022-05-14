#pragma once
#include <stdio.h>

typedef struct {
    int stackSize;
    int codeSectionSize;
    char* stack;
    unsigned char* code;
    int line;
} context;

context *createContext();
void destroyContext(context* ctx);
void pushToStack(context* ctx, int count, void * data);
void pushToCodeSection(context* ctx, int count, void * data);
FILE* buildExecutable(context* ctx);