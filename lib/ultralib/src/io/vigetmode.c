#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/viint.h"

u32 osViGetCurrentMode(void) {
    register u32 saveMask;
    register u32 modeType;

#ifdef _DEBUG
    if (!__osViDevMgr.active) {
        __osError(ERR_OSVIGETCURRENTMODE, 0);
        return -1;
    }
#endif

    saveMask = __osDisableInt();
    modeType = (u32)__osViCurr->modep->type;

    __osRestoreInt(saveMask);
    return modeType;
}
