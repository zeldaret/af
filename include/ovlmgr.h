#ifndef OVLMGR_H
#define OVLMGR_H

#include "ultra64.h"
#include "other_types.h"
#include "unk.h"

struct OverlayRelocationSection;

void ovlmgr_LoadImpl(RomOffset vromStart, RomOffset vromEndUnused, void* vramStart, void* vramEnd, void* allocatedRamAddr, struct OverlayRelocationSection* ovl, size_t size);
void ovlmgr_Load(RomOffset vromStart, RomOffset vromEnd, void* vramStart, void* vramEnd, void* allocatedRamAddr);


#endif
