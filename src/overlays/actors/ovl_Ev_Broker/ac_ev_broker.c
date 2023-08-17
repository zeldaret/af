#include "ac_ev_broker.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEBRK_actor_ct(Actor* thisx, Game_Play* game_play);
void aEBRK_actor_dt(Actor* thisx, Game_Play* game_play);
void aEBRK_actor_init(Actor* thisx, Game_Play* game_play);
void aEBRK_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Ev_Broker_Profile = {
    /* */ ACTOR_EV_BROKER,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0xD001,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Broker),
    /* */ aEBRK_actor_ct,
    /* */ aEBRK_actor_dt,
    /* */ aEBRK_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aEBRK_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/aEBRK_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/aEBRK_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/aEBRK_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/aEBRK_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D77FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D783C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D785C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D78C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7934_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D79DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7A58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7A94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7B20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7B94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7BB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7BE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7C30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7C7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7C90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7CB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7CE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7D10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7E00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7E30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7E60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7EA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7F0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7F3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D7FE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D801C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D804C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D808C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Broker/ac_ev_broker/func_809D80D4_jp.s")
