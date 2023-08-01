#include "PR/os_internal.h"
#include "PR/rcp.h"

void osDpGetCounters(u32* array) {
    *array++ = IO_READ(DPC_CLOCK_REG);
    *array++ = IO_READ(DPC_BUFBUSY_REG);
    *array++ = IO_READ(DPC_PIPEBUSY_REG);
    *array++ = IO_READ(DPC_TMEM_REG);
}
