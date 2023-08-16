#include "ac_fuusen.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aFSN_actor_ct(Actor* thisx, PlayState* play);
void aFSN_actor_dt(Actor* thisx, PlayState* play);
void aFSN_actor_move(Actor* thisx, PlayState* play);
void aFSN_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Fuusen_Profile = {
    /* */ 178,
    /* */ ACTOR_PART_7,
    /* */ 16,
    /* */ 0,
    /* */ 400,
    /* */ sizeof(Fuusen),
    /* */ aFSN_actor_ct,
    /* */ aFSN_actor_dt,
    /* */ aFSN_actor_move,
    /* */ aFSN_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/aFSN_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/aFSN_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AAD270_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AAD490_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AAD4A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AAD4DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AAD580_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AAD5A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AADB9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AADDA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AADEC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AADF10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/aFSN_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/func_80AAE10C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fuusen/ac_fuusen/aFSN_actor_draw.s")
