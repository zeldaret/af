#ifndef M_PLAY_H
#define M_PLAY_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct PlayState {
    /* 0x00 */ GameState state;
    /* 0xA4 */ UNK_TYPE1 unk_00[0x236C];
} PlayState; // size = 0x2410

void play_init(GameState *thisx);

#endif
