#include "m_player.h"
#include "m_player_lib.h"
#include "game.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_room_type.h"
#include "audio.h"
#include "m_actor_dlftbls.h"
#include "m_field_info.h"
#include "m_name_table.h"
#include "m_scene_table.h"
#include "m_debug.h"
#include "m_demo.h"
#include "m_bgm.h"

extern ClObjPipe_Init Player_actor_OcInfoData_forStand;
#if 0
ClObjPipe_Init Player_actor_OcInfoData_forStand = { { OC1_1 | OC1_TYPE_8 | OC1_TYPE_10 | OC1_TYPE_20, OC2_TYPE_8, COLSHAPE_TRIS }, { ELEM_FLAG_1 }, { { 0x14, 0x3C, 0, { 0, 0, 0 } } } };
#endif

extern ClObjTrisElem_Init Player_actor_pclobj_tris_base_forItem[];
extern ClObjTris_Init Player_actor_pclobj_tris_data_forItem;
#if 0
ClObjTrisElem_Init Player_actor_pclobj_tris_base_forItem[] = {
    {
        { ELEM_FLAG_NONE },
        {
            {
                { { -70.0f, 176.0f, 0.0f }, { -70.0f, -4.0f, 0.0f }, { 0.0f, -4.0f, 30.0f } },
            },
        },
    },
};
ClObjTris_Init Player_actor_pclobj_tris_data_forItem = { { OC1_TYPE_10 | OC1_TYPE_20, OC2_2, COLSHAPE_TRIS }, ARRAY_COUNT(Player_actor_pclobj_tris_base_forItem), Player_actor_pclobj_tris_base_forItem };
#endif

s8 Player_actor_Get_ItemKind(Actor* actor, s32 kind);
void Player_actor_request_camera2_main_simple_fishing(Actor* actor, Game* game);
void Player_actor_request_camera2_main_simple_return(Actor* actor, Game* game);
void Player_actor_request_camera2_main_normal(Game* game);
void Player_actor_request_camera2_change_priority(Game* game);

void Player_actor_cancel_request_change_proc_index_by_A_btn(Actor* actor);
void Player_actor_request_main_change_from_submenu(Actor* actor, Game* game);
void Player_actor_request_change_item(Game* game);
void Player_actor_cancel_request_change_proc_index(Actor* actor);
void Player_actor_change_proc_index(Actor* actor, Game* game);
void Player_actor_Reset_excute_cancel_wade(Actor* actor);
void Player_actor_Set_OldAngle(Actor* actor);
void Player_actor_Culc_player_frame_counter(Actor* actor);

void Player_actor_set_eye_PositionAndAngle(Actor* actor);
void Player_actor_sound_SetStatus(Actor* actor);
void Player_actor_Set_Indoor_Camera_Index(Actor* actor, Game* game);
void Player_actor_check_forward(Actor* actor, Game* game);
void Player_actor_check_little_shake_tree(Actor* actor, Game* game);
void Player_actor_check_shake_tree_timer(Actor* actor);
void Player_actor_check_pitfall(Actor* actor, Game* game);
void Player_actor_set_ripple(Actor* actor, Game* game);

void Player_actor_SetPosition_OBJtoLine_forItem(Actor* actor, Game* game);
void Player_actor_SetFootMark_for_settle_main(Actor* actor, Game* game);
s32 Player_actor_CheckScene_AbleOutItem(s32 sceneNo);

// m_player_controller

s32 Player_actor_CheckController_forPickup(Game* game) {
    if (mEv_CheckTitleDemo() > 0) {
        PlayerControllerData* data = mPlib_Get_controller_data_for_title_demo_p();
        Actor* actor = (Actor*)get_player_actor_withoutCheck((Game_Play*)game);
        Player* player = (Player*)actor;
        s8 kind = Player_actor_Get_ItemKind(actor, player->nowMainIndex);

        return !Player_ITEM_IS_VALID(kind) && (data->triggerButtonA != 0) && (data->buttonB != 0);
    }

    return chkTrigger(B_BUTTON);
}

s32 Player_actor_CheckController_forAxe(Game* game) {
    Actor* actor = (Actor*)get_player_actor_withoutCheck((Game_Play*)game);
    Player* player = (Player*)actor;
    s8 kind = Player_actor_Get_ItemKind(actor, player->nowMainIndex);

    if (Player_ITEM_IS_AXE(kind)) {
        if (mEv_CheckTitleDemo() > 0) {
            return mPlib_Get_controller_data_for_title_demo_p()->triggerButtonA;
        }
        return chkTrigger(A_BUTTON);
    }

    return FALSE;
}

s32 Player_actor_CheckController_forNet(Game* game) {
    Actor* actor = (Actor*)get_player_actor_withoutCheck((Game_Play*)game);
    Player* player = (Player*)actor;
    s8 kind = Player_actor_Get_ItemKind(actor, player->nowMainIndex);

    if (Player_ITEM_IS_NET(kind)) {
        if (mEv_CheckTitleDemo() > 0) {
            return mPlib_Get_controller_data_for_title_demo_p()->buttonA;
        }
        return chkButton(A_BUTTON);
    }

    return FALSE;
}

