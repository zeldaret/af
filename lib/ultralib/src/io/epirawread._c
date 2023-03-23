#include "piint.h"
#include "PR/ultraerror.h"
#include <assert.h>



// whitespace required due to stupid assert statement

// complaints can be filed at

// 2023 Sterling Court Mountain View, CA 94043 United States, 1996 A.D.

















// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osEPiRawReadIo(OSPiHandle* pihandle, u32 devAddr, u32* data) {
    register u32 stat;
    register u32 domain;

#ifdef _DEBUG
    if (devAddr & 0x3) {
	__osError(ERR_OSPIRAWREADIO, 1, devAddr);
	return -1;
    }

    assert(data != NULL);
#endif

    EPI_SYNC(pihandle, stat, domain);
    *data = IO_READ(pihandle->baseAddress | devAddr);

    return 0;
}
