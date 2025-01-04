#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PR/ultralog.h"
#include "PRinternal/viint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

void osViSetXScale(f32 value) {
    register u32 nomValue;
    register u32 saveMask;

#ifdef _DEBUG
    if (!__osViDevMgr.active) {
        __osError(ERR_OSVISETXSCALE_VIMGR, 0);
        return;
    }

    if ((value < 0.25f) || (value > 1.0f)) {
        __osError(ERR_OSVISETXSCALE_VALUE, 1, OS_LOG_FLOAT(value));

        if (value < 0.25f) {
            value = 0.25f;
        } else {
            value = 1.0f;
        }
    }
#endif

    saveMask = __osDisableInt();

    __osViNext->x.factor = value;
    __osViNext->state |= VI_STATE_XSCALE_UPDATED;
    nomValue = __osViNext->modep->comRegs.xScale & VI_SCALE_MASK;
    __osViNext->x.scale = (u32)(__osViNext->x.factor * nomValue) & VI_SCALE_MASK;
    __osRestoreInt(saveMask);
}
