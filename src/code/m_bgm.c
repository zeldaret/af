#include "m_bgm.h"
#include "6E3240.h"
#include "audio.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "m_melody.h"
#include "m_player_lib.h"
#include "m_scene_table.h"
#include "macros.h"
#include "overlays/actors/player_actor/m_player.h"
#include "prevent_bss_reordering.h"

// TODO : revisit for iQue, has some nonmatchings

Bgm M_bgm;

int mBGM_check_MD(u8 num) {
    return ((num >= 0x80 && num <= 0xB3) || (num >= 0xB4 && num <= 0xB6));
}

int mBGM_check_ignore_talk_volume(u8 num) {
    return BGM_CHECK_BGM_DATA(num);
}

int func_8005ACA8_jp(u8 num) {
    return num == 40;
}

void mBGMElem_default_set(BgmElement* element) {
    static BgmElement default_data = { 255, 0, 0, 0x168, 0x168 };
    bcopy(&default_data, element, sizeof(BgmElement));
}

int mBGMClock_after_time_check(BgmClock* clock, u32 checktTime, u32 checkMask) {
    u32 timeNow = clock->now & checkMask;
    u32 timeCheck = checktTime & checkMask;

    return timeNow >= timeCheck;
}

int mBGMClock_over_time_check(BgmClock* clock, u32 checktTime, u32 checkMask) {
    u32 timeNow = clock->now & checkMask;
    u32 timePrior = clock->prior & checkMask;
    u32 timeCheck = checktTime & checkMask;

    if (timeNow >= timePrior) {
        return (timeCheck > timePrior && timeCheck <= timeNow);

    } else {
        return (timeCheck > timePrior || timeCheck <= timeNow);
    }
}

int mBGMClock_range_time_check(BgmClock* clock, u32 checktTime0, u32 checktTime1, u32 checkMask) {
    u32 timeNow = clock->now & checkMask;
    u32 timeCheck0 = checktTime0 & checkMask;
    u32 timeCheck1 = checktTime1 & checkMask;

    if (timeCheck1 >= timeCheck0) {
        return (timeNow >= timeCheck0 && timeNow < timeCheck1);

    } else {
        return (timeNow >= timeCheck0 || timeNow < timeCheck1);
    }
}

void mBGMClock_now_set(BgmClock* clock) {
    lbRTC_time_c* time = &common_data.time.rtcTime;

    clock->prior = clock->now;
    clock->now = BGM_RTC_TIME_TO_BGM_TIME(time->month, time->day, time->hour, time->min, time->sec);
}

void mBGMClock_move(BgmClock* clock, UNUSED Game_Play* play) {
    mBGMClock_now_set(clock);
}

void mBGMClock_ct(BgmClock* clock) {
    bzero(clock, sizeof(BgmClock));
    mBGMClock_now_set(clock);
    clock->prior = clock->now;
}

void mBGMDemo_make_scene_bgm(BgmDemo* demo) {
    if (demo->element.num == 255 && mFI_CheckFieldData()) {
        u16 fieldId = mFI_GetFieldId();
        u8 num;

        switch (fieldId) {
            case 0x5000:
            case 0x5001:
                num = 42;
                break;

            case 0x5002:
                if (common_data.save.sceneNo == SCENE_PLAYERSELECT_SAVE) {
                    num = 46;
                } else {
                    num = 43;
                }
                break;

            default:
                num = 255;
                break;
        }

        if (num != 255) {
            mBGMElem_default_set(&demo->element);
            demo->element.num = num;
            mBGMPsComp_make_ps_demo(num, 0x168);
        }
    }
}

void mBGMDemo_delete_scene_bgm(BgmDemo* demo) {
    if (demo->element.num != 255) {
        mBGMPsComp_delete_ps_demo(demo->element.num, 0x168);
        demo->element.num = 255;
    }
}

void mBGMDemo_move(BgmDemo* demo, UNUSED Game_Play* play) {
    if (demo->deleteFlag) {
        mBGMDemo_delete_scene_bgm(demo);
    }

    if (demo->makeFlag) {
        mBGMDemo_make_scene_bgm(demo);
    }

    demo->makeFlag = FALSE;
    demo->deleteFlag = FALSE;
}

void mBGMDemo_scene_bgm_make_req() {
    M_bgm.demo.makeFlag = TRUE;
}

void mBGMDemo_scene_bgm_delete_req() {
    M_bgm.demo.deleteFlag = TRUE;
}

void mBGMDemo_ct(BgmDemo* demo) {
    bzero(demo, sizeof(BgmDemo));
    mBGMElem_default_set(&demo->element);
}

void mBGMRoom_shop_close_time_set(BgmRoom* room) {
    if (mFI_CheckFieldData()) {
        u16 fieldId = mFI_GetFieldId();

        if (fieldId == 0x3001 || fieldId == 0x3006 || fieldId == 0x3007 || fieldId == 0x3008 || fieldId == 0x3009) {
            lbRTC_time_c time;

            bzero(&time, sizeof(lbRTC_time_c));
            time.hour = mSP_GetShopCloseTime_Bgm();

            lbRTC_Sub_mm(&time, 5);
            room->shopCloseTime1 = BGM_TIME_TO_SHOP_CLOSE_TIME(time.hour, time.min, time.sec);

            lbRTC_Sub_ss(&time, 5);
            room->shopCloseTime0 = BGM_TIME_TO_SHOP_CLOSE_TIME(time.hour, time.min, time.sec);
        }
    }
}

u8 mBGMRoom_make_scene_bgm_shop_get(BgmRoom* room, u16 fieldId) {
    u8 num;

    if (mEv_CheckRealArbeit() == FALSE &&
        mBGMClock_after_time_check(&M_bgm.clock, room->shopCloseTime1,
                                   BGM_CLOCK_CHECK_HOUR | BGM_CLOCK_CHECK_MIN | BGM_CLOCK_CHECK_SEC)) {
        if (fieldId == 0x3001) {
            num = 79;
        } else if (fieldId == 0x3006) {
            num = 80;
        } else if (fieldId == 0x3007) {
            num = 81;
        } else {
            num = 82;
        }
    } else {
        if (fieldId == 0x3001) {
            num = 44;
        } else if (fieldId == 0x3006) {
            num = 37;
        } else if (fieldId == 0x3007) {
            num = 38;
        } else {
            num = 39;
        }
    }

    return num;
}

void mBGMRoom_make_scene_bgm(BgmRoom* room) {
    if (room->element.num == 255 && mFI_CheckFieldData()) {
        u16 fieldId = mFI_GetFieldId();
        u8 num;

        switch (fieldId) {
            case 0x3001:
            case 0x3006:
            case 0x3007:
            case 0x3008:
            case 0x3009:
                num = mBGMRoom_make_scene_bgm_shop_get(room, fieldId);
                break;

            case 0x3002:
                num = 25;
                break;

            case 0x3003:
                if (common_data.unk10A6B != 0) {
                    num = 62;
                } else {
                    num = 41;
                }
                break;

            case 0x3004:
                num = 45;
                break;

            case 0x3005:
                num = 26;
                break;

            case 0x300A:
                num = 77;
                break;

            default:
                num = 255;
                break;
        }

        if (num != 255) {
            mBGMElem_default_set(&room->element);
            room->element.num = num;
            mBGMPsComp_make_ps_room(num, 0x168);
        }
    }
}

void mBGMRoom_delete_scene_bgm(BgmRoom* room) {
    if (room->element.num != 255) {
        mBGMPsComp_delete_ps_room(room->element.num, 0x168);
        room->element.num = 255;
    }
}

s32 mBGMRoom_shop_close_check(BgmRoom* room) {
    s32 res = FALSE;
    s32 fadeoutFlag = FALSE;

    if (mFI_CheckFieldData()) {
        u16 fieldId = mFI_GetFieldId();

        if (fieldId == 0x3001 || fieldId == 0x3006 || fieldId == 0x3007 || fieldId == 0x3008 || fieldId == 0x3009) {
            s32 realArbeit = mEv_CheckRealArbeit();

            fadeoutFlag =
                realArbeit == FALSE &&
                mBGMClock_range_time_check(&M_bgm.clock, room->shopCloseTime0, room->shopCloseTime1,
                                           BGM_CLOCK_CHECK_HOUR | BGM_CLOCK_CHECK_MIN | BGM_CLOCK_CHECK_SEC) != FALSE;

            res = realArbeit == FALSE &&
                  mBGMClock_over_time_check(&M_bgm.clock, room->shopCloseTime1,
                                            BGM_CLOCK_CHECK_HOUR | BGM_CLOCK_CHECK_MIN | BGM_CLOCK_CHECK_SEC) != FALSE;
        }
    }

    if (fadeoutFlag && room->shopFadeoutFlag == FALSE) {
        mBGMPsComp_make_ps_quietRoom(0x13DE);
        room->shopFadeoutFlag = TRUE;
    } else if (!fadeoutFlag && room->shopFadeoutFlag) {
        mBGMPsComp_delete_ps_quietRoom();
        room->shopFadeoutFlag = FALSE;
    }

    return res;
}

