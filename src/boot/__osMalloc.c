#include "osmalloc.h"
#include "alignment.h"
#include "boot_functions.h"
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

#ifdef NON_EQUIVALENT
ArenaNode* search_last_block(Arena* arena) {
    ArenaNode* var_v1;

    var_v1 = NULL;
    if (arena != NULL) {
        if ((arena->head != NULL) && (arena->head->magic == 0x7373)) {
            ArenaNode* var_a0;

            var_a0 = arena->head;
            while (var_a0 != NULL) {
                var_v1 = var_a0;
                var_a0 = ((var_a0->next != NULL) && (var_a0->next->magic == 0x7373)) ? var_a0->next : NULL;
            }
        }
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/search_last_block.s")
#endif

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

void __osFree_NoLock(Arena* arena UNUSED, void* ptr) {
    ArenaNode* node;
    ArenaNode* next;
    ArenaNode* prev;

    if (ptr == NULL) {
        return;
    }

    node = (ArenaNode *)((uintptr_t)ptr - sizeof(ArenaNode));

    if ((node == NULL) || (node->magic != NODE_MAGIC) || node->isFree) {
        return;
    }

    next = ((node->next != NULL) && (node->next->magic == NODE_MAGIC)) ? node->next : NULL;
    prev = ((node->prev != NULL) && (node->prev->magic == NODE_MAGIC)) ? node->prev : NULL;

    node->isFree = true;

    // Checks if the next node is contiguous to the current node and if it isn't currently allocated. Then merge the two nodes into one.
    if (((uintptr_t)next == ((uintptr_t)node + node->size + sizeof(ArenaNode))) && next->isFree) {
        ArenaNode* newNext;

        newNext = ((next->next != NULL) && (next->next->magic == NODE_MAGIC)) ? next->next : NULL;

        if (newNext != NULL) {
            newNext->prev = node;
        }

        node->size += next->size + sizeof(ArenaNode);
        node->next = newNext;

        next = newNext;
    }

    // Checks if the previous node is contiguous to the current node and if it isn't currently allocated. Then merge the two nodes into one.
    if ((prev != NULL) && prev->isFree && ((uintptr_t)node == ((uintptr_t)prev + prev->size + sizeof(ArenaNode)))) {
        if (next != NULL) {
            next->prev = prev;
        }

        prev->next = next;
        prev->size += node->size + sizeof(ArenaNode);
    }
}

void __osFree(Arena* arena, void* ptr) {
    arena_lock(arena);

    __osFree_NoLock(arena, ptr);

    arena_unlock(arena);
}

#ifdef NON_MATCHING
void *__osRealloc(Arena *arena, void *ptr, size_t newSize) {

    newSize = (newSize + 0xF) & ~0xF;

    osSyncPrintf("__osRealloc(%08x, %d)\n", ptr, newSize);

    arena_lock(arena);

    if (ptr == NULL) {
        ptr = __osMallocNoLock(arena, newSize);
    } else if (newSize == 0) {
        __osFree_NoLock(arena, ptr);
        ptr = NULL;
    } else {
        ArenaNode *temp_v1_2;
        ArenaNode *var_v0;
        ArenaNode *var_a1; // sp64
        ArenaNode *var_v1;
        ArenaNode *var_v1_2;
        s32 var_a1_3;
        ArenaNode *var_a1_2; // sp54
        size_t temp_t0; // sp50
        size_t temp_v1;
        ArenaNode sp3C;
        ArenaNode *temp_a3; // sp30

        temp_a3 = (uintptr_t)ptr - 0x10;

        if (newSize == temp_a3->size) {
            // "Do nothing because the memory block size doesn't change"
            osSyncPrintf("メモリブロックサイズが変わらないためなにもしません\n");
        } else if (temp_a3->size < newSize) {
            var_a1 = ((temp_a3->next != NULL) && (temp_a3->next->magic == 0x7373)) ? temp_a3->next : NULL;
            temp_t0 = newSize - temp_a3->size;

            if (((uintptr_t)var_a1 == ((uintptr_t)temp_a3 + temp_a3->size + 0x10)) && var_a1->isFree && (var_a1->size >= temp_t0)) {
                // "Join because there is a free block after the current memory block"
                osSyncPrintf("現メモリブロックの後ろにフリーブロックがあるので結合します\n");

                var_a1->size -= temp_t0;

                var_v1 = ((var_a1->next != NULL) && (var_a1->next->magic == 0x7373)) ? var_a1->next : NULL;

                if (var_v1 != NULL) {
                    var_v1->prev = (ArenaNode *) ((uintptr_t)var_a1 + temp_t0);
                }

                temp_a3->next = (uintptr_t)var_a1 + temp_t0;
                temp_a3->size = newSize;
                func_8003BA60_jp(temp_a3->next, var_a1, 0x10);
            } else {
                void *temp_v0_3;

                // "Allocate a new memory block and move the contents"
                osSyncPrintf("新たにメモリブロックを確保して内容を移動します\n");

                temp_v0_3 = __osMallocNoLock(arena, newSize);
                if (temp_v0_3 != NULL) {
                    bcopy(ptr, temp_v0_3, temp_a3->size);
                    __osFree_NoLock(arena, ptr);
                }
                ptr = temp_v0_3;
            }
        } else if (newSize < temp_a3->size) {
            var_a1_2 = ((temp_a3->next != NULL) && (temp_a3->next->magic == 0x7373)) ?  temp_a3->next : NULL;

            if ((var_a1_2 != NULL) && (var_a1_2->isFree != 0)) {
                // "Increase the free block behind the current memory block"
                osSyncPrintf("現メモリブロックの後ろのフリーブロックを大きくしました\n");

                temp_v1_2 = (uintptr_t)temp_a3 + ((newSize + 0xF) & ~0xF) + 0x10;

                sp3C = *var_a1_2;
                *temp_v1_2 = sp3C;

                temp_v1_2->size += temp_a3->size - newSize;
                temp_a3->next = temp_v1_2;
                temp_a3->size = newSize;

                var_v0 = ((temp_v1_2->next != NULL) && (temp_v1_2->next->magic == 0x7373)) ? temp_v1_2->next : NULL;

                if (var_v0 != NULL) {
                    var_v0->prev = temp_v1_2;
                }
            } else if (newSize + 0x10 < temp_a3->size) {
                // "Create because there is no free block after the current memory block"
                osSyncPrintf("現メモリブロックの後ろにフリーブロックがないので生成します\n");

                var_a1_3 = ((newSize + 0xF) & ~0xF) + 0x10;
                var_v1_2 = (uintptr_t)temp_a3 + var_a1_3;

                var_v1_2->next = ((temp_a3->next != NULL) && (temp_a3->next->magic == 0x7373)) ? temp_a3->next : NULL;

                var_v1_2->prev = temp_a3;
                var_v1_2->size = temp_a3->size - var_a1_3;
                var_v1_2->isFree = 1;
                var_v1_2->magic = 0x7373;

                // if (1) { }

                temp_a3->next = var_v1_2;
                temp_a3->size = newSize;

                var_v0 = ((var_v1_2->next != NULL) && (var_v1_2->next->magic == 0x7373)) ? var_v1_2->next : NULL;
                if (var_v0 != NULL) {
                    var_v0->prev = var_v1_2;
                }
            } else {
                // "Not enough space to generate free blocks"
                osSyncPrintf("フリーブロック生成するだけの空きがありません\n");
                ptr = NULL;
            }
        }
    }

    arena_unlock(arena);

    return ptr;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/__osMalloc/__osRealloc.s")
#endif

void __osGetFreeArena(Arena* arena, size_t* outMaxFree, size_t* outFree, size_t* outAlloc) {
    ArenaNode* iter;

    arena_lock(arena);

    *outMaxFree = 0;
    *outFree = 0;
    *outAlloc = 0;

    iter = arena->head;
    while (iter != NULL) {
        if (iter->isFree) {
            *outFree += iter->size;
            if (*outMaxFree < iter->size) {
                *outMaxFree = iter->size;
            }
        } else {
            *outAlloc += iter->size;
        }

        iter = ((iter->next != NULL) && (iter->next->magic == 0x7373)) ? iter->next : NULL;
    }

    arena_unlock(arena);
}

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
