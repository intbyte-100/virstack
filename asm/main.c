#include <string.h>
#include <err.h>
#include "asm.h"
#include "output.h"
#include "opcode.h"


int main(int argc, char **argv) {
    char *format = 0;
    FILE *source;
    FILE *output;

    initOpcodes();
    printf("VRM asm: ");
    printf("version 0.0.1 alpha\n");

    if (argc == 1) {
        printf("Developer: intbyte company\n");
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') errx(1, "%s: invalid argument", argv[i]);

        if (i + 1 == argc) {
            errx(1, "%s: not specified arguments", argv[i]);
        }
        if (strcmp(argv[i], "-f") == 0) {
            format = argv[++i];
        } else if (strcmp(argv[i], "-c") == 0) {
            source = fopen(argv[++i], "r");
            if (source == NULL)
                errx(1, "%s: invalid file", argv[i]);
        } else if (strcmp(argv[i], "-o") == 0) {
            output = fopen(argv[++i], "w");
            if (output == NULL)
                errx(1, "%s: invalid file", argv[i]);
        }
    }

    context *ctx = createContext();
    
    compileFile(source, ctx);
    writeObjectFile(output, ctx, format);
    destroyContext(ctx);
}
