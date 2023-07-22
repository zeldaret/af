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
// TODO: CHECK_MAGIC macro?

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

void arena_lock(Arena* arena) {
    osSendMesg(&arena->lock, NULL, OS_MESG_BLOCK);
}

void arena_unlock(Arena* arena) {
    osRecvMesg(&arena->lock, NULL, OS_MESG_BLOCK);
}

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

u8 __osMallocIsInitalized(Arena* arena) {
    return arena->isInit;
}

void* __osMallocNoLock(Arena* arena, size_t size) {
    ArenaNode* iter;
    size_t blockSize;
    void* alloc = NULL;

    size = ALIGN16(size);
    blockSize = ALIGN16(size) + sizeof(ArenaNode);

    iter = arena->head;
    while (iter != NULL) {
        if (iter->isFree && (iter->size >= size)) {
            if (blockSize < iter->size) {
                ArenaNode* newNode;
                ArenaNode* next;

                newNode = (ArenaNode*)((uintptr_t)iter + blockSize);
                newNode->next = ((iter->next != NULL) && (iter->next->magic == 0x7373)) ? iter->next : NULL;

                newNode->prev = iter;
                newNode->size = iter->size - blockSize;
                newNode->isFree = 1;
                newNode->magic = 0x7373;

                iter->next = newNode;
                iter->size = size;

                next = ((newNode->next != NULL) && (newNode->next->magic == 0x7373)) ? newNode->next : NULL;
                if (next != NULL) {
                    next->prev = newNode;
                }
            }

            iter->isFree = 0;
            alloc = (void*)((uintptr_t)iter + sizeof(ArenaNode));
            break;
        }

        iter = ((iter->next != NULL) && (iter->next->magic == 0x7373)) ? iter->next : NULL;
    }

    return alloc;
}

void* __osMalloc(Arena* arena, size_t size) {
    void* alloc;

    arena_lock(arena);

    alloc = __osMallocNoLock(arena, size);

    arena_unlock(arena);

    return alloc;
}

void* __osMallocR(Arena* arena, size_t size) {
    ArenaNode *newNode;
    ArenaNode* temp_a0;
    ArenaNode* next;
    ArenaNode* iter;
    ArenaNode* alloc;
    size_t blockSize;

    alloc = NULL;
    size = ALIGN16(size);
    blockSize = ALIGN16(size) + sizeof(ArenaNode);

    arena_lock(arena);

    iter = search_last_block(arena);
    while (iter != NULL) {
        if (iter->isFree && (iter->size >= size)) {
            if (blockSize < iter->size) {
                temp_a0 = (ArenaNode*)((uintptr_t)iter + (iter->size - size));

                temp_a0->next = ((iter->next != NULL) && (iter->next->magic == NODE_MAGIC)) ? iter->next : NULL;
                //! FAKE?
                newNode = temp_a0;
                newNode->prev = iter;
                newNode->size = size;
                newNode->magic = NODE_MAGIC;

                iter->next = newNode;
                iter->size -= blockSize;

                next = ((newNode->next != NULL) && (newNode->next->magic == NODE_MAGIC)) ? newNode->next : NULL;
                if (next != NULL) {
                    next->prev = newNode;
                }

                iter = newNode;
            }

            iter->isFree = false;
            alloc = (void*)((uintptr_t)iter + sizeof(ArenaNode));
            break;
        }

        iter = ((iter->prev != NULL) && (iter->prev->magic == NODE_MAGIC)) ? iter->prev : NULL;
    }

    arena_unlock(arena);

    return alloc;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osFree_NoLock.s")

void __osFree(Arena* arena, void* ptr) {
    arena_lock(arena);

    __osFree_NoLock(arena, ptr);

    arena_unlock(arena);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osRealloc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osGetFreeArena.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/ArenaImpl_FaultClient.s")

s32 __osCheckArena(Arena* arena) {
    ArenaNode* iter;
    s32 err = false;

    arena_lock(arena);

    // "Checking the contents of the arena..."
    osSyncPrintf("アリーナの内容をチェックしています．．． (%08x)\n", arena);

    iter = arena->head;
    while (iter != NULL) {
        if ((iter != NULL) && (iter->magic == NODE_MAGIC)) {
            // "Oops!!"
            osSyncPrintf("おおっと！！ (%08x %08x)\n", iter, iter->magic);

            err = true;
            break;
        }

        iter = ((iter->next != NULL) && (iter->next->magic == NODE_MAGIC)) ? iter->next : NULL;
    }

    if (!err) {
        osSyncPrintf("アリーナはまだ、いけそうです\n");
    }

    arena_unlock(arena);

    return err;
}
