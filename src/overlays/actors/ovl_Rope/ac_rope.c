#include "ac_rope.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aRP_actor_ct(Actor* thisx, PlayState* play);
void aRP_actor_dt(Actor* thisx, PlayState* play);
void aRP_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Rope_Profile = {
    /* */ ACTOR_ROPE,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 0x0000,
    /* */ OBJECT_394,
    /* */ sizeof(Rope),
    /* */ aRP_actor_ct,
    /* */ aRP_actor_dt,
    /* */ (ActorFunc)none_proc1,
    /* */ aRP_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Rope/ac_rope/aRP_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Rope/ac_rope/aRP_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Rope/ac_rope/func_8096D920_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Rope/ac_rope/aRP_actor_draw.s")
