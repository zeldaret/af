#include "ac_ev_santa.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aESNT_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aESNT_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aESNT_actor_init(Actor* thisx, Game_Play* gamePlay);
void aESNT_actor_save(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Ev_Santa_Profile = {
    /* */ ACTOR_EV_SANTA,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD00F,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Santa),
    /* */ aESNT_actor_ct,
    /* */ aESNT_actor_dt,
    /* */ aESNT_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aESNT_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/aESNT_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/aESNT_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/aESNT_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/aESNT_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7304_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E73A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7438_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E74F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7544_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7574_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E75C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E75F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7628_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7674_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E77A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7800_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E78D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E78F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E79FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7A54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7AC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7B48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7B88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7BBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7BF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7C40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Santa/ac_ev_santa/func_809E7C6C_jp.s")
