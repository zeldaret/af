#include "ac_train_window.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Train_Window_Actor_ct(Actor* thisx, PlayState* play);
void Train_Window_Actor_dt(Actor* thisx, PlayState* play);
void Train_Window_Actor_move(Actor* thisx, PlayState* play);
void Train_Window_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Train_Window_Profile = {
    /* */ ACTOR_TRAIN_WINDOW,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x8011,
    /* */ OBJECT_41,
    /* */ sizeof(Train_Window),
    /* */ Train_Window_Actor_ct,
    /* */ Train_Window_Actor_dt,
    /* */ Train_Window_Actor_move,
    /* */ Train_Window_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A59360_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/Train_Window_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/Train_Window_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A5961C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/Train_Window_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A599DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A59A2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A59AB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A59BA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A59CF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A59E88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A59EA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A5A034_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/func_80A5A120_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train_Window/ac_train_window/Train_Window_Actor_draw.s")
