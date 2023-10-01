#include "ac_npc_guide.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNGD_actor_ct(Actor* thisx, Game_Play* game_play);
void aNGD_actor_dt(Actor* thisx, Game_Play* game_play);
void aNGD_actor_init(Actor* thisx, Game_Play* game_play);
void aNGD_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Guide_Profile = {
    /* */ ACTOR_NPC_GUIDE,
    /* */ ACTOR_PART_NPC,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0xD004,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Guide),
    /* */ aNGD_actor_ct,
    /* */ aNGD_actor_dt,
    /* */ aNGD_actor_init,
    /* */ (ActorFunc)none_proc1,
    /* */ aNGD_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/aNGD_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/aNGD_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/aNGD_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/aNGD_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF1B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF23C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF5E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF628_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF654_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF680_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF6A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF72C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF784_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF7CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF868_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF8E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF94C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF97C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AF9E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFA24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFA58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFAF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFB80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFBE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFC34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFC60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFD38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFE28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFE70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFF04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809AFF9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B00B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B013C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0188_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B01B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B01F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0248_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B02D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0324_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0350_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0400_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0480_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B050C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0558_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B058C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0624_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0674_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B06AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B06EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0730_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B07C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B07F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0828_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B086C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B08B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B08C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B08DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0900_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0948_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B097C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0990_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B09C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B09F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0A14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0A44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0B64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0B94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0BE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Guide/ac_npc_guide/func_809B0C80_jp.s")
