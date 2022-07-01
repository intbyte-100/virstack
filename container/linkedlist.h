#pragma once

#include "iteraror.h"

struct vrs_list_node {
    struct vrs_list_node* next;
    void* value;
};

typedef struct vrs_list_node vrs_list_node;

typedef struct {
    int size;
    vrs_list_node *first;
} vrs_linked_list;

vrs_linked_list *vrsLinkedList();
void vrsAddLinkedElement(vrs_linked_list *list,void *element);
void **vrsLinkedListElement(vrs_linked_list *list, unsigned int index);
void *vrsRemoveElement(vrs_linked_list *list, unsigned int index);
vrs_iterator *vrsLinkedListIterator(vrs_linked_list *list);
