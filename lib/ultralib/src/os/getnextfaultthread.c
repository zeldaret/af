#include "PR/os_internal.h"
#include "osint.h"

OSThread *__osGetNextFaultedThread(OSThread *lastFault) {
    register int saveMask = __osDisableInt();
    register OSThread *fault;

    if (lastFault == NULL) {
        fault = __osActiveQueue;
    } else {
        fault = lastFault;
    }

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

