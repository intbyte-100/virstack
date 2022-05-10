#include "stdio.h"
#include "vistack.h"

int main(){

    /**
     * ldb R0, 0x0 ; load the data to registers from the stack
     * ldb R1, 0x1
     * ldb R2, 0x1
     *
     * add R0, R0, R1
     * mul R0, R0, R2
     *
     * strh R0, 0x0 ; write data to the stack
     **/

    vrs_byte code[] = {
            ldb, 0, 0, 0, 0, 0,
            ldb, 1, 1, 0, 0, 0,
            ldb, 2, 2, 0, 0, 0,
            add, 0, 0, 1,
            mul, 0, 0, 2,
            strh, 0, 0, 0, 0, 0,
            exit
    };

    vrsInit();

    vrs_config config = {
            .stackSize = 2048
    };

    vrs_vm* vm = vrsInitVm(&config);
    vm->stack[0] = 2;
    vm->stack[1] = 3;
    vm->stack[2] = 5;

    vrsExecute(vm, (unsigned char *) &code);
    vrsDestroyVm(vm);
}