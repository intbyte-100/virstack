#include <stdio.h>
#include <malloc.h>
#include "container.h"

int main(){
    vrs_hashmap map = vrsCreateHashmap();

    vrsPut(map, "test", 10);

    *(long*) vrsPut(map, "test 2", (void*) 404) = 1000;
    int i = *(int*) vrsGetElement(map, "test 2");
    vrsDisposeHashmap(map, 0);
    printf("%i\n", i);
}