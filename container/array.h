#pragma once

#define vrsAllocArray(type, size) __vrsAllocArray(size*sizeof(type))
#define vrsArrayLength(type, array) array->size/sizeof(type)
#define vrsArrayElement(type, array, index) ((type*) &array->values[index*sizeof(type)])
#define __vrsSortGenericArray(type, array, size)                 \
                                                                \
    for(int _vrs_i = 0; _vrs_i < size; _vrs_i++) {               \
        for(int _vrs_j = _vrs_i + 1; _vrs_j < size; _vrs_j++) {  \
            if (array[_vrs_i] > array[_vrs_j]) {                 \
                type _vrs_swap = array[_vrs_i];                  \
                array[_vrs_i] = array[_vrs_j];                   \
                array[_vrs_j] = _vrs_swap;                       \
            }\
        }\
    }\






typedef struct {
    char *values;
    int size;
} vrs_array;


void vrsDeleteArray(vrs_array *vrsArray);

vrs_array *__vrsAllocArray(int size);

void _vrsCharArraySort(char* array, int size);
void _vrsShortArraySort(short* array, int size);
void _vrsIntArraySort(int* array, int size);
void _vrsFloatArraySort(float* array, int size);
void _vrsDoubleArraySort(double * array, int size);
void _vrsLongArraySort(long* array, int size);