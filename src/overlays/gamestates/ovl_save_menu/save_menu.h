#ifndef SAVE_MENU_H
#define SAVE_MENU_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct SaveMenuState {
    /* 0x00 */ GameState state;
    /* 0xA4 */ UNK_TYPE1 unk_00[0x230-0xA4];
} SaveMenuState; // size = 0x230

void save_menu_init(GameState *thisx);
void save_menu_cleanup(GameState *thisx);

#endif
