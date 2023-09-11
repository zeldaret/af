#ifndef M_SNOWMAN_H
#define M_SNOWMAN_H

#include "ultra64.h"
#include "z64math.h"

#define SNOWMAN_SAVE_COUNT 3

typedef struct SnowmanData {
    /* 0x00 */ u8 exists;
    /* 0x01 */ u8 headSize;
    /* 0x02 */ u8 bodySize;
    /* 0x03 */ u8 unk3; //score
} SnowmanData; // size = 0x4

typedef struct SnowmanInfo {
    /* 0x00 */ s32 unk0; //scale
    /* 0x04 */ Vec3f position;
} SnowmanInfo; // size = 0x10

s32 mSN_check_life(u16* name, s32 daysElapsed);
void mSN_ClearSnowmanData(u16* name, s32 snowmanIndex);
s32 mSN_ClearSnowman(u16* name);
s32 mSN_MeltSnowman(u16* name, s32 daysElapsed);
s32 mSN_get_free_space(void);
void mSN_regist_snowman_society(SnowmanInfo* snowmanInfo);
void mSN_decide_msg(void);
void mSN_snowman_init(void);

#endif
