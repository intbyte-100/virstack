#include <malloc.h>
#include <stdbool.h>
#include "linkedlist.h"

vrs_linked_list *vrsLinkedList() {
    return malloc(sizeof(vrs_linked_list));
}

void vrsAddLinkedElement(vrs_linked_list *list, void *element) {
    vrs_list_node *node = malloc(sizeof(vrs_list_node));
    node->value = element;
    list->size++;

    if (list->first == NULL) {
        list->first = node;
        return;
    }

    vrs_list_node* each = list->first;
    while (true){
        if(each->next == NULL) {
            each->next = node;
            return;
        }
        each = each->next;
    }
}

void **vrsGetElement(vrs_linked_list *list, unsigned int index) {
    int i = 0;
    vrs_list_node* node = list->first;
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
