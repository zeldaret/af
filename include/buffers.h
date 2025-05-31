#ifndef BUFFERS_H
#define BUFFERS_H

#include "gfx.h"
#include "stack.h"

extern STACK(D_80153CC0_jp, 0x400);
extern STACK(D_801530C0_jp, 0xC00);
extern STACK(D_801524C0_jp, 0xC00);
extern GfxPool gGfxPools[2];

#endif
