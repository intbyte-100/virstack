#include "stdio.h"
#include "vistack.h"

int main(){

    vrsInit();

    vrs_config config = {
            .stackSize = 2048
    };

    vrs_vm* vm = vrsInitVm(&config);
    vrsDestroyVm(vm);
}