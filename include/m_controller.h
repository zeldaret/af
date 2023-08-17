#ifndef M_CONTROLLER_H
#define M_CONTROLLER_H

#include "ultra64.h"

#define CHECK_BTN_ALL(state, combo) (~((state) | ~(combo)) == 0)
#define RESET_BUTTON 0x80

#define STICK_MIN 9.899495f
#define STICK_MAX 61.0f
#define STICK_UNCORRECTED_SCALE (1.0f / STICK_MAX)
#define STICK_CORRECTED_SCALE (1.0f / (STICK_MAX - STICK_MIN))

typedef struct Controller {
    /* 0x00 */ f32 moveX;
    /* 0x04 */ f32 moveY;
    /* 0x08 */ f32 moveR;
    /* 0x0C */ s16 moveAngle;

    /* 0x10 */ f32 lastMoveX;
    /* 0x14 */ f32 lastMoveY;
    /* 0x18 */ f32 lastMoveR;
    /* 0x1C */ s16 lastMoveAngle;

    /* 0x20 */ f32 adjustedX;
    /* 0x24 */ f32 adjustedY;
    /* 0x28 */ f32 adjustedR;
  
    /* 0x2C */ f32 lastAdjustedX;
    /* 0x30 */ f32 lastAdjustedY;
    /* 0x34 */ f32 lastAdjustedR;
} Controller; // size = 0x38

struct Game;

void mCon_ct(struct Game* gameState);
void mCon_dt(struct Game* gameState);
void mCon_calc(Controller* controller, f32 x, f32 y);
void mCon_main(struct Game* game);
s32 chkButton(u16 mask);
u16 getButton(void);
s32 chkTrigger(u16 mask);
u16 getTrigger(void);
s32 getJoystick_X(void);
s32 getJoystick_Y(void);

#endif
