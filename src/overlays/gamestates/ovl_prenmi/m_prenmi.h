#ifndef PRENMI_H
#define PRENMI_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct Game_Prenmi {
    /* 0x00 */ Game state;
    /* 0xE0 */ s32 timer;
    /* 0xE4 */ UNK_TYPE unk_E4;
} Game_Prenmi; // size = 0xE8

void prenmi_init(Game* game);
void prenmi_cleanup(Game* thisx);

#endif
