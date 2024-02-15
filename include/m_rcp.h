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
void texture_z_light_prim_xlu_disp(struct GraphicsContext* gfxCtx);
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
void rect_moji(struct GraphicsContext* gfxCtx);
void polygon_z_light_prim(struct GraphicsContext* gfxCtx);
void softsprite_prim(struct GraphicsContext* gfxCtx);
Gfx* gfx_softsprite_prim_xlu(Gfx* gfx);
Gfx* gfx_tex_scroll2(Gfx** gfxP, u32 x, u32 y, s32 width, s32 height);
Gfx* gfx_two_tex_scroll(Gfx** gfxP, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2, s32 width2, s32 height2);
Gfx* func_800BD9D8_jp(Gfx** gfxP, u32 x, u32 y);
Gfx* func_800BD9FC_jp(struct GraphicsContext* gfxCtx, u32 x, u32 y);
Gfx* tex_scroll2(struct GraphicsContext* gfxCtx, u32 x, u32 y, s32 width, s32 height);
extern Gfx* two_tex_scroll(struct GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2, s32 width2, s32 height2);
void DisplayList_initialize(struct GraphicsContext* gfxCtx, u8 clearR, u8 clearG, u8 clearB, struct Game_Play* game_play);
void fade_rgba8888_draw(Gfx** gfxP, u32 color);
void func_800BE030_jp(Gfx** gfxP, u32 r, u32 g, u32 b, u32 a);
void fade_black_draw(Gfx** gfxP, u32 color);
Gfx* gfx_gDPFillRectangle1(Gfx* gfx, s32 ulx, s32 uly, s32 lrx, s32 lry);
void func_800BE0E4_jp(Gfx** gfxP, s32 ulx, s32 uly, s32 lrx, s32 lry);
Gfx* gfx_gDPFillRectangleF(Gfx* gfx, s32 ulx, s32 uly, s32 lrx, s32 lry);
void func_800BE184_jp(Gfx** gfxP, s32 ulx, s32 uly, s32 lrx, s32 lry);
// void func_800BE1D4_jp();
// void func_800BE27C_jp();
Gfx* func_800BE320_jp(Gfx*, s32, s32, s32, s32, s32, s32, s32, s32, s32);
// void func_800BE4F8_jp();

#endif
