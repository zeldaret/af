#include "PR/os_internal.h"

int __osAtomicDec(unsigned int* p) {
    u32 mask;
    int result;

    mask = __osDisableInt();
    if (*p) {
        (*p)--;
        result = 1;
    } else {
        result = 0;
    }
    __osRestoreInt(mask);
    return result;
}
