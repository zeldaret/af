#ifndef GFXALLOC_H
#define GFXALLOC_H

#include "ultra64.h"

Gfx* gfxopen(Gfx* gfxHead);
Gfx* gfxclose(Gfx* gfxHead, Gfx* gfx);
void* gfxalloc(Gfx** gfxP, size_t size);

#endif
