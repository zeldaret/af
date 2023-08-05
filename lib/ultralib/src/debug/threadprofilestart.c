#include "osint_debug.h"

void osThreadProfileStart(void) {
    register u32 saveMask;

#ifndef NDEBUG
    if (!__osThprofFlag) {
        __osError(136, 0);
        return;
    }
    if (__osThprofFunc != NULL) {
        __osError(137, 0);
        return;
    }
#endif

    saveMask = __osDisableInt();

    __osThprofLastTimer = osGetCount();
    __osThprofFunc = osThreadProfileCallback;
    __osRestoreInt(saveMask);
}
