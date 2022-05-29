#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "loader.h"

int vrs_loadVpe(FILE *file, vrs_scope *scope) {
    char magicNumber[5];
    magicNumber[4] = '\0';
    fread(&magicNumber, 1, 4, file);
    if(strcmp("vpe\n", magicNumber) != 0)
        return 1;

    fread(&scope->stackSize, 1, 4, file);
    scope->stack = malloc(scope->stackSize);
    fread(scope->stack, 1, scope->stackSize, file);
    fread(&scope->codeSectionSize, 1, 4, file);
    scope->code = malloc(scope->codeSectionSize);
    fread(scope->code, 1, scope->codeSectionSize, file);
    return 0;
}
