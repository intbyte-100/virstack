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

void _vrsIntArraySort(int *array, int size) {
    __vrsSortGenericArray(int, array, size);
}

void _vrsCharArraySort(char *array, int size) {
    __vrsSortGenericArray(char, array, size);
}

void _vrsShortArraySort(short *array, int size) {
    __vrsSortGenericArray(short, array, size);
}

void _vrsFloatArraySort(float *array, int size) {
    __vrsSortGenericArray(float, array, size);
}

void _vrsDoubleArraySort(double *array, int size) {
    __vrsSortGenericArray(double, array, size);
}

void _vrsLongArraySort(long *array, int size) {
    __vrsSortGenericArray(long, array, size);
}
