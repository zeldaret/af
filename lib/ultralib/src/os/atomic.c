#include "PR/os_internal.h"

int __osAtomicDec(unsigned int *p) {
    register u32 saveMask = __osDisableInt();
    int mask;

    if (*p) {
        (*p)--;
        mask = 1;
    } else {
        mask = 0;
    }
    __osRestoreInt(saveMask);
    return mask;
}
