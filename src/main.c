#include "stdio.h"
#include "config.h"
#include "vm.h"

int main(){
    vrs_config config = {
            .stackSize = 2048
    };

    vrs_vm* vm = vrsInitVm(&config);
    vrsDestroyVm(vm);
}