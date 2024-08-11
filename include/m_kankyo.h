#ifndef M_KANKYO_H
#define M_KANKYO_H

#include "ultra64.h"
#include "unk.h"
#include "m_lights.h"
#include "lb_rtc.h"

struct Actor;
struct Global_light;
struct s_xyz;
struct Game_Play;

#define ENV_SAVE_GET_WEATHER_TYPE(w) (((w) & 0xF0) >> 4) 
#define ENV_SAVE_GET_WEATHER_INTENSITY(w) ((w) & 0xF)
#define ENV_SAVE_SET_WEATHER(intensity, type) ( intensity | type << 4)

#define mEnv_TERM 8
#define mEnv_FOG_NEAR_MAX 996
#define mEnv_FOG_FAR_MAX 1600

typedef enum mEnv_Weather {
    /* 0 */ mEnv_WEATHER_CLEAR,
    /* 1 */ mEnv_WEATHER_RAIN,
    /* 2 */ mEnv_WEATHER_SNOW,
    /* 3 */ mEnv_WEATHER_SAKURA,
    /* 4 */ mEnv_WEATHER_LEAVES,
    /* 5 */ mEnv_WEATHER_MAX
} mEnv_Weather;

typedef enum mEnv_WeatherIntensity {
    /* 0 */ mEnv_WEATHER_INTENSITY_NONE,
    /* 1 */ mEnv_WEATHER_INTENSITY_LIGHT,
    /* 2 */ mEnv_WEATHER_INTENSITY_NORMAL,
    /* 3 */ mEnv_WEATHER_INTENSITY_HEAVY,
    /* 4 */ mEnv_WEATHER_INTENSITY_MAX
} mEnv_WeatherIntensity;

typedef struct mEnv_WindInfo {
   /* 0x00 */ lbRTC_time_c time;
   /* 0x08 */ f32 unk8;
   /* 0x0C */ f32 windAngleS;
   /* 0x10 */ f32 unk10;
   /* 0x14 */ f32 unk14;
   /* 0x18 */ f32 windPowerF;
   /* 0x1C */ f32 unk1C;
} mEnv_WindInfo; // size = 0x20

typedef void (*NatureProc)(struct Actor*);

typedef struct BaseLight {
    /* 0x00 */ u8 ambientColor[3];
    /* 0x03 */ s8 sunDir[3];
    /* 0x06 */ u8 sunColor[3];
    /* 0x09 */ s8 moonDir[3];
    /* 0x0C */ u8 moonColor[3];
    /* 0x0F */ u8 fogColor[3];
    /* 0x12 */ s16 fogNear;
    /* 0x14 */ s16 fogFar;
    /* 0x16 */ u8 shadowColor[3];
    /* 0x19 */ u8 roomColor[3];
    /* 0x1C */ u8 sunColorWindow[3];
    /* 0x1F */ u8 moonColorWindow[3];
    /* 0x22 */ u8 bgColor[3];
} BaseLight; // size = 0x26

typedef struct AddLightInfo {
    /* 0x00 */ s16 ambientColor[3];
    /* 0x06 */ s16 diffuseColor[3];
    /* 0x0C */ s16 fogColor[3];
    /* 0x12 */ s16 fogNear;
    /* 0x14 */ s16 fogFar;
} AddLightInfo; // size = 0x16

typedef struct KankyoNature {
    /* 0x0 */ NatureProc proc;
    /* 0x4 */ void* arg;
} KankyoNature; // size = 0x8

typedef struct Kankyo {
    /* 0x00 */ Lights sunLight;
    /* 0x0E */ Lights moonLight;
    /* 0x1C */ struct Lights* unk_1C;
    /* 0x20 */ Lights pointLight; 
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ UNK_TYPE1 unk_30[0x40];
    /* 0x70 */ AddLightInfo addLightsInfo;
    /* 0x86 */ UNK_TYPE1 unk_86[0x6];
    /* 0x8C */ BaseLight baseLight; 
    /* 0xB2 */ UNK_TYPE1 unk_B2[0x6];
    /* 0xB8 */ f32 shadowPos;
    /* 0xBC */ u8 shadowAlpha;
    /* 0xBD */ u8 countdownTimer;
    /* 0xBE */ s8 unk_BE;
    /* 0xBC */ KankyoNature nature;
} Kankyo; // size = 0xC8

