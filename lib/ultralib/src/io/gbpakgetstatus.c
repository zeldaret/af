#include "PR/os_internal.h"
#include "PRinternal/controller.h"

s32 osGbpakGetStatus(OSPfs* pfs, u8* status) {
    s32 ret;
    s32 i;
    u32 temp[BLOCKSIZE / sizeof(u32)];

    ret = __osContRamRead(pfs->queue, pfs->channel, CONT_BLOCK_GB_POWER, (u8*)temp);

    if ((ret == PFS_ERR_NEW_PACK) || (((u8*)temp)[BLOCKSIZE - 1] != GB_POWER_ON)) {
        ERRCK(osGbpakInit(pfs->queue, pfs, pfs->channel));
    }

    ret = __osContRamRead(pfs->queue, pfs->channel, CONT_BLOCK_GB_STATUS, (u8*)temp);

    if (ret == 0) {
        ERRCK(__osPfsGetStatus(pfs->queue, pfs->channel));

        *status = ((u8*)temp)[0];

        for (i = 1; i < BLOCKSIZE; i++) {
            *status |= ((u8*)temp)[i];
        }

        *status &= (OS_GBPAK_GBCART_PULL | OS_GBPAK_RSTB_DETECTION);
        *status |= ((u8*)temp)[BLOCKSIZE - 1];

        if (!(*status & OS_GBPAK_GBCART_ON)) {
            ret = PFS_ERR_NO_GBCART;
        } else if (*status & OS_GBPAK_GBCART_PULL) {
            ret = PFS_ERR_NEW_GBCART;
        }
    } else if (ret == 2) {
        ret = PFS_ERR_CONTRFAIL;
    }

    return ret;
}
