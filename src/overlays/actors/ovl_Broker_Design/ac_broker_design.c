#include "ac_broker_design.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Broker_Design_Actor_ct(Actor* thisx, Game_Play* gamePlay);
void Broker_Design_Actor_dt(Actor* thisx, Game_Play* gamePlay);
void Broker_Design_Actor_move(Actor* thisx, Game_Play* gamePlay);
void Broker_Design_Actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Broker_Design_Profile = {
    /* */ ACTOR_BROKER_DESIGN,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Broker_Design),
    /* */ Broker_Design_Actor_ct,
    /* */ Broker_Design_Actor_dt,
    /* */ Broker_Design_Actor_move,
    /* */ Broker_Design_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Broker_Design/ac_broker_design/func_809516E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Broker_Design/ac_broker_design/Broker_Design_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Broker_Design/ac_broker_design/Broker_Design_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Broker_Design/ac_broker_design/Broker_Design_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Broker_Design/ac_broker_design/Broker_Design_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Broker_Design/ac_broker_design/func_8095182C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Broker_Design/ac_broker_design/func_809518D0_jp.s")
