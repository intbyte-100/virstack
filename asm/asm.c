#include "stdlib.h"
#include "asm.h"
#include "string.h"
#include "stdbool.h"
#include "instruction_set.h"
#include <errno.h>

#define SWITCH_BEGIN(value) \
    if (strcmp(COMPARABLE, value) == 0)


#define CASE(value) \
else if (strcmp(COMPARABLE, value) == 0)


#define DEFAULT else


const char delim[] = " ";

bool syntaxIsInvalid = false;

unsigned char parseRegister(char* value){
    errno = 0;
    if (value[0] != 'R')
        return 255;
    value[0] = ' ';

    long registerIndex = strtol(value, NULL, 10);

    if (errno == ERANGE || registerIndex > 15)
        return 255;

    return registerIndex;
}

void compileCodeSection(char *line, context *ctx) {
    char *token = strtok(line, delim);
    int wordIndex = 0;
    int argsCount = 0;

    while (token != NULL) {
        wordIndex++;
        unsigned char value;
        if (wordIndex == 1) {

            #define COMPARABLE token
            SWITCH_BEGIN("mov") {
                value = mov;
                argsCount = 2;
            } CASE("ld") {
                value = ld;
                argsCount = 2;
            } CASE("ldh") {
                value = ldh;
                argsCount = 2;
            } CASE("ldb") {
                value = ldb;
                argsCount = 2;
            } DEFAULT {
                printf("invalid syntax on %i line: unknown symbol \'%s\'\n", ctx->line, token);
                syntaxIsInvalid = true;
                continue;
            }

            if (!syntaxIsInvalid)
                pushToCodeSection(ctx, 1, &value);
        } else {
            if (value == mov) {
                unsigned char registerIndex = parseRegister(line);
                syntaxIsInvalid = syntaxIsInvalid || registerIndex == 255;
            }
        }

        token = strtok(NULL, delim);
    }
    if (wordIndex != argsCount) {
        printf("invalid syntax on %i line: arguments cannot be less then %i\n", ctx->line, argsCount);
        syntaxIsInvalid = true;
    }
}


void compileStackSection(char *line, context *ctx) {
    char *token = strtok(line, delim);

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, delim);
    }
}

void compileFile(FILE *file, context *ctx) {
    bool isStackSection = false;

    if (file == NULL) {
        printf("invalid file\n");
        exit(-1);
    }

    char *line = NULL;
    size_t size = 0;

    while ((getline(&line, &size, file)) != -1) {

        ctx->line++;

        if (strcmp(line, ".stack") == 0)
            isStackSection = true;
        else if (strcmp(line, ".code") == 0)
            isStackSection = false;

        if (isStackSection)
            compileStackSection(line, ctx);
        else
            compileCodeSection(line, ctx);
    }
}
