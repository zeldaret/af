#include "PRinternal/piint.h"
#include "PR/ultraerror.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osPiRawWriteIo(u32 devAddr, u32 data) {
    register u32 stat;

#ifdef _DEBUG
    if (devAddr & 0x3) {
        __osError(ERR_OSPIRAWWRITEIO, 1, devAddr);
        return -1;
    }
#endif

    WAIT_ON_IOBUSY(stat);
    IO_WRITE((u32)osRomBase | devAddr, data);

    return 0;
}
