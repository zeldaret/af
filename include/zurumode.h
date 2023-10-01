#ifndef ZURUMODE_H
#define ZURUMODE_H

#include "ultra64.h"

typedef struct zuru_keycheck {
    /* 0x0 */ u8 state;
    /* 0x1 */ u8 progressing;
    /* 0x2 */ u16 lastController;
    /* 0x4 */ u8 zurumodeEnabled;
} zuruKeycheck; // size = 0x6


enum zurumode_stage {
    /* 0 */ ZURUMODE_BEGIN_STAGE = 0,

    /* 0 */ ZURUMODE_STAGE_0 = ZURUMODE_BEGIN_STAGE,
    /* 1 */ ZURUMODE_STAGE_1,
    /* 2 */ ZURUMODE_STAGE_2,
    /* 3 */ ZURUMODE_STAGE_3,
    /* 4 */ ZURUMODE_STAGE_4,
    /* 5 */ ZURUMODE_STAGE_5,
    /* 6 */ ZURUMODE_STAGE_6,
    /* 7 */ ZURUMODE_STAGE_7,
    /* 8 */ ZURUMODE_STAGE_8,
    /* 9 */ ZURUMODE_STAGE_9,
    /* 91 */ ZURUMODE_STAGE_91 = 91,
    /* 92 */ ZURUMODE_STAGE_92 = 92,
    /* 10 */ ZURUMODE_STAGE_10 = 10,
    /* 11 */ ZURUMODE_STAGE_11,

    /* 11 */ ZURUMODE_STAGE_FINAL = ZURUMODE_STAGE_11
};

extern s32 zurumode_flag;

s32 zurumode_update(void);
s32 zerucheck_init(zuruKeycheck* keycheck);
s32 zerucheck_key_check(zuruKeycheck* keycheck, u16 controller);
void zurumode_callback(void* p);
void zurumode_init(void);
void zurumode_cleanup(void);

#endif
