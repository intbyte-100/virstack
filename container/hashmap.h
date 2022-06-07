#pragma once

#include "list.h"

typedef struct {
    const char* name;
    long object;
} __vrs_node;

typedef struct {
    int hash;
    __vrs_node *nodes;
} __vrs_bucket;

typedef struct {
    vrs_list* _buckets;
}* vrs_hashmap;

vrs_hashmap vrsCreateHashmap();
void vrsPut(const char *name, void *object);
void* __vrsGetElement(const char* name);