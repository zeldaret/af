#include "osmalloc.h"
#include "alignment.h"
#include "libc/stdbool.h"
#include "libc/stddef.h"
#include "libc/stdint.h"
#include "macros.h"

//#define FILL_ALLOCBLOCK (1 << 0)
//#define FILL_FREEBLOCK (1 << 1)
//#define CHECK_FREE_BLOCK (1 << 2)

#define NODE_MAGIC (0x7373)

//#define BLOCK_UNINIT_MAGIC (0xAB)
//#define BLOCK_UNINIT_MAGIC_32 (0xABABABAB)
//#define BLOCK_ALLOC_MAGIC (0xCD)
//#define BLOCK_ALLOC_MAGIC_32 (0xCDCDCDCD)
//#define BLOCK_FREE_MAGIC (0xEF)
//#define BLOCK_FREE_MAGIC_32 (0xEFEFEFEF)

// sArenaLockMsg
extern OSMesg B_80041A00_jp[1];

void arena_lock_init(Arena* arena) {
    osCreateMesgQueue(&arena->lock, B_80041A00_jp, ARRAY_COUNT(B_80041A00_jp));
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/arena_lock.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/arena_unlock.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/search_last_block.s")

void __osMallocInit(Arena* arena, void* heap, size_t size) {
    bzero(arena, sizeof(Arena));

    arena_lock_init(arena);

    __osMallocAddBlock(arena, heap, size);
    arena->isInit = true;
}

void __osMallocAddBlock(Arena* arena, void* heap, size_t size) {
    ptrdiff_t diff;
    s32 alignedSize;
    ArenaNode *firstNode;
    ArenaNode* lastNode;

    if (heap == NULL) {
        return;
    }

    firstNode = (ArenaNode*)ALIGN16((uintptr_t)heap);
    diff = (uintptr_t)firstNode - (uintptr_t)heap;
    alignedSize = ((s32)size - diff) & ~0xF;

    // If the size of the heap is smaller than sizeof(ArenaNode), then the initialization will silently fail
    if (alignedSize <= (s32)sizeof(ArenaNode)) {
        return;
    }

    firstNode->next = NULL;
    firstNode->prev = NULL;
    firstNode->size = alignedSize - sizeof(ArenaNode);
    firstNode->isFree = true;
    firstNode->magic = NODE_MAGIC;

    arena_lock(arena);

    lastNode = search_last_block(arena);

    // Checks if there's already a block
    if (lastNode == NULL) {
        arena->head = firstNode;
        arena->start = heap;
    } else {
        // Chain the existing block with the new one
        firstNode->prev = lastNode;
        lastNode->next = firstNode;
    }

    arena_unlock(arena);
}

void __osMallocCleanup(Arena* arena) {
    bzero(arena, sizeof(Arena));
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osMallocIsInitalized.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osMallocNoLock.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osMalloc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osMallocR.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osFree_NoLock.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osFree.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osRealloc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osGetFreeArena.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/ArenaImpl_FaultClient.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osCheckArena.s")
