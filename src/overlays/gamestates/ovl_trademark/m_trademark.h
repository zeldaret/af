#ifndef TRADEMARK_H
#define TRADEMARK_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct TrademarkState {
    /* 0x00 */ GameState state;
    /* 0xA4 */ UNK_TYPE1 unk_00[0x25A78-0xA4];
} TrademarkState; // size = 0x25A78

void trademark_init(GameState *thisx);
void trademark_cleanup(GameState *thisx);

#endif
