#pragma once

#include "linkedlist.h"

typedef struct {
    char* name;
    long object;
} __vrs_node;

typedef struct {
    int hash;
    vrs_linked_list *nodes;
} __vrs_bucket;

typedef struct {
    vrs_linked_list *_buckets;
}* vrs_hashmap;

vrs_hashmap vrsCreateHashmap();
void* vrsPut(vrs_hashmap map, const char *name, void *object);
void* vrsGetElement(vrs_hashmap map,const char* name);
void vrsDisposeHashmap(vrs_hashmap map, vrs_dispose dispose);
void vrsClearHashmap(vrs_hashmap map, vrs_dispose dispose);