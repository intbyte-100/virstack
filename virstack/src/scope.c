#include <malloc.h>
#include "scope.h"

void vrsDestroyScope(vrs_scope *scope) {
    free(scope->code);
    free(scope->stack);
    free(scope);
}