void mEnv_regist_nature(Kankyo* kankyo, NatureProc natureProc, void* arg);
s32 mEnv_unregist_nature(Kankyo* kankyo, NatureProc natureProc);
s32 func_80096CDC_jp(void);
s32 mEnv_GetNowRoomPointLightInfo(struct Game_Play* play, struct s_xyz* pos, u8* color, s16* power, s16* isFlame);
void mEnv_RoomTypePointLightSet(struct Game_Play* play);
void mEnv_RoomTypediffuseLightSet(struct Game_Play* play, Kankyo* kankyo);
void mEnv_RoomTypeLightSet(struct Game_Play* play, Kankyo* kankyo);
void Global_kankyo_ct(struct Game_Play* play, Kankyo* kankyo);
void mEnv_MakeShadowInfo(Kankyo* kankyo);
void mEnv_set_time(Kankyo* kankyo);
void mEnv_ChangeRGBLight(u8* dst, u8* light0, u8* light1, f32 f0);
void mEnv_ChangeDiffuseVctlSet(BaseLight* baseLight);
void mEnv_ChangeDiffuseLight(BaseLight* dst, BaseLight* light0, BaseLight* light1, f32 f0);
void mEnv_ChangeFogLight(BaseLight* dst, BaseLight* light0, BaseLight* light1, f32 f0);
void mEnv_CalcSetLight_train(BaseLight* light);
void mEnv_CalcSetLight(BaseLight* dst, BaseLight* light0, BaseLight* light1, f32 f0);
void mEnv_SetBaseLight(Kankyo* kankyo);
u8 mEnv_LimitChkRGBColor(s32 c);
void mEnv_AddAndSetRGBColor(u8* dst, u8* src0, s16* src1);
void mEnv_SetDiffuseLight(Kankyo* kankyo);
void mEnv_SetFog(Kankyo* kankyo, Global_light* gLight);
void mEnv_PermitCheckDiffuseLight(Kankyo* kankyo);
void Global_kankyo_set_room_prim(struct Game_Play* play);
void mEnv_check_countdown_start(struct Game_Play* play);
void mEnv_countdown_proc(struct Game_Play* play);
void Global_kankyo_set(struct Game_Play* play, Kankyo* kankyo, Global_light* gLight);
void mEnv_DecideWindDirect(s_xyz* dir, s16 x, s16 z);
s32 mEnv_GetWeatherChangeStep(void);
void mEnv_RandomWeather(s16* next_weather, s16* next_intensity);
s16 mEnv_GetWindAngleS(void);
f32 mEnv_GetWindPowerF(void);
void mEnv_ChangeWind(void);
void mEnv_InitWind(void);
void mEnv_WindMove(void);
void mEnv_DecideWeather_GameStart(void);
void mEnv_DecideWeather_FirstGameStart(void);
void mEnv_DecideWeather_NormalGameStart(void);
s32 mEnv_NowWeather(void);
s32 mEnv_CheckNpcRoomPointLightNiceStatus(void);
void mEnv_TaimatuPointLightWaveMoveProc(struct Game_Play* play);
void mEnv_CheckNpcLight_ToSwitchON(struct Game_Play* play);
void target_lighting_amb(struct Game_Play* play, f32 f0);
void target_lighting_dif(struct Game_Play* play, f32 f0);
void target_lighting_fog(struct Game_Play* play, f32 f0);
void mEnv_PointLightSet(struct Game_Play* play, f32 f0);
void staffroll_light_init(struct Game_Play* play);
void staffroll_light_proc_start(struct Game_Play* play);
s32 staffroll_light_proc_end(struct Game_Play* play);
void staffroll_light_dt(struct Game_Play* play);
void mEnv_GetShadowPrimColor_Light(u8* r, u8* g, u8* b, struct Game_Play* play);
u8 mEnv_GetCurrentLightSwitchStatus(void);
s32 mEnv_HereIsPlayerSelect(void);
void mEnv_MakeWindowLightAlpha(s32 enabled);
f32 mKK_windowlight_alpha_get(void);

#endif
