#include "ac_my_house.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_80A05D50_jp(Actor* thisx, Game_Play* game_play);
void func_80A05F88_jp(Actor* thisx, Game_Play* game_play);
void func_80A06DF0_jp(Actor* thisx, Game_Play* game_play);
void func_80A071A0_jp(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile MyHouse_Profile = {
    /* */ ACTOR_MY_HOUSE,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5800,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(MyHouse),
    /* */ func_80A05D50_jp,
    /* */ func_80A05F88_jp,
    /* */ func_80A06DF0_jp,
    /* */ func_80A071A0_jp,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A05D50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A05F88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06068_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06098_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A0612C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A061BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06284_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A063B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A064E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A0664C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A0668C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A066B4_jp.s")

// aMHS_make_bgOffset
// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A067D8_jp.s")
extern u8 D_80A07510_jp[];

typedef struct collision_offset_table_s {
    /* 0x00 */ u8 unit_attribute;
    /* 0x01 */ s8 centerRight_offset; 
    /* 0x02 */ s8 leftUp_offset;
    /* 0x03 */ s8 leftDown_offset;
    /* 0x04 */ s8 rightDown_offset;
    /* 0x05 */ s8 rightUp_offset;
    /* 0x06 */ s8 shape;
} mCoBG_OffsetTable_c; // size = 0x7

void func_80A067D8_jp(mCoBG_OffsetTable_c* arg0, s8 arg1, s32 arg2)
{
    s32 var_v0;
    s32 var_v1;
    s8 *var_a1;
    
    if (arg2 == 0)
    {
        var_v0 = 0;
    }
    else
    {
        var_v0 = 0x60;
    }

    for (var_v1 = 0; var_v1 != 16; var_v1++, arg0++)
    {
        var_a1 = &D_80A07510_jp[var_v0];
        arg0->unit_attribute = 0x64;
        if (var_a1[var_v1 * 6 + 0] != 0xB)
        {
            arg0->centerRight_offset = var_a1[var_v1 * 6 + 0];
        }
        else
        {
            arg0->centerRight_offset = arg1;
        }

        if (var_a1[var_v1 * 6 + 1] != 0xB)
        {
            arg0->leftUp_offset = var_a1[var_v1 * 6 + 1];
        }
        else
        {
            arg0->leftUp_offset = arg1;
        }

        if (var_a1[var_v1 * 6 + 2] != 0xB)
        {
            arg0->leftDown_offset = var_a1[var_v1 * 6 + 2];
        }
        else
        {
            arg0->leftDown_offset = arg1;
        }

        if (var_a1[var_v1 * 6 + 3] != 0xB)
        {
            arg0->rightDown_offset = var_a1[var_v1 * 6 + 3];
        }
        else
        {
            arg0->rightDown_offset = arg1;
        }

        if (var_a1[var_v1 * 6 + 4] != 0xB)
        {
            arg0->rightUp_offset = var_a1[var_v1 * 6 + 4];
        }
        else
        {
            arg0->rightUp_offset = arg1;
        }

        arg0->shape = var_a1[var_v1 * 6 + 5];
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A068AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06A58_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06AF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06B74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06BE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06CD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06CF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06DF0_jp.s")

// aMHS_actor_draw_before
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A06E64_jp.s")

// aMHS_actor_draw_after
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A07008_jp.s")

// aMHS_actor_draw
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_MyHouse/ac_my_house/func_80A071A0_jp.s")
