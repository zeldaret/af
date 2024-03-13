#include "ac_weather.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "audio.h"
#include "m_common_data.h"
#include "m_scene_table.h"
#include "m_player_lib.h"
#include "ovlmgr.h"
#include "m_malloc.h"
#include "m_field_info.h"
#include "m_rcp.h"
#include "code_variables.h"
#include "m_kankyo.h"
#include "6EDD10.h"
#include "m_event.h"
#include "6792F0.h"
#include "683030.h"
#include "segment_symbols.h"

#include "overlays/weather/ac_weather_fine/ac_weather_fine.h"
#include "overlays/weather/ac_weather_rain/ac_weather_rain.h"
#include "overlays/weather/ac_weather_snow/ac_weather_snow.h"
#include "overlays/weather/ac_weather_sakura/ac_weather_sakura.h"
#include "overlays/weather/ac_weather_leaf/ac_weather_leaf.h"

void Weather_Actor_ct(Actor* thisx, Game_Play* play);
void Weather_Actor_dt(Actor* thisx, Game_Play* game_play);
void Weather_Actor_move(Actor* thisx, Game_Play* play);
void Weather_Actor_draw(Actor* thisx, Game_Play* play);

WeatherOvlInfo profile_tbl[] = {
    WEATHER_OVERLAY_NONE(ac_weather_fine, &iam_weather_fine),
    WEATHER_OVERLAY(ac_weather_rain, func_80A3C130_jp, &iam_weather_rain),
    WEATHER_OVERLAY(ac_weather_snow, func_80A3C890_jp, &iam_weather_snow),
    WEATHER_OVERLAY(ac_weather_sakura, func_80A3D010_jp, &iam_weather_sakura),
    WEATHER_OVERLAY(ac_weather_leaf, func_80A3D7E0_jp, &iam_weather_leaf),
};

WeatherDmaInfo WeatherRainDmaInfo = {
    WEATHER_SEGMENT_DMA(segment_01408000),
};

WeatherDmaInfo WeatherSnowDmaInfo = {
    WEATHER_SEGMENT_DMA(segment_01409000),
};

WeatherDmaInfo WeatherSakuraDmaInfo = {
    WEATHER_SEGMENT_DMA(segment_0140A000),
};

WeatherDmaInfo WeatherLeafDmaInfo = {
    WEATHER_SEGMENT_DMA(segment_0140B000),
};

WeatherDmaInfo* weatherDmaTable[] = {
    NULL, &WeatherRainDmaInfo, &WeatherSnowDmaInfo, &WeatherSakuraDmaInfo, &WeatherLeafDmaInfo,
};

ActorProfile Weather_Profile = {
    /* */ ACTOR_WEATHER,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Weather),
    /* */ Weather_Actor_ct,
    /* */ Weather_Actor_dt,
    /* */ Weather_Actor_move,
    /* */ Weather_Actor_draw,
    /* */ NULL,
};

void func_80A21DFC_jp(Actor* thisx, s16 /*id*/);
void aWeather_ChangingWeather(void);
s32 aWeather_CountWeatherPrivate(Weather* this);
void aWeather_AbolishPrivate(Actor* thisx, s32 /*num*/);
void aWeather_SetNowProfile(Actor* thisx, s16 id);

void aWeather_SysLevCall_MoveEnd(Weather* this) {
    if (this->stopSoundEffect != 0) {
        sAdo_SysLevStop(this->stopSoundEffect);
    }
    if (this->startSoundEffect != 0) {
        sAdo_SysLevStart(this->startSoundEffect);
    }
    this->stopSoundEffect = 0;
    this->startSoundEffect = 0;
}

void aWeather_SysLevStart(u8 flag) {
    s32 startFlag = flag;
    Weather* this = common_data.clip.weatherClip->actor;
    this->startSoundEffect = startFlag;
}

void aWeather_SysLevStop(u8 flag) {
    Weather* this = common_data.clip.weatherClip->actor;
    s16 stopFlag = flag;

    if (this->startSoundEffect == stopFlag) {
        this->startSoundEffect = 0;
    } else {
        this->stopSoundEffect = flag;
    }
}
void aWeather_weatherinfo_CommonSet(s16 type, s16 intensity) {
    if (type >= 4) {
        type = 0;
    }

    common_data.weather = type;
    common_data.weatherIntensity = intensity;
}

