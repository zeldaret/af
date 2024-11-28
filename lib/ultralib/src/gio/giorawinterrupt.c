#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PRinternal/piint.h"

void __osGIORawInterrupt(s32 value) {
    register u32 stat;

    WAIT_ON_IOBUSY(stat);

    IO_WRITE(GIO_GIO_INTR_REG, value);

    WAIT_ON_IOBUSY(stat);
}
