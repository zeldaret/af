#include "m_malloc.h"
#include "libc64/osmalloc.h"
#include "fault.h"

Arena zelda_arena;
FaultClient B_80141FC8_jp;

void* zelda_malloc(size_t size) {
    return __osMalloc(&zelda_arena, size);
}

void* zelda_malloc_r(size_t size) {
    return __osMallocR(&zelda_arena, size);
}

void* zelda_realloc(void* ptr, size_t size) {
    __osRealloc(&zelda_arena, ptr, size);
}

void zelda_free(void* ptr) {
    __osFree(&zelda_arena, ptr);
}

void* zelda_calloc(s32 num, size_t size) {
    void* ptr;
    u32 n = num * size;

    ptr = __osMalloc(&zelda_arena, n);
    if (ptr != NULL) {
        bzero(ptr, n);
    }
    return ptr;
}

void zelda_GetFreeArena(size_t* outMaxFree, size_t* outFree, size_t* outAlloc) {
    __osGetFreeArena(&zelda_arena, outMaxFree, outFree, outAlloc);
}

s32 zelda_CheckArena(void) {
    return __osCheckArena(&zelda_arena);
}

void zelda_InitArena(void* heap, size_t size) {
    __osMallocInit(&zelda_arena, heap, size);
    fault_AddClient(&B_80141FC8_jp, (void*)ArenaImpl_FaultClient, &zelda_arena, NULL);
}

void zelda_CleanupArena(void) {
    fault_RemoveClient(&B_80141FC8_jp);
    __osMallocCleanup(&zelda_arena);
}

s32 zelda_MallocIsInitalized(void) {
    return __osMallocIsInitalized(&zelda_arena);
}
