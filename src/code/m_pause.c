#include "m_pause.h"
#include "m_controller.h"
#include "libc/stdbool.h"

void Pause_ct(Pause* pause) {
    pause->timer = 0;
    pause->enabled = 0;
}

s32 Pause_proc(Pause* pause, Input* input) {
    if (CHECK_BTN_ALL(input->cur.button, R_TRIG) && CHECK_BTN_ALL(input->press.button, D_JPAD)) {
        pause->enabled = !pause->enabled;
    }

    if ((!pause->enabled) || (CHECK_BTN_ALL(input->cur.button, Z_TRIG) &&
                              (CHECK_BTN_ALL(input->press.button, R_TRIG) ||
                               (CHECK_BTN_ALL(input->cur.button, R_TRIG) && (++pause->timer >= 9))))) {
        pause->timer = 0;
        return true;
    }
    return false;
}
