#include "ac_radio.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aRAD_actor_ct(Actor* thisx, Game_Play* game_play);
void func_80A76958_jp(Actor* thisx, Game_Play* game_play);
void aRAD_actor_init(Actor* thisx, Game_Play* game_play);
void aRAD_actor_draw(Actor* thisx, Game_Play* game_play);

void func_80A76A30_jp(Radio* this, Game_Play* game_play);

/* original `.data` order:
 * - Radio_Profile
 * - aRAD_shadow_vtx_fix_flg_table
 * - aRAD_shadow_data
 * - aRAD_clip_offset
 * - aRAD_processes
 */

ActorProfile Radio_Profile = {
    /* */ ACTOR_RADIO,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x582B,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Radio),
    /* */ aRAD_actor_ct,
    /* */ func_80A76958_jp,
    /* */ aRAD_actor_init,
    /* */ aRAD_actor_draw,
    /* */ NULL,
};

extern Vtx aRAD_shadow_vertices[];
extern Gfx aRAD_shadow_model[];

static u8 aRAD_shadow_vtx_fix_flg_table[] = { 1, 0, 0, 1, 0, 1, 1, 0 };
static ShadowData aRAD_shadow_data = { 0x00000008, aRAD_shadow_vtx_fix_flg_table, 60.0f, aRAD_shadow_vertices,
                                       aRAD_shadow_model };

extern Gfx aRAD_model[];

static xyz_t aRAD_clip_offset = { 2.0f, 0.0f, -10.0f };
static RadioActionFunc aRAD_processes[] = { func_80A76A30_jp };

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/aRAD_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/func_80A76958_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/func_80A769E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/func_80A76A30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/func_80A76B2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/func_80A76B4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/aRAD_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Radio/ac_radio/aRAD_actor_draw.s")
