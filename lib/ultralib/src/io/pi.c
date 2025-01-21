
#include "PR/os_internal.h"
#include "PRinternal/piint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

int __osPiDeviceBusy(void) {
    register u32 stat = IO_READ(PI_STATUS_REG);
    if (stat & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
        return TRUE;
    } else {
        return FALSE;
    }
}
