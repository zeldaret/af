#ifndef C_67E840_H
#define C_67E840_H

#include "ultra64.h"
#include "m_lib.h"

struct Game_Play;
struct Game;

#define BGM_CHECK_BGM_DATA(num)                                                                              \
    (num == 40 || num == 73 || num == 68 || num == 74 || num == 76 || num == 75 || num == 49 || num == 50 || \
     num == 71 || num == 64 || num == 66 || num == 78)

#define BGM_MONTH_TIME_TO_BGM_MONTH_TIME(month) (((month) << 22) & 0x03C00000)
#define BGM_DAY_TIME_TO_BGM_DAY_TIME(day) (((day) << 17) & 0x3E0000)
#define BGM_HOUR_TIME_TO_BGM_HOUR_TIME(hour) (((hour) << 12) & 0x1F000)
#define BGM_MIN_TIME_TO_BGM_MIN_TIME(min) (((min) << 6) & 0xFC0)
#define BGM_SEC_TIME_TO_BGM_SEC_TIME(sec) (((sec) << 0) & 0x3F)

#define BGM_RTC_TIME_TO_BGM_TIME(month, day, hour, min, sec)                                                             \
    (BGM_MONTH_TIME_TO_BGM_MONTH_TIME(month) | BGM_DAY_TIME_TO_BGM_DAY_TIME(day) | \
     BGM_HOUR_TIME_TO_BGM_HOUR_TIME(hour) | BGM_MIN_TIME_TO_BGM_MIN_TIME(min) |    \
     BGM_SEC_TIME_TO_BGM_SEC_TIME(sec))

#define BGM_TIME_TO_SHOP_CLOSE_TIME(hour, min, sec)                                                   \
    (BGM_HOUR_TIME_TO_BGM_HOUR_TIME(hour) | BGM_MIN_TIME_TO_BGM_MIN_TIME(min) | \
     BGM_SEC_TIME_TO_BGM_SEC_TIME(sec))

#define BGM_CLOCK_CHECK_SEC (((1 << 6) - 1) << 0)
#define BGM_CLOCK_CHECK_MIN (((1 << 6) - 1) << 6)
#define BGM_CLOCK_CHECK_HOUR (((1 << 5) - 1) << 12)
#define BGM_CLOCK_CHECK_DAY (((1 << 5) - 1) << 17)
#define BGM_CLOCK_CHECK_MONTH (((1 << 4) - 1) << 22)

#define BGM_CLOCK_CHECK_ALL (BGM_CLOCK_CHECK_MONTH | BGM_CLOCK_CHECK_DAY | BGM_CLOCK_CHECK_HOUR | BGM_CLOCK_CHECK_MIN | BGM_CLOCK_CHECK_SEC)

#define BGM_PS_MAX 12
    
typedef struct BgmElement {
    /* 0x00 */ u8 num;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 stopType0;
    /* 0x06 */ u16 stopType1;
} BgmElement; // size = 0x8

typedef struct BgmClock {
    /* 0x00 */ u32 now;
    /* 0x04 */ u32 prior;
} BgmClock; // size = 0x8

typedef struct BgmDemo {
    /* 0x00 */ BgmElement element;
    /* 0x08 */ u8 makeFlag;
    /* 0x09 */ u8 deleteFlag;
    /* 0x0A */ UNK_TYPE1 unkA[2];
} BgmDemo; // size = 0xC

typedef struct BgmRoom {
    /* 0x00 */ BgmElement element;
    /* 0x08 */ u8 makeFlag;
    /* 0x09 */ u8 deleteFlag;
    /* 0x0A */ u8 shopFadeoutFlag;
    /* 0x0B */ UNK_TYPE1 unkB;
    /* 0x0C */ u32 shopCloseTime0;
    /* 0x10 */ u32 shopCloseTime1;
} BgmRoom; // size 0x14

typedef struct BgmTime BgmTime;

typedef void (*BgmTimeMoveFunc)(BgmTime*, struct Game_Play*);

struct BgmTime {
    /* 0x4 */ BgmTimeMoveFunc moveFunc;
    /* 0x5 */ u8 newYearEventFlag;
    /* 0x6 */ UNK_TYPE1 unk6;
}; // size = 0x8

