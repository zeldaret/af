#ifndef YAZ0_H
#define YAZ0_H

#include "ultra64.h"
#include "other_types.h"

// void Yaz0_FirstDMA();
// void Yaz0_NextDMA();
// void Yaz0_DecompressImpl();
void Yaz0_Decompress(RomOffset vrom, void* dst, size_t size);

#endif
