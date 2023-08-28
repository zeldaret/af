#include "ac_hanabi_npc1.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHN1_actor_ct(Actor* thisx, Game_Play* game_play);
void aHN1_actor_dt(Actor* thisx, Game_Play* game_play);
void aHN1_actor_init(Actor* thisx, Game_Play* game_play);
void aHN1_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Hanabi_Npc1_Profile = {
    /* */ ACTOR_HANABI_NPC1,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Hanabi_Npc1),
    /* */ aHN1_actor_ct,
    /* */ aHN1_actor_dt,
    /* */ aHN1_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aHN1_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/aHN1_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/aHN1_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/aHN1_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/aHN1_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DD954_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DD9A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DD9D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DD9F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDA54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDA74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDAA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDB00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDB30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDC20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDC34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDC9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDCC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDCF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDD8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDDBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDDEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDF34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDFAC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DDFDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DE050_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DE084_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DE0B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hanabi_Npc1/ac_hanabi_npc1/func_809DE0F0_jp.s")
