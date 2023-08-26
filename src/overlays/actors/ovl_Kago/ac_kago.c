#include "ac_kago.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aKAG_actor_ct(Actor* thisx, Game_Play* gamePlay);
void func_80A8F340_jp(Actor* thisx, Game_Play* gamePlay);
void aKAG_actor_init(Actor* thisx, Game_Play* gamePlay);
void aKAG_actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Kago_Profile = {
    /* */ ACTOR_KAGO,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5835,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Kago),
    /* */ aKAG_actor_ct,
    /* */ func_80A8F340_jp,
    /* */ aKAG_actor_init,
    /* */ aKAG_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kago/ac_kago/aKAG_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kago/ac_kago/func_80A8F340_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kago/ac_kago/func_80A8F3CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kago/ac_kago/func_80A8F418_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kago/ac_kago/func_80A8F428_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kago/ac_kago/func_80A8F448_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kago/ac_kago/aKAG_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kago/ac_kago/aKAG_actor_draw.s")
