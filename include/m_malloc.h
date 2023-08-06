#ifndef M_MALLOC_H
#define M_MALLOC_H

#include "ultra64.h"

void *zelda_malloc(size_t size);
void* zelda_malloc_r(size_t size);
void *zelda_realloc(void* ptr, size_t size);
void zelda_free(void* ptr);
void* zelda_calloc(s32 num, size_t size);
void zelda_GetFreeArena(size_t *outMaxFree, size_t *outFree, size_t *outAlloc);
s32 zelda_CheckArena(void);
void zelda_InitArena(void* heap, size_t size);
void zelda_CleanupArena(void);
s32 zelda_MallocIsInitalized(void);

#endif
