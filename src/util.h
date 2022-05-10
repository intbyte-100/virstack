#pragma once

#include "malloc.h"

#define vrs_byte unsigned char
#define vrsMalloc(structure) ((structure*) malloc(sizeof(structure)))
#define vrsForceCast(type, value) *((type*) &value)