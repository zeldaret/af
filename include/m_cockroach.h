#ifndef M_COCKROACH_H
#define M_COCKROACH_H

#include "ultra64.h"
#include "m_home.h"

#define mCkRh_MAX_NUM 10
#define mCkRh_MAX_LOOK_NUM 3

s32 mCkRh_GokiFamilyCount2Good(s32 count);
s32 mCkRh_InitGokiSaveData_1Room(s32 player);
void mCkRh_InitGokiSaveData_1Room_ByHomeData(mHm_hs_c * home);
void mCkRh_InitGokiSaveData_InitNewPlayer(void);
void mCkRh_SavePlayTime(s32 player);
s32 mCkRh_DaysGapCompareWithSaveTime(s32 player);
void mCkRh_DecideNowGokiFamilyCount(s32 player);
s32 mCkRh_PlussGokiN_NowRoom(s32 count);
s32 mCkRh_MinusGokiN_NowRoom(s32 count);
s32 mCkRh_NowSceneGokiFamilyCount(void);
void mCkRh_InitCanLookGokiCount(void);
s32 mCkRh_CalcCanLookGokiCount(s32 count);
s32 mCkRh_GetCanLookGokiCount(void);

#endif
