#include "osint_debug.h"

#include "PRinternal/macros.h"

s32 __osThprofFlag = 0;
void (*__osThprofFunc)(OSThread*) = NULL;

u32 __osThprofLastTimer;
u32 __osThprofCount;
__OSThreadprofile_s thprof[THPROF_IDMAX] ALIGNED(0x10);
u64 __osThprofHeap[THPROF_STACKSIZE] ALIGNED(0x10);
void* __osThprofStack;

void osThreadProfileCallback(OSThread* osthread) {
    register u32 now_time = osGetCount();
    __OSThreadprofile_s* thprof = osthread->thprof;

    thprof->time += now_time - __osThprofLastTimer;
    thprof->count++;
    __osThprofCount++;
    __osThprofLastTimer = now_time;
}
