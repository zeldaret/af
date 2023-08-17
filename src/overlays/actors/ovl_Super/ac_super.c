#include "ac_super.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aSPR_actor_ct(Actor* thisx, Game_Play* game_play);
void aSPR_actor_dt(Actor* thisx, Game_Play* game_play);
void aSPR_actor_init(Actor* thisx, Game_Play* game_play);
void aSPR_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Super_Profile = {
    /* */ ACTOR_SUPER,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5806,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Super),
    /* */ aSPR_actor_ct,
    /* */ aSPR_actor_dt,
    /* */ aSPR_actor_init,
    /* */ aSPR_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/aSPR_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/aSPR_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0B61C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0B64C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0B750_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0B7AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0B888_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0B99C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0B9DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0BAE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0BB84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0BCC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0BCFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0BD30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0BE38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/aSPR_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0BF28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/func_80A0BFBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Super/ac_super/aSPR_actor_draw.s")
