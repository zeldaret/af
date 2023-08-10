#ifndef M_MALLOC_H
#define M_MALLOC_H

#include "ultra64.h"

// void zelda_malloc();
void* zelda_malloc_r(size_t size);
// void zelda_realloc();
void* zelda_free(void* ptr);
// void zelda_calloc();
// void zelda_GetFreeArena();
// void zelda_CheckArena();
// void zelda_InitArena();
// void zelda_CleanupArena();
s32 zelda_MallocIsInitalized(void);

#endif
