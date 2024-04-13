#ifndef M_DLF_H
#define M_DLF_H

#include "global.h"
#include "libc64/malloc.h"
#include "game.h"
#include "ovlmgr.h"

void Overlay_LoadGameState(GameStateOverlay* overlayEntry);
void Overlay_FreeGameState(GameStateOverlay* overlayEntry);

#endif
