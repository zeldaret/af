#ifndef SAVE_MENU_H
#define SAVE_MENU_H

#include "game.h"
#include "m_view.h"

typedef struct Game_SaveMenu {
    /* 0x0000 */ Game game;
    /* 0x00E0 */ View view;
    /* 0x0200 */ u32 frame;
    /* 0x0204 */ s32 mode;
    /* 0x0208 */ s32 error;
    /* 0x020C */ s32 cursorColumn[2][3];
} Game_SaveMenu; // size = 0x224

typedef enum SaveMenuSaveError {
    /* 0 */ SAVE_ERROR_NONE,
    /* 1 */ SAVE_ERROR_FLASHROM,
    /* 2 */ SAVE_ERROR_CPAK,
    /* 3 */ SAVE_ERROR_EXIT,
    /* 4 */ SAVE_ERROR_MAX
} SaveMenuSaveError;

typedef enum SaveMenuSaveMode {
    /* 0 */ SAVE_MODE_START,
    /* 0 */ SAVE_MODE_FLASHROM = SAVE_MODE_START,
    /* 1 */ SAVE_MODE_CPAK,
    /* 2 */ SAVE_MODE_MAX
}SaveMenuSaveMode;

void save_menu_init(Game* game);
void save_menu_cleanup(Game *thisx);

#endif
