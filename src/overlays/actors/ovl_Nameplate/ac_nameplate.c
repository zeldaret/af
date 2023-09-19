#include "ac_nameplate.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_field_info.h"
#include "m_player_lib.h"
#include "m_npc.h"
#include "m_msg_main.h"
#include "69E2C0.h"
#include "overlays/actors/player_actor/m_player.h"

void aNP_actor_ct(Actor* thisx, Game_Play* game_play);
void aNP_actor_dt(Actor* thisx, Game_Play* game_play);
void aNP_set_talk_info(Actor* thisx);
void aNP_actor_move(Actor* thisx, Game_Play* game_play);
void aNP_actor_init(Actor* thisx, Game_Play* game_play);

ActorProfile Nameplate_Profile = {
    /* */ ACTOR_NAMEPLATE,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0xA012,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Nameplate),
    /* */ aNP_actor_ct,
    /* */ aNP_actor_dt,
    /* */ aNP_actor_init,
    /* */ NULL,
    /* */ NULL,
};

void aNP_actor_ct(Actor* thisx, Game_Play* game_play) {
}

void aNP_actor_dt(Actor* thisx, Game_Play* game_play) {
}

void aNP_set_talk_info(Actor* thisx) {
    Color_RGBA8 color;
    s32 pad; // TODO: find out what this pad is/if it's part of sp1C
    s32 sp1C;

    mNpc_GetAnimalPlateName(&sp1C, thisx->world.pos);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), 0, &sp1C, 6);
    mDemo_Set_msg_num(0x1369);
    mDemo_Set_talk_display_name(0);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(1);
    mPlib_Set_able_hand_all_item_in_demo(1);
    color.r = 205;
    color.g = 120;
    color.b = 0;
    color.a = 255;
    mDemo_Set_talk_window_color(&color);
}

void aNP_actor_move(Actor* thisx, Game_Play* game_play) {
    Player* temp_v0;
    s16 temp_v0_2;
    s32 var_v1;

    if (mDemo_Check(7, thisx) == 0) {
        temp_v0 = get_player_actor_withoutCheck(game_play);
        if ((temp_v0 != NULL) && (thisx->world.pos.z <= temp_v0->actor.world.pos.z)) {
            temp_v0_2 = thisx->yawTowardsPlayer;
            var_v1 = (temp_v0_2 >= 0) ? temp_v0_2 : -temp_v0_2;
            if (var_v1 < 0x2000) {
                mDemo_Request(7, thisx, aNP_set_talk_info);
            }
        }
    }
}

void aNP_actor_init(Actor* thisx, Game_Play* game_play) {
    mFI_SetFG_common(0xF0EE, thisx->home.pos, 0);
    aNP_actor_move(thisx, game_play);
    thisx->update = aNP_actor_move;
}
