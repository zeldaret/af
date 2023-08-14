#ifndef M_PLAY_H
#define M_PLAY_H

#include "ultra64.h"
#include "game.h"

typedef struct PlayState {
    /* 0x0000 */ GameState state;
    /* 0x00A4 */ UNK_TYPE1 unk_00A4[0x1D6C];
    /* 0x1E10 */ u8 unk_1E10;
    /* 0x1E14 */ UNK_PTR unk_1E14;
} PlayState; // size = ??
#endif
