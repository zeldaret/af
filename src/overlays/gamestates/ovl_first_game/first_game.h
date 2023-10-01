#ifndef FIRST_GAME_H
#define FIRST_GAME_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct Game_FirstGame {
    /* 0x00 */ Game state;
} Game_FirstGame; // size = 0xE0

void first_game_init(Game *thisx);
void first_game_cleanup(Game *thisx);

#endif
