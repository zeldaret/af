#include "sFRm_flashrom.h"
#include "global.h"

#include "m_thread.h"

extern STACK(B_80144718_jp, 0x400);
extern StackEntry B_80144B18_jp;
extern s32 D_80144B34; // padding
extern OSThread B_80144B38_jp;
extern FlashromRequest B_80144CE8_jp;
extern OSMesgQueue B_80144CFC_jp;
extern OSMesg B_80144D14_jp[1];

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDB10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDBE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDBF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDC10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDC30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDCC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDDE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDE54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDECC_jp.s")

void func_800CDEDC_jp(void* arg);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CDEDC_jp.s")

void func_800CDF78_jp(s32 arg0, s32 arg1, s32 arg2) {
    B_80144CE8_jp.unk_00 = 1;
    B_80144CE8_jp.unk_08 = arg0;
    B_80144CE8_jp.unk_0C = arg1;
    B_80144CE8_jp.unk_10 = arg2;

    osCreateMesgQueue(&B_80144CFC_jp, B_80144D14_jp, ARRAY_COUNT(B_80144D14_jp));
    StackCheck_Init(&B_80144B18_jp, B_80144718_jp, STACK_TOP(B_80144718_jp), 0, 0x100, "sFRm_flashrom");
    osCreateThread(&B_80144B38_jp, M_THREAD_ID_FLASHROM, func_800CDEDC_jp, &B_80144CE8_jp, STACK_TOP(B_80144718_jp),
                   M_PRIORITY_FLASHROM);
    osStartThread(&B_80144B38_jp);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CE04C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CE090_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CE0E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/sFRm_flashrom/func_800CE110_jp.s")
