#include "container.h"

int main(){
    vrs_linked_list *list = vrsLinkedList();
    vrsAddLinkedElement(list,(void*) 0x1);
    vrsAddLinkedElement(list,(void*) 0x2);
    vrsAddLinkedElement(list,(void*) 0x3);
    vrsAddLinkedElement(list,(void*) 0x4);
    vrsAddLinkedElement(list,(void*) 0x5);
    int size = list->size;
    for (int i = 0; i < size; ++i) {
        vrsRemoveElement(list, 0);
    }

    return 0;
}