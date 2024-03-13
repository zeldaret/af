#ifndef AC_WEATHER_H
#define AC_WEATHER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "other_types.h"

struct Game_Play;

typedef struct Weather Weather;

//these might go better on kankyo
#define ENV_SAVE_GET_WEATHER_TYPE(w) (((w) & 0xF0) >> 4) 
#define ENV_SAVE_GET_WEATHER_INTENSITY(w) ((w) & 0xF)

typedef struct WeatherPrv {
    /* 0x00 */ xyz_t pos;
    /* 0x0C */ xyz_t speed;
    /* 0x18 */ f32 currentY;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 timer;
    /* 0x22 */ s16 work[5]; 
    /* 0x2C */ u8 use;
    /* 0x2D */ u8 id;
    /* 0x2E */ u8 status;
} WeatherPrv; // size = 0x30

typedef void (*ChangingWeatherProc)();
typedef void (*ChangeWeatherProc)(Actor* thisx, s16 status, s16 level);
typedef s32 (*GetWeatherPrvvNumProc)(Actor* thisx);
typedef void (*RemoveWeatherPrvProc)(Actor* thisx, s32 id);
typedef WeatherPrv* (*GetWeatherPrvProc)(u8 status, s16 timer, xyz_t* pos, xyz_t* speed, Actor* weather, int id);
typedef s32 (*WeatherSoundEffectProc)();
typedef void (*ChangeWeatherInstanceProc)(Weather* weather, s16 status, s16 level);

typedef struct WeatherClip {
    /* 0x00 */ Weather* actor;
    /* 0x04 */ ChangingWeatherProc changingWeather;
    /* 0x08 */ ChangeWeatherProc changeWeather;
    /* 0x0C */ GetWeatherPrvvNumProc getPrvNum;
    /* 0x10 */ RemoveWeatherPrvProc removePrv;
    /* 0x14 */ GetWeatherPrvProc getPrv;
    /* 0x18 */ WeatherSoundEffectProc stopSound;
    /* 0x1C */ WeatherSoundEffectProc startSound;
    /* 0x20 */ ChangeWeatherInstanceProc changeWeatherInstance;
} WeatherClip; // size = 0x24 

typedef void (*MakeWeatherProc)(Actor*, struct Game_Play*);
typedef void (*CtWeatherProc)(WeatherPrv*, struct Game_Play*);
typedef void (*MvWeatherProc)(WeatherPrv*, struct Game_Play*);
typedef void (*StWeatherProc)(struct Game_Play*);
typedef void (*DwWeatherProc)(WeatherPrv*, struct Game_Play*);

typedef struct WeatherProfile {
    /* 0x00 */ MakeWeatherProc mk;
    /* 0x04 */ CtWeatherProc ct;
    /* 0x08 */ MvWeatherProc mv;
    /* 0x0C */ StWeatherProc st;
    /* 0x10 */ DwWeatherProc dw;
} WeatherProfile; // size = 0x14

typedef struct WeatherOvlInfo {
    /* 0x00 */ RomOffset vromStart;
    /* 0x04 */ RomOffset vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* ovlTypeEnd;
} WeatherOvlInfo; // size = 0x14

typedef struct WeatherDmaInfo {
    /* 0x00 */ RomOffset vromStart;
    /* 0x04 */ RomOffset vromEnd;
} WeatherDmaInfo;


typedef void (*WeatherActionFunc)(struct Weather*, struct Game_Play*);

struct Weather{
    /* 0x000 */ Actor actor;
    /* 0x174 */ WeatherProfile* currentProfile; 
    /* 0x178 */ s16 currentStatus;
    /* 0x17A */ s16 nextStatus;
    /* 0x17C */ s16 counter;
    /* 0x17E */ s16 currentLevel;
    /* 0x180 */ s16 currentAimLevel;
    /* 0x182 */ s16 nextLevel;
    /* 0x184 */ u8* segment;
    /* 0x188 */ xyz_t pos;
    /* 0x194 */ WeatherPrv* priv;
    /* 0x198 */ void* allocatedSize; 
    /* 0x19C */ u8 requestChange;
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ WeatherClip clip; 
    /* 0x1C4 */ s16 timer;
    /* 0x1C6 */ s16 timer2;
    /* 0x1C8 */ xyz_t windInfo;
    /* 0x1D4 */ s16 lightningTimer;
    /* 0x1D6 */ s16 lightningTimer2;
    /* 0x1D8 */ s16 currentSoundEffect;
    /* 0x1DA */ s16 umbrellaFlag;
    /* 0x1DC */ s16 currentYAngle;
    /* 0x1DE */ s16 soundFlag;
    /* 0x1E0 */ s16 startSoundEffect;
    /* 0x1E2 */ s16 stopSoundEffect;
    /* 0x1E4 */ s16 basementEvent;
};  // size = 0x1E4

#endif