void aWeather_RequestChangeWeather(Actor* thisx, s16 status, s16 level) {
    Weather* this = (Weather*)thisx;

    if (status != this->currentStatus) {
        this->nextStatus = status;
        this->nextLevel = level;
        this->requestChange = TRUE;
        this->currentAimLevel = 0;
    } else {
        this->currentAimLevel = level;
    }
}

s32 aWeather_GetWeatherPrvNum(Actor* thisx) {
    Weather* this = (Weather*)thisx;
    WeatherPrv* priv = this->priv;

    s32 i;

    for (i = 0; i != 100; i++) {
        if (priv->use == 0) {
            return i;
        }
        priv++;
    }

    return -1;
}

void aWeather_AbolishPrivate(Actor* thisx, s32 num) {
    Weather* this = (Weather*)thisx;
    WeatherPrv* priv = this->priv;

    if (priv != NULL) {
        if ((&priv[num])->use != 0) {
            (&priv[num])->use = 0;
        }
    }
}

WeatherPrv* aWeather_GetWeatherPrv(u8 status, s16 timer, xyz_t* pos, xyz_t* speed, Actor* thisx, int id) {
    Weather* this = (Weather*)thisx;
    WeatherPrv* priv = this->priv;

    if ((id != -1) && (id < 100)) {
        if (priv[id].use == 0) {
            priv[id].use = 1;
            priv[id].status = status;
            priv[id].timer = timer;
            priv[id].id = id;
            if (pos != NULL) {
                priv[id].pos = *pos;
            }
            if (speed != NULL) {
                priv[id].speed = *speed;
            }
            return &priv[id];
        }
        return NULL;
    }
    return NULL;
}

s32 aWeather_StopSysLevSE() {
    Weather* this = common_data.clip.weatherClip->actor;

    u8 current = this->currentSoundEffect;

    if (this->soundFlag == 0) {
        if ((current == 7) || (current == 8) || (current == 9) || (current == 18) || (current == 19) ||
            (current == 20)) {
            aWeather_SysLevStop(current);
        }
        this->soundFlag = 1;
        return 1;
    } else {
        return 0;
    }
}

s32 aWeather_StartSysLevSE() {
    Weather* this = common_data.clip.weatherClip->actor;

    if (this->soundFlag == 1) {
        if (ENV_SAVE_GET_WEATHER_TYPE(common_data.saveWeather) == 1) {
            switch (ENV_SAVE_GET_WEATHER_INTENSITY(common_data.saveWeather)) {
                case 1:
                    aWeather_SysLevStart(7);
                    this->currentSoundEffect = 7;
                    break;

                case 2:
                    aWeather_SysLevStart(8);
                    this->currentSoundEffect = 8;
                    break;

                case 3:
                    aWeather_SysLevStart(9);
                    this->currentSoundEffect = 9;
                    break;
            }
        }
        this->soundFlag = 2;
    }
    return 0;
}

void aWeather_ChangeWeatherInstance(Weather* this, s16 status, s16 level) {
    this->nextStatus = status;
    this->nextLevel = level;
    this->currentStatus = status;
    this->currentLevel = 0;
    this->requestChange = TRUE;

    if (!aWeather_CountWeatherPrivate(this)) {
        this->currentStatus = this->nextStatus;
        aWeather_SetNowProfile(&this->actor, this->currentStatus);
        func_80A21DFC_jp(&this->actor, this->currentStatus);
        aWeather_weatherinfo_CommonSet(this->currentStatus, this->nextLevel);
        this->currentLevel = level;
        this->currentAimLevel = this->nextLevel;
        this->requestChange = FALSE;
    }
}

