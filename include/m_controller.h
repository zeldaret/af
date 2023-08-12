#ifndef M_CONTROLLER_H
#define M_CONTROLLER_H

#include "ultra64.h"

#define CHECK_BTN_ALL(state, combo) (~((state) | ~(combo)) == 0)
#define RESET_BUTTON 0x80

struct GameState;

void mCon_ct(struct GameState* gameState);
void mCon_dt(struct GameState* gameState);
// void mCon_calc();
// void mCon_main();
// void chkButton();
// void getButton();
// void chkTrigger();
// void getTrigger();
// void getJoystick_X();
// void getJoystick_Y();

#endif
