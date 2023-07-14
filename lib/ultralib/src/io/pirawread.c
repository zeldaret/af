#include "piint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osPiRawReadIo(u32 devAddr, u32* data) {
    register u32 stat;

    WAIT_ON_IOBUSY(stat);
    *data = IO_READ((u32)osRomBase | devAddr);

    return 0;
}
