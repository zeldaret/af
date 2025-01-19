#ifndef SFRM_FLASHROM_H
#define SFRM_FLASHROM_H

#include "ultra64.h"
#include "unk.h"

typedef struct FlashromRequest {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 response;
    /* 0x08 */ void* addr;
    /* 0x0C */ u32 pageNum;
    /* 0x10 */ u32 pageCount;
    /* 0x14 */ OSMesgQueue queue;
    /* 0x2C */ OSMesg msgBuf[1];
} FlashromRequest; // size = 0x30

#define FLASHROM_REQUEST_WRITE 1
#define FLASHROM_REQUEST_READ 2

s32 func_800CDB10_jp(void);
s32 func_800CDBE0_jp(void);
s32 func_800CDC10_jp(void);
s32 func_800CDC30_jp(void* addr, u32 pageNum);
s32 func_800CDDE0_jp(void* addr, u32 pageNum);
void func_800CDECC_jp(void);
void func_800CDF78_jp(void* addr, u32 pageNum, u32 pageCount);
s32 func_800CE04C_jp(void);
s32 func_800CE090_jp(void);
void func_800CE0E8_jp(void* addr, u32 pageNum, u32 pageCount);
// void func_800CE110_jp();

#endif
