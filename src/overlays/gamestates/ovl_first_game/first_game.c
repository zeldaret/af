#include "first_game.h"
#include "m_common_data.h"
#include "67E840.h"
#include "attributes.h"
#include "boot_variables.h"
#include "overlays/gamestates/ovl_second_game/second_game.h"

void func_808029D0_jp(FirstGameState* this);
void func_80802A60_jp(void);

void func_808029D0_jp(FirstGameState* this) {
    func_80802A60_jp();
    mBGM_ct();
    common_data_init();

    STOP_GAMESTATE(&this->state);
    SET_NEXT_GAMESTATE(&this->state, second_game_init, sizeof(SecondGameState));
}

void first_game_cleanup(GameState* thisx UNUSED) {
}

void first_game_init(GameState* thisx) {
    FirstGameState* this = (FirstGameState*)thisx;

    thisx->destroy = first_game_cleanup;
    func_808029D0_jp(this);
}
