#include <malloc.h>
#include <string.h>
#include "context.h"

context *createContext() {
    context* ctx = malloc(sizeof(context));
    ctx->stack = malloc(2048 * 2);
    ctx->code = malloc(2048 * 2);
}

void destroyContext(context *ctx) {
    free(ctx->stack);
    free(ctx->code);
    free(ctx);
}

