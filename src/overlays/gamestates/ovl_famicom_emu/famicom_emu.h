#ifndef FAMICOM_EMU_H
#define FAMICOM_EMU_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct Game_FamicomEmu {
    /* 0x00 */ Game state;
} Game_FamicomEmu; // size = 0xE0

void famicom_emu_init(Game *thisx);
void famicom_emu_cleanup(Game *thisx);

#endif
