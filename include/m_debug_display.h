#ifndef M_DEBUG_DISPLAY_H
#define M_DEBUG_DISPLAY_H

#include "ultra64.h"

struct PlayState;

void Debug_Display_init(void);
// void Debug_Display_new();
void Debug_Display_output(struct PlayState* play);
// void debug_display_output_sprite_16x16_I8();
// void debug_display_output_polygon();

#endif
