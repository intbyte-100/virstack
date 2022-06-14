
#include <malloc.h>
#include <string.h>
#include "hashmap.h"


__vrs_bucket* getBucket(vrs_hashmap map, const char *name){
    int bucketsCount = map->_buckets->size;
}

__vrs_node *getNode(__vrs_bucket *bucket, const char *name){
    vrs_iterator *iterator = vrsLinkedListIterator(bucket->nodes);

    while (iterator->has(iterator)) {
        __vrs_node *node = iterator->next(iterator);
        if(strcmp(name, node->name) == 0) {
            iterator->dispose(iterator);
            return node;
        }
    }

    iterator->dispose(iterator);

    return NULL;
}

vrs_hashmap vrsCreateHashmap() {
    vrs_hashmap map = malloc(sizeof(vrs_linked_list *));
    map->_buckets = vrsLinkedList();
}
