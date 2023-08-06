#ifndef OVLMGR_H
#define OVLMGR_H

#include "ultra64.h"
#include "unk.h"

struct OverlayRelocationSection;

void ovlmgr_LoadImpl(void* vromStart, UNK_TYPE arg1, void* vramStart, void* vramEnd, void* allocatedRamAddr, struct OverlayRelocationSection* ovl, size_t size);
void ovlmgr_Load(void* vromStart, UNK_TYPE arg1, void* vramStart, void* vramEnd, void* allocatedRamAddr);


#endif
