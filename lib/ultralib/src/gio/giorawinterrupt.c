#include "PR/os_internal.h"
#include "PR/rcp.h"

void __osGIORawInterrupt(s32 value) {
    register u32 stat;

    stat = IO_READ(PI_STATUS_REG);
    while (stat & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
        stat = IO_READ(PI_STATUS_REG);
    }

    IO_WRITE(GIO_GIO_INTR_REG, value);

    stat = IO_READ(PI_STATUS_REG);
    while (stat & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
        stat = IO_READ(PI_STATUS_REG);
    }
}
