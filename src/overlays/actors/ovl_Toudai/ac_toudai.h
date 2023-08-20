#ifndef AC_TOUDAI_H
#define AC_TOUDAI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "z64math.h"
#include "c_keyframe.h"

struct Toudai;
struct Game_Play;

typedef void (*ToudaiActionFunc)(struct Toudai*, struct Game_Play*);

//TODO: replace with the ac_structure struct
typedef struct Toudai {
    /* 0x000 */ Actor actor;
    /* 0x174 */ s32 unk174;
    /* 0x178 */ SkeletonInfoR skeletonInfo;
    /* 0x1E8 */ s32 unk1E8;
    /* 0x1EC */ Vec3s jointTable[15];
    /* 0x246 */ Vec3s morphTable[15];
    /* 0x2A0 */ ToudaiActionFunc unk2A0;
    /* 0x2A4 */ UNK_TYPE1 unk2A4[0x10];
    /* 0x2B4 */ UNK_TYPE unk2B4;
    /* 0x2B8 */ UNK_TYPE1 unk2B8[0x4];
    /* 0x2BC */ UNK_TYPE unk2BC;
    /* 0x2C0 */ UNK_TYPE1 unk2C0[0x8];
    /* 0x2C8 */ f32 unk2C8;
    /* 0x2CC */ f32 unk2CC;
    /* 0x2D0 */ f32 unk2D0;
    /* 0x2D4 */ UNK_TYPE1 unk2D4[0x4];
} Toudai; // size = 0x2D8

void aTOU_set_bgOffset(Toudai* this, s32 heightTableIndex);
void aTOU_init(Toudai* this, struct Game_Play* game_play);
void aTOU_wait(Toudai* this, struct Game_Play* game_play);
void aTOU_lighting(Toudai* this, struct Game_Play* game_play);
void aTOU_lightout(Toudai* this, struct Game_Play* game_play);
void aTOU_setup_action(Toudai* this, s32 processIndex);

#endif
