#ifndef PAD_UTILS_H
#define PAD_UTILS_H

#include "ultra64.h"

typedef struct Input {
    /* 0x00 */ OSContPad cur;
    /* 0x06 */ OSContPad prev;
    /* 0x0C */ OSContPad press; // X/Y store delta from last frame
    /* 0x12 */ OSContPad rel; // X/Y store adjusted
} Input; // size = 0x18

void pad_init(Input* input);
void pad_cleanup(void);
void pad_flush(Input* input);
s32 pad_push_only(Input* input, u16 value);
s32 pad_push_also(Input* input, u16 key);
s32 pad_on_trigger(Input* input, u16 key);
s32 pad_off_trigger(Input* input, u16 key);
u16 pad_button(Input* input);
u16 pad_trigger(Input* input);
s8 pad_physical_stick_x(Input* input);
s8 pad_physical_stick_y(Input* input);
void pad_set_logical_stick(Input* input, s32 x, s32 y);
s8 pad_logical_stick_x(Input* input);
s8 pad_logical_stick_y(Input* input);
s8 pad_stick_x(Input* input);
s8 pad_stick_y(Input* input);
void pad_correct_stick(Input* input);

#endif
