#ifndef AUDIO_H
#define AUDIO_H

#include "ultra64.h"
#include "game.h"

struct xyz_t;
 
extern s32 S_ongenpos_refuse_fg;

void sAdo_Calc_MicPosition_common(f32*, u16*, struct xyz_t*);
void sAdo_Calc_MicPosition_forTrig(f32*, u16*, struct xyz_t*);
void sAdo_Calc_MicPosition_forLevel(f32*, u16*, struct xyz_t*);
void sAdo_GameFrame(void);
void func_800D19BC_jp(void);
void func_800D19DC_jp(void);
void sAdo_BgmStart(u8);
void sAdo_BgmStop(u16);
void sAdo_BgmTrOn(u8);
void sAdo_BgmTrOff(u8);
void sAdo_SysTrgStart(u16);
void sAdo_PlyWalkSe(s32, struct xyz_t*);
void sAdo_PlyWalkSeRoom(s32, struct xyz_t*);
void sAdo_NpcWalkSe(s32, struct xyz_t*);
void sAdo_NpcWalkSeRoom(u16, struct xyz_t*);
void sAdo_PlayerStatusLevel(u8, f32);
void sAdo_VoiceSe(u8, s16, u8);
void sAdo_Inst(u8, u8*);
void sAdo_MessageStatus(u8);
void sAdo_MessageSpeed(u8);
u8 sAdo_MessageSpeedGet(void);
void sAdo_SysLevStart(u8);
void sAdo_SysLevStop(u8);
void sAdo_OngenPos(s32, u8, struct xyz_t*);
void sAdo_OngenTrgStart(u16, struct xyz_t*);
void sAdo_SetOutMode(u8);
void sAdo_SetVoiceMode(u8);
void sAdo_FloorTrgStart(u8, struct xyz_t*);
void sAdo_RhythmStart(s32, s8, s8);
void sAdo_RhythmStop(void);
void sAdo_RhythmAllStop(void);
void sAdo_FurnitureInst(s32, u8, s32, struct xyz_t*);
void sAdo_Pause(u8);
f32 sAdo_get_rhythm_buffer(void);
s16 sAdo_GetRhythmSubTrack(void);
void sAdo_GetRhythmInfo(void*);
void sAdo_SetRhythmInfo(void*);
s32 sAdo_InstCountGet(void);
void sAdo_RhythmPos(s32, u8, struct xyz_t*);
void sAdo_SpecChange(s32);
void sAdo_MDPlayerPos(struct xyz_t*, u16, u16, s32);
void sAdo_BGMVolume(f32, u16);
void sAdo_BgmCrossfadeStart(u8);
void sAdo_SubGameStart(void);
void sAdo_SubGameEnd(void);
s32 sAdo_SubGameOK(void);
void sAdo_Tenki(u8);
void func_800D213C_jp(void);
void sAdos_KishaStatusTrg(u8);
void sAdos_KishaStatusLevel(f32, s32, f32, u16, s32, f32, u16);
s32 func_800D21CC_jp(void*);
void sAdos_GetStaffRollInfo(u16*);
void sAdos_TTKK_ARM(u8);
void sAdo_OngenTrgStartSpeed(u16, struct xyz_t*, f32);
void sAdo_TrgSeEcho(u8);
void sAdo_LevSeEcho(u8);
void sAdo_BGMFilter(u8);
void sAdo_BgmMuteClear(void);
u8 sAdo_BgmFadeoutCheck(void);
u8 sAdo_SeFadeoutCheck(void);
void sAdo_SeStart(s32);
void sAdo_SeStop(s32);
void sAdo_RoomType(u8);
void sAdo_SoftReset(void);
u16 sAdo_Get_WalkLabel(s32);
s32 sAdo_Get_KokeruLabel(s32);
void sAdo_SceneMode(u8);
void sAdo_RoomIncectPos(s32, u8, struct xyz_t*);
void sAdo_FurnitureInstPos(s32, struct xyz_t*);
void sAdo_Set_ongenpos_refuse_fg(s32);
s32 sAdo_GameframeEnd_Check(void);

#endif
