#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "osint.h"
#include "../io/viint.h"

void osSetTime(OSTime time) {

#ifdef _DEBUG
    if (!__osViDevMgr.active) {
        __osError(ERR_OSSETTIME, 0);
        return;
    }
#endif

    __osCurrentTime = time;
}
