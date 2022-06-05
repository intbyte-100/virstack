#pragma once

#include "malloc.h"

#define vrs_byte unsigned char
#define vrsMalloc(structure) ((structure*) malloc(sizeof(structure)))
#define vrsForceCast(type, value) *((type*) &value)
#define vrsDispose(object) _Generic((object), vrs_vm*: vrsDestroyVm, vrs_scope*: vrsDestroyScope)(object)