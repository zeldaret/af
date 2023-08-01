#include "macros.h"
#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "osint.h"

__OSEventState __osEventStateTab[OS_NUM_EVENTS] ALIGNED(8);
u32 __osPreNMI = FALSE;

void osSetEventMesg(OSEvent event, OSMesgQueue* mq, OSMesg msg) {
    register u32 saveMask;
    __OSEventState* es;

#ifdef _DEBUG
    if (event >= OS_NUM_EVENTS) {
        __osError(ERR_OSSETEVENTMESG, 1, event);
        return;
    }
#endif

    saveMask = __osDisableInt();

    es = &__osEventStateTab[event];

    es->messageQueue = mq;
    es->message = msg;

    if (event == OS_EVENT_PRENMI) {
        if (__osShutdown && !__osPreNMI) {
            osSendMesg(mq, msg, OS_MESG_NOBLOCK);
        }
        __osPreNMI = TRUE;
    }

    __osRestoreInt(saveMask);
}
