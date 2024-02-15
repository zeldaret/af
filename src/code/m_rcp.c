#include "global.h"

void gfx_set_fog_position(Gfx** gfxP, s32 near, s32 far) {
    if (near == far) {
        gSPFogFactor((*gfxP)++, 0, 0);
    } else {
        gSPFogPosition((*gfxP)++, near, far);
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/gfx_set_fog_nosync.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD3EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD428_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD448_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD470_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD498_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD4C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/_texture_z_light_fog_prim.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/_texture_z_light_fog_prim_shadow.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD538_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/_texture_z_light_fog_prim_xlu.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD5C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/_texture_z_light_fog_prim_npc.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD68C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD6D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD6F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD720_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/rect_moji.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD7C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD804_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD8A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD9D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BD9FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/tex_scroll2.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/two_tex_scroll.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/DisplayList_initialize.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/fade_rgba8888_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE030_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/fade_black_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE094_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE0E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE12C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE184_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE1D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE27C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE320_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_rcp/func_800BE4F8_jp.s")