s32 Player_actor_CheckController_forRod(Game* game) {
    Actor* actor = (Actor*)get_player_actor_withoutCheck((Game_Play*)game);
    Player* player = (Player*)actor;
    s8 kind = Player_actor_Get_ItemKind(actor, player->nowMainIndex);

    if (Player_ITEM_IS_ROD(kind)) {
        if (mEv_CheckTitleDemo() > 0) {
            return mPlib_Get_controller_data_for_title_demo_p()->triggerButtonA;
        }
        return chkTrigger(A_BUTTON);
    }

    return FALSE;
}

s32 Player_actor_CheckController_forScoop(Game* game) {
    Actor* actor = (Actor*)get_player_actor_withoutCheck((Game_Play*)game);
    Player* player = (Player*)actor;
    s8 kind = Player_actor_Get_ItemKind(actor, player->nowMainIndex);

    if (Player_ITEM_IS_SCOOP(kind)) {
        if (mEv_CheckTitleDemo() > 0) {
            return mPlib_Get_controller_data_for_title_demo_p()->triggerButtonA;
        }
        return chkTrigger(A_BUTTON);
    }

    return FALSE;
}

s32 Player_actor_CheckController_forUmbrella(Game* game) {
    Actor* actor = (Actor*)get_player_actor_withoutCheck((Game_Play*)game);
    Player* player = (Player*)actor;
    s8 kind = Player_actor_Get_ItemKind(actor, player->nowMainIndex);

    if (Player_ITEM_IS_UMBRELLA(kind) != FALSE) {
        if (mEv_CheckTitleDemo() > 0) {
            return mPlib_Get_controller_data_for_title_demo_p()->triggerButtonA;
        }
        return chkTrigger(A_BUTTON);
    }

    return FALSE;
}

int Player_actor_CheckController_forShake_tree(Game* game) {
    Actor* actor = (Actor*)get_player_actor_withoutCheck((Game_Play*)game);
    Player* player = (Player*)actor;
    s8 kind = Player_actor_Get_ItemKind(actor, player->nowMainIndex);

    if (!Player_ITEM_IS_VALID(kind) || Player_ITEM_IS_UMBRELLA(kind) != FALSE) {
        if (mEv_CheckTitleDemo() > 0) {
            PlayerControllerData* data = mPlib_Get_controller_data_for_title_demo_p();
            return (data->triggerButtonA != 0) && (data->buttonB == 0);
        } else {
            return chkTrigger(A_BUTTON);
        }
    }
    return FALSE;
}

f32 Player_actor_CheckController_forStruggle_pitfall() {
    if (chkTrigger(A_BUTTON) != 0) {
        return 1.0f;
    } else {
        return 0.0f;
    }
}

s32 Player_actor_CheckController_forDush() {
    if (mEv_CheckTitleDemo() > 0) {
        return mPlib_Get_controller_data_for_title_demo_p()->buttonB;
    } else {
        return chkButton(Z_TRIG);
    }
}

f32 Player_actor_GetController_move_percentX() {
    if (mEv_CheckTitleDemo() > 0) {
        PlayerControllerData* data = mPlib_Get_controller_data_for_title_demo_p();
        return data->controller.moveX;
    } else {
        return gamePT->controller.moveX;
    }
}

f32 Player_actor_GetController_move_percentY() {
    if (mEv_CheckTitleDemo() > 0) {
        PlayerControllerData* data = mPlib_Get_controller_data_for_title_demo_p();

        return data->controller.moveY;
    } else {
        return gamePT->controller.moveY;
    }
}

f32 Player_actor_GetController_move_percentR() {
    if (mEv_CheckTitleDemo() > 0) {
        PlayerControllerData* data = mPlib_Get_controller_data_for_title_demo_p();

        return data->controller.moveR;
    } else {
        return gamePT->controller.moveR;
    }
}

s16 Player_actor_GetController_move_angle() {
    if (mEv_CheckTitleDemo() > 0) {
        PlayerControllerData* data = mPlib_Get_controller_data_for_title_demo_p();

        return data->controller.moveAngle;
    } else {
        return gamePT->controller.moveAngle;
    }
}

s16 Player_actor_GetController_old_move_angle() {
    if (mEv_CheckTitleDemo() > 0) {
        PlayerControllerData* data = mPlib_Get_controller_data_for_title_demo_p();

        return data->controller.lastMoveAngle;
    } else {
        return gamePT->controller.lastMoveAngle;
    }
}

f32 Player_actor_GetController_recognize_percentR() {
    if (mEv_CheckTitleDemo() > 0) {
        PlayerControllerData* data = mPlib_Get_controller_data_for_title_demo_p();

        return data->controller.adjustedR;
    } else {
        return gamePT->controller.adjustedR;
    }
}

