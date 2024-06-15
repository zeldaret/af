#ifndef M_DEBUG_DISPLAY_H
#define M_DEBUG_DISPLAY_H

#include "ultra64.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "z64math.h"
#include "color.h"

struct Game_Play;

typedef struct DebugDispObject {
    /* 0x00 */ xyz_t pos;
    /* 0x0C */ s_xyz rot;
    /* 0x14 */ xyz_t scale;
    /* 0x20 */ Color_RGBA8 color;
    /* 0x24 */ s16 type;
    /* 0x28 */ struct DebugDispObject* next;
} DebugDispObject; // size = 0x30

void Debug_Display_init(void);
DebugDispObject* Debug_Display_new(f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, f32 scaleX, f32 scaleY,
                                   f32 scaleZ, u8 red, u8 green, u8 blue, u8 alpha, s16 type, GraphicsContext* gfxCtx);
void Debug_Display_output(Game_Play* game_play);
void debug_display_output_sprite_16x16_I8(DebugDispObject* dispObj, void* texture, Game_Play* game_play);
void debug_display_output_polygon(DebugDispObject* dispObj, void* dList, Game_Play* game_play);

#endif
