#include "osint_debug.h"

void osThreadProfileStop(void) {
    register u32 saveMask;
    int i;
    OSId id;
    u32 now_time = osGetCount();

    saveMask = __osDisableInt();

    if (__osThprofFlag == 0) {
        __osRestoreInt(saveMask);
        __osError(138, 0);
        return;
    }

    if (__osThprofFunc != NULL) {
        id = osGetThreadId(0);

        if (id < THPROF_IDMAX) {
            thprof[id].time += now_time - __osThprofLastTimer;
        } else {
            __osRestoreInt(saveMask);
            __osError(147, 1, id);
            saveMask = __osDisableInt();
        }
    }
    __osThprofFunc = NULL;

    for (i = 0; i < THPROF_IDMAX; i++) {
        thprof[i].flag = 0;
    }
    __osRestoreInt(saveMask);
}
