#include "ac_t_tam.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTTM_actor_draw(Actor* thisx, Game_Play* play);

#if 0
ActorProfile T_Tama_Profile = {
    /* */ ACTOR_T_TAMA,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_391,
    /* */ sizeof(T_Tama),
    /* */ (ActorFunc)none_proc1,
    /* */ (ActorFunc)none_proc1,
    /* */ (ActorFunc)none_proc1,
    /* */ aTTM_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Tama/ac_t_tam/aTTM_actor_draw.s")