typedef struct BgmFieldSudden {
    /* 0x0 */ u32 flag;
    /* 0x4 */ u32 priorFlag;
} BgmFieldSuddenEvent; // size = 0x8

typedef enum BgmBlAttribute {
    /* 0 */ BGM_BL_ATTRIBUTE_INACTIVE,
    /* 1 */ BGM_BL_ATTRIBUTE_NEARBY,
    /* 2 */ BGM_BL_ATTRIBUTE_ACTIVE,
    /* 3 */ BGM_BL_ATTRIBUTE_MAX
} BgmBlAttribute;

typedef enum BgmEventArea {
    /* 0 */ BGM_EVENT_AREA_EVERYWHERE,
    /* 1 */ BGM_EVENT_AREA_BLOCK,
    /* 2 */ BGM_EVENT_AREA_MAX,
} BgmEventArea;

typedef struct BgmFieldScheduleInfo {
    /* 0x0 */ u32 flag;
    /* 0x4 */ s32 attribute;
    /* 0x8 */ s32 priorAttribute;
} BgmFieldScheduleInfo; // size = 0xC

typedef struct BgmFieldScheduleEvent {
    /* 0x00 */ BgmFieldScheduleInfo info[21];
} BgmFieldScheduleEvent; // size = 0xFC

typedef struct BgmNorm {
    /* 0x00 */ BgmElement element;
    /* 0x08 */ u8 makeFlag;
    /* 0x09 */ u8 deleteFlag;
    /* 0x0A */ UNK_TYPE1 unkA[2];
} BgmFieldNorm; // size = 0xC

typedef struct BgmPS {
    /* 0x00 */ BgmElement element;   
    /* 0x04 */ s32 category;
    /* 0x08 */ s16 counter;
    /* 0x0A */ u16 cfFlags;
    /* 0x0C */ u8 priority;
    /* 0x0D */ UNK_TYPE1 unkD;
} BgmPS; // size = 0x10

typedef struct BgmPSStop {
    /* 0x0 */ u8 requestFlag;
    /* 0x2 */ u16 type;
    /* 0x4 */ UNK_TYPE1 unk4;
} BgmPSStop; // size = 0x6

typedef struct BgmPSStart {
    /* 0x0 */ u8 requestFlag;
    /* 0x1 */ u8 num;
    /* 0x2 */ u8 flags;
    /* 0x3 */ u8 unk;
} BgmPSStart; // size = 0x4

typedef struct BgmPSVolume {
   /* 0x00 */ f32 mainVolume;
   /* 0x04 */ u16 mainVolumeMoveCounter;
   /* 0x06 */ u8 mainRequestFlag;
   /* 0x08 */ f32 psVolume;
   /* 0x0C */ u16 psVolumeMoveCounter;
   /* 0x0E */ u8 psRequestFlag;
   /* 0x10 */ f32 fishingInsectVolume;
   /* 0x14 */ u16 fishingInsectVolumeMoveCounter;
   /* 0x16 */ u8 fishingInsectRequestFlag;
   /* 0x18 */ f32 talkVolume;
   /* 0x1C */ u8 talkRequestFlag;
   /* 0x20 */ f32 pauseVolume;
   /* 0x24 */ u16 pauseVolumeMoveCounter;
   /* 0x26 */ u8 pauseRequestFlag;
} BgmPSVolume; // size = 0x28

typedef struct BgmPSPause {
   /* 0x0 */ u8 requestFlag;
   /* 0x1 */ u8 mode;
   /* 0x2 */ UNK_TYPE1 unk2[2];
} BgmPSPause; // size = 0x4

typedef struct BgmPSMd {
   /* 0x00 */ u8 requestFlag;
   /* 0x01 */ u8 makeFlag;
   /* 0x02 */ u8 deleteFlag;
   /* 0x03 */ u8 moveFlag;
   /* 0x04 */ xyz_t pos;
   /* 0x10 */ u16 angle;
   /* 0x12 */ u16 mdType;
   /* 0x14 */ u32 ongenNum;    
} BgmPSMd; // size = 0x18

typedef struct BgmPSArm {
   /* 0x0 */ u8 requestFlag;
   /* 0x1 */ u8 armState;
   /* 0x2 */ UNK_TYPE1 unk2[2];
} BgmPSArm; // size = 0x4

typedef struct BgmPSComp {
   /* 0x000 */ BgmPS ps[BGM_PS_MAX];
   /* 0x0F0 */ s32 psNum;
   /* 0x0F4 */ s32 fishInsectState;
   /* 0x0F8 */ s32 talkState;
   /* 0x0FC */ s32 pauseState;
   /* 0x100 */ BgmPSStop stop;
   /* 0x106 */ BgmPSStart start;
   /* 0x10C */ BgmPSVolume volume;
   /* 0x134 */ BgmPSPause pause;
   /* 0x138 */ BgmPSMd md;
   /* 0x150 */ BgmPSArm arm;
} BgmPSComp; // size = 0x154

typedef struct BgmForce {
   /* 0x0 */ s32 inform;
   /* 0x4 */ u8 flag;
   /* 0x8 */ s32 roomNonstop;
} BgmForce; // size = 0xC

typedef struct Bgm {
   /* 0x000 */ BgmClock clock;
   /* 0x008 */ BgmDemo demo;
   /* 0x014 */ BgmRoom room;
   /* 0x028 */ BgmTime time;
   /* 0x030 */ BgmFieldSuddenEvent fieldSuddenEvent;
   /* 0x038 */ BgmFieldScheduleEvent fieldScheduleEvent;
   /* 0x134 */ BgmFieldNorm fieldNorm;
   /* 0x140 */ BgmPSComp psComp;
   /* 0x294 */ BgmForce force;
} Bgm; // size = 0x2A0

typedef struct BgmEventData {
    /* 0x0 */ s16 eventType;
    /* 0x2 */ u8 num;
    /* 0x3 */ u8 eventArea;
    /* 0x4 */ u32 blockType;
} BgmEventData; // size = 0x8

int mBGM_check_MD(u8 num);
int mBGM_check_ignore_talk_volume(u8 num);
int func_8005ACA8_jp(u8 num);
void mBGMElem_default_set(BgmElement* element);
int mBGMClock_after_time_check(BgmClock* clock, u32 checktTime, u32 checkMask);
int mBGMClock_over_time_check(BgmClock* clock, u32 checktTime, u32 checkMask);
int mBGMClock_range_time_check(BgmClock* clock, u32 checktTime0, u32 checktTime1, u32 checkMask);
void mBGMClock_now_set(BgmClock* clock);
void mBGMClock_move(BgmClock* clock, struct Game_Play* play);
void mBGMClock_ct(BgmClock* clock);
void mBGMDemo_make_scene_bgm(BgmDemo* demo);
void mBGMDemo_delete_scene_bgm(BgmDemo* demo);
void mBGMDemo_move(BgmDemo* demo, struct Game_Play* play);
void mBGMDemo_scene_bgm_make_req(void);
void mBGMDemo_scene_bgm_delete_req(void);
void mBGMDemo_ct(BgmDemo* demo);
void mBGMRoom_shop_close_time_set(BgmRoom* room);
u8 mBGMRoom_make_scene_bgm_shop_get(BgmRoom* room, u16 fieldId);
void mBGMRoom_make_scene_bgm(BgmRoom* room);
void mBGMRoom_delete_scene_bgm(BgmRoom* room);
s32 mBGMRoom_shop_close_check(BgmRoom* room);
void mBGMRoom_move(BgmRoom* room, struct Game_Play* play);
void mBGMRoom_scene_bgm_make_req(void);
void mBGMRoom_scene_bgm_delete_req(void);
void mBGMRoom_ct(BgmRoom* room);
void mBGMTime_signal_melody(BgmTime* time);
int mBGMTime_silent_check(BgmTime* time);
void mBGMTime_new_year_ev_flag_set(void);
void mBGMTime_new_year_ev_flag_clr(void);
void mBGMTime_move_wait(BgmTime* time, struct Game_Play* play);
void mBGMTime_move_change(BgmTime* time, struct Game_Play* play);
void mBGMTime_move(BgmTime* time, struct Game_Play* play);
void mBGMTime_ct(BgmTime* time);
s32 mBGMFieldSuddenEv_flag_check_arbeit(BgmFieldSuddenEvent* fieldSuddenEvent, struct Game_Play* play);
void mBGMFieldSuddenEv_flag_set(BgmFieldSuddenEvent* fieldSudden, struct Game_Play* play);
void mBGMFieldSuddenEv_ps_compose(BgmFieldSuddenEvent* fieldSudden, struct Game_Play* play);
void mBGMFieldSuddenEv_move(BgmFieldSuddenEvent* fieldSudden, struct Game_Play* play);
void mBGMFieldSuddenEv_ct(BgmFieldSuddenEvent* fieldSudden);
s32 mBGMFieldSchedEv_bl_attr_get(s32 blockX, s32 blockZ, s32 eventArea, u32 blockType);
s32 mBGMFieldSchedEv_bl_attr_evdata_get(BgmEventData* data, struct Game_Play* play);
void mBGMFieldSchedEv_Info_old_copy(BgmFieldScheduleInfo* info);
void mBGMFieldSchedEv_Info_ev_now_set_standard(BgmFieldScheduleInfo* info, BgmEventData* data, struct Game_Play* play,
                                               s32 eventStartFlag);
void mBGMFieldSchedEv_Info_ev_now_set_Silence_0(BgmFieldScheduleInfo* info, BgmEventData* data, struct Game_Play* play,
                                                s32 eventStartFlag);
void mBGMFieldSchedEv_Info_ev_now_set_CountDown_1(BgmFieldScheduleInfo* info, BgmEventData* data, struct Game_Play* play,
                                                  s32 eventStartFlag);
void mBGMFieldSchedEv_Info_ev_now_set_CountDown_2(BgmFieldScheduleInfo* info, BgmEventData* data, struct Game_Play* play,
                                                  s32 eventStartFlag);
void mBGMFieldSchedEv_Info_ev_now_set_CountDown_3(BgmFieldScheduleInfo* info, BgmEventData* data, struct Game_Play* play,
                                                  s32 eventStartFlag);
void mBGMFieldSchedEv_Info_ev_now_set_CountDown_4(BgmFieldScheduleInfo* info, BgmEventData* data, struct Game_Play* play,
                                                  s32 eventStartFlag);
void mBGMFieldSchedEv_Info_ev_now_set_CountDown_5(BgmFieldScheduleInfo* info, BgmEventData* data, struct Game_Play* play,
                                                  s32 eventStartFlag);
void mBGMFieldSchedEv_Info_ev_now_set_CountDown_6(BgmFieldScheduleInfo* info, BgmEventData* data, struct Game_Play* play,
                                                  s32 eventStartFlag);
void mBGMFieldSchedEv_Info_ev_now_set_NewYear01(BgmFieldScheduleInfo* info, BgmEventData* data, struct Game_Play* play,
                                                  s32 eventStartFlag);
void mBGMFieldSchedEv_Info_ev_now_set_NewYear02(BgmFieldScheduleInfo* info, BgmEventData* data, struct Game_Play* play,
                                                  s32 eventStartFlag);
void mBGMFieldSchedEv_Info_attr_now_set(BgmFieldScheduleInfo* info,  struct Game_Play* play, BgmEventData* data);
void mBGMFieldSchedEv_info_set(BgmFieldScheduleEvent* schedule, struct Game_Play* play);
void mBGMFieldSchedEv_Info_ps_delete(BgmFieldScheduleInfo* info, BgmEventData* data, s32 flag);
void mBGMFieldSchedEv_Info_ps_make(BgmFieldScheduleInfo* info, BgmEventData* data, s32 priority);
void mBGMFieldSchedEv_Info_ps_volume_change(BgmFieldScheduleInfo* info, BgmEventData* data);
void mBGMFieldSchedEv_ps_compose(BgmFieldScheduleEvent* schedule, struct Game_Play* play);
void mBGMFieldSchedEv_sp_flag(BgmFieldScheduleEvent* schedule);
void mBGMFieldSchedEv_move(BgmFieldScheduleEvent* schedule, struct Game_Play* play);
void mBGMFieldSchedEv_ct(BgmFieldScheduleEvent* schedule);
u8 mBGMFieldNorm_bgm_num_get(s32 hour);
void mBGMFieldNorm_elem_set(BgmFieldNorm* norm);
void mBGMFieldNorm_make_bgm(BgmFieldNorm* norm, struct Game_Play* play);
void mBGMFieldNorm_delete_bgm(BgmFieldNorm* norm);
void mBGMFieldNorm_move(BgmFieldNorm* norm,  struct Game_Play* play);
void mBGMFieldNorm_make_req(void);
void mBGMFieldNorm_delete_req(void);
void mBGMFieldNorm_ct(BgmFieldNorm* norm);
void mBGMPs_counter_dec(BgmPS* ps);
void mBGMPsComp_ps_remove(BgmPSComp* psComp, s32 removePos);
s32 mBGMPsComp_search_insert_pos_kategorie(BgmPSComp* psComp, s32 category, u8 priority);
s32 mBGMPsComp_search_pos_kategorie_bgm_num(BgmPSComp* psComp, s32 category, u8 num, s32 counterFlag, s32 delPass);
void mBGMPsComp_shift_behind(BgmPSComp* psComp, s32 shiftIdx);
void mBGMPsComp_all_ps_bitclr(BgmPSComp* psComp, u8 bits);
s32 mBGMPsComp_execute_ps_pos_get(BgmPSComp* psComp);
BgmPS* mBGMPsComp_high_ps_not_delete(BgmPSComp* psComp, s32 maxPos);
void mBGMPsComp_main_req_stop(BgmPSComp* psComp);
void mBGMPsComp_main_remove(BgmPSComp* psComp);
void mBGMPsComp_main_req_start(BgmPSComp* psComp);
void mBGMPsComp_main_req_pause(BgmPSComp* psComp);
void mBGMPsComp_main_req_md(BgmPSComp* psComp);
void mBGMPsComp_main_md_move(BgmPSComp* psComp);
void mBGMPsComp_main_req_volume_ps(BgmPSComp* psComp);
void func_8005D2A4_jp(BgmPSComp* psComp);
void mBGMPsComp_main_req_volume_talk(BgmPSComp* psComp);
void mBGMPsComp_main_req_volume_pause(BgmPSComp* psComp);
void mBGMPsComp_main_req_volume(BgmPSComp* psComp);
void mBGMPsComp_MDPlayerPos_main_inform_sound(BgmPSMd* md);
void mBGMPsComp_Arm_main_inform_sound(BgmPSArm* arm);
void mBGMPsComp_Stop_main_inform_sound(BgmPSStop* stop);
void mBGMPsComp_Start_main_inform_sound(BgmPSStart* start);
void mBGMPsComp_Volume_main_inform_sound(BgmPSVolume* volume);
void mBGMPsComp_Pause_main_inform_sound(BgmPSPause* pause);
void mBGMPsComp_main_inform_sound(BgmPSComp* psComp);
void mBGMPsComp_main_counter_dec(BgmPSComp* psComp);
void mBGMPsComp_main_fo_check(BgmPSComp* psComp);
void mBGMPsComp_main_lost(BgmPSComp* psComp);
s32 mBGMPsComp_make_ps(BgmPSComp* psComp, BgmElement* element, s32 category, s16 counter, u16 cfFlags, u8 priority);
void _mBGMPsComp_make_ps_fanfare(u8 num, u16 stopType);
void mBGMPsComp_make_ps_fanfare(u8 num, u16 stopType);
void _mBGMPsComp_make_ps_lost_fanfare(u8 num, u16 stopType);
void mBGMPsComp_make_ps_lost_fanfare(u8 num, u16 stopType);
void _mBGMPsComp_make_ps_wipe(u16 stopType);
void mBGMPsComp_make_ps_wipe(u16 stopType);
void _mBGMPsComp_make_ps_quiet(u16 stopType);
void mBGMPsComp_make_ps_quiet(u16 stopType);
void _mBGMPsComp_make_ps_co_quiet(u16 stopType, s16 counter);
void mBGMPsComp_make_ps_co_quiet(u16 stopType, s16 counter);
void _mBGMPsComp_make_ps_demo(u8 num, u16 stopType);
void mBGMPsComp_make_ps_demo(u8 num, u16 stopType);
void _mBGMPsComp_make_ps_happening(u8 num, u16 stopType);
void mBGMPsComp_make_ps_happening(u8 num, u16 stopType);
void mBGMPsComp_make_ps_quietRoom(u16 stopType);
void _mBGMPsComp_make_ps_room(u8 num, u16 stopType);
void mBGMPsComp_make_ps_room(u8 num, u16 stopType);
void mBGMPsComp_make_ps_time(void);
void _mBGMPsComp_make_ps_quietField(u16 stopType);
void mBGMPsComp_make_ps_quietField(u16 stopType);
void _mBGMPsComp_make_ps_fc_quietField(u16 stopType);
void mBGMPsComp_make_ps_fc_quietField(u16 stopType);
void _mBGMPsComp_make_ps_fieldSuddenEv(u8 num, u16 stopType, u8 priority);
void mBGMPsComp_make_ps_fieldSuddenEv(u8 num, u16 stopType, u8 priority);
void mBGMPsComp_make_ps_fieldSchedEv(u8 num, s32 updateVolumeMoveCounter, s32 updateVolumeFlag, s32 cfFlag,
                                     u16 stopType, u8 priority);
void mBGMPsComp_make_ps_fieldNorm(u8 num, u16 stopType);
void mBGMPsComp_delete_ps(BgmPSComp* psComp, s32 category, u8 num, u16 stopType, s32 counterFlag);
void _mBGMPsComp_delete_ps_fanfare(u8 num, u16 stopType);
void mBGMPsComp_delete_ps_fanfare(u8 num, u16 stopType);
void mBGMPsComp_delete_ps_wipe(void);
void _mBGMPsComp_delete_ps_quiet(void);
void mBGMPsComp_delete_ps_quiet(void);
void _mBGMPsComp_delete_ps_demo(u8 num, u16 stopType);
void mBGMPsComp_delete_ps_demo(u8 num, u16 stopType);
void _mBGMPsComp_delete_ps_happening(u8 num, u16 stopType);
void mBGMPsComp_delete_ps_happening(u8 num, u16 stopType);
void mBGMPsComp_delete_ps_quietRoom(void);
void _mBGMPsComp_delete_ps_room(u8 num, u16 stopType);
void mBGMPsComp_delete_ps_room(u8 num, u16 stopType);
void mBGMPsComp_delete_ps_time(void);
void _mBGMPsComp_delete_ps_quietField(void);
void mBGMPsComp_delete_ps_quietField(void);
void _mBGMPsComp_delete_ps_fieldSuddenEv(u8 num, u16 stopType);
void mBGMPsComp_delete_ps_fieldSuddenEv(u8 num, u16 stopType);
void mBGMPsComp_delete_ps_fieldSchedEv(u8 num, u16 stopType);
void mBGMPsComp_delete_ps_fieldNorm(u8 num, u16 stopType);
void mBGMPsComp_volume_change_fieldSchedEv(u8 num, s32 updateVolumeCounter, s32 updateVolumeLevel);
void mBGMPsComp_search_cf_set_field(u8 num, s32 category);
void func_8005E9B4_jp(void);
void func_8005E9C8_jp(void);
void mBGMPsComp_volume_talk_start(void);
void mBGMPsComp_volume_talk_end(void);
void mBGMPsComp_pause(s32 state);
void mBGMPsComp_MDPlayerPos_make(void);
void mBGMPsComp_MDPlayerPos_delete(void);
void mBGMPsComp_MDPlayerPos_param_set(xyz_t* pos, u16 angle, u16 mdType, u32 ongenNum);
void mBGMPsComp_scene_mode(u8 mode);
void mBGMPsComp_arm_make(s32 state);
void mBGMPsComp_arm_delete(void);
s32 mBGMPsComp_execute_bgm_num_get(void);
void mBGMPsComp_ct(BgmPSComp* psComp);
s32 mBGMForce_wipe_ps_make_permit(BgmForce* force);
void mBGMForce_move_inform(BgmForce* force);
void mBGMForce_move_room_nonstop(BgmForce* force);
void mBGMForce_move(BgmForce* force);
void mBGMForce_ct(BgmForce* force);
void mBGMForce_inform_cleanup(BgmForce* force);
void mBGMForce_room_nonstop_cleanup(BgmForce* force);
void mBGMForce_cleanup(BgmForce* force);
void mBGMForce_inform_start(void);
void mBGMForce_inform_end(void);
void _mBGMForce_room_nonstop_start(void);
void mBGMForce_room_nonstop_start(void);
void mBGM_main_control(Bgm* bgm);
void mBGM_weather_set(void);
void mBGM_main(struct Game* game);
void mBGM_ct(void);
void mBGM_init(void);
void mBGM_cleanup(void);
void mBGM_reset(void);


#endif
