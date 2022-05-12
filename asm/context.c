#include <malloc.h>
#include "context.h"

context *createContext() {
    context* ctx = malloc(sizeof(context));
    ctx->stack = malloc(2048);
    ctx->code = malloc(2048);
    ctx->stackSize = 0;
    ctx->codeSectionSize = 0;
}

void destroyContext(context *ctx) {
    free(ctx->stack);
    free(ctx->code);
    free(ctx);
}
