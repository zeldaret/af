#include "ac_buggy.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aBGY_actor_ct(Actor* thisx, Game_Play* game_play);
void aBGY_actor_dt(Actor* thisx, Game_Play* game_play);
void aBGY_actor_init(Actor* thisx, Game_Play* game_play);
void aBGY_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Buggy_Profile = {
    /* */ ACTOR_BUGGY,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5827,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Buggy),
    /* */ aBGY_actor_ct,
    /* */ aBGY_actor_dt,
    /* */ aBGY_actor_init,
    /* */ aBGY_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/aBGY_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/aBGY_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_809FFDA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_809FFF90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A00190_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A0024C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A002A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A00378_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A003A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A00400_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A004A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A005CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A00600_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A00634_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A006F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/aBGY_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A00874_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/func_80A00918_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Buggy/ac_buggy/aBGY_actor_draw.s")
