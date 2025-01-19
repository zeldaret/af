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

s32 sFRm_Init(void);
s32 sFRm_IsInit(void);
s32 sFRm_EraseAll(void);
s32 sFRm_WritePage(void* addr, u32 pageNum);
s32 sFRm_ReadPage(void* addr, u32 pageNum);
void sFRm_InitRequest(void);
void sFRm_WriteAsync(void* addr, u32 pageNum, u32 pageCount);
s32 sFRm_IsBusy(void);
s32 sFRm_AwaitResult(void);
void sFRm_WriteSync(void* addr, u32 pageNum, u32 pageCount);
s32 sFRm_GetResult(void);

#endif
