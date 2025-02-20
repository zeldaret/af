#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/controller_gbpak.h"

s32 osGbpakPower(OSPfs* pfs, s32 flag) {
    s32 i;
    s32 ret;
    u8 temp[BLOCKSIZE];

    for (i = 0; i < BLOCKSIZE; temp[i++] = (u8)flag) {
        ;
    }

    ret = __osContRamWrite(pfs->queue, pfs->channel, CONT_BLOCK_GB_STATUS, temp, 0);

    if (ret == PFS_ERR_NEW_PACK) {
        ret = osGbpakInit(pfs->queue, pfs, pfs->channel);

        if (ret == 0) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, CONT_BLOCK_GB_STATUS, temp, 0);

            if (ret == PFS_ERR_NEW_PACK) {
                ret = PFS_ERR_CONTRFAIL;
            }
        }
    }

    if (flag != OS_GBPAK_POWER_OFF) {
        osSetTimer(&__osGbpakTimer, OS_USEC_TO_CYCLES(120000), 0, &__osGbpakTimerQ, &__osGbpakTimerMsg);
        osRecvMesg(&__osGbpakTimerQ, NULL, OS_MESG_BLOCK);
    }

    return ret;
}
