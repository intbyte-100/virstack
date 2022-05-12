#include "stdio.h"
#include "asm.h"

int main(int argc, char** argv){
    compileFile(fopen(argv[1], "r"), NULL);
}