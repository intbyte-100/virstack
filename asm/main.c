#include "stdio.h"
#include "asm.h"

int main(int argc, char** argv){
    context *ctx = createContext();
    compileFile(fopen(argv[1], "r"), ctx);
    return ctx->compilationFailed;
}