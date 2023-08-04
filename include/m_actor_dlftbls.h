#ifndef M_ACTOR_DLFTBLS_H
#define M_ACTOR_DLFTBLS_H

#include "ultra64.h"
#include "libc/stdint.h"

struct ActorProfile;


#define DEFINE_ACTOR(_name, enumValue, _allocType) enumValue,
#define DEFINE_ACTOR_INTERNAL(_name, enumValue, _allocType) enumValue,
#define DEFINE_ACTOR_UNSET(enumValue) enumValue,

typedef enum ActorId {
    #include "tables/actor_table.h"
    /* 0xC9 */ ACTOR_ID_MAX
} ActorId;

#undef DEFINE_ACTOR
#undef DEFINE_ACTOR_INTERNAL
#undef DEFINE_ACTOR_UNSET

typedef struct ActorOverlay {
    /* 0x00 */ uintptr_t vromStart;
    /* 0x04 */ uintptr_t vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* loadedRamAddr;
    /* 0x14 */ struct ActorProfile* profile;
    /* 0x18 */ char* name;
    /* 0x1C */ u16 allocType;
    /* 0x1E */ s8 numLoaded;
} ActorOverlay; // size = 0x20


void actor_dlftbls_init(void);
void actor_dlftbls_cleanup(void);

extern ActorOverlay actor_dlftbls[];
extern ActorId actor_dlftbls_num;

#endif
