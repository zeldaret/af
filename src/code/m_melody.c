#include "m_melody.h"
#include "m_common_data.h"
#include "audio.h"

void mMld_SetDefaultMelody() {
    static u8 melody[] = {0x7, 0xC, 0xF, 0x7, 0x6, 0xB, 0xF, 0x9, 0xA, 0xE, 0xD, 0xE, 0x3, 0xF, 0xE, 0xE};

    mMld_SetSaveMelody(melody);
}

void mMld_TransformMelodyData_u64_2_u8(u8* dst, u64 src) {
    s32 i;

    for (i = 0; i < mMld_MELODY_LEN; i++) {
        *dst++ = (src >> (60 - i * 4)) & 0xF;
    }
}
void mMld_TransformMelodyData_u8_2_u64(u64* dst, u8* src) {
    s32 i;

    *dst = 0;

    for (i = 0; i < mMld_MELODY_LEN; i++) {
        *dst |= (u64)(*src & 0xF) << (60 - i * 4);
        src++;
    }
}

void mMld_GetMelody(u8* dst) {
    u64 melody = common_data.save.melody;

    mMld_TransformMelodyData_u64_2_u8(dst, melody);
}

void mMld_SetSaveMelody(u8* melody) { 
    mMld_TransformMelodyData_u8_2_u64(&common_data.save.melody, melody); 
}

void mMld_MakeMelody(u8 inst) {
    static u8 melody[mMld_MELODY_LEN];

    mMld_GetMelody(melody);
    sAdo_Inst(inst, melody);
}

void mMld_ActorMakeThisMelody(u8* melody, Npc* npc) {
    if (npc != NULL && npc->actor.part == ACTOR_PART_NPC) {
        if (npc->unk_930 != 0) {
            sAdo_Inst(npc->unk_930, melody);
        }
    }
}

void mMld_ActorMakeMelody(Npc* npc) {
    if (npc != NULL && npc->actor.part == ACTOR_PART_NPC) {
        if (npc->unk_930 != 0) {
            mMld_MakeMelody(npc->unk_930);
        }
    }
}
