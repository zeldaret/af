#ifndef PRENMI_H
#define PRENMI_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct PrenmiState {
    /* 0x00 */ GameState state;
    /* 0xA4 */ UNK_TYPE1 unk_00[0xE8-0xA4];
} PrenmiState; // size = 0xE8

void prenmi_init(GameState *thisx);
void prenmi_cleanup(GameState *thisx);

#endif
