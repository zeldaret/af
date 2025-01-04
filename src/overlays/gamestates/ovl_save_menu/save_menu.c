#include "save_menu.h"
#include "overlays/gamestates/ovl_trademark/m_trademark.h"
#include "gfx.h"
#include "m_view.h"
#include "m_common_data.h"
#include "macros.h"
#include "m_flashrom.h"
#include "m_cpk.h"
#include "6B3DC0.h"
#include "m_rcp.h"
#include "sys_matrix.h"

void save_menu_set_cursor_col(Game_SaveMenu* saveMenu) {
    s32 cursor_col[10][3] = {
        { 192, 120, 120 }, { 224, 130, 130 }, { 240, 150, 150 }, { 255, 180, 180 }, { 240, 150, 150 },
        { 224, 130, 130 }, { 192, 120, 120 }, { 128, 80, 80 },   { 64, 64, 64 },    { 128, 80, 80 },
    };
    s32 dstIndex;
    s32* dst;
    u32 colorIndex;
    s32 i;

    dstIndex = saveMenu->mode;
    dst = saveMenu->cursorColumn[dstIndex];
    colorIndex = saveMenu->frame / 4;

    for (i = 0; i < 3; i++) {
        dst[i] = cursor_col[colorIndex][i];
    }
}

void save_menu_reset_cursor_col(s32 (*color)[3]) {
    s32 default_color[3] = { 40, 40, 40 };
    s32 i;

    for (i = 0; i < 3; i++) {
        (*color)[i] = default_color[i];
    }
}

typedef void (*SaveMenuProc)(Game_SaveMenu*);

void save_menu_data_save_from(Game_SaveMenu* saveMenu) {
    u8 playerNo = common_data.playerNumber;
    if ((playerNo) != 4) {
        common_data.privateInfo->exists = TRUE;
        if (func_8008F7C8_jp() != -1) {
            saveMenu->error = SAVE_ERROR_EXIT; // OK
        } else {
            saveMenu->error = SAVE_ERROR_FLASHROM;
        }
    } else {
        saveMenu->error = SAVE_ERROR_FLASHROM; // Player is foriegner
    }
}

void save_menu_data_save_pak(Game_SaveMenu* saveMenu) {
    PrivateInfo* private = common_data.privateInfo;
    AnmPersonalID_c* foreignId;
    u8 playerNo = common_data.playerNumber;
    if (playerNo == 4) {
        foreignId = mNpc_GetOtherAnimalPersonalID(NULL, 0);
        if (foreignId != NULL) {
            mNpc_CopyAnimalPersonalID(&private->storedAnmId, foreignId);
        }
    }

    mCPk_PakOpen(mCPk_get_pkinfo(), 0);
    if (mCPk_SavePak(common_data.save.saveFilePrivateInfo, common_data.save.animals, mCPk_get_pkinfo()) == TRUE) {
        if (mLd_PlayerManKindCheck() == FALSE) {
            common_data.privateInfo->exists = FALSE;
        }
        if (func_8008F7C8_jp() != -1) {
            saveMenu->error = SAVE_ERROR_EXIT; // OK
        } else {
            saveMenu->error = SAVE_ERROR_FLASHROM;
            { UNUSED s32 scopedTemp; }
        }
    } else {
        saveMenu->error = SAVE_ERROR_CPAK; // Failed to save to CPak
    }
}
void save_menu_move_do_save(Game_SaveMenu* saveMenu) {
    static SaveMenuProc save_proc[2] = { &save_menu_data_save_from, &save_menu_data_save_pak };

    s32 mode = saveMenu->mode;

    if (chkTrigger(A_BUTTON)) {
        save_proc[mode](saveMenu);
    }

    if (chkTrigger(R_TRIG) || chkTrigger(U_JPAD) || chkTrigger(D_JPAD)) {
        saveMenu->frame = 0;
        save_menu_reset_cursor_col(saveMenu->cursorColumn + mode);
        saveMenu->mode++;

        if (saveMenu->mode >= 2) {
            saveMenu->mode = 0;
        }
    }

    if (chkTrigger(B_BUTTON)) {
        saveMenu->error = SAVE_ERROR_EXIT; // OK
    }
}

