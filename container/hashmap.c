
#include <malloc.h>
#include <string.h>
#include "hashmap.h"


__vrs_bucket* getBucket(vrs_hashmap map, const char *name){
    int bucketsCount = vrsListSize(__vrs_bucket*, map->_buckets);
}

__vrs_node *getNode(__vrs_bucket *bucket, const char *name){
    for (int i = 0; i < vrsListSize(__vrs_node*, bucket->nodes); ++i) {
        __vrs_node *node = vrsListElement(__vrs_node, bucket->nodes, i);
        if(strcmp(name, node->name) == 0)
            return node;
    }
    return NULL;
}

vrs_hashmap vrsCreateHashmap() {
    vrs_hashmap map = malloc(sizeof(vrs_list *));
    map->_buckets = vrsCreateList();
}
