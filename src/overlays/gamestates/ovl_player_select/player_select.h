#ifndef PLAYER_SELECT_H
#define PLAYER_SELECT_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct PlayerSelectState {
    /* 0x00 */ Game state;
    /* 0xE0 */ UNK_TYPE1 unk_00[0x288-0xE0];
} PlayerSelectState; // size = 0x288

void player_select_init(Game *thisx);
void player_select_cleanup(Game *thisx);

#endif
