#ifndef BOOT_FUNCTIONS_H
#define BOOT_FUNCTIONS_H

#include "ultra64.h"
#include "unknown_structs.h"

// void func_8002BFA0_jp();

// void func_8003B960_jp();
// void func_8003B9B0_jp();
// void func_8003B9E0_jp();
// void func_8003BA20_jp();
void* func_8003BA60_jp(void* dst, void* src, size_t size); // MM: __osMemcpy, gamecube refers to it as memmove
// void func_8003BAF0_jp();


#endif
