#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"

#if BUILD_VERSION >= VERSION_J

s32 osPfsRepairId(OSPfs* pfs) {
    s32 ret = 0;

    if ((pfs->status & (PFS_INITIALIZED | PFS_ID_BROKEN))) {
        ret = __osGetId(pfs);

        if (ret == 0) {
            pfs->status &= ~(PFS_ID_BROKEN);
        }
    } else {
        ret = PFS_ERR_INVALID;
    }

    return ret;
}

#else

s32 osPfsRepairId(OSPfs *pfs) {
    int k;
    u16 sum;
    u16 isum;
    u8 temp[32];
    __OSPackId newid;
    s32 ret;
    __OSPackId *id;

    SET_ACTIVEBANK_TO_ZERO();
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, 1, (u8*)&temp));
    __osIdCheckSum((u16*)&temp, &sum, &isum);
    id = (__OSPackId*)&temp;
    
    if (id->checksum != sum || id->inverted_checksum != isum) {
        ret = __osCheckPackId(pfs, id);

        if (ret == 10) {
            ERRCK(__osRepairPackId(pfs, id, &newid));
            id = &newid;
        } else if (ret != 0) {
            return ret;
        }
    }

    if ((id->deviceid & 1) == 0) {
        ERRCK(__osRepairPackId(pfs, id, &newid));
        id = &newid;

        if ((id->deviceid & 1) == 0) {
            return PFS_ERR_DEVICE;
        }
    }
    
    for (k = 0; k < ARRLEN(pfs->id); k++) {
        pfs->id[k] = ((u8*)id)[k];
    }

    pfs->version = id->version;
    pfs->banks = id->banks;
    pfs->inode_start_page = pfs->banks * 2 + 3;
    pfs->dir_size = 16;
    pfs->inode_table = 8;
    pfs->minode_table = (pfs->banks + 1) * PFS_ONE_PAGE;
    pfs->dir_table = pfs->minode_table + pfs->banks * PFS_ONE_PAGE;
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, 7, pfs->label));
    return 0;
}

#endif
