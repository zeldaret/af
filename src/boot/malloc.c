#include "malloc.h"
#include "osmalloc.h"

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/malloc/malloc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/malloc/malloc_r.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/malloc/realloc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/malloc/free.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/malloc/calloc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/malloc/DisplayArena.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/malloc/GetFreeArena.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/malloc/MallocInit.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/malloc/MallocCleanup.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/boot/malloc/MallocIsInitialized.s")
