#include "ac_tama.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTAM_actor_ct(Actor* thisx, Game_Play* play);
void func_80A8EF30_jp(Actor* thisx, Game_Play* play);
void aTAM_actor_init(Actor* thisx, Game_Play* play);
void aTAM_actor_draw(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Tama_Profile = {
    /* */ ACTOR_TAMA,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5833,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Tama),
    /* */ aTAM_actor_ct,
    /* */ func_80A8EF30_jp,
    /* */ aTAM_actor_init,
    /* */ aTAM_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tama/ac_tama/aTAM_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tama/ac_tama/func_80A8EF30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tama/ac_tama/func_80A8EFBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tama/ac_tama/func_80A8EFCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tama/ac_tama/func_80A8EFEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tama/ac_tama/aTAM_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Tama/ac_tama/aTAM_actor_draw.s")