void aWeather_ChangeEnvSE(Weather* this, Game_Play* play, s16 status, s16 level) {
    UNUSED s32 pad;
    u8 current = this->currentSoundEffect;

    if (this->soundFlag == 1 || this->soundFlag == 2) {
        return;
    }

    if ((current == 7) || (current == 8) || (current == 9) || (current == 18) || (current == 19) || (current == 20)) {
        aWeather_SysLevStop(current);
        this->currentSoundEffect = -1000;
    }

    if (mEv_CheckTitleDemo() <= 0) {
        if (common_data.sceneNo == SCENE_START_DEMO || common_data.sceneNo == SCENE_START_DEMO2) {
            return;
        }
        if ((status == 1) && (this->currentSoundEffect == -1000)) {
            switch (level) {
                case 1:
                    if (mPlib_check_player_open_umbrella(play) != 0) {
                        aWeather_SysLevStart(0x12);
                        this->currentSoundEffect = 0x12;
                    } else {
                        aWeather_SysLevStart(7);
                        this->currentSoundEffect = 7;
                    }
                    break;
                case 2:
                    if (mPlib_check_player_open_umbrella(play) != 0) {
                        aWeather_SysLevStart(0x13);
                        this->currentSoundEffect = 0x13;
                    } else {
                        aWeather_SysLevStart(8);
                        this->currentSoundEffect = 8;
                    }
                    break;
                case 3:
                    if (mPlib_check_player_open_umbrella(play) != 0) {
                        aWeather_SysLevStart(0x14);
                        this->currentSoundEffect = 0x14;
                    } else {
                        aWeather_SysLevStart(9);
                        this->currentSoundEffect = 9;
                    }
                    break;
            }
        }
    }
}

void aWeather_EndEnvSE(Actor* thisx) {
    Weather* this = (Weather*)thisx;
    u8 current = this->currentSoundEffect;

    if (sAdo_GameframeEnd_Check() == 1) {
        if ((current == 7) || (current == 8) || (current == 9) || (current == 18) || (current == 19) ||
            (current == 20)) {
            aWeather_SysLevStop(current);
            this->currentSoundEffect = -1000;
            common_data.currentSoundEffect = -1000;
        }
    } else if (sAdo_GameframeEnd_Check() == 2) {
        common_data.currentSoundEffect = this->currentSoundEffect;
    }

    aWeather_SysLevCall_MoveEnd(this);
}
// fabricated name from ac_tools
void aWeather_secure_bank_area(Weather* this, Game_Play* play) {
    UNUSED s32 pad[3];
    s32 bank = play->objectExchangeBank.num;

    if (mSc_secure_exchange_keep_bank(&play->objectExchangeBank, 0, 0xA00)) {
        this->segment = play->objectExchangeBank.status[bank].segment;
    }
}

void func_80A21DFC_jp(Actor* thisx, s16 id) {
    Weather* this = (Weather*)thisx;

    if (weatherDmaTable[id] != NULL) {
        if (this->segment != NULL) {
            if (weatherDmaTable[id]->vromStart != 0) {
                if (weatherDmaTable[id]->vromEnd != 0) {
                    DmaMgr_RequestSyncDebug(this->segment, weatherDmaTable[id]->vromStart,
                                            weatherDmaTable[id]->vromEnd - weatherDmaTable[id]->vromStart,
                                            "../ac_weather.c", 836);
                }
            }
        }
    }
}

void aWeather_SetNowProfile(Actor* thisx, s16 id) {
    Weather* this = (Weather*)thisx;

    this->currentProfile = NULL;
    if (this->allocatedSize != NULL) {
        uintptr_t size = (uintptr_t)profile_tbl[id].vramEnd - (uintptr_t)profile_tbl[id].vramStart;
        if (size <= 0xC00) {
            ovlmgr_Load(profile_tbl[id].vromStart, profile_tbl[id].vromEnd, profile_tbl[id].vramStart,
                        profile_tbl[id].vramEnd, this->allocatedSize);
            this->currentProfile =
                (WeatherProfile*)(((uintptr_t)this->allocatedSize + (uintptr_t)profile_tbl[id].ovlTypeEnd) -
                                  (uintptr_t)profile_tbl[id].vramStart);
        }
    }
}

void func_80A21F14_jp(Weather* this) {
    this->allocatedSize = zelda_malloc(0xC00);
}

void aWeather_SecureWeatherPrivateWork(Weather* this) {
    s32 i;

    this->priv = zelda_malloc(sizeof(WeatherPrv) * 100);

    if (this->priv != NULL) {
        for (i = 0; i < 100; i++) {
            bzero(&this->priv[i], sizeof(WeatherPrv));
        }
    }
}

