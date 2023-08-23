#include "z_std_dma.h"
#include "fault.h"
#include "irqmgr.h"
#include "yaz0.h"
#include "libu64/stackcheck.h"
#include "libc/stdbool.h"
#include "macros.h"
#include "segment_symbols.h"
#include "boot_variables.h"

extern u16 B_8003FF5C_jp;
extern void* B_8003FF78_jp;
extern StackEntry B_8003FF40_jp;
extern u64 B_800401A8_jp;
extern OSThread B_8003FFF8_jp;
void func_800269E4_jp(void* arg0);

extern OSMesgQueue B_8003FF60_jp;

extern const char* B_800406A8_jp;
extern UNK_TYPE B_800406AC_jp;

extern s32 B_800406B0_jp;
extern u32 D_8003BBE0_jp;

extern s32 B_800406B4_jp;

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_STR_8003D1D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/z_std_dma/RO_STR_8003D1D4_jp.s")

void func_800263F0_jp(DmaRequest* req, const char* arg1, const char* arg2, const char* arg3) {
    RomOffset vrom = req->vrom;
    void* vram = req->vram;
    size_t size = req->size;
    char sp7C[80];
    char sp2C[80];

    //! FAKE
    if (arg3) {}
    if (1) { }
    if (1) { }

    if (req->unk_0C != 0) {
        //! FAKE
        if (1) {}
        sprintf(sp7C, "DMA ERROR: %.50s %d", req->unk_0C, req->unk_10);
    } else if (B_800406A8_jp != NULL) {
        sprintf(sp7C, "DMA ERROR: %.50s %d", B_800406A8_jp, B_800406AC_jp);
    } else {
        sprintf(sp7C, "DMA ERROR: %.50s", (arg2 != NULL) ? arg2 : "???");
    }

    sprintf(sp2C, "%07X %08X %X %.50s", vrom, vram, size, (arg1 != NULL) ? arg1 : "???");
    Fault_AddHungupAndCrashImpl(sp7C, sp2C);
}

s32 DmaMgr_DmaRomToRam(RomOffset vrom, void* vram, size_t size) {
    OSIoMesg sp80;
    OSMesgQueue sp68;
    OSMesg sp64[1];
    s32 ret; // sp60
    u32 temp_s0;
    DmaRequest sp3C;

    temp_s0 = D_8003BBE0_jp;
    if (((vrom << 31) != 0) || (((u32)vram << 29) != 0) || ((size << 31) != 0)) {
        sp3C.vrom = vrom;
        sp3C.vram = vram;
        sp3C.size = size;
        sp3C.unk_0C = "percial_DMA";
        sp3C.unk_10 = 0;
        func_800263F0_jp(&sp3C, NULL, "ILLIGAL ALIGNMENT", "アライメント異常");
    }

    osInvalDCache(vram, size);
    osCreateMesgQueue(&sp68, sp64, ARRAY_COUNT(sp64));

    if (temp_s0 != 0) {
        while (temp_s0 < size) {
            sp80.hdr.pri = 0;
            sp80.hdr.retQueue = &sp68;
            sp80.devAddr = vrom;
            sp80.dramAddr = vram;
            sp80.size = temp_s0;
            B_800406B0_jp += temp_s0;

            //! FAKE
            if (1) {}
            if (1) {}

            ret = osEPiStartDma(gCartHandle, &sp80, 0);
            if (ret != 0) {
                goto end;
            }

            osRecvMesg(&sp68, NULL, OS_MESG_BLOCK);
            size -= temp_s0;
            vrom += temp_s0;
            vram = (uintptr_t)vram + temp_s0;
        }
    }

    sp80.hdr.pri = 0;
    sp80.hdr.retQueue = &sp68;
    sp80.devAddr = vrom;
    sp80.dramAddr = vram;
    sp80.size = size;
    B_800406B0_jp += size;
    ret = osEPiStartDma(gCartHandle, &sp80, 0);
    if (ret == 0) {
        osRecvMesg(&sp68, NULL, OS_MESG_BLOCK);
        osInvalDCache(vram, size);
    }

end:
    return ret;
}

s32 func_800266C4_jp(OSPiHandle* arg0, OSIoMesg* arg1, s32 arg2) {
    s32 ret = osEPiStartDma(arg0, arg1, arg2);

    B_800406B0_jp += arg1->size;
    B_800406B4_jp += arg1->size;

    return ret;
}

DmaEntry* func_80026714_jp(RomOffset vrom) {
    DmaEntry* entry;

    for (entry = gDmaDataTable; entry->vromEnd != 0; entry++) {
        if ((vrom >= entry->vromStart) && (vrom < entry->vromEnd)) {
            return entry;
        }
    }
    return NULL;
}

RomOffset func_80026770_jp(RomOffset vrom) {
    DmaEntry* entry = func_80026714_jp(vrom);

    if (entry != NULL) {
        if (entry->romEnd == 0) {
            return (entry->romStart + vrom) - entry->vromStart;
        }

        if (vrom == entry->vromStart) {
            return entry->romStart;
        }

        return -1;
    }

    return -1;
}

s32 func_800267DC_jp(RomOffset vrom) {
    DmaEntry* entry = func_80026714_jp(vrom);

    if (entry != NULL) {
        return entry - gDmaDataTable;
    }
    return -1;
}

const char* func_80026814_jp(s32 arg0) {
    return "??";
}

