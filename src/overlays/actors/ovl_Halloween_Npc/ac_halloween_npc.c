#include "ac_halloween_npc.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aHWN_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aHWN_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aHWN_actor_init(Actor* thisx, Game_Play* gamePlay);
void aHWN_actor_save(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Halloween_Npc_Profile = {
    /* */ ACTOR_HALLOWEEN_NPC,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Halloween_Npc),
    /* */ aHWN_actor_ct,
    /* */ aHWN_actor_dt,
    /* */ aHWN_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aHWN_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/aHWN_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/aHWN_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/aHWN_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/aHWN_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4884_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4928_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4954_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4AF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4B70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4BD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4C64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4CCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4DC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4E58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4EDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4F3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A4FE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A503C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A50C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5128_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5178_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5194_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A51CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A52CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A530C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5340_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A536C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A53F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5470_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A54E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A550C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5548_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5584_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A55C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5610_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5640_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5680_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A56C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A57E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Halloween_Npc/ac_halloween_npc/func_809A5810_jp.s")
