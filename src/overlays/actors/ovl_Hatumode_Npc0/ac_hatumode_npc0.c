#include "ac_hatumode_npc0.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_8052ab54(Actor* thisx, Game_Play* game_play);
void func_8052ac90(Actor* thisx, Game_Play* game_play);
void func_8052ad14(Actor* thisx, Game_Play* game_play);
void func_8052ac70(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Hatumode_Npc0_Profile = {
    /* */ ACTOR_HATUMODE_NPC0,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0xD058,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Hatumode_Npc0),
    /* */ func_8052ab54,
    /* */ func_8052ac90,
    /* */ func_8052ad14,
    /* */ (ActorFunc)none_proc1,
    /* */ func_8052ac70,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_8052ab54.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_8052ac70.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_8052ac90.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_8052ad14.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88970_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88A10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88A5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88AC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88AF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88B44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88B7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88BC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88C08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88C84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88D7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88DF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88E64_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88EF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88F2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A88FC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A89018_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A89058_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A890C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A8916C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A891CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A8922C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A8927C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A892F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A89364_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A893FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A89480_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A89510_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A8954C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A895C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A8960C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A8964C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A896EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Hatumode_Npc0/ac_hatumode_npc0/func_80A89734_jp.s")
