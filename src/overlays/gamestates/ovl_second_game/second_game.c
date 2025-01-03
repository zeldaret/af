#include "second_game.h"
#include "libc/stdbool.h"
#include "overlays/gamestates/ovl_trademark/m_trademark.h"
#include "overlays/gamestates/ovl_cpedit/m_cpedit.h"
#include "69CB30.h"
#include "m_common_data.h"
#include "padmgr.h"
#include "sys_math.h"
#include "attributes.h"

void second_game_main(Game* game) {
    PakInfo* info = mCPk_get_pkinfo();
    s32 mempak;
    Game_SecondGame* secondGame = (Game_SecondGame*)game;

    if (mCPk_PakOpen(info, 0) == 0) {
        if (info->unk_70 == 1 || info->unk_70 == 11) {
            mempak = 0;
        } else {
            mempak = 1;
        }
    } else {
        mempak = 1;
    }

    if ((chkButton(START_BUTTON) != 0) && (mempak != 0)) {
        STOP_GAMESTATE(&secondGame->state);
        SET_NEXT_GAMESTATE(&secondGame->state, cpedit_init, sizeof(Game_CPEdit));
    } else {
        STOP_GAMESTATE(&secondGame->state);
        SET_NEXT_GAMESTATE(&secondGame->state, trademark_init, sizeof(Game_Trademark));
    }

    secondGame->state.unk_9E = true;
}

void second_game_cleanup(UNUSED Game* game) {
}

void second_game_init(Game* game) {
    game->main = second_game_main;
    game->destroy = second_game_cleanup;
    init_rnd();
    common_data.unk_10AB0 = padmgr_isConnectedAnyPak(0) != 0;
}
