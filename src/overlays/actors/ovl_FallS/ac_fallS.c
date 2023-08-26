#include "ac_fallS.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_80A03230_jp(Actor* thisx, Game_Play* gamePlay);
void func_80A03240_jp(Actor* thisx, Game_Play* gamePlay);
void aFLS_actor_move(Actor* thisx, Game_Play* gamePlay);
void aFLS_actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile FallS_Profile = {
    /* */ ACTOR_FALL_S,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x580D,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(FallS),
    /* */ func_80A03230_jp,
    /* */ func_80A03240_jp,
    /* */ aFLS_actor_move,
    /* */ aFLS_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_FallS/ac_fallS/func_80A03230_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_FallS/ac_fallS/func_80A03240_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_FallS/ac_fallS/aFLS_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_FallS/ac_fallS/aFLS_actor_draw.s")
