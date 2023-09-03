#include "libc64/osmalloc.h"
#include "alignment.h"
#include "fault.h"
#include "libc/stdbool.h"
#include "libc/stddef.h"
#include "libc/stdint.h"
#include "libc/memmove.h"
#include "macros.h"

#define NODE_MAGIC (0x7373)
#define NODE_IS_VALID(node) (((node) != NULL) && ((node)->magic == NODE_MAGIC))
#define NODE_GET_NEXT(node) (NODE_IS_VALID((node)->next) ? (node)->next : NULL)
#define NODE_GET_PREV(node) (NODE_IS_VALID((node)->prev) ? (node)->prev : NULL)

OSMesg sArenaLockMsg[1];

void __osMallocAddBlock(Arena* arena, void* heap, size_t size);

void arena_lock_init(Arena* arena) {
    osCreateMesgQueue(&arena->lock, sArenaLockMsg, ARRAY_COUNT(sArenaLockMsg));
}

void arena_lock(Arena* arena) {
    osSendMesg(&arena->lock, NULL, OS_MESG_BLOCK);
}

void arena_unlock(Arena* arena) {
    osRecvMesg(&arena->lock, NULL, OS_MESG_BLOCK);
}

ArenaNode* search_last_block(Arena* arena) {
    ArenaNode* last = NULL;

    if (arena != NULL) {
        if (NODE_IS_VALID(arena->head)) {
            ArenaNode* iter;

            iter = arena->head;
            while (iter != NULL) {
                last = iter;
                iter = NODE_GET_NEXT(last);
            }
        }
    }

    return last;
}

/**
 * Initializes \p arena to manage the memory region \p heap.
 *
 * @param arena  The Arena to initialize.
 * @param heap   The memory region to use as heap space.
 * @param size   The size of the heap.
 */
void __osMallocInit(Arena* arena, void* heap, size_t size) {
    bzero(arena, sizeof(Arena));

    arena_lock_init(arena);

    __osMallocAddBlock(arena, heap, size);
    arena->isInit = true;
}

