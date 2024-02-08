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


s32 mActorShadow_OperateScrollLimit(s32 /*value*/, s32 /*step*/, s32 /*limit*/);
Gfx* mActorShadow_TileScroll2(u32* /*x1*/, u32* /*y1*/, s32 /*step1*/, s32 /*step2*/, s32 /*limit1*/, s32 /*limit2*/, s32 /*width1*/, s32 /*height1*/, u32* /*x2*/, u32* /*y2*/, s32 /*step3*/, s32 /*step4*/, s32 /*limit3*/, s32 /*limit4*/, s32 /*width2*/, s32 /*height2*/, Game* /*game*/);
void mActorShadow_AdjustRate(f32* /*rate*/);
void mActorShadow_GetTimeAngleY_TimeAlpha(ShadowInfo* /*shadow*/, Game_Play* /*play*/);
void mActorShadow_GetGroundAverageAngle(ShadowInfo* /*shadow*/);
void mActorShadow_GetDistanceRate(ShadowInfo* /*shadow*/, f32 /*rate*/);
f32 mActorShadow_GetAbsBigger(f32 /*a*/, f32 /*b*/);
void mActorShadow_RadiusScaleRate(Actor* /*actor*/, ShadowInfo* /*shadow*/);
void mActorShadow_GetShadowTopPos_GetSlideS(ShadowInfo* /*shadow*/);
Gfx* mActorShadow_SetTexScroll(Actor* /*actor*/, ShadowInfo* /*shadow*/, Game* /*game*/);
void mActorShadow_GetLastAlphaScale(f32* /*scale*/, u8* /*alpha*/, Actor* /*actor*/, ShadowInfo* /*shadow*/);
void mActorShadow_DrawActorShadow(Actor* actor, ShadowInfo* shadow, Game* game, f32 rad, s32 id, xyz_t ofs);
void mActorShadow_GetShadowPosition(Actor* /*actor*/, xyz_t* /*position*/);
s32 mActorShadow_GetShadowKind(void);
f32 mAc_GetShadowGroundY_NoneForce(ShadowInfo* /*shadow*/);
f32 mAc_GetShadowGroundY_Force(ShadowInfo* /*shadow*/);
void mAc_DecideShadowRadius_IamNotFish(ShadowInfo* /*shadow*/, Actor* /*actor*/, f32* /*radius*/);
void mAc_DecideShadowRadius_IamFish(ShadowInfo* /*shadow*/, Actor* /*actor*/, f32* /*radius*/);
void mAc_ActorShadowDraw_ShadowDrawFlagOff(Actor* /*actor*/, Game_Play* /*play*/, s32 /*arg2*/, xyz_t /*arg3*/, f32 /*arg6*/);
void mAc_ActorShadowDraw_ShadowDrawFlagOn(Actor* /*actor*/, Game_Play* /*play*/, s32 /*proc*/, xyz_t /*pos*/, f32 /*rate*/);
void mAc_ActorShadowDraw(Actor* /*actor*/, Game_Play* /*play*/, s32 /*arg2*/, xyz_t /*arg3*/, f32 /*arg6*/);
void mActorShadow_SetForceShadowPos(Actor* /*actor*/, xyz_t* /*pos*/);
void mActorShadow_UnSetForceShadowPos(Actor* /*actor*/);
void mAc_NormalActorShadow(Actor* /*actor*/, Game_Play* /*play*/, f32 /*rad*/);
void mAc_UnagiActorShadow(Actor* /*actor*/, Game_Play* /*play*/, xyz_t /*pos*/);
void mAc_ActorShadowCircle(Actor* /*actor*/, LightsN* /*lights*/, Game_Play* /*play*/);
void mAc_ActorShadowEllipse(Actor* /*actor*/, LightsN* /*lights*/, Game_Play* /*play*/);


#endif