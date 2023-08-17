#ifndef AC_EV_ARTIST_H
#define AC_EV_ARTIST_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Ev_Artist;

typedef void (*Ev_ArtistActionFunc)(struct Ev_Artist*, struct Game_Play*);

typedef struct Ev_Artist {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D4];
} Ev_Artist; // size = 0x948

#endif