f32 Player_actor_GetController_old_recognize_percentR() {
    if (mEv_CheckTitleDemo() > 0) {
        PlayerControllerData* data = mPlib_Get_controller_data_for_title_demo_p();

        return data->controller.lastAdjustedR;
    } else {
        return gamePT->controller.lastAdjustedR;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3308_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3334_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3370_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B33B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B33EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3438_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B34C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B34E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3584_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B35C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B360C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B36E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B36F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B37D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B37F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3804_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3828_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B39D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3A44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3A84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3AE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3AF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3B08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3B3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3BD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3BF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3C74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3C94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3D28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3D7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B3E10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B400C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4428_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4660_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B468C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B46C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B47F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B482C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B488C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B48F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4924_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4A44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4B6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4C88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4CA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4D5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4DAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4DE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4E34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4EE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B4EF4_jp.s")

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_SetPosition_OBJtoLine_forItem.s")
// clang-format on

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5150_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_set_eye_PositionAndAngle.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B527C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5310_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5348_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5374_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B53A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B53F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5470_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B54B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B54FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5544_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5584_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B55E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5644_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5698_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B56C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5844_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B589C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B58D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B58E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B58F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5944_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B59C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5A10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5B38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_Set_OldAngle.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5C58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5C68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5D44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5DA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5DE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5E8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5F6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5FB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B5FFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B603C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B606C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B612C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B6138_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B61E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B6234_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B6258_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B6284_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B6310_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B6334_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B6360_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_CheckScene_AbleOutItem.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B63B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B63EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B6424_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B6458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B7CDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B7DD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B7E6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B7F10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8058_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8094_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B80D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8114_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B81B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8204_jp.s")

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_SetFootMark_for_settle_main.s")
// clang-format on

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B83B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B846C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B84DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B856C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8628_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8730_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8778_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B87C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B87FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8874_jp.s")

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_cancel_request_change_proc_index.s")
// clang-format on

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8928_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8948_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B89F8_jp.s")

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_cancel_request_change_proc_index_by_A_btn.s")
// clang-format on

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8B54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8B90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8C04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8C5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8CF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8DB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B8EA8_jp.s")

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_request_camera2_main_simple_fishing.s")
// clang-format on

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_request_camera2_main_simple_return.s")
// clang-format on

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_request_camera2_main_normal.s")
// clang-format on

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_request_camera2_change_priority.s")
// clang-format on

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B9028_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B90C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B91CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B9248_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B9288_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B937C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B93B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B93F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B9568_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B9594_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B95EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B9634_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B9698_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B96C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B96F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808B996C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BA0B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BA13C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BA1DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_check_little_shake_tree.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_check_shake_tree_timer.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BA7BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BA88C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BA94C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BAA18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BAAE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BAB34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_check_pitfall.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BADFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BAE38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_set_ripple.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB098_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB158_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB1DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB43C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB4D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB520_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB570_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB604_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB650_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_Culc_player_frame_counter.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_Reset_excute_cancel_wade.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB724_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB904_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BB98C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BBA0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BBB7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BBCA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BBD34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BBD80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BBDE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_Set_Indoor_Camera_Index.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BBF38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BBFA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BBFD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BC2D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BC308_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BC358_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BC3A0_jp.s")

// m_player_audio

void Player_actor_sound_SetStatus(Actor* actor) {
    Player* player = (Player*)actor;
    u8 status;
    f32 speed;
    f32 frameControlSpeed;

    status = player->nowMainIndex;
    frameControlSpeed = player->skeletonInfo0.frameControl.speed;
    speed = frameControlSpeed / 1.1999999f;

    switch (player->nowMainIndex) {
        case 42:
        case 74:
        case 8:
            status = Player_WALK;
            break;
        case 9:
            status = Player_RUN;
            break;
        case 10:
            status = Player_DASH;
            break;
        default:
            status = Player_WAIT;
            break;
    }

    if (speed > 1.0f) {
        speed = 1.0f;
    } else if (speed < 0.0f) {
        speed = 0.0f;
    }
    sAdo_PlayerStatusLevel(status, speed);
}

void Player_actor_set_sound_common1(xyz_t* pos, u16 id) {
    sAdo_OngenTrgStart(id, pos);
}

void Player_actor_set_sound_common2(Actor* actor, u16 id) {
    Player_actor_set_sound_common1(&actor->world.pos, id);
}

void Player_actor_sound_FootStep1(Actor* actor, u16 id) {
    sAdo_PlyWalkSe(id, &actor->world.pos);
}

void Player_actor_sound_FootStep2(Actor* actor) {
    s32 floorId;

    floorId = common_data.floorIdx;
    if (common_data.floorIdx >= 0) {
        if (common_data.floorIdx < 0x49) {
            sAdo_PlyWalkSeRoom(floorId, &actor->world.pos);
        }
    } else {
        Player_actor_sound_FootStep1(actor, sAdo_Get_WalkLabel(actor->colCheck.colResult.unk5));
    }
}

void Player_actor_sound_Tumble(Actor* actor) {
    Player_actor_set_sound_common2(actor, sAdo_Get_KokeruLabel(actor->colCheck.colResult.unk5));
}

void Player_actor_sound_AMI_FURI(Actor* actor) {
    Player* player = (Player*)actor;

    Player_actor_set_sound_common1(&player->netPos, 0x5A);
}

void Player_actor_sound_AMI_HIT(Actor* actor) {
    Player* player = (Player*)actor;

    Player_actor_set_sound_common1(&player->netPos, 0x5C);
}

void Player_actor_sound_AMI_GET(Actor* actor) {
    Player* player = (Player*)actor;

    Player_actor_set_sound_common1(&player->netPos, 0x5D);
}

void Player_actor_sound_GASAGOSO(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x69);
}

void Player_actor_sound_AXE_FURI(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x5A);
}

