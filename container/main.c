#include <stdio.h>
#include "container.h"

int main(){
    vrs_hashmap map = vrsCreateHashmap();

    int i = vrsGetElement(map, "10");
    printf("%i\n", i);
}