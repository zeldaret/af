#include <PR/os_internal.h>
#include "viint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

void osViSwapBuffer(void* frameBufPtr) {
    u32 saveMask = __osDisableInt();

    __osViNext->framep = frameBufPtr;
    __osViNext->state |= VI_STATE_BUFFER_UPDATED;
    __osRestoreInt(saveMask);
}
