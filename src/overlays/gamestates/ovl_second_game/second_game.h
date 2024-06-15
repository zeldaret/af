#ifndef SECOND_GAME_H
#define SECOND_GAME_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct Game_SecondGame {
    /* 0x00 */ Game state;
} Game_SecondGame; // size = 0xE0

void second_game_init(Game* game);
void second_game_cleanup(Game *thisx);

#endif
