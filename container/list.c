#include "list.h"
#include "malloc.h"
#include "memory.h"

void __vrsExtendList(vrs_list* list, int elementSize, int elementsCount)
{
    if (list->size >= list->array.size + elementsCount * elementSize) {
        int newSize = list->array.size*1.60;
        __vrsResizeList(list, newSize);
        list->array.size = newSize;
        list->size += elementsCount * elementSize;
    } else {
        list->size += elementsCount * elementSize;
    }
}

void __vrsResizeList(vrs_list* list, int newSize)
{
    list->array.values = realloc(list->array.values, newSize);
    list->array.size = newSize;
}

char * __vrsAddElement(vrs_list* list, int size)
{
    __vrsExtendList(list, size, 1);
    return &list->array.values[list->size - size];
}


vrs_list * vrsCreateList()
{
    vrs_list *list = malloc(sizeof(vrs_list));
    list->array.values = malloc(14);
    list->array.size = 14;
    return list;
}

void vrsDeleteList(vrs_list* list)
{
    free(list->array.values);
    free(list);
}

void __vrsAddAllFromArray(vrs_list* list, vrs_array* array)
{
    vrsExtendList(list, char, array->size);
    memcpy(array->values, list->array.values+list->size-array->size, array->size);
}

void __vrsAddAllFromList(vrs_list* list, vrs_list* fromList)
{
    vrsExtendList(list, char, fromList->size);
    memcpy(fromList->array.values, list->array.values+list->size, fromList->size);
}