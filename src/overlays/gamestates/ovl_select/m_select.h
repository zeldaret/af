#ifndef SELECT_H
#define SELECT_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct MapSelectState {
    /* 0x00 */ GameState state;
    /* 0xE0 */ UNK_TYPE1 unk_00[0x240-0xE0];
} MapSelectState; // size = 0x240

void select_init(GameState *thisx);
void select_cleanup(GameState *thisx);

#endif
