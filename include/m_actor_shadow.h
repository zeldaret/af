#ifndef M_ACTOR_SHADOW_H
#define M_ACTOR_SHADOW_H

#include "ultra64.h"
#include "m_lib.h"

s32 mActorShadow_OperateScrollLimit(s32, s32, s32);
Gfx* mActorShadow_TileScroll2(u32 *, u32 *, s32, s32, s32, s32, s32, s32, u32 *, u32 *, s32, s32, s32, s32, s32, s32, GAME *);
void mActorShadow_AdjustRate(f32 *);
void mActorShadow_GetTimeAngleY_TimeAlpha(Shadow_Info*, Game_Play*);
void mActorShadow_GetGroundAverageAngle(Shadow_Info *);
void mActorShadow_GetDistanceRate(Shadow_Info *, f32);
f32 mActorShadow_GetAbsBigger(f32, f32);
void mActorShadow_RadiusScaleRate(Actor *, Shadow_Info *);
void mActorShadow_GetShadowTopPos_GetSlideS(Shadow_Info *);
Gfx* mActorShadow_SetTexScroll(Actor *, Shadow_Info *, Game *);
void mActorShadow_GetLastAlphaScale(f32 *, u8 *, Actor *, Shadow_Info *);
void mActorShadow_DrawActorShadow(Actor *, Shadow_Info *, Game_Play *, s32, xyz_t, f32);
void mActorShadow_GetShadowPosition(Actor *, xyz_t *);
s32 mActorShadow_GetShadowKind(void);
f32 mAc_GetShadowGroundY_NoneForce(const Shadow_Info *);
f32 mAc_GetShadowGroundY_Force(const Shadow_Info *);
void mAc_DecideShadowRadius_IamNotFish(Shadow_Info *, Actor *, f32 *);
void mAc_DecideShadowRadius_IamFish(Shadow_Info *, Actor *, f32 *);
void mAc_ActorShadowDraw_ShadowDrawFlagOff(Actor *, Game_Play *, s32, xyz_t, f32);
void mAc_ActorShadowDraw_ShadowDrawFlagOn(Actor *, Game_Play *, s32, xyz_t, f32);
void mAc_ActorShadowDraw(Actor *, Game_Play *, s32, xyz_t, f32);
void mActorShadow_SetForceShadowPos(Actor *, xyz_t *);
void mActorShadow_UnSetForceShadowPos(Actor *);
void mAc_NormalActorShadow(Actor *, Game_Play *, f32);
void mAc_UnagiActorShadow(Actor *, Game_Play *, xyz_t);
void mAc_ActorShadowCircle(Actor *, LightsN *, Game_Play *);
void mAc_ActorShadowEllipse(Actor *, LightsN *, Game_Play *);


#endif