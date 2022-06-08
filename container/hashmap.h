#pragma once

#include "arraylist.h"

typedef struct {
    const char* name;
    long object;
} __vrs_node;

typedef struct {
    int hash;
    vrs_arraylist *nodes;
} __vrs_bucket;

typedef struct {
    vrs_arraylist* _buckets;
}* vrs_hashmap;

vrs_hashmap vrsCreateHashmap();
void vrsPut(const char *name, void *object);
void* __vrsGetElement(const char* name);