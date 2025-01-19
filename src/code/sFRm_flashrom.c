#include "sFRm_flashrom.h"
#include "global.h"

#include "m_thread.h"

extern STACK(B_80144718_jp, 0x400);
extern StackEntry B_80144B18_jp;
extern OSThread B_80144B38_jp;
extern FlashromRequest B_80144CE8_jp;

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDB10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDBE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDBF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDC10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDC30_jp.s")

s32 func_800CDCC0_jp(void* addr, u32 pageNum, u32 pageCount);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDCC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDDE0_jp.s")

s32 func_800CDE54_jp(void* addr, u32 pageNum, u32 pageCount);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDE54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDECC_jp.s")

void func_800CDEDC_jp(void* arg) {
    FlashromRequest* req = (FlashromRequest*)arg;

    switch (req->type) {
        case 0x1:
            req->response = func_800CDCC0_jp(req->addr, req->pageNum, req->pageCount);
            osSendMesg(&req->queue, (OSMesg)req->response, OS_MESG_BLOCK);
            break;

        case 0x2:
            req->response = func_800CDE54_jp(req->addr, req->pageNum, req->pageCount);
            osSendMesg(&req->queue, (OSMesg)req->response, OS_MESG_BLOCK);
            break;
    }
}

void func_800CDF78_jp(void* addr, u32 pageNum, u32 pageCount) {
    FlashromRequest* req = &B_80144CE8_jp;

    req->type = 1;
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