void __osMallocAddBlock(Arena* arena, void* heap, size_t size) {
    ptrdiff_t diff;
    s32 alignedSize;
    ArenaNode* firstNode;
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

/**
 * Clears the whole \p arena, invalidating every allocated pointer to it.
 *
 * @param arena  The Arena to clear.
 */
void __osMallocCleanup(Arena* arena) {
    bzero(arena, sizeof(Arena));
}

/**
 * Returns whether or not the \p arena has been initialized.
 *
 * @param arena  The Arena to check.
 * @return u8    `true` if the \p arena has been initialized. `false` otherwise.
 */
u8 __osMallocIsInitalized(Arena* arena) {
    return arena->isInit;
}

/**
 * See the description of `__osMalloc`.
 *
 * The only difference is this function does not lock the arena, making it suitable for being reused from other
 * functions of this file.
 */
void* __osMallocNoLock(Arena* arena, size_t size) {
    ArenaNode* iter;
    size_t blockSize;
    void* alloc = NULL;

    size = ALIGN16(size);
    blockSize = ALIGN16(size) + sizeof(ArenaNode);

    // Start iterating from the head of the arena.
    iter = arena->head;

    // Iterate over the arena looking for a big enough space of memory.
    while (iter != NULL) {
        if (iter->isFree && (iter->size >= size)) {

            // If the block is larger than the requested size, then split it and just use the required size of the
            // current block.
            if (blockSize < iter->size) {
                ArenaNode* newNode;
                ArenaNode* next;

                newNode = (ArenaNode*)((uintptr_t)iter + blockSize);
                newNode->next = NODE_GET_NEXT(iter);

                newNode->prev = iter;
                newNode->size = iter->size - blockSize;
                newNode->isFree = true;
                newNode->magic = NODE_MAGIC;

                iter->next = newNode;
                iter->size = size;

                next = NODE_GET_NEXT(newNode);
                if (next != NULL) {
                    next->prev = newNode;
                }
            }

            iter->isFree = 0;
            alloc = (void*)((uintptr_t)iter + sizeof(ArenaNode));
            break;
        }

        iter = NODE_GET_NEXT(iter);
    }

    return alloc;
}

/**
 * Allocates at least \p size bytes of memory using the given \p arena.
 * The block of memory will be allocated at the start of the first sufficiently large free block.
 *
 *  - If there's not enough space in the given \p arena, this function will fail, returning `NULL`.
 *  - If \p size is zero, then an empty region of memory is returned.
 *
 * To avoid memory leaks, the returned pointer should be eventually deallocated using either `__osFree` or
 * `__osRealloc`.
 *
 * @param[in, out] arena  The specific Arena to be used for the allocation.
 * @param[in] size        The size in bytes that will be allocated.
 * @return void*          On success, the allocated area of the \p arena memory. Otherwise, `NULL`.
 */
void* __osMalloc(Arena* arena, size_t size) {
    void* alloc;

    arena_lock(arena);

    alloc = __osMallocNoLock(arena, size);

    arena_unlock(arena);

    return alloc;
}

/**
 * Allocates at least \p size bytes of memory using the given \p arena.
 * Unlike __osMalloc, the block of memory will be allocated from the end of the \p arena.
 *
 * - If there's not enough space in the given \p arena, this function will fail, returning `NULL`.
 * - If \p size is zero, then an empty region of memory is returned.
 *
 * To avoid memory leaks, the returned pointer should be eventually deallocated using `__osFree` or `__osRealloc`.
 *
 * @param[in, out] arena  The specific Arena to be used for the allocation.
 * @param[in] size        The size in bytes that will be allocated.
 * @return void*          On success, the allocated area of the \p arena memory. Otherwise, `NULL`.
 */
void* __osMallocR(Arena* arena, size_t size) {
    ArenaNode* newNode;
    ArenaNode* temp_a0;
    ArenaNode* next;
    ArenaNode* iter;
    ArenaNode* alloc;
    size_t blockSize;

    alloc = NULL;
    size = ALIGN16(size);
    blockSize = ALIGN16(size) + sizeof(ArenaNode);

    arena_lock(arena);

    // Start iterating from the last block of the arena.
    iter = search_last_block(arena);

    // Iterate in reverse the arena looking for a big enough space of memory.
    while (iter != NULL) {
        if (iter->isFree && (iter->size >= size)) {
            // If the block is larger than the requested size, then split it and just use the required size of the
            // current block.
            if (blockSize < iter->size) {
                temp_a0 = (ArenaNode*)((uintptr_t)iter + (iter->size - size));

                temp_a0->next = NODE_GET_NEXT(iter);
                //! FAKE?
                newNode = temp_a0;
                newNode->prev = iter;
                newNode->size = size;
                newNode->magic = NODE_MAGIC;

                iter->next = newNode;
                iter->size -= blockSize;

                next = NODE_GET_NEXT(newNode);
                if (next != NULL) {
                    next->prev = newNode;
                }

                iter = newNode;
            }

            iter->isFree = false;
            alloc = (void*)((uintptr_t)iter + sizeof(ArenaNode));
            break;
        }

        iter = NODE_GET_PREV(iter);
    }

    arena_unlock(arena);

    return alloc;
}

/**
 * See the description of `__osFree`.
 *
 * The only difference is this function does not lock the arena, making it suitable for being reused from other
 * functions of this file.
 */
void __osFree_NoLock(Arena* arena UNUSED, void* ptr) {
    ArenaNode* node;
    ArenaNode* next;
    ArenaNode* prev;

    if (ptr == NULL) {
        return;
    }

    node = (ArenaNode*)((uintptr_t)ptr - sizeof(ArenaNode));

    if ((node == NULL) || (node->magic != NODE_MAGIC) || node->isFree) {
        return;
    }

    next = NODE_GET_NEXT(node);
    prev = NODE_GET_PREV(node);

    node->isFree = true;

    // Checks if the next node is contiguous to the current node and if it isn't currently allocated. Then merge the two
    // nodes into one.
    if (((uintptr_t)next == ((uintptr_t)node + node->size + sizeof(ArenaNode))) && next->isFree) {
        ArenaNode* newNext;

        newNext = NODE_GET_NEXT(next);

        if (newNext != NULL) {
            newNext->prev = node;
        }

        node->size += next->size + sizeof(ArenaNode);
        node->next = newNext;

        next = newNext;
    }

    // Checks if the previous node is contiguous to the current node and if it isn't currently allocated. Then merge the
    // two nodes into one.
    if ((prev != NULL) && prev->isFree && ((uintptr_t)node == ((uintptr_t)prev + prev->size + sizeof(ArenaNode)))) {
        if (next != NULL) {
            next->prev = prev;
        }

        prev->next = next;
        prev->size += node->size + sizeof(ArenaNode);
    }
}

/**
 * Deallocates the pointer \p ptr previously allocated by `__osMalloc`, `__osMallocR` or `__osRealloc`.
 * If \p ptr is `NULL` or it has been already been freed, then this function does nothing.
 *
 * - The behaviour is undefined if \p ptr is not a memory region returned by one of the cited allocating
 * functions.
 * - The behaviour is undefined if \p ptr doesn't correspond to the given \p arena.
 * - Any access to the freed pointer is undefined behaviour.
 *
 * @param[in, out] arena  The specific Arena to be used for the allocation.
 * @param[in, out] ptr    The allocated memory block to deallocate.
 */
void __osFree(Arena* arena, void* ptr) {
    arena_lock(arena);

    __osFree_NoLock(arena, ptr);

    arena_unlock(arena);
}

/**
 * Reallocates the pointer \p ptr.
 * \p ptr must be either a pointer previously allocated by `__osMalloc`, `__osMallocR` or `__osRealloc` and
 * not freed yet, or a `NULL` pointer.
 *
 * - If \p ptr is `NULL` a new pointer is allocated. See `__osMalloc` for more details.
 * - If \p newSize is 0, then the given pointer is freed and `NULL` is returned. See `__osFree` for more details.
 * - If \p newSize is the same than the currently allocated pointer then the original unmodified pointer is returned.
 * - If \p newSize is bigger than the currently allocated allocated pointer, then the area of memory is expanded to a
 * size big enough to fit the requested size.
 * - If \p newSize is smaller than the currently allocated allocated pointer, then the area of memory is shrinked to an
 * smaller size.
 *
 * Resizing the allocated space of the passed may fail, in which case `NULL` is returned.
 *
 * - The behaviour is undefined if \p ptr is not a memory region returned by one of the cited allocating
 * functions.
 * - The behaviour is undefined if \p ptr doesn't correspond to the given \p arena.
 * - If the pointer is freed, then any access to the original freed pointer is undefined behaviour.
 *
 * @param[in, out] arena  The specific Arena to be used for the allocation.
 * @param[in, out] ptr    The allocated memory block to deallocate.
 * @param[in] newSize     The new requested size.
 * @return void*          On success, the pointer to the reallocated area of memory. On failure, `NULL` is returned,
 * and the original parameter \p ptr remains valid.
 */
void* __osRealloc(Arena* arena, void* ptr, size_t newSize) {
    newSize = ALIGN16(newSize);

    osSyncPrintf("__osRealloc(%08x, %d)\n", ptr, newSize);

    arena_lock(arena);

    if (ptr == NULL) {
        // if the `ptr` is NULL, then allocate a new pointer with the specified size
        // if newSize is 0, then __osMalloc would return a NULL pointer

        ptr = __osMallocNoLock(arena, newSize);
    } else if (newSize == 0) {
        // if the requested size is zero, then free the pointer
        __osFree_NoLock(arena, ptr);
        ptr = NULL;
    } else {
        ArenaNode* node;
        ArenaNode* nextAux;
        ArenaNode* next; // sp64
        s32 pad UNUSED;
        ArenaNode* var_v0;
        s32 fullNodeSize;
        ArenaNode* var_a1_2; // sp54
        size_t sizeDiff;     // sp50

        // Gets the start of the ArenaNode pointer embedded
        node = (ArenaNode*)((uintptr_t)ptr - sizeof(ArenaNode));

        if (newSize == node->size) {
            // If the requested size is the same as the already allocated one then do nothing.

            // "Do nothing because the memory block size doesn't change"
            osSyncPrintf("メモリブロックサイズが変わらないためなにもしません\n");
        } else if (node->size < newSize) {
            // The requested size is bigger than the already allocated one.

            next = NODE_GET_NEXT(node);
            sizeDiff = newSize - node->size;

            // Checks if the next node is contiguous to the current allocated node and it has enough space to fit the
            // new requested size
            if (((uintptr_t)next == ((uintptr_t)node + node->size + sizeof(ArenaNode))) && next->isFree &&
                (next->size >= sizeDiff)) {
                // "Join because there is a free block after the current memory block"
                osSyncPrintf("現メモリブロックの後ろにフリーブロックがあるので結合します\n");

                next->size -= sizeDiff;

                nextAux = NODE_GET_NEXT(next);
                if (nextAux != NULL) {
                    nextAux->prev = (ArenaNode*)((uintptr_t)next + sizeDiff);
                }

                node->next = (ArenaNode*)((uintptr_t)next + sizeDiff);
                node->size = newSize;
                memmove(node->next, next, sizeof(ArenaNode));
            } else {
                // Create a new pointer and manually copy the data from the old pointer to the new one.
                void* newPtr;

                // "Allocate a new memory block and move the contents"
                osSyncPrintf("新たにメモリブロックを確保して内容を移動します\n");

                newPtr = __osMallocNoLock(arena, newSize);
                if (newPtr != NULL) {
                    bcopy(ptr, newPtr, node->size);
                    __osFree_NoLock(arena, ptr);
                }
                ptr = newPtr;
            }
        } else if (newSize < node->size) {
            // The requested size is smaller than the already allocated one.

            ArenaNode sp3C;
            ArenaNode* temp_v1_2;
            s32 pad2 UNUSED;

            var_a1_2 = NODE_GET_NEXT(node);

            if ((var_a1_2 != NULL) && var_a1_2->isFree) {
                // Decrease the size of the allocated pointer and pass that size to the next node.

                // "Increase the free block behind the current memory block"
                osSyncPrintf("現メモリブロックの後ろのフリーブロックを大きくしました\n");

                fullNodeSize = ALIGN16(newSize) + sizeof(ArenaNode);
                temp_v1_2 = (ArenaNode*)((uintptr_t)node + fullNodeSize);

                sp3C = *var_a1_2;
                *temp_v1_2 = sp3C;

                temp_v1_2->size += node->size - newSize;
                node->next = temp_v1_2;
                node->size = newSize;

                var_v0 = NODE_GET_NEXT(temp_v1_2);
                if (var_v0 != NULL) {
                    var_v0->prev = temp_v1_2;
                }
            } else if (newSize + sizeof(ArenaNode) < node->size) {
                // Create a new node after the current one to allow shrinking it.

                // "Create because there is no free block after the current memory block"
                osSyncPrintf("現メモリブロックの後ろにフリーブロックがないので生成します\n");

                fullNodeSize = ALIGN16(newSize) + sizeof(ArenaNode);
                temp_v1_2 = (ArenaNode*)((uintptr_t)node + fullNodeSize);

                temp_v1_2->next = NODE_GET_NEXT(node);

                temp_v1_2->prev = node;
                temp_v1_2->size = node->size - fullNodeSize;
                temp_v1_2->isFree = true;
                temp_v1_2->magic = NODE_MAGIC;

                node->next = temp_v1_2;
                node->size = newSize;

                var_v0 = NODE_GET_NEXT(temp_v1_2);
                if (var_v0 != NULL) {
                    var_v0->prev = temp_v1_2;
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

/**
 * Gets the size of the largest free block, the total free space and the total allocated space.
 *
 * @param[in, out] arena   The Arena which will be used to get the values from.
 * @param[out] outMaxFree  The size of the largest free block.
 * @param[out] outFree     The total free space.
 * @param[out] outAlloc    The total allocated space.
 */
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

        iter = NODE_GET_NEXT(iter);
    }

    arena_unlock(arena);
}

/**
 * Fault Client for an Arena. Reports information about the state of the Arena in the crash debugger.
 */
void ArenaImpl_FaultClient(Arena* arena) {
    ArenaNode* iter;
    ArenaNode* next;
    size_t allocated;
    size_t free;
    size_t largestFree;

    FaultDrawer_Printf("ARENA INFO (0x%08x)\n", arena);

    if (!__osMallocIsInitalized(arena)) {
        FaultDrawer_Printf("Arena is uninitalized\n", arena);
        return;
    }

    largestFree = 0;
    free = 0;
    allocated = 0;

    FaultDrawer_Printf("Memory Block Region status size\n");

    for (iter = arena->head; iter != NULL; iter = next) {
        if (NODE_IS_VALID(iter)) {
            next = iter->next;

            FaultDrawer_Printf("%08x-%08x%c %s %08x", iter, (uintptr_t)iter + iter->size + sizeof(ArenaNode),
                               (next == NULL) ? '$' : ((iter != next->prev) ? '!' : ' '), iter->isFree ? "F" : "A",
                               iter->size);
            FaultDrawer_Printf("\n");
            if (iter->isFree) {
                free += iter->size;
                if (largestFree < iter->size) {
                    largestFree = iter->size;
                }
            } else {
                allocated += iter->size;
            }
        } else {
            FaultDrawer_SetFontColor(GPACK_RGBA5551(255, 0, 0, 1));
            FaultDrawer_Printf("%08x Block Invalid\n", iter);
            next = NULL;
        }
    }

    FaultDrawer_SetFontColor(GPACK_RGBA5551(0, 255, 192, 1));
    FaultDrawer_Printf("Total Alloc Block Size  %08x\n", allocated);
    FaultDrawer_Printf("Total Free Block Size   %08x\n", free);
    FaultDrawer_Printf("Largest Free Block Size %08x\n", largestFree);
}

/**
 * Checks the validity of every node of the \p arena.
 *
 * @param arena  The Arena to check.
 * @return s32   `false` if every pointer is valid. `true` otherwise.
 */
s32 __osCheckArena(Arena* arena) {
    ArenaNode* iter;
    s32 err = false;

    arena_lock(arena);

    // "Checking the contents of the arena..."
    osSyncPrintf("アリーナの内容をチェックしています．．． (%08x)\n", arena);

    iter = arena->head;
    while (iter != NULL) {
        //! @bug This condition should be inverted. Because of it, this function will report a valid Arena as being
        //! faulty.
        if (NODE_IS_VALID(iter)) {
            // "Oops!!"
            osSyncPrintf("おおっと！！ (%08x %08x)\n", iter, iter->magic);

            err = true;
            break;
        }

        iter = NODE_GET_NEXT(iter);
    }

    if (!err) {
        // "Arena is still valid"
        osSyncPrintf("アリーナはまだ、いけそうです\n");
    }

    arena_unlock(arena);

    return err;
}
