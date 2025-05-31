#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"

s32 osPfsSetLabel(OSPfs* pfs, u8* label) {
    int i;
    s32 ret;

#if BUILD_VERSION >= VERSION_J
    if (!(pfs->status & PFS_INITIALIZED)) {
        return PFS_ERR_INVALID;
    }

    ERRCK(__osCheckId(pfs));
#else
    PFS_CHECK_ID();
#endif

    if (label != NULL) {
        for (i = 0; i < ARRLEN(pfs->label); i++) {
            if (*label == 0) {
                break;
            }

            *(pfs->label + i) = *label++;
        }
    }

#if BUILD_VERSION >= VERSION_J
    if (pfs->activebank != 0) {
        ret = SELECT_BANK(pfs, 0);
        if (ret == 0) {
            ret = (__osContRamWrite(pfs->queue, pfs->channel, PFS_LABEL_AREA, pfs->label, FALSE));
        }
    }
    return ret;
#else
    SET_ACTIVEBANK_TO_ZERO();
    ERRCK(__osContRamWrite(pfs->queue, pfs->channel, PFS_LABEL_AREA, pfs->label, FALSE));
    return 0;
#endif
}
