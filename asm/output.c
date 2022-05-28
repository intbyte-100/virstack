#include <string.h>
#include <err.h>
#include <stdlib.h>
#include "output.h"

void writePve(FILE *file, context *ctx) {
    fprintf(file, "vpe\n");
    fwrite(&ctx->stackSize, sizeof(int), 1, file);
    fwrite(ctx->stack, 1, ctx->stackSize, file);
    fwrite(&ctx->codeSectionSize, sizeof(int), 1, file);
    fwrite(ctx->code, 1, ctx->codeSectionSize, file);
}

void writeObjectFile(FILE *file, context *ctx, const char* format) {
    if (ctx->compilationFailed) return;

    printf("creating of the object file...\n");
    if(strcmp("vpe", format) == 0) {
        writePve(file, ctx);
    } else {
        errx(EXIT_FAILURE, "unknown output format '%s'\n", format);
    }
    printf("complete!\n");
}
