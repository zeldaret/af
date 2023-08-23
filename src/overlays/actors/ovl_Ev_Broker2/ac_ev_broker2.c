#include "ac_ev_broker2.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEBR2_actor_ct(Actor* thisx, Game_Play* game_play);
void aEBR2_actor_dt(Actor* thisx, Game_Play* game_play);
void aEBR2_actor_init(Actor* thisx, Game_Play* game_play);
void aEBR2_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Ev_Broker2_Profile = {
    /* */ ACTOR_EV_BROKER2,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD013,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Broker2),
    /* */ aEBR2_actor_ct,
    /* */ aEBR2_actor_dt,
    /* */ aEBR2_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aEBR2_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/aEBR2_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/aEBR2_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/aEBR2_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/aEBR2_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8404_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8440_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8480_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D84A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8504_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8560_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D85A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D85F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D86D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8718_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8738_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8764_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8790_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D87A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D87BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D88C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8958_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8A1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8A98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8AA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8B5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8C28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8DF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8EC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8FAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D8FF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D9060_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D90CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D9138_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D91A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D9210_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D92A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D92F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D9314_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D9394_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D944C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D95EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D9630_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D96A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D96F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D976C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D97AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D97E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D9810_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D9858_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker2/ac_ev_broker2/func_809D98FC_jp.s")
