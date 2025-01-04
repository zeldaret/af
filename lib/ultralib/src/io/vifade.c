#include "PR/os_internal.h"
#include "PRinternal/viint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

void osViFade(u8 active, u16 factor) {
    register u32 saveMask = __osDisableInt();

    if (active) {
        __osViNext->y.offset = factor & VI_2_10_FPART_MASK;
        __osViNext->state |= VI_STATE_FADE;
    } else {
        __osViNext->state &= ~VI_STATE_FADE;
    }

    __osRestoreInt(saveMask);
}
