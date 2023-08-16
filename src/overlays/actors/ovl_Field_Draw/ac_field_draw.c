#include "ac_field_draw.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Bg_Draw_Actor_ct(Actor* thisx, PlayState* play);
void Bg_Draw_Actor_dt(Actor* thisx, PlayState* play);
void Bg_Draw_Actor_move(Actor* thisx, PlayState* play);
void Bg_Draw_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Field_Draw_Profile = {
    /* */ 4,
    /* */ ACTOR_PART_5,
    /* */ 48,
    /* */ 0,
    /* */ 3,
    /* */ sizeof(Field_Draw),
    /* */ Bg_Draw_Actor_ct,
    /* */ Bg_Draw_Actor_dt,
    /* */ Bg_Draw_Actor_move,
    /* */ Bg_Draw_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_809347E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/Bg_Draw_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/Bg_Draw_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/Bg_Draw_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_80934B44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_80934B68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_80934BB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_80934C38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_80934CE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_80934E2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_80934E5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_80934EDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_809350C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/func_809356A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Field_Draw/ac_field_draw/Bg_Draw_Actor_draw.s")