#include "m_kankyo.h"
#include "m_time.h"
#include "m_lib.h"
#include "m_common_data.h"
#include "m_scene_table.h"
#include "macros.h"
#include "m_field_info.h"
#include "m_event.h"
#include "audio.h"
#include "m_all_grow.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_player_lib.h"

// fake names following l_mEnv_electric_light naming convention, since that's what these got refactored to
u8 l_mEnv_index_light_switch_electric_light = 0; // needs to be signed in iQue
s16 l_mEnv_point_light_is_flame_electric_light = 0;

s32 klight_chg_time[] = {
    mTM_TIME_TO_SEC(0, 0, 0),  mTM_TIME_TO_SEC(4, 0, 0),  mTM_TIME_TO_SEC(6, 0, 0),
    mTM_TIME_TO_SEC(8, 0, 0),  mTM_TIME_TO_SEC(12, 0, 0), mTM_TIME_TO_SEC(16, 0, 0),
    mTM_TIME_TO_SEC(18, 0, 0), mTM_TIME_TO_SEC(20, 0, 0), mTM_TIME_TO_SEC(24, 0, 0),
};

BaseLight l_mEnv_kcolor_fine_data[] = {
    /* 00:00 -> 03:59 */
    {
        { 20, 10, 120 }, // ambient color

        { 73, 73, 73 }, // sun direction
        { 0, 0, 0 },    // sun color

        { 73, 73, 73 },   // moon direction
        { 120, 180, 80 }, // moon color

        { 20, 20, 80 }, // fog color
        1799,           // fog near
        1000,           // fog far

        { 0, 0, 20 },      // shadow color
        { 120, 160, 150 }, // room color
        { 120, 160, 150 }, // window sun color
        { 240, 255, 120 }, // window moon color
        { 28, 32, 92 }     // background color
    },

    {
        { 0, 20, 100 }, // ambient color

        { 73, 73, 73 }, // sun direction
        { 0, 20, 40 },  // sun color

        { 73, 73, 73 },    // moon direction
        { 150, 200, 100 }, // moon color

        { 60, 80, 120 }, // fog color
        1799,            // fog near
        950,             // fog far

        { 0, 10, 30 },     // shadow color
        { 120, 180, 200 }, // room color
        { 120, 200, 200 }, // window sun color
        { 240, 255, 120 }, // window moon color
        { 32, 48, 104 }    // background color
    },

    {
        { 60, 60, 120 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 255, 255, 200 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 10, 40, 60 }, // moon color

        { 120, 120, 120 }, // fog color
        1799,              // fog near
        900,               // fog far

        { 0, 20, 40 },     // shadow color
        { 240, 255, 255 }, // room color
        { 240, 255, 255 }, // window sun color
        { 240, 255, 120 }, // window moon color
        { 48, 52, 128 }    // background color
    },

    {
        { 100, 100, 150 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 255, 255, 200 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 0, 10, 20 },  // moon color

        { 80, 100, 120 }, // fog color
        1799,             // fog near
        1000,             // fog far

        { 0, 30, 60 },     // shadow color
        { 255, 255, 220 }, // room color
        { 255, 255, 240 }, // window sun color
        { 240, 255, 120 }, // window moon color
        { 40, 56, 140 }    // background color
    },

    {
        { 80, 80, 150 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 255, 255, 200 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 0, 0, 0 },    // moon color

        { 180, 100, 120 }, // fog color
        1949,              // fog near
        1000,              // fog far

        { 0, 20, 60 },     // shadow color
        { 255, 255, 220 }, // room color
        { 255, 255, 240 }, // window sun color
        { 240, 255, 120 }, // window moon color
        { 32, 48, 144 }    // background color
    },

    {
        { 80, 80, 120 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 255, 240, 100 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 10, 0, 30 },  // moon color

        { 80, 100, 120 }, // fog color
        1949,             // fog near
        1000,             // fog far

        { 0, 0, 60 },      // shadow color
        { 255, 250, 200 }, // room color
        { 255, 250, 200 }, // window sun color
        { 240, 255, 120 }, // window moon color
        { 36, 40, 104 }    // background color
    },

    {
        { 60, 60, 120 }, // ambient color

        { 73, 73, 73 },  // sun direction
        { 255, 100, 0 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 20, 0, 60 },  // moon color

        { 50, 60, 100 }, // fog color
        1949,            // fog near
        1000,            // fog far

        { 0, 0, 40 },      // shadow color
        { 255, 140, 120 }, // room color
        { 255, 160, 140 }, // window sun color
        { 240, 255, 120 }, // window moon color
        { 24, 24, 80 }     // background color
    },

    {
        { 30, 30, 120 }, // ambient color

        { 73, 73, 73 }, // sun direction
        { 60, 60, 0 },  // sun color

        { 73, 73, 73 },   // moon direction
        { 120, 180, 80 }, // moon color

        { 20, 20, 80 }, // fog color
        1949,           // fog near
        1000,           // fog far

        { 0, 0, 30 },      // shadow color
        { 150, 130, 120 }, // room color
        { 255, 160, 140 }, // window sun color
        { 240, 255, 120 }, // window moon color
        { 24, 24, 96 }     // background color
    }
};

BaseLight l_mEnv_kcolor_rain_data[] = {
    {
        { 20, 10, 120 }, // ambient color

        { 73, 73, 73 }, // sun direction
        { 0, 0, 0 },    // sun color

        { 73, 73, 73 },   // moon direction
        { 120, 180, 80 }, // moon color

        { 20, 20, 80 }, // fog color
        1799,           // fog near
        1000,           // fog far

        { 0, 0, 20 },      // shadow color
        { 120, 160, 150 }, // room color
        { 120, 160, 150 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 28, 32, 92 }     // background color
    },

    {
        { 30, 20, 120 }, // ambient color

        { 73, 73, 73 }, // sun direction
        { 0, 20, 40 },  // sun color

        { 73, 73, 73 },   // moon direction
        { 120, 180, 80 }, // moon color

        { 80, 100, 120 }, // fog color
        1774,             // fog near
        1000,             // fog far

        { 0, 10, 30 },     // shadow color
        { 140, 190, 190 }, // room color
        { 150, 170, 170 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 44, 52, 112 }    // background color
    },

    {
        { 60, 60, 120 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 150, 180, 180 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 10, 40, 60 }, // moon color

        { 120, 150, 150 }, // fog color
        1749,              // fog near
        950,               // fog far

        { 0, 20, 40 },     // shadow color
        { 180, 210, 210 }, // room color
        { 160, 180, 180 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 60, 76, 120 }    // background color
    },

    {
        { 80, 80, 150 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 180, 220, 220 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 0, 10, 20 },  // moon color

        { 80, 120, 150 }, // fog color
        1749,             // fog near
        1000,             // fog far

        { 0, 20, 60 },     // shadow color
        { 210, 240, 240 }, // room color
        { 190, 220, 220 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 56, 72, 140 }    // background color
    },

    {
        { 80, 80, 150 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 200, 240, 240 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 0, 0, 0 },    // moon color

        { 80, 120, 150 }, // fog color
        1749,             // fog near
        1000,             // fog far

        { 0, 20, 60 },     // shadow color
        { 220, 250, 250 }, // room color
        { 210, 240, 240 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 52, 78, 144 }    // background color
    },

    {
        { 80, 80, 150 }, // ambient color

        { 73, 73, 73 },    // sun direction
        { 200, 240, 240 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 10, 0, 30 },  // moon color

        { 80, 120, 150 }, // fog color
        1749,             // fog near
        1000,             // fog far

        { 0, 20, 60 },     // shadow color
        { 220, 250, 250 }, // room color
        { 220, 240, 240 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 48, 72, 140 }    // background color
    },

    {
        { 60, 60, 150 }, // ambient color

        { 73, 73, 73 },  // sun direction
        { 200, 120, 0 }, // sun color

        { 73, 73, 73 }, // moon direction
        { 20, 0, 80 },  // moon color

        { 20, 20, 80 }, // fog color
        1774,           // fog near
        1000,           // fog far

        { 0, 20, 50 },     // shadow color
        { 190, 120, 120 }, // room color
        { 180, 120, 120 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 32, 32, 92 }     // background color
    },

    {
        { 30, 30, 120 }, // ambient color

        { 73, 73, 73 }, // sun direction
        { 60, 60, 0 },  // sun color

        { 73, 73, 73 },   // moon direction
        { 120, 180, 80 }, // moon color

        { 20, 20, 80 }, // fog color
        1774,           // fog near
        1000,           // fog far

        { 0, 0, 30 },      // shadow color
        { 130, 160, 160 }, // room color
        { 180, 120, 120 }, // window sun color
        { 230, 230, 120 }, // window moon color
        { 28, 28, 92 }     // background color
    },
};

BaseLight l_mEnv_kcolor_data_p_sel = {
    { 30, 30, 80 }, // ambient color

    { 0, 89, 79 },     // sun direction
    { 255, 255, 200 }, // sun color

    { 0, 185, 160 }, // moon direction
    { 0, 0, 0 },     // moon color

    { 100, 100, 120 }, // fog color
    2000,              // fog near
    1280,              // fog far

    { 0, 20, 60 },     // shadow color
    { 255, 255, 255 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

BaseLight l_mEnv_kcolor_shop = {
    { 20, 10, 100 }, // ambient color

    { 0, 69, 97 },     // sun direction
    { 150, 160, 130 }, // sun color

    { 0, 223, 115 }, // moon direction
    { 50, 40, 20 },  // moon color

    { 100, 100, 120 }, // fog color
    2000,              // fog near
    1280,              // fog far

    { 0, 20, 60 },     // shadow color
    { 255, 255, 255 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

BaseLight l_mEnv_kcolor_buggy = {
    { 30, 30, 30 }, // ambient color

    { 0, 69, 97 }, // sun direction
    { 0, 0, 0 },   // sun color

    { 0, 223, 115 }, // moon direction
    { 0, 60, 90 },   // moon color

    { 100, 100, 120 }, // fog color
    2000,              // fog near
    1280,              // fog far

    { 0, 20, 60 },     // shadow color
    { 175, 175, 155 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

BaseLight l_mEnv_kcolor_kamakura = {
    { 50, 25, 20 }, // ambient color

    { 0, 69, 97 }, // sun direction
    { 50, 40, 5 }, // sun color

    { 0, 223, 115 }, // moon direction
    { 50, 80, 85 },  // moon color

    { 100, 100, 120 }, // fog color
    2000,              // fog near
    1280,              // fog far

    { 0, 20, 60 },     // shadow color
    { 250, 240, 160 }, // room color
    { 0, 0, 0 },       // window sun color
    { 0, 0, 0 },       // window moon color
    { 22, 27, 94 }     // background color
};

BaseLight* l_mEnv_normal_kcolor_data[] = {
    l_mEnv_kcolor_fine_data, // clear
    l_mEnv_kcolor_rain_data, // rain
    l_mEnv_kcolor_rain_data, // snow
    l_mEnv_kcolor_fine_data  // cherry blossoms
};

LightNode* S_get_light_list;

// fake names following l_mEnv_electric_light naming convention, since that's what these got refactored to
u8 l_mEnv_point_light_on_electric_light;
s16 l_mEnv_add_moon_color_electric_light[3];
f32 l_mEnv_staffroll_fade_rate_electric_light;
f32 l_mEnv_sun_percent_electric_light;
f32 l_mEnv_shadow_adjust_electric_light;
f32 l_mEnv_windowlight_alpha_electric_light;
LightNode* l_mEnv_current_lightnode_electric_light;

void mEnv_regist_nature(Kankyo* kankyo, NatureProc natureProc, void* arg) {
    kankyo->nature.proc = natureProc;
    kankyo->nature.arg = arg;
}

s32 mEnv_unregist_nature(Kankyo* kankyo, NatureProc natureProc) {
    s32 res = FALSE;

    if (natureProc == kankyo->nature.proc) {
        mEnv_regist_nature(kankyo, (void*)none_proc1, NULL);
        res = TRUE;
    }

    return res;
}

s32 func_80096CDC_jp() {
    s32 ret = TRUE;
    UNUSED s32 pad;
    u16 homeId = common_data.houseOwnerName & 3;

    if (!mEv_CheckFirstIntro() && mPr_NullCheckPersonalID(&common_data.save.homes[homeId].ownerID)) {
        ret = FALSE;
    }

    return ret;
}

#define SET_COLOR(color, r, g, b) \
    (color[0] = r);               \
    (color[1] = g);               \
    (color[2] = b)

#define SET_POS(pos, xValue, yValue, zValue) \
    (pos->x = xValue);                       \
    (pos->y = yValue);                       \
    (pos->z = zValue)

s32 mEnv_GetNowRoomPointLightInfo(UNUSED Game_Play* play, s_xyz* pos, u8* color, s16* power, s16* isFlame) {
    u8 res = TRUE;

    switch (common_data.fieldDrawType) {
        case FIELD_DRAW_TYPE_INDOORS: {
            SET_COLOR(color, 160, 160, 160);

            power[0] = 1000;

            switch (common_data.save.sceneNo) {
                case SCENE_MY_ROOM_S: {
                    if (func_80096CDC_jp() == TRUE) {
                        SET_POS(pos, 120, 180, 180);
                    } else {
                        res = FALSE;
                    }

                    break;
                }

                case SCENE_MY_ROOM_M:
                case SCENE_SHOP0:
                case SCENE_POST_OFFICE:
                case SCENE_NPC_HOUSE: {
                    SET_POS(pos, 160, 180, 240);

                    break;
                }

                case SCENE_BUGGY: {
                    SET_POS(pos, 160, 80, 200);
                    SET_COLOR(color, 205, 165, 110);

                    power[0] = 155;
                    *isFlame = TRUE;

                    break;
                }

                case SCENE_MY_ROOM_L:
                case SCENE_POLICE_BOX: {
                    SET_POS(pos, 200, 220, 300);

                    break;
                }

                case SCENE_KAMAKURA: {
                    SET_POS(pos, 160, 80, 38);
                    SET_COLOR(color, 250, 240, 120);

                    power[0] = 300;
                    *isFlame = TRUE;

                    break;
                }

                default: {
                    SET_POS(pos, 250, 1000, 378);

                    power[0] = 8000;

                    break;
                }
            }

            break;
        }

        case FIELD_DRAW_TYPE_TRAIN: {
            switch (common_data.save.sceneNo) {
                case SCENE_START_DEMO: {
                    common_data.sunlightFlag = FALSE;

                    break;
                }
            }

            l_mEnv_sun_percent_electric_light = 0.0f;

            SET_POS(pos, 80, 120, 510);
            SET_COLOR(color, 255, 255, 160);

            power[0] = 1200;

            break;
        }

        default:
            res = FALSE;
            break;
    }

    return res;
}

void mEnv_RoomTypePointLightSet(Game_Play* play) {
    Game_Play* play2 = play;
    u8 color[3];
    s16 power;
    s_xyz pos;

    l_mEnv_point_light_on_electric_light = 0;
    l_mEnv_point_light_is_flame_electric_light = FALSE;

    if (mEnv_GetNowRoomPointLightInfo(play2, &pos, color, &power, &l_mEnv_point_light_is_flame_electric_light) ==
        TRUE) {
        if (common_data.save.sceneNo == SCENE_NPC_HOUSE && mEnv_CheckNpcRoomPointLightNiceStatus() == FALSE) {
            l_mEnv_index_light_switch_electric_light = 1;
        } else {
            l_mEnv_index_light_switch_electric_light = 0;

            Light_point_ct(&play2->kankyo.pointLight, pos.x, pos.y, pos.z, color[0], color[1], color[2], power);

            l_mEnv_current_lightnode_electric_light =
                Global_light_list_new(play2, &play2->glight, &play2->kankyo.pointLight);
            l_mEnv_point_light_on_electric_light = 1;
        }
    }
}

void mEnv_RoomTypediffuseLightSet(Game_Play* play, Kankyo* kankyo) {
    Game_Play* play2 = play;

    Light_diffuse_ct(&kankyo->sunLight, 1, 0, 0, 0, 0, 0);
    Global_light_list_new(play2, &play2->glight, &kankyo->sunLight);

    Light_diffuse_ct(&kankyo->moonLight, 1, 0, 0, 0, 0, 0);
    Global_light_list_new(play2, &play2->glight, &kankyo->moonLight);
}

void mEnv_RoomTypeLightSet(Game_Play* play, Kankyo* kankyo) {
    Game_Play* play2 = play;

    mEnv_RoomTypePointLightSet(play2);
    mEnv_RoomTypediffuseLightSet(play2, kankyo);
}

void Global_kankyo_ct(Game_Play* play, Kankyo* kankyo) {
    l_mEnv_shadow_adjust_electric_light = 1.0f;
    l_mEnv_sun_percent_electric_light = 1.0f;
    l_mEnv_index_light_switch_electric_light = 0;
    l_mEnv_current_lightnode_electric_light = NULL;

    bzero(kankyo, sizeof(Kankyo));
    bzero(l_mEnv_add_moon_color_electric_light, sizeof(l_mEnv_add_moon_color_electric_light));

    common_data.unk_10148 = 0;

    mEnv_set_time(kankyo);
    kankyo->countdownTimer = 0xFF;
    mEnv_RoomTypeLightSet(play, kankyo);
    mEnv_regist_nature(kankyo, (void*)none_proc1, NULL);
    mEnv_MakeWindowLightAlpha(FALSE);
}
void mEnv_MakeShadowInfo(Kankyo* kankyo) {
    u8 hour = common_data.time.rtcTime.hour;
    u8 min = common_data.time.rtcTime.min;
    u8 sec = common_data.time.rtcTime.sec;
    s32 time = mTM_TIME_TO_SEC(hour, min, sec);
    f32 shadowAdjust;
    f32 preAdjust;
    s32 tmp;
    s32 transitionZero = FALSE;

    if (time > mTM_TIME_TO_SEC(6, 0, 0) && time < mTM_TIME_TO_SEC(18, 0, 0)) {
        shadowAdjust = 1.0f;
    } else if (time < mTM_TIME_TO_SEC(3, 59, 30) || time > mTM_TIME_TO_SEC(20, 0, 3)) {
        shadowAdjust = 0.4f;
    } else if (time >= mTM_TIME_TO_SEC(4, 0, 3) && time <= mTM_TIME_TO_SEC(6, 0, 0)) {
        preAdjust = ((time - mTM_TIME_TO_SEC(3, 59, 57)) / (f32)mTM_TIME_TO_SEC(2, 0, 3));
        shadowAdjust = 0.6f * preAdjust + 0.4f;
    } else if (time >= mTM_TIME_TO_SEC(18, 0, 0) && time <= mTM_TIME_TO_SEC(19, 59, 30)) {
        preAdjust = (1.0f - ((time - mTM_TIME_TO_SEC(18, 0, 0)) / (f32)mTM_TIME_TO_SEC(1, 59, 30)));
        shadowAdjust = 0.6f * preAdjust + 0.4f;

    } else {
        transitionZero = TRUE;
        shadowAdjust = 0.4f;
    }

    if (transitionZero == TRUE) {
        if ((time > mTM_TIME_TO_SEC(3, 59, 55) && time < mTM_TIME_TO_SEC(4, 0, 3)) ||
            (time > mTM_TIME_TO_SEC(19, 59, 55) && time < mTM_TIME_TO_SEC(20, 0, 3))) {
            add_calc(&l_mEnv_shadow_adjust_electric_light, 0.0f, 0.5f, 0.01f, 0.01f);
        } else {
            add_calc(&l_mEnv_shadow_adjust_electric_light, 0.0f, 0.1f, 0.0012f, 0.0008f);
        }
    } else {
        add_calc(&l_mEnv_shadow_adjust_electric_light, 1.0f, 0.1f, 0.001f, 0.0001f);
    }

    if (common_data.weather == mEnv_WEATHER_RAIN || common_data.weather == mEnv_WEATHER_SNOW) {
        shadowAdjust *= 0.75f;
    }

    kankyo->shadowAlpha = (s32)(255.0f * shadowAdjust * l_mEnv_shadow_adjust_electric_light);

    if (mEnv_HereIsPlayerSelect() == TRUE) {
        kankyo->shadowAlpha = 200.0f;
    }

    if (time >= mTM_TIME_TO_SEC(4, 0, 0) && time <= mTM_TIME_TO_SEC(20, 0, 0)) {
        tmp = mTM_TIME_TO_SEC(16, 0, 0);
        preAdjust = (f32)(time - mTM_TIME_TO_SEC(4, 0, 0)) / (f32)tmp;
    } else {
        if (time < mTM_TIME_TO_SEC(20, 0, 0)) {
            time += mTM_SECONDS_IN_DAY;
        }

        tmp = mTM_TIME_TO_SEC(8, 0, 0);
        if (1) {}
        preAdjust = (f32)(time - mTM_TIME_TO_SEC(20, 0, 0)) / (f32)tmp;
    }

    kankyo->shadowPos = 200.0f * preAdjust - 100.0f;
}
void mEnv_set_time(Kankyo* kankyo) {
    u8 hour = common_data.time.rtcTime.hour;
    s16 timeAngle = ((common_data.time.nowSec - mTM_SECONDS_IN_HALFDAY) / (f32)(mTM_SECONDS_IN_DAY)) * 65536.0f;
    UNUSED f32 sin = sin_s(timeAngle);
    f32 cos = cos_s(timeAngle);
    UNUSED f32 end = 0;
    f32 tmp;
    Color_RGBA8 lightColor;
    s32 shadowsAffected;
    u32 min;

    tmp = ABS(cos) * 255.0f + 10.0f;

    min = hour - 6;
    if (min < 12) {
        if (tmp > 255.0f) {
            tmp = 255.0f;
        }
    }

    mEnv_MakeShadowInfo(kankyo);

    if (common_data.clip.unk_090 != NULL && common_data.clip.unk_090->unk_3C(&lightColor, &shadowsAffected) &&
        shadowsAffected == TRUE) {
        f32 colorAdd;
        f32 adjustedShadowAlpha;

        colorAdd = lightColor.r + lightColor.g + lightColor.b;
        adjustedShadowAlpha = kankyo->shadowAlpha;

        if (colorAdd > 200.0f) {
            colorAdd = 200.0f;
        }

        adjustedShadowAlpha += (colorAdd / 200.0f) * 110.0f;

        if (adjustedShadowAlpha > 255.0f) {
            adjustedShadowAlpha = 255.0f;
        }

        if (adjustedShadowAlpha < 0.0f) {
            adjustedShadowAlpha = 0.0f;
        }

        kankyo->shadowAlpha = (s32)adjustedShadowAlpha;
    }

    mNPS_schedule_manager();
}
void mEnv_ChangeRGBLight(u8* dst, u8* light0, u8* light1, f32 f0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        dst[0] = (s32)(((*light1 - *light0) * f0 + *light0) * l_mEnv_sun_percent_electric_light);

        light0++;
        light1++;

        dst++;
    }
}
void mEnv_ChangeDiffuseVctlSet(BaseLight* baseLight) {
    s32 secondsRadAngle;

    if (common_data.save.sceneNo == SCENE_CONVENI || common_data.save.sceneNo == SCENE_SUPER ||
        common_data.save.sceneNo == SCENE_DEPART || common_data.save.sceneNo == SCENE_DEPART_2 ||
        common_data.save.sceneNo == SCENE_BUGGY || common_data.save.sceneNo == SCENE_KAMAKURA) {
        baseLight->sunDir[0] = 0;
        baseLight->sunDir[1] = 69;
        baseLight->sunDir[2] = 97;

        baseLight->moonDir[0] = 0;
        baseLight->moonDir[1] = -33;
        baseLight->moonDir[2] = 115;
    } else {
        f32 diff;
        xyz_t dir;

        switch (common_data.fieldDrawType) {
            case FIELD_DRAW_TYPE_TRAIN:
            case FIELD_DRAW_TYPE_PLAYER_SELECT:
                dir.x = 0.0f;
                dir.y = 60.0f;
                dir.z = 60.0f;
                break;
            default:
                diff = common_data.time.nowSec - mTM_SECONDS_IN_HALFDAY;
                secondsRadAngle = (diff / (f32)(mTM_SECONDS_IN_HALFDAY)) * (f32)(0x8000);

                dir.x = 60.0f * sin_s(secondsRadAngle);
                dir.y = 60.0f * cos_s(secondsRadAngle);
                dir.z = 60.f * cos_s(secondsRadAngle);
                break;
        }

        baseLight->sunDir[0] = -dir.x;
        baseLight->sunDir[1] = dir.y + 30.0f;
        baseLight->sunDir[2] = dir.z + 20.0f;
        baseLight->moonDir[0] = dir.x;
        baseLight->moonDir[1] = (-dir.y) + 30.0f;
        baseLight->moonDir[2] = (-dir.z) + 20.0f;
    }
}

void mEnv_ChangeDiffuseLight(BaseLight* dst, BaseLight* light0, BaseLight* light1, f32 f0) {
    u8 current[3];
    u8 current2[3];
    s32 i;

    mEnv_ChangeDiffuseVctlSet(dst);
    if (common_data.sunlightFlag == TRUE) {
        add_calc(&l_mEnv_sun_percent_electric_light, 1.0f, 0.5f, 0.2f, 0.01f);
    } else {
        add_calc(&l_mEnv_sun_percent_electric_light, 0.0f, 0.5f, 0.2f, 0.01f);
    }

    for (i = 0; i < 3; i++) {
        current[i] = (s32)(light0->sunColor[i] * l_mEnv_sun_percent_electric_light);
        current2[i] = (s32)(light1->sunColor[i] * l_mEnv_sun_percent_electric_light);
    }
    mEnv_ChangeRGBLight(dst->sunColor, current, current2, f0);

    for (i = 0; i < 3; i++) {
        current[i] = (s32)(light0->moonColor[i] * l_mEnv_sun_percent_electric_light);
        current2[i] = (s32)(light1->moonColor[i] * l_mEnv_sun_percent_electric_light);
    }

    mEnv_ChangeRGBLight(dst->moonColor, light0->moonColor, light1->moonColor, f0);
}
void mEnv_ChangeFogLight(BaseLight* dst, BaseLight* light0, BaseLight* light1, f32 f0) {
    mEnv_ChangeRGBLight(dst->fogColor, light0->fogColor, light1->fogColor, f0);

    dst->fogNear = (((light1->fogNear & 0x3FF) - (light0->fogNear & 0x3FF)) * f0) + (light0->fogNear & 0x3FF);
    dst->fogFar = (((light1->fogFar) - (light0->fogFar)) * f0) + light0->fogFar;
}

void mEnv_CalcSetLight_train(BaseLight* light) {
    s32 rColor;
    s32 gColor;
    s32 bColor;
    f32 inv;

    if (common_data.save.sceneNo == SCENE_START_DEMO && l_mEnv_sun_percent_electric_light < 1.0f) {
        inv = 1.0f - l_mEnv_sun_percent_electric_light;
        if (common_data.save.sceneNo == SCENE_START_DEMO) {
            rColor = 35.0f * inv;
            gColor = 30.0f * inv;
            bColor = 40.0f * inv;

            light->ambientColor[0] += (u8)rColor;
            light->ambientColor[1] += (u8)gColor;
            light->ambientColor[2] += (u8)bColor;
        }
    }
}

void mEnv_CalcSetLight(BaseLight* dst, BaseLight* light0, BaseLight* light1, f32 f0) {
    mEnv_ChangeRGBLight(dst->ambientColor, light0->ambientColor, light1->ambientColor, f0);
    mEnv_CalcSetLight_train(dst);
    mEnv_ChangeDiffuseLight(dst, light0, light1, f0);
    mEnv_ChangeFogLight(dst, light0, light1, f0);

    mEnv_ChangeRGBLight(dst->shadowColor, light0->shadowColor, light1->shadowColor, f0);
    mEnv_ChangeRGBLight(dst->roomColor, light0->roomColor, light1->roomColor, f0);
    mEnv_ChangeRGBLight(dst->sunColorWindow, light0->sunColorWindow, light1->sunColorWindow, f0);
    mEnv_ChangeRGBLight(dst->moonColorWindow, light0->moonColorWindow, light1->moonColorWindow, f0);
    mEnv_ChangeRGBLight(dst->bgColor, light0->bgColor, light1->bgColor, f0);
}

void mEnv_SetBaseLight(Kankyo* kankyo) {
    f32 percent;
    s32 i;
    s32 fogEnabled;
    s32 weather;
    s32 nowSec;
    s32* cur;
    s32 term;

    nowSec = common_data.time.nowSec;
    fogEnabled = TRUE;
    cur = klight_chg_time;

    for (i = 0; i < mEnv_TERM; i++) {
        if (klight_chg_time[i + 1] >= nowSec) {
            break;
        }
    }

    term = i + 1;
    weather = common_data.weather;
    percent = get_percent(cur[term], cur[i], nowSec);

    switch (common_data.fieldDrawType) {
        case FIELD_DRAW_TYPE_TRAIN:
            mEnv_CalcSetLight(&kankyo->baseLight, &l_mEnv_normal_kcolor_data[weather][i],
                              &l_mEnv_normal_kcolor_data[weather][(term) % 8], percent);
            break;
        case FIELD_DRAW_TYPE_PLAYER_SELECT:

            mEnv_CalcSetLight(&kankyo->baseLight, &l_mEnv_kcolor_data_p_sel, &l_mEnv_kcolor_data_p_sel, 0.5f);
            break;
        default:
            if (common_data.save.sceneNo == SCENE_CONVENI || common_data.save.sceneNo == SCENE_SUPER ||
                common_data.save.sceneNo == SCENE_DEPART || common_data.save.sceneNo == SCENE_DEPART_2) {
                mEnv_CalcSetLight(&kankyo->baseLight, &l_mEnv_kcolor_shop, &l_mEnv_kcolor_shop, 0.5f);
            } else if (common_data.save.sceneNo == SCENE_BUGGY) {
                mEnv_CalcSetLight(&kankyo->baseLight, &l_mEnv_kcolor_buggy, &l_mEnv_kcolor_buggy, 0.5f);
            } else if (common_data.save.sceneNo == SCENE_KAMAKURA) {
                mEnv_CalcSetLight(&kankyo->baseLight, &l_mEnv_kcolor_kamakura, &l_mEnv_kcolor_kamakura, 0.5f);
            } else {
                mEnv_CalcSetLight(&kankyo->baseLight, &l_mEnv_normal_kcolor_data[weather][i],
                                  &l_mEnv_normal_kcolor_data[weather][(i + 1) % 8], percent);
            }

            if (common_data.unk_10001 == 0) {
                fogEnabled = FALSE;
            }

            break;
    }

    if (fogEnabled == TRUE) {
        kankyo->baseLight.fogColor[2] = 0;
        kankyo->baseLight.fogColor[1] = 0;
        kankyo->baseLight.fogColor[0] = 0;
        kankyo->baseLight.fogNear = 2020;
        kankyo->baseLight.fogFar = 1000;
    }
}

u8 mEnv_LimitChkRGBColor(s32 c) {
    if (c > 255) {
        c = 255;
    } else if (c < 0) {
        c = 0;
    }

    return c;
}

void mEnv_AddAndSetRGBColor(u8* dst, u8* src0, s16* src1) {
    s32 i;

    for (i = 0; i < 3; i++) {
        dst[0] = mEnv_LimitChkRGBColor(src0[0] + src1[0]);

        dst++;
        src0++;
        src1++;
    }
}

void mEnv_SetDiffuseLight(Kankyo* kankyo) {
    LightParams* sunLight = &kankyo->sunLight.lights;
    LightParams* moonLight = &kankyo->moonLight.lights;
    BaseLight* light = &kankyo->baseLight;
    UNUSED s32 pad;
    UNUSED s32 pad2;

    mEnv_AddAndSetRGBColor(sunLight->diffuse.color, light->sunColor, kankyo->addLightsInfo.diffuseColor);
    mEnv_AddAndSetRGBColor(moonLight->diffuse.color, light->moonColor, l_mEnv_add_moon_color_electric_light);

    sunLight->diffuse.x = light->sunDir[0];
    sunLight->diffuse.y = light->sunDir[1];
    sunLight->diffuse.z = light->sunDir[2];

    moonLight->diffuse.x = light->moonDir[0];
    moonLight->diffuse.y = light->moonDir[1];
    moonLight->diffuse.z = light->moonDir[2];
}

void mEnv_SetFog(Kankyo* kankyo, Global_light* gLight) {
    BaseLight* light = &kankyo->baseLight;
    AddLightInfo* info = &kankyo->addLightsInfo;

    mEnv_AddAndSetRGBColor(gLight->fogColor, light->fogColor, info->fogColor);

    if (light->fogNear + info->fogNear <= mEnv_FOG_NEAR_MAX) {
        gLight->fogNear = light->fogNear + info->fogNear;
    } else {
        gLight->fogNear = mEnv_FOG_NEAR_MAX;
    }

    if (light->fogFar + info->fogFar <= mEnv_FOG_FAR_MAX) {
        gLight->fogFar = light->fogFar + info->fogFar;
    } else {
        gLight->fogFar = mEnv_FOG_FAR_MAX;
    }
}
void mEnv_PermitCheckDiffuseLight(Kankyo* kankyo) {
    if (kankyo->sunLight.lights.diffuse.x == 0 && kankyo->sunLight.lights.diffuse.y == 0 &&
        kankyo->sunLight.lights.diffuse.z == 0) {
        kankyo->sunLight.lights.diffuse.x = 1;
    }

    if (kankyo->moonLight.lights.diffuse.x == 0 && kankyo->moonLight.lights.diffuse.y == 0 &&
        kankyo->moonLight.lights.diffuse.z == 0) {
        kankyo->moonLight.lights.diffuse.x = 1;
    }
}
void Global_kankyo_set_room_prim(Game_Play* play) {
    GraphicsContext* graph;
    s32 i;
    s32 color;
    u8 colors[3];
    s32 lightOn;
    u8* pointColor;
    u8* roomColor;

    if (l_mEnv_point_light_on_electric_light != 0) {
        lightOn = TRUE;
    } else {
        lightOn = FALSE;
    }

    pointColor = play->kankyo.pointLight.lights.point.color;
    roomColor = play->kankyo.baseLight.roomColor;

    for (i = 0; i < 3; i++) {
        if (lightOn == TRUE) {
            if (l_mEnv_point_light_is_flame_electric_light) {
                color = (*pointColor >> 1) + (*roomColor >> 1);
            } else {
                color = (*roomColor * 0.7f) + (*pointColor * 0.6f);
            }
        } else {
            color = *roomColor;
        }

        if (color < 0) {
            color = 0;
        } else if (color > 255) {
            color = 255;
        }

        colors[i] = color;
        pointColor++;
        roomColor++;
    }

    graph = play->state.gfxCtx;

    OPEN_DISPS(graph);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, colors[0], colors[1], colors[2], 255);
    gDPPipeSync(POLY_XLU_DISP++);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 128, colors[0], colors[1], colors[2], 255);

    CLOSE_DISPS(graph);
}

void mEnv_check_countdown_start(Game_Play* play) {
    s32 time = mTM_TIME_TO_SEC(23, 59, 0);

    if (mEv_check_status(6, 8) == FALSE) {
        s32 bx;
        s32 bz;

        mFI_BlockKind2BkNum(&bx, &bz, 0x8000);

        if (bx != play->unk_00E4 || bz != play->unk_00E5) {
            if (common_data.time.nowSec >= time) {
                mEv_set_status(6, 8);
            }
        }
    }
}

void mEnv_countdown_proc(Game_Play* play) {
    UNUSED u8 pad;
    u8 timer;

    if (common_data.fieldDrawType != FIELD_DRAW_TYPE_TRAIN &&
        common_data.fieldDrawType != FIELD_DRAW_TYPE_PLAYER_SELECT && mEv_check_status(6, 1) == 1) {
        mEnv_check_countdown_start(play);

        if (mEv_check_status(6, 8) == 1) {
            u16 sfx;
            u8 cur = play->kankyo.countdownTimer;

            if (common_data.time.rtcTime.month != lbRTC_DECEMBER) {
                timer = 0;
            } else {
                timer = mTM_SECONDS_IN_DAY - common_data.time.nowSec;
            }

            if (timer != cur) {
                if (timer == 0) {
                    sfx = 0x151;
                } else if (timer <= 10) {
                    sfx = 0x150;
                } else {
                    sfx = 0x431;
                }

                sAdo_SysTrgStart(sfx);

                play->kankyo.countdownTimer = timer;
            }
        }
    }
}

void Global_kankyo_set(Game_Play* play, Kankyo* kankyo, Global_light* gLight) {
    mEnv_set_time(kankyo);
    mEnv_SetBaseLight(kankyo);
    mEnv_AddAndSetRGBColor(gLight->ambientColor, kankyo->baseLight.ambientColor, kankyo->addLightsInfo.ambientColor);
    mEnv_SetDiffuseLight(kankyo);
    mEnv_SetFog(kankyo, gLight);
    mEnv_PermitCheckDiffuseLight(kankyo);
    mEnv_TaimatuPointLightWaveMoveProc(play);
    mEnv_CheckNpcLight_ToSwitchON(play);
    mEnv_countdown_proc(play);
    mEnv_MakeWindowLightAlpha(TRUE);
}

void mEnv_DecideWindDirect(s_xyz* dir, s16 x, s16 z) {
    xyz_t windDir = { 0.0f, -100.0f, 0.0f };
    f32 xF = x;
    f32 zF = z;
    s16 rotX;
    s16 rotZ;
    f32 frotX;
    f32 frotZ;

    rotX = (RANDOM_F(xF) - xF);
    rotZ = (RANDOM_F(zF) - zF);

    frotX = BINANG_TO_RAD(rotX);
    frotZ = BINANG_TO_RAD(rotZ);

    sMath_RotateX(&windDir, frotX);

    sMath_RotateZ(&windDir, frotZ);

    dir->x = windDir.x;
    dir->y = windDir.y;
    dir->z = windDir.z;
}

s32 mEnv_GetWeatherChangeStep() {
    static u8 weather_term_table[][2] = {
        { lbRTC_JANUARY, 7 },    // January 1st - January 7th
        { lbRTC_FEBRUARY, 24 },  // January 8th - February 24th
        { lbRTC_MARCH, 31 },     // February 25th - March 31st
        { lbRTC_APRIL, 4 },      // April 1st - April 4th
        { lbRTC_APRIL, 7 },      // April 5th - April 7th
        { lbRTC_APRIL, 8 },      // April 8th - April 8th
        { lbRTC_APRIL, 19 },     // April 9th - April 19th
        { lbRTC_APRIL, 20 },     // April 20th - April 20th
        { lbRTC_JUNE, 15 },      // April 21st - June 15th
        { lbRTC_JULY, 15 },      // June 16th - July 15th
        { lbRTC_AUGUST, 31 },    // July 16th - August 31st
        { lbRTC_SEPTEMBER, 30 }, // September 1st - September 30th
        { lbRTC_OCTOBER, 30 },   // October 1st - October 30th
        { lbRTC_OCTOBER, 31 },   // October 31st - Octber 31st
        { lbRTC_NOVEMBER, 15 },  // November 1st - November 15th
        { lbRTC_DECEMBER, 9 },   // November 16th - December 9th
        { lbRTC_DECEMBER, 10 },  // December 10th - December 10th
        { lbRTC_DECEMBER, 23 },  // December 11th - December 23rd
        { lbRTC_DECEMBER, 30 },  // December 24th - December 30th
        { lbRTC_DECEMBER, 31 }   // December 31st - December 31st
    };

    lbRTC_month_t month = common_data.time.rtcTime.month;
    lbRTC_day_t day = common_data.time.rtcTime.day;
    s32 i;

    for (i = 0; i < 20; i++) {
        if (month < weather_term_table[i][0]) {
            return i;
        } else if (month == weather_term_table[i][0] && day <= weather_term_table[i][1]) {
            return i;
        }
    }

    return 1;
}

#define mEnv_MAKE_WEATHER_TABLE_ENTRY(clear, rain, thunder, snow, blizzard, sakura, heavySakura)    \
    ((((clear)&0xF) << 24) | (((rain)&0xF) << 16) | (((thunder)&0xF) << 20) | (((snow)&0xF) << 8) | \
     (((blizzard)&0xF) << 12) | (((sakura)&0xF) << 0) | (((heavySakura)&0xF) << 4))

void mEnv_RandomWeather(s16* next_weather, s16* next_intensity) {
    static const u32 weather_table[] = {
        mEnv_MAKE_WEATHER_TABLE_ENTRY(10, 0, 0, 0, 0, 0, 0), // 100% chance of clear weather
        mEnv_MAKE_WEATHER_TABLE_ENTRY(6, 0, 0, 3, 1, 0,
                                      0), // 60% chance of clear weather, 30% chance of snow, 10% chance of blizzard
        mEnv_MAKE_WEATHER_TABLE_ENTRY(8, 2, 0, 0, 0, 0, 0),  // 80% chance of clear weather, 20% chance of rain
        mEnv_MAKE_WEATHER_TABLE_ENTRY(10, 0, 0, 0, 0, 0, 0), // 100% chance of clear weather
        mEnv_MAKE_WEATHER_TABLE_ENTRY(0, 0, 0, 0, 0, 10, 0), // 100% chance of light cherry blossoms
        mEnv_MAKE_WEATHER_TABLE_ENTRY(0, 0, 0, 0, 0, 0, 10), // 100% chance of heavy cherry blossoms
        mEnv_MAKE_WEATHER_TABLE_ENTRY(8, 2, 0, 0, 0, 0, 0),  // 80% chance of clear weather, 20% chance of rain
        mEnv_MAKE_WEATHER_TABLE_ENTRY(10, 0, 0, 0, 0, 0, 0), // 100% chance of clear weather
        mEnv_MAKE_WEATHER_TABLE_ENTRY(
            7, 2, 1, 0, 0, 0, 0), // 70% chance of clear weather, 20% chance of rain, 10% chance of thunderstorms
        mEnv_MAKE_WEATHER_TABLE_ENTRY(
            2, 5, 3, 0, 0, 0, 0), // 20% chance of clear weather, 50% chance of rain, 30% chance of thunderstorms
        mEnv_MAKE_WEATHER_TABLE_ENTRY(9, 0, 1, 0, 0, 0, 0),  // 90% chance of clear weather, 10% chance of thunderstorms
        mEnv_MAKE_WEATHER_TABLE_ENTRY(6, 0, 4, 0, 0, 0, 0),  // 60% chance of clear weather, 40% chance of thunderstorms
        mEnv_MAKE_WEATHER_TABLE_ENTRY(8, 2, 0, 0, 0, 0, 0),  // 80% chance of clear weather, 20% chance of rain
        mEnv_MAKE_WEATHER_TABLE_ENTRY(10, 0, 0, 0, 0, 0, 0), // 100% chance of clear weather
        mEnv_MAKE_WEATHER_TABLE_ENTRY(8, 1, 0, 1, 0, 0,
                                      0), // 80% chance of clear weather, 10% chance of rain, 10% chance of snow
        mEnv_MAKE_WEATHER_TABLE_ENTRY(7, 0, 0, 3, 0, 0, 0),  // 70% chance of clear weather, 30% chance of snow
        mEnv_MAKE_WEATHER_TABLE_ENTRY(0, 0, 0, 0, 10, 0, 0), // 100% chance of blizzard
        mEnv_MAKE_WEATHER_TABLE_ENTRY(4, 0, 0, 4, 2, 0,
                                      0), // 40% chance of clear weather, 40% chance of snow, 20% chance of blizzard
        mEnv_MAKE_WEATHER_TABLE_ENTRY(0, 0, 0, 6, 4, 0, 0), // 60% chance of snow, 40% chance of blizzard
        mEnv_MAKE_WEATHER_TABLE_ENTRY(10, 0, 0, 0, 0, 0, 0) // 100% chance of clear weather
    };

    s32 step = mEnv_GetWeatherChangeStep();

    u32 weather = weather_table[step];
    u32 selected;
    u32 c0;
    u32 c1;
    u32 c2;
    u32 c3;
    u32 c4;
    u32 c5;

    c0 = (weather >> 24) & 0xF;
    c1 = (weather >> 16) & 0xF;
    c2 = (weather >> 20) & 0xF;
    c3 = (weather >> 8) & 0xF;
    c4 = (weather >> 12) & 0xF;
    c5 = (weather >> 8) & 0xF; // !@bug sets blizzard again, making light sakura weather impossible to get

    selected = RANDOM_F(10.0f);

    if (selected < c0) {
        next_weather[0] = mEnv_WEATHER_CLEAR;
        next_intensity[0] = mEnv_WEATHER_INTENSITY_LIGHT;
    } else if (selected < c0 + c1) {
        next_weather[0] = mEnv_WEATHER_RAIN;
        next_intensity[0] = mEnv_WEATHER_INTENSITY_LIGHT;
    } else if (selected < c0 + c1 + c2) {
        next_weather[0] = mEnv_WEATHER_RAIN;
        next_intensity[0] = mEnv_WEATHER_INTENSITY_HEAVY;
    } else if (selected < c0 + c1 + c2 + c3) {
        next_weather[0] = mEnv_WEATHER_SNOW;
        next_intensity[0] = mEnv_WEATHER_INTENSITY_LIGHT;
    } else if (selected < c0 + c1 + c2 + c3 + c4) {
        next_weather[0] = mEnv_WEATHER_SNOW;
        next_intensity[0] = mEnv_WEATHER_INTENSITY_HEAVY;
    } else if (selected < c0 + c1 + c2 + c3 + c4 + c5) {
        next_weather[0] = mEnv_WEATHER_SAKURA;
        next_intensity[0] = mEnv_WEATHER_INTENSITY_LIGHT;
    } else {
        next_weather[0] = mEnv_WEATHER_SAKURA;
        next_intensity[0] = mEnv_WEATHER_INTENSITY_HEAVY;
    }
}

mEnv_WindInfo mEnv_wind_info = {
    { 0, 0, 0, 1, 0, lbRTC_JANUARY, 2000 }, 8192.0f, 8192.0f, 0.0f, 0.5f, 0.5f, 0.0f,
};

s16 mEnv_GetWindAngleS() {
    return mEnv_wind_info.windAngleS;
}

f32 mEnv_GetWindPowerF(void) {
    return mEnv_wind_info.windPowerF;
}

void mEnv_ChangeWind() {
    f32 angle;
    f32 power;
    f32 rand;

    if (mEv_check_schedule(0x18)) {
        mEnv_wind_info.unk8 = 24576.0f;
        mEnv_wind_info.unk14 = 1.0f;
    } else {
        angle = RANDOM_F(5461.0f) - 2730.5f;
        rand = fqrand();
        power = (rand * 0.4f) - 0.2f;

        mEnv_wind_info.unk8 = mEnv_wind_info.windAngleS + angle;
        mEnv_wind_info.unk10 = angle / 18000.0f;

        mEnv_wind_info.unk14 = mEnv_wind_info.windPowerF + power;
        mEnv_wind_info.unk1C = power / 18000.0f;

        if (mEnv_wind_info.unk14 < 0.0f) {
            mEnv_wind_info.unk14 = 0.0f;
        } else if (mEnv_wind_info.unk14 > 1.0f) {
            mEnv_wind_info.unk14 = 1.0f;
        }
    }
}

void mEnv_InitWind() {
    if (mEv_check_schedule(0x18)) {
        mEnv_wind_info.unk8 = 24576.0f;
        mEnv_wind_info.unk14 = 1.0f;
    } else {
        mEnv_wind_info.unk8 = RANDOM_F(65536);
        mEnv_wind_info.unk14 = fqrand();
    }

    mEnv_wind_info.time = common_data.time.rtcTime;
    mEnv_wind_info.windAngleS = mEnv_wind_info.unk8;
    mEnv_wind_info.unk10 = 0.0f;
    mEnv_wind_info.unk1C = 0.0f;
    mEnv_wind_info.windPowerF = mEnv_wind_info.unk14;

    mEnv_WindMove();
}

void mEnv_WindMove() {
    if (lbRTC_IsOverTime(&mEnv_wind_info.time, &common_data.time.rtcTime) == TRUE) {
        mEnv_ChangeWind();
        mEnv_wind_info.time = common_data.time.rtcTime;
        lbRTC_Add_mm(&mEnv_wind_info.time, 10);
    }
    if (mEnv_wind_info.unk8 != mEnv_wind_info.windAngleS) {
        mEnv_wind_info.windAngleS += mEnv_wind_info.unk10;
        if (mEnv_wind_info.unk10 > 0.0f) {
            if (mEnv_wind_info.unk8 <= mEnv_wind_info.windAngleS) {
                mEnv_wind_info.windAngleS = mEnv_wind_info.unk8;
                mEnv_wind_info.unk10 = 0.0f;
            }
        } else if (mEnv_wind_info.unk10 < 0.0f && mEnv_wind_info.windAngleS <= mEnv_wind_info.unk8) {
            mEnv_wind_info.windAngleS = mEnv_wind_info.unk8;
            mEnv_wind_info.unk10 = 0.0f;
        }
    }
    if (mEnv_wind_info.unk14 != mEnv_wind_info.windPowerF) {
        mEnv_wind_info.windPowerF += mEnv_wind_info.unk1C;
        if (mEnv_wind_info.unk1C > 0.0f) {
            if (mEnv_wind_info.unk14 <= mEnv_wind_info.windPowerF) {
                mEnv_wind_info.windPowerF = mEnv_wind_info.unk14;
                mEnv_wind_info.unk1C = 0.0f;
            }
        } else if (mEnv_wind_info.unk1C < 0.0f && mEnv_wind_info.windPowerF <= mEnv_wind_info.unk14) {
            mEnv_wind_info.windPowerF = mEnv_wind_info.unk14;
            mEnv_wind_info.unk1C = 0.0f;
        }
    }
}

void mEnv_DecideWeather_GameStart() {
    s16 weather;
    s16 intensity;
    s16 eventWeather;
    s16 eventIntensity;

    mEnv_RandomWeather(&weather, &intensity);
    mEv_GetEventWeather(&eventWeather, &eventIntensity);

    if (eventWeather != -1) {
        weather = eventWeather;
        intensity = eventIntensity;
    }

    if (mEv_CheckRealArbeit() == TRUE && weather == mEnv_WEATHER_RAIN) {
        weather = mEnv_WEATHER_CLEAR;
        intensity = mEnv_WEATHER_INTENSITY_NONE;
    }

    common_data.weather = weather;
    common_data.weatherIntensity = intensity;
    common_data.weatherTime = common_data.time.rtcTime;
    mEnv_InitWind();
}

void mEnv_DecideWeather_FirstGameStart() {
    u8 saveWeather;
    u8 intensity;
    u8 weather;

    mEnv_DecideWeather_GameStart();

    weather = (u8)common_data.weather;
    intensity = (u8)common_data.weatherIntensity;

    saveWeather = ENV_SAVE_SET_WEATHER(intensity, weather);

    common_data.save.saveWeather = saveWeather;

    if (mTM_check_renew_time(mTM_RENEW_TIME_WEATHER)) {
        mTM_off_renew_time(mTM_RENEW_TIME_WEATHER);
    }
}

void mEnv_DecideWeather_NormalGameStart() {
    u8 saveWeather;
    u8 weather;
    u8 intensity;
    u8 lastWeather;

    if (mTM_check_renew_time(mTM_RENEW_TIME_WEATHER)) {
        mEnv_DecideWeather_GameStart();
        mTM_off_renew_time(mTM_RENEW_TIME_WEATHER);

        weather = common_data.weather;
        intensity = common_data.weatherIntensity;
        saveWeather = (common_data.save.saveWeather & 0xF0);
        lastWeather = ENV_SAVE_GET_WEATHER_TYPE(common_data.save.saveWeather);

        if (weather == mEnv_WEATHER_CLEAR || weather == mEnv_WEATHER_SAKURA) {
            if (lastWeather == mEnv_WEATHER_SNOW || lastWeather == mEnv_WEATHER_RAIN) {
                mAGrw_OrderSetHaniwa();
            }
        }
        common_data.save.saveWeather = ENV_SAVE_SET_WEATHER(intensity, weather);
    } else {
        saveWeather = common_data.save.saveWeather;
        weather = ENV_SAVE_GET_WEATHER_TYPE(saveWeather);
        intensity = ENV_SAVE_GET_WEATHER_INTENSITY(saveWeather);

        if (mEv_CheckRealArbeit() == TRUE && weather == mEnv_WEATHER_RAIN) {
            weather = mEnv_WEATHER_CLEAR;
            intensity = mEnv_WEATHER_INTENSITY_NONE;

            common_data.save.saveWeather = ENV_SAVE_SET_WEATHER(intensity, weather);
        }

        common_data.weather = weather;
        common_data.weatherIntensity = intensity;
    }
}

s32 mEnv_NowWeather() {
    switch (mEv_CheckTitleDemo()) {
        case 1:
            return mEnv_WEATHER_SAKURA;
        case 2:
            return mEnv_WEATHER_RAIN;
        case 3:
        case 4:
            return mEnv_WEATHER_CLEAR;
        case 5:
            return mEnv_WEATHER_SNOW;
    }
    if (FI_GET_TYPE(mFI_GetFieldId()) == 0) {
        return common_data.weather;
    }

    return mEnv_WEATHER_CLEAR;
}

s32 mEnv_CheckNpcRoomPointLightNiceStatus() {
    Animal_c* animal;
    NpsSchedule* schedule;
    s32 ret = FALSE;

    animal = mNpc_GetAnimalInfoP(common_data.houseOwnerName);

    if (animal != NULL) {
        schedule = mNPS_get_schedule_area(&animal->id);

        if (schedule != NULL) {
            if (schedule->currentType == NPS_SCHEDULE_IN_HOUSE && animal->isHome == TRUE &&
                (common_data.time.nowSec < mTM_TIME_TO_SEC(5, 0, 0) ||
                 common_data.time.nowSec >= mTM_TIME_TO_SEC(18, 0, 0))) {
                ret = TRUE;
            }
        }
    }

    return ret;
}

void mEnv_TaimatuPointLightWaveMoveProc(Game_Play* play) {
    static s16 point_light_wave_counter;

    point_light_wave_counter += 800;

    if (l_mEnv_point_light_is_flame_electric_light) {
        f32 wave = sin_s(point_light_wave_counter);
        u8 c = (s32)(((wave >= 0.0f ? sin_s(point_light_wave_counter) : -sin_s(point_light_wave_counter)) * 40.0f) +
                     40.0f);

        play->kankyo.pointLight.lights.point.color[0] = 255 - c;
        play->kankyo.pointLight.lights.point.color[1] = 240 - c;
    }
}

void mEnv_CheckNpcLight_ToSwitchON(Game_Play* play) {
    UNUSED s32 pad;
    if (common_data.save.sceneNo == SCENE_NPC_HOUSE && l_mEnv_index_light_switch_electric_light != 0 &&
        mEnv_CheckNpcRoomPointLightNiceStatus()) {
        l_mEnv_point_light_on_electric_light = TRUE;
        l_mEnv_index_light_switch_electric_light = FALSE;
        Light_point_ct(&play->kankyo.pointLight, 160, 180, 240, 220, 220, 180, 1000);
        l_mEnv_current_lightnode_electric_light = Global_light_list_new(play, &play->glight, &play->kankyo.pointLight);
    }
}

void target_lighting_amb(Game_Play* play, f32 f0) {
    u16 i;

    if (f0 > 0.999f) {
        for (i = 0; i < 3; i++) {
            play->kankyo.addLightsInfo.ambientColor[i] = -255;
        }
    } else {
        for (i = 0; i < 3; i++) {
            play->kankyo.addLightsInfo.ambientColor[i] = (s32)((f32)-play->kankyo.baseLight.ambientColor[i] * f0);
        }
    }
}

void target_lighting_dif(Game_Play* play, f32 f0) {
    u16 i;

    if (f0 > 0.999f) {
        for (i = 0; i < 3; i++) {
            play->kankyo.addLightsInfo.diffuseColor[i] = l_mEnv_add_moon_color_electric_light[i] = -255;
        }
    } else {
        for (i = 0; i < 3; i++) {
            play->kankyo.addLightsInfo.diffuseColor[i] = (s32)(-play->kankyo.baseLight.sunColor[i] * f0);
            l_mEnv_add_moon_color_electric_light[i] = (s32)((f32)-play->kankyo.baseLight.moonColor[i] * f0);
        }
    }
}

void target_lighting_fog(Game_Play* play, f32 f0) {

    if (f0 > 0.999f) {
        u16 i;
        for (i = 0; i < 3; i++) {
            play->kankyo.addLightsInfo.fogNear = mEnv_FOG_NEAR_MAX;
            play->kankyo.addLightsInfo.fogFar = mEnv_FOG_FAR_MAX;
        }
    } else {
        s16 near = mEnv_FOG_NEAR_MAX - play->kankyo.baseLight.fogNear;
        s16 far = mEnv_FOG_FAR_MAX - play->kankyo.baseLight.fogFar;

        play->kankyo.addLightsInfo.fogNear = near * f0;
        play->kankyo.addLightsInfo.fogFar = far * f0;
    }
}

void mEnv_PointLightSet(Game_Play* play, f32 f0) {
    Player* player = get_player_actor_withoutCheck(play);
    s16* KKData = (s16*)mEv_get_save_area(0x21, 0xA);

    Light_point_ct(&play->kankyo.pointLight, player->actor.world.pos.x, player->actor.world.pos.y,
                   player->actor.world.pos.z - 25.0f, 255, 255, 220, (*KKData * (1.0f - f0)));
}

void staffroll_light_init(Game_Play* play) {
    l_mEnv_staffroll_fade_rate_electric_light = 1.0f;
    mEnv_PointLightSet(play, l_mEnv_staffroll_fade_rate_electric_light);
    S_get_light_list = Global_light_list_new(play, &play->glight, &play->kankyo.pointLight);
}

void staffroll_light_proc_start(Game_Play* play) {
    add_calc(&l_mEnv_staffroll_fade_rate_electric_light, 0.0f, 0.5f, 0.01f, 0.00001f);
    target_lighting_amb(play, 1.0f - l_mEnv_staffroll_fade_rate_electric_light);
    target_lighting_dif(play, 1.0f - l_mEnv_staffroll_fade_rate_electric_light);
    target_lighting_fog(play, 1.0f - l_mEnv_staffroll_fade_rate_electric_light);

    play->kankyo.shadowAlpha = (s32)(play->kankyo.shadowAlpha * l_mEnv_staffroll_fade_rate_electric_light);
    mEnv_PointLightSet(play, l_mEnv_staffroll_fade_rate_electric_light);
}

s32 staffroll_light_proc_end(Game_Play* play) {
    s32 ret = FALSE;
    add_calc(&l_mEnv_staffroll_fade_rate_electric_light, 1.0f, 0.5f, 0.01f, 0.00001f);
    target_lighting_amb(play, 1.0f - l_mEnv_staffroll_fade_rate_electric_light);
    target_lighting_dif(play, 1.0f - l_mEnv_staffroll_fade_rate_electric_light);
    target_lighting_fog(play, 1.0f - l_mEnv_staffroll_fade_rate_electric_light);

    play->kankyo.shadowAlpha = (s32)(play->kankyo.shadowAlpha * l_mEnv_staffroll_fade_rate_electric_light);
    mEnv_PointLightSet(play, l_mEnv_staffroll_fade_rate_electric_light);

    if ((s16)(l_mEnv_staffroll_fade_rate_electric_light * 1000.0f) >= 1000) {
        ret = TRUE;
    }
    return ret;
}

void staffroll_light_dt(Game_Play* play) {
    Global_light_list_delete(&play->glight, S_get_light_list);
}

void mEnv_GetShadowPrimColor_Light(u8* r, u8* g, u8* b, Game_Play* play) {
    Kankyo* kankyo = &play->kankyo;

    r[0] = kankyo->baseLight.shadowColor[0];
    g[0] = kankyo->baseLight.shadowColor[1];
    b[0] = kankyo->baseLight.shadowColor[2];
}

u8 mEnv_GetCurrentLightSwitchStatus() {
    return l_mEnv_point_light_on_electric_light;
}

s32 mEnv_HereIsPlayerSelect() {
    static s32 place_chk[4] = { SCENE_PLAYERSELECT, SCENE_PLAYERSELECT_2, SCENE_PLAYERSELECT_3,
                                SCENE_PLAYERSELECT_SAVE };
    s32 ret = FALSE;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (common_data.save.sceneNo == place_chk[i]) {
            ret = TRUE;
            break;
        }
    }

    return ret;
}
void mEnv_MakeWindowLightAlpha(s32 enabled) {
    f32 step = 1.0f / 100.0f;
    f32 target = 0.0f;
    if (common_data.fieldDrawType == FIELD_DRAW_TYPE_INDOORS) {
        if (enabled == FALSE) {
            step = 1.0f;
            l_mEnv_windowlight_alpha_electric_light = 0.0f;
        }

        if (common_data.save.sceneNo == SCENE_MY_ROOM_S || common_data.save.sceneNo == SCENE_MY_ROOM_M ||
            common_data.save.sceneNo == SCENE_MY_ROOM_L) {
            if (common_data.time.nowSec >= mTM_TIME_TO_SEC(5, 0, 0) &&
                common_data.time.nowSec < mTM_TIME_TO_SEC(18, 0, 0)) {
                target = 1.0f;
            } else {
                target = 0.0f;

                if (mEnv_GetCurrentLightSwitchStatus() == 0) {
                    target = 1.0f;
                }
            }
        } else if (common_data.save.sceneNo == SCENE_NPC_HOUSE) {
            target = 0.0f;
            if (mEnv_GetCurrentLightSwitchStatus() == 0) {
                target = 1.0f;
            }
        } else if (common_data.time.nowSec >= mTM_TIME_TO_SEC(5, 0, 0) &&
                   common_data.time.nowSec < mTM_TIME_TO_SEC(18, 0, 0)) {
            target = 1.0f;
        }
        add_calc(&l_mEnv_windowlight_alpha_electric_light, target, 0.2f, step, step);
    }
}

f32 mKK_windowlight_alpha_get() {
    return l_mEnv_windowlight_alpha_electric_light;
}
