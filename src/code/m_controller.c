#include "m_controller.h"
#include "game.h"
#include "m_event.h"
#include "m_lib.h"
#include "sys_math_atan.h"
#include "attributes.h"

void mCon_ct(UNUSED GameState* game) {
}

void mCon_dt(UNUSED GameState* game) {
}

void mCon_calc(Controller* controller, f32 x, f32 y) {
    controller->lastMoveX = controller->moveX;
    controller->lastMoveY = controller->moveY;
    controller->lastMoveR = controller->moveR;

    controller->lastMoveAngle = controller->moveAngle;

    controller->lastAdjustedX = controller->adjustedX;
    controller->lastAdjustedY = controller->adjustedY;
    controller->lastAdjustedR = controller->adjustedR;

    {
        f32 r = sqrtf((x * x) + (y * y));

        if (r <= STICK_MIN) {
            controller->moveX = 0.0f;
            controller->moveY = 0.0f;
            controller->moveR = 0.0f;
            controller->adjustedX = 0.0f;
            controller->adjustedY = 0.0f;
            controller->adjustedR = 0.0f;
        } else {
            s16 theta = atans_table(x, y);

            if (r > STICK_MAX) {
                x = cos_s(theta) * STICK_MAX;
                y = sin_s(theta) * STICK_MAX;
                r = STICK_MAX;
            }

            controller->moveAngle = theta;
            { UNUSED s32 requiredScopeTemp; }
            controller->moveX = check_percent_abs(x, STICK_MIN, STICK_MAX, STICK_UNCORRECTED_SCALE, 0);
            controller->moveY = check_percent_abs(y, STICK_MIN, STICK_MAX, STICK_UNCORRECTED_SCALE, 0);
            controller->moveR = check_percent_abs(r, STICK_MIN, STICK_MAX, STICK_UNCORRECTED_SCALE, 0);

            controller->adjustedX = check_percent_abs(x, STICK_MIN, STICK_MAX, STICK_CORRECTED_SCALE, 1);
            controller->adjustedY = check_percent_abs(y, STICK_MIN, STICK_MAX, STICK_CORRECTED_SCALE, 1);
            controller->adjustedR = check_percent_abs(r, STICK_MIN, STICK_MAX, STICK_CORRECTED_SCALE, 1);
        }
    }
}

void mCon_main(GameState* game) {
    Controller* controller = &game->controller;
    f32 x = getJoystick_X();
    f32 y = getJoystick_Y();

    mCon_calc(controller, x, y);
}

s32 chkButton(u16 mask) {
    if (mEv_CheckTitleDemo() > 0) {
        return 0;
    } else {
        return mask == (CONTROLLER1(gamePT)->cur.button & mask);
    }
}

u16 getButton(void) {
    if (mEv_CheckTitleDemo() > 0) {
        return 0;
    } else {
        return CONTROLLER1(gamePT)->cur.button;
    }
}

s32 chkTrigger(u16 mask) {
    if (mEv_CheckTitleDemo() > 0) {
        return 0;
    } else {
        return mask == (CONTROLLER1(gamePT)->press.button & mask);
    }
}

u16 getTrigger(void) {
    if (mEv_CheckTitleDemo() > 0) {
        return 0;
    } else {
        return CONTROLLER1(gamePT)->press.button;
    }
}

s32 getJoystick_X(void) {
    if (mEv_CheckTitleDemo() > 0) {
        return 0;
    } else {
        return CONTROLLER1(gamePT)->cur.stick_x;
    }
}

s32 getJoystick_Y(void) {
    if (mEv_CheckTitleDemo() > 0) {
        return 0;
    } else {
        return CONTROLLER1(gamePT)->cur.stick_y;
    }
}
