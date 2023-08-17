#ifndef AC_NPC_RTC_H
#define AC_NPC_RTC_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Npc_Rtc;

typedef void (*Npc_RtcActionFunc)(struct Npc_Rtc*, struct Game_Play*);

typedef struct Npc_Rtc {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7EC];
} Npc_Rtc; // size = 0x960

#endif
