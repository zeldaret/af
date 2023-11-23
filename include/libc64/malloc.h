#ifndef LIBC64_MALLOC_H
#define LIBC64_MALLOC_H

#include "ultra64.h"

struct Arena;

void* malloc(size_t size);
void* malloc_r(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);
void* calloc(size_t num, size_t size);
void GetFreeArena(size_t* outMaxFree, size_t* outFree, size_t* outAlloc);
s32 CheckArena(void);
void MallocInit(void* heap, size_t size);
void MallocCleanup(void);
s32 MallocIsInitialized(void);

extern struct Arena malloc_arena;

#endif
