#include "stdio.h"
#include "string.h"
#include "vistack.h"

int main(int argc, char **argv){
    if(argc == 1) {
        printf("virstack virtual machine v0.1\n");
    } else if (strcmp(argv[1], "--load") == 0) {
        if (argv[2] == 0)
            printf("Error: --load requires vbc file specification\n");
        //TODO: implement vbc loader
    }
}