#include <PR/os_internal.h>
#include "viint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

void osViSetYScale(f32 value) {
    register u32 saveMask = __osDisableInt();

    __osViNext->y.factor = value;
    __osViNext->state |= VI_STATE_YSCALE_UPDATED;
    __osRestoreInt(saveMask);
}
