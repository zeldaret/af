#ifndef GFXALLOC_H
#define GFXALLOC_H

#include "ultra64.h"

Gfx* gfxopen(Gfx* gfx);
Gfx* gfxclose(Gfx* gfx, Gfx* gfxNew);
void* gfxalloc(Gfx** gfxp, size_t size);

#endif
