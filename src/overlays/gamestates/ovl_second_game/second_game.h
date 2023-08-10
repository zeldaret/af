#ifndef SECOND_GAME_H
#define SECOND_GAME_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct SecondGameState {
    /* 0x00 */ GameState state;
    /* 0xA4 */ UNK_TYPE1 unk_00[0xE0-0xA4];
} SecondGameState; // size = 0xE0

void second_game_init(GameState *thisx);
void second_game_cleanup(GameState *thisx);

#endif
