#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "../os/osint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osSpRawReadIo(u32 devAddr, u32 *data) {
    if (__osSpDeviceBusy()) {
        return -1;
    }
    
    *data = IO_READ(devAddr);
    return 0;
}

