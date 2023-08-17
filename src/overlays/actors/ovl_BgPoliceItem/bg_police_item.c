#include "bg_police_item.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void bPI_actor_move(Actor* thisx, Game_Play* play);
void bPI_actor_draw(Actor* thisx, Game_Play* play);

#if 0
ActorProfile BgPoliceItem_Profile = {
    /* */ ACTOR_BG_POLICE_ITEM,
    /* */ ACTOR_PART_0,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(BgPoliceItem),
    /* */ (ActorFunc)none_proc1,
    /* */ (ActorFunc)none_proc1,
    /* */ bPI_actor_move,
    /* */ bPI_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPoliceItem/bg_police_item/func_808EB720_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPoliceItem/bg_police_item/func_808EB854_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPoliceItem/bg_police_item/func_808EB954_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPoliceItem/bg_police_item/func_808EBA24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPoliceItem/bg_police_item/func_808EBA8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPoliceItem/bg_police_item/bPI_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPoliceItem/bg_police_item/func_808EBB4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPoliceItem/bg_police_item/func_808EBC7C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_BgPoliceItem/bg_police_item/bPI_actor_draw.s")
