#ifndef TRADEMARK_H
#define TRADEMARK_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct TrademarkState {
    /* 0x00 */ Game state;
    /* 0xE0 */ UNK_TYPE1 unk_00[0x25A78-0xE0];
} TrademarkState; // size = 0x25A78

void trademark_init(Game *thisx);
void trademark_cleanup(Game *thisx);

#endif
