#include "stdio.h"
#include "asm.h"

int main(int argc, char** argv){
    context *ctx = createContext();
    FILE *file = fopen(argv[1], "r");
    compileFile(file, ctx);
    fclose(file);
    destroyContext(ctx);
    return ctx->compilationFailed;
}