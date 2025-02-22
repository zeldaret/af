#include "PR/os_internal.h"
#include "PRinternal/osint.h"

OSThread* __osGetNextFaultedThread(OSThread* lastFault) {
    register int saveMask = __osDisableInt();
    register OSThread* fault;

    fault = lastFault == NULL ? __osActiveQueue : lastFault;

    while (fault->priority != -1) {
        if ((fault->flags & OS_FLAG_FAULT) != 0 && fault != lastFault) {
            break;
        }
        fault = fault->tlnext;
    }

    if (fault->priority == -1) {
        fault = NULL;
    }

    __osRestoreInt(saveMask);
    return fault;
}