void Player_actor_sound_AXE_HIT(Actor* actor, Game* game) {
    Player* player = (Player*)actor;
    UNUSED s32 pad;
    UNUSED s32 pad2;
    xyz_t pos;

    if ((mPlib_get_player_actor_main_index((Game_Play*)game) == Player_INDEX_REFLECT_AXE) != FALSE) {

        pos.x = player->mainIndexData.reflectAxe.axeCommon.target.x;
        pos.z = player->mainIndexData.reflectAxe.axeCommon.target.z;
        pos.y = actor->world.pos.y + 20.0f;

        Player_actor_set_sound_common1(&pos, 0x41D);
    }
}

void Player_actor_sound_AXE_CUT(Actor* actor, Game* game) {
    Player* player = (Player*)actor;
    UNUSED s32 pad;
    UNUSED s32 pad2;
    xyz_t pos;

    if ((mPlib_get_player_actor_main_index((Game_Play*)game) == Player_INDEX_SWING_AXE) != FALSE) {

        pos.x = player->mainIndexData.swingAxe.axeCommon.target.x;
        pos.z = player->mainIndexData.swingAxe.axeCommon.target.z;
        pos.y = actor->world.pos.y + 20.0f;

        Player_actor_set_sound_common1(&pos, 0x41E);
    }
}

void Player_actor_sound_SIT(Actor* actor, Game* game) {
    if ((mPlib_get_player_actor_main_index((Game_Play*)game) == Player_INDEX_SITDOWN) != FALSE) {
        Player* player = (Player*)actor;
        s32 id = mRmTp_GetFtrActionSE(player->mainIndexData.sitdown.ftrIdx, mRmTp_CHAIR_ACTION_SIT);

        if (id >= 0) {
            Player_actor_set_sound_common2(actor, id);
        }
    }
}

void Player_actor_sound_STANDUP(Actor* actor, s32 ftrIdx) {
    s32 id = mRmTp_GetFtrActionSE(ftrIdx, mRmTp_CHAIR_ACTION_STAND);

    if (id >= 0) {
        Player_actor_set_sound_common2(actor, id);
    }
}

void Player_actor_sound_JUMP(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x42A);
}

void Player_actor_sound_LANDING(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x42B);
}

void Player_actor_sound_ITEM_GET(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x40);
}

void Player_actor_sound_BED_IN(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x415);
}

void Player_actor_sound_BED_NEGAERI(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x416);
}

void Player_actor_sound_BED_OUT(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x417);
}

void Player_actor_sound_ROD_STROKE(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x109);
}

void Player_actor_sound_ROD_STROKE_small(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x445);
}

void Player_actor_sound_ROD_BACK(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x10A);
}

void Player_actor_sound_scoop1(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x11E);
}

void Player_actor_sound_scoop_umeru(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x120);
}

void Player_actor_sound_scoop_hit(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x121);
}

void Player_actor_sound_scoop_shigemi(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x401);
}

void Player_actor_sound_ITEM_HORIDASHI(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x57);
}

void Player_actor_sound_slip(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x129);
}

void Player_actor_sound_tree_touch(xyz_t* pos) {
    sAdo_OngenTrgStart(0x134, pos);
}

void Player_actor_sound_tree_yurasu(xyz_t* pos) {
    sAdo_OngenTrgStart(0x135, pos);
}

void Player_actor_sound_kirikabu_scoop(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x148);
}

void Player_actor_sound_kirikabu_out(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x149);
}

void Player_actor_sound_coin_gasagoso(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x14A);
}

void Player_actor_sound_knock(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x14E);
}
void Player_actor_sound_araiiki(Actor* actor) {
    s8 gender = common_data.privateInfo->gender;
    u16 id = (gender == 0) ? 0x158 : 0x15A;

    Player_actor_set_sound_common2(actor, id);
}

void Player_actor_sound_zassou_nuku(xyz_t* pos) {
    sAdo_OngenTrgStart(0x15F, pos);
}

void Player_actor_sound_hachi_sasareru(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x160);
}

void Player_actor_sound_wear(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x11C);
}

void Player_actor_sound_dai_ue_kakunou(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x430);
}

void Player_actor_sound_umbrella_rotate(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x432);
}

u8 Player_actor_sound_Get_bgm_num_forCompletePayment(void) {
    switch (common_data.paymentType) {
        case 1:
            return 0x49;
        default:
            return 0x4A;
    }
}

void Player_actor_sound_camera_move1(void) {
    sAdo_SysTrgStart(0x40D);
}

void Player_actor_sound_camera_move2(void) {
    sAdo_SysTrgStart(0x40E);
}

void Player_actor_sound_karaburi(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x43A);
}

void Player_actor_sound_scoop_tree_hit(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x448);
}

void Player_actor_sound_scoop_item_hit(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x449);
}

void Player_actor_sound_axe_ball_hit(Actor* actor) {
    Player_actor_set_sound_common2(actor, 0x449);
}

// m_player_other_func

void Player_actor_ct_other_func1(UNUSED Actor* actor, Game* game) {
    Game_Play* play = (Game_Play*)game;

    play->submenu.unk_E2 = TRUE;
    actor->unk_0B4 = 1;

    Actor_info_make_actor(&play->actorInfo, play, ACTOR_FIELD_DRAW, actor->world.pos.x, actor->world.pos.y,
                          actor->world.pos.z, 0, 0, 0, -1, -1, -1, 0, -1, -1, -1);
}

void Player_actor_setup_main_Wade_other_func1(UNUSED Actor* actor, Game* game) {
    Game_Play* play = (Game_Play*)game;

    play->objectExchangeBank.unk1820 = 1;
}

void Player_actor_setup_main_Wade_snowball_other_func1(Actor* actor, Game* game) {
    Player_actor_setup_main_Wade_other_func1(actor, game);
}

void Player_actor_setup_main_Wade_other_func2(Actor* actor, Game* game) {
    Player* player = (Player*)actor;
    Game_Play* play = (Game_Play*)game;

    mFI_SetBearActor(play, player->mainIndexData.wade.endPos, TRUE);

    common_data.unk_104AC = FALSE;
}

void Player_actor_setup_main_Wade_snowball_other_func2(Actor* actor, Game* game) {
    Player_actor_setup_main_Wade_other_func2(actor, game);
}

void Player_actor_setup_main_Demo_wade_other_func2(Actor* actor, Game* game) {
    Player* player = (Player*)actor;
    Game_Play* play = (Game_Play*)game;

    mFI_SetBearActor(play, player->mainIndexData.wade.endPos, TRUE);

    common_data.unk_104AC = FALSE;
}

void Player_actor_main_Wade_other_func1(UNUSED Actor* actor, UNUSED Game* game) {
}

void Player_actor_main_Sitdown_wait_other_func2(Actor* actor, UNUSED Game* game) {
    if (common_data.clip.myRoomClip != NULL) {
        common_data.clip.myRoomClip->unk_54(&actor->world.pos);
    }
}

void Player_actor_main_Relax_rod_other_func2(Actor* actor, Game* game) {
    Player_actor_request_camera2_main_simple_fishing(actor, game);
}

void Player_actor_main_Vib_rod_other_func2(Actor* actor, Game* game) {
    Player_actor_request_camera2_main_simple_fishing(actor, game);
}

void Player_actor_main_Collect_rod_other_func2(Actor* actor, Game* game) {
    Player_actor_request_camera2_main_simple_return(actor, game);
}

void Player_actor_main_Fly_rod_other_func2(Actor* actor, Game* game) {
    Player_actor_request_camera2_main_simple_return(actor, game);
}

void Player_actor_settle_main_Collect_rod_other_func2(UNUSED Actor* actor, Game* game) {
    Player_actor_request_camera2_main_normal(game);
}

void Player_actor_settle_main_Fly_rod_other_func2(UNUSED Actor* actor, Game* game) {
    Player_actor_request_camera2_change_priority(game);
}

void Player_actor_set_nextgoto_info_type0(Actor* actor) {
    Game_Play* play = (Game_Play*)gamePT;
    Player* player = get_player_actor_withoutCheck(play);

    if (goto_other_scene(play, &common_data.structureExitDoorData, TRUE) != TRUE) {
        mDemo_End(actor);
    } else {
        mBGMPsComp_make_ps_wipe(0x428A);
    }
    player->updateSceneBGMode = TRUE;
}

void Player_actor_set_nextgoto_info_type1(Actor* actor) {
    Game_Play* play = (Game_Play*)gamePT;
    Player* player = (Player*)actor;
    s32 item = player->itemInFront;

    if (goto_next_scene(play, item - DOOR_START, TRUE) != TRUE) {
        mDemo_End(actor);
    } else {
        if (common_data.doorData.nextSceneId - 1 == SCENE_DEPART_2) {
            mBGMForce_room_nonstop_start();
        } else {
            mBGMPsComp_make_ps_wipe(0x28A);
        }
    }
}

void Player_actor_check_nextgoto(Actor* actor, Game* game) {
    Game_Play* play = (Game_Play*)game;
    Player* player = (Player*)actor;
    s32 door;

    s32 item = (u16)player->itemInFront;

    if (ACTOR_FGNAME_GET_F000((u16)player->itemInFront) == FGNAME_F000_4) {
        if (mEv_CheckTitleDemo() <= 0 && play->unk_1EE3 == 0) {
            door = item;

            if (door >= EXIT_DOOR && door < EXIT_DOOR1) {
                mDemo_Request(2, actor, Player_actor_set_nextgoto_info_type0);

                if (player->updateSceneBGMode != FALSE) {
                    mBGMPsComp_scene_mode(0xE);
                    player->updateSceneBGMode = FALSE;
                }
            } else if (door >= DOOR0 && door < EXIT_DOOR) {
                mDemo_Request(2, actor, Player_actor_set_nextgoto_info_type1);
            }
        }
    }
}

