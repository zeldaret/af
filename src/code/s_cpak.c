#include "global.h"

#include "s_cpak.h"

#include "padmgr.h"

void func_800CD640_jp(OSPfsState* pfsState, u16* company_code, u32* game_code) {
    bcopy(company_code, &pfsState->company_code, sizeof(pfsState->company_code));
    bcopy(game_code, &pfsState->game_code, sizeof(pfsState->game_code));
}

s32 func_800CD68C_jp(OSPfsInfo* pfsInfo, s32 channel) {
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

s32 func_800CD730_jp(OSPfsInfo* pfsInfo) {
    s32 bytes;

    pfsInfo->err = osPfsFreeBlocks(&pfsInfo->pfs, &bytes);
    return bytes;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/s_cpak/func_800CD760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/s_cpak/func_800CD82C_jp.s")

s32 func_800CD8F8_jp(OSPfsInfo* pfsInfo, OSPfsState* pfsState, size_t size) {
    s32 alignedSize = ALIGN256(size);
    s32 ret = FALSE;
    s32 err;

    if (func_800CD730_jp(pfsInfo) < alignedSize) {
        return FALSE;
    }

    err = osPfsAllocateFile(&pfsInfo->pfs, pfsState->company_code, pfsState->game_code, (u8*)pfsState->game_name,
                            (u8*)pfsState->ext_name, alignedSize, &pfsInfo->file_no);
    if (err == 0) {
        ret = TRUE;
    }

    pfsInfo->err = err;
    return ret;
}

s32 func_800CD990_jp(OSPfsInfo* pfsInfo, OSPfsState* pfsState) {
    s32 err;
    s32 ret = FALSE;

    err = osPfsFindFile(&pfsInfo->pfs, pfsState->company_code, pfsState->game_code, (u8*)pfsState->game_name,
                        (u8*)pfsState->ext_name, &pfsInfo->file_no);

    pfsInfo->err = err;
    if (err == 0) {
        ret = TRUE;
    }

    return ret;
}

s32 func_800CD9F0_jp(OSPfsInfo* pfsInfo, OSPfsState* pfsState) {
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

u32 func_800CDA4C_jp(OSPfsInfo* pfsInfo, OSPfsState* pfsState) {
    s32 err = osPfsFileState(&pfsInfo->pfs, pfsInfo->file_no, pfsState);

    pfsInfo->err = err;
    if (err != 0) {
        return 0;
    }

    return pfsState->file_size;
}

s32 func_800CDA90_jp(OSPfsInfo* pfsInfo, s32* max_files, s32* files_used) {
    s32 err;
    s32 ret = FALSE;

    err = osPfsNumFiles(&pfsInfo->pfs, max_files, files_used);

    if (err == 0) {
        ret = TRUE;
    }

    pfsInfo->err = err;
    return ret;
}

s32 func_800CDAD0_jp(OSPfsInfo* pfsInfo) {
    s32 err;
    s32 ret = FALSE;

    err = osPfsRepairId(&pfsInfo->pfs);

    if (err == 0) {
        ret = TRUE;
    }

    pfsInfo->err = err;
    return ret;
}