void func_80026828_jp(DmaRequest* req) {
    RomOffset vrom = req->vrom;
    void* vram = req->vram;
    size_t size = req->size;
    RomOffset romStart;
    size_t romSize;
    DmaEntry* entry;
    s32 index = func_800267DC_jp(vrom);

    if ((index >= 0) && (index < B_8003FF5C_jp)) {
        entry = &gDmaDataTable[index];

        if (entry->romEnd == 0) {
            if (entry->vromEnd < (vrom + size)) {
                func_800263F0_jp(req, "", "Segment Alignment Error", "セグメント境界をまたがってＤＭＡ転送することはできません");
            }
            DmaMgr_DmaRomToRam((entry->romStart + vrom) - entry->vromStart, vram, size);
            return;
        } else {
            romSize = entry->romEnd - entry->romStart;
            romStart = entry->romStart;
            if (vrom != entry->vromStart) {
                func_800263F0_jp(req, "", "Can't Transfer Segment", "圧縮されたセグメントの途中からはＤＭＡ転送することはできません");
            }

            if (size != (entry->vromEnd - entry->vromStart)) {
                func_800263F0_jp(req, "", "Can't Transfer Segment", "圧縮されたセグメントの一部だけをＤＭＡ転送することはできません");
            }

            osSetThreadPri(NULL, 0xA);
            Yaz0_Decompress(romStart, vram, romSize);
            osSetThreadPri(NULL, 0x11);
        }
    } else {
        func_800263F0_jp(req, NULL, "DATA DON'T EXIST", "該当するデータが存在しません");
    }
}

void func_800269E4_jp(void* arg0) {
    OSMesg msg;
    DmaRequest* sp34;

    while (true) {
        osRecvMesg(&B_8003FF60_jp, &msg, 1);
        if (msg == NULL) {
            break;
        }
        sp34 = msg;

        func_80026828_jp(sp34);

        if (sp34->mq != NULL) {
            osSendMesg(sp34->mq, sp34->unk_1C, 0);
        }
    }
}

s32 func_80026A64_jp(DmaRequest* req, void* vram, RomOffset vrom, size_t size, s32 arg4, OSMesgQueue* mq, s32 arg6) {
    if ((vs32)ResetStatus >= 2) {
        return -2;
    }

    req->vrom = vrom;
    req->vram = vram;
    req->size = size;
    req->unk_14 = 0;
    req->mq = mq;
    req->unk_1C = arg6;

    if ((vram == NULL) || ((u32) osMemSize < (u32) ((uintptr_t)vram + size + 0x80000000)) || (vrom & 1) || (vrom >= 0x04000001U) || (size == 0) || (size & 1)) {
        func_800263F0_jp(req, NULL, "ILLIGAL DMA-FUNCTION CALL", "パラメータ異常です");
    }

    osSendMesg(&B_8003FF60_jp, req, 1);
    return 0;
}

s32 DmaMgr_RequestSync(void* ram, RomOffset vrom, size_t size) {
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

void func_80026BC0_jp(void* vram, RomOffset vrom) {
    DmaEntry* entry = func_80026714_jp(vrom);

    DmaMgr_RequestSync(vram, vrom, entry->vromEnd - entry->vromStart);
}

size_t func_80026C00_jp(RomOffset vrom) {
    DmaEntry* entry = func_80026714_jp(vrom);

    return entry->vromEnd - entry->vromStart;
}

s32 func_80026C28_jp(RomOffset vrom) {
    DmaEntry* entry = func_80026714_jp(vrom);

    return entry[1].vromStart;
}

s32 func_80026C4C_jp(RomOffset vromStart, RomOffset* vromEnd, RomOffset* ovlStart, RomOffset* ovlEnd) {
    DmaEntry* entry = func_80026714_jp(vromStart);

    if (entry != NULL) {
        *vromEnd = entry[0].vromEnd;
        *ovlStart = entry[1].vromStart;
        *ovlEnd = entry[1].vromEnd;
        return 0;
    }
    return -1;
}

void func_80026CAC_jp(void) {
    DmaMgr_DmaRomToRam(SEGMENT_ROM_START(dmadata), SEGMENT_VRAM_START(dmadata), SEGMENT_ROM_SIZE(dmadata));

    do {
        DmaEntry* var_v0 = gDmaDataTable;
        s32 var_v1 = 0;

        for (; var_v0->vromEnd != 0; var_v0++) {
            var_v1++;
        }

        B_8003FF5C_jp = var_v1;
    } while (0);

    osCreateMesgQueue(&B_8003FF60_jp, &B_8003FF78_jp, 0x20);
    StackCheck_Init(&B_8003FF40_jp, &B_800401A8_jp, &B_800406A8_jp, 0U, 0x100, "dmamgr");
    osCreateThread(&B_8003FFF8_jp, 8, func_800269E4_jp, NULL, &B_800406A8_jp, 0x11);
    osStartThread(&B_8003FFF8_jp);
}

void func_80026DA0_jp(void) {
    osSendMesg(&B_8003FF60_jp, NULL, 1);
}

void func_80026DCC_jp(DmaRequest* arg0, void* arg1, u32 arg2, u32 arg3, s32 arg4, OSMesgQueue* arg5, s32 arg6, s32 arg7, s32 arg8) {
    arg0->unk_0C = arg7;
    arg0->unk_10 = arg8;
    func_80026A64_jp(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}

s32 func_80026E10_jp(void* arg0, RomOffset arg1, size_t arg2, const char* arg3, s32 arg4) {
    DmaRequest sp50;
    s32 temp;
    OSMesgQueue sp34;
    OSMesg sp30[1];
    s32 pad;

    sp50.unk_0C = arg3;
    sp50.unk_10 = arg4;

    osCreateMesgQueue(&sp34, sp30, ARRAY_COUNT(sp30));

    temp = func_80026A64_jp(&sp50, arg0, arg1, arg2, 0, &sp34, 0);
    if (temp == -1) {
        return temp;
    }

    osRecvMesg(&sp34, NULL, OS_MESG_BLOCK);
    return 0;
}
