#include <malloc.h>
#include <string.h>
#include "context.h"

context *createContext() {
    context* ctx = malloc(sizeof(context));
    ctx->stack = malloc(2048);
    ctx->code = malloc(2048);
}

void destroyContext(context *ctx) {
    free(ctx->stack);
    free(ctx->code);
    free(ctx);
}

void pushToCodeSection(context *ctx, int count, void *data) {
    memcpy(&ctx->code[ctx->codeSectionSize], data, count);
    ctx->codeSectionSize+=count;
}
