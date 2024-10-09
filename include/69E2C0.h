#ifndef C_69E2C0_H
#define C_69E2C0_H

#include "ultra64.h"
#include "color.h"

struct Input;
struct GraphicsContext;
struct Game_Play;
struct Actor;

// void func_8007A620_jp();
// void func_8007A630_jp();
// void Debug_Print_output();
// void func_8007A74C_jp();
// void Debug_Print2_output();
void Debug_mode_input(struct Input *input);
// void Debug_mode_output_sub();
// void Debug_mode_zelda_malloc_info_output();
void Debug_mode_output(struct GraphicsContext* gfxCtx);

#endif
