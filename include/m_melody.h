#ifndef M_MELODY_H
#define M_MELODY_H

#include "ultra64.h"

struct Npc;

#define mMld_MELODY_LEN 16

void mMld_SetDefaultMelody(void);
void mMld_TransformMelodyData_u64_2_u8(u8* dst, u64 src);
void mMld_TransformMelodyData_u8_2_u64(u64* dst, u8* src);
void mMld_GetMelody(u8* dst);
void mMld_SetSaveMelody(u8* melody);
void mMld_MakeMelody(u8 inst);
void mMld_ActorMakeThisMelody(u8* melody, struct Npc* npc);
void mMld_ActorMakeMelody(struct Npc* npc);


#endif
