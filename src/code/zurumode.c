#include "zurumode.h"
#include "m_nmi_buf.h"
#include "padmgr.h"

zuruKeycheck zuruKeyCheck;

s32 zurumode_flag = 0;

s32 zurumode_update() {
    zurumode_flag = (APPNMI_ZURUMODE_GET()) ? ((APPNMI_ZURUMODE2_GET()) ? 2 : 1) : 0;

    return zurumode_flag;
}

s32 zerucheck_init(zuruKeycheck* keycheck) {
    keycheck->state = 0;
    keycheck->progressing = 0;
    keycheck->lastController = 0;
}

s32 zerucheck_key_check(zuruKeycheck* keycheck, u16 controller) {
    u32 controller_now = controller;
    s32 state = keycheck->state;
    s32 progressing = keycheck->progressing;
    u32 controller_new;

    if (state != ZURUMODE_STAGE_FINAL) {
        controller_new = (keycheck->lastController ^ controller_now) & controller_now;
        keycheck->lastController = controller_now;

        if ((controller == 0) && (progressing == 1)) {
            progressing = 0;
        } else if (controller_new != 0) {
            if (progressing == 1) {
                state = 0;
            }
            switch (state) {

                case ZURUMODE_STAGE_0:

                    if (controller_now == (R_TRIG | L_TRIG | Z_TRIG) && controller_new == Z_TRIG) {
                        state = ZURUMODE_STAGE_1;
                        progressing = 1;
                    }
                    break;

                case ZURUMODE_STAGE_1:

                    if (controller_new == U_JPAD) {
                        state = ZURUMODE_STAGE_2;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }

                    break;

                case ZURUMODE_STAGE_2:

                    if (controller_new == D_CBUTTONS) {
                        state = ZURUMODE_STAGE_3;
                        progressing = 1;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }
                    break;

                case ZURUMODE_STAGE_3:

                    if (controller_new == U_CBUTTONS) {
                        state = ZURUMODE_STAGE_4;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }

                    break;

                case ZURUMODE_STAGE_4:

                    if (controller_new == D_JPAD) {
                        state = ZURUMODE_STAGE_5;
                        progressing = 1;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }

                    break;

                case ZURUMODE_STAGE_5:

                    if (controller_new == L_JPAD) {
                        state = ZURUMODE_STAGE_6;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }
                    break;

                case ZURUMODE_STAGE_6:

                    if (controller_new == L_CBUTTONS) {
                        state = ZURUMODE_STAGE_7;
                        progressing = 1;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }

                    break;

                case ZURUMODE_STAGE_7:

                    if (controller_new == R_CBUTTONS) {
                        state = ZURUMODE_STAGE_8;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }
                    break;

                case ZURUMODE_STAGE_8:

                    if (controller_new == R_JPAD) {
                        state = ZURUMODE_STAGE_9;
                        progressing = 1;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }

                    break;

                case ZURUMODE_STAGE_9:

                    if (controller_new == (B_BUTTON | A_BUTTON)) {
                        state = ZURUMODE_STAGE_10;
                    } else if (controller_new == A_BUTTON) {
                        state = ZURUMODE_STAGE_91;
                    } else if (controller_new == B_BUTTON) {
                        state = ZURUMODE_STAGE_92;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }

                    break;

                case ZURUMODE_STAGE_91:

                    if (controller_new == B_BUTTON) {
                        state = ZURUMODE_STAGE_10;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }

                    break;

                case ZURUMODE_STAGE_92:

                    if (controller_new == A_BUTTON) {
                        state = ZURUMODE_STAGE_10;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }

                    break;

                case ZURUMODE_STAGE_10:

                    if (controller_new == START_BUTTON) {
                        state = ZURUMODE_STAGE_FINAL;
                    } else {
                        state = ZURUMODE_STAGE_0;
                    }

                    break;
            }
        }
    }

    keycheck->state = state;
    keycheck->progressing = progressing;

    return state == ZURUMODE_STAGE_FINAL;
}

void zurumode_callback(void* p) {
    Padmgr* mgr = p;

    if (zerucheck_key_check(&zuruKeyCheck, mgr->pads[1].button)) {
        zerucheck_init(&zuruKeyCheck);
        APPNMI_ZURUMODE_FLP();
        zurumode_update();
        if ((mgr->pads[0].button) & 0x80) {
            APPNMI_ZURUMODE3_FLP();
        }
    }
}

void zurumode_init() {
    zurumode_update();
    zerucheck_init(&zuruKeyCheck);
    PADMGR_SET_RETRACE_CALLACK(&zurumode_callback, &padmgr_class);
}

void zurumode_cleanup() {
    PADMGR_UNSET_RETRACE_CALLACK(&zurumode_callback, &padmgr_class);
    zurumode_flag = 0;
}
