#ifndef TWO_HEAD_ARENA_H
#define TWO_HEAD_ARENA_H

#include "ultra64.h"
#include "libc/stdint.h"

typedef struct TwoHeadArena {
    /* 0x00 */ size_t size;
    /* 0x04 */ void* start;
    /* 0x08 */ void* head;
    /* 0x0C */ void* tail;
} TwoHeadArena; // size = 0x10

void* THA_getHeadPtr(TwoHeadArena* tha);
void THA_setHeadPtr(TwoHeadArena* tha, void* newHead);
void* THA_getTailPtr(TwoHeadArena* tha);
void* THA_nextPtrN(TwoHeadArena* tha, size_t size);
void* THA_nextPtr1(TwoHeadArena* tha);
void* THA_alloc(TwoHeadArena* tha, size_t size);
void* THA_alloc16(TwoHeadArena* tha, size_t size);
void* THA_allocAlign(TwoHeadArena* tha, size_t size, uintptr_t mask);
s32 THA_getFreeBytes(TwoHeadArena* tha);
u32 THA_isCrash(TwoHeadArena* tha);
void THA_init(TwoHeadArena* tha);
void THA_ct(TwoHeadArena* tha, void* start, size_t size);
void THA_dt(TwoHeadArena* tha);

#endif
