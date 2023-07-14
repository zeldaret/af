#include "piint.h"

s32 __osPiRawReadIo(u32, u32*);

s32 osPiReadIo(u32 devAddr, u32* data) {
    register s32 ret;

    __osPiGetAccess();
    ret = __osPiRawReadIo(devAddr, data);
    __osPiRelAccess();

    return ret;
}
