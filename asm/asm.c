#include <stdlib.h>
#include "asm.h"
#include "string.h"


void compileFile(FILE *file, context *ctx) {
    if (file == NULL) {
        printf("invalid file\n");
        exit(-1);
    }

    char line[256];
    char delim[] = " ";

    while (fgets(line, 256, file) != NULL){
        char* token = strtok(line, delim);

        while (token != NULL){
            printf("%s\n", token);
            token = strtok(NULL, delim);
        }
    }
}
