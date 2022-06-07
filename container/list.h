#pragma once
#include "array.h"

#define vrsExtendList(list, type, count) __vrsExtendList(list, sizeof(type), count)
#define vrsResizeList(list, type, newSize) __vrsResizeList(list, newSize*sizeof(type))
#define vrsListSize(type, list) list->size / sizeof(type)
#define vrsAddElement(type, list, element) *((type*) __vrsAddElement(list, sizeof(type))) = element;
#define vrsAddAll(list, from) _Generic((from),\
    vrs_array*:  __vrsAddAllFromArray, \
    vrs_list*: __vrsAddAllFromList, \
    default: 0)(list, from)
#define vrsListElement(type, list, index) vrsArrayElement(type, (&list->array), index)


typedef struct
{
    vrs_array array;
    int size;

} vrs_list;

vrs_list* vrsCreateList();
void __vrsResizeList(vrs_list* list, int newSize);
void __vrsExtendList(vrs_list* list, int elementSize, int elementsCount);
char* __vrsAddElement(vrs_list* list, int size);
void vrsDeleteList(vrs_list* list);
void __vrsAddAllFromArray(vrs_list* list, vrs_array* array);
void __vrsAddAllFromList(vrs_list* list, vrs_list* fromList);