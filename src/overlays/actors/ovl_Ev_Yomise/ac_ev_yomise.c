#include "ac_ev_yomise.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEYMS_actor_ct(Actor* thisx, Game_Play* game_play);
void aEYMS_actor_dt(Actor* thisx, Game_Play* game_play);
void aEYMS_actor_init(Actor* thisx, Game_Play* game_play);
void aEYMS_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Ev_Yomise_Profile = {
    /* */ ACTOR_EV_YOMISE,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD02C,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Yomise),
    /* */ aEYMS_actor_ct,
    /* */ aEYMS_actor_dt,
    /* */ aEYMS_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aEYMS_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/aEYMS_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/aEYMS_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/aEYMS_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/aEYMS_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A72AE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A72B0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A72BD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A72D78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A72DB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A72FA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A72FF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A730C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A731B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A731F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A7325C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A732E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A73360_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A73420_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A73464_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A736B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A73758_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A737F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A7389C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A73914_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A73944_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A739D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A73A18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Yomise/ac_ev_yomise/func_80A73A38_jp.s")
