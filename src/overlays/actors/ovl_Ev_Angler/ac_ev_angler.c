#include "ac_ev_angler.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aEANG_actor_ct(Actor* thisx, Game_Play* game_play);
void aEANG_actor_dt(Actor* thisx, Game_Play* game_play);
void aEANG_actor_init(Actor* thisx, Game_Play* game_play);
void aEANG_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Ev_Angler_Profile = {
    /* */ ACTOR_EV_ANGLER,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD01D,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ev_Angler),
    /* */ aEANG_actor_ct,
    /* */ aEANG_actor_dt,
    /* */ aEANG_actor_init,
    /* */ (void*)none_proc1,
    /* */ aEANG_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/aEANG_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/aEANG_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/aEANG_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/aEANG_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5928_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5978_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D59E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5A58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5B80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5C28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5C7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5CD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5CFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5D38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5D5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5D84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5DB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5E14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5E9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5F1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D5F68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D60EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D616C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6200_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6298_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6374_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D63C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D63F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6588_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D65E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6614_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6658_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6694_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6790_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D67C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6814_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D6848_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D68C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D69B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ev_Angler/ac_ev_angler/func_809D69E4_jp.s")
