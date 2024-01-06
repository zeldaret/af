#include "ac_t_flag.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTFL_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile T_Flag_Profile = {
    /* */ ACTOR_T_FLAG,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_6,
    /* */ sizeof(T_Flag),
    /* */ (void*)none_proc1,
    /* */ (void*)none_proc1,
    /* */ (void*)none_proc1,
    /* */ aTFL_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Flag/ac_t_flag/func_80A207B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Flag/ac_t_flag/func_80A2083C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Flag/ac_t_flag/aTFL_actor_draw.s")
