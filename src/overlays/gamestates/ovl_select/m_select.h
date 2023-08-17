#ifndef SELECT_H
#define SELECT_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct MapSelectState {
    /* 0x00 */ Game state;
    /* 0xE0 */ UNK_TYPE1 unk_00[0x240-0xE0];
} MapSelectState; // size = 0x240

void select_init(Game *thisx);
void select_cleanup(Game *thisx);

#endif
