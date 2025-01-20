#include "s_cpak.h"
#include "global.h"

#include "getcurrentms.h"
#include "padmgr.h"

void sCPk_SetCode(OSPfsState* pfsState, u16* companyCode, u32* gameCode) {
    bcopy(companyCode, &pfsState->company_code, sizeof(pfsState->company_code));
    bcopy(gameCode, &pfsState->game_code, sizeof(pfsState->game_code));
}

s32 sCPk_PakOpen(OSPfsInfo* pfsInfo, s32 channel) {
    OSMesgQueue* queue;
    s32 err;
    s32 ret = FALSE;

    queue = padmgr_LockSerialMesgQ();
    err = osPfsInitPak(queue, &pfsInfo->pfs, channel);

    if (err == 0) {
        ret = TRUE;
    }

    if (err == PFS_ERR_DEVICE) {
        if (osMotorInit(queue, &pfsInfo->pfs, channel) != 0) {
            if (osGbpakInit(queue, &pfsInfo->pfs, channel) != 0) {
                err = PFS_ERR_ID_FATAL;
            }
        }
    }

    pfsInfo->err = err;
    padmgr_UnlockSerialMesgQ(queue);

    return ret;
}

s32 sCPk_PakFreeArea(OSPfsInfo* pfsInfo) {
    s32 bytes;

    pfsInfo->err = osPfsFreeBlocks(&pfsInfo->pfs, &bytes);
    return bytes;
}

s32 sCPk_Save(OSPfsInfo* pfsInfo, s32 offset, s32 size, u8* buffer) {
    UNUSED s32 pad;
    s32 err;
    s32 ret = FALSE;
    s32 writeSize = 0x2300;

    do {
        if (size < writeSize) {
            writeSize = size;
        }
        err = osPfsReadWriteFile(&pfsInfo->pfs, pfsInfo->fileNo, PFS_WRITE, offset, writeSize, buffer);
        offset += writeSize;
        buffer += writeSize;
        size -= writeSize;
        B_80145FF8_jp = GetCurrentMilliseconds();
    } while ((size > 0) && (err == 0));

    if (err == 0) {
        ret = TRUE;
    }

    pfsInfo->err = err;
    return ret;
}

s32 sCPk_Load(OSPfsInfo* pfsInfo, s32 offset, s32 size, u8* buffer) {
    UNUSED s32 pad;
    s32 err;
    s32 ret = FALSE;
    s32 readSize = 0x2300;

    do {
        if (size < readSize) {
            readSize = size;
        }
        err = osPfsReadWriteFile(&pfsInfo->pfs, pfsInfo->fileNo, PFS_READ, offset, readSize, buffer);
        offset += readSize;
        buffer += readSize;
        size -= readSize;
        B_80145FF8_jp = GetCurrentMilliseconds();
    } while ((size > 0) && (err == 0));

    if (err == 0) {
        ret = TRUE;
    }

    pfsInfo->err = err;
    return ret;
}

s32 sCPk_MakeFile(OSPfsInfo* pfsInfo, OSPfsState* pfsState, size_t size) {
    s32 alignedSize = ALIGN256(size);
    s32 ret = FALSE;
    s32 err;

    if (sCPk_PakFreeArea(pfsInfo) < alignedSize) {
        return FALSE;
    }

    err = osPfsAllocateFile(&pfsInfo->pfs, pfsState->company_code, pfsState->game_code, (u8*)pfsState->game_name,
                            (u8*)pfsState->ext_name, alignedSize, &pfsInfo->fileNo);
    if (err == 0) {
        ret = TRUE;
    }

    pfsInfo->err = err;
    return ret;
}

s32 sCPk_FileOpen(OSPfsInfo* pfsInfo, OSPfsState* pfsState) {
    s32 err;
    s32 ret = FALSE;

    err = osPfsFindFile(&pfsInfo->pfs, pfsState->company_code, pfsState->game_code, (u8*)pfsState->game_name,
                        (u8*)pfsState->ext_name, &pfsInfo->fileNo);

    pfsInfo->err = err;
    if (err == 0) {
        ret = TRUE;
    }

    return ret;
}

s32 sCPk_DeleteFile(OSPfsInfo* pfsInfo, OSPfsState* pfsState) {
    s32 err;
    s32 ret = FALSE;

    err = osPfsDeleteFile(&pfsInfo->pfs, pfsState->company_code, pfsState->game_code, (u8*)pfsState->game_name,
                          (u8*)pfsState->ext_name);
    if (err == 0) {
        ret = TRUE;
    }

    pfsInfo->err = err;

    return ret;
}

u32 sCPk_FileState(OSPfsInfo* pfsInfo, OSPfsState* pfsState) {
    s32 err = osPfsFileState(&pfsInfo->pfs, pfsInfo->fileNo, pfsState);

    pfsInfo->err = err;
    if (err != 0) {
        return 0;
    }

    return pfsState->file_size;
}

s32 sCPk_FileNum(OSPfsInfo* pfsInfo, s32* maxFiles, s32* filesUsed) {
    s32 err;
    s32 ret = FALSE;

    err = osPfsNumFiles(&pfsInfo->pfs, maxFiles, filesUsed);

    if (err == 0) {
        ret = TRUE;
    }

    pfsInfo->err = err;
    return ret;
}

s32 sCPk_RepairID(OSPfsInfo* pfsInfo) {
    s32 err;
    s32 ret = FALSE;

    err = osPfsRepairId(&pfsInfo->pfs);

    if (err == 0) {
        ret = TRUE;
    }

    pfsInfo->err = err;
    return ret;
}
