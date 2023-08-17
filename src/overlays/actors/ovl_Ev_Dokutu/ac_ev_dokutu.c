#include "ac_ev_dokutu.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEVD_actor_ct(Actor* thisx, Game_Play* play);
void aEVD_actor_dt(Actor* thisx, Game_Play* play);
void aEVD_actor_init(Actor* thisx, Game_Play* play);
void aEVD_actor_save(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Ev_Dokutu_Profile = {
    /* */ ACTOR_EV_DOKUTU,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD06C,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Dokutu),
    /* */ aEVD_actor_ct,
    /* */ aEVD_actor_dt,
    /* */ aEVD_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aEVD_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/aEVD_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/aEVD_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/aEVD_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/aEVD_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEAC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEB64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEB90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEBB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEC10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEC5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAECBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAED08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAED48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEDC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEE04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEE30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEE68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEEA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEF48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEF90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAEFD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAF03C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Dokutu/ac_ev_dokutu/func_80AAF084_jp.s")
