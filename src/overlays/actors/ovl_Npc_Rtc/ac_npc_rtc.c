#include "ac_npc_rtc.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aNRTC_actor_ct(Actor* thisx, Game_Play* game_play);
void aNRTC_actor_dt(Actor* thisx, Game_Play* game_play);
void aNRTC_actor_init(Actor* thisx, Game_Play* game_play);
void aNRTC_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Npc_Rtc_Profile = {
    /* */ ACTOR_NPC_RTC,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD066,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Npc_Rtc),
    /* */ aNRTC_actor_ct,
    /* */ aNRTC_actor_dt,
    /* */ aNRTC_actor_init,
    /* */ (void*)none_proc1,
    /* */ aNRTC_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/aNRTC_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/aNRTC_actor_save.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/aNRTC_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/aNRTC_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA31C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA3FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA438_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA480_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA4F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA68C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA6AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA6DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA744_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA7B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA7E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA864_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA8E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA94C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAA9B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAAA64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAAA84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAAACC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAAB00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAAB78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Npc_Rtc/ac_npc_rtc/func_80AAACD0_jp.s")
