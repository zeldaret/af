#ifndef Z_STD_DMA_H
#define Z_STD_DMA_H

#include "libc/stdint.h"
#include "ultra64.h"
#include "other_types.h"

typedef struct DmaEntry {
    /* 0x0 */ RomOffset vromStart;
    /* 0x4 */ RomOffset vromEnd;
    /* 0x8 */ RomOffset romStart;
    /* 0xC */ RomOffset romEnd;
} DmaEntry; // size = 0x10

extern DmaEntry gDmaDataTable[];

// void func_800263F0_jp();
// void DmaMgr_DmaRomToRam();
// void func_800266C4_jp();
// void func_80026714_jp();
// void func_80026770_jp();
// void func_800267DC_jp();
// void func_80026814_jp();
// void func_80026828_jp();
// void func_800269E4_jp();
// void func_80026A64_jp();
void DmaMgr_RequestSync(void* ram, void* vrom, size_t size);
// void func_80026BC0_jp();
// void func_80026C00_jp();
// void func_80026C28_jp();
s32 func_80026C4C_jp(void* vromStart, void* vromEnd, void* ovlStart, void* ovlEnd);
void func_80026CAC_jp(void);
void func_80026DA0_jp(void);
// void func_80026DCC_jp();
void func_80026E10_jp(void* arg0, RomOffset arg1, size_t arg2, const char* arg3, s32 arg4);

#endif
