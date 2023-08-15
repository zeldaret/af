#ifndef FIRST_GAME_H
#define FIRST_GAME_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct FirstGameState {
    /* 0x00 */ GameState state;
} FirstGameState; // size = 0xE0

void first_game_init(GameState *thisx);
void first_game_cleanup(GameState *thisx);

#endif
