#ifndef C_71A140_H
#define C_71A140_H

#include "ultra64.h"
#include "other_types.h"

typedef struct AudioTask {
    /* 0x00 */ OSTask task;
    /* 0x40 */ OSMesgQueue* taskQueue;
    /* 0x44 */ void* unk_44; // probably a message that gets unused.
    /* 0x48 */ char unk_48[0x8];
} AudioTask; // size = 0x50


// void func_800F64A0_jp();
// void func_800F65F4_jp();
// void func_800F6644_jp();
// void func_800F67AC_jp();
// void func_800F6884_jp();
// void func_800F695C_jp();
// void func_800F6A20_jp();
// void func_800F6AA4_jp();
// void func_800F6B0C_jp();
// void func_800F6B34_jp();
// void func_800F6BB4_jp();
// void func_800F6BF8_jp();
// void func_800F6FCC_jp();
// void func_800F7078_jp();
// void func_800F70B0_jp();
// void func_800F70E8_jp();
// void func_800F71A0_jp();
// void func_800F7288_jp();
// void func_800F755C_jp();
// void func_800F7620_jp();
// void func_800F76CC_jp();
// void func_800F7810_jp();
// void func_800F7870_jp();
// void func_800F7A24_jp();
// void func_800F7A7C_jp();
// void func_800F7DA0_jp();
// void func_800F8024_jp();
// void func_800F8164_jp();
// void func_800F83E4_jp();
// void func_800F8440_jp();
// void func_800F8448_jp();
// void func_800F84AC_jp();
// void func_800F85B4_jp();
// void func_800F85D0_jp();
// void func_800F86B8_jp();
// void func_800F87A4_jp();
// void func_800F8814_jp();
// void func_800F8848_jp();
// void func_800F8850_jp();
// void func_800F88BC_jp();
void func_800F88E8_jp(void*,void*, RomOffset, RomOffset, RomOffset);
void* func_800F8984_jp(void);
void Na_GameFrame(void);
void func_800F8B2C_jp(void);
void Na_SoftReset(void);
// void func_800F8C94_jp();
void Na_Tenki(u8);
void Na_BgmStart(u8 id);
void Na_BgmCrossfadeStart(u8);
void Na_BgmStop(u16 id);
void Na_SysTrgStart(u16 id);
// void func_800F8E24_jp();
void Na_PlyWalkSe(u16, u16, f32);
void Na_PlyWalkSeRoom(u8, u16, f32);
void Na_NpcWalkSe(u16, u16, f32);
void Na_NpcWalkSeRoom(u8, u16, f32);
void Na_PlayerStatusLevel(u8 arg0, f32 speed);
void Na_VoiceSe(u8 arg0, s16 arg1, u8 arg2);
void Na_Inst(u16, u8*);
void Na_MessageStatus(u8);
void Na_MessageSpeed(u8);
u8 Na_MessageSpeedGet(void);
void Na_OngenPos(s32,u8,u16,f32);
// void func_800FA0AC_jp();
// void func_800FA2E0_jp();
void Na_OngenTrgStartSpeed(u16,u16,f32,f32);
void Na_OngenTrgStart(u16,u16,f32);
void Na_SetOutMode(u8);
void Na_SetVoiceMode(u8);
void Na_FloorTrgStart(u8,u16,f32);
void Na_SysLevStart(u8);
void Na_SysLevStop(u8);
void Na_Pause(u8);
void Na_RhythmPos(s32,u8,u16,f32);
void Na_SpecChange(s32);
void Na_MDPlayerPos(u16,f32,u16,s32, s32);
void Na_BGMVolume(f32,u16);
void Na_SubGameStart(void);
void Na_SubGameEnd(void);
u8 Na_SubGameOK(void);
void Na_KishaStatusTrg(u8);
void Na_KishaStatusLevel(f32 arg0, s32 arg1, u16 arg2, f32 arg3,s32 arg4, u16 arg5, f32 arg6);
void Na_TTKK_ARM(u8);
void Na_BgmMuteClear(void);
u8 Na_BgmFadeoutCheck(void);
u8 Na_SeFadeoutCheck(void);
void Na_BgmTrOn(u8 id);
void Na_BgmTrOff(u8 id);
void Na_SceneMode(u8);
void Na_RoomIncectPos(s32,u16,u16,f32);
void Na_FurnitureInstPos(s32,u16,f32);
void Na_TrgSeEcho(u8);
void Na_LevSeEcho(u8);
void Na_BGMFilter(u8);
void Na_RoomType(u8);

#endif
