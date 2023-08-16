#ifndef AC_WEATHER_H
#define AC_WEATHER_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Weather;

typedef struct Weather {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x70];
} Weather; // size = 0x1E4

#endif
