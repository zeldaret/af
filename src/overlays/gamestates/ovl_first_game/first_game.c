#include "first_game.h"
#include "m_common_data.h"
#include "67E840.h"
#include "attributes.h"
#include "overlays/gamestates/ovl_second_game/second_game.h"

void func_808029D0_jp(Game_FirstGame* this);
void func_80802A60_jp(void);

void func_808029D0_jp(Game_FirstGame* this) {
    func_80802A60_jp();
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
    func_808029D0_jp(this);
}