void save_menu_move_finish(Game_SaveMenu* save) {
    STOP_GAMESTATE((Game*)save);
    SET_NEXT_GAMESTATE((Game*)save, trademark_init, sizeof(Game_Trademark));
}

void save_menu_move_err(Game_SaveMenu* saveMenu) {
    saveMenu->error = SAVE_ERROR_NONE; // cleared
}

void save_menu_move_main(Game_SaveMenu* saveMenu) {
    static SaveMenuProc sub_proc[] = { &save_menu_move_do_save, &save_menu_move_err, &save_menu_move_err,
                                       &save_menu_move_finish };

    s32 error = saveMenu->error;

    if (error >= SAVE_ERROR_NONE && error < SAVE_ERROR_MAX) {
        sub_proc[error](saveMenu);
    }

    save_menu_set_cursor_col(saveMenu);
    saveMenu->frame++;

    if (saveMenu->frame == 40) {
        saveMenu->frame = 0;
    }
}

void save_menu_draw_title(Game_SaveMenu* saveMenu) {
    UNUSED s32 pad;
    char title[] = { 0x9E, 0x90, 0xDF, 0x20, 0xB2, 0xA6, 0x8D, 0x90 };

    mFont_SetMatrix(saveMenu->game.gfxCtx, 1);
    mFont_SetLineStrings_AndSpace((Game*)saveMenu, title, ARRAY_COUNT(title) * sizeof(char), 110.0f, 30.0f, 200, 50, 50,
                                  255, FALSE, TRUE, FALSE, 1.1f, 1.1f, 1);
    mFont_UnSetMatrix(saveMenu->game.gfxCtx, 1);
}

void save_menu_draw_push_a(Game_SaveMenu* saveMenu) {
    UNUSED s32 pad;
    char push_a[] = { 0x50, 0x75, 0x73, 0x68, 0x20, 0x41, 0x20, 0x42, 0x75, 0x74, 0x74, 0x6F, 0x6E };

    mFont_SetMatrix(saveMenu->game.gfxCtx, 1);
    mFont_SetLineStrings_AndSpace((Game*)saveMenu, push_a, ARRAY_COUNT(push_a) * sizeof(char), 95.0f, 175.0f, 200, 200,
                                  200, 255, FALSE, TRUE, FALSE, 0.8f, 0.8f, 1);
    mFont_UnSetMatrix(saveMenu->game.gfxCtx, 1);
}

void save_menu_draw_select_r(Game_SaveMenu* saveMenu) {
    UNUSED s32 pad;
    char select_r[0xF] = { 0x53, 0x65, 0x6C, 0x65, 0x63, 0x74, 0x20, 0x52, 0x20, 0x42, 0x75, 0x74, 0x74, 0x6F, 0x6E };

    mFont_SetMatrix(saveMenu->game.gfxCtx, 1);
    mFont_SetLineStrings_AndSpace((Game*)saveMenu, select_r, ARRAY_COUNT(select_r), 76.0f, 185.0f, 200, 200, 200, 255,
                                  FALSE, TRUE, FALSE, 0.8f, 0.8f, 1);
    mFont_UnSetMatrix(saveMenu->game.gfxCtx, 1);
}

void save_menu_draw_push_b(Game_SaveMenu* saveMenu) {
    UNUSED s32 pad;
    char push_b[] = { 0x50, 0x75, 0x73, 0x68, 0x20, 0x42, 0x20, 0x42, 0x75, 0x74, 0x74,
                      0x6F, 0x6E, 0x20, 0x74, 0x6F, 0x20, 0x45, 0x58, 0x49, 0x54 };

    mFont_SetMatrix(saveMenu->game.gfxCtx, 1);
    mFont_SetLineStrings_AndSpace((Game*)saveMenu, push_b, ARRAY_COUNT(push_b) * sizeof(char), 50.0f, 210.0f, 200, 200,
                                  200, 255, FALSE, TRUE, FALSE, 0.8f, 0.8f, 1);
    mFont_UnSetMatrix(saveMenu->game.gfxCtx, 1);
}

void save_menu_draw_select_mode(Game_SaveMenu* saveMenu) {
    UNUSED s32 pad;
    char select_mode[2][13] = {
        { 0x46, 0x6C, 0x61, 0x73, 0x68, 0x52, 0x6F, 0x6D, 0x20, 0x15, 0x9E, 0x90, 0xDF },
        { 0xE2, 0x8F, 0x98, 0x20, 0x15, 0x9E, 0x90, 0xDF, 0x20, 0x20, 0x20, 0x20, 0x20 },
    };

    mFont_SetMatrix(saveMenu->game.gfxCtx, 1);
    mFont_SetLineStrings_AndSpace(
        (Game*)saveMenu, select_mode[SAVE_MODE_FLASHROM], ARRAY_COUNT(select_mode[SAVE_MODE_FLASHROM]) * sizeof(char),
        60.0f, 85.0f, saveMenu->cursorColumn[SAVE_MODE_FLASHROM][0], saveMenu->cursorColumn[SAVE_MODE_FLASHROM][1],
        saveMenu->cursorColumn[SAVE_MODE_FLASHROM][2], 255, FALSE, TRUE, FALSE, 1.2f, 1.2f, 1);
    mFont_UnSetMatrix(saveMenu->game.gfxCtx, 1);

    mFont_SetMatrix(saveMenu->game.gfxCtx, 1);
    mFont_SetLineStrings_AndSpace((Game*)saveMenu, select_mode[SAVE_MODE_CPAK],
                                  ARRAY_COUNT(select_mode[SAVE_MODE_CPAK]), 100.0f, 125.0f,
                                  saveMenu->cursorColumn[SAVE_MODE_CPAK][0], saveMenu->cursorColumn[SAVE_MODE_CPAK][1],
                                  saveMenu->cursorColumn[SAVE_MODE_CPAK][2], 255, FALSE, TRUE, FALSE, 1.2f, 1.2f, 1);
    mFont_UnSetMatrix(saveMenu->game.gfxCtx, 1);
}

void save_menu_draw_main(Game_SaveMenu* saveMenu) {
    GraphicsContext* g = saveMenu->game.gfxCtx;

    OPEN_DISPS(g);

    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_0, 0);
    DisplayList_initialize(g, 0, 0, 0, NULL);
    gDPPipeSync(POLY_OPA_DISP++);

    CLOSE_DISPS(g);

    showView(&saveMenu->view, 15);
    save_menu_draw_title(saveMenu);
    save_menu_draw_push_a(saveMenu);
    save_menu_draw_select_r(saveMenu);
    save_menu_draw_push_b(saveMenu);
    save_menu_draw_select_mode(saveMenu);
}

void save_menu_main(Game* game) {
    Game_SaveMenu* saveMenu = (Game_SaveMenu*)game;
    GraphicsContext* g;

    save_menu_move_main(saveMenu);
    save_menu_draw_main(saveMenu);

    g = game->gfxCtx;
    game_debug_draw_last(game, g);
    game_draw_last(g);
}

void save_menu_cleanup(UNUSED Game* game) {
}

void save_menu_init(Game* game) {
    GraphicsContext* g = game->gfxCtx;
    View* view;
    Game_SaveMenu* saveMenu = (Game_SaveMenu*)game;
    int i;

    game->main = &save_menu_main;
    game->destroy = &save_menu_cleanup;

    view = &saveMenu->view;
    initView(view, g);
    view->flag = 8;
    new_Matrix(game);
    SetGameFrame(1);

    saveMenu->frame = 0;
    saveMenu->mode = SAVE_MODE_START;
    saveMenu->error = SAVE_ERROR_NONE;

    for (i = 0; i < SAVE_MODE_MAX; i++) {
        save_menu_reset_cursor_col(saveMenu->cursorColumn + i);
    }
}
