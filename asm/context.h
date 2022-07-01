#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "../container/container.h"

typedef struct {
    int stackSize;
    int codeSectionSize;
    char* stack;
    unsigned char* code;
    int line;
    bool compilationFailed;
    int currentWord;
    vrs_hashmap localLabels;
    vrs_hashmap globalLabels;
} context;

context *createContext();
void destroyContext(context* ctx);
FILE* buildExecutable(context* ctx);

inline static void pushToStack(context* ctx, int count, void * data) {
    if (ctx->compilationFailed) return;
    memcpy(&ctx->stack[ctx->stackSize], data, count);
    ctx->stackSize += count;
}

inline static void pushToCodeSection(context* ctx, int count, void * data){
    if (ctx->compilationFailed) return;
    memcpy(&ctx->code[ctx->codeSectionSize], data, count);
    ctx->codeSectionSize += count;
}