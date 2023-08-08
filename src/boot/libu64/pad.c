#include "libu64/pad.h"

void pad_init(Input* input) {
    bzero(input, sizeof(Input));
}

void pad_cleanup(void) {
}

void pad_flush(Input* input) {
    input->press.button = 0;
    input->rel.button = 0;
}

s32 pad_push_only(Input* input, u16 value) {
    return value == input->cur.button;
}

s32 pad_push_also(Input* input, u16 key) {
    return key == (input->cur.button & key);
}

s32 pad_on_trigger(Input* input, u16 key) {
    return key == (input->press.button & key);
}

s32 pad_off_trigger(Input* input, u16 key) {
    return key == (input->rel.button & key);
}

u16 pad_button(Input* input) {
    return input->cur.button;
}

u16 pad_trigger(Input* input) {
    return input->press.button;
}

s8 pad_physical_stick_x(Input* input) {
    return input->cur.stick_x;
}

s8 pad_physical_stick_y(Input* input) {
    return input->cur.stick_y;
}

void pad_set_logical_stick(Input* input, s32 x, s32 y) {
    input->rel.stick_x = x;
    input->rel.stick_y = y;
}

s8 pad_logical_stick_x(Input* input) {
    return input->rel.stick_x;
}

s8 pad_logical_stick_y(Input* input) {
    return input->rel.stick_y;
}

s8 pad_stick_x(Input* input) {
    return pad_logical_stick_x(input);
}

s8 pad_stick_y(Input* input) {
    return pad_logical_stick_y(input);
}

void pad_correct_stick(Input* input) {
    s32 curX = pad_physical_stick_x(input);
    s32 curY = pad_physical_stick_y(input);
    s32 relX;
    s32 relY;

    if (curX > 7) {
        relX = (curX < 0x43) ? curX - 7 : 0x43 - 7;
    } else if (curX < -7) {
        relX = (curX > -0x43) ? curX + 7 : -0x43 + 7;
    } else {
        relX = 0;
    }

    if (curY > 7) {
        relY = (curY < 0x43) ? curY - 7 : 0x43 - 7;

    } else if (curY < -7) {
        relY = (curY > -0x43) ? curY + 7 : -0x43 + 7;
    } else {
        relY = 0;
    }

    pad_set_logical_stick(input, relX, relY);
}
