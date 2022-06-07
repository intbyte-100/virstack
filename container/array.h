#pragma once

#define vrsAllocArray(type, size) __vrsAllocArray(size*sizeof(type))
#define vrsArrayLength(type, array) array->size/sizeof(type)
#define vrsArrayElement(type, array, index) ((type*) &array->values[index*sizeof(type)])

typedef struct
{
    char *values;
    int size;
} vrs_array;



void vrsDeleteArray(vrs_array* vrsArray);
vrs_array* __vrsAllocArray(int size);