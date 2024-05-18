#ifndef M_CPEDIT_H
#define M_CPEDIT_H

#include "ultra64.h"
#include "game.h"
#include "m_view.h"
#include "m_submenu.h"
#include "m_scene.h"

typedef struct Game_CPEdit Game_CPEdit;
typedef void (*Game_CPEdit_unk208)(Game_CPEdit* edit);

struct Game_CPEdit {
    /* 0x000 */ Game state;
    /* 0x0E0 */ View view;
    /* 0x208 */ Game_CPEdit_unk208 unk208;
    /* 0x20C */ Submenu submenu;
    /* 0x2FC */ ObjectExchangeBank bank;
}; // size = 0x1B20

void cpedit_init(Game *thisx);
void cpedit_cleanup(Game *thisx);

#endif
