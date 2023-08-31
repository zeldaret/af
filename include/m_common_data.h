#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "ultra64.h"
#include "unk.h"
#include "m_npc.h"
#include "m_npc_walk.h"
#include "m_quest.h"
#include "m_private.h"
#include "m_land.h"
#include "lb_rtc.h"
#include "m_home.h"
#include "m_event.h"
#include "m_field_make.h"

struct Actor;
struct ActorOverlay;
struct struct_801161E8_jp;
struct Game_Play_unk_0110;
struct CommonData_unk_1004C_unk_14_arg0;
struct Game_Play;
struct struct_809AEFA4;

typedef UNK_RET (*CommonData_unk_1004C_unk_04)(struct ActorOverlay*, const struct struct_801161E8_jp*, size_t, s32);
typedef UNK_RET (*CommonData_unk_1004C_unk_08)(void);

// TODO: figure out if this is a generic memory allocation or if it is Actor specific
typedef UNK_PTR (*CommonData_unk_1004C_unk_0C)(size_t, const struct struct_801161E8_jp*, s32);

typedef UNK_RET (*CommonData_unk_1004C_unk_10)(struct Actor*);
typedef UNK_RET (*CommonData_unk_1004C_unk_14)(struct CommonData_unk_1004C_unk_14_arg0*, u16);

typedef UNK_RET (*CommonData_unk_1004C_unk_BC)(struct Actor*, struct Game_Play*);
typedef void (*CommonData_unk_1004C_unk_C0)(struct Actor*, struct Game_Play*, struct struct_809AEFA4*);
typedef UNK_RET (*CommonData_unk_1004C_unk_C4)(struct Actor*, struct Game_Play*);
typedef UNK_RET (*CommonData_unk_1004C_unk_C8)(struct Actor*, struct Game_Play*);
typedef UNK_RET (*CommonData_unk_1004C_unk_CC)(struct Actor*, struct Game_Play*);
typedef UNK_RET (*CommonData_unk_1004C_unk_D0)(void);

typedef UNK_RET (*CommonData_unk_1004C_unk_E4)(void);

typedef UNK_RET (*CommonData_unk_1004C_unk_EC)(struct Game_Play_unk_0110*, s16, s16);
typedef UNK_RET (*CommonData_unk_1004C_unk_F0)(struct Game_Play_unk_0110*, struct Actor*);
typedef s32 (*CommonData_unk_1004C_unk_F4)(struct Game_Play_unk_0110*, struct Actor*);

typedef UNK_RET (*CommonData_unk_1004C_unk_118)(struct Actor*);

typedef struct CommonData_unk_1004C {
    /* 0x000 */ UNK_TYPE1 unk_00[0x4];
    /* 0x004 */ CommonData_unk_1004C_unk_04 unk_04;
    /* 0x008 */ CommonData_unk_1004C_unk_08 unk_08;
    /* 0x00C */ CommonData_unk_1004C_unk_0C unk_0C;
    /* 0x010 */ CommonData_unk_1004C_unk_10 unk_10;
    /* 0x014 */ CommonData_unk_1004C_unk_14 unk_14;
    /* 0x018 */ UNK_TYPE1 unk_18[0xA4];
    /* 0x0BC */ CommonData_unk_1004C_unk_BC unk_BC;
    /* 0x0C0 */ CommonData_unk_1004C_unk_C0 unk_C0;
    /* 0x0C4 */ CommonData_unk_1004C_unk_C4 unk_C4;
    /* 0x0C8 */ CommonData_unk_1004C_unk_C8 unk_C8;
    /* 0x0CC */ CommonData_unk_1004C_unk_CC unk_CC;
    /* 0x0D0 */ CommonData_unk_1004C_unk_D0 unk_D0;
    /* 0x0D4 */ UNK_TYPE1 unk_D4[0x10];
    /* 0x0E4 */ CommonData_unk_1004C_unk_E4 unk_E4;
    /* 0x0E8 */ UNK_TYPE1 unk_E8[0x4];
    /* 0x0EC */ CommonData_unk_1004C_unk_EC unk_EC;
    /* 0x0F0 */ CommonData_unk_1004C_unk_F0 unk_F0;
    /* 0x0F4 */ CommonData_unk_1004C_unk_F4 unk_F4;
    /* 0x0F8 */ UNK_TYPE1 unk_F8[0x20];
    /* 0x118 */ CommonData_unk_1004C_unk_118 unk_118;
} CommonData_unk_1004C; // size >= 0x11C

typedef UNK_RET (*CommonData_unk_10078_unk_00)(UNK_TYPE);
typedef UNK_RET (*CommonData_unk_10078_unk_04)(UNK_TYPE);
typedef UNK_RET (*CommonData_unk_10078_unk_08)(UNK_TYPE);


typedef struct CommonData_unk_10078 {
    /* 0x00 */ CommonData_unk_10078_unk_00 unk_00;
    /* 0x04 */ CommonData_unk_10078_unk_04 unk_04;
    /* 0x08 */ CommonData_unk_10078_unk_08 unk_08;
} CommonData_unk_10078; // size >= 0xC

typedef UNK_RET (*CommonData_unk_10098_unk_4)(struct ActorOverlay*, size_t);
typedef UNK_RET (*CommonData_unk_10098_unk_8)(void);

// TODO: figure out if this is a generic memory allocation or if it is Actor specific
typedef UNK_PTR (*CommonData_unk_10098_unk_0C)(void);

typedef UNK_RET (*CommonData_unk_10098_unk_10)(struct Actor*);

typedef struct CommonData_unk_10098 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ CommonData_unk_10098_unk_4 unk_4;
    /* 0x08 */ CommonData_unk_10098_unk_8 unk_08;
    /* 0x0C */ CommonData_unk_10098_unk_0C unk_0C;
    /* 0x10 */ CommonData_unk_10098_unk_10 unk_10;
} CommonData_unk_10098; // size >= 0x10

typedef struct mPr_mother_mail_info_c {
    /* 0x00 */ UNK_TYPE1 unk_00[0xE];
} mPr_mother_mail_info_c; // size = 0xE

typedef struct Time_c {
    /* 0x00 */ u32 season;
    /* 0x04 */ u32 term_idx;
    /* 0x08 */ s16 bgitem_profile;
    /* 0x0A */ s16 bgitem_bank;
    /* 0x0C */ s32 now_sec;
    /* 0x10 */ lbRTC_time_c rtc_time;
    /* 0x18 */ s16 rad_min; /* clock hand radial position for mins */
    /* 0x1A */ s16 rad_hour; /* clock hand radial position for hours */
    /* 0x1C */ u8 time_signal;
    /* 0x1D */ u8 under_sec;
    /* 0x1E */ u8 disp;
    /* 0x1F */ u8 rtc_crashed;
    /* 0x20 */ s32 rtc_enabled;
    /* 0x24 */ s32 add_sec;
    /* 0x28 */ s32 add_idx;
} Time_c; // size = 0x2C

typedef struct FamicomEmuCommonData {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
}FamicomEmuCommonData; // size >= 0x26

typedef void (*CommonData_100E4_Func)(struct Game_Play*);

typedef struct CommonData {
    /* 0x00000 */ u8 unk00000[0x14];
    /* 0x00014 */ s32 unk_00014;
    /* 0x00018 */ u8 unk00018[0x8];
    /* 0x00020 */ Private_c private[PLAYER_NUM]; /* player data */
    /* 0x02F60 */ mLd_land_info_c land_info; /* town name & id */
    /* 0x02F6A */ u8 unk02F6A[0x61E];
    /* 0x03588 */ mHm_hs_c homes[PLAYER_NUM];
    /* 0x062A8 */ mFM_fg_c fg[FG_BLOCK_Z_NUM][FG_BLOCK_X_NUM]; /* fg items (fg = foreground?) */
    /* 0x09EA8 */ u8 unk09EA8[0x70];
    /* 0x09F18 */ Animal_c animals[ANIMAL_NUM_MAX]; /* villagers in town */
    /* 0x0EC70 */ u8 unk0EC70[0x134];
    /* 0x0EDA4 */ mEv_event_save_c event_save_data;
    /* 0x0EE40 */ u8 unk0EE40[0x118];
    /* 0x0EF58 */ u16 fruit;
    /* 0x0EF5A */ u8 unk0EF5A[0x4DE];
    /* 0x0F438 */ u8 station_type; /* train station type */
    /* 0x0F439 */ u8 unk0F439[0x3];
    /* 0x0F43C */ u16 deposit[FG_BLOCK_X_NUM * FG_BLOCK_Z_NUM][UT_Z_NUM]; /* flags for which items are buried around town */
    /* 0x0F7FC */ lbRTC_time_c unk_0F7FC;
    /* 0x0F804 */ mPr_mother_mail_info_c mother_mail[PLAYER_NUM];
    /* 0x0F83C */ u8 unk0F83C[0x8];
    /* 0x0F844 */ FamicomEmuCommonData famicom_emu_common_data;
    /* 0x0F86A */ u8 unk0F86A[0x32];
    /* 0x0F89C */ lbRTC_time_c unk_0F89C;
    /* 0x0F8A4 */ lbRTC_time_c unk_0F8A4;
    /* 0x0F8AC */ u8 unk0F8AC[0x754];
    /* 0x10000 */ u8 unk_10000; // named "game_started" in AC GCN decomp
    /* 0x10001 */ u8 unk_10001;
    /* 0x10002 */ u8 unk10002[0x1];
    /* 0x10003 */ u8 player_no;
    /* 0x10004 */ s32 unk_10004; // named "last_scene_no" in AC GCN decomp
    /* 0x10008 */ UNK_TYPE1 unk_10008[0x44];
    /* 0x1004C */ CommonData_unk_1004C *unk_1004C;
    /* 0x10050 */ UNK_TYPE1 unk_10050[0x28];
    /* 0x10078 */ CommonData_unk_10078 *unk_10078;
    /* 0x1007C */ UNK_TYPE1 unk_1007C[0x1C];
    /* 0x10098 */ CommonData_unk_10098 *unk_10098;
    /* 0x1009C */ UNK_TYPE1 unk_1009C[0x48];
    /* 0x100E4 */ CommonData_100E4_Func* unk_100E4;
    /* 0x100E8 */ u8 unk100E8[0x24];
    /* 0x1010C */ Time_c time;
    /* 0x10138 */ Private_c* now_private;
    /* 0x1013C */ u8 unk1013C[0x4];
    /* 0x10140 */ u8 unk_10140;
    /* 0x10141 */ u8 fish_location;
    /* 0x10142 */ u8 unk10142[0x7];
    /* 0x10149 */ u8 unk_10149;
    /* 0x1014A */ u8 unk_1014A;
    /* 0x1014B */ u8 unk_1014B; // named "wipeType" in AC GCN decomp
    /* 0x1014C */ UNK_TYPE1 unk_1014C[0x2];
    /* 0x1014E */ s16 unk_1014E;
    /* 0x10150 */ UNK_TYPE1 unk_10150[0x10];
    /* 0x10160 */ mNpc_NpcList_c npclist[ANIMAL_NUM_MAX];
    /* 0x104A8 */ u16 house_owner_name;
    /* 0x104AA */ u16 last_field_id;
    /* 0x104AC */ UNK_TYPE1 unk_104AC[0x1];
    /* 0x104AD */ u8 unk_104AD;
    /* 0x104AE */ UNK_TYPE1 unk_104AE[0x2];
    /* 0x104B0 */ UNK_TYPE1 unk_104B0[0xE8];
    /* 0x10598 */ mQst_not_saved_c quest;
    /* 0x105A0 */ u32 scene_from_title_demo;
    /* 0x105A4 */ UNK_TYPE1 unk_105A4[0xF0];
    /* 0x10694 */ mNpc_walk_c npc_walk;
    /* 0x10710 */ UNK_TYPE1 unk_10710[0xA6];
    /* 0x107B6 */ s16 unk_107B6; // named "demo_profile" in AC GCN decomp (though it's an array of two s16s in that game)
    /* 0x107B8 */ u8 unk107B8[0x28];
    /* 0x107E0 */ s8 player_decoy_flag;
    /* 0x107E1 */ u8 unk107E1[0x3];
    /* 0x107E4 */ s16 unk_107E4;
    /* 0x107E6 */ u8 unk107E6[0x254];
    /* 0x10A3A */ u8 goki_shocked_flag;
    /* 0x10A3B */ UNK_TYPE1 unk_10A3B[0x1];
    /* 0x10A3C */ UNK_TYPE1 unk_10A3C[0x2C];
    /* 0x10A68 */ u8 unk_10A68;
    /* 0x10A69 */ UNK_TYPE1 unk_10A69[0x3];
    /* 0x10A6C */ UNK_TYPE1 unk_10A6C[0x14];
    /* 0x10A80 */ UNK_TYPE1 unk_10A80[0x2];
    /* 0x10A82 */ s16 unk_10A82;
    /* 0x10A84 */ u8 unk10A84[0x2C];
    /* 0x10AB0 */ u8 unk_10AB0; // named "pad_connected" in AC GCN decomp
    /* 0x10AB1 */ UNK_TYPE1 unk_10AB1[0x7];
} CommonData; // size = 0x10AB8

void common_data_reinit(void);
void common_data_init(void);
void common_data_clear(void);

extern CommonData common_data;

#endif
