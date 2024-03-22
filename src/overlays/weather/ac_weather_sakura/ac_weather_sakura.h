#ifndef AC_WEATHER_SAKURA_H
#define AC_WEATHER_SAKURA_H

#include "ultra64.h"
#include "overlays/actors/ovl_Weather/ac_weather.h"

struct Game_Play;

extern WeatherProfile iam_weather_sakura;
extern s32 aWeatherSakura_DecideMakeSakuraCount(Actor* thisx, struct Game_Play* play);

#endif
