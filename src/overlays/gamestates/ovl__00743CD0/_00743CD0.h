#ifndef _00743CD0_H
#define _00743CD0_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct Game_00743CD0 {
    /* 0x00 */ Game state;
    /* 0xE0 */ UNK_TYPE1 unk_00[0x1B20-0xE0];
} Game_00743CD0; // size = 0x1B20

void _00743CD0_init(Game *thisx);
void _00743CD0_cleanup(Game *thisx);

#endif
