#include <malloc.h>
#include <string.h>
#include "hashmap.h"

int hashCode(const char *name) {
    int i = 0;
    int value = 0;
    do {
        value = 31 * value + name[i];
    } while (name[++i] != 0);
    return value;
}

__vrs_bucket* getBucket(vrs_hashmap map, int hash){
    vrs_iterator *iterator = vrsLinkedListIterator(map->_buckets);

    vrs_foreach(iterator, __vrs_bucket *bucket, {
        if (bucket->hash == hash) {
            iterator->dispose(iterator);
            return bucket;
        }
    })
    iterator->dispose(iterator);
    return NULL;
}

__vrs_node *getNode(__vrs_bucket *bucket, const char *name){
    if (bucket == NULL) return NULL;

    vrs_iterator *iterator = vrsLinkedListIterator(bucket->nodes);

    while ((iterator)->has(iterator)) {
        __vrs_node *node = (iterator)->next(iterator);
        {
            if (strcmp(name, node->name) == 0) {
                iterator->dispose(iterator);
                return node;
            }
        }
    }


    iterator->dispose(iterator);

    return NULL;
}

vrs_hashmap vrsCreateHashmap() {
    vrs_hashmap map = malloc(sizeof(vrs_linked_list *));
    map->_buckets = vrsLinkedList();
    return map;
}

void* vrsGetElement(vrs_hashmap map, const char *name) {
    __vrs_node *node = getNode(getBucket(map, hashCode(name)), name);

    if (node != NULL)
        return (void *) node->object;
    else
        return NULL;
}


static __vrs_node* createNode(const char *name, void *object) {
    __vrs_node *node = malloc(sizeof(__vrs_node));
    node->name = name;
    node->object = (long) object;
    return node;
}

void vrsPut(vrs_hashmap map, const char *name, void *object) {
    int hash = hashCode(name);
    __vrs_bucket *bucket = getBucket(map, hash);

    if (bucket == NULL) {
        bucket = malloc(sizeof(__vrs_bucket));
        bucket->hash = hash;
        bucket->nodes = vrsLinkedList();
        vrsAddLinkedElement(bucket->nodes, createNode(name, object));
        vrsAddLinkedElement(map->_buckets, bucket);
        return;
    }

    __vrs_node *node = getNode(bucket, name);

    if (node == NULL)
        node = createNode(name, object);

    vrsAddLinkedElement(bucket->nodes, node);
}
