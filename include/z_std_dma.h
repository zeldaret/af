#ifndef Z_STD_DMA_H
#define Z_STD_DMA_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "alignment.h"
#include "other_types.h"
#include "unk.h"

typedef struct DmaRequest {
    /* 0x00 */ RomOffset vrom;
    /* 0x04 */ void* vram;
    /* 0x08 */ size_t size;
    /* 0x0C */ const char* filename;
    /* 0x10 */ s32 line;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ OSMesgQueue* mq;
    /* 0x1C */ OSMesg unk_1C;
} DmaRequest; // size = 0x20

typedef struct DmaEntry {
    /* 0x0 */ RomOffset vromStart;
    /* 0x4 */ RomOffset vromEnd;
    /* 0x8 */ RomOffset romStart;
    /* 0xC */ RomOffset romEnd;
} DmaEntry; // size = 0x10

extern DmaEntry dma_rom_ad[];

s32 DmaMgr_DmaRomToRam(RomOffset vrom, void* vram, size_t size);
s32 DmaMgr_AudioDmaHandler(OSPiHandle* arg0, OSIoMesg* arg1, s32 arg2);
s32 DmaMgr_RequestSync(void* ram, RomOffset vrom, size_t size);
s32 func_80026BC0_jp(void* vram, RomOffset vrom);
size_t func_80026C00_jp(RomOffset vrom);
RomOffset func_80026C28_jp(RomOffset vrom);
s32 func_80026C4C_jp(RomOffset vromStart, RomOffset* vromEnd, RomOffset* ovlStart, RomOffset* ovlEnd);
void DmaMgr_Init(void);
void DmaMgr_Stop(void);
void DmaMgr_RequestAsync(DmaRequest* req, void* vram, RomOffset vrom, size_t size, s32 arg4, OSMesgQueue* mq, OSMesg msg, const char* filename, s32 line);
s32 DmaMgr_RequestSyncDebug(void* arg0, RomOffset arg1, size_t arg2, const char* arg3, s32 arg4);


#define DMAMGR_DEFAULT_BUFSIZE ALIGN16(0x2000)

// .data
extern size_t gDmaMgrDmaBuffSize;

// .bss
extern size_t B_800406B0_jp;
extern size_t B_800406B4_jp;

#endif
