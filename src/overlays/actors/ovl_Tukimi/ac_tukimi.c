#include "ac_tukimi.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTUK_actor_ct(Actor* thisx, Game_Play* game_play);
void aTUK_actor_dt(Actor* thisx, Game_Play* game_play);
void aTUK_actor_init(Actor* thisx, Game_Play* game_play);
void aTUK_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Tukimi_Profile = {
    /* */ ACTOR_TUKIMI,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x582E,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tukimi),
    /* */ aTUK_actor_ct,
    /* */ aTUK_actor_dt,
    /* */ aTUK_actor_init,
    /* */ aTUK_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi/ac_tukimi/aTUK_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi/ac_tukimi/aTUK_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi/ac_tukimi/func_80A7FAD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi/ac_tukimi/func_80A7FB1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi/ac_tukimi/func_80A7FB2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi/ac_tukimi/func_80A7FBC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi/ac_tukimi/aTUK_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi/ac_tukimi/func_80A7FD44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi/ac_tukimi/func_80A7FD64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tukimi/ac_tukimi/aTUK_actor_draw.s")
