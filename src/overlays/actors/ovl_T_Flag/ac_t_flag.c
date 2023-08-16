#include "ac_t_flag.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTFL_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile T_Flag_Profile = {
    /* */ 139,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 0,
    /* */ 6,
    /* */ sizeof(T_Flag),
    /* */ (ActorFunc)none_proc1,
    /* */ (ActorFunc)none_proc1,
    /* */ (ActorFunc)none_proc1,
    /* */ aTFL_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Flag/ac_t_flag/func_80A207B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Flag/ac_t_flag/func_80A2083C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Flag/ac_t_flag/aTFL_actor_draw.s")
