#include "ac_hatumode_control.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHTC_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aHTC_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aHTC_actor_move(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Hatumode_Control_Profile = {
    /* */ ACTOR_HATUMODE_CONTROL,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Hatumode_Control),
    /* */ aHTC_actor_ct,
    /* */ aHTC_actor_dt,
    /* */ aHTC_actor_move,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/aHTC_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/aHTC_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8D740_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8D810_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8D8F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8D940_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8D9D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DA20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DA7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DB18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DBAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DBE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DC90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DCF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DD3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DDE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/aHTC_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DE30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DECC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8DFF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E044_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E0FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E11C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E21C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E288_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E348_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E3F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E480_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E54C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E584_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E5DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E63C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E6E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E730_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E870_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E8B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E968_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E9AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8E9F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Control/ac_hatumode_control/func_80A8EA44_jp.s")
