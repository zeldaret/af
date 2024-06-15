#ifndef AC_AIRPLANE_H
#define AC_AIRPLANE_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Airplane;

typedef enum AirplaneState {
    /* 0 */ Ap_STATE_FREE_FLY_MOVE,
    /* 1 */ Ap_STATE_FALL_FLY_MOVE,
    /* 2 */ Ap_STATE_FALL_FLY_MOVE2,
    /* 3 */ Ap_STATE_SOMER_FLY_MOVE,
    /* 4 */ Ap_STATE_START_FLY_MOVE,
    /* 5 */ Ap_STATE_STOP_FLY_MOVE,
    /* 6 */ Ap_STATE_PLAYER_CATCH,
} AirplaneState;

typedef enum AirplaneTiltState {
    /* 0 */ Ap_TILT_DOWN,
    /* 1 */ Ap_TILT_UP,
} AirplaneTiltState;

typedef void (*AirplaneActionFunc)(struct Airplane*, struct Game_Play*);

typedef struct Airplane {
    /* 0x000 */ Actor actor;
    /* 0x174 */ s16 state;
    /* 0x176 */ s16 tiltState;
    /* 0x178 */ f32 speed;
    /* 0x17C */ f32 ySpeed;
    /* 0x180 */ f32 targetYRot;
    /* 0x184 */ f32 startYRot;
    /* 0x188 */ f32 yRot;
    /* 0x18C */ f32 xRot;
    /* 0x190 */ f32 zRot;
    /* 0x194 */ s32 joystickY;
    /* 0x198 */ s32 joystickX;
    /* 0x19C */ s16 groundTimer;
    /* 0x1A0 */ s32 windFrame;
    /* 0x1A4 */ s32 windChangeFrame;
    /* 0x1A8 */ xyz_t* wind;
    /* 0x1AC */ UNK_TYPE1 unk_1AC[0x1C];
} Airplane; // size = 0x1C8

#endif
