#include "PR/os_internal.h"
#include "PRinternal/controller.h"

s32 __osGbpakSetBank(OSPfs* pfs, u8 bank) {
    int i;
    s32 ret;
    u8 temp[BLOCKSIZE];

    if (bank > 2) {
        return PFS_ERR_INVALID;
    }

    for (i = 0; i < BLOCKSIZE; temp[i++] = bank) {
        ;
    }

    ret = __osContRamWrite(pfs->queue, pfs->channel, CONT_BLOCK_GB_BANK, temp, FALSE);

    if (ret == PFS_ERR_NEW_PACK) {
        ret = osGbpakInit(pfs->queue, pfs, pfs->channel);

        if (ret == 0) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, CONT_BLOCK_GB_BANK, temp, FALSE);
            if (ret == PFS_ERR_NEW_PACK) {
                ret = PFS_ERR_CONTRFAIL;
            }
        }
    }

    if (ret == 0) {
        pfs->banks = bank;
    }

    return ret;
}
