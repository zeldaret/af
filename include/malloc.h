#ifndef MALLOC_H
#define MALLOC_H

#include "ultra64.h"

void* malloc(size_t size);
void* malloc_r(size_t size);
// void realloc();
void free(void* ptr);
// void calloc();
// void DisplayArena();
// void GetFreeArena();
// void MallocInit();
// void MallocCleanup();
// void MallocIsInitialized();

#endif
