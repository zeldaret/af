#include "osint_debug.h"

u32 osThreadProfileReadCount(OSId id) {
#ifndef NDEBUG
    if (!__osThprofFlag) {
        __osError(139, 0);
        return 0;
    }
#endif

    if (id >= THPROF_IDMAX) {
#ifndef NDEBUG
        __osError(143, 1, id);
#endif
        return 0;
    }
    return thprof[id].count;
}

u32 osThreadProfileReadCountTh(OSThread* thread) {
    OSId id;

#ifndef NDEBUG
    if (!__osThprofFlag) {
        __osError(141, 0);
        return 0;
    }
#endif

    id = osGetThreadId(thread);

    if (id >= THPROF_IDMAX) {
#ifndef NDEBUG
        __osError(145, 1, id);
#endif
        return 0;
    }
    return thprof[id].count;
}
