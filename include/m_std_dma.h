#ifndef M_STD_DMA_H
#define M_STD_DMA_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "alignment.h"
#include "other_types.h"
#include "unk.h"

typedef s32 (*DmaHandler)(OSPiHandle* handle, OSIoMesg* mb, s32 direction);

typedef struct DmaRequest {
    /* 0x00 */ RomOffset vrom;
    /* 0x04 */ void* vram;
    /* 0x08 */ size_t size;
    /* 0x0C */ const char* filename;
    /* 0x10 */ s32 line;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ OSMesgQueue* mq;
    /* 0x1C */ OSMesg msg;
} DmaRequest; // size = 0x20

typedef struct DmaEntry {
    /* 0x0 */ RomOffset vromStart;
    /* 0x4 */ RomOffset vromEnd;
    /* 0x8 */ RomOffset romStart;
    /* 0xC */ RomOffset romEnd;
} DmaEntry; // size = 0x10

extern DmaEntry dma_rom_ad[];

s32 DmaMgr_DmaRomToRam(RomOffset vrom, void* vram, size_t size);
s32 DmaMgr_AudioDmaHandler(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction);
s32 DmaMgr_RequestSync(void* vram, RomOffset vrom, size_t size);
s32 DmaMgr_RequestSyncNoSize(void* vram, RomOffset vrom);
size_t DmaMgr_GetSegmentSize(RomOffset vrom);
RomOffset DmaMgr_GetOvlStart(RomOffset vrom);
s32 DmaMgr_GetOvlOffsets(RomOffset vromStart, RomOffset* vromEnd, RomOffset* ovlStart, RomOffset* ovlEnd);
void DmaMgr_Init(void);
void DmaMgr_Stop(void);
void DmaMgr_RequestAsync(DmaRequest* req, void* vram, RomOffset vrom, size_t size, s32 arg4, OSMesgQueue* mq, OSMesg msg, const char* filename, s32 line);
s32 DmaMgr_RequestSyncDebug(void* vram, RomOffset vrom, size_t size, const char* filename, s32 line);


#define DMAMGR_DEFAULT_BUFSIZE ALIGN16(0x2000)

extern size_t gDmaMgrDmaBuffSize;

extern size_t B_800406B0_jp;
extern size_t B_800406B4_jp;

#endif
