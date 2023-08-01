#include "PR/os_internal.h"
#include "assert.h"
#include "siint.h"












































// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osSiRawReadIo(u32 devAddr, u32* data) {
#ifdef _DEBUG
    assert((devAddr & 0x3) == 0);
    assert(data != NULL);
#endif
    if (__osSiDeviceBusy()) {
        return -1;
    }

    *data = IO_READ(devAddr);
    return 0;
}
