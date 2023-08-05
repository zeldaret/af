#include "PR/os_internal.h"
#include "viint.h"

__OSViContext* __osViGetNextContext(void) {
    return __osViNext;
}
