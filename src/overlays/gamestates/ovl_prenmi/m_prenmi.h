#ifndef PRENMI_H
#define PRENMI_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct Game_Prenmi {
    /* 0x00 */ Game state;
    /* 0xE0 */ UNK_TYPE1 unk00[0xE8 - 0xE0];
} Game_Prenmi; // size = 0xE8

void prenmi_init(Game *thisx);
void prenmi_cleanup(Game *thisx);

#endif
