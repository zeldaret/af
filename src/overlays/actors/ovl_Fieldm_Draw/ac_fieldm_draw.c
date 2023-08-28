#include "ac_fieldm_draw.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Fieldm_Actor_ct(Actor* thisx, Game_Play* game_play);
void Fieldm_Actor_dt(Actor* thisx, Game_Play* game_play);
void Fieldm_Actor_move(Actor* thisx, Game_Play* game_play);
void Fieldm_Actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Fieldm_Draw_Profile = {
    /* */ ACTOR_FIELDM_DRAW,
    /* */ ACTOR_PART_4,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Fieldm_Draw),
    /* */ Fieldm_Actor_ct,
    /* */ Fieldm_Actor_dt,
    /* */ Fieldm_Actor_move,
    /* */ Fieldm_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fieldm_Draw/ac_fieldm_draw/Fieldm_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fieldm_Draw/ac_fieldm_draw/Fieldm_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fieldm_Draw/ac_fieldm_draw/Fieldm_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Fieldm_Draw/ac_fieldm_draw/Fieldm_Actor_draw.s")