void aWeather_SetClip(Weather* this, s32 flag) {
    WeatherClip* clip;

    if (flag != 0) {
        common_data.clip.weatherClip = NULL;
    } else {
        clip = &this->clip;

        clip->actor = this;
        clip->changingWeather = aWeather_ChangingWeather;
        clip->changeWeather = aWeather_RequestChangeWeather;
        clip->getPrvNum = aWeather_GetWeatherPrvNum;
        clip->removePrv = aWeather_AbolishPrivate;
        clip->getPrv = aWeather_GetWeatherPrv;
        clip->stopSound = aWeather_StopSysLevSE;
        clip->startSound = aWeather_StartSysLevSE;
        clip->changeWeatherInstance = aWeather_ChangeWeatherInstance;

        common_data.clip.weatherClip = clip;
    }
}

void aWeather_RenewWindInfo(Weather* this) {
    UNUSED s32 pad;
    s_xyz pos = common_data.wind;
    f32 factor = 1.0f / 1.0f;
    f32 speed = common_data.windSpeed * 0.01f;

    this->windInfo.x = (pos.x * speed * factor);
    this->windInfo.y = (pos.y * speed * factor);
    this->windInfo.z = (pos.z * speed * factor);
}

void aWeather_SnowInAdvance(Weather* this, Game_Play* play, s32 moves) {
    s32 i;

    for (i = 0; i < moves; i++) {
        Weather_Actor_move(&this->actor, play);
    }
}

void Weather_Actor_ct(Actor* thisx, Game_Play* play) {
    static s16 DemoWeatherTbl[5][2] = {
        3, 1, 1, 2, 0, 0, 0, 0, 2, 1,
    };
    Weather* this = (Weather*)thisx;
    UNUSED s32 pad;

    xyz_t* pos = Camera2_getCenterPos_p();
    s32 cur;

    aWeather_SetClip(this, 0);

    if (mEv_CheckTitleDemo() > 0) {
        UNUSED s32 scopedTemp;

        cur = mEv_CheckTitleDemo() - 1;

        this->currentStatus = DemoWeatherTbl[cur][0];
        this->nextStatus = DemoWeatherTbl[cur][0];
        this->currentLevel = DemoWeatherTbl[cur][1];
        this->currentAimLevel = DemoWeatherTbl[cur][1];

    } else {
        this->currentStatus = common_data.weather;
        this->nextStatus = this->currentStatus;
        this->currentLevel = common_data.weatherIntensity;
        this->currentAimLevel = common_data.weatherIntensity;
    }

    this->segment = NULL;
    this->priv = NULL;
    this->requestChange = FALSE;

    this->pos = *pos;

    this->timer = 0;
    this->timer2 = 0;
    this->lightningTimer = 0;
    this->lightningTimer2 = 30;

    this->soundFlag = 0;
    aWeather_RenewWindInfo(this);

    if (!FI_GET_TYPE(mFI_GetFieldId())) {
        func_80A21F14_jp(this);
        aWeather_secure_bank_area(this, play);
        aWeather_SecureWeatherPrivateWork(this);
    }

    aWeather_SetNowProfile(thisx, this->currentStatus);
    func_80A21DFC_jp(&this->actor, this->currentStatus);

    if ((this->currentStatus == 2) || (this->currentStatus == 3)) {
        this->pos.y -= 50.0f;
        aWeather_SnowInAdvance(this, play, 0x28);
        this->pos.y += 50.0f;
    }

    this->stopSoundEffect = 0;
    this->startSoundEffect = 0;
    if (play->unk_1EE1 == 6) {
        this->currentSoundEffect = common_data.currentSoundEffect;
    } else {
        this->currentSoundEffect = -1000;
        aWeather_ChangeEnvSE(this, play, this->currentStatus, this->currentLevel);
        aWeather_SysLevCall_MoveEnd(this);
    }
}

void Weather_Actor_dt(Actor* thisx, UNUSED Game_Play* play) {
    Weather* this = (Weather*)thisx;

    if (this->priv != NULL) {
        zelda_free(this->priv);
    }
    if (this->allocatedSize != 0) {
        zelda_free(this->allocatedSize);
    }

    aWeather_SetClip(this, 1);
}

void aWeather_DrawWeatherPrv(Actor* thisx, Game_Play* play) {
    Weather* this = (Weather*)thisx;

    WeatherPrv* priv = this->priv;
    s32 i;

    _texture_z_light_fog_prim_xlu(play->state.gfxCtx);
    gSegments[6] = OS_K0_TO_PHYSICAL(this->segment);

    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 6, this->segment);

    CLOSE_DISPS(play->state.gfxCtx);

    if ((this->currentProfile != NULL) && (priv != NULL)) {
        if (this->currentProfile->st != NULL) {
            this->currentProfile->st(play);
        }
        if (this->currentProfile->dw != NULL) {
            for (i = 0; i < 100; i++, priv++) {
                if (priv->use != 0) {
                    this->currentProfile->dw(priv, play);
                }
            }
        }
    }
}

void Weather_Actor_draw(Actor* thisx, Game_Play* play) {
    aWeather_DrawWeatherPrv(thisx, play);
}

void aWeather_MakeWeatherPrv(Actor* thisx, Game_Play* play) {
    Weather* this = (Weather*)thisx;

    if (this->currentLevel != 0) {
        if (this->currentProfile != NULL) {
            if (this->currentProfile->mk != NULL) {
                this->currentProfile->mk(thisx, play);
            }
        }
    }
}

void aWeather_MoveWeatherPrv(Weather* this, Game_Play* play) {
    WeatherPrv* priv = this->priv;
    s32 i;

    if ((this->currentProfile != NULL) && (priv != NULL) && (this->currentProfile->mv != NULL)) {
        gSegments[6] = OS_K0_TO_PHYSICAL(this->segment);

        OPEN_DISPS(play->state.gfxCtx);

        gSPSegment(POLY_XLU_DISP++, 6, this->segment);

        CLOSE_DISPS(play->state.gfxCtx);

        for (i = 0; i != 100; priv++) {
            if (priv->use != 0) {
                this->currentProfile->mv(priv, play);

                if (priv->timer != -100) {
                    priv->timer--;

                    if (priv->timer <= 0) {
                        aWeather_AbolishPrivate(&this->actor, i);
                    }
                }
            }
            // FAKE!!
            { i++, i--, i++; }
        }
    }
}

s32 aWeather_CountWeatherPrivate(Weather* this) {
    s32 i;
    s32 count;
    WeatherPrv* priv = this->priv;

    count = 0;

    for (i = 0; i < 100; i++, priv++) {
        if (priv->use != 0) {
            count++;
        }
    }

    return count;
}

void aWeather_ChangeWeather(Weather* this, Game_Play* play) {
    if ((this->requestChange == TRUE) && (this->currentLevel == 0)) {
        if (FI_GET_TYPE(mFI_GetFieldId())) {
            this->currentStatus = this->nextStatus;
            aWeather_weatherinfo_CommonSet(this->currentStatus, this->nextLevel);
            this->currentLevel = 1;
            this->currentAimLevel = this->nextLevel;
            aWeather_ChangeEnvSE(this, play, this->currentStatus, this->currentLevel);
            this->requestChange = FALSE;
        } else if (aWeather_CountWeatherPrivate(this) == 0) {
            this->currentStatus = this->nextStatus;
            aWeather_SetNowProfile(&this->actor, this->currentStatus);
            func_80A21DFC_jp(&this->actor, this->currentStatus);
            aWeather_weatherinfo_CommonSet(this->currentStatus, this->nextLevel);
            this->currentLevel = 1;
            this->currentAimLevel = this->nextLevel;
            aWeather_ChangeEnvSE(this, play, this->currentStatus, this->currentLevel);
            this->requestChange = FALSE;
        }
    }
}

void aWeather_CheckWeatherTimer(UNUSED Weather* this) {
    s_xyz dir;

    mEnv_DecideWindDirect(&dir, 0x3000, 0x3000);
}

void aWeather_RenewWeatherLevel(Weather* this, Game_Play* play) {
    if (this->currentLevel != this->currentAimLevel) {
        this->counter++;
        if (this->counter >= 90) {
            this->counter = 0;
            if (this->currentAimLevel < this->currentLevel) {
                this->currentLevel--;
            } else {
                this->currentLevel++;
            }
            aWeather_ChangeEnvSE(this, play, this->currentStatus, this->currentLevel);
        }
    }
}

