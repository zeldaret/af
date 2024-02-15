#ifndef C_6E0F50_H
#define C_6E0F50_H

#include "ultra64.h"

struct GraphicsContext;
struct Game_Play;

extern Gfx RSP_RDP_clear_data[];

Gfx* gfx_set_fog_nosync(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
Gfx* func_800BD428_jp(Gfx* gfx, s32 i);
Gfx* func_800BD448_jp(Gfx* gfx);
void func_800BD470_jp(struct GraphicsContext* gfxCtx);
void func_800BD498_jp(struct GraphicsContext* gfxCtx);
void func_800BD4C0_jp(struct GraphicsContext* gfxCtx);
void _texture_z_light_fog_prim(struct GraphicsContext *gfxCtx);
void _texture_z_light_fog_prim_shadow(struct GraphicsContext* gfxCtx); 
void _texture_z_light_fog_prim_npc_shadow(struct GraphicsContext* gfxCtx);
void _texture_z_light_fog_prim_xlu(struct GraphicsContext* gfxCtx);
void _texture_z_light_fog_prim_light(struct GraphicsContext* gfxCtx);
void _texture_z_light_fog_prim_npc(struct GraphicsContext *gfxCtx);
Gfx* texture_z_light_fog_prim_bb_pal_opa(Gfx* gfx);
Gfx* texture_z_light_fog_prim_bb_pal_xlu(Gfx* gfx);
Gfx* texture_z_fog_lod_alpha_shadow(Gfx* gfx);
void func_800BD6F8_jp(struct GraphicsContext* gfxCtx);
Gfx* gfx_rect_moji(Gfx* gfx);
void rect_moji(struct GraphicsContext*);
// void func_800BD770_jp();
// void func_800BD798_jp();
Gfx* func_800BD7C0_jp(Gfx* gfx);
// void func_800BD804_jp();
// void func_800BD8A8_jp();
// void func_800BD9D8_jp();
// void func_800BD9FC_jp();
Gfx* tex_scroll2(struct GraphicsContext* gfxCtx, u32 x, u32 y, s32 width, s32 height);
extern Gfx* two_tex_scroll(struct GraphicsContext* gfxCtx, s32 tile1, s32 x1, s32 y1, s32 width1, s32 height1, s32 tile2, s32 x2, s32 y2, s32 width2, s32 height2);
void DisplayList_initialize(struct GraphicsContext* gfxCtx, u8 arg1, u8 arg2, u8 arg3, struct Game_Play* game_play);
void fade_rgba8888_draw(Gfx** gfx, s32 arg1);
// void func_800BE030_jp();
// void fade_black_draw();
// void func_800BE094_jp();
// void func_800BE0E4_jp();
Gfx *func_800BE12C_jp(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
// void func_800BE184_jp();
// void func_800BE1D4_jp();
// void func_800BE27C_jp();
Gfx* func_800BE320_jp(Gfx*, s32, s32, s32, s32, s32, s32, s32, s32, s32);
// void func_800BE4F8_jp();

#endif
