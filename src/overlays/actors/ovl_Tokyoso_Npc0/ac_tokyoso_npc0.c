#include "ac_tokyoso_npc0.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTKN0_actor_ct(Actor* thisx, Game_Play* game_play);
void aTKN0_actor_dt(Actor* thisx, Game_Play* game_play);
void aTKN0_actor_init(Actor* thisx, Game_Play* game_play);
void aTKN0_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Tokyoso_Npc0_Profile = {
    /* */ ACTOR_TOKYOSO_NPC0,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD02D,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tokyoso_Npc0),
    /* */ aTKN0_actor_ct,
    /* */ aTKN0_actor_dt,
    /* */ aTKN0_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aTKN0_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/aTKN0_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/aTKN0_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/aTKN0_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/aTKN0_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A73E2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A73EC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A73F2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A73F74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A73FFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A74048_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A74088_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A74104_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A74140_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A74198_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A741F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A7424C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A7428C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A7432C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A743AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A743E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A7441C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A7447C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A744B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A744F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A74594_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A7468C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A746B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A74754_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A7479C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A747DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A74848_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tokyoso_Npc0/ac_tokyoso_npc0/func_80A74890_jp.s")
