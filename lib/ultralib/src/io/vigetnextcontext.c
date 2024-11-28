#include "PR/os_internal.h"
#include "PRinternal/viint.h"

__OSViContext* __osViGetNextContext(void) {
    return __osViNext;
}
