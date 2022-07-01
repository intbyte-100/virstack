#include <err.h>
#include "stdlib.h"
#include "asm.h"
#include "string.h"
#include "stdbool.h"
#include "opcode.h"
#include "context.h"


const char delim[] = " ";


int *parseDefinitionLabel(context *ctx, char *token) {
    bool isGlobal = (strcmp(token, "global") == 0);

    if (isGlobal)
        token = strtok(NULL, delim);

    size_t length = strlen(token);

    if (token[length - 1] == ':' && token[0] >= '0' && token[0] <= '9') {
        return vrsPut(isGlobal ? ctx->globalLabels : ctx->localLabels, token, 0);
    }

    warnx("invalid syntax in %i line, %i word:\n\tinvalid label definition \'%s\'",
          ctx->line,
          ctx->currentWord, token);
    ctx->compilationFailed = true;

    return NULL;
}

int* getLabel(context *ctx, char *token) {
    int *local = vrsGetElement(ctx->localLabels, token);
    int *global = vrsGetElement(ctx->globalLabels, token);

    if (local != NULL)
        return local;
    return global;
}

unsigned char parseRegister(context *ctx, char *value) {
    bool invalidRegister = value[0] != 'R';
    char *error;

    long registerIndex = strtol(&value[1], &error, 10);

    if (*error != 0 || registerIndex > 5 || invalidRegister) {
        ctx->compilationFailed = true;
        warnx("invalid syntax in %i line, %i word:\n\tthe unknown register name \'%s\'",
              ctx->line,
              ctx->currentWord, value);
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

    warnx("invalid syntax in %i line, %i word:\n\tinvalid number \'%s\'", ctx->line, ctx->currentWord, value);
    ctx->compilationFailed = true;
    return 0;

}

void compileCodeSection(char *token, context *ctx) {

    ctx->currentWord = 0;
    int argsCount = 0;

    unsigned char value = 255;
    char *operandsType = NULL;

    while (token != NULL) {
        bool knownSymbol = false;
        ctx->currentWord++;

        if (ctx->currentWord == 1) {

            vrs_iterator *iter = vrsLinkedListIterator(opcodes);
            vrs_foreach(iter, opcode *i, {
                if (strcmp(i->name, token) == 0) {
                    knownSymbol = true;
                    argsCount = i->argc;
                    operandsType = &i->operands;
                    value = i->opcode;
                    break;
                }
            })
            iter->dispose(iter);

            if (!knownSymbol) {
                ctx->compilationFailed = true;
                warnx("invalid syntax in %i line, %i word:\n\tthe unknown symbol \'%s\'\n",
                      ctx->line,
                      ctx->currentWord,
                      token);
                break;
            }
            pushToCodeSection(ctx, 1, &value);


        } else {
            char i = operandsType[ctx->currentWord - 2];
            if (i == REGISTER) {
                unsigned char registerIndex = parseRegister(ctx, token);
                pushToCodeSection(ctx, 1, &registerIndex);
            } else if (i > REGISTER || i <= I64) {
                unsigned long number = parseInteger(ctx, token);
                pushToCodeSection(ctx, i, &number);
            }
        }

        token = strtok(NULL, delim);
    }
    if (ctx->currentWord && ctx->currentWord - 1 != argsCount) {
        warnx("invalid syntax in %i line, %i word:"
              "\n\trequired argument count = %i;"
              "\n\tprovided argument count = %i",
              ctx->line, ctx->currentWord, argsCount, ctx->currentWord - 1);
        ctx->compilationFailed = true;
    }
}


void compileStackSection(char *token, context *ctx) {

    ctx->currentWord = 0;

    char *tokens[2] = {NULL, NULL};
    while (token != NULL) {
        if (ctx->currentWord == 3) {
            ctx->compilationFailed = true;
            warnx("invalid syntax in %i line, %i word:"
                  "\n\trequirement argument count = 2;"
                  "\n\tprovided argument count = %i\n",
                  ctx->line, ctx->currentWord, ctx->currentWord);
            break;
        }
        tokens[ctx->currentWord] = token;
        token = strtok(NULL, delim);
        ctx->currentWord++;
    }

    if (tokens[0] == NULL) return;

    ctx->currentWord = 2;
    if (strcmp(tokens[0], "word") == 0) {
        long value = parseInteger(ctx, tokens[1]);
        pushToStack(ctx, 8, &value);
    } else if (strcmp(tokens[0], "half") == 0) {
        int value = parseInteger(ctx, tokens[1]);
        pushToStack(ctx, 4, &value);
    } else if (strcmp(tokens[0], "little") == 0) {
        short value = parseInteger(ctx, tokens[1]);
        pushToStack(ctx, 2, &value);
    } else if (strcmp(tokens[0], "byte") == 0) {
        char value = parseInteger(ctx, tokens[1]);
        pushToStack(ctx, 1, &value);
    } else {
        warnx("invalid syntax in %i line, %i word:\n\tthe unknown symbol \'%s\'\n",
              ctx->line,
              ctx->currentWord,
              tokens[0]);
        ctx->compilationFailed = true;
    }
}

void compileFile(FILE *file, context *ctx) {
    printf("compiling...\n");
    bool isStackSection = false;

    if (file == NULL) {
        warnx("invalid file\n");
        exit(-1);
    }

    char *line = NULL;
    size_t size = 0;

    while ((getline(&line, &size, file)) != -1) {

        ctx->line++;

        int i = 0;
        do {
            if (line[i] == '\n' || line[i] == ';') line[i] = '\0';
            else if (line[i] == ',' || line[i] == '\t') line[i] = ' ';
        } while (line[++i] != '\0');

        char *token = strtok(line, delim);

        bool isSectionDefinition = true;

        if (token != NULL && strcmp(token, "section") == 0) {
            token = strtok(NULL, delim);
            if (strcmp(token, ".stack") == 0)
                isStackSection = true;
            else if (strcmp(token, ".code") == 0)
                isStackSection = false;
            else {
                errx(1, "invalid syntax in %i line, %i word:\n\tinvalid section name \'%s\'\n",
                     ctx->line,
                     ctx->currentWord,
                     token);
            }
        } else
            isSectionDefinition = false;

        if (!isSectionDefinition) {
            if (isStackSection)
                compileStackSection(token, ctx);
            else
                compileCodeSection(token, ctx);
        }
    }

    printf(ctx->compilationFailed ? "compilation is failed.\n" : "compilation is complete.\n");
}