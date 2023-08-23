#include "z_std_dma.h"
#include "irqmgr.h"
#include "macros.h"

extern OSMesgQueue B_8003FF60_jp;

extern const char* B_800406A8_jp;
extern UNK_TYPE B_800406AC_jp;
#if 0
void func_800263F0_jp(DmaRequest* req, const char* arg1, const char* arg2, const char* arg3) {
    s32 spD4;
    s32 spD0;
    s32 spCC;
    char sp7C[0xCC-0x7C];
    char sp2C[0x7C-0x2C];

    spD4 = req->unk_00;
    spD0 = req->unk_04;
    spCC = req->unk_08;
    if (req->unk_0C != 0) {
        sprintf(&sp7C, "DMA ERROR: %.50s %d", req->unk_0C, req->unk_10);
    } else if (B_800406A8_jp != 0) {
        sprintf(&sp7C, "DMA ERROR: %.50s %d", B_800406A8_jp, B_800406AC_jp);
    } else {
        sprintf(&sp7C, "DMA ERROR: %.50s", (arg2 != NULL) ? arg2 : "???");
    }

    sprintf(&sp2C, "%07X %08X %X %.50s", spD4, spD0, spCC, (arg1 != NULL) ? arg1 : "???");
    Fault_AddHungupAndCrashImpl(&sp7C, &sp2C);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_800263F0_jp.s")
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_STR_8003D1D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_STR_8003D1D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_STR_8003D1D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_STR_8003D1EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_STR_8003D200_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_STR_8003D214_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_STR_8003D218_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_STR_8003D22C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/DmaMgr_DmaRomToRam.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_800266C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026714_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_800267DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026814_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_8003D268_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026828_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_800269E4_jp.s")


s32 func_80026A64_jp(DmaRequest* req, void* ram, RomOffset vrom, size_t size, s32 arg4, OSMesgQueue* mq, s32 arg6) {
    if ((vs32)ResetStatus >= 2) {
        return -2;
    }
    req->unk_00 = (s32) vrom;
    req->unk_04 = (s32) ram;
    req->unk_08 = (s32) size;
    req->unk_14 = 0;
    req->unk_18 = (s32) mq;
    req->unk_1C = arg6;
    if ((ram == NULL) || ((u32) osMemSize < (u32) ((uintptr_t)ram + size + 0x80000000)) || (vrom & 1) || (vrom >= 0x04000001U) || (size == 0) || (size & 1)) {
        func_800263F0_jp(req, NULL, "ILLIGAL DMA-FUNCTION CALL", "パラメータ異常です");
    }

    osSendMesg(&B_8003FF60_jp, req, 1);
    return 0;
}

s32 DmaMgr_RequestSync(void* ram, void* vrom, size_t size) {
    DmaRequest sp48;
    OSMesgQueue sp30;
    OSMesg sp2C[1];
    s32 temp_v0;

    osCreateMesgQueue(&sp30, sp2C, ARRAY_COUNT(sp2C));
    temp_v0 = func_80026A64_jp(&sp48, ram, vrom, size, 0, &sp30, 0);
    if (temp_v0 == -1) {
        return temp_v0;
    }

    osRecvMesg(&sp30, NULL, OS_MESG_BLOCK);

    return 0;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026BC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026C00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026C28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026C4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026CAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026DA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026DCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/func_80026E10_jp.s")
