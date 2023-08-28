#include "ac_psnowman.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aPSM_actor_ct(Actor* thisx, Game_Play* game_play);
void aPSM_actor_dt(Actor* thisx, Game_Play* game_play);
void aPSM_actor_move(Actor* thisx, Game_Play* game_play);
void aPSM_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Psnowman_Profile = {
    /* */ ACTOR_PSNOWMAN,
    /* */ ACTOR_PART_4,
    /* */ 0,
    /* */ 0xA008,
    /* */ OBJECT_25,
    /* */ sizeof(Psnowman),
    /* */ aPSM_actor_ct,
    /* */ aPSM_actor_dt,
    /* */ aPSM_actor_move,
    /* */ aPSM_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Psnowman/ac_psnowman/aPSM_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Psnowman/ac_psnowman/aPSM_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Psnowman/ac_psnowman/func_80972528_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Psnowman/ac_psnowman/func_80972564_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Psnowman/ac_psnowman/aPSM_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Psnowman/ac_psnowman/aPSM_actor_draw.s")
