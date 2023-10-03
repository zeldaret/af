#include "ac_taisou_npc0.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTS0_actor_ct(Actor* thisx, Game_Play* game_play);
void aTS0_actor_dt(Actor* thisx, Game_Play* game_play);
void aTS0_actor_init(Actor* thisx, Game_Play* game_play);
void aTS0_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Taisou_Npc0_Profile = {
    /* */ ACTOR_TAISOU_NPC0,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Taisou_Npc0),
    /* */ aTS0_actor_ct,
    /* */ aTS0_actor_dt,
    /* */ aTS0_actor_init,
    /* */ (void*)none_proc1,
    /* */ aTS0_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/aTS0_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/aTS0_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/aTS0_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/aTS0_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3750_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E37C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3814_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3848_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3904_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3924_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3938_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E396C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E399C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3A68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3AF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3B30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3BB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3D08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3D70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3DD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3E04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E3F2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E4018_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E414C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E41A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E41D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E4204_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E42DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E4348_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E4378_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E44A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E44DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E451C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Taisou_Npc0/ac_taisou_npc0/func_809E455C_jp.s")
