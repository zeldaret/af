#include "osint_debug.h"

u32 osThreadProfileReadCount(OSId id) {
    if (!__osThprofFlag) {
        __osError(139, 0);
        return 0;
    }

    if (id >= THPROF_IDMAX) {
        __osError(143, 1, id);
        return 0;
    }
    return thprof[id].count;
}

u32 osThreadProfileReadCountTh(OSThread* thread) {
    OSId id;

    if (!__osThprofFlag) {
        __osError(141, 0);
        return 0;
    }

    id = osGetThreadId(thread);

    if (id >= THPROF_IDMAX) {
        __osError(145, 1, id);
        return 0;
    }
    return thprof[id].count;
}
