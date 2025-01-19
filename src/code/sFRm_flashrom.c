#include "sFRm_flashrom.h"
#include "global.h"

#include "os_internal_flash.h"

#include "m_thread.h"

extern OSMesgQueue B_801446E0_jp;

extern OSIoMesg B_80144700_jp;

extern STACK(B_80144718_jp, 0x400);
extern StackEntry B_80144B18_jp;
extern OSThread B_80144B38_jp;
extern FlashromRequest B_80144CE8_jp;

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDB10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDBE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDBF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDC10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDC30_jp.s")

s32 func_800CDCC0_jp(void* addr, u32 pageNum, u32 pageCount) {
    s32 ret;
    s32 retries;
    u32 i;

    if ((pageNum % FLASH_BLOCK_SIZE) != 0) {
        return 1;
    }

    osWritebackDCache(addr, pageCount * FLASH_BLOCK_SIZE);

    retries = 3;
    do {
        ret = osFlashSectorErase(pageNum);
        if (ret == -1) {
            return ret;
        }

        for (i = 0; i < pageCount; i++) {
            ret = osFlashWriteBuffer(&B_80144700_jp, OS_MESG_PRI_NORMAL, (u8*)addr + i * FLASH_BLOCK_SIZE,
                                     &B_801446E0_jp);
            osRecvMesg(&B_801446E0_jp, NULL, OS_MESG_BLOCK);
            if (ret == -1) {
                break;
            }

            ret = osFlashWriteArray(pageNum + i);
            if (ret == -1) {
                break;
            }
        }
        retries--;
    } while ((ret == -1) && (retries != 0));

    return ret;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDDE0_jp.s")

s32 func_800CDE54_jp(void* addr, u32 pageNum, u32 pageCount) {
    s32 ret;
    OSIoMesg msg;

    osInvalDCache(addr, pageCount * FLASH_BLOCK_SIZE);
    ret = osFlashReadArray(&msg, OS_MESG_PRI_NORMAL, pageNum, addr, pageCount, &B_801446E0_jp);
    osRecvMesg(&B_801446E0_jp, NULL, OS_MESG_BLOCK);
    return ret;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDECC_jp.s")

void func_800CDEDC_jp(void* arg) {
    FlashromRequest* req = (FlashromRequest*)arg;

    switch (req->type) {
        case FLASHROM_REQUEST_WRITE:
            req->response = func_800CDCC0_jp(req->addr, req->pageNum, req->pageCount);
            osSendMesg(&req->queue, (OSMesg)req->response, OS_MESG_BLOCK);
            break;

        case FLASHROM_REQUEST_READ:
            req->response = func_800CDE54_jp(req->addr, req->pageNum, req->pageCount);
            osSendMesg(&req->queue, (OSMesg)req->response, OS_MESG_BLOCK);
            break;
    }
}

void func_800CDF78_jp(void* addr, u32 pageNum, u32 pageCount) {
    FlashromRequest* req = &B_80144CE8_jp;

    req->type = FLASHROM_REQUEST_WRITE;
    req->addr = addr;
    req->pageNum = pageNum;
    req->pageCount = pageCount;

    osCreateMesgQueue(&req->queue, req->msgBuf, ARRAY_COUNT(req->msgBuf));
    StackCheck_Init(&B_80144B18_jp, B_80144718_jp, STACK_TOP(B_80144718_jp), 0, 0x100, "sFRm_flashrom");
    osCreateThread(&B_80144B38_jp, M_THREAD_ID_FLASHROM, func_800CDEDC_jp, &B_80144CE8_jp, STACK_TOP(B_80144718_jp),
                   M_PRIORITY_FLASHROM);
    osStartThread(&B_80144B38_jp);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CE04C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CE090_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CE0E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CE110_jp.s")
