#include "PR/os_internal.h"
#include "PRinternal/controller.h"

s32 __osGbpakGetBank(OSPfs* pfs, u8* bank) {
    s32 ret;
    u32 temp[BLOCKSIZE / sizeof(u32)];

    ret = __osContRamRead(pfs->queue, pfs->channel, CONT_BLOCK_GB_BANK, (u8*)temp);

    if (ret == PFS_ERR_NEW_PACK) {
        ret = osGbpakInit(pfs->queue, pfs, pfs->channel);

        if (ret == 0) {
            ret = __osContRamRead(pfs->queue, pfs->channel, CONT_BLOCK_GB_BANK, (u8*)temp);

            if (ret == PFS_ERR_NEW_PACK) {
                ret = PFS_ERR_CONTRFAIL;
            }
        }
    }

    if (ret == 0) {
        *bank = ((u8*)temp)[0];
        pfs->banks = *bank;
    }

    return ret;
}
