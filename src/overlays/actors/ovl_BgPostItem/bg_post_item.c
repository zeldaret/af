#include "bg_post_item.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void bPTI_actor_ct(Actor* thisx, Game_Play* game_play);
void bPTI_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile BgPostItem_Profile = {
    /* */ ACTOR_BG_POST_ITEM,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
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
