#include <PR/os_internal.h>
#include "viint.h"

u32 osViGetCurrentMode(void) {
    register u32 savedMask = __osDisableInt();
    register u32 modeType = __osViCurr->modep->type;

    __osRestoreInt(savedMask);
    return modeType;
}
