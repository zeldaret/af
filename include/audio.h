#ifndef AUDIO_H
#define AUDIO_H

#include "ultra64.h"
#include "game.h"
#include "m_std_dma.h"

struct xyz_t;
 
extern s32 S_ongenpos_refuse_fg;

void sAdo_Calc_MicPosition_common(f32* distanceVal, u16* angleVal, struct xyz_t* pos);
void sAdo_Calc_MicPosition_forTrig(f32* distanceVal, u16* angleVal, struct xyz_t* pos);
void sAdo_Calc_MicPosition_forLevel(f32* distanceVal, u16* angleVal, struct xyz_t* pos);
void sAdo_GameFrame(void);
void* func_800D19BC_jp(void);
void func_800D19DC_jp(void);
void sAdo_BgmStart(u8 id);
void sAdo_BgmStop(u16 id);
void sAdo_BgmTrOn(u8 id);
void sAdo_BgmTrOff(u8 id);
void sAdo_SysTrgStart(u16 id);
void sAdo_PlyWalkSe(s32 arg0, struct xyz_t* pos);
void sAdo_PlyWalkSeRoom(s32 arg0, struct xyz_t* pos);
void sAdo_NpcWalkSe(s32 arg0, struct xyz_t* pos);
void sAdo_NpcWalkSeRoom(u16 arg0, struct xyz_t* pos);
void sAdo_PlayerStatusLevel(u8 arg0, f32 speed);
void sAdo_VoiceSe(u8 arg0, s16 arg1, u8 arg2);
void sAdo_Inst(u8 num, u8* arg1);
void sAdo_MessageStatus(u8 status);
void sAdo_MessageSpeed(u8 speed);
u8 sAdo_MessageSpeedGet(void);
void sAdo_SysLevStart(u8 id);
void sAdo_SysLevStop(u8 id);
void sAdo_OngenPos(s32 arg0, u8 arg1, struct xyz_t* pos);
void sAdo_OngenTrgStart(u16 id, struct xyz_t* pos);
void sAdo_SetOutMode(u8 mode);
void sAdo_SetVoiceMode(u8 mode);
void sAdo_FloorTrgStart(u8 id, struct xyz_t* pos);
void sAdo_RhythmStart(s32 arg0, s8 arg1, s8 arg2);
void sAdo_RhythmStop(void);
void sAdo_RhythmAllStop(void);
void sAdo_FurnitureInst(s32 distance, u8 trackId, s32 arg2, struct xyz_t* pos);
void sAdo_Pause(u8 mode);
f32 sAdo_get_rhythm_buffer(void);
s16 sAdo_GetRhythmSubTrack(void);
void sAdo_GetRhythmInfo(void* arg0);
void sAdo_SetRhythmInfo(void* arg0);
s32 sAdo_InstCountGet(void);
void sAdo_RhythmPos(s32 distance, u8 arg1, struct xyz_t* pos);
void sAdo_SpecChange(s32 spec);
void sAdo_MDPlayerPos(struct xyz_t* pos, u16 arg1, u16 arg2, s32 arg3);
void sAdo_BGMVolume(f32 volume, u16 pan);
void sAdo_BgmCrossfadeStart(u8 arg0);
void sAdo_SubGameStart(void);
void sAdo_SubGameEnd(void);
s32 sAdo_SubGameOK(void);
void sAdo_Tenki(u8 mode);
void func_800D213C_jp(DmaHandler handler);
void sAdos_KishaStatusTrg(u8 state);
void sAdos_KishaStatusLevel(f32 arg0, s32 arg1, f32 arg2, u16 arg3, s32 arg4, f32 arg5, u16 arg6);
s32 func_800D21CC_jp(void* arg0);
void sAdos_GetStaffRollInfo(u16* arg0);
void sAdos_TTKK_ARM(u8 arg0);
void sAdo_OngenTrgStartSpeed(u16 num, struct xyz_t* pos, f32 speed);
void sAdo_TrgSeEcho(u8 idx);
void sAdo_LevSeEcho(u8 idx);
void sAdo_BGMFilter(u8 arg0);
void sAdo_BgmMuteClear(void);
u8 sAdo_BgmFadeoutCheck(void);
u8 sAdo_SeFadeoutCheck(void);
void sAdo_SeStart(s32 arg0);
void sAdo_SeStop(s32 arg0);
void sAdo_RoomType(u8 type);
void sAdo_SoftReset(void);
u16 sAdo_Get_WalkLabel(s32 type);
s32 sAdo_Get_KokeruLabel(s32 type);
void sAdo_SceneMode(u8 mode);
void sAdo_RoomIncectPos(s32 distance, u8 insectId, struct xyz_t* pos);
void sAdo_FurnitureInstPos(s32 distance, struct xyz_t* pos);
void sAdo_Set_ongenpos_refuse_fg(s32 state);
s32 sAdo_GameframeEnd_Check(void);

#endif
