#ifndef SECOND_GAME_H
#define SECOND_GAME_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct SecondGameState {
    /* 0x00 */ GameState state;
} SecondGameState; // size = 0xE0

void second_game_init(GameState *thisx);
void second_game_cleanup(GameState *thisx);

#endif
