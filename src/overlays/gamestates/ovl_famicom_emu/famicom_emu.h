#ifndef FAMICOM_EMU_H
#define FAMICOM_EMU_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct FamicomEmuState {
    /* 0x00 */ GameState state;
} FamicomEmuState; // size = 0xE0

void famicom_emu_init(GameState *thisx);
void famicom_emu_cleanup(GameState *thisx);

#endif
