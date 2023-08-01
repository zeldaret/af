#include "PR/os_internal.h"
#include "controller.h"

s32 osPfsSetLabel(OSPfs* pfs, u8* label) {
    int i;
    s32 ret;

    if (!(pfs->status & PFS_INITIALIZED)) {
        return PFS_ERR_INVALID;
    }

    ERRCK(__osCheckId(pfs));

    if (label != NULL) {
        for (i = 0; i < ARRLEN(pfs->label); i++) {
            if (*label == 0) {
                break;
            }

            *(pfs->label + i) = *label++;
        }
    }

    if (pfs->activebank != 0) {
        ret = (__osPfsSelectBank(pfs, 0));
        if (ret == 0) {
            ret = (__osContRamWrite(pfs->queue, pfs->channel, PFS_LABEL_AREA, pfs->label, FALSE));
        }
    }
    return ret;
}
