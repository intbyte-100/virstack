#include "stdlib.h"
#include "asm.h"
#include "string.h"
#include "stdbool.h"
#include "instruction_set.h"
#include <errno.h>
#include "context.h"


const char delim[] = " ";

unsigned char parseRegister(context *ctx, char *value) {
    bool invalidRegister = value[0] != 'R';
    char *error;

    long registerIndex = strtol(&value[1], &error, 10);

    if (*error != 0 || registerIndex > 5 || invalidRegister) {
        ctx->compilationFailed = true;
        printf("invalid syntax in %i line, %i word:\n\tthe unknown register name \'%s\'\n",
               ctx->line,
               ctx->_currentWord, value);
        return 255;
    }

    return registerIndex;
}


long parseInteger(context *ctx, char *value) {
    char *ptr = value;
    char *error;
    int base = 10;

    if (value[0] == '0') {
        if (value[1] == 'x') {
            ptr = &value[2];
            base = 16;
        } else if (value[1] == 'b') {
            ptr = &value[2];
            base = 2;
        }
    }

    long integer = strtol(ptr, &error, base);

    if (*error == 0)
        return integer;

    printf("invalid syntax in %i line, %i word:\n\tinvalid number \'%s\'\n", ctx->line, ctx->_currentWord, value);
    ctx->compilationFailed = true;
    return 0;

}

void compileCodeSection(char *line, context *ctx) {
    char *token = strtok(line, delim);
    ctx->_currentWord = 0;
    int argsCount = 0;

    unsigned char value = 255;

    while (token != NULL) {
        ctx->_currentWord++;
        if (ctx->_currentWord == 1) {

            if (strcmp(token, "mov") == 0) {
                value = mov;
                argsCount = 2;
            } else if (strcmp(token, "ld") == 0) {
                value = ld;
                argsCount = 2;
            } else if (strcmp(token, "ldh") == 0) {
                value = ldh;
                argsCount = 2;
            } else if (strcmp(token, "ldb") == 0) {
                value = ldb;
                argsCount = 2;
            } else {
                printf("invalid syntax in %i line, %i word:\n\tthe unknown symbol \'%s\'\n",
                       ctx->line,
                       ctx->_currentWord,
                       token);
                ctx->compilationFailed = true;
                continue;
            }

            pushToCodeSection(ctx, 1, &value);


        } else if (value == mov) {
            unsigned char registerIndex = parseRegister(ctx, token);
            pushToCodeSection(ctx, 1, &registerIndex);

        } else if (value >= ld && value <= ldb) {
            if (ctx->_currentWord == 2) {
                unsigned char registerIndex = parseRegister(ctx, token);
                pushToCodeSection(ctx, 1, &registerIndex);
            } else if (ctx->_currentWord == 3) {
                unsigned int address = parseInteger(ctx, token);
                pushToCodeSection(ctx, 4, &address);
            }
        }

        token = strtok(NULL, delim);
    }
    if (argsCount && ctx->_currentWord - 1 != argsCount) {
        printf("invalid syntax in %i line, %i word:"
               "\n\trequirement argument count = %i;"
               "\n\tprovided argument count = %i\n",
               ctx->line, ctx->_currentWord, argsCount, ctx->_currentWord - 1);
        ctx->compilationFailed = true;
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

        int i = 0;
        do {
            if (line[i] == '\n') line[i] = '\0';
            else if (line[i] == ',' || line[i] == '\t') line[i] = ' ';
        } while (line[++i] != '\0');

        bool isSectionDefinition = true;

        if (strcmp(line, ".stack") == 0)
            isStackSection = true;
        else if (strcmp(line, ".code") == 0)
            isStackSection = false;
        else
            isSectionDefinition = false;

        if (!isSectionDefinition) {
            if (isStackSection)
                compileStackSection(line, ctx);
            else
                compileCodeSection(line, ctx);
        }
    }
}
