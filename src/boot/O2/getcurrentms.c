#include "getcurrentms.h"

// original name unknown
u32 GetCurrentMilliseconds(void) {
    return (osGetTime() * 1000ULL) / OS_CPU_COUNTER;
}
