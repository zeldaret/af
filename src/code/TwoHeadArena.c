/**
 * @file TwoHeadArena.c
 *
 * This file implements a simple general purpose double-ended stack allocator.
 *
 * A double-ended stack allocator accepts allocations at either the "head" or "tail" of its allotted memory region.
 * While in general this type of allocator could accept deallocations on the most recently allocated block at either
 * end, this implementation does not support any individual deallocations; the only provided way to deallocate anything
 * is to reset the entire arena, deallocating everything. This scheme is most applicable to allocating similar data
 * with identical lifetime.
 */

#include "global.h"
#include "TwoHeadArena.h"

void* THA_getHeadPtr(TwoHeadArena* tha) {
    return tha->head;
}

void THA_setHeadPtr(TwoHeadArena* tha, void* newHead) {
    tha->head = newHead;
}

void* THA_getTailPtr(TwoHeadArena* tha) {
    return tha->tail;
}

/**
 * Allocates to the head of the Two Head Arena. The allocation will not have any alignment guarantees.
 */
void* THA_nextPtrN(TwoHeadArena* tha, size_t size) {
    void* start = tha->head;

    tha->head = (u8*)tha->head + size;
    return start;
}

void* THA_nextPtr1(TwoHeadArena* tha) {
    return THA_nextPtrN(tha, 1);
}

/**
 * Allocates to the tail end of the Two Head Arena. The allocation will be aligned based on the size of the allocation.
 * All allocations of 16 bytes or more will be aligned to 16-bytes. Otherwise, the alignment will be the largest power
 * of 2 for which the size is a multiple, in order to accommodate the alignment requirements of any data types that can
 * fit within the allocation.
 */
void* THA_alloc(TwoHeadArena* tha, size_t size) {
    uintptr_t mask;

    if (size == 0x8) {
        mask = ALIGN_MASK(0x8);
    } else if ((size == 0x4) || (size == 0xC)) {
        mask = ALIGN_MASK(0x4);
    } else if ((size == 0x2) || (size == 0x6) || (size == 0xA) || (size == 0xE)) {
        mask = ALIGN_MASK(0x2);
    } else if (size >= 0x10) {
        mask = ALIGN_MASK(0x10);
    } else {
        mask = ALIGN_MASK(0x1);
    }
    tha->tail = (void*)((((uintptr_t)tha->tail & mask) - size) & mask);
    return tha->tail;
}

/**
 * Allocates to the tail end of the Two Head Arena with guaranteed 16-byte alignment.
 */
void* THA_alloc16(TwoHeadArena* tha, size_t size) {
    uintptr_t mask = ALIGN_MASK(0x10);

    tha->tail = (void*)((((uintptr_t)tha->tail & mask) - size) & mask);
    return tha->tail;
}

/**
 * Allocates to the tail end of the Two Head Arena using the provided mask to align the allocated region.
 *
 * @param tha   Arena to allocate to
 * @param size  Size of the allocation
 * @param mask  Mask to use to align the allocated region. To align to n-bytes where n is a power of 2, use the
 *              ALIGN_MASK(n) macro
 *
 * @return Pointer to the start of the allocated block
 */
void* THA_allocAlign(TwoHeadArena* tha, size_t size, uintptr_t mask) {
    tha->tail = (void*)((((uintptr_t)tha->tail & mask) - size) & mask);
    return tha->tail;
}

/**
 * Gets the remaining size of the Two Head Arena
 *
 * @return Remaining size. A negative number indicates an overflow.
 */
s32 THA_getFreeBytes(TwoHeadArena* tha) {
    return (s32)((u8*)tha->tail - (u8*)tha->head);
}

/**
 * @return true if the Two Head Arena has overflowed, false otherwise
 */
u32 THA_isCrash(TwoHeadArena* tha) {
    return THA_getFreeBytes(tha) < 0;
}

void THA_init(TwoHeadArena* tha) {
    tha->head = tha->start;
    tha->tail = (u8*)tha->start + tha->size;
}

/**
 * Creates a new Two Head Arena at `start` with available size `size`
 */
void THA_ct(TwoHeadArena* tha, void* start, size_t size) {
    tha->start = start;
    tha->size = size;
    THA_init(tha);
}

/**
 * Destroys the Two Head Arena, no further allocations are possible
 */
void THA_dt(TwoHeadArena* tha) {
    bzero(tha, sizeof(TwoHeadArena));
}