void aWeather_ChangeWeatherTime0(Weather* this) {
    UNUSED s32 pad;
    s16 saveWeather;
    s16 rndWeather;
    s16 rndIntensity;
    s16 evWeather;
    s16 evIntensity;
    s16 saveRnd;

    if ((mEv_CheckTitleDemo() <= 0)) {
        if ((common_data.sceneNo == 15) || (common_data.sceneNo == 16)) {
            return;
        }
        if ((mTM_check_renew_time(0) != 0)) {
            mEnv_RandomWeather(&rndWeather, &rndIntensity);
            mEv_GetEventWeather(&evWeather, &evIntensity);
            if (evWeather != -1) {
                rndWeather = evWeather;
                rndIntensity = evIntensity;
            }
            if ((mEv_CheckRealArbeit() == 1) && (rndWeather == 1)) {
                rndWeather = 0;
                rndIntensity = 0;
            }
            mTM_off_renew_time(0);

            saveWeather = ENV_SAVE_GET_WEATHER_TYPE(common_data.saveWeather);
            if (rndWeather == 0 || rndWeather == 3) {
                if (saveWeather == 2 || saveWeather == 1) {
                    mAGrw_OrderSetHaniwa();
                }
            }
            saveRnd = rndIntensity | ((rndWeather ^ 0) * 16);
            common_data.saveWeather = saveRnd;

            if (((mEv_CheckTitleDemo() != -9) || (this->soundFlag != 1))) {
                aWeather_RequestChangeWeather(&this->actor, rndWeather, rndIntensity);
            }
            common_data.weatherTime = common_data.time.rtcTime;
        }
    }
}

void aWeather_MakeKaminari(Actor* thisx) {
    Weather* this = (Weather*)thisx;
    lbRTC_time_c time = common_data.time.rtcTime;
    u8 month = time.month;

    if ((common_data.sceneNo != 15) && (common_data.sceneNo != 16)) {
        if ((month >= lbRTC_JUNE) && (month <= lbRTC_AUGUST) && (this->currentStatus == 1)) {
            s16* ptr = &this->lightningTimer;
            if (this->currentLevel == 3) {
                s16 timer = ptr[0] % 1000;
                if (((timer == this->lightningTimer2) || (timer == (this->lightningTimer2 + 20))) &&
                    (common_data.clip.unk_090 != NULL)) {
                    Color_RGBA8 color = { 70, 70, 160, 255 };

                    common_data.clip.unk_090->unk_30(color, 2, 0x23, 0);
                }
                if (timer == (this->lightningTimer2 + 65)) {
                    sAdo_SysTrgStart(0x424);
                    this->lightningTimer2 = ((RANDOM_F(500.0f) + 100.0f));
                }
                ptr[0]++;
            }
        }
    }
}

void Weather_Actor_move(Actor* thisx, Game_Play* play) {
    xyz_t* pos = Camera2_getCenterPos_p();
    Weather* this = (Weather*)thisx;

    UNUSED s32 pad[3];
    s16 angle = search_position_angleY(&play->camera.unk4, &play->camera.unk0);
    s16 umbrella;

    aWeather_MakeKaminari(thisx);
    aWeather_CheckWeatherTimer(this);
    aWeather_MakeWeatherPrv(thisx, play);
    aWeather_RenewWeatherLevel(this, play);
    aWeather_MoveWeatherPrv(this, play);
    aWeather_ChangeWeather(this, play);

    this->pos = *pos;

    aWeather_ChangeWeatherTime0(this);

    if (common_data.weather == 1) {
        umbrella = mPlib_check_player_open_umbrella(play);
        if (umbrella != this->umbrellaFlag) {
            aWeather_ChangeEnvSE(this, play, this->currentStatus, this->currentLevel);
        }

        this->umbrellaFlag = umbrella;
        this->currentYAngle = angle;
    }

    if (this->soundFlag == 2) {
        this->soundFlag = 0;
    }

    aWeather_EndEnvSE(thisx);
}

void aWeather_ChangingWeather() {
    Weather* this;

    if (common_data.clip.weatherClip != NULL) {
        this = common_data.clip.weatherClip->actor;
        if (this != NULL) {
            this->requestChange = FALSE;
            this->nextStatus = this->currentStatus;
            func_80A21DFC_jp(&this->actor, this->currentStatus);
        }
    }
}
