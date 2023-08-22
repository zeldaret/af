#include "ac_dump.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aDUM_actor_ct(Actor* thisx, Game_Play* game_play);
void aDUM_actor_dt(Actor* thisx, Game_Play* game_play);
void aDUM_actor_init(Actor* thisx, Game_Play* game_play);
void aDUM_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Dump_Profile = {
    /* */ ACTOR_DUMP,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x583A,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Dump),
    /* */ aDUM_actor_ct,
    /* */ aDUM_actor_dt,
    /* */ aDUM_actor_init,
    /* */ aDUM_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dump/ac_dump/aDUM_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dump/ac_dump/aDUM_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dump/ac_dump/func_80A96A70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dump/ac_dump/func_80A96B28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dump/ac_dump/func_80A96BE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dump/ac_dump/func_80A96C50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dump/ac_dump/func_80A96D04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dump/ac_dump/func_80A96D24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dump/ac_dump/aDUM_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Dump/ac_dump/aDUM_actor_draw.s")
