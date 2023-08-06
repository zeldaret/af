#include "malloc.h"
#include "osmalloc.h"

extern Arena B_800419C0_jp;

void* malloc(size_t size) {
    return __osMalloc(&B_800419C0_jp, size);
}

void* malloc_r(size_t size) {
    return __osMallocR(&B_800419C0_jp, size);
}

void* realloc(void* ptr, size_t size) {
    return __osRealloc(&B_800419C0_jp, ptr, size);
}

void free(void* ptr) {
    __osFree(&B_800419C0_jp, ptr);
}

void* calloc(s32 num, size_t size) {
    void* ptr;
    u32 n = num * size;

    ptr = __osMalloc(&B_800419C0_jp, n);
    if (ptr != NULL) {
        bzero(ptr, n);
    }
    return ptr;
}

void DisplayArena(size_t* outMaxFree, size_t* outFree, size_t* outAlloc) {
    __osGetFreeArena(&B_800419C0_jp, outMaxFree, outFree, outAlloc);
}

s32 GetFreeArena(void) {
    return __osCheckArena(&B_800419C0_jp);
}

void MallocInit(void* heap, size_t size) {
    __osMallocInit(&B_800419C0_jp, heap, size);
}

void MallocCleanup(void) {
    __osMallocCleanup(&B_800419C0_jp);
}

s32 MallocIsInitialized(void) {
    return __osMallocIsInitalized(&B_800419C0_jp);
}
