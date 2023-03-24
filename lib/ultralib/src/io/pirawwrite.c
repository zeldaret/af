#include "piint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osPiRawWriteIo(u32 devAddr, u32 data) {
    register u32 stat;

    WAIT_ON_IOBUSY(stat);
    IO_WRITE((u32)osRomBase | devAddr, data);

    return 0;
}
