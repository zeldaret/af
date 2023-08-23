#include "z_std_dma.h"
#include "fault.h"
#include "irqmgr.h"
#include "yaz0.h"
#include "libu64/stackcheck.h"
#include "libc/stdbool.h"
#include "stack.h"
#include "m_thread.h"
#include "macros.h"
#include "segment_symbols.h"
#include "boot_variables.h"

u32 D_8003BBE0_jp = 0x2000;

StackEntry sDmaMgrStackInfo;
u16 B_8003FF5C_jp;
OSMesgQueue sDmaMgrMsgQueue;
OSMesg sDmaMgrMsgs[0x20];
OSThread sDmaMgrThread;
STACK(sDmaMgrStack, 0x500);
const char* B_800406A8_jp;
UNK_TYPE B_800406AC_jp;
size_t B_800406B0_jp;
size_t B_800406B4_jp;

void func_800263F0_jp(DmaRequest* req, const char* arg1, const char* arg2, const char* arg3) {
    RomOffset vrom = req->vrom;
    void* vram = req->vram;
    size_t size = req->size;
    char buff1[80];
    char buff2[80];

    //! FAKE?
    if (arg3 != NULL) {
        (void)"???";
        (void)"???";
    }
    if (1) { }
    if (1) { }

    if (req->filename != NULL) {
        //! FAKE
        if (1) {}
        sprintf(buff1, "DMA ERROR: %.50s %d", req->filename, req->line);
    } else if (B_800406A8_jp != NULL) {
        sprintf(buff1, "DMA ERROR: %.50s %d", B_800406A8_jp, B_800406AC_jp);
    } else {
        sprintf(buff1, "DMA ERROR: %.50s", (arg2 != NULL) ? arg2 : "???");
    }

    sprintf(buff2, "%07X %08X %X %.50s", vrom, vram, size, (arg1 != NULL) ? arg1 : "???");
    Fault_AddHungupAndCrashImpl(buff1, buff2);
}

s32 DmaMgr_DmaRomToRam(RomOffset vrom, void* vram, size_t size) {
    OSIoMesg sp80;
    OSMesgQueue sp68;
    OSMesg sp64[1];
    s32 ret;
    u32 temp_s0 = D_8003BBE0_jp;
    DmaRequest sp3C;

    if (((vrom << 31) != 0) || (((u32)vram << 29) != 0) || ((size << 31) != 0)) {
        sp3C.vrom = vrom;
        sp3C.vram = vram;
        sp3C.size = size;
        sp3C.filename = "percial_DMA";
        sp3C.line = 0;
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
            vram = (void*)((uintptr_t)vram + temp_s0);
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

const char* func_80026814_jp(UNUSED s32 arg0) {
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

void func_800269E4_jp(UNUSED void* arg) {
    OSMesg msg;
    DmaRequest* sp34;

    while (true) {
        osRecvMesg(&sDmaMgrMsgQueue, &msg, OS_MESG_BLOCK);

        if (msg == NULL) {
            break;
        }
        sp34 = msg;

        func_80026828_jp(sp34);

        if (sp34->mq != NULL) {
            osSendMesg(sp34->mq, sp34->unk_1C, OS_MESG_NOBLOCK);
        }
    }
}

s32 func_80026A64_jp(DmaRequest* req, void* vram, RomOffset vrom, size_t size, UNUSED s32 arg4, OSMesgQueue* mq, OSMesg arg6) {
    if (ResetStatus >= 2) {
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

    osSendMesg(&sDmaMgrMsgQueue, req, OS_MESG_BLOCK);
    return 0;
}

s32 DmaMgr_RequestSync(void* ram, RomOffset vrom, size_t size) {
    DmaRequest sp48;
    OSMesgQueue sp30;
    OSMesg sp2C[1];
    s32 temp_v0;

    osCreateMesgQueue(&sp30, sp2C, ARRAY_COUNT(sp2C));
    temp_v0 = func_80026A64_jp(&sp48, ram, vrom, size, 0, &sp30, NULL);
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
        DmaEntry* entry = gDmaDataTable;
        s32 count = 0;

        for (; entry->vromEnd != 0; entry++) {
            count++;
        }

        B_8003FF5C_jp = count;
    } while (0);

    osCreateMesgQueue(&sDmaMgrMsgQueue, sDmaMgrMsgs, ARRAY_COUNT(sDmaMgrMsgs));
    StackCheck_Init(&sDmaMgrStackInfo, sDmaMgrStack, STACK_TOP(sDmaMgrStack), 0, 0x100, "dmamgr");
    osCreateThread(&sDmaMgrThread, M_THREAD_ID_DMAMGR, func_800269E4_jp, NULL, STACK_TOP(sDmaMgrStack), M_PRIORITY_DMAMGR);
    osStartThread(&sDmaMgrThread);
}

void func_80026DA0_jp(void) {
    osSendMesg(&sDmaMgrMsgQueue, NULL, OS_MESG_BLOCK);
}

void func_80026DCC_jp(DmaRequest* req, void* arg1, u32 arg2, u32 arg3, s32 arg4, OSMesgQueue* arg5, OSMesg arg6, const char* arg7, s32 arg8) {
    req->filename = arg7;
    req->line = arg8;
    func_80026A64_jp(req, arg1, arg2, arg3, arg4, arg5, arg6);
}

s32 func_80026E10_jp(void* arg0, RomOffset arg1, size_t arg2, const char* arg3, s32 arg4) {
    DmaRequest sp50;
    s32 temp;
    OSMesgQueue sp34;
    OSMesg sp30[1];
    UNUSED s32 pad;

    sp50.filename = arg3;
    sp50.line = arg4;

    osCreateMesgQueue(&sp34, sp30, ARRAY_COUNT(sp30));

    temp = func_80026A64_jp(&sp50, arg0, arg1, arg2, 0, &sp34, 0);
    if (temp == -1) {
        return temp;
    }

    osRecvMesg(&sp34, NULL, OS_MESG_BLOCK);
    return 0;
}
