#ifndef FAMICOM_EMU_H
#define FAMICOM_EMU_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct FamicomEmuState {
    /* 0x00 */ GameState state;
    /* 0xA4 */ UNK_TYPE1 unk_00[0x3C];
} FamicomEmuState; // size = 0xE0

void famicom_emu_init(GameState *thisx);

#endif