void mBGMRoom_move(BgmRoom* room, UNUSED Game_Play* play) {
    if (mBGMRoom_shop_close_check(room)) {
        room->deleteFlag = TRUE;
        room->makeFlag = TRUE;
    }

    if (room->deleteFlag) {
        mBGMRoom_delete_scene_bgm(room);
    }

    if (room->makeFlag) {
        mBGMRoom_make_scene_bgm(room);
    }

    room->makeFlag = FALSE;
    room->deleteFlag = FALSE;
}

void mBGMRoom_scene_bgm_make_req() {
    M_bgm.room.makeFlag = TRUE;
}

void mBGMRoom_scene_bgm_delete_req() {
    M_bgm.room.deleteFlag = TRUE;
}

void mBGMRoom_ct(BgmRoom* room) {
    bzero(room, sizeof(BgmRoom));
    mBGMElem_default_set(&room->element);
}

void mBGMTime_signal_melody(BgmTime* time) {
    static u8 signal_melody_buf[8];

    if (mEv_CheckFirstIntro() == FALSE && mEv_CheckTitleDemo() != -9 && mFI_CheckFieldData() &&
        FI_GET_TYPE(mFI_GetFieldId()) != 0x5000 && time->newYearEventFlag == FALSE) {
        mMld_GetMelody(signal_melody_buf);
        sAdo_Inst(0xFF, signal_melody_buf);
    }
}

int mBGMTime_silent_check(BgmTime* time) {
    if (time->newYearEventFlag) {
        return FALSE;
    }

    return mBGMClock_range_time_check(&M_bgm.clock, BGM_MIN_TIME_TO_BGM_MIN_TIME(59) | BGM_SEC_TIME_TO_BGM_SEC_TIME(52),
                                      BGM_MIN_TIME_TO_BGM_MIN_TIME(0) | BGM_SEC_TIME_TO_BGM_SEC_TIME(16),
                                      BGM_CLOCK_CHECK_MIN | BGM_CLOCK_CHECK_SEC);
}

void mBGMTime_new_year_ev_flag_set() {
    M_bgm.time.newYearEventFlag = TRUE;
}

void mBGMTime_new_year_ev_flag_clr() {
    M_bgm.time.newYearEventFlag = FALSE;
}

void mBGMTime_move_wait(BgmTime* time, UNUSED Game_Play* play) {
    if (mBGMTime_silent_check(time)) {
        mBGMPsComp_make_ps_time();
        time->moveFunc = &mBGMTime_move_change;
    }
}

void mBGMTime_move_change(BgmTime* time, UNUSED Game_Play* play) {
    if (mBGMClock_over_time_check(&M_bgm.clock, 0, BGM_CLOCK_CHECK_MIN | BGM_CLOCK_CHECK_SEC)) {
        mBGMTime_signal_melody(time);
    }

    if (mBGMTime_silent_check(time) == FALSE) {
        mBGMPsComp_delete_ps_time();
        time->moveFunc = &mBGMTime_move_wait;
    }
}

void mBGMTime_move(BgmTime* time, Game_Play* play) {
    time->moveFunc(time, play);
}

void mBGMTime_ct(BgmTime* time) {
    bzero(time, sizeof(BgmTime));
    time->moveFunc = &mBGMTime_move_wait;
}

s32 mBGMFieldSuddenEv_flag_check_arbeit(UNUSED BgmFieldSuddenEvent* fieldSuddenEvent, UNUSED Game_Play* play) {
    return mEv_CheckFirstJob();
}

typedef s32 (*BgmFieldSuddenEventFunc)(BgmFieldSuddenEvent*, Game_Play*);

void mBGMFieldSuddenEv_flag_set(BgmFieldSuddenEvent* fieldSudden, Game_Play* play) {
    static BgmFieldSuddenEventFunc ev_chk[] = { NULL, &mBGMFieldSuddenEv_flag_check_arbeit };

    fieldSudden->priorFlag = fieldSudden->flag;
    fieldSudden->flag = 0;

    if (mFI_CheckFieldData() && FI_GET_TYPE(mFI_GetFieldId()) == 0) {
        s32 i = 0;
        u32 mask = 1;

        for (; i < ARRAY_COUNT(ev_chk); i++) {
            if (ev_chk[i] != NULL && ev_chk[i](fieldSudden, play) != FALSE) {
                fieldSudden->flag |= mask;
            }

            mask <<= 1;
        }
    }
}

void mBGMFieldSuddenEv_ps_compose(BgmFieldSuddenEvent* fieldSudden, UNUSED Game_Play* play) {
    static u8 bgm_num_data[] = { 255, 52 };
    s32 now;
    s32 prior;
    s32 i;
    s32 mask;

    for (i = 0, mask = 1; i < ARRAY_COUNT(bgm_num_data); i++) {
        now = (fieldSudden->flag & mask) != 0;
        prior = (fieldSudden->priorFlag & mask) != 0;

        if (!now && prior) {
            mBGMPsComp_delete_ps_fieldSuddenEv(bgm_num_data[i], 0x168);
        }

        if (now && !prior) {
            mBGMPsComp_make_ps_fieldSuddenEv(bgm_num_data[i], 0x168, i);
        }

        mask <<= 1;
    }
}

void mBGMFieldSuddenEv_move(BgmFieldSuddenEvent* fieldSudden, Game_Play* play) {
    mBGMFieldSuddenEv_flag_set(fieldSudden, play);
    mBGMFieldSuddenEv_ps_compose(fieldSudden, play);
}

void mBGMFieldSuddenEv_ct(BgmFieldSuddenEvent* fieldSudden) {
    bzero(fieldSudden, sizeof(BgmFieldSuddenEvent));
}

s32 mbgm_pattern_data[3][3] = { { 2, 2, 2 }, { 0, 1, 2 }, { 0, 0, 2 } };

BgmEventData mbgm_event_data[] = {
    { -1, 255, BGM_EVENT_AREA_BLOCK, 0x8000 }, { 11, 55, BGM_EVENT_AREA_BLOCK, 0x8000 },
    { 13, 53, BGM_EVENT_AREA_EVERYWHERE, 0 },  { 26, 54, BGM_EVENT_AREA_EVERYWHERE, 0 },
    { 12, 56, BGM_EVENT_AREA_BLOCK, 4 },       { 16, 27, BGM_EVENT_AREA_BLOCK, 4 },
    { 21, 30, BGM_EVENT_AREA_BLOCK, 0x8000 },  { 22, 30, BGM_EVENT_AREA_BLOCK, 0x8000 },
    { 8, 27, BGM_EVENT_AREA_BLOCK, 4 },        { 10, 28, BGM_EVENT_AREA_BLOCK, 4 },
    { 7, 29, BGM_EVENT_AREA_BLOCK, 4 },        { 9, 60, BGM_EVENT_AREA_BLOCK, 4 },
    { 6, 31, BGM_EVENT_AREA_BLOCK, 0x8000 },   { -1, 32, BGM_EVENT_AREA_BLOCK, 0x8000 },
    { -1, 33, BGM_EVENT_AREA_BLOCK, 0x8000 },  { -1, 34, BGM_EVENT_AREA_BLOCK, 0x8000 },
    { -1, 35, BGM_EVENT_AREA_BLOCK, 0x8000 },  { -1, 57, BGM_EVENT_AREA_BLOCK, 0x8000 },
    { 3, 59, BGM_EVENT_AREA_BLOCK, 4 },        { -1, 36, BGM_EVENT_AREA_EVERYWHERE, 0 },
    { -1, 61, BGM_EVENT_AREA_EVERYWHERE, 0 },
};

s32 mBGMFieldSchedEv_bl_attr_get(s32 blockX, s32 blockZ, s32 eventArea, u32 blockType) {
    s32 attr = BGM_BL_ATTRIBUTE_INACTIVE;

    if (eventArea == BGM_EVENT_AREA_EVERYWHERE) {
        attr = BGM_BL_ATTRIBUTE_ACTIVE;
    } else if (blockType != 0) {
        s32 eventBlockX;
        s32 eventBlockZ;

        if (mFI_BlockKind2BkNum(&eventBlockX, &eventBlockZ, blockType)) {
            s32 diffBlockX = eventBlockX - blockX;
            s32 diffBlockZ = eventBlockZ - blockZ;

            if (diffBlockX == 0 && diffBlockZ == 0) {
                attr = BGM_BL_ATTRIBUTE_ACTIVE;
            } else if (eventArea == BGM_EVENT_AREA_BLOCK) {
                diffBlockX = ABS(diffBlockX);
                diffBlockZ = ABS(diffBlockZ);

                if ((diffBlockX == 0 && diffBlockZ == 1) || (diffBlockX == 1 && diffBlockZ == 0)) {
                    attr = BGM_BL_ATTRIBUTE_NEARBY;
                }
            }
        }
    }

    return attr;
}

s32 mBGMFieldSchedEv_bl_attr_evdata_get(BgmEventData* data, Game_Play* play) {
    Player* player = get_player_actor_withoutCheck(play);
    s32 attr = BGM_BL_ATTRIBUTE_MAX;

    if (player != NULL) {
        s32 wadeCheck = mFI_CheckPlayerWade(0) || mFI_CheckPlayerWade(3);
        s32 validPos;
        s32 blockX;
        s32 blockZ;

        if (wadeCheck) {
            s32 inform = M_bgm.force.inform;

            if (inform == 3 || inform == 4 || inform == 5 || inform == 6) {
                xyz_t priorPos;

                xyz_t_move_s_xyz(&priorPos, &common_data.eventDoorData.exitPos);
                validPos = mFI_Wpos2BlockNum(&blockX, &blockZ, priorPos);
            } else {
                validPos = mFI_Wpos2BlockNum(&blockX, &blockZ, player->actor.world.pos);
            }
        } else {
            validPos = mFI_GetNextBlockNum(&blockX, &blockZ);
        }

        if (validPos) {
            attr = mBGMFieldSchedEv_bl_attr_get(blockX, blockZ, data->eventArea, data->blockType);
        }
    }

    return attr;
}

void mBGMFieldSchedEv_Info_old_copy(BgmFieldScheduleInfo* info) {
    if ((info->flag & 1)) {
        info->flag |= 2;
    } else {
        info->flag &= ~2;
    }

    if ((info->flag & 4)) {
        info->flag |= 8;
    } else {
        info->flag &= ~8;
    }

    info->priorAttribute = info->attribute;
}

void mBGMFieldSchedEv_Info_ev_now_set_standard(BgmFieldScheduleInfo* info, BgmEventData* data, UNUSED Game_Play* play,
                                               s32 eventStartFlag) {
    if (eventStartFlag || (info->flag & 1)) {
        if (mEv_check_status(data->eventType, 1)) {
            info->flag |= 1;
        } else {
            info->flag &= ~1;
        }
    }
}

void mBGMFieldSchedEv_Info_ev_now_set_Silence_0(BgmFieldScheduleInfo* info, UNUSED BgmEventData* data,
                                                UNUSED Game_Play* play, UNUSED s32 eventStartFlag) {
    s32 eventNow = FALSE;

    if ((info->flag & 4) &&
        mBGMClock_over_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 59, 0),
                                  BGM_CLOCK_CHECK_ALL) &&
        mBGMFieldSchedEv_bl_attr_evdata_get(&mbgm_event_data[0], play) == BGM_BL_ATTRIBUTE_ACTIVE) {
        info->flag |= 0x10;
    }

    if (mBGMClock_range_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 59, 0),
                                   BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0), BGM_CLOCK_CHECK_ALL)) {
        if ((info->flag & 0x10)) {
            if (mEv_check_status(6, 8)) {
                eventNow = TRUE;
            }
        } else {
            eventNow = TRUE;
        }
    } else {
        info->flag &= ~0x10;
    }

    if (eventNow) {
        info->flag |= 1;
    } else {
        info->flag &= ~1;
    }
}

void mBGMFieldSchedEv_Info_ev_now_set_CountDown_1(BgmFieldScheduleInfo* info, UNUSED BgmEventData* data,
                                                  UNUSED Game_Play* play, UNUSED s32 eventStartFlag) {
    if (mEv_check_status(6, 1) &&
        mBGMClock_range_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 0, 0),
                                   BGM_RTC_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 30, 0), BGM_CLOCK_CHECK_ALL)) {
        info->flag |= 1;
    } else {
        info->flag &= ~1;
    }
}

void mBGMFieldSchedEv_Info_ev_now_set_CountDown_2(BgmFieldScheduleInfo* info, UNUSED BgmEventData* data,
                                                  UNUSED Game_Play* play, UNUSED s32 eventStartFlag) {
    if (mEv_check_status(6, 1) &&
        mBGMClock_range_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 30, 0),
                                   BGM_RTC_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 50, 0), BGM_CLOCK_CHECK_ALL)) {
        info->flag |= 1;
    } else {
        info->flag &= ~1;
    }
}

void mBGMFieldSchedEv_Info_ev_now_set_CountDown_3(BgmFieldScheduleInfo* info, UNUSED BgmEventData* data,
                                                  UNUSED Game_Play* play, UNUSED s32 eventStartFlag) {
    if (mEv_check_status(6, 1) &&
        mBGMClock_range_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 50, 0),
                                   BGM_RTC_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 55, 0), BGM_CLOCK_CHECK_ALL)) {
        info->flag |= 1;
    } else {
        info->flag &= ~1;
    }
}
void mBGMFieldSchedEv_Info_ev_now_set_CountDown_4(BgmFieldScheduleInfo* info, UNUSED BgmEventData* data,
                                                  UNUSED Game_Play* play, UNUSED s32 eventStartFlag) {
    if (mEv_check_status(6, 1) &&
        mBGMClock_range_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_DECEMBER, 31, 23, 55, 0),
                                   BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0), BGM_CLOCK_CHECK_ALL)) {
        info->flag |= 1;
    } else {
        info->flag &= ~1;
    }
}

void mBGMFieldSchedEv_Info_ev_now_set_CountDown_5(BgmFieldScheduleInfo* info, UNUSED BgmEventData* data,
                                                  Game_Play* play, UNUSED s32 eventStartFlag) {
    s32 eventNow = FALSE;

    if (mBGMClock_range_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                   BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 1, 0, 0), BGM_CLOCK_CHECK_ALL)) {
        if ((info->flag & 4) &&
            mBGMClock_over_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                      BGM_CLOCK_CHECK_ALL) &&
            mBGMFieldSchedEv_bl_attr_evdata_get(&mbgm_event_data[16], play) != BGM_BL_ATTRIBUTE_INACTIVE) {
            info->flag |= 0x20;
        }

        if ((info->flag & 0x20)) {
            UNUSED s32 scoped;

            if (mBGMFieldSchedEv_bl_attr_evdata_get(&mbgm_event_data[16], play) == BGM_BL_ATTRIBUTE_INACTIVE) {
                info->flag &= ~0x20;
            }
        }

        if (info->flag & 0x20) {
            if (mEv_check_status(6, 1)) {
                eventNow = TRUE;
            }
        }
    } else {
        info->flag &= ~0x20;
    }

    if (eventNow) {
        info->flag |= 1;
    } else {
        info->flag &= ~1;
    }
}

void mBGMFieldSchedEv_Info_ev_now_set_CountDown_6(BgmFieldScheduleInfo* info, UNUSED BgmEventData* data,
                                                  Game_Play* play, UNUSED s32 eventStartFlag) {
    s32 eventNow = FALSE;

    if (mBGMClock_range_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                   BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 1, 0, 0), BGM_CLOCK_CHECK_ALL)) {
        if ((info->flag & 4) &&
            mBGMClock_over_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                      BGM_CLOCK_CHECK_ALL) &&
            mBGMFieldSchedEv_bl_attr_evdata_get(&mbgm_event_data[17], play) != BGM_BL_ATTRIBUTE_INACTIVE) {
            info->flag |= 0x20;
        }

        if (info->flag & 0x20) {
            UNUSED s32 scoped;

            if (mBGMFieldSchedEv_bl_attr_evdata_get(&mbgm_event_data[17], play) == BGM_BL_ATTRIBUTE_INACTIVE) {
                info->flag &= ~0x20;
            }
        }

        if (!(info->flag & 0x20)) {
            if (mEv_check_status(6, 1)) {
                eventNow = TRUE;
            }
        }
    } else {
        info->flag &= ~0x20;
    }

    if (eventNow) {
        info->flag |= 1;
    } else {
        info->flag &= ~1;
    }
}

void mBGMFieldSchedEv_Info_ev_now_set_NewYear01(BgmFieldScheduleInfo* info, UNUSED BgmEventData* data,
                                                UNUSED Game_Play* play, UNUSED s32 eventStartFlag) {
    if (mBGMClock_range_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                   BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 18, 0, 0), BGM_CLOCK_CHECK_ALL)) {
        info->flag |= 1;
    } else {
        info->flag &= ~1;
    }
}

void mBGMFieldSchedEv_Info_ev_now_set_NewYear02(BgmFieldScheduleInfo* info, UNUSED BgmEventData* data,
                                                UNUSED Game_Play* play, UNUSED s32 eventStartFlag) {
    if (mBGMClock_range_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 18, 0, 0),
                                   BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 2, 0, 0, 0), BGM_CLOCK_CHECK_ALL)) {
        info->flag |= 1;
    } else {
        info->flag &= ~1;
    }
}

void mBGMFieldSchedEv_Info_attr_now_set(BgmFieldScheduleInfo* info, Game_Play* play, BgmEventData* data) {
    info->attribute = BGM_BL_ATTRIBUTE_INACTIVE;

    if ((info->flag & 5) == 5) {
        s32 attribute = mBGMFieldSchedEv_bl_attr_evdata_get(data, play);

        if (attribute < BGM_BL_ATTRIBUTE_MAX) {
            info->attribute = attribute;
        }
    }
}

typedef void (*BgmFieldScheduleEventInfoFunc)(BgmFieldScheduleInfo*, BgmEventData*, Game_Play*, s32);

void mBGMFieldSchedEv_info_set(BgmFieldScheduleEvent* schedule, Game_Play* play) {
    static BgmFieldScheduleEventInfoFunc ev_chk[] = {
        mBGMFieldSchedEv_Info_ev_now_set_Silence_0,   mBGMFieldSchedEv_Info_ev_now_set_standard,
        mBGMFieldSchedEv_Info_ev_now_set_standard,    mBGMFieldSchedEv_Info_ev_now_set_standard,
        mBGMFieldSchedEv_Info_ev_now_set_standard,    mBGMFieldSchedEv_Info_ev_now_set_standard,
        mBGMFieldSchedEv_Info_ev_now_set_standard,    mBGMFieldSchedEv_Info_ev_now_set_standard,
        mBGMFieldSchedEv_Info_ev_now_set_standard,    mBGMFieldSchedEv_Info_ev_now_set_standard,
        mBGMFieldSchedEv_Info_ev_now_set_standard,    mBGMFieldSchedEv_Info_ev_now_set_standard,
        mBGMFieldSchedEv_Info_ev_now_set_CountDown_1, mBGMFieldSchedEv_Info_ev_now_set_CountDown_2,
        mBGMFieldSchedEv_Info_ev_now_set_CountDown_3, mBGMFieldSchedEv_Info_ev_now_set_CountDown_4,
        mBGMFieldSchedEv_Info_ev_now_set_CountDown_5, mBGMFieldSchedEv_Info_ev_now_set_CountDown_6,
        mBGMFieldSchedEv_Info_ev_now_set_standard,    mBGMFieldSchedEv_Info_ev_now_set_NewYear01,
        mBGMFieldSchedEv_Info_ev_now_set_NewYear02,
    };

    BgmFieldScheduleInfo* info;
    BgmEventData* data;
    s32 i;
    s32 edge = mEv_check_status_edge(1);
    s32 validField = mFI_CheckFieldData() && FI_GET_TYPE(mFI_GetFieldId()) == 0;

    for (i = 0, info = schedule->info, data = mbgm_event_data; i < ARRAY_COUNT(mbgm_event_data); info++, i++, data++) {
        mBGMFieldSchedEv_Info_old_copy(info);
        info->flag &= ~4;

        if (validField) {
            info->flag |= 4;
        }

        ev_chk[i](info, data, play, edge);
        mBGMFieldSchedEv_Info_attr_now_set(info, play, data);
    }
}

void mBGMFieldSchedEv_Info_ps_delete(UNUSED BgmFieldScheduleInfo* info, BgmEventData* data, s32 flag) {
    mBGMPsComp_delete_ps_fieldSchedEv(data->num, 0x168);

    if (flag) {
        s32 num = mBGMPsComp_execute_bgm_num_get();

        if (num == data->num) {
            mBGMPsComp_search_cf_set_field(data->num, 10);
        }
    }
}
void mBGMFieldSchedEv_Info_ps_make(BgmFieldScheduleInfo* info, BgmEventData* data, s32 priority) {
    s32 updateVolumeCtrl =
        info->attribute != BGM_BL_ATTRIBUTE_INACTIVE && info->priorAttribute == BGM_BL_ATTRIBUTE_INACTIVE;
    s32 updateVolumeLevel = mbgm_pattern_data[data->eventArea][info->attribute] == 1;
    s32 crossfade = mBGMPsComp_execute_bgm_num_get() >= 0;
    u16 stopType = priority == 0 ? (u16)0xA8C : (u16)0x168;

    mBGMPsComp_make_ps_fieldSchedEv(data->num, updateVolumeCtrl, updateVolumeLevel, crossfade, stopType, priority);
}

void mBGMFieldSchedEv_Info_ps_volume_change(BgmFieldScheduleInfo* info, BgmEventData* data) {
    s32 flag = mbgm_pattern_data[data->eventArea][info->attribute] == 1;

    mBGMPsComp_volume_change_fieldSchedEv(data->num, TRUE, flag);
}

void mBGMFieldSchedEv_ps_compose(BgmFieldScheduleEvent* schedule, UNUSED Game_Play* play) {
    s32 i;
    s32 nowFlag = 0;
    s32 priorFlag;
    BgmFieldScheduleInfo* info;
    BgmEventData* data;
    s32 flag = TRUE;

    for (i = 0, info = schedule->info, data = mbgm_event_data; i < ARRAY_COUNT(mbgm_event_data); i++, info++, data++) {
        nowFlag = (info->flag & 5) == 5 && info->attribute != BGM_BL_ATTRIBUTE_INACTIVE;
        priorFlag = (info->flag & 10) == 10 && info->priorAttribute != BGM_BL_ATTRIBUTE_INACTIVE;

        if (!nowFlag && priorFlag) {
            mBGMFieldSchedEv_Info_ps_delete(info, data, flag);
        }

        if (nowFlag && !priorFlag) {
            if (data && data) {}
            mBGMFieldSchedEv_Info_ps_make(info, data, i);
        }

        if (nowFlag && priorFlag) {
            s32 nowVol = mbgm_pattern_data[data->eventArea][info->attribute];
            s32 priorVol = mbgm_pattern_data[data->eventArea][info->priorAttribute];

            if (nowVol != priorVol && nowVol != 0 && priorVol != 0 && data->num != 255) {
                mBGMFieldSchedEv_Info_ps_volume_change(info, data);
            }
        }

        if (flag && priorFlag) {
            flag = FALSE;
        }
    }
}
void mBGMFieldSchedEv_sp_flag(BgmFieldScheduleEvent* schedule) {
    BgmFieldScheduleInfo* info0 = &schedule->info[16];
    BgmFieldScheduleInfo* info1 = &schedule->info[17];

    if ((((info0->flag & 5) == 5 && info0->attribute != BGM_BL_ATTRIBUTE_INACTIVE) ||
         ((info1->flag & 5) == 5 && info1->attribute != BGM_BL_ATTRIBUTE_INACTIVE)) &&
        mBGMClock_range_time_check(&M_bgm.clock, BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 0, 0),
                                   BGM_RTC_TIME_TO_BGM_TIME(lbRTC_JANUARY, 1, 0, 1, 0), BGM_CLOCK_CHECK_ALL)) {
        mBGMTime_new_year_ev_flag_set();
    } else {
        mBGMTime_new_year_ev_flag_clr();
    }
}

void mBGMFieldSchedEv_move(BgmFieldScheduleEvent* schedule, Game_Play* play) {
    mBGMFieldSchedEv_info_set(schedule, play);
    mBGMFieldSchedEv_ps_compose(schedule, play);
    mBGMFieldSchedEv_sp_flag(schedule);
}

void mBGMFieldSchedEv_ct(BgmFieldScheduleEvent* schedule) {
    s32 i;
    bzero(schedule, sizeof(BgmFieldScheduleEvent));

    for (i = 0; i < ARRAY_COUNT(schedule->info); i++) {
        schedule->info[i].priorAttribute = BGM_BL_ATTRIBUTE_INACTIVE;
        schedule->info[i].attribute = BGM_BL_ATTRIBUTE_INACTIVE;
    }
}

u8 mBGMFieldNorm_bgm_num_get(s32 hour) {
    static u8 bgm_table[lbRTC_HOURS_PER_DAY] = { 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
                                                 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };

    return bgm_table[hour];
}

void mBGMFieldNorm_elem_set(BgmFieldNorm* norm) {
    s32 hour = common_data.time.rtcTime.hour % 24;

    mBGMElem_default_set(&norm->element);
    norm->element.num = mBGMFieldNorm_bgm_num_get(hour);
}

void mBGMFieldNorm_make_bgm(BgmFieldNorm* norm, UNUSED Game_Play* play) {
    if (norm->element.num == 255) {
        mBGMFieldNorm_elem_set(norm);
        mBGMPsComp_make_ps_fieldNorm(norm->element.num, 0x168);
    }
}

void mBGMFieldNorm_delete_bgm(BgmFieldNorm* norm) {
    if (norm->element.num != 255) {
        mBGMPsComp_delete_ps_fieldNorm(norm->element.num, norm->element.stopType0);
        norm->element.num = 255;
    }
}

void mBGMFieldNorm_move(BgmFieldNorm* norm, Game_Play* play) {
    if (mBGMClock_over_time_check(&M_bgm.clock, 0, BGM_CLOCK_CHECK_MIN | BGM_CLOCK_CHECK_SEC) && mFI_CheckFieldData() &&
        FI_GET_TYPE(mFI_GetFieldId()) == 0) {
        norm->deleteFlag = TRUE;
        norm->makeFlag = TRUE;
    }

    if (norm->deleteFlag) {
        mBGMFieldNorm_delete_bgm(norm);
    }

    if (norm->makeFlag) {
        mBGMFieldNorm_make_bgm(norm, play);
    }

    norm->makeFlag = FALSE;
    norm->deleteFlag = FALSE;
}

void mBGMFieldNorm_make_req() {
    M_bgm.fieldNorm.makeFlag = TRUE;
}

void mBGMFieldNorm_delete_req() {
    M_bgm.fieldNorm.deleteFlag = TRUE;
}

void mBGMFieldNorm_ct(BgmFieldNorm* norm) {
    bzero(norm, sizeof(BgmFieldNorm));
    mBGMElem_default_set(&norm->element);
}

void mBGMPs_counter_dec(BgmPS* ps) {
    if (ps->counter > 0) {
        ps->counter--;

        if (ps->counter == 0) {
            ps->cfFlags |= 1;
        }
    }
}

void mBGMPsComp_ps_remove(BgmPSComp* psComp, s32 removePos) {
    if (removePos >= 0 && removePos < BGM_PS_MAX) {
        if (removePos < psComp->psNum && psComp->psNum > 0) {
            s32 i;
            s32 max = psComp->psNum - 1;

            for (i = removePos; i < max; i++) {
                psComp->ps[i] = psComp->ps[i + 1];
            }

            bzero(&psComp->ps[max], sizeof(BgmPS));
            psComp->psNum = max;
        }
    }
}

s32 mBGMPsComp_search_insert_pos_kategorie(BgmPSComp* psComp, s32 category, u8 priority) {
    s32 max = psComp->psNum;
    s32 res = -1;

    if (max < BGM_PS_MAX) {
        s32 i = 0;
        BgmPS* ps = psComp->ps;

        res = max;
        for (; i < max; i++, ps++) {
            if ((category == ps->category && priority < ps->priority) || category < ps->category) {
                res = i;
                break;
            }
        }
    } else {
        res = -1;
    }

    return res;
}

s32 mBGMPsComp_search_pos_kategorie_bgm_num(BgmPSComp* psComp, s32 category, u8 num, s32 counterFlag, s32 delPass) {
    BgmPS* ps;
    s32 validCategory = category < 12;
    s32 bgmIsReset = num != 255;
    s32 res = -1;
    s32 mask = delPass != 0 ? 0 : 1;

    if (validCategory || bgmIsReset) {
        s32 max = psComp->psNum;
        s32 i = 0;

        for (ps = psComp->ps; i < max; i++, ps++) {
            if ((!validCategory || ps->category == category) && (bgmIsReset == 0 || ps->element.num == num) &&
                (counterFlag == FALSE || (ps->counter < 0 && (ps->cfFlags & 0x80) == 0)) &&
                ((ps->cfFlags & mask) == 0)) {
                res = i;
                break;
            }
        }
    }

    return res;
}

void mBGMPsComp_shift_behind(BgmPSComp* psComp, s32 shiftIdx) {
    if (psComp->psNum != 0) {
        s32 i;

        for (i = psComp->psNum - 1; i >= shiftIdx; i--) {
            bcopy(&psComp->ps[i], &psComp->ps[i + 1], sizeof(BgmPS));
        }
    }

    bzero(&psComp->ps[shiftIdx], sizeof(BgmPS));
    psComp->psNum++;
}

void mBGMPsComp_all_ps_bitclr(BgmPSComp* psComp, u8 bits) {
    BgmPS* ps;
    s32 max = psComp->psNum;
    s32 i = 0;

    for (ps = psComp->ps; i < max; i++, ps++) {
        ps->cfFlags &= ~bits;
    }
}

s32 mBGMPsComp_execute_ps_pos_get(BgmPSComp* psComp) {
    BgmPS* ps;
    s32 idx = -1;
    s32 max = psComp->psNum;
    s32 i = 0;

    for (ps = psComp->ps; i < max; i++, ps++) {
        if ((ps->cfFlags & 4)) {
            idx = i;
            break;
        }
    }

    return idx;
}

BgmPS* mBGMPsComp_high_ps_not_delete(BgmPSComp* psComp, s32 maxPos) {
    BgmPS* ps;
    BgmPS* highPs = NULL;
    s32 max = maxPos;
    s32 i = 0;

    for (ps = psComp->ps; i < max; i++, ps++) {
        if (!(ps->cfFlags & 1)) {
            highPs = ps;
            break;
        }
    }

    return highPs;
}

void mBGMPsComp_main_req_stop(BgmPSComp* psComp) {
    s32 executePos;
    BgmPS* ps;
    BgmPS* highPs;

    executePos = mBGMPsComp_execute_ps_pos_get(psComp);
    if (executePos >= 0) {
        ps = psComp->ps + executePos;

        if ((ps->cfFlags & 0x40) == 0) {
            if (executePos > 0) {
                highPs = mBGMPsComp_high_ps_not_delete(psComp, executePos);

                if (highPs != NULL) {
                    psComp->stop.requestFlag = TRUE;
                    psComp->stop.type = highPs->element.stopType1;
                    return;
                }
            }

            if ((ps->cfFlags & 0x1) && (ps->cfFlags & 0x100) == 0) {
                psComp->stop.requestFlag = TRUE;
                psComp->stop.type = ps->element.stopType0;
            }
        }
    }
}

void mBGMPsComp_main_remove(BgmPSComp* psComp) {
    BgmPS* ps;
    s32 i;

    for (i = psComp->psNum - 1, ps = &psComp->ps[i]; i >= 0; i--, ps--) {
        if ((ps->cfFlags & 1)) {
            ps->cfFlags &= ~1;
            mBGMPsComp_ps_remove(psComp, i);
        }
    }
}

void mBGMPsComp_main_req_start(BgmPSComp* psComp) {
    if (psComp->psNum > 0) {
        BgmPS* ps = &psComp->ps[0];

        if ((ps->cfFlags & 4) == 0) {
            if ((ps->cfFlags & 0x40) == 0) {
                psComp->start.requestFlag = TRUE;

                psComp->start.flags = ps->cfFlags & 0x8 ? 1 : 0;
                psComp->start.num = ps->element.num;

                if (mBGM_check_MD(ps->element.num) == FALSE) {
                    ps->cfFlags |= 2;
                }
            }

            mBGMPsComp_all_ps_bitclr(psComp, 4);
            ps->cfFlags |= 4;
        }

        mBGMPsComp_all_ps_bitclr(psComp, 8);
    }
}

void mBGMPsComp_main_req_pause(BgmPSComp* psComp) {
    if (psComp->pauseState == 1 || psComp->pauseState == 3) {
        psComp->pause.mode = 1;
        psComp->pause.requestFlag = TRUE;
    } else if (psComp->pauseState == 2) {
        psComp->pause.mode = 2;
        psComp->pause.requestFlag = TRUE;
    } else if (psComp->pauseState == 5) {
        psComp->pause.mode = 0;
        psComp->pause.requestFlag = TRUE;
    }
}

void mBGMPsComp_main_req_md(BgmPSComp* psComp) {
    if (psComp->md.moveFlag) {
        psComp->md.requestFlag = TRUE;
    }
}

void mBGMPsComp_main_md_move(BgmPSComp* psComp) {
    BgmPSMd* md = &psComp->md;

    if (md->deleteFlag) {
        md->moveFlag = FALSE;
        md->deleteFlag = FALSE;
    }

    if (md->makeFlag) {
        md->moveFlag = TRUE;
        md->makeFlag = FALSE;
    }
}

void mBGMPsComp_main_req_volume_ps(BgmPSComp* psComp) {
    if (psComp->psNum > 0) {
        if ((psComp->ps[0].cfFlags & 2)) {
            if ((psComp->ps[0].cfFlags & 0x10)) {
                psComp->volume.psVolumeMoveCounter = 90;
            } else {
                psComp->volume.psVolumeMoveCounter = 0;
            }

            if ((psComp->ps[0].cfFlags & 0x20)) {
                psComp->volume.psVolume = 0.5f;
            } else {
                psComp->volume.psVolume = 1.0f;
            }

            psComp->volume.psRequestFlag = TRUE;
        }

        mBGMPsComp_all_ps_bitclr(psComp, 0x12);
    }

    if (mBGMPsComp_execute_bgm_num_get() < 0) {
        psComp->volume.psVolume = -1.0f;
    }
}

void func_8005D2A4_jp(BgmPSComp* psComp) {
    if (psComp->fishInsectState == 1) {
        psComp->fishInsectState = 2;
        psComp->volume.fishingInsectVolume = 0.65f;
        psComp->volume.fishingInsectVolumeMoveCounter = 100;
        psComp->volume.fishingInsectRequestFlag = TRUE;
    } else if (psComp->fishInsectState == 3) {
        psComp->fishInsectState = 0;
        psComp->volume.fishingInsectVolume = -1.0f;
        psComp->volume.fishingInsectVolumeMoveCounter = 17;

        if (psComp->psNum <= 0 || mBGM_check_MD(psComp->ps[0].element.num) == FALSE) {
            psComp->volume.fishingInsectRequestFlag = TRUE;
        }
    }
}

void mBGMPsComp_main_req_volume_talk(BgmPSComp* psComp) {
    if (psComp->talkState == 1) {
        psComp->talkState = 2;
        psComp->volume.talkVolume = 0.7f;
        psComp->volume.talkRequestFlag = TRUE;
    } else if (psComp->talkState == 3) {
        psComp->talkState = 0;
        psComp->volume.talkVolume = -1.0f;

        if (psComp->psNum <= 0 || mBGM_check_MD(psComp->ps[0].element.num) == FALSE) {
            psComp->volume.talkRequestFlag = TRUE;
        }
    }
}

void mBGMPsComp_main_req_volume_pause(BgmPSComp* psComp) {
    if (psComp->pauseState == 1) {
        psComp->pauseState = 4;
        psComp->volume.pauseVolume = 0.5f;
        psComp->volume.pauseVolumeMoveCounter = 2;
        psComp->volume.pauseRequestFlag = TRUE;
    } else if (psComp->pauseState == 2) {
        psComp->pauseState = 4;
        psComp->volume.pauseVolume = 0.0f;
        psComp->volume.pauseVolumeMoveCounter = 2;
        psComp->volume.pauseRequestFlag = TRUE;
    } else if (psComp->pauseState == 3) {
        psComp->pauseState = 4;
        psComp->volume.pauseVolume = 0.5f;
        psComp->volume.pauseVolumeMoveCounter = 2;
        psComp->volume.pauseRequestFlag = TRUE;
    } else if (psComp->pauseState == 5) {
        psComp->pauseState = 0;
        psComp->volume.pauseVolume = -1.0f;
        psComp->volume.pauseVolumeMoveCounter = 2;

        if (psComp->psNum <= 0 || mBGM_check_MD(psComp->ps[0].element.num) == FALSE) {
            psComp->volume.pauseRequestFlag = TRUE;
        }
    }
}
void mBGMPsComp_main_req_volume(BgmPSComp* psComp) {
    f32 psVolume;
    f32 fishInsectVolume;
    f32 talkVolume;
    f32 pauseVolume;
    f32 finalVolume;
    u16 finalVolumeMoveCounter;
    BgmPS* ps = &psComp->ps[0];

    s32 ignoreTalk;
    s32 ignoreFishInsect;
    BgmPSVolume* volume;
    f32 psVolumeTemp;

    volume = &psComp->volume;

    ignoreTalk = psComp->psNum > 0 ? mBGM_check_ignore_talk_volume(ps->element.num) : FALSE;
    ignoreFishInsect = psComp->psNum > 0 ? func_8005ACA8_jp(ps->element.num) : FALSE;

    mBGMPsComp_main_req_volume_ps(psComp);
    func_8005D2A4_jp(psComp);
    mBGMPsComp_main_req_volume_talk(psComp);
    mBGMPsComp_main_req_volume_pause(psComp);

    psVolumeTemp = volume->psVolume;
    psVolume = psVolumeTemp;

    if (psVolumeTemp < 0.0f) {
        fishInsectVolume = -1.0f;
        talkVolume = -1.0f;
        pauseVolume = -1.0f;
    } else {
        fishInsectVolume =
            (volume->fishingInsectVolume < 0.0f || ignoreFishInsect) ? psVolume : volume->fishingInsectVolume;

        talkVolume = (volume->talkVolume < 0.0f || ignoreTalk) ? fishInsectVolume : volume->talkVolume;

        pauseVolume = (volume->pauseVolume < 0.0f) ? talkVolume : volume->pauseVolume;
    }

    finalVolume = -1.0f;
    finalVolumeMoveCounter = 0;

    if (volume->psRequestFlag) {
        finalVolume = psVolume;
        finalVolumeMoveCounter = volume->psVolumeMoveCounter;
    }

    if (volume->fishingInsectRequestFlag && !ignoreFishInsect) {
        finalVolume = fishInsectVolume;
        finalVolumeMoveCounter = volume->fishingInsectVolumeMoveCounter;
    }

    if (volume->talkRequestFlag && !ignoreTalk) {
        finalVolume = talkVolume;
        finalVolumeMoveCounter = 30;
    }

    if (volume->pauseRequestFlag) {
        finalVolume = pauseVolume;
        finalVolumeMoveCounter = volume->pauseVolumeMoveCounter;
    }

    if (psComp->pauseState == 4) {
        if ((finalVolume < 0) == FALSE) {
            finalVolume = pauseVolume;
        }
    } else if (psComp->talkState == 2) {
        if ((finalVolume < 0) == FALSE) {
            finalVolume = talkVolume;
        }
    } else if (psComp->fishInsectState == 2) {
        if ((finalVolume < 0) == FALSE) {
            finalVolume = fishInsectVolume;
        }
    }

    if ((finalVolume < 0.0f) == FALSE) {
        volume->mainVolume = finalVolume;
        volume->mainVolumeMoveCounter = finalVolumeMoveCounter;
        volume->mainRequestFlag = TRUE;
    }

    volume->psRequestFlag = FALSE;
    volume->fishingInsectRequestFlag = FALSE;
    volume->talkRequestFlag = FALSE;
    volume->pauseRequestFlag = FALSE;
}

void mBGMPsComp_MDPlayerPos_main_inform_sound(BgmPSMd* md) {
    if (md->requestFlag) {
        sAdo_MDPlayerPos(&md->pos, md->angle, md->mdType, md->ongenNum);
        md->requestFlag = FALSE;
    }
}

void mBGMPsComp_Arm_main_inform_sound(BgmPSArm* arm) {
    if (arm->requestFlag) {
        if (mBGMPsComp_execute_bgm_num_get() == 43) {
            sAdos_TTKK_ARM(arm->armState);

            if (arm->armState == 0) {
                mBGMPsComp_arm_delete();
            }
        } else {
            mBGMPsComp_arm_delete();
        }
    }
}

void mBGMPsComp_Stop_main_inform_sound(BgmPSStop* stop) {
    if (stop->requestFlag) {
        sAdo_BgmStop(stop->type);
        stop->requestFlag = FALSE;
    }
}

void mBGMPsComp_Start_main_inform_sound(BgmPSStart* start) {
    if (start->requestFlag) {
        if (start->flags != 0) {
            sAdo_BgmCrossfadeStart(start->num);
        } else {
            sAdo_BgmStart(start->num);

            if (start->num == 43) {
                if (common_data.save.sceneNo == SCENE_PLAYERSELECT_2) {
                    mBGMPsComp_arm_make(1);
                } else {
                    mBGMPsComp_arm_make(0);
                }
            }
        }

        start->requestFlag = FALSE;
    }
}

void mBGMPsComp_Volume_main_inform_sound(BgmPSVolume* volume) {
    if (volume->mainRequestFlag) {
        sAdo_BGMVolume(volume->mainVolume, volume->mainVolumeMoveCounter);
        volume->mainRequestFlag = FALSE;
    }
}

void mBGMPsComp_Pause_main_inform_sound(BgmPSPause* pause) {
    if (pause->requestFlag) {
        sAdo_Pause(pause->mode);
        pause->requestFlag = FALSE;
    }
}

void mBGMPsComp_main_inform_sound(BgmPSComp* psComp) {
    mBGMPsComp_MDPlayerPos_main_inform_sound(&psComp->md);
    mBGMPsComp_Arm_main_inform_sound(&psComp->arm);
    mBGMPsComp_Stop_main_inform_sound(&psComp->stop);
    mBGMPsComp_Start_main_inform_sound(&psComp->start);
    mBGMPsComp_Pause_main_inform_sound(&psComp->pause);
    mBGMPsComp_Volume_main_inform_sound(&psComp->volume);
}

void mBGMPsComp_main_counter_dec(BgmPSComp* psComp) {
    BgmPS* ps;
    s32 i;
    s32 max = psComp->psNum;

    for (i = 0, ps = psComp->ps; i < max; i++, ps++) {
        mBGMPs_counter_dec(ps);
    }
}

void mBGMPsComp_main_fo_check(BgmPSComp* psComp) {
    BgmPS* ps;
    s32 i;
    s32 max = psComp->psNum;

    for (i = 0, ps = psComp->ps; i < max; i++, ps++) {
        if (ps->cfFlags & 0x80) {
            s32 executePos = mBGMPsComp_execute_ps_pos_get(psComp);

            if ((executePos >= i || executePos < 0) || (psComp->ps[executePos].element.num == 255) ||
                (psComp->ps[executePos].cfFlags & 0x40)) {
                if (sAdo_BgmFadeoutCheck() == FALSE) {
                    continue;
                }
            }

            ps->cfFlags &= ~0x80;
            ps->cfFlags |= 1;
        }
    }
}

void mBGMPsComp_main_lost(BgmPSComp* psComp) {
    BgmPS* ps;
    s32 i;
    s32 max = psComp->psNum;

    for (i = 0, ps = psComp->ps; i < max; i++, ps++) {
        if ((ps->cfFlags & 0x100)) {
            ps->cfFlags |= 1;
        }
    }
}

s32 mBGMPsComp_make_ps(BgmPSComp* psComp, BgmElement* element, s32 category, s16 counter, u16 cfFlags, u8 priority) {
    s32 pos = mBGMPsComp_search_insert_pos_kategorie(psComp, category, priority);

    if (pos >= 0) {
        BgmPS* dstPs = &psComp->ps[pos];

        mBGMPsComp_shift_behind(psComp, pos);
        bcopy(element, &dstPs->element, sizeof(BgmElement));
        dstPs->category = category;
        dstPs->counter = counter;
        dstPs->cfFlags = cfFlags;
        dstPs->priority = priority;
    }

    return pos;
}

void _mBGMPsComp_make_ps_fanfare(u8 num, u16 stopType) {
    UNUSED s32 pad;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.num = num;
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(&M_bgm.psComp, &element, 0, -1, 0, 0xFF);
}

void mBGMPsComp_make_ps_fanfare(u8 num, u16 stopType) {
    _mBGMPsComp_make_ps_fanfare(num, stopType);
}

void _mBGMPsComp_make_ps_lost_fanfare(u8 num, u16 stopType) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.num = num;
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 0, -1, 0x100, 0xFF);
}

void mBGMPsComp_make_ps_lost_fanfare(u8 num, u16 stopType) {
    _mBGMPsComp_make_ps_lost_fanfare(num, stopType);
}

void _mBGMPsComp_make_ps_wipe(u16 stopType) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    if (mBGMForce_wipe_ps_make_permit(&M_bgm.force) &&
        mBGMPsComp_search_pos_kategorie_bgm_num(psComp, 1, 255, FALSE, FALSE) < 0) {
        mBGMElem_default_set(&element);
        element.stopType1 = stopType;
        mBGMPsComp_make_ps(&M_bgm.psComp, &element, 1, -1, 0x40, 0xFF);
    }
}

void mBGMPsComp_make_ps_wipe(u16 stopType) {
    _mBGMPsComp_make_ps_wipe(stopType);
}

void _mBGMPsComp_make_ps_quiet(u16 stopType) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 2, -1, 0x40, 0xFF);
}

void mBGMPsComp_make_ps_quiet(u16 stopType) {
    _mBGMPsComp_make_ps_quiet(stopType);
}

void _mBGMPsComp_make_ps_co_quiet(u16 stopType, s16 counter) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 2, counter, 0x40, 0xFF);
}

void mBGMPsComp_make_ps_co_quiet(u16 stopType, s16 counter) {
    _mBGMPsComp_make_ps_co_quiet(stopType, counter);
}

void _mBGMPsComp_make_ps_demo(u8 num, u16 stopType) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.num = num;
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 3, -1, 0, 0xFF);
}

void mBGMPsComp_make_ps_demo(u8 num, u16 stopType) {
    _mBGMPsComp_make_ps_demo(num, stopType);
}

void _mBGMPsComp_make_ps_happening(u8 num, u16 stopType) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.num = num;
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 4, -1, 0, 0xFF);
}

void mBGMPsComp_make_ps_happening(u8 num, u16 stopType) {
    _mBGMPsComp_make_ps_happening(num, stopType);
}

void mBGMPsComp_make_ps_quietRoom(u16 stopType) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 5, -1, 0x40, 0xFF);
}

void _mBGMPsComp_make_ps_room(u8 num, u16 stopType) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.num = num;
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 6, -1, 0, 0xFF);
}

void mBGMPsComp_make_ps_room(u8 num, u16 stopType) {
    _mBGMPsComp_make_ps_room(num, stopType);
}

void mBGMPsComp_make_ps_time() {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.stopType1 = 0x870;
    mBGMPsComp_make_ps(psComp, &element, 7, -1, 0x40, 0xFF);
}

void _mBGMPsComp_make_ps_quietField(u16 stopType) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 8, -1, 0x40, 0xFF);
}

void mBGMPsComp_make_ps_quietField(u16 stopType) {
    _mBGMPsComp_make_ps_quietField(stopType);
}

void _mBGMPsComp_make_ps_fc_quietField(u16 stopType) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 8, -1, 0xC0, 0xFF);
}

void mBGMPsComp_make_ps_fc_quietField(u16 stopType) {
    _mBGMPsComp_make_ps_fc_quietField(stopType);
}

void _mBGMPsComp_make_ps_fieldSuddenEv(u8 num, u16 stopType, u8 priority) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.num = num;
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 9, -1, 0, priority);
}

void mBGMPsComp_make_ps_fieldSuddenEv(u8 num, u16 stopType, u8 priority) {
    _mBGMPsComp_make_ps_fieldSuddenEv(num, stopType, priority);
}

void mBGMPsComp_make_ps_fieldSchedEv(u8 num, s32 updateVolumeMoveCounter, s32 updateVolumeFlag, s32 cfFlag,
                                     u16 stopType, u8 priority) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;
    u16 flags;

    mBGMElem_default_set(&element);
    element.num = num;
    element.stopType1 = stopType;
    flags = 0;

    if (updateVolumeMoveCounter) {
        flags |= 0x10;
    }

    if (updateVolumeFlag) {
        flags |= 0x20;
    }

    if (cfFlag) {
        flags |= 8;
    }

    if (num == 255) {
        flags |= 0x40;
    }

    mBGMPsComp_make_ps(psComp, &element, 10, -1, flags, priority);
}

void mBGMPsComp_make_ps_fieldNorm(u8 num, u16 stopType) {
    BgmPSComp* psComp = &M_bgm.psComp;
    BgmElement element;

    mBGMElem_default_set(&element);
    element.num = num;
    element.stopType1 = stopType;
    mBGMPsComp_make_ps(psComp, &element, 11, -1, 0, 0xFF);
}

void mBGMPsComp_delete_ps(BgmPSComp* psComp, s32 category, u8 num, u16 stopType, s32 counterFlag) {
    s32 searchNum = mBGMPsComp_search_pos_kategorie_bgm_num(psComp, category, num, counterFlag, FALSE);

    if (searchNum >= 0 && searchNum < psComp->psNum) {
        psComp->ps[searchNum].cfFlags |= 1;
        psComp->ps[searchNum].element.stopType0 = stopType;
    }
}

void _mBGMPsComp_delete_ps_fanfare(u8 num, u16 stopType) {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 0, num, stopType, FALSE);
}

void mBGMPsComp_delete_ps_fanfare(u8 num, u16 stopType) {
    _mBGMPsComp_delete_ps_fanfare(num, stopType);
}

void mBGMPsComp_delete_ps_wipe() {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 1, 255, 0x168, FALSE);
}

void _mBGMPsComp_delete_ps_quiet() {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 2, 255, 0x168, TRUE);
}

void mBGMPsComp_delete_ps_quiet() {
    _mBGMPsComp_delete_ps_quiet();
}

void _mBGMPsComp_delete_ps_demo(u8 num, u16 stopType) {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 3, num, stopType, FALSE);
}

void mBGMPsComp_delete_ps_demo(u8 num, u16 stopType) {
    _mBGMPsComp_delete_ps_demo(num, stopType);
}

void _mBGMPsComp_delete_ps_happening(u8 num, u16 stopType) {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 4, num, stopType, FALSE);
}

void mBGMPsComp_delete_ps_happening(u8 num, u16 stopType) {
    _mBGMPsComp_delete_ps_happening(num, stopType);
}

void mBGMPsComp_delete_ps_quietRoom() {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 5, 255, 0x168, TRUE);
}

void _mBGMPsComp_delete_ps_room(u8 num, u16 stopType) {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 6, num, stopType, FALSE);
}

void mBGMPsComp_delete_ps_room(u8 num, u16 stopType) {
    _mBGMPsComp_delete_ps_room(num, stopType);
}

void mBGMPsComp_delete_ps_time() {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 7, 255, 0x168, FALSE);
}

void _mBGMPsComp_delete_ps_quietField() {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 8, 255, 0x168, TRUE);
}

void mBGMPsComp_delete_ps_quietField() {
    _mBGMPsComp_delete_ps_quietField();
}

void _mBGMPsComp_delete_ps_fieldSuddenEv(u8 num, u16 stopType) {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 9, num, stopType, FALSE);
}

void mBGMPsComp_delete_ps_fieldSuddenEv(u8 num, u16 stopType) {
    _mBGMPsComp_delete_ps_fieldSuddenEv(num, stopType);
}

void mBGMPsComp_delete_ps_fieldSchedEv(u8 num, u16 stopType) {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 10, num, stopType, FALSE);
}

void mBGMPsComp_delete_ps_fieldNorm(u8 num, u16 stopType) {
    mBGMPsComp_delete_ps(&M_bgm.psComp, 11, num, stopType, FALSE);
}

void mBGMPsComp_volume_change_fieldSchedEv(u8 num, s32 updateVolumeCounter, s32 updateVolumeLevel) {
    BgmPSComp* psComp = &M_bgm.psComp;
    s32 posNum = mBGMPsComp_search_pos_kategorie_bgm_num(psComp, 10, num, FALSE, FALSE);

    if (posNum >= 0) {
        BgmPS* ps = &psComp->ps[posNum];

        if (updateVolumeCounter) {
            ps->cfFlags |= 0x10;
        }

        if (updateVolumeLevel) {
            ps->cfFlags |= 0x20;
        } else {
            ps->cfFlags &= ~0x20;
        }

        ps->cfFlags |= 2;
    }
}

void mBGMPsComp_search_cf_set_field(u8 num, s32 category) {
    BgmPSComp* psComp = &M_bgm.psComp;
    s32 posNum = mBGMPsComp_search_pos_kategorie_bgm_num(psComp, category, num, FALSE, TRUE);

    if (posNum >= 0) {
        s32 i;

        for (i = posNum + 1; i < psComp->psNum; i++) {
            if (psComp->ps[i].category == 9 || psComp->ps[i].category == 10 || psComp->ps[i].category == 11) {
                psComp->ps[i].cfFlags |= 0x18;
            }
        }
    }
}

void func_8005E9B4_jp() {
    M_bgm.psComp.fishInsectState = 1;
}

void func_8005E9C8_jp() {
    M_bgm.psComp.fishInsectState = 3;
}

void mBGMPsComp_volume_talk_start() {
    M_bgm.psComp.talkState = 1;
}

void mBGMPsComp_volume_talk_end() {
    BgmPSComp* psComp = &M_bgm.psComp;

    if (psComp->talkState != 0) {
        psComp->talkState = 3;
    }
}

void mBGMPsComp_pause(s32 state) {
    M_bgm.psComp.pauseState = state;
}

void mBGMPsComp_MDPlayerPos_make() {
    M_bgm.psComp.md.makeFlag = TRUE;
}

void mBGMPsComp_MDPlayerPos_delete() {
    M_bgm.psComp.md.deleteFlag = TRUE;
}

void mBGMPsComp_MDPlayerPos_param_set(xyz_t* pos, u16 angle, u16 mdType, u32 ongenNum) {
    BgmPSMd* md;

    md = &M_bgm.psComp.md;

    xyz_t_move(&md->pos, pos);
    md->angle = angle;
    md->mdType = mdType;
    md->ongenNum = ongenNum;
}

void mBGMPsComp_scene_mode(u8 mode) {
    sAdo_SceneMode(mode);
}

void mBGMPsComp_arm_make(s32 state) {
    BgmPSArm* arm = &M_bgm.psComp.arm;

    arm->requestFlag = TRUE;
    arm->armState = state;
}

void mBGMPsComp_arm_delete() {
    BgmPSArm* arm = &M_bgm.psComp.arm;

    arm->requestFlag = FALSE;
    arm->armState = 0;
}

s32 mBGMPsComp_execute_bgm_num_get() {
    BgmPSComp* psComp = &M_bgm.psComp;
    s32 pos = mBGMPsComp_execute_ps_pos_get(psComp);

    if (pos >= 0 && psComp->ps[pos].element.num != 255 && (psComp->ps[pos].cfFlags & 0x40) == 0) {
        return psComp->ps[pos].element.num;
    }

    return -1;
}

void mBGMPsComp_ct(BgmPSComp* psComp) {
    BgmPSVolume* volume = &psComp->volume;

    bzero(psComp, sizeof(BgmPSComp));

    volume->mainVolume = -1.0f;
    volume->mainVolumeMoveCounter = 0;
    volume->psVolume = -1.0f;
    volume->psVolumeMoveCounter = 0;
    volume->fishingInsectVolume = -1.0f;
    volume->fishingInsectVolumeMoveCounter = 100;
    volume->talkVolume = -1.0f;
    volume->pauseVolume = -1.0f;
    volume->pauseVolumeMoveCounter = 2;
}

s32 mBGMForce_wipe_ps_make_permit(BgmForce* force) {
    return force->roomNonstop == 0;
}

void mBGMForce_move_inform(BgmForce* force) {
    if (force->inform == 1) {
        s32 checkField = mFI_CheckFieldData();

        if (checkField == FALSE || (checkField != FALSE && FI_GET_TYPE(mFI_GetFieldId()) != 0)) {
            force->flag = TRUE;
            mBGMPsComp_make_ps_wipe(0x428A);
        }

        force->inform = 2;
    } else if (force->inform == 3) {
        force->inform = 4;
    } else if (force->inform == 5) {
        if (force->flag) {
            mBGMPsComp_make_ps_wipe(0x28A);
        }

        force->inform = 6;
    } else if (force->inform == 7) {
        force->inform = 0;
        force->flag = FALSE;
    }
}

void mBGMForce_move_room_nonstop(BgmForce* force) {
    if (force->roomNonstop == 1) {
        force->roomNonstop = 2;
    } else if (force->roomNonstop == 3) {
        force->roomNonstop = 0;
    }
}

void mBGMForce_move(BgmForce* force) {
    mBGMForce_move_inform(force);
    mBGMForce_move_room_nonstop(force);
}

void mBGMForce_ct(BgmForce* force) {
    bzero(force, sizeof(BgmForce));
}

void mBGMForce_inform_cleanup(BgmForce* force) {
    if (force->inform == 2) {
        force->inform = 3;
    } else if (force->inform == 6) {
        force->inform = 7;
    }
}

void mBGMForce_room_nonstop_cleanup(BgmForce* force) {
    if (force->roomNonstop == 2) {
        force->roomNonstop = 3;
    }
}

void mBGMForce_cleanup(BgmForce* force) {
    mBGMForce_inform_cleanup(force);
    mBGMForce_room_nonstop_cleanup(force);
}

void mBGMForce_inform_start() {
    M_bgm.force.inform = 1;
}

void mBGMForce_inform_end() {
    M_bgm.force.inform = 5;
}

void _mBGMForce_room_nonstop_start() {
    M_bgm.force.roomNonstop = 1;
}

void mBGMForce_room_nonstop_start() {
    _mBGMForce_room_nonstop_start();
}

void mBGM_main_control(Bgm* bgm) {
    BgmPSComp* psComp = &bgm->psComp;

    mBGMPsComp_main_req_md(psComp);
    mBGMPsComp_main_req_stop(psComp);
    mBGMPsComp_main_remove(psComp);
    mBGMPsComp_main_req_start(psComp);
    mBGMPsComp_main_req_pause(psComp);
    mBGMPsComp_main_req_volume(psComp);
    mBGMPsComp_main_inform_sound(psComp);
    mBGMPsComp_main_md_move(psComp);
    mBGMPsComp_main_counter_dec(psComp);
    mBGMPsComp_main_fo_check(psComp);
    mBGMPsComp_main_lost(psComp);
}

void mBGM_weather_set() {
    s16 weather = common_data.weather;

    if (weather >= mEnv_WEATHER_LEAVES) {
        weather = mEnv_WEATHER_SAKURA;
    } else if (weather < 0) {
        weather = mEnv_WEATHER_CLEAR;
    }

    sAdo_Tenki(weather);
}

void mBGM_main(Game* game) {
    Game_Play* play = (Game_Play*)game;

    mBGMClock_move(&M_bgm.clock, play);
    mBGMDemo_move(&M_bgm.demo, play);
    mBGMRoom_move(&M_bgm.room, play);
    mBGMFieldSuddenEv_move(&M_bgm.fieldSuddenEvent, play);
    mBGMFieldSchedEv_move(&M_bgm.fieldScheduleEvent, play);
    mBGMFieldNorm_move(&M_bgm.fieldNorm, play);
    mBGMTime_move(&M_bgm.time, play);
    mBGM_main_control(&M_bgm);
    mBGMForce_move(&M_bgm.force);
    mBGM_weather_set();
}

void mBGM_ct() {
    mBGMClock_ct(&M_bgm.clock);
    mBGMDemo_ct(&M_bgm.demo);
    mBGMRoom_ct(&M_bgm.room);
    mBGMTime_ct(&M_bgm.time);
    mBGMFieldSuddenEv_ct(&M_bgm.fieldSuddenEvent);
    mBGMFieldSchedEv_ct(&M_bgm.fieldScheduleEvent);
    mBGMFieldNorm_ct(&M_bgm.fieldNorm);
    mBGMPsComp_ct(&M_bgm.psComp);
    mBGMForce_ct(&M_bgm.force);
}

void mBGM_init() {
    mBGMPsComp_delete_ps_wipe();

    if (mFI_CheckFieldData()) {
        u16 fieldId = mFI_GetFieldId();
        u16 fieldType = FI_GET_TYPE(fieldId);
        BgmForce* force = &M_bgm.force;

        if (fieldType == 0) {
            if (mEv_CheckTitleDemo() > 0) {
                mBGMPsComp_make_ps_demo(70, 0x168);
            } else {
                if ((force->inform != 3 && force->inform != 7) || force->flag) {
                    mBGMFieldNorm_make_req();
                }

                if (force->inform == 3 && force->flag) {
                    mBGMPsComp_make_ps_quiet(0x168);
                }
            }
        } else if (fieldType == 0x3000 || fieldType == 0x4000 || fieldType == 0x6000) {
            if (force->roomNonstop != 3) {
                mBGMRoom_shop_close_time_set(&M_bgm.room);
                mBGMRoom_scene_bgm_make_req();
            }
        } else {
            mBGMDemo_scene_bgm_make_req();
        }
    }
}

void mBGM_cleanup() {
    BgmForce* force = &M_bgm.force;

    mBGMForce_cleanup(force);
    if (mFI_CheckFieldData()) {
        u16 fieldId = mFI_GetFieldId();
        u16 fieldType = FI_GET_TYPE(fieldId);

        if (fieldType == 0) {
            if (mEv_CheckTitleDemo() > 0) {
                mBGMPsComp_delete_ps_demo(70, 0x168);
            } else {
                if ((force->inform != 3 && force->inform != 7) || force->flag) {
                    mBGMFieldNorm_delete_req();
                }

                if (force->inform == 7 && force->flag) {
                    mBGMPsComp_delete_ps_quiet();
                }
            }
        } else if (fieldType == 0x3000 || fieldType == 0x4000 || fieldType == 0x6000) {
            if (force->roomNonstop != 3) {
                mBGMRoom_scene_bgm_delete_req();
            }
        } else {
            mBGMDemo_scene_bgm_delete_req();
        }
    }
}

void mBGM_reset() {
    Bgm* bgm = &M_bgm;
    BgmPSComp* psComp = &bgm->psComp;
    BgmPS* ps = psComp->ps;
    s32 i;
    s32 max = psComp->psNum;

    for (i = 0; i < max; i++, ps++) {
        ps->cfFlags |= 1;
        ps->element.stopType0 = 0x168;
    }

    psComp->talkState = 0;

    if (psComp->pauseState != 0) {
        sAdo_Pause(0);
        psComp->pauseState = 0;
    }

    mBGMDemo_ct(&bgm->demo);
    mBGMRoom_ct(&bgm->room);
    mBGMTime_ct(&bgm->time);
    mBGMFieldSuddenEv_ct(&bgm->fieldSuddenEvent);
    mBGMFieldSchedEv_ct(&bgm->fieldScheduleEvent);
    mBGMFieldNorm_ct(&bgm->fieldNorm);
    mBGMForce_ct(&bgm->force);
}
