#include "ac_fuusen.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aFSN_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aFSN_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aFSN_actor_move(Actor* thisx, Game_Play* gamePlay);
void aFSN_actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Fuusen_Profile = {
    /* */ ACTOR_FUUSEN,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10,
    /* */ 0x0000,
    /* */ OBJECT_400,
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
