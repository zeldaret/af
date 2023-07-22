#ifndef OS_MALLOC_H
#define OS_MALLOC_H

#include "ultra64.h"

typedef struct ArenaNode {
    /* 0x0 */ s16 magic; // Should always be 0x7373
    /* 0x2 */ s16 isFree;
    /* 0x4 */ size_t size;
    /* 0x8 */ struct ArenaNode* next;
    /* 0xC */ struct ArenaNode* prev;
} ArenaNode; // size = 0x10

typedef struct Arena {
    /* 0x00 */ ArenaNode* head;
    /* 0x04 */ void* start;
    /* 0x08 */ OSMesgQueue lock;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 isInit;
    /* 0x22 */ u8 flag;
} Arena; // size = 0x24

void arena_lock_init(Arena* arena);
void arena_lock(Arena* arena);
void arena_unlock(Arena* arena);
ArenaNode* search_last_block(Arena* arena);
void __osMallocInit(Arena* arena, void* heap, size_t size);
void __osMallocAddBlock(Arena* arena, void* heap, size_t size);
void __osMallocCleanup(Arena* arena);
u8 __osMallocIsInitalized(Arena* arena);
void* __osMallocNoLock(Arena* arena, size_t size);
void* __osMalloc(Arena* arena, size_t size);
void* __osMallocR(Arena* arena, size_t size);
void __osFree_NoLock(Arena* arena, void* ptr);
void __osFree(Arena* arena, void* ptr);
void* __osRealloc(Arena* arena, void* ptr, size_t newSize);
void __osGetFreeArena(Arena* arena, size_t* outMaxFree, size_t* outFree, size_t* outAlloc);
void ArenaImpl_FaultClient(Arena* arena);
s32 __osCheckArena(Arena* arena);

#endif
