#include "osint_debug.h"

void osThreadProfileInit(void) {
    register u32 saveMask = __osDisableInt();
    OSId i;

    __osThprofFunc = NULL;
    __osThprofFlag = 1;
    __osThprofCount = 0;
    __osThprofStack = &__osThprofHeap[(THPROF_STACKSIZE - 8) / sizeof(*__osThprofHeap)];
    __osRestoreInt(saveMask);

    for (i = 0; i < THPROF_IDMAX; i++) {
        osThreadProfileClear(i);
    }
}
