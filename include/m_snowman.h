#ifndef M_SNOWMAN_H
#define M_SNOWMAN_H

#include "ultra64.h"
#include "z64math.h"

#define SNOWMAN_SAVE_COUNT 3

typedef struct {
    /* 0x00 */ u8 exists;
    /* 0x01 */ u8 headSize;
    /* 0x02 */ u8 bodySize;
    /* 0x03 */ u8 score;
} SnowmanData; // size = 0x4

typedef struct {
    /* 0x00 */ s32 scale;
    /* 0x04 */ Vec3f position;
} SnowmanInfo; // size = 0x4

// void mSN_check_life();
// void mSN_ClearSnowmanData();
// void mSN_ClearSnowman();
// void mSN_MeltSnowman();
// void mSN_get_free_space();
// void func_800C8BC4_jp();
void mSN_decide_msg(void);
void mSN_snowman_init(void);

#endif
