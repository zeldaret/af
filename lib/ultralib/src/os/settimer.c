#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "osint.h"
#include "../io/viint.h"

int osSetTimer(OSTimer* t, OSTime countdown, OSTime interval, OSMesgQueue* mq, OSMesg msg) {
    OSTime time;
    OSTimer* next;
    u32 count;
    u32 value;
    u32 saveMask;

#ifdef _DEBUG
    if (!__osViDevMgr.active) {
        __osError(ERR_OSSETTIMER, 0);
        return 0;
    }
#endif

    t->next = NULL;
    t->prev = NULL;
    t->interval = interval;
    t->value = (countdown != 0) ? countdown : interval;
    t->mq = mq;
    t->msg = msg;

    saveMask = __osDisableInt();
    if (__osTimerList->next == __osTimerList) {

    } else {
        next = __osTimerList->next;
        count = osGetCount();
        value = count - __osTimerCounter;

        if (value < next->value) {
            next->value -= value;
        } else {
            next->value = 1;
        }
    }

    time = __osInsertTimer(t);
    __osSetTimerIntr(__osTimerList->next->value);
    __osRestoreInt(saveMask);

    return 0;
}
