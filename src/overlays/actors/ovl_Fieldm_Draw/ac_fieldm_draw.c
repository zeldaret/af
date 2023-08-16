#include "ac_fieldm_draw.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Fieldm_Actor_ct(Actor* thisx, PlayState* play);
void Fieldm_Actor_dt(Actor* thisx, PlayState* play);
void Fieldm_Actor_move(Actor* thisx, PlayState* play);
void Fieldm_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Fieldm_Draw_Profile = {
    /* */ 3,
    /* */ ACTOR_PART_4,
    /* */ 0,
    /* */ 0,
    /* */ 3,
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