void Player_actor_check_forward(Actor* actor, Game* game) {
    s16 rot = actor->shape.rot.y;
    xyz_t pos;
    Player* player = (Player*)actor;
    u16* item;

    pos.x = actor->world.pos.x + 0.00061037019f * sins(rot);
    pos.z = actor->world.pos.z + 0.00061037019f * coss(rot);

    item = mFI_GetUnitFG(pos);

    player->forwardUtPos.x = pos.x;
    player->forwardUtPos.z = pos.z;

    if (item != NULL) {
        player->itemInFront = *item;
    } else {
        player->itemInFront = 0;
    }

    Player_actor_check_nextgoto(actor, game);

    if (chkTrigger(A_BUTTON)) {
        player->pressedAButton = TRUE;
    } else {
        player->pressedAButton = FALSE;
    }
}

void Player_actor_move_other_func1(Actor* actor, Game* game) {
    Player_actor_cancel_request_change_proc_index_by_A_btn(actor);
    Player_actor_request_main_change_from_submenu(actor, game);
    Player_actor_request_change_item(game);
    Player_actor_cancel_request_change_proc_index(actor);
    Player_actor_change_proc_index(actor, game);
    Player_actor_Reset_excute_cancel_wade(actor);
    Player_actor_Set_OldAngle(actor);
    Player_actor_Culc_player_frame_counter(actor);
}

void Player_actor_move_other_func2(Actor* actor, Game* game) {
    Player* player = (Player*)actor;

    Player_actor_set_eye_PositionAndAngle(actor);
    Player_actor_sound_SetStatus(actor);
    Player_actor_Set_Indoor_Camera_Index(actor, game);
    Player_actor_check_forward(actor, game);
    mFI_SetPlayerWade(game);
    Player_actor_check_little_shake_tree(actor, game);
    Player_actor_check_shake_tree_timer(actor);
    Player_actor_check_pitfall(actor, game);
    Player_actor_set_ripple(actor, game);

    PLAYERREG(87) = player->nowMainIndex;
    PLAYERREG(88) = player->unk_0D04;
    PLAYERREG(89) = actor->world.rot.y;
    PLAYERREG(90) = actor->shape.rot.y;
    PLAYERREG(91) = actor->world.pos.x;
    PLAYERREG(92) = actor->world.pos.y;
    PLAYERREG(93) = actor->world.pos.z;
}

void Player_actor_draw_other_func2(Actor* actor, Game* game) {
    Player_actor_SetPosition_OBJtoLine_forItem(actor, game);
}

void Player_actor_change_main_index_other_func1(UNUSED Actor* actor, UNUSED Game* game) {
}

void Player_actor_change_main_index_other_func2(UNUSED Actor* actor, UNUSED Game* game) {
}

void Player_actor_settle_main_other_func2(Actor* actor, Game* game) {
    Player_actor_SetFootMark_for_settle_main(actor, game);
}

void Player_actor_SetActorUki(Actor* actor, Game* game) {
    Player* player = (Player*)actor;
    Game_Play* play = (Game_Play*)game;

    if (Player_actor_CheckScene_AbleOutItem(common_data.save.sceneNo) != FALSE && player->fishingRodActor == NULL) {
        player->fishingRodActor = Actor_info_name_search(&play->actorInfo, ACTOR_UKI, ACTOR_PART_4);
    }
}

