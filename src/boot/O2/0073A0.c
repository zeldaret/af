#include "ultra64.h"

u32 func_8002BFA0_jp(void) {
    return (osGetTime() * 1000ULL) / OS_CPU_COUNTER;
}
