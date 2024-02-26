#include "osint_debug.h"

void osThreadProfileStop(void) {
    register u32 saveMask;
    int i;
    OSId id;
    u32 now_time = osGetCount();

    saveMask = __osDisableInt();

#ifndef NDEBUG
    if (__osThprofFlag == 0) {
#if BUILD_VERSION >= VERSION_L
        __osRestoreInt(saveMask);
        __osError(138, 0);
#else
        __osError(138, 0);
        __osRestoreInt(saveMask);
#endif
        return;
    }
#endif

    if (__osThprofFunc != NULL) {
        id = osGetThreadId(0);

        if (id < THPROF_IDMAX) {
            thprof[id].time += now_time - __osThprofLastTimer;
        } else {
#ifndef NDEBUG
#if BUILD_VERSION >= VERSION_L
            __osRestoreInt(saveMask);
#endif
            __osError(147, 1, id);
#if BUILD_VERSION >= VERSION_L
            saveMask = __osDisableInt();
#endif
#endif
        }
    }
    __osThprofFunc = NULL;

    for (i = 0; i < THPROF_IDMAX; i++) {
        thprof[i].flag = 0;
    }
    __osRestoreInt(saveMask);
}
