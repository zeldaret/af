#ifndef MALLOC_H
#define MALLOC_H

#include "ultra64.h"

void* malloc(size_t size);
void* malloc_r(size_t size);
// void realloc();
void free(void* ptr);
// void calloc();
void DisplayArena(size_t* maxFree, size_t* bytesFree, size_t* bytesAllocated);
// void GetFreeArena();
// void MallocInit();
// void MallocCleanup();
// void MallocIsInitialized();

#endif
