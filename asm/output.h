#pragma once

#include "context.h"


void writePve(FILE* file, context *ctx);
void writeObjectFile(FILE* file, context *ctx, const char* format);