#include "player_select.h"
#include "attributes.h"
#include "m_field_info.h"
#include "m_start_data_init.h"
#include "m_common_data.h"
#include "overlays/gamestates/ovl_select/m_select.h"
#include "gfx.h"
#include "6B3DC0.h"
#include "macros.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "m_flashrom.h"

/* ' みとうろく' (Unregistered) */
char mitouroku_str[] = { 0x20, 0x1F, 0x13, 0x02, 0xC0, 0x07 };

/* '<がいしゅつちゅう>' (<Away>) */
char l_gaishutu_str[] = { 0x3C, 0xE7, 0x01, 0x0B, 0xCA, 0x11, 0x10, 0xCA, 0x02, 0x3E };

/* '<ざいたくちゅう>' (<Home>) */
char l_zaitaku_str[] = { 0x3C, 0xEC, 0x01, 0x0F, 0x07, 0x10, 0xCA, 0x02, 0x3E };

/* 'よそからあそびにきた' (Came from another place) */
char l_yosokara_str[] = { 0x60, 0x0E, 0x05, 0x7B, 0x00, 0x0E, 0xF7, 0x15, 0x06, 0x0F };

void player_select_game_data_init(Game_PlayerSelect* playerSelect) {
    UNUSED s32 pad;
    s32 playerNo = playerSelect->playerNo;

    mFI_ClearFieldData();
    if (mSDI_StartInitBefore(&playerSelect->game, playerNo, mSDI_INIT_MODE_NEW, mSDI_MALLOC_FLAG_GAME) == TRUE) {
        playerSelect->status = PLAYER_SELECT_STATUS_SUCCESSFUL;
    }
}

void player_select_game_data_init_save(Game_PlayerSelect* playerSelect) {
    if (mSDI_StartInitBefore(&playerSelect->game, playerSelect->playerNo, mSDI_INIT_MODE_FROM, mSDI_MALLOC_FLAG_GAME) ==
        TRUE) {
        playerSelect->status = PLAYER_SELECT_STATUS_SUCCESSFUL;
    } else {
        playerSelect->status = PLAYER_SELECT_STATUS_ERR_SAVE;
    }
}

void player_select_game_data_init_new_player(Game_PlayerSelect* playerSelect) {
    if (mSDI_StartInitBefore(&playerSelect->game, playerSelect->playerNo, mSDI_INIT_MODE_NEW_PLAYER,
                             mSDI_MALLOC_FLAG_GAME) == TRUE) {
        playerSelect->status = PLAYER_SELECT_STATUS_SUCCESSFUL;
    } else {
        playerSelect->status = PLAYER_SELECT_STATUS_ERR_SAVE;
    }
}

void player_select_game_data_init_pak(Game_PlayerSelect* playerSelect) {
    if (mSDI_StartInitBefore(&playerSelect->game, playerSelect->playerNo, mSDI_INIT_MODE_PAK, mSDI_MALLOC_FLAG_GAME) ==
        TRUE) {
        playerSelect->status = PLAYER_SELECT_STATUS_SUCCESSFUL;
    } else {
        playerSelect->status = PLAYER_SELECT_STATUS_ERR_PAK;
    }
}

void player_select_game_data_init_err(Game_PlayerSelect* playerSelect) {
    playerSelect->mode = 0;
}

PlayerSelectInitProc l_init_proc[] = {
    &player_select_game_data_init,     &player_select_game_data_init_new_player, &player_select_game_data_init_save,
    &player_select_game_data_init_pak, &player_select_game_data_init_err,
};

void player_select_init_after(Game_PlayerSelect* playerSelect) {
    mSDI_StartInitAfter(&playerSelect->game, FALSE, mSDI_MALLOC_FLAG_GAME);
}

void player_select_next_mode(s32* mode, s32 max) {
    (*mode)++;
    if (*mode >= max) {
        *mode = 0;
    }
}

void player_select_back_mode(s32* mode, s32 max) {
    (*mode)--;
    if (*mode < 0) {
        *mode = max - 1;
    }
}

void player_select_move_main(Game_PlayerSelect* playerSelect) {
    UNUSED s32 pad;
    UNUSED s32 pad2;
    s32 mode = playerSelect->mode;
    UNUSED s32 pad3;
    s32 playerNo;

    if (playerSelect->status == PLAYER_SELECT_STATUS_NONE) {
        if (chkTrigger(A_BUTTON)) {
            playerNo = playerSelect->playerNo;
            if (mode == PLAYER_SELECT_MODE_SELECTION) {
                playerSelect->mode = PLAYER_SELECT_MODE_PLAY;
            }

            if (playerSelect->mode == PLAYER_SELECT_MODE_PLAY) {
                (*playerSelect->initProcs[playerNo])(playerSelect);
            }
        }

        if (chkTrigger(D_JPAD) && playerSelect->mode == PLAYER_SELECT_MODE_SELECTION) {
            if (playerSelect->landExist == TRUE) {
                //! FAKE
                if (((!playerSelect->mode) && (!playerSelect->mode)) && (!playerSelect->mode)) {}
                player_select_next_mode(&playerSelect->playerNo, SELECT_PLAYER_NUM);
            } else {
                player_select_next_mode(&playerSelect->playerNo, PLAYER_NUM);
            }
        }

        if (chkTrigger(U_JPAD) && playerSelect->mode == PLAYER_SELECT_MODE_SELECTION) {
            if (playerSelect->landExist == TRUE) {
                //! FAKE
                if (((!playerSelect->mode) && (!playerSelect->mode)) && (!playerSelect->mode)) {}
                player_select_back_mode(&playerSelect->playerNo, SELECT_PLAYER_NUM);
            } else {
                player_select_back_mode(&playerSelect->playerNo, PLAYER_NUM);
            }
        }
    } else if (playerSelect->status == PLAYER_SELECT_STATUS_SUCCESSFUL) {
        player_select_init_after(playerSelect);
        STOP_GAMESTATE(&playerSelect->game);
        SET_NEXT_GAMESTATE(&playerSelect->game, &select_init, sizeof(Game_Select));
    } else {
        common_data.sceneFromTitleDemo = -1;
        playerSelect->status = PLAYER_SELECT_STATUS_NONE;
        playerSelect->mode = PLAYER_SELECT_MODE_SELECTION;
    }
}

void str_add_word(char* dst, const char* word0, const char* word1, s32 len1, s32 len2) {
    for (; len1 != 0; len1--) {
        *dst++ = *word0++;
    }

    for (; len2 != 0; len2--) {
        *dst++ = *word1++;
    }
}

s32 l_ps_white_color[3] = { 250, 220, 100 };
s32 l_ps_select_color[3] = { 200, 55, 55 };

/* not translated, プレーヤー せんたく, player selection */
char _debug_player_select[10] = {
    0xE4, 0xBA, 0x90, 0xB4, 0x90, 0x20, 0x0D, 0xC3, 0x0F, 0x07,
};

void player_select_draw_title(Game_PlayerSelect* playerSelect) {
    mFont_SetMatrix(playerSelect->game.gfxCtx, 1);
    mFont_SetLineStrings_AndSpace(&playerSelect->game, _debug_player_select,
                                  ARRAY_COUNT(_debug_player_select) * sizeof(char), 85.0f, 15.0f, 200, 200, 200, 255,
                                  FALSE, TRUE, 0, 1.2f, 1.2f, 1);
    mFont_UnSetMatrix(playerSelect->game.gfxCtx, 1);
}

void player_select_draw_player_no(Game_PlayerSelect* playerSelect) {
    UNUSED s32 pad;
    char preStr[8] = { 0xED, 0xCA, 0x02, 0x15, 0xC3, 0x20, 0x20, 0x20 };
    char buf[8 + SELECT_NAME_LEN];
    s32 playerNo = playerSelect->playerNo;
    s32 i;

    for (i = 0; i < PLAYER_NUM; i++) {
        s32* color;

        mem_clear((u8*)buf, ARRAY_COUNT(buf) * sizeof(char), ' ');
        str_add_word(buf, preStr, playerSelect->playerNames[i], 8, SELECT_NAME_LEN);

        buf[6] = (u8)i | 0x30;

        color = (playerNo == i) ? l_ps_select_color : l_ps_white_color;

        mFont_SetMatrix(playerSelect->game.gfxCtx, 1);
        mFont_SetLineStrings_AndSpace(&playerSelect->game, buf, ARRAY_COUNT(buf) * sizeof(char), 70.0f,
                                      65.0f + 15.0f * i, color[0], color[1], color[2], 255, FALSE, TRUE, 0, 0.8f, 0.8f,
                                      1);
        mFont_UnSetMatrix(playerSelect->game.gfxCtx, 1);
    }
}

void player_select_draw_yosokara(Game_PlayerSelect* playerSelect) {
    UNUSED s32 pad;
    s32 playerNo;
    char* name = playerSelect->playerNames[PLAYER_NUM];
    s32* color;

    playerNo = playerSelect->playerNo;
    if (playerNo == PLAYER_NUM) {
        color = l_ps_select_color;
    } else {
        color = l_ps_white_color;
    }

    mFont_SetMatrix(playerSelect->game.gfxCtx, 1);
    mFont_SetLineStrings_AndSpace(&playerSelect->game, name, SELECT_NAME_LEN, 70.0f, 65.0f + 15.0f * PLAYER_NUM,
                                  color[0], color[1], color[2], 255, FALSE, TRUE, 0, 0.8f, 0.8f, 1);
    mFont_UnSetMatrix(playerSelect->game.gfxCtx, 1);
}

void player_select_draw_main(Game_PlayerSelect* playerSelect) {
    GraphicsContext* graph = playerSelect->game.gfxCtx;

    if (1) {}
    if (1) {}
    if (1) {}
    OPEN_DISPS(graph);

    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_0, 0);
    gSPSegment(FONT_DISP++, G_MWO_SEGMENT_0, 0);

    DisplayList_initialize(graph, 0, 0, 0, NULL);

    gDPPipeSync(POLY_OPA_DISP++);

    CLOSE_DISPS(graph);

    showView(&playerSelect->view, 15);
    player_select_draw_title(playerSelect);
    player_select_draw_player_no(playerSelect);
    player_select_draw_yosokara(playerSelect);
}

void player_select_main(Game* game) {
    Game_PlayerSelect* playerSelect = (Game_PlayerSelect*)game;

    player_select_move_main(playerSelect);
    player_select_draw_main(playerSelect);

    {
        GraphicsContext* graph = game->gfxCtx;
        game_debug_draw_last(game, graph);
        game_draw_last(graph);
    }
}

void player_select_cleanup(UNUSED Game* game) {
}

void player_select_init(Game* game) {
    Game_PlayerSelect* playerSelect = (Game_PlayerSelect*)game;
    GraphicsContext* graph = game->gfxCtx;
    s32 j;
    s32 i;

    View* view = &playerSelect->view;
    game->main = &player_select_main;
    game->destroy = &player_select_cleanup;

    initView(view, graph);
    view->flag = 8;

    new_Matrix(game);
    SetGameFrame(1);

    playerSelect->playerNo = 0;
    playerSelect->status = PLAYER_SELECT_STATUS_NONE;
    playerSelect->mode = PLAYER_SELECT_MODE_SELECTION;

    for (i = 0; i < SELECT_PLAYER_NUM; i++) {
        for (j = 0; j < 6; j++) {
            playerSelect->playerNames[i][j] = mitouroku_str[j];
        }

        for (j = 6; j < SELECT_NAME_LEN; j++) {
            playerSelect->playerNames[i][j] = ' ';
        }

        playerSelect->playerTypes[i] = PLAYER_SELECT_PLAYER_MODE_NO_SAVE;
    }

    for (i = 0; i < LAND_NAME_SIZE; i++) {
        playerSelect->landName[i] = ' ';
    }
    playerSelect->landExist = FALSE;

    if (mFRm_CheckSaveData() == TRUE) {
        PrivateInfo* private = common_data.save.saveFilePrivateInfo;
        for (i = 0; i < PLAYER_NUM; i++, private ++) {
            char* name = playerSelect->playerNames[i];

            if (mPr_CheckPrivate(private) == TRUE) {
                mPr_CopyPlayerName(name, private->playerId.playerName);

                if (private->exists == FALSE) {
                    mem_copy((u8*)(name + PLAYER_NAME_LEN), (u8*)l_gaishutu_str, 10);
                    playerSelect->playerTypes[i] = PLAYER_SELECT_PLAYER_MODE_OUT;
                } else {
                    mem_copy((u8*)(name + PLAYER_NAME_LEN), (u8*)l_zaitaku_str, 9);
                    playerSelect->playerTypes[i] = PLAYER_SELECT_PLAYER_MODE_HOME;
                }
            } else {
                playerSelect->playerTypes[i] = PLAYER_SELECT_PLAYER_MODE_UNREGISTERED;
            }
        }

        mLd_CopyLandName(playerSelect->landName, common_data.save.landInfo.name);
        playerSelect->landExist = TRUE;
    }

    for (j = 0; j < SELECT_PLAYER_NAME_EXTRA; j++) {
        playerSelect->playerNames[PLAYER_NUM][j] = l_yosokara_str[j];
    }

    for (j = SELECT_PLAYER_NAME_EXTRA; j < SELECT_NAME_LEN; j++) {
        playerSelect->playerNames[PLAYER_NUM][j] = ' ';
    }

    playerSelect->playerTypes[PLAYER_NUM] = PLAYER_SELECT_PLAYER_MODE_OUT;

    for (i = 0; i < SELECT_PLAYER_NUM; i++) {
        u8 idx = playerSelect->playerTypes[i];
        playerSelect->initProcs[i] = l_init_proc[idx];
    }

    common_data.playerNumber = 0;
    common_data.playerDataMode = 0;
    common_data.sceneFromTitleDemo = -1;
}
