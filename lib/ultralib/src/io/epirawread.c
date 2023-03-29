#include "piint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osEPiRawReadIo(OSPiHandle* pihandle, u32 devAddr, u32* data) {
    u32 stat;
    u32 domain;

    EPI_SYNC(pihandle, stat, domain);
    *data = IO_READ(pihandle->baseAddress | devAddr);

    return 0;
}
