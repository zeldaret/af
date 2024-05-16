#include "ac_fallSESW.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_80A034A0_jp(Actor* thisx, Game_Play* game_play);
void func_80A034B0_jp(Actor* thisx, Game_Play* game_play);
void aFLEW_actor_move(Actor* thisx, Game_Play* game_play);
void aFLEW_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile FallSESW_Profile = {
    /* */ ACTOR_FALL_SESW,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x580E,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(FallSESW),
    /* */ func_80A034A0_jp,
    /* */ func_80A034B0_jp,
    /* */ aFLEW_actor_move,
    /* */ aFLEW_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_FallSESW/ac_fallSESW/func_80A034A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_FallSESW/ac_fallSESW/func_80A034B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_FallSESW/ac_fallSESW/aFLEW_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_FallSESW/ac_fallSESW/aFLEW_actor_draw.s")
