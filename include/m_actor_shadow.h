#ifndef M_ACTOR_SHADOW_H
#define M_ACTOR_SHADOW_H

#include "ultra64.h"
#include "m_lib.h"

typedef struct ShadowInfo{
    /* 0x00 */ xyz_t position;
    /* 0x0C */ f32 groundY;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24; 
    /* 0x26 */ s16 unk26;
    /* 0x28 */ char pad28[0xC];
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 kind;
}ShadowInfo;


s32 mActorShadow_OperateScrollLimit(s32, s32, s32);
Gfx* mActorShadow_TileScroll2(u32*, u32*, s32, s32, s32, s32, s32, s32, u32*, u32*, s32, s32, s32, s32, s32, s32, Game*);
void mActorShadow_AdjustRate(f32*);
void mActorShadow_GetTimeAngleY_TimeAlpha(ShadowInfo*, Game_Play*);
void mActorShadow_GetGroundAverageAngle(ShadowInfo*);
void mActorShadow_GetDistanceRate(ShadowInfo*, f32);
f32 mActorShadow_GetAbsBigger(f32, f32);
void mActorShadow_RadiusScaleRate(Actor*, ShadowInfo*);
void mActorShadow_GetShadowTopPos_GetSlideS(ShadowInfo*);
Gfx* mActorShadow_SetTexScroll(Actor*, ShadowInfo*, Game*);
void mActorShadow_GetLastAlphaScale(f32*, u8*, Actor*, ShadowInfo*);
void mActorShadow_DrawActorShadow(Actor* actor, ShadowInfo* shadow, Game* game, f32 rad, s32 id, xyz_t ofs);
void mActorShadow_GetShadowPosition(Actor*, xyz_t*);
s32 mActorShadow_GetShadowKind(void);
f32 mAc_GetShadowGroundY_NoneForce(ShadowInfo*);
f32 mAc_GetShadowGroundY_Force(ShadowInfo*);
void mAc_DecideShadowRadius_IamNotFish(ShadowInfo*, Actor*, f32*);
void mAc_DecideShadowRadius_IamFish(ShadowInfo*, Actor*, f32*);
void mAc_ActorShadowDraw_ShadowDrawFlagOff(Actor*, Game_Play*, s32, xyz_t, f32);
void mAc_ActorShadowDraw_ShadowDrawFlagOn(Actor*, Game_Play*, s32, xyz_t, f32);
void mAc_ActorShadowDraw(Actor*, Game_Play*, s32, xyz_t, f32);
void mActorShadow_SetForceShadowPos(Actor*, xyz_t*);
void mActorShadow_UnSetForceShadowPos(Actor*);
void mAc_NormalActorShadow(Actor*, Game_Play*, f32);
void mAc_UnagiActorShadow(Actor*, Game_Play*, xyz_t);
void mAc_ActorShadowCircle(Actor*, LightsN*, Game_Play*);
void mAc_ActorShadowEllipse(Actor*, LightsN*, Game_Play*);


#endif