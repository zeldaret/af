#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "ultra64.h"
#include "lb_rtc.h"
#include "m_event.h"
#include "m_field_make.h"
#include "m_home.h"
#include "m_land.h"
#include "m_mail.h"
#include "m_npc.h"
#include "m_npc_walk.h"
#include "m_npc_schedule.h"
#include "m_private.h"
#include "m_quest.h"
#include "unk.h"
#include "m_snowman.h"
#include "m_clip.h"
#include "m_scene.h"
#include "m_demo.h"

typedef enum Season {
    /* 0 */ SPRING,
    /* 1 */ SUMMER,
    /* 2 */ FALL,
    /* 3 */ WINTER
} Season;

typedef struct Time {
    /* 0x00 */ u32 season;
    /* 0x04 */ u32 termIdx;
    /* 0x08 */ s16 bgitemProfile;
    /* 0x0A */ s16 bgitemBank;
    /* 0x0C */ s32 nowSec;
    /* 0x10 */ lbRTC_time_c rtcTime;
    /* 0x18 */ s16 radMin;
    /* 0x1A */ s16 radHour;
    /* 0x1C */ u8 timeSignal;
    /* 0x1D */ u8 underSec;
    /* 0x1E */ u8 disp;
    /* 0x1F */ u8 rtcCrashed;
    /* 0x20 */ s32 rtcEnabled;
    /* 0x24 */ s32 addSec;
    /* 0x28 */ s32 addIdx;
} Time; // size = 0x2C

typedef struct FamicomEmuCommonData {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
} FamicomEmuCommonData; // size >= 0x26

typedef struct Save {
    /* 0x00000 */ u8 unk_00000[0x14];
    /* 0x00014 */ s32 sceneNo;
    /* 0x00018 */ u8 nowNpcMax;
    /* 0x00019 */ u8 removeAnimalIdx;
    /* 0x0001A */ u8 unk_1A[0x20 - 0x1A];
    /* 0x00020 */ PrivateInfo saveFilePrivateInfo[PLAYER_NUM]; // player data
    /* 0x02F60 */ LandInfo landInfo; // town name & id
    /* 0x02F6A */ u8 unk_02F6A[0x61E];
    /* 0x03588 */ mHm_hs_c homes[PLAYER_NUM];
    /* 0x062A8 */ Foreground foreground[FG_BLOCK_Z_NUM][FG_BLOCK_X_NUM];
    /* 0x09EA8 */ u8 unk_09EA8[0x70];
    /* 0x09F18 */ Animal_c animals[ANIMAL_NUM_MAX]; // villagers in town
    /* 0x0EC70 */ AnmPersonalID_c lastRemovedAnimalId;
    /* 0x0EC7C */ u8 unk_0EC7C[0x128];
    /* 0x0EDA4 */ EventSaveInfo eventSaveInfo;
    /* 0x0EE40 */ u8 unk_0EE40[0x118];
    /* 0x0EF58 */ u16 fruit;
    /* 0x0EF5A */ UNK_TYPE1 unk_0EF5A[2];
    /* 0x0EF5C */ lbRTC_time_c allGrowRenewTime;
    /* 0x0EF64 */ UNK_TYPE1 unk_0EF64[0x4B8];
    /* 0x0F41C */ SnowmanData snowmanData[SNOWMAN_SAVE_COUNT];
    /* 0x0F428 */ u64 melody;
    /* 0x0F430 */ UNK_TYPE1 unk_F430[0x4];
    /* 0x0F434 */ lbRTC_ymd_t renewTime;
    /* 0x0F438 */ u8 stationType;
    /* 0x0F439 */ u8 saveWeather;
    /* 0x0F440 */ u8 unk_F440[0x2];
    /* 0x0F43C */ u16 deposit[FG_BLOCK_X_NUM * FG_BLOCK_Z_NUM][UT_Z_NUM]; // flags for which items are buried around town
    /* 0x0F7FC */ lbRTC_time_c lastGrowTime;
    /* 0x0F804 */ PrivateMotherMail motherMailInfo[PLAYER_NUM];
    /* 0x0F83C */ u8 unk_0F83C[0x8];
    /* 0x0F844 */ FamicomEmuCommonData famicomEmuCommonData;
    /* 0x0F86A */ UNK_TYPE1 unk_0F86A[0x2];
    /* 0x0F86C */ u8 npcUsedTable[32];
    /* 0x0F88C */ UNK_TYPE1 unk_0F88A[0x10];
    /* 0x0F89C */ lbRTC_time_c unk_0F89C;
    /* 0x0F8A4 */ lbRTC_time_c unk_0F8A4;
    /* 0x0F8AC */ UNK_TYPE1 unk_0F8AC;
    /* 0x0F8AD */ u8 snowmanYear;  // Year last snowman was built.
    /* 0x0F8AE */ u8 snowmanMonth; // Month last snowman was built.
    /* 0x0F8AF */ u8 snowmanDay;   // Day last snowman was built.
    /* 0x0F8B0 */ u8 snowmanHour;  // Hour last snowman was built.
    /* 0X0F8B1 */ u8 haniwaScheduled;
    /* 0x0F8B2 */ UNK_TYPE1 unk_0F8B2[0x74E];
} Save; // size = 0x10000

