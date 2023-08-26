#include "ac_ev_designer.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEDSN_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aEDSN_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aEDSN_actor_init(Actor* thisx, Game_Play* gamePlay);
void aEDSN_actor_save(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Ev_Designer_Profile = {
    /* */ ACTOR_EV_DESIGNER,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0xD002,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Designer),
    /* */ aEDSN_actor_ct,
    /* */ aEDSN_actor_dt,
    /* */ aEDSN_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aEDSN_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/aEDSN_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/aEDSN_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/aEDSN_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/aEDSN_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB014_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB0B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB12C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB174_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB1D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB25C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB284_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB390_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB448_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB5AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB73C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB76C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB788_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB82C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB860_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DB9F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBA24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBA54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBAD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBB84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBC18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBD7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBDA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBE24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBE54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBE94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBEBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBF10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBF70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DBFA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DC00C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DC078_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Designer/ac_ev_designer/func_809DC0A8_jp.s")
