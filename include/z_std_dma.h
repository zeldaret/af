#ifndef Z_STD_DMA_H
#define Z_STD_DMA_H

#include "ultra64.h"
#include "attributes.h"
#include "libc/stdint.h"
#include "other_types.h"
#include "unk.h"

typedef struct DmaRequest {
    /* 0x00 */ UNK_TYPE unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE unk_1C;
} DmaRequest; // size = 0x20

typedef struct DmaEntry {
    /* 0x0 */ RomOffset vromStart;
    /* 0x4 */ RomOffset vromEnd;
    /* 0x8 */ RomOffset romStart;
    /* 0xC */ RomOffset romEnd;
} DmaEntry; // size = 0x10

extern DmaEntry gDmaDataTable[];

NORETURN void func_800263F0_jp(DmaRequest* req, const char* arg1, const char* arg2, const char* arg3);
// void DmaMgr_DmaRomToRam();
// void func_800266C4_jp();
// void func_80026714_jp();
// void func_80026770_jp();
// void func_800267DC_jp();
// void func_80026814_jp();
// void func_80026828_jp();
// void func_800269E4_jp();
s32 func_80026A64_jp(DmaRequest* req, void* ram, RomOffset vrom, size_t size, UNK_TYPE arg4, OSMesgQueue* mq, UNK_TYPE arg6);
s32 DmaMgr_RequestSync(void* ram, void* vrom, size_t size);
// void func_80026BC0_jp();
// void func_80026C00_jp();
// void func_80026C28_jp();
s32 func_80026C4C_jp(RomOffset vromStart, RomOffset* vromEnd, void* ovlStart, void* ovlEnd);
void func_80026CAC_jp(void);
void func_80026DA0_jp(void);
// void func_80026DCC_jp();
void func_80026E10_jp(void* arg0, RomOffset arg1, size_t arg2, const char* arg3, s32 arg4);

#endif