typedef struct CommonData {
    /* 0x00000 */ Save save;
    /* 0x10000 */ u8 unk_10000; // named "game_started" in AC GCN decomp
    /* 0x10001 */ u8 unk_10001;
    /* 0x10002 */ u8 fieldDrawType;
    /* 0x10003 */ u8 playerNumber;
    /* 0x10004 */ s32 unk_10004; // named "last_scene_no" in AC GCN decomp
    /* 0x10008 */ s32 playerDataMode;
    /* 0x1000C */ Clip clip;
    /* 0x1010C */ Time time;
    /* 0x10138 */ PrivateInfo* privateInfo;
    /* 0x1013C */ u8 unk_1013C[0x4];
    /* 0x10140 */ u8 unk_10140;
    /* 0x10141 */ u8 fish_location;
    /* 0x10142 */ u8 unk_10142[0x6];
    /* 0x10148 */ u8 unk_10148;
    /* 0x10149 */ u8 unk_10149;
    /* 0x1014A */ u8 unk_1014A;
    /* 0x1014B */ u8 unk_1014B; // named "wipeType" in AC GCN decomp
    /* 0x1014C */ s16 unk_1014C;
    /* 0x1014E */ s16 unk_1014E;
    /* 0x10150 */ UNK_TYPE1 unk_10150[0x10];
    /* 0x10160 */ NpcList npclist[ANIMAL_NUM_MAX];
    /* 0x104A8 */ u16 houseOwnerName;
    /* 0x104AA */ u16 lastFieldId;
    /* 0x104AC */ u8 unk_104AC;
    /* 0x104AD */ u8 unk_104AD;
    /* 0x104AE */ u8 sunlightFlag;
    /* 0x104AF */ UNK_TYPE1 unk_104AF[0x1];
    /* 0x104B0 */ UNK_TYPE1 unk_104B0[0xBC];
    /* 0x1056C */ s16 weather;
    /* 0x1056E */ s16 weatherIntensity;
    /* 0x10570 */ lbRTC_time_c weatherTime;
    /* 0x10578 */ s_xyz wind;
    /* 0x10580 */ f32 windSpeed;
    /* 0x10584 */ UNK_TYPE1 unk10584[0x14];
    /* 0x10598 */ mQst_not_saved_c quest;
    /* 0x105A0 */ s32 sceneFromTitleDemo;
    /* 0x105A4 */ NpsSchedule npcSchedule[ANIMAL_NUM_MAX];
    /* 0x10694 */ NpcWalking npcWalk;
    /* 0x10710 */ NpcEvent npcEvent[5];
    /* 0x1074C */ s32 unk_1074C;
    /* 0x10750 */ s16 moneyPower;
    /* 0x10752 */ s16 goodsPower;
    /* 0x10754 */ DoorData doorData;
    /* 0x10764 */ DoorData structureExitDoorData;
    /* 0x1077C */ DemoRequest startDemoRequest;
    /* 0x1078C */ DoorData eventDoorData;
    /* 0x107A0 */ DoorData famicomEmuDoorData;
    /* 0x107B4 */ s8 unk_107B4;
    /* 0x107B5 */ s8 floorIdx;
    /* 0x107B6 */ s16 unk_107B6; // named "demo_profile" in AC GCN decomp (though it's an array of two s16s in that game)
    /* 0x107B8 */ UNK_TYPE1 unk_107B8[0x27];
    /* 0x107FF*/  s8 paymentType;
    /* 0x107E0 */ s8 playerDecoyFlag;
    /* 0x107E1 */ s8 unk_107E1;
    /* 0x107E2 */ s16 unk_107E2;
    /* 0x107E4 */ s16 unk_107E4; 
    /* 0x107E6 */ UNK_TYPE1 unk107E6[0x212];
    /* 0x109F8 */ u8 unk109F8;
    /* 0x109FC */ s8 unk109F9[0x3F];
    /* 0x10A38 */ s8 beeStingFlag;
    /* 0x10A39 */ s8 unk_10A39;
    /* 0x10A3A */ u8 gokiShockedFlag;
    /* 0x10A3B */ UNK_TYPE1 unk_10A3B[0x1];
    /* 0x10A3C */ UNK_TYPE1 unk_10A3C[0x2C];
    /* 0x10A68 */ u8 unk_10A68;
    /* 0x10A69 */ UNK_TYPE1 unk_10A69[0x3];
    /* 0x10A6C */ xyz_t unk_10A6C;
    /* 0x10A78 */ u8 unk_10A78;
    /* 0x10A79 */ UNK_TYPE1 unk_10A79[0x7];
    /* 0x10A80 */ UNK_TYPE1 unk_10A80[0x2];
    /* 0x10A82 */ s16 unk_10A82;
    /* 0x10A84 */ UNK_TYPE1 unk_10A84[0x2C];
    /* 0x10AB0 */ u8 unk_10AB0; // named "pad_connected" in AC GCN decomp
    /* 0x10AB1 */ UNK_TYPE1 unk_10AB1;
    /* 0x10AB2 */ s16 currentSoundEffect;
    /* 0x10AB4 */ UNK_TYPE1 unk_10AB4[0x4];
} CommonData; // size = 0x10AB8

void common_data_reinit(void);
void common_data_init(void);
void common_data_clear(void);

extern CommonData common_data;

#endif
