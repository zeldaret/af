#ifndef SAVE_MENU_H
#define SAVE_MENU_H

#include "ultra64.h"
#include "game.h"
#include "unk.h"

typedef struct Game_SaveMenu {
    /* 0x00 */ Game state;
    /* 0xE0 */ UNK_TYPE1 unk_00[0x230-0xE0];
} Game_SaveMenu; // size = 0x230

void save_menu_init(Game *thisx);
void save_menu_cleanup(Game *thisx);

#endif