void Player_actor_Item_main_other_func1(Actor* actor, Game* game) {
    Player_actor_SetActorUki(actor, game);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD3F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD584_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_Get_ItemKind.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD668_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD690_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD6B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD6E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD7D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD81C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD880_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD8B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BD934_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BDACC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BDAE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BDBF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BDD04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BDD30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BDD88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BDDB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BDEF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BDF6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE000_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE014_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE0B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE140_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE184_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE1C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE4AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE4EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE530_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE570_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE5A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE5D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE620_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE670_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE6A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE6DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE71C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE788_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE85C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE880_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE8C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE968_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BE9CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEA04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEA58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEA8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEAC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEB18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEB50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEBA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEBF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEC2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BECFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BED44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BED64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BED9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEDF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEE20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEE58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEF40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEFA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BEFD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF008_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF068_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF098_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF0D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF148_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF1A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF1E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF21C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF288_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF360_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF374_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF410_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF494_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF6C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF77C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF7E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF824_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF858_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF890_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF91C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BF954_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BFA84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BFAC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BFB30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BFEB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BFF08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808BFF28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0150_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0188_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C01D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0260_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0280_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C02A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C02C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C02E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C031C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C037C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0408_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C04E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0500_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0520_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0540_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0560_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C05D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0624_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C06AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0734_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0758_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0778_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C07B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0808_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0888_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C08FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0998_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C09B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C09D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C09F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0A18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0AA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0B24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0BA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0C48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0C68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0C88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0CA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0CC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0D34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0DB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0E30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0ED8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0EF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0F18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0F38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0F58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C0FE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1064_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C10E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1118_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C11EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1210_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1230_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1250_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1270_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1370_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C13F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C14B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C15D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C15F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1678_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1790_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C18C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C191C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1C08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1C28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1C48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1DB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1E5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1EDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1FC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C1FE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C200C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C203C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2098_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C20B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C20D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C20F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C223C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C225C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2300_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2380_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2468_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2490_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2630_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C278C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C27E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2808_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2828_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2848_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2994_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2B78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2B98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2C3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2C8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2D4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2D74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2E10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2ECC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2EF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2F68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C2F88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C305C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C30A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C30C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C30E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3114_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C31BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C320C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C32CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C32F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C33A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C33E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3464_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C34CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3504_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3610_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3630_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C36C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C36E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3728_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3748_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3768_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3788_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C37D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C37F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3888_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3908_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C39B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C39D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C39F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3A14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3A34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3AB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3AD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3B50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3BB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3BE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3D2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3D4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3D70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3D90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3E30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3E50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3E70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3EDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3F34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3F44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C3FE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4098_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C41B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C41D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4260_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4298_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4338_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4358_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C43C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C44E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4588_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4698_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C46B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C470C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C472C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C479C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4810_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C48B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C48D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C48F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C492C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C494C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C49A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C49B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4A18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4AA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4AF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4B24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4BAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4BCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4BEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4C0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4C2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4CA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4CF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4DB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4E4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4E6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4F18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4F38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C4F58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C51E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5260_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5300_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C532C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5418_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5438_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5480_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C54C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C54E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5508_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5578_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5618_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C56F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5734_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5858_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C59BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5A04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5A24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5A44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5AB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5B54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5BFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5D14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5D34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5D54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5DC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5DE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5E00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5EB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5F48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C5FE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6014_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6104_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6124_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6170_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C61B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C61D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C61F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6258_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C62F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C638C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C645C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6488_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C64A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C64C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C64E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6554_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C65F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6624_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C66F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6718_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C67A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C67C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C67E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C685C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C68FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6948_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6A10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6AE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6BE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6C38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6C58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6C94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6DCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6E18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6E40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6EB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6EF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6F54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C6FE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7000_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7020_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C71C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C721C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7250_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C72C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C72F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C73C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C74B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C74D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C751C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7544_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C75AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C75E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C779C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C78D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C79C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C79E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7A1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7B64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7BB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7BD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7C98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7D3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7E80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7EA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7EC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7EE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7F00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7F5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C7FB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8100_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8170_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8218_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C82A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C843C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8478_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C850C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8538_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8558_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8578_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8598_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8898_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C88D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8944_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C89DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8A64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8B94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8BD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8C64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8C90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8CB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8CD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8CF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8F64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C8FC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9024_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9094_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9134_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C91C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9288_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9330_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9354_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9374_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9394_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C93B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C943C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9578_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C95A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C963C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9688_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9748_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C978C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9898_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C98D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9928_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9974_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9994_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C99C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9A60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9AC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9B38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9B58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9B78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9BE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9C60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9D40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9E20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9E60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9E80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9EA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9EE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9F24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9F70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9F90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808C9FD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA060_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA104_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA1A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA23C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA268_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA288_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA3C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA400_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA4C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA62C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA668_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA6B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA724_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA7B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA7D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA93C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CA9E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAA58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAACC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAAEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAB0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAB2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAB4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CABA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CACB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAD58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAE00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAE90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAEAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAF04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAF24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAF50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAF8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CAFDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB088_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB104_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB17C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB28C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB32C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB39C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB4A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB534_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB554_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB578_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB598_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB5B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB5D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB6BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB74C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB7E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB834_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB8B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB8DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB8FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB91C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CB93C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CBA3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CBABC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CBB0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CBB90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CBC8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CBCE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CBEF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CBF18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CBF38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CC064_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CC108_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CC178_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CC240_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CC380_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CC3A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CC54C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CC7B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CC7E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CC988_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCA60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCA80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCABC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCADC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCB28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCB70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCB90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCBB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCC20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCCF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCD64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCE5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCEC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCF34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCF54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCF74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCF94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CCFDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD0EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD188_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD1C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD280_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD2D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD340_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD360_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD380_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD3A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD3C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD3EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD46C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD4D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD5C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD6B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD6D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD6F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD714_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD76C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD78C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD7AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CD9E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDA78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDB24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDB8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDC40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDC60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDC80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDD70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDDB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDDD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDDF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDE88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDF28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CDF78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE018_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE038_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE058_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE078_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE098_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE0E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE338_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE3D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE44C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE534_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE554_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE574_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE5B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE604_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE624_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE644_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE66C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE758_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE860_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE880_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE8A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE8DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE930_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE950_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE970_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CE9B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEA50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEAA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEB44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEB74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEB94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEBB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEBD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CED20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEDB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEE04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEF14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEF34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEF54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEF74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEFBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEFDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CEFFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF044_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF0F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF144_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF1E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF210_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF230_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF250_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF270_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF298_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF328_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF378_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF418_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF438_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF478_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF4C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF4E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF500_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF540_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF5F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF664_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF7B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF7FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF84C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF86C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF8A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF8C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF8E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CF92C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CFA54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CFD10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CFDB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CFE6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CFEEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CFFB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CFFD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808CFFF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0010_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0030_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0078_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0094_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0128_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D01D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0258_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0300_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D032C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D034C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0508_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D052C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0640_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0748_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D07B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D07D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D07F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D08B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D08D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0A44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0AE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0B60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0BE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0C30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0CD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0F0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0F2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D0FBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D102C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D104C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D106C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D10D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1248_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D12F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1380_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1414_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1430_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1488_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D14A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1A78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1A98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1AE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1F4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1FB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1FD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D1FF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2108_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D21A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D21F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2268_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2288_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D22A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D22E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2338_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2358_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2378_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D23B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D24E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D251C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2674_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2694_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D26B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2710_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2730_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2750_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2774_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2794_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D283C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D28CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2974_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2994_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D29B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D29D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D29F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2A3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2A58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2AD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2B7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2C04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2D5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2DD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2E40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2E60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2E84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2ED8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2F44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2F7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2F9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D2FBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D307C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3134_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3318_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3384_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3404_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D34C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3544_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3614_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3660_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D371C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D373C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3788_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D37C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D38F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D391C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D39A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D39C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3A44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3A64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3A84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3B40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3BD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3C8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3CAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3CCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3CEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3D88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3E08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3EA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3F88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3FA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3FC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D3FE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D406C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D40F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D418C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4284_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D42A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D42C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D42E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4380_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4410_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D44A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D45A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D45CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D45EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D460C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D462C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D46B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D47EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4870_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4990_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D49B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D49D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D49F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4A70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4B00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4B98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4CAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4CDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4CFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4D1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4D3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4D68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4DFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4E84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D4EE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5088_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D50A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D50C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D50E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5108_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5150_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5170_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5274_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5324_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D53D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5434_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D55DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D55FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D561C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D563C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D565C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D56FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D57A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5848_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D58BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D59AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5A34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5A54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5A8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5AB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5AD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5AF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5B54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5C18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5C9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5DA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5DE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D5E18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6258_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6278_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6298_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6318_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D63C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6448_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6524_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D655C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D657C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D65C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6610_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D66D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6720_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D678C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D67AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D67CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6820_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D68A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6984_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D69BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D69DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6A24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6A70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6AD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6B5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6BAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6C34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6C54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6CDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6D3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6DA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6EDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6F00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6F20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6FC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D6FE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7000_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D706C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D70DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D715C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D71AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D71CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D71F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D729C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D72E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7460_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7488_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D74AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D74CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D74EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D750C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7570_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7814_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D787C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7904_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D79BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7A7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7ADC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7C0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7C74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7CAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7CE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7D30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7D80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7E00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7E24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7E44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7EE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7F24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7F44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7F64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D7FE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8090_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D817C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D81B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8200_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8220_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8240_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8260_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D82E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8374_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8408_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D850C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8544_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8564_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D85B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D85D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D85F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D862C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8668_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D86B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8748_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D87DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D88F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8958_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8978_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D89C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D89E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8A04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8A44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8AD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8B68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8C2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8C58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D8C78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D90B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D90FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9144_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D91B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D91D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D91F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9348_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D93F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9484_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9584_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D95BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D95DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9628_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9668_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D96DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D972C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9758_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D97D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D97FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D981C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D983C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D985C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D995C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D99E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9A60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9B58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9BA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9BC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9C0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9C48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9C84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9CA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9CC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9CEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9D78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9DC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9DF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9F00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9F2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9F4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9F98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9FB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808D9FD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA000_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA080_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA0D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA16C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA1A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA1C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA380_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA3A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA3D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA3F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA418_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA49C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA4EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA51C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA6C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA6F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA710_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA75C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA780_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA7A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA7C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA88C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA91C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DA9E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAA4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAA6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAAFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DABB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DABD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DABF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAC18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAC84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAD2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAD7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAE7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAEC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAEE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAF2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAF70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAF90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DAFB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB028_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB10C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB154_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB1F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB280_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB338_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB358_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB378_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB4C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB508_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB528_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB548_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB588_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB628_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB6AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB76C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB7AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB7F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB818_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB860_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB89C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB96C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DB9E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBA00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBA20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBAE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBB90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBC20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBD4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBD84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBDA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBDF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBE40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBE7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBE9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBEBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBF10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DBFA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC034_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC0A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC1E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC274_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC294_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC344_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC3E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC430_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC450_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC470_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC4F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC594_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC6F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC714_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC7A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC7E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC85C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC8AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC988_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC9A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC9C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DC9E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCA08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCB18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCBA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCBF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCC78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCCB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCCD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCD24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCD5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCD7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCD9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCE40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCF6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DCFA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD02C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD07C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD0F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD108_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD12C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD14C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD16C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD18C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD1F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD2D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD318_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD398_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_dt.s")

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_request_main_change_from_submenu.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_request_change_item.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DD9B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/func_808DDA18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_change_proc_index.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/player_actor/m_player/Player_actor_draw.s")
