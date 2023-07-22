#ifndef OS_MALLOC_H
#define OS_MALLOC_H

#include "ultra64.h"

// TODO: check size and members
typedef struct ArenaNode {
    /* 0x0 */ s16 magic; // Should always be 0x7373
    /* 0x2 */ s16 isFree;
    /* 0x4 */ size_t size;
    /* 0x8 */ struct ArenaNode* next;
    /* 0xC */ struct ArenaNode* prev;
} ArenaNode; // size = 0x10

// TODO: check size and members
typedef struct {
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
// void __osMallocIsInitalized();
// void __osMallocNoLock();
// void __osMalloc();
// void __osMallocR();
// void __osFree_NoLock();
// void __osFree();
// void __osRealloc();
// void __osGetFreeArena();
// void ArenaImpl_FaultClient();
// void __osCheckArena();

#endif
