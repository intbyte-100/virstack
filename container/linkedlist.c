#include <malloc.h>
#include <stdbool.h>
#include "linkedlist.h"

vrs_linked_list *vrsLinkedList() {
    return malloc(sizeof(vrs_linked_list));
}

void* vrsAddLinkedElement(vrs_linked_list *list, void *element) {
    vrs_list_node *node = malloc(sizeof(vrs_list_node));
    node->value = element;
    list->size++;

    if (list->first == NULL) {
        list->first = node;
        return &node->value;
    }

    vrs_list_node *each = list->first;
    while (true) {
        if (each->next == NULL) {
            each->next = node;
            return &node->value;
        }
        each = each->next;
    }
}

void **vrsLinkedListElement(vrs_linked_list *list, unsigned int index) {
    int i = 0;
    vrs_list_node *node = list->first;
    while (i++ != index) {
        node = node->next;
    }
    return &node->value;
}

void *vrsRemoveElement(vrs_linked_list *list, unsigned int index) {
    if (index > list->size) return NULL;
    vrs_list_node *node = list->first->next;
    list->size--;
    if (index == 0) {
        void *value = list->first->value;
        free(list->first);
        list->first = node;
        return value;
    }

    node = list->first;

    for (int i = 0; i < index; ++i) {
        if (i == index - 1) {
            void *value = node->value;
            vrs_list_node *removableNode = node->next;
            node->next = node->next->next;
            free(removableNode);
            return value;
        }
        node = node->next;
    }
}

typedef struct {
    vrs_iterator iterator;
    vrs_linked_list *list;
    vrs_list_node *node;
    int nodeIndex;
} vrs_linked_list_iterator;

int linkedListHas(vrs_iterator *iterator) {
    vrs_linked_list_iterator *iter = (vrs_linked_list_iterator *) iterator;
    return iter->nodeIndex < iter->list->size;
}

vrs_iterator_element linkedListNext(vrs_iterator *iterator) {
    vrs_linked_list_iterator *iter = (vrs_linked_list_iterator *) iterator;

    iter->nodeIndex++;
    vrs_list_node *node = iter->node;
    iter->node = iter->node->next;
    return node->value;
}

void linkedListIteratorDispose(vrs_iterator *iterator) {
    free(iterator);
}

vrs_iterator *vrsLinkedListIterator(vrs_linked_list *list) {
    vrs_linked_list_iterator *iterator = malloc(sizeof(vrs_linked_list_iterator));
    iterator->list = list;
    iterator->node = list->first;
    iterator->nodeIndex = 0;
    iterator->iterator.has = &linkedListHas;
    iterator->iterator.next = &linkedListNext;
    iterator->iterator.dispose = &linkedListIteratorDispose;
    return (vrs_iterator *) iterator;
}

void vrsClearLinkedList(vrs_linked_list *list, vrs_dispose dispose) {
    int i = 0;
    vrs_list_node *node = list->first;
    vrs_list_node *next;

    while (i++ != list->size) {
        next = node->next;
        if (dispose)
            dispose(node->value);
        free(node);
        node = next;
    }

    list->size = 0;
}
