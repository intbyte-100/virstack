#include <stdio.h>
#include "container.h"

int main(){
    vrs_linked_list *list = vrsLinkedList();
    vrsAddLinkedElement(list,(void*) 0x1);
    vrsAddLinkedElement(list,(void*) 0x2);
    vrsAddLinkedElement(list,(void*) 0x3);
    vrsAddLinkedElement(list,(void*) 0x4);
    vrsAddLinkedElement(list,(void*) 0x5);


    vrs_iterator *iter = vrsLinkedListIterator(list);

    vrs_foreach(iter, int next, {
        printf("%i\n", next);
    })

    iter->dispose(iter);

    return 0;
}