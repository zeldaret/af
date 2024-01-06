#include "m_select.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_debug.h"
#include "6B81C0.h"
#include "6BA500.h"
#include "libu64/gfxprint.h"
#include "m_scene_table.h"
#include "macros.h"
#include "libc/alloca.h"
#include "m_rcp.h"
#include "audio.h"

#define nf_str(s0, s1) (s0 GFXPRINT_KATAKANA_MODE s1)
NameFunction nf_tbl[SCENE_NUM] = {
    { nf_str(" 1:", "ﾌｨｰﾙﾄﾞ ｺｰｽ1"), game_next_play, SCENE_TEST1 },
    { nf_str(" 2:", "ﾌｨｰﾙﾄﾞ ｺｰｽ2"), game_next_play, SCENE_TEST2 },
    { nf_str(" 3:", "ﾌｨｰﾙﾃﾞ ｺｰｽ3"), game_next_play, SCENE_TEST3 },
    { nf_str(" 4:", "ｵﾐｽﾞﾃｽﾄ ｺｰｽ"), game_next_play, SCENE_WATER_TEST },
    { nf_str(" 5:", "ｱｼｱﾄﾃｽﾄｺｰｽ"), game_next_play, SCENE_FOOTPRINT_TEST },
    { nf_str(" 6:", "npc ﾃｽﾄｺｰｽ"), game_next_play, SCENE_NPC_TEST },
    { nf_str(" 7:", "NPCｱﾚﾝｼﾞﾙｰﾑ"), game_next_play, SCENE_NPC_HOUSE },
    { nf_str(" 8:", "NPCﾗﾝﾀﾞﾑｺｰｽ"), game_next_play, SCENE_FG },
    { nf_str(" 9:", "FGﾂｰﾙ ﾌｨｰﾙﾄﾞﾖｳ"), game_next_play, SCENE_RANDOM_NPC_TEST },
    { nf_str("10:", "ｵﾐｾ"), game_next_play, SCENE_SHOP0 },
    { nf_str("11:", "BGﾌﾟﾚﾋﾞｭｰ ｶﾜﾅｼ"), game_next_play, SCENE_BG_TEST_NO_RIVER },
    { nf_str("12:", "BGﾌﾟﾚﾋﾞｭｰ ｶﾜｱﾘ"), game_next_play, SCENE_BG_TEST_RIVER },
    { nf_str("13:", "ﾔﾐﾌﾞﾛｰｶｰﾉ ｵﾐｾ"), game_next_play, SCENE_BROKER_SHOP },
    { nf_str("14:", "FGﾂｰﾙ ﾍﾔﾉﾅｶﾖｳ"), game_next_play, SCENE_FIELD_TOOL_INSIDE },
    { nf_str("15:", "ﾕｳﾋﾞﾝｷｮｸ"), game_next_play, SCENE_POST_OFFICE },
    { nf_str("16:", "start demo 1"), game_next_play, SCENE_START_DEMO },
    { nf_str("17:", "start demo 2"), game_next_play, SCENE_START_DEMO2 },
    { nf_str("18:", "ｺｳﾊﾞﾝ"), game_next_play, SCENE_POLICE_BOX },
    { nf_str("19:", "ﾎﾛﾊﾞｼｬ"), game_next_play, SCENE_BUGGY },
    { nf_str("20:", "ﾌﾟﾚｰﾔｰ ｾﾚｸﾄ"), game_next_play, SCENE_PLAYERSELECT },
    { nf_str("21:", "ﾏｲﾙｰﾑ size S"), game_next_play, SCENE_MY_ROOM_S },
    { nf_str("22:", "ﾏｲﾙｰﾑ size M"), game_next_play, SCENE_MY_ROOM_M },
    { nf_str("23:", "ﾏｲﾙｰﾑ size L"), game_next_play, SCENE_MY_ROOM_L },
    { nf_str("24:", "ｺﾝﾋﾞﾆ"), game_next_play, SCENE_CONVENI },
    { nf_str("25:", "ｽｰﾊﾟｰ"), game_next_play, SCENE_SUPER },
    { nf_str("26:", "ﾃﾞﾊﾟｰﾄ1F"), game_next_play, SCENE_DEPART },
    { nf_str("27:", "ﾃｽﾄｺｰｽ 5"), game_next_play, SCENE_TEST5 },
    { nf_str("28:", "ﾌﾟﾚｰﾔｰ ｾﾚｸﾄ 2"), game_next_play, SCENE_PLAYERSELECT_2 },
    { nf_str("29:", "ﾌﾟﾚｰﾔｰ ｾﾚｸﾄ 3"), game_next_play, SCENE_PLAYERSELECT_3 },
    { nf_str("30:", "ﾃﾞﾊﾟｰﾄ2F"), game_next_play, SCENE_DEPART_2 },
    { nf_str("31:", "ｲﾍﾞﾝﾄ ｺｸﾁ"), game_next_play, SCENE_EVENT_ANNOUNCEMENT },
    { nf_str("32:", "ｶﾏｸﾗ"), game_next_play, SCENE_KAMAKURA },
    { nf_str("33:", "for field tool"), game_next_play, SCENE_FIELD_TOOL },
    { nf_str("34:", "ｷｬｸﾏﾁ ﾃﾞﾓ"), game_next_play, SCENE_TITLE_DEMO },
    { nf_str("35:", "ﾌﾟﾚｰﾔｰ ｾﾚｸﾄ 4"), game_next_play, SCENE_PLAYERSELECT_SAVE },
};

void game_next_play(Game* game, s32 scene) {
    common_data.sceneNo = scene;
    STOP_GAMESTATE(game);
    SET_NEXT_GAMESTATE(game, play_init, sizeof(Game_Play));
    mHm_SetNowHome();
    common_data.unk_10754 = 0;
    func_800968C0_jp();
    common_data.unk_10140 = 1;
}

char data2fcode(char data) {
    char fcode = ' ';

    if (data != 0) {
        fcode = data + 0x90;
    }

    return fcode;
}

char fcode2data(char fcode) {
    char data = 0;
    if (fcode != ' ') {
        data = fcode - 0x90;
    }

    return data;
}

void select_pass(Game_Select* select) {
    lbRTC_time_c* rtc = &common_data.time.rtcTime;
    NameFunction* nfPtr;
    s32 scene = common_data.sceneFromTitleDemo;

    common_data.time.nowSec = rtc->hour * 3600 + rtc->min * 60 + rtc->sec;
    nfPtr = &nf_tbl[scene];
    if (nfPtr->nextProc != NULL) {
        (*nfPtr->nextProc)((Game*)select, nfPtr->sceneNo);
    }

    common_data.sceneFromTitleDemo = -1;
}

s32 select_start_proc(Game_Select* select) {
    NameFunction* nfPtr;
    s32 i;

    common_data.time.nowSec =
        common_data.time.rtcTime.hour * 3600 + common_data.time.rtcTime.min * 60 + common_data.time.rtcTime.sec;
    nfPtr = &nf_tbl[select->selectedScene];
    if (nfPtr->nextProc != NULL) {
        (*nfPtr->nextProc)((Game*)select, nfPtr->sceneNo);
    }

    DORO(80) = select->selectedScene;
    DORO(81) = select->topScene;

    if (common_data.time.rtcTime.min == 0) {
        common_data.time.timeSignal = 1;
    }

    for (i = 0; i < PLAYER_NAME_LEN; i++) {
        common_data.privateInfo->playerId.playerName[i] = data2fcode(select->name[i]);
    }

    return 1;
}

s32 select_check_start(Game_Select* select) {
    if (select->status == 0) {
        if (chkTrigger(START_BUTTON) || chkTrigger(A_BUTTON)) {
            return select_start_proc(select);
        }
    } else if (chkTrigger(START_BUTTON)) {
        return select_start_proc(select);
    }

    return 0;
}

s32 select_check_A_button_rtc(UNUSED Game_Select* select) {
    return FALSE;
}

s32 select_check_A_button_time(UNUSED Game_Select* select) {
    return FALSE;
}

s32 select_check_A_buttonStep(UNUSED Game_Select* select) {
    return FALSE;
}

s32 select_check_A_button_weather(UNUSED Game_Select* select) {
    s32 weather = common_data.weather;
    weather++;
    if (weather >= 5 || weather < 0) {
        weather = 0;
    }

    common_data.weather = weather;
    common_data.weatherIntensity = 3;

    {
        u8 saved;
        saved = weather;
        saved = weather << 4;
        common_data.saveWeather = saved | 3;
    }

    return 0;
}

s32 select_check_A_button_sex(UNUSED Game_Select* select) {
    s32 sex = common_data.privateInfo->gender;
    sex++;
    sex %= mPr_SEX_NUM;
    common_data.privateInfo->gender = sex;

    return FALSE;
}

s32 select_check_A_button_face_type(UNUSED Game_Select* select) {
    s32 face_type = common_data.privateInfo->face;
    face_type++;
    face_type %= mPr_FACE_TYPE_NUM;
    common_data.privateInfo->face = face_type;

    return FALSE;
}

s32 select_check_A_button_swell(UNUSED Game_Select* select) {
    s32 sting;

    sting = common_data.beeStingFlag;
    if (sting != 0) {
        sting = 0;
    } else {
        sting = 1;
    }

    common_data.beeStingFlag = sting;

    return FALSE;
}

s32 select_check_A_button_decoy(UNUSED Game_Select* select) {
    s32 decoy;

    decoy = common_data.playerDecoyFlag;
    if (decoy != 0) {
        decoy = 0;
    } else {
        decoy = 1;
    }
    common_data.playerDecoyFlag = decoy;

    return FALSE;
}

s32 select_check_A_button_cloth(UNUSED Game_Select* select) {
    return FALSE;
}

s32 select_check_A_button_event(UNUSED Game_Select* select) {
    return FALSE;
}

typedef s32 (*SelectCheckProc)(Game_Select*);

s32 select_check_A_button(Game_Select* select) {
    static SelectCheckProc process[] = {
        &select_check_A_button_rtc,     &select_check_A_button_time,  &select_check_A_buttonStep,
        &select_check_A_button_weather, &select_check_A_button_sex,   &select_check_A_button_face_type,
        &select_check_A_button_swell,   &select_check_A_button_decoy, &select_check_A_button_cloth,
        &select_check_A_button_event,
    };

    if (chkTrigger(A_BUTTON)) {
        return (*process[select->cursorY])(select);
    } else {
        return FALSE;
    }
}

s32 select_move_cursol(Game_Select* select) {
    if (chkTrigger(L_JPAD)) {
        select->status = 0;
        return TRUE;
    } else if (chkTrigger(U_JPAD)) {
        if (select->cursorY == 0) {
            select->cursorY = SELECT_CHECK_A_BUTTON_NUM - 1;
        } else {
            select->cursorY--;
        }
    } else if (chkTrigger(D_JPAD)) {
        select->cursorY = (select->cursorY + 1) % SELECT_CHECK_A_BUTTON_NUM;
    }

    return FALSE;
}

s32 select_course_step_sub(s32 course) {
    if (course < 0) {
        course += 0x23;
    } else if (course >= 0x23) {
        course -= 0x23;
    }

    return course;
}

void select_adjust_top_no(Game_Select* select, s32 course, s32 adjust) {
    s32 top = select->topScene;
    s32 newTop = (select->topScene + 0xE) % 0x23;

    if (top < newTop) {
        if (course <= top || course >= newTop) {
            top = select_course_step_sub(top + adjust);
        }
    } else if (course <= top && course >= newTop) {
        top = select_course_step_sub(top + adjust);
    }

    select->topScene = top;
}

void select_course_step(Game_Select* select, s32 addend) {
    s32 step = select->step + addend;

    if (ABS(step) >= 32) {
        s32 course = select->selectedScene;
        sAdo_SysTrgStart(1);

        if (step > 0) {
            step = 0;
            course = select_course_step_sub(course + 1);
            select_adjust_top_no(select, course, 1);
        } else {
            step = 0;
            course = select_course_step_sub(course - 1);
            select_adjust_top_no(select, course, -1);
        }

        select->stepAdd = 6;
        select->selectedScene = course;
    }

    select->step = step;
}

void select_course(Game_Select* select) {
    if (chkTrigger(U_JPAD)) {
        if (select->step > 0) {
            select->step = 0;
        }

        select_course_step(select, -32);
        select->stepAdd = 1;
    } else if (chkButton(U_JPAD)) {
        select_course_step(select, -select->stepAdd);
    } else if (chkTrigger(D_JPAD)) {
        if (select->step < 0) {
            select->step = 0;
        }

        select_course_step(select, 32);
        select->stepAdd = 1;
    } else if (chkButton(D_JPAD)) {
        select_course_step(select, select->stepAdd);
    }
}

void select_move_main(Game_Select* select) {
    if (select_check_start(select) != TRUE) {
        if (chkTrigger(R_JPAD)) {
            select->status = 1;
        } else {
            select_course(select);
        }
    }
}

void select_move_setup(Game_Select* select) {
    if (select_check_start(select) != TRUE && select_move_cursol(select) != TRUE) {
        if (select_check_A_button(select) == TRUE) {}
    }
}

void select_move_time_year_set(s32 adjust) {
    s32 year = common_data.time.rtcTime.year;
    year += adjust;

    if (year > lbRTC_YEAR_MAX) {
        year -= ((lbRTC_YEAR_MAX - lbRTC_YEAR_MIN) + 1);
    } else if (year < lbRTC_YEAR_MIN) {
        year = lbRTC_YEAR_MAX - ((lbRTC_YEAR_MIN - 1) - year);
    }

    common_data.time.rtcTime.year = year;
}

void select_move_time_month_set(s32 adjust) {
    static s32 season_table[] = {
        SPRING, WINTER, WINTER, SPRING, SPRING, SPRING, SUMMER, SUMMER, SUMMER, FALL, FALL, FALL, WINTER,
    };

    s32 month;
    month = common_data.time.rtcTime.month;
    month = (month + adjust);
    month %= (lbRTC_MONTHS_MAX + 1);

    if (month == 0) {
        month = (adjust > 0) ? 1 : 12;
    }
    common_data.time.rtcTime.month = month;
    {
        u8 save = lbRTC_GetDaysByMonth(common_data.time.rtcTime.year, common_data.time.rtcTime.month);
        if (common_data.time.rtcTime.day > save) {
            common_data.time.rtcTime.day = save;
        }
    }

    common_data.time.season = season_table[month];
}

void select_move_time_day_set(s32 adjust) {
    u8 max_day = lbRTC_GetDaysByMonth(common_data.time.rtcTime.year, common_data.time.rtcTime.month);
    s32 day = common_data.time.rtcTime.day;
    day = (day + adjust) % (max_day + 1);

    if (day == 0) {
        day = (adjust > 0) ? 1 : max_day;
    }

    common_data.time.rtcTime.day = day;
}

void select_move_time_hour_set(s32 adjust) {
    s32 hour = common_data.time.rtcTime.hour;
    if (hour == 0 && adjust < 0) {
        hour = lbRTC_HOURS_PER_DAY - 1;
    } else {
        hour = (hour + adjust) % lbRTC_HOURS_PER_DAY;
    }

    common_data.time.rtcTime.hour = hour;
}

void select_move_time_min_set(s32 adjust) {
    s32 min = common_data.time.rtcTime.min;
    if (min == 0 && adjust < 0) {
        min = lbRTC_MINUTES_PER_HOUR - 1;
    } else {
        min = (min + adjust) % lbRTC_MINUTES_PER_HOUR;
    }

    common_data.time.rtcTime.min = min;
}

void select_move_time_week_set(s32 adjust) {
    static lbRTC_time_c base = {
        0,
        0,
        0, // 00:00:00
        1,
        lbRTC_SATURDAY,
        lbRTC_JANUARY, // Sunday Jan 1st
        2000,
    };

    if (adjust != 0) {
        u32 interval = lbRTC_IntervalTime(&common_data.time.rtcTime, &base);
        interval = interval / (lbRTC_HOURS_PER_DAY * lbRTC_MINUTES_PER_HOUR) + (lbRTC_WEEK - 1);
        common_data.time.rtcTime.weekday = interval % lbRTC_WEEK;
    }
}

typedef void (*SelectMoveTimeProc)(s32);

void select_move_time_set(Game_Select* select) {
    if (chkTrigger(A_BUTTON) || chkTrigger(START_BUTTON)) {
        select->status = 1;
        if (common_data.time.rtcEnabled == TRUE) {
            lbRTC_SetTime(&common_data.time.rtcTime);
        }
    } else if (chkTrigger(L_JPAD)) {
        if (select->cursorX == 0) {
            select->cursorX = 4;
        } else {
            select->cursorX--;
        }
    } else if (chkTrigger(R_JPAD)) {
        select->cursorX = (select->cursorX + 1) % 5;
    } else {
        int adjust = 0;

        if (chkButton(D_JPAD)) {
            if (chkTrigger(D_JPAD)) {

                select->buttonStep = -16;
                adjust = -1;
            }

            select->buttonStep++;
            if (select->buttonStep == 6) {
                select->buttonStep = 0;
                adjust = -1;
            }
        }

        if (chkButton(U_JPAD)) {
            if (chkTrigger(U_JPAD)) {

                select->buttonStep = 16;
                adjust = 1;
            }

            select->buttonStep--;
            if (select->buttonStep == -6) {
                select->buttonStep = 0;
                adjust = 1;
            }
        }

        if (chkButton(B_BUTTON)) {
            adjust *= 10;
        }

        {
            static SelectMoveTimeProc process[5] = {
                &select_move_time_year_set, &select_move_time_month_set, &select_move_time_day_set,
                &select_move_time_hour_set, &select_move_time_min_set,
            };

            int i;

            for (i = 0; i < 5; i++) {
                if (i == select->cursorX) {
                    (*process[i])(adjust);
                    select_move_time_week_set(adjust);
                }
            }

            if (adjust != 0 && common_data.time.rtcEnabled == TRUE) {
                lbRTC_SetTime(&common_data.time.rtcTime);
            }
        }
    }
}

void select_move_cloth_sel(Game_Select* select) {
    if (chkTrigger(A_BUTTON) || chkTrigger(START_BUTTON)) {
        select->status = 1;
    } else {
        int cloth = common_data.privateInfo->cloth.item - 0x2401; // shouldn't this be CLOTH000?
        int adjust = (chkButton(B_BUTTON)) ? 10 : 1;

        if (chkButton(D_JPAD)) {
            if (chkTrigger(D_JPAD)) {
                select->buttonStep = -16;
                cloth += adjust;
            }

            select->buttonStep++;
            if (select->buttonStep == 6) {
                select->buttonStep = 0;
                cloth += adjust;
            }
        }

        if (chkButton(U_JPAD)) {
            if (chkTrigger(U_JPAD)) {
                select->buttonStep = 16;
                cloth -= adjust;
            }

            select->buttonStep--;
            if (select->buttonStep == -6) {
                select->buttonStep = 0;
                cloth -= adjust;
            }
        }

        while (cloth < 0) {
            cloth += 255;
        }

        while (cloth > 255 - 1) {
            cloth -= 255;
        }

        common_data.privateInfo->cloth.item = 0x2401 + cloth;
    }
}

typedef void (*SelectMoveProc)(Game_Select*);

void select_move(Game_Select* select) {
    static SelectMoveProc process[] = {
        &select_move_main,
        &select_move_setup,
        &select_move_time_set,
        &select_move_cloth_sel,
    };

    if (common_data.sceneFromTitleDemo >= 0) {
        select_pass(select);
    } else {
        (*process[select->status])(select);
    }
}

void select_print_wait(gfxprint* gfxprint) {
    static const char* msgs[12] = {
        GFXPRINT_HIRAGANA_MODE "ｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ", /* (しばらくお待ち下さい) "Please wait for a bit" */
        GFXPRINT_HIRAGANA_MODE "ﾁｮｯﾄ ﾏｯﾃﾈ",     /* (ちょっと 待ってね) "Wait a minute" */
        GFXPRINT_KATAKANA_MODE "ｳｪｲﾄ ｱ ﾓｰﾒﾝﾄ",  /* "Wait a moment" */
        GFXPRINT_KATAKANA_MODE "ﾛｰﾄﾞ" GFXPRINT_HIRAGANA_MODE "ﾁｭｳ", /* (ロード中) "Loading" */
        GFXPRINT_HIRAGANA_MODE "ﾅｳ ﾜｰｷﾝｸﾞ",                         /* "Now working" */
        GFXPRINT_HIRAGANA_MODE "ｲﾏ ﾂｸｯﾃﾏｽ",                         /* (今つくってます) "Now making" */
        GFXPRINT_HIRAGANA_MODE "ｺｼｮｳｼﾞｬﾅｲﾖ",                        /* (故障じゃないよ) "It's not faulty" */
        GFXPRINT_KATAKANA_MODE "ｺｰﾋｰ ﾌﾞﾚｲｸ",                        /* "coffee break" */
        GFXPRINT_KATAKANA_MODE "Bﾒﾝｦｾｯﾄｼﾃｸﾀﾞｻｲ", /* (Bメンヲ セットしてください) "Please set the B menu" */
        GFXPRINT_HIRAGANA_MODE "ｼﾞｯﾄ" GFXPRINT_KATAKANA_MODE "ｶﾞﾏﾝ" GFXPRINT_HIRAGANA_MODE "ﾉ" GFXPRINT_KATAKANA_MODE
                               "ｺ" GFXPRINT_HIRAGANA_MODE "ﾃﾞｱｯﾀ", /* (ジっと我慢のこであった) "I am patient" */
        GFXPRINT_HIRAGANA_MODE "ｲﾏｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ", /* (今しばらくお待ちください) "Please wait a moment now" */
        GFXPRINT_HIRAGANA_MODE "ｱﾜﾃﾅｲｱﾜﾃﾅｲ｡ﾋﾄﾔｽﾐﾋﾄﾔｽﾐ｡", /* (あわてないあわてない｡ ひとやすみひとやすみ｡) "Don't rush,
                                                           don't rush. Take a break, take a break." */
    };

    s32 msg;
    gfxprint_locate8x8(gfxprint, 10, 15);
    gfxprint_color(gfxprint, 255, 255, 255, 255);
    msg = RANDOM(12.0f);
    gfxprint_printf(gfxprint, "%s", msgs[msg]);
}

void select_print_course_name(Game_Select* select, gfxprint* gfxprint) {
    const char* name;
    s32 i;
    s32 course;

    gfxprint_color(gfxprint, 255, 155, 150, 255);
    gfxprint_locate8x8(gfxprint, 12, 2);
    gfxprint_printf(gfxprint, "FOREST MAP SELECT");

    gfxprint_color(gfxprint, 255, 255, 255, 255);
    for (i = 0; i < 15; i++) {
        gfxprint_locate8x8(gfxprint, 5, i + 4);
        course = (select->topScene + i + 35) % 35;
        if (course == select->selectedScene) {
            if (select->status != 0) {
                gfxprint_color(gfxprint, 255, 120, 120, 255);

            } else {
                gfxprint_color(gfxprint, 255, 20, 20, 255);
            }
        } else {
            gfxprint_color(gfxprint, 200, 200, 55, 255);
        }

        name = nf_tbl[course].name;
        if (name == NULL) {
            name = "**Null**";
        }

        gfxprint_printf(gfxprint, "%s", name);
    }
}

void select_print_rtc(gfxprint* gfxprint, UNUSED Game_Select* select) {
    gfxprint_locate8x8(gfxprint, 23, 6);
    gfxprint_printf(gfxprint, "RTC  Z:USE");
}

void select_print_time_sub(gfxprint* gfxprint, Game_Select* select, lbRTC_time_c* time) {
    const char* weekday_name;

    gfxprint_locate8x8(gfxprint, 23, 7);
    gfxprint_printf(gfxprint, "%04d/%02d/%02d", time->year, time->month, time->day);

    gfxprint_locate8x8(gfxprint, 33, 7);
    switch (time->weekday) {
        case lbRTC_SUNDAY:
            weekday_name = "SUN";
            break;

        case lbRTC_MONDAY:
            weekday_name = "MON";
            break;

        case lbRTC_TUESDAY:
            weekday_name = "TUE";
            break;

        case lbRTC_WEDNESDAY:
            weekday_name = "WED";
            break;

        case lbRTC_THURSDAY:
            weekday_name = "THU";
            break;

        case lbRTC_FRIDAY:
            weekday_name = "FRI";
            break;

        case lbRTC_SATURDAY:
            weekday_name = "SAT";
            break;

        default:
            weekday_name = "---";
            break;
    }

    gfxprint_printf(gfxprint, "<%s>", weekday_name);

    gfxprint_locate8x8(gfxprint, 28, 8);
    gfxprint_printf(gfxprint, "%02d:%02d", time->hour, time->min);

    if (select->status == 2) {
        gfxprint_color(gfxprint, 255, 180, 180, 255);

        switch (select->cursorX) {
            case 0: {
                gfxprint_locate8x8(gfxprint, 23, 7);
                gfxprint_printf(gfxprint, "%04d", time->year);
                break;
            }

            case 1: {
                gfxprint_locate8x8(gfxprint, 28, 7);
                gfxprint_printf(gfxprint, "%02d", time->month);
                break;
            }

            case 2: {
                gfxprint_locate8x8(gfxprint, 31, 7);
                gfxprint_printf(gfxprint, "%02d", time->day);
                break;
            }

            case 3: {
                gfxprint_locate8x8(gfxprint, 28, 8);
                gfxprint_printf(gfxprint, "%02d", time->hour);
                break;
            }

            case 4: {
                gfxprint_locate8x8(gfxprint, 31, 8);
                gfxprint_printf(gfxprint, "%02d", time->min);
                break;
            }
        }
    }
}

void select_print_time(gfxprint* gfxprint, Game_Select* select) {
    lbRTC_time_c time;

    lbRTC_GetTime(&time);
    select_print_time_sub(gfxprint, select, &time);
}

void select_print_step_sub2(gfxprint* gfxprint) {
    gfxprint_locate8x8(gfxprint, 23, 9);
    gfxprint_printf(gfxprint, GFXPRINT_KATAKANA_MODE "ｽﾃｯﾌﾟ :**m**s");
}

void select_print_step(gfxprint* gfxprint, UNUSED Game_Select* select) {
    select_print_step_sub2(gfxprint);
}

void select_print_weather(gfxprint* gfxprint, UNUSED Game_Select* select) {
    static const char* Weather_type[] = {
        GFXPRINT_HIRAGANA_MODE "ﾊﾚ",   // 晴れ (clear/fine)
        GFXPRINT_HIRAGANA_MODE "ｱﾒ",   // 雨 (rain)
        GFXPRINT_HIRAGANA_MODE "ﾕｷ",   // 雪 (snow)
        GFXPRINT_HIRAGANA_MODE "ｻｸﾗ",  // 桜 (cherry blossoms)
        GFXPRINT_HIRAGANA_MODE "ﾗﾝﾀﾞﾑ" // "random" (should be leaves seen in K.K. Slider demo)
    };

    gfxprint_locate8x8(gfxprint, 23, 10);
    gfxprint_printf(gfxprint, GFXPRINT_HIRAGANA_MODE "ﾃﾝｷ   :%s", Weather_type[common_data.weather]);
}

void select_print_sex(gfxprint* gfxprint, UNUSED Game_Select* select) {
    static const char* Distinction[mPr_SEX_NUM] = {
        GFXPRINT_HIRAGANA_MODE "ｵﾄｺﾉｺ", // 男の子 (boy)
        GFXPRINT_HIRAGANA_MODE "ｵﾝﾅﾉｺ"  // 女の子 (girl)
    };

    gfxprint_locate8x8(gfxprint, 23, 11);
    gfxprint_printf(gfxprint, "ｾｲﾍﾞﾂ :%s", Distinction[common_data.privateInfo->gender]);
}

void select_print_cloth(gfxprint* gfxprint, Game_Select* select) {
    gfxprint_locate8x8(gfxprint, 23, 15);
    if (select->status == 3) {
        gfxprint_color(gfxprint, 255, 180, 180, 255);
    }

    gfxprint_printf(gfxprint, "ﾌｸ    :%03d", common_data.privateInfo->cloth.item - 0x2400);
}

void select_print_swell(gfxprint* gfxprint, UNUSED Game_Select* select) {
    s32 swell = common_data.beeStingFlag;
    gfxprint_locate8x8(gfxprint, 23, 13);

    if (swell == FALSE) {
        gfxprint_printf(gfxprint, "ﾑｼｻｻﾚ :ｲﾀｸﾅｲ"); // 虫刺され: 痛くない (sting: painless)
    } else {
        gfxprint_printf(gfxprint, "ﾑｼｻｻﾚ :ｲﾀｿｳ"); // 虫刺され: 痛そう (sting: painful)
    }
}

void select_print_decoy(gfxprint* gfxprint, UNUSED Game_Select* select) {
    s32 decoy = common_data.playerDecoyFlag;
    gfxprint_locate8x8(gfxprint, 23, 14);

    if (decoy == FALSE) {
        gfxprint_printf(gfxprint, "ﾃﾞｰﾀ  :ﾓﾉﾎﾝ"); // (data: genuine)
    } else {
        gfxprint_printf(gfxprint, "ﾃﾞｰﾀ  :ｶｹﾞﾑｼｬ"); // (data: double) [double meaning body double/puppet master]
    }
}
void select_print_face_type(gfxprint* gfxprint, UNUSED Game_Select* select) {
    static const char* Distinction[] = { GFXPRINT_HIRAGANA_MODE "ﾀｲﾌﾟ1", GFXPRINT_HIRAGANA_MODE "ﾀｲﾌﾟ2",
                                         GFXPRINT_HIRAGANA_MODE "ﾀｲﾌﾟ3", GFXPRINT_HIRAGANA_MODE "ﾀｲﾌﾟ4",
                                         GFXPRINT_HIRAGANA_MODE "ﾀｲﾌﾟ5", GFXPRINT_HIRAGANA_MODE "ﾀｲﾌﾟ6",
                                         GFXPRINT_HIRAGANA_MODE "ﾀｲﾌﾟ7", GFXPRINT_HIRAGANA_MODE "ﾀｲﾌﾟ8" };

    gfxprint_locate8x8(gfxprint, 23, 12);
    gfxprint_printf(gfxprint, "ｶｵ    :%s", Distinction[common_data.privateInfo->face]);
}

void select_print_event(gfxprint* gfxprint, UNUSED Game_Select* select) {
    static const char* event_kind[] = {
        GFXPRINT_KATAKANA_MODE "---",
        GFXPRINT_KATAKANA_MODE "ｻﾞｯｶﾔ",   // (雑貨屋) (general store/shop)
        GFXPRINT_KATAKANA_MODE "ﾃﾞｻﾞｲﾅ-", // designer
        GFXPRINT_KATAKANA_MODE "ﾌﾞﾛ-ｶ-",  // broker
        GFXPRINT_KATAKANA_MODE "ｶﾞﾊｸ",    // (画伯) artist
        GFXPRINT_KATAKANA_MODE "ｼﾞｭｳﾀﾝ",  // (絨毯) carpet
        GFXPRINT_KATAKANA_MODE "ｸﾛﾋｮｳ"    // (黒豹) black panther
    };

    gfxprint_locate8x8(gfxprint, 23, 16);
    gfxprint_printf(gfxprint, GFXPRINT_KATAKANA_MODE "ｲﾍﾞﾝﾄ :%s", event_kind[0]);
}

typedef void (*SelectPrintProc)(gfxprint*, Game_Select*);

void select_draw_main(Game_Select* select) {
    static SelectPrintProc print_process[] = {
        &select_print_rtc,       &select_print_time,  &select_print_step,  &select_print_weather, &select_print_sex,
        &select_print_face_type, &select_print_swell, &select_print_decoy, &select_print_cloth,   &select_print_event,
    };

    GraphicsContext* graph = select->state.gfxCtx;
    s32 i;

    OPEN_DISPS(graph);

    gSPSegment(POLY_OPA_DISP++, 0, 0);

    DisplayList_initialize(graph, 0, 0, 0, NULL);

    SET_FULLSCREEN_VIEWPORT(&select->view);
    showView(&select->view, 15);

    rect_moji(graph);

    {
        gfxprint* gfxprint_p;
        gfxprint_p = alloca(sizeof(gfxprint));

        gfxprint_init(gfxprint_p);
        gfxprint_open(gfxprint_p, POLY_OPA_DISP);

        select_print_course_name(select, gfxprint_p);

        gfxprint_color(gfxprint_p, 200, 200, 55, 255);
        gfxprint_locate8x8(gfxprint_p, 26, 4);
        gfxprint_printf(gfxprint_p, GFXPRINT_HIRAGANA_MODE "-ｾｯﾃｲ-"); // -settings-

        for (i = 0; i < 10; i++) {
            if (select->cursorY == i) {
                if (select->status == 0) {
                    gfxprint_color(gfxprint_p, 180, 180, 255, 255);
                } else {
                    gfxprint_color(gfxprint_p, 120, 120, 255, 255);
                }
            } else {
                gfxprint_color(gfxprint_p, 255, 255, 55, 255);
            }

            (*print_process[i])(gfxprint_p, select);
        }

        POLY_OPA_DISP = (gfxprint_close(gfxprint_p));

        gfxprint_cleanup(gfxprint_p);
    }
    CLOSE_DISPS(graph);
}

void select_draw_wait(Game_Select* select) {
    GraphicsContext* graph = select->state.gfxCtx;
    gfxprint* gfxprint_p;

    OPEN_DISPS(graph);

    gSPSegment(POLY_OPA_DISP++, 0, 0);

    DisplayList_initialize(graph, 0, 0, 0, NULL);

    SET_FULLSCREEN_VIEWPORT(&select->view);
    showView(&select->view, 15);

    rect_moji(graph);
    {
        gfxprint_p = alloca(sizeof(gfxprint));

        gfxprint_init(gfxprint_p);
        gfxprint_open(gfxprint_p, POLY_OPA_DISP);

        select_print_wait(gfxprint_p);

        POLY_OPA_DISP = (gfxprint_close(gfxprint_p));

        gfxprint_cleanup(gfxprint_p);
    }
    CLOSE_DISPS(graph);
}

void select_draw(Game_Select* select) {
    GraphicsContext* graph = select->state.gfxCtx;

    OPEN_DISPS(graph);

    gSPSegment(POLY_OPA_DISP++, 0, 0);

    DisplayList_initialize(graph, 0, 0, 0, NULL);

    // FAKE !!
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    CLOSE_DISPS(graph);

    SET_FULLSCREEN_VIEWPORT(&select->view);
    showView(&select->view, 15);

    if (select->state.running == FALSE) {
        select_draw_wait(select);
    } else {
        select_draw_main(select);
    }
}

void select_main(Game* game) {
    Game_Select* select = (Game_Select*)game;

    select_move(select);
    select_draw(select);

    {
        GraphicsContext* graph = game->gfxCtx;
        game_debug_draw_last(game, graph);
        game_draw_last(graph);
    }
}

void select_cleanup(UNUSED Game* game) {
}

void select_init(Game* game) {
    Game_Select* select = (Game_Select*)game;
    s32 i;

    game->main = &select_main;
    game->destroy = &select_cleanup;

    select->status = 0;
    select->cursorY = 9;
    select->step = 0;
    select->stepAdd = 0;

    select->topScene = 0;
    select->selectedScene = 0;

    initView(&select->view, game->gfxCtx);
    select->view.unk_120 = 10;

    select->unk_234 = 0;
    select->unk_238 = 0;
    select->unk_23C = 0;
    for (i = 0; i < PLAYER_NAME_LEN; i++) {
        select->name[i] = fcode2data(common_data.privateInfo->playerId.playerName[i]);
    }
    if ((DORO(80) >= 0) && (DORO(80) < 0x23)) {
        select->selectedScene = DORO(80);
        select->topScene = DORO(81);
    }

    SetGameFrame(1);

    common_data.unk_10004 = common_data.sceneNo;
    common_data.unk_104AD = 0;
    common_data.privateInfo->inventory.loan = 1000;

    mNpc_ClearEventNpc();
}
