#include "arraylist.h"
#include "malloc.h"
#include "memory.h"

void __vrsExtendArrayList(vrs_arraylist* list, int elementSize, int elementsCount)
{
    if (list->size >= list->array.size + elementsCount * elementSize) {
        int newSize = list->array.size*1.60f;
        __vrsResizeArrayList(list, newSize);
        list->array.size = newSize;
        list->size += elementsCount * elementSize;
    } else {
        list->size += elementsCount * elementSize;
    }
}

void __vrsResizeArrayList(vrs_arraylist* list, int newSize)
{
    list->array.values = realloc(list->array.values, newSize);
    list->array.size = newSize;
}

char * __vrsAddElement(vrs_arraylist* list, int size)
{
    __vrsExtendArrayList(list, size, 1);
    return &list->array.values[list->size - size];
}


vrs_arraylist * vrsCreateArrayList()
{
    vrs_arraylist *list = malloc(sizeof(vrs_arraylist));
    list->array.values = malloc(14);
    list->array.size = 14;
    return list;
}

void vrsDeleteArrayList(vrs_arraylist* list)
{
    free(list->array.values);
    free(list);
}

void __vrsAddAllFromArray(vrs_arraylist* list, vrs_array* array)
{
    vrsExtendArrayList(list, char, array->size);
    memcpy(array->values, list->array.values+list->size-array->size, array->size);
}

void __vrsAddAllFromArrayList(vrs_arraylist* list, vrs_arraylist* fromArrayList)
{
    vrsExtendArrayList(list, char, fromArrayList->size);
    memcpy(fromArrayList->array.values, list->array.values+list->size, fromArrayList->size);
}