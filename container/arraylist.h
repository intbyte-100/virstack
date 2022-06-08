#pragma once
#include "array.h"

#define vrsExtendArrayList(list, type, count) __vrsExtendArrayList(list, sizeof(type), count)
#define vrsResizeArrayList(list, type, newSize) __vrsResizeArrayList(list, newSize*sizeof(type))
#define vrsArrayListSize(type, list) list->size / sizeof(type)
#define vrsAddElement(type, list, element) *((type*) __vrsAddElement(list, sizeof(type))) = element;
#define vrsAddAll(list, from) _Generic((from),\
    vrs_array*:  __vrsAddAllFromArray, \
    vrs_list*: __vrsAddAllFromArrayList, \
    default: 0)(list, from)
#define vrsArrayListElement(type, list, index) vrsArrayElement(type, (&list->array), index)


typedef struct
{
    vrs_array array;
    int size;

} vrs_arraylist;

vrs_arraylist* vrsCreateArrayList();
void __vrsResizeArrayList(vrs_arraylist* list, int newSize);
void __vrsExtendArrayList(vrs_arraylist* list, int elementSize, int elementsCount);
char* __vrsAddElement(vrs_arraylist* list, int size);
void vrsDeleteArrayList(vrs_arraylist* list);
void __vrsAddAllFromArray(vrs_arraylist* list, vrs_array* array);
void __vrsAddAllFromArrayList(vrs_arraylist* list, vrs_arraylist* fromArrayList);