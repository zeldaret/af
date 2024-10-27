#include "first_game.h"
#include "m_common_data.h"
#include "m_bgm.h"
#include "attributes.h"
#include "overlays/gamestates/ovl_second_game/second_game.h"

void exit_game(Game_FirstGame* this);
void sys_romcheck(void);

void exit_game(Game_FirstGame* this) {
    sys_romcheck();
    mBGM_ct();
    common_data_init();

    STOP_GAMESTATE(&this->state);
    SET_NEXT_GAMESTATE(&this->state, second_game_init, sizeof(Game_SecondGame));
}

void first_game_cleanup(Game* thisx UNUSED) {
}

void first_game_init(Game* thisx) {
    Game_FirstGame* this = (Game_FirstGame*)thisx;

    thisx->destroy = first_game_cleanup;
    exit_game(this);
}
