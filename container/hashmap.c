
#include <malloc.h>
#include "hashmap.h"

vrs_hashmap vrsCreateHashmap() {
    vrs_hashmap map = malloc(sizeof(vrs_list *));
    map->_buckets = vrsCreateList();
}
