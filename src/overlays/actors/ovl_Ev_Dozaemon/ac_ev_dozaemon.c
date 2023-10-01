#include "ac_ev_dozaemon.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEDZ_actor_ct(Actor* thisx, Game_Play* game_play);
void aEDZ_actor_dt(Actor* thisx, Game_Play* game_play);
void aEDZ_actor_init(Actor* thisx, Game_Play* game_play);
void aEDZ_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Ev_Dozaemon_Profile = {
    /* */ ACTOR_EV_DOZAEMON,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD064,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Dozaemon),
    /* */ aEDZ_actor_ct,
    /* */ aEDZ_actor_dt,
    /* */ aEDZ_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aEDZ_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/aEDZ_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/aEDZ_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/aEDZ_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/aEDZ_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A981AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98248_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98274_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98320_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A983B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98444_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A984C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98500_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A985D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A985F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A9868C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A986D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98794_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A987E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A988AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A988EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A9897C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A989D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A989F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98A20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98A58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98AC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98B2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98B74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98C14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98C5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98C9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98D08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dozaemon/ac_ev_dozaemon/func_80A98D50_jp.s")
