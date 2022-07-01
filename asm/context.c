#include <malloc.h>
#include <string.h>
#include "context.h"

context *createContext() {
    context* ctx = malloc(sizeof(context));
    ctx->stack = malloc(2048 * 2);
    ctx->code = malloc(2048 * 2);
    ctx->localLabels = vrsCreateHashmap();
    ctx->globalLabels = vrsCreateHashmap();
    return ctx;
}

void destroyContext(context *ctx) {
    vrsDisposeHashmap(ctx->globalLabels, 0);
    vrsDisposeHashmap(ctx->localLabels, 0);
    free(ctx->stack);
    free(ctx->code);
    free(ctx);
}

