#include "piint.h"

s32 __osPiRawWriteIo(u32, u32);

s32 osPiWriteIo(u32 devAddr, u32 data) {
    register s32 ret;

    __osPiGetAccess();
    ret = __osPiRawWriteIo(devAddr, data);
    __osPiRelAccess();

    return ret;
}
