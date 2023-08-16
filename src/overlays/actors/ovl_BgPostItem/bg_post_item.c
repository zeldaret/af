#include "bg_post_item.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void bPTI_actor_ct(Actor* thisx, PlayState* play);
void bPTI_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile BgPostItem_Profile = {
    /* */ 82,
    /* */ ACTOR_PART_0,
    /* */ 48,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(BgPostItem),
    /* */ bPTI_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ (ActorFunc)none_proc1,
    /* */ bPTI_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPostItem/bg_post_item/bPTI_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPostItem/bg_post_item/bPTI_actor_draw.s")
