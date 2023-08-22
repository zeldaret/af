#include "ac_handOverItem.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHOI_actor_ct(Actor* thisx, Game_Play* game_play);
void aHOI_actor_dt(Actor* thisx, Game_Play* game_play);
void aHOI_actor_move(Actor* thisx, Game_Play* game_play);
void aHOI_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile HandOverItem_Profile = {
    /* */ ACTOR_HAND_OVER_ITEM,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(HandOverItem),
    /* */ aHOI_actor_ct,
    /* */ aHOI_actor_dt,
    /* */ aHOI_actor_move,
    /* */ aHOI_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/aHOI_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/aHOI_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_80963E08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_80963E50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_80963F00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_8096400C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_8096407C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_809640A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_8096413C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_8096415C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_809641DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_80964308_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_809643B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_809644A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/aHOI_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/func_8096462C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_HandOverItem/ac_handOverItem/aHOI_actor_draw.s")
