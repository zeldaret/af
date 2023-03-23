#include "osint_debug.h"

OSTime osThreadProfileReadTime(OSId id) {
    OSTime adjust = 0;
    u32 now_time = osGetCount();

#ifndef NDEBUG
    if (!__osThprofFlag) {
        __osError(140, 0);
        return 0;
    }
#endif
    if (id >= THPROF_IDMAX) {
#ifndef NDEBUG
        __osError(144, 1, id);
#endif
        return 0;
    }

    if (id == osGetThreadId(NULL) && __osThprofFunc != NULL) {
        adjust = now_time - __osThprofLastTimer;
    }
    return thprof[id].time + adjust;
}

OSTime osThreadProfileReadTimeTh(OSThread* thread) {
    OSId id;
    OSTime adjust = 0;
    u32 now_time = osGetCount();

#ifndef NDEBUG
    if (!__osThprofFlag) {
        __osError(142, 0);
        return 0;
    }
#endif

    id = osGetThreadId(thread);

    if (id >= THPROF_IDMAX) {
#ifndef NDEBUG
        __osError(146, 1, id);
#endif
        return 0;
    }

    if (id == osGetThreadId(NULL) && __osThprofFunc != NULL) {
        adjust = now_time - __osThprofLastTimer;
    }
    return thprof[id].time + adjust;
}
