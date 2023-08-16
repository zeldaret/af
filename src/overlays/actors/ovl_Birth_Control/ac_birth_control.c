#include "ac_birth_control.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aBC_actor_move(Actor* thisx, PlayState* play);

#if 0
ActorProfile Birth_Control_Profile = {
    /* */ ACTOR_BIRTH_CONTROL,
    /* */ ACTOR_PART_0,
    /* */ 48,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Birth_Control),
    /* */ (ActorFunc)none_proc1,
    /* */ (ActorFunc)none_proc1,
    /* */ aBC_actor_move,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Birth_Control/ac_birth_control/func_80935DF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Birth_Control/ac_birth_control/func_80935E98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Birth_Control/ac_birth_control/func_80935FA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Birth_Control/ac_birth_control/func_809361BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Birth_Control/ac_birth_control/func_8093629C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Birth_Control/ac_birth_control/aBC_actor_move.s")
