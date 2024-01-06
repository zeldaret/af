#include "libc64/malloc.h"
#include "libc64/osmalloc.h"

Arena malloc_arena;

void* malloc(size_t size) {
    return __osMalloc(&malloc_arena, size);
}

void* malloc_r(size_t size) {
    return __osMallocR(&malloc_arena, size);
}

void* realloc(void* ptr, size_t size) {
    return __osRealloc(&malloc_arena, ptr, size);
}

void free(void* ptr) {
    __osFree(&malloc_arena, ptr);
}

void* calloc(size_t num, size_t size) {
    void* ptr;
    u32 n = num * size;

    ptr = __osMalloc(&malloc_arena, n);
    if (ptr != NULL) {
        bzero(ptr, n);
    }
    return ptr;
}

void GetFreeArena(size_t* outMaxFree, size_t* outFree, size_t* outAlloc) {
    __osGetFreeArena(&malloc_arena, outMaxFree, outFree, outAlloc);
}

s32 CheckArena(void) {
    return __osCheckArena(&malloc_arena);
}

void MallocInit(void* heap, size_t size) {
    __osMallocInit(&malloc_arena, heap, size);
}

void MallocCleanup(void) {
    __osMallocCleanup(&malloc_arena);
}

s32 MallocIsInitialized(void) {
    return __osMallocIsInitalized(&malloc_arena);
}
