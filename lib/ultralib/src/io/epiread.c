#include "piint.h"

s32 __osEPiRawReadIo(OSPiHandle*, u32, u32*);

s32 osEPiReadIo(OSPiHandle* pihandle, u32 devAddr, u32* data) {
    register s32 ret;

    __osPiGetAccess();
    ret = __osEPiRawReadIo(pihandle, devAddr, data);
    __osPiRelAccess();

    return ret;
}
