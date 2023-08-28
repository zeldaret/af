#include "ac_train1.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTR1_actor_ct(Actor* thisx, Game_Play* game_play);
void aTR1_actor_dt(Actor* thisx, Game_Play* game_play);
void aTR1_actor_move(Actor* thisx, Game_Play* game_play);
void aTR1_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Train1_Profile = {
    /* */ ACTOR_TRAIN1,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20000000,
    /* */ 0x580B,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Train1),
    /* */ aTR1_actor_ct,
    /* */ aTR1_actor_dt,
    /* */ aTR1_actor_move,
    /* */ aTR1_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/aTR1_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/aTR1_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D3A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D3D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D444_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D480_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D558_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D5F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/func_80A0D708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/aTR1_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Train1/ac_train1/aTR1_actor_draw.s")
