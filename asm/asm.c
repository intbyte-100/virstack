#include "stdlib.h"
#include "asm.h"
#include "string.h"
#include "stdbool.h"


#define STRING_SWITCH(value, code) { \
    const char* switchString = value;        \
    if (false) ;                             \
    code                                     \
}

#define CASE(value, code) \
else if (strcmp(switchString, value) == 0) { \
    code \
}

#define DEFAULT(code) else {code}


const char delim[] = " ";

void compileCodeSection(char *line, context *ctx) {
    char *token = strtok(line, delim);
    int wordIndex = 0;
    int argsCount = 0;

    while (token != NULL) {
        wordIndex++;
        if (wordIndex != 1)
            goto compileOperands;

        STRING_SWITCH(token,
            CASE("mov", {
                argsCount = 2;
            })
            CASE("ld", {
                argsCount = 2;
            })
            CASE("ldh", {
                argsCount = 2;
            })
            DEFAULT(
                    printf("invalid syntax on %i line: unknown symbol \'%s\'\n", ctx->line, token);
                    continue;
            )
        );


        compileOperands:
        token = strtok(NULL, delim);
    }
    if (wordIndex != argsCount) {
        printf("invalid syntax on %i line: arguments cannot be less then %i\n", ctx->line, argsCount);
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
