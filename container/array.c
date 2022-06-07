#include "array.h"
#include "malloc.h"


vrs_array *__bdbAllocArray(int size){
    vrs_array *array = malloc(sizeof(vrs_array));
    array->size = size;
    array->values = malloc(size);
    return array;
}

void bdbDeleteArray(vrs_array *array){
    free(array->values);
    free(array);
}