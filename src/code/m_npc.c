#include "global.h"
#include "m_npc.h"
#include "game.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_common_data.h"
#include "6B8A70.h"
#include "m_npc_schedule.h"
#include "m_npc_walk.h"
#include "m_npc_personal_id.h"
#include "6DB420.h"
#include "6F8A60.h"
#include "6DE300.h"
#include "m_time.h"
#include "libc64/malloc.h"
#include "m_malloc.h"
#include "z_std_dma.h"
#include "macros.h"
#include "6E7AD0.h"
#include "libu64/gfxprint.h"
#include "6D9D80.h"
#include "m_field_info.h"
#include "m_mail.h"
#include "6BFE60.h"
#include "6DA460.h"
#include "m_handbill.h"
#include "6B81C0.h"
#include "6E30B0.h"
#include "6C05A0.h"
#include "m_item_name.h"
#include "m_actor.h"
#include "overlays/actors/ovl_Npc/ac_npc.h"
#include "6A5B00.h"
#include "6A83A0.h"
#include "prevent_bss_reordering.h"
#include "segment_symbols.h"
#include "libc64/qrand.h"

typedef struct Struct_D_E03000 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
} Struct_D_E03000; // size = 0x6

typedef struct Struct_D_E04000 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ u8 unk_08[100][PLAYER_NAME_LEN];
} Struct_D_E04000;

typedef struct Struct_D_8010B510_jp {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} Struct_D_8010B510_jp; // size = 0xC

extern u8 D_8010AF58_jp[];

Struct_D_8010B510_jp D_8010B510_jp[] = {
    { 0xD008, 0x0000, 0x00000205, 0x00000002 }, { 0xD01E, 0x0000, 0x00000205, 0x00000002 },
    { 0xD03A, 0x0000, 0x00000205, 0x00000002 }, { 0xD03B, 0x0000, 0x00000205, 0x00000002 },
    { 0xD03C, 0x0000, 0x00000205, 0x00000002 }, { 0xD009, 0x0000, 0x00000205, 0x00000002 },
    { 0xD00A, 0x0000, 0x00000205, 0x00000002 }, { 0xD00B, 0x0000, 0x00000205, 0x00000002 },
    { 0xD014, 0x0000, 0x00000205, 0x00000002 }, { 0xD019, 0x0000, 0x00000205, 0x00000002 },
    { 0xD015, 0x0000, 0x00000205, 0x00000002 }, { 0xD01A, 0x0000, 0x00000205, 0x00000002 },
    { 0xD016, 0x0000, 0x00000205, 0x00000002 }, { 0xD01B, 0x0000, 0x00000205, 0x00000002 },
    { 0xD017, 0x0000, 0x00000205, 0x00000002 }, { 0xD01C, 0x0000, 0x00000205, 0x00000002 },
    { 0xD001, 0x0000, 0x00000206, 0x00000002 }, { 0xD013, 0x0000, 0x00000206, 0x00000002 },
    { 0xD02C, 0x0000, 0x00000206, 0x00000002 }, { 0xD039, 0x0000, 0x00000206, 0x00000002 },
    { 0xD00C, 0x0001, 0x00000207, 0x00000002 }, { 0xD03D, 0x0001, 0x00000207, 0x00000002 },
    { 0xD006, 0x0000, 0x00000208, 0x00000002 }, { 0xD000, 0x0000, 0x00000209, 0x00000003 },
    { 0xD00F, 0x0000, 0x0000020A, 0x00000002 }, { 0xD002, 0x0000, 0x0000020B, 0x00000002 },
    { 0xD007, 0x0001, 0x0000020C, 0x00000008 }, { 0xD003, 0x0001, 0x0000020D, 0x00000004 },
    { 0xD012, 0x0001, 0x0000020E, 0x00000004 }, { 0xD011, 0x0000, 0x0000020F, 0x00000003 },
    { 0xD00D, 0x0000, 0x00000210, 0x00000002 }, { 0xD010, 0x0000, 0x00000210, 0x00000003 },
    { 0xD04E, 0x0000, 0x00000210, 0x00000002 }, { 0xD00E, 0x0000, 0x00000211, 0x00000002 },
    { 0xD025, 0x0000, 0x00000212, 0x00000003 }, { 0xA004, 0x0002, 0x00000213, 0x00000002 },
    { 0xA005, 0x0002, 0x00000213, 0x00000002 }, { 0xA006, 0x0002, 0x00000213, 0x00000002 },
    { 0xA007, 0x0002, 0x00000213, 0x00000002 }, { 0xD018, 0x0002, 0x00000214, 0x00000002 },
    { 0xD05D, 0x0002, 0x00000214, 0x00000002 }, { 0xD066, 0x0002, 0x00000214, 0x00000002 },
    { 0xD004, 0x0000, 0x00000215, 0x00000002 }, { 0xD005, 0x0000, 0x00000215, 0x00000002 },
    { 0xD01D, 0x0000, 0x00000216, 0x00000002 }, { 0xD026, 0x0000, 0x00000217, 0x00000002 },
    { 0xD037, 0x0000, 0x00000218, 0x00000002 }, { 0xD03E, 0x0000, 0x000004E0, 0x00000002 },
    { 0xD065, 0x0000, 0x000004E0, 0x00000002 }, { 0xD068, 0x0000, 0x000004E0, 0x00000002 },
    { 0xD069, 0x0000, 0x000004E0, 0x00000002 }, { 0xD06B, 0x0000, 0x000004E0, 0x00000002 },
    { 0xD064, 0x0000, 0x000004E1, 0x00000002 }, { 0x800D, 0x0000, 0x000004E2, 0x00000002 },
    { 0x800E, 0x0000, 0x000004E2, 0x00000002 }, { 0xA008, 0x0000, 0x000004E2, 0x00000002 },
    { 0xA009, 0x0000, 0x000004E2, 0x00000002 }, { 0xA00A, 0x0000, 0x000004E2, 0x00000002 },
    { 0xA00B, 0x0000, 0x000004E2, 0x00000002 }, { 0xA00C, 0x0000, 0x000004E2, 0x00000002 },
    { 0xA00D, 0x0000, 0x000004E2, 0x00000002 }, { 0xA00E, 0x0000, 0x000004E2, 0x00000002 },
    { 0xA00F, 0x0000, 0x000004E2, 0x00000002 }, { 0xA010, 0x0000, 0x000004E2, 0x00000002 },
};

u8 l_no_name_npc_name[PLAYER_NAME_LEN] = { 0xD4, 0x8E, 0xA6, 0x90, 0x85, 0x42 };

u8 l_no_ending_npc_ending[] = { 0xD3, 0xAF, 0x9D, 0x20 };

s32 category_table1[] = { 0, 2 };

s32 base_str_no[] = { 0x314, 0x334, 0x2F4, 0x219, 0x1E5, 0x354, 0x374, 0x394, 0x3D4, 0x3F4, 0x3B4 };

s32 this_start_no[] = {
    0x00000020, 0x00000040, 0x00000000, 0x00000060, 0x00000080, 0x000000A0,
};
s32 other_start_no[] = {
    0x000000E0, 0x00000100, 0x000000C0, 0x00000120, 0x00000140, 0x00000160,
};

s32* start_no_table[] = { this_start_no, other_start_no };

s32 mail_no[] = { 0xC5, 0xD8 };

typedef void (*Funcs_D_8010B890_jp)(Mail*, Private*, AnmPersonalId*, AnmRemail*, u8);
Funcs_D_8010B890_jp get_remail[] = {
    func_800A8F30_jp,
    func_800A8DB4_jp,
};

s32 D_8010B898_jp[] = { 5, 2, 0 };
s32 category_table2[] = { 0, 0, 2 };

s32 D_8010B8B0_jp[] = { 1, 0 };

u8 D_8010B8B8_jp[] = {
    0x00, 0x00, 0x02, 0x02, 0xFF,
};

typedef struct Struct_D_8010B8C0_jp {
    /* 0x00 */ s32 unk_00;
    /* 0x00 */ s32 unk_04;
} Struct_D_8010B8C0_jp; // size = 0x8

Struct_D_8010B8C0_jp ut_d[] = {
    { 0x00000000, 0x00000000 }, { 0xFFFFFFFF, 0x00000001 }, { 0x00000000, 0x00000001 },
    { 0x00000001, 0x00000001 }, { 0xFFFFFFFF, 0x00000000 }, { 0x00000001, 0x00000000 },
    { 0xFFFFFFFF, 0xFFFFFFFF }, { 0x00000000, 0xFFFFFFFF }, { 0x00000001, 0xFFFFFFFF },
};

u16 set_fg[] = { 0, 0xA012, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };

s32 spec_table[] = { 4, 4, 2, 2, 3, 4 };

s32 npc_grow_table[] = { 0x28, 0x32, 0x3C, 0x46, 0x50, 0x5A, 0x64 };

typedef struct Struct_D_8010B950_jp {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
} Struct_D_8010B950_jp; // size = 0x4

Struct_D_8010B950_jp l_npc_temper[] = {
    { 0x0FA0, 0x0C, 0x0F }, { 0x0BB8, 0x0A, 0x0D }, { 0x0FA0, 0x0C, 0x0F },
    { 0x0FA0, 0x0A, 0x0D }, { 0x1388, 0x09, 0x0C }, { 0x1388, 0x09, 0x0C },
};

s32 D_8010B968_jp = -1;

s32 B_80142C00_jp[60];
u8 B_80142CF0_jp[HANDBILL_HEADER_LEN];

typedef struct Struct_B_80142D08_jp {
    /* 0x00 */ char unk00[0x1];
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
} Struct_B_80142D08_jp; // size = 0x5

Struct_B_80142D08_jp B_80142D08_jp[60];
u8 B_80142E38_jp[HANDBILL_FOOTER_LEN];
u8 B_80142E58_jp[0x1B];
UNK_TYPE1 PAD_80142E73_jp[3];
Struct_D_E03000 B_80142E78_jp;
u8 B_80142E80_jp[HANDBILL_HEADER_LEN];
u8 B_80142E98_jp[HANDBILL_FOOTER_LEN];
u16 B_80142EB8_jp[16];

typedef struct Struct_B_80142ED8_jp {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
} Struct_B_80142ED8_jp; // size = 0x8

Struct_B_80142ED8_jp B_80142ED8_jp[ANIMAL_NUM_MAX];

u8 B_80142F50_jp[PLAYER_NAME_LEN];
u8 B_80142F58_jp[PLAYER_NAME_LEN];
u8 B_80142F60_jp[PLAYER_NAME_LEN];
u8 B_80142F68_jp[PLAYER_NAME_LEN];

typedef struct Struct_B_80142F70_jp {
    /* 0x00 */ AnmPersonalId id;
    /* 0x0C */ u8 unk_0C;
} Struct_B_80142F70_jp; // size = 0x10

Struct_B_80142F70_jp B_80142F70_jp;
Mail B_80142F80_jp;
s32 B_80143028_jp[216];
Animal B_80143388_jp;

void func_800A6810_jp(s32* arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 j;

    for (i = 0; i < arg1; i++) {
        arg0[i] = i;
    }

    while (arg2--) {
        s32 temp;

        i = RANDOM(arg1);
        j = RANDOM(arg1);
        temp = arg0[i];
        arg0[i] = arg0[j];
        arg0[j] = temp;
    }
}

void func_800A6920_jp(u8* catchphrase, s32 len) {
    mem_clear(catchphrase, len, 0x20);
}

void func_800A6940_jp(u8* npcMax) {
    if (*npcMax < ANIMAL_NUM_MAX) {
        (*npcMax)++;
    }
}

void func_800A695C_jp(u8* arg0) {
    if (*arg0 >= 6) {
        (*arg0)--;
    }
}

void mNpc_ClearAnimalPersonalID(AnmPersonalId* anmId) {
    anmId->npcId = 0;
    anmId->nameId = 0xFF;
    anmId->landId = 0xFFFF;
    anmId->looks = 6;
    mNPS_reset_schedule_area(anmId);
    func_80094EE0_jp(anmId->landName);
}

s32 mNpc_CheckFreeAnimalPersonalID(AnmPersonalId* anmId) {
    s32 res = FALSE;

    if (((anmId->npcId == 0) && (anmId->nameId == 0xFF)) || (ACTOR_FGNAME_GET_F000(anmId->npcId) != FGNAME_F000_E)) {
        res = TRUE;
    }
    return res;
}

void mNpc_CopyAnimalPersonalID(AnmPersonalId* dst, AnmPersonalId* src) {
    if (src != NULL) {
        if (ACTOR_FGNAME_GET_F000(src->npcId) == FGNAME_F000_E) {
            dst->npcId = src->npcId;
            dst->nameId = src->nameId;
            dst->landId = src->landId;
            dst->looks = src->looks;
            mLd_CopyLandName(dst->landName, src->landName);
        }
    }
}

s32 mNpc_CheckCmpAnimalPersonalID(AnmPersonalId* id0, AnmPersonalId* id1) {
    s32 res = FALSE;

    if ((id0 != NULL) && (id1 != NULL) && (id0->npcId == id1->npcId) && (id0->nameId == id1->nameId) &&
        (id0->landId == id1->landId)) {
        if (func_80094E38_jp(id0->landName, id1->landName) == TRUE) {
            res = TRUE;
        }
    }
    return res;
}

s32 func_800A6AF0_jp(void) {
    Animal* animal = gCommonData.save.animals;
    s32 res = 0;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == 0) {
            res++;
        }
        animal++;
    }
    return res;
}

s32 func_800A6B58_jp(Animal* animal) {
    s32 res = (animal->unk_522 >> 0xD) & 7;
    return res;
}

s32 func_800A6B6C_jp(Animal* animal) {
    s32 res = animal->unk_522 & 0x1FFF;
    return res;
}

void func_800A6B7C_jp(Animal* animal) {
    if ((animal->unk_522 & 0x1FFF) < 0x1FFF) {
        animal->unk_522++;
    }
}

void func_800A6B9C_jp(Animal* animal, u16 arg1) {
    animal->unk_522 = ((((animal->unk_522 >> 0xD) & 7) >> 0xD) | arg1) << 0xD;
}

void func_800A6BC8_jp(Animal* animal, PersonalId* pid) {
    if ((pid != NULL) && (func_800B7914_jp(pid) == 0)) {
        if (func_800B77C4_jp(animal->parentName) == 1) {
            mPr_CopyPlayerName(animal->parentName, pid->playerName);
        }
    }
}

void func_800A6C1C_jp(void) {
    Animal* animal = gCommonData.save.animals;
    Private* priv = gCommonData.nowPrivate;
    s32 i;

    if (priv != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            func_800A6BC8_jp(animal, &priv->playerId);
            animal++;
        }
    }
}

void func_800A6C84_jp(AnmPLMail* letter) {
    letter->font = 0xFF;
    letter->paperType = 0;
    letter->present = 0;
    mem_clear(letter->body, MAIL_BODY_LEN, 0x20);
    letter->date.year = mTM_rtcTime_ymd_clear_code.year;
    letter->date.month = mTM_rtcTime_ymd_clear_code.month;
    letter->date.day = mTM_rtcTime_ymd_clear_code.day;
}

void func_800A6CE4_jp(AnmPLMail* dst, AnmPLMail* src) {
    mem_copy((void*)dst, (void*)src, sizeof(AnmPLMail));
}

void func_800A6D04_jp(AnmMemory* memory, s32 count) {
    while (count) {
        if (memory != NULL) {
            func_800B795C_jp(&memory->memoryPlayerId);
            lbRTC_TimeCopy(&memory->lastSpeakTime, &mTM_rtcTime_clear_code);
            func_80094EE0_jp(memory->unk_18.land.name);
            memory->unk_18.land.id = 0;
            memory->savedTownTune = 0;
            memory->info.friendship = 0;
            memory->info.exists = FALSE;
            memory->info.passwordLetter = FALSE;
            memory->info.sendReply = FALSE;
            func_800A6C84_jp(&memory->letter);
        }
        memory++;
        count--;
    }
}

void func_800A6DB0_jp(AnmMemory* dst, AnmMemory* src) {
    mem_copy((void*)dst, (void*)src, sizeof(AnmMemory));
}

void func_800A6DD0_jp(AnmMemory* memory, s32 arg1) {
    s32 temp_v0 = memory->info.friendship + arg1;

    if (memory != NULL) {
        if (temp_v0 >= 0x80) {
            memory->info.friendship = 0x7F;
        } else if (temp_v0 < 0) {
            memory->info.friendship = 0;
        } else {
            memory->info.friendship = temp_v0;
        }
    }
}

s32 func_800A6E0C_jp(PersonalId* pid) {
    s32 res = FALSE;

    if (func_800B7914_jp(pid) == TRUE) {
        res = TRUE;
    }
    return res;
}

void mNpc_RenewalAnimalMemory(void) {
    Animal* animal = gCommonData.save.animals;
    Private* priv;
    AnmMemory* memory;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        memory = animal->memories;
        for (j = 0; j < ANIMAL_MEMORY_NUM; j++) {
            if (func_800A6E0C_jp(&memory->memoryPlayerId) == FALSE) {
                if (func_800951E4_jp(memory->memoryPlayerId.landName, memory->memoryPlayerId.landId) == TRUE) {
                    priv = gCommonData.save.private;
                    for (k = 0; k < PLAYER_NUM; k++) {
                        if ((func_800B7914_jp(&priv->playerId) == FALSE) &&
                            (mPr_CheckCmpPersonalID(&priv->playerId, &memory->memoryPlayerId) == TRUE)) {
                            break;
                        }
                        priv++;
                    }
                    if (k == PLAYER_NUM) {
                        func_800A6D04_jp(memory, 1);
                    }
                }
            }
            memory++;
        }
        animal++;
    }
}

s32 func_800A6F48_jp(AnmMemory* memory, s32 count) {
    LBRTCTime sp48;
    s32 res;
    s32 i;

    lbRTC_TimeCopy(&sp48, &mTM_rtcTime_clear_code);
    res = 0;

    for (i = 0; i < count; i++) {
        if (func_800D52C0_jp(&sp48, &memory->lastSpeakTime) == -1) {
            res = i;
            lbRTC_TimeCopy(&sp48, &memory->lastSpeakTime);
        }
        memory++;
    }

    return res;
}

s32 func_800A6FF4_jp(AnmMemory* memory, s32 count) {
    s32 res = -1;
    s32 i;

    for (i = 0; i < count; i++) {
        if (func_800A6E0C_jp(&memory->memoryPlayerId) == TRUE) {
            res = i;
            break;
        }
        memory++;
    }

    return res;
}

s32 func_800A706C_jp(AnmMemory* memory, s32 count) {
    AnmMemory* foundMemory = NULL;
    s32 foundIdx = func_800A6FF4_jp(memory, count);
    s32 i;

    if (foundIdx == -1) {
        for (i = 0; i < count; i++) {
            if (func_800951E4_jp(memory->memoryPlayerId.landName, memory->memoryPlayerId.landId) == 0) {
                if (foundMemory != NULL) {
                    if (foundMemory->info.exists == memory->info.exists) {
                        if (memory->info.friendship < foundMemory->info.friendship) {
                            foundMemory = memory;
                            foundIdx = i;
                        } else if ((foundMemory->info.friendship == memory->info.friendship) &&
                                   (func_800D52C0_jp(&foundMemory->lastSpeakTime, &memory->lastSpeakTime) == -1)) {
                            foundMemory = memory;
                            foundIdx = i;
                        }
                    } else if (memory->info.exists == FALSE) {
                        foundMemory = memory;
                        foundIdx = i;
                    }
                } else {
                    foundMemory = memory;
                    foundIdx = i;
                }
            }
            memory++;
        }
    } else {
        foundMemory = &memory[foundIdx];
    }
    func_800A6D04_jp(foundMemory, 1);
    return foundIdx;
}

void func_800A71AC_jp(Private* private, AnmMemory* memory) {
    if (memory != NULL) {
        func_800A6D04_jp(memory, 1);
        func_800B79E0_jp(&memory->memoryPlayerId, &private->playerId);
        memory->info.friendship = 1;
    }
}

void func_800A71F8_jp(Private* private, AnmMemory* memory) {
    if (memory != NULL) {
        func_800A71AC_jp(private, memory);
        lbRTC_TimeCopy(&memory->lastSpeakTime, &gCommonData.time.rtcTime);
    }
}

s32 func_800A7238_jp(PersonalId* pid, AnmMemory* memory, s32 count) {
    s32 foundIdx = -1;
    s32 i;

    for (i = 0; i < count; i++) {
        if (mPr_CheckCmpPersonalID(&memory->memoryPlayerId, pid) == TRUE) {
            foundIdx = i;
            break;
        }
        memory++;
    }

    return foundIdx;
}

void func_800A72C0_jp(Animal* animal) {
    Private* priv;
    AnmMemory* memory = NULL;
    s32 idx;

    if ((gCommonData.nowPrivate != NULL) && (animal != NULL)) {
        priv = gCommonData.nowPrivate;
        idx = func_800A7238_jp(&priv->playerId, animal->memories, ANIMAL_MEMORY_NUM);
        if (idx != -1) {
            memory = &animal->memories[idx];
        } else {
            idx = func_800A706C_jp(animal->memories, ANIMAL_MEMORY_NUM);
            if (idx != -1) {
                memory = &animal->memories[idx];
                func_800A71F8_jp(priv, memory);
            }
        }

        if (memory != NULL) {
            lbRTC_TimeCopy(&memory->lastSpeakTime, &gCommonData.time.rtcTime);
            mLd_CopyLandName(memory->unk_18.land.name, gCommonData.save.landInfo.name);
            memory->unk_18.land.id = gCommonData.save.landInfo.landId;
            memory->savedTownTune = gCommonData.save.unk_0F428;
        }
    }
}

void func_800A73D8_jp(AnmPersonalId* anmId) {
    Private* priv = gCommonData.nowPrivate;
    Animal* animal;
    s32 idx;

    if (priv != NULL) {
        idx = func_800A7D08_jp(anmId);
        if (idx != -1) {
            animal = &gCommonData.save.animals[idx];
            idx = func_800A7238_jp(&priv->playerId, animal->memories, ANIMAL_MEMORY_NUM);
            if (idx == -1) {
                idx = func_800A706C_jp(animal->memories, ANIMAL_MEMORY_NUM);
                if (idx != -1) {
                    func_800A71AC_jp(priv, &animal->memories[idx]);
                }
            }
        }
    }
}

s32 func_800A74A0_jp(AnmMemory* memory, s32 count) {
    s32 i;
    s8 maxFriendship = 0;
    s32 idx = -1;

    for (i = 0; i < count; i++) {
        if (func_800A6E0C_jp(&memory->memoryPlayerId) == 0) {
            if (memory->info.friendship >= maxFriendship) {
                maxFriendship = memory->info.friendship;
                idx = i;
            }
        }
        memory++;
    }

    return idx;
}

s32 func_800A7530_jp(AnmMemory** outMemory, AnmMemory* memory, s8* arg2) {
    s32 res = FALSE;
    AnmMemory* outMem;

    if (*arg2 < memory->info.friendship) {
        *arg2 = memory->info.friendship;
        *outMemory = memory;
        res = TRUE;
    } else if (memory->info.friendship == *arg2) {
        outMem = *outMemory;
        if (outMem != NULL) {
            if (outMem->info.exists == memory->info.exists) {
                if (func_800D52C0_jp(&outMem->lastSpeakTime, &memory->lastSpeakTime) == -1) {
                    *outMemory = memory;
                    res = TRUE;
                }
            } else if (memory->info.exists == TRUE) {
                *outMemory = memory;
                res = TRUE;
            }
        } else {
            *outMemory = memory;
            res = TRUE;
        }
    }
    return res;
}

s32 func_800A75FC_jp(AnmMemory* memory, s32 count) {
    AnmMemory* sp4C = memory;
    AnmMemory* sp48 = 0;
    s8 sp47 = 0;
    s32 foundIdx = -1;
    s32 i;

    for (i = 0; i < count; i++) {
        if ((func_800A6E0C_jp(&memory->memoryPlayerId) == FALSE) && (func_800A7530_jp(&sp48, memory, &sp47) == TRUE)) {
            foundIdx = i;
        }
        memory++;
    }

    if ((foundIdx != -1) && (sp4C[foundIdx].info.friendship < 0x50)) {
        foundIdx = -1;
    }
    return foundIdx;
}

s32 func_800A76E4_jp(AnmMemory* memory, s32 count, s32 arg2) {
    AnmMemory* sp54 = NULL;
    s8 sp53 = 0;
    s32 privIdx;
    s32 foundIdx = -1;
    s32 i;

    for (i = 0; i < count; i++) {
        if (func_800A6E0C_jp(&memory->memoryPlayerId) == FALSE) {
            privIdx = func_800B7FD4_jp(memory);
            if ((privIdx != -1) && (arg2 == gCommonData.save.private[privIdx].gender) &&
                (func_800A7530_jp(&sp54, memory, &sp53) == TRUE)) {
                foundIdx = i;
            }
        }
        memory++;
    }

    return foundIdx;
}

s32 func_800A77F0_jp(AnmMemory* memory, s32 count) {
    s32 num = 0;
    s32 i;

    for (i = 0; i < count; i++) {
        if (func_800A6E0C_jp(&memory->memoryPlayerId) == FALSE) {
            num++;
        }
        memory++;
    }

    return num;
}

s32 func_800A7858_jp(AnmMemory* memory, s32 count) {
    s32 num = 0;
    s32 i;

    for (i = 0; i < count; i++) {
        if ((func_800A6E0C_jp(&memory->memoryPlayerId) == FALSE) && (memory->info.exists == TRUE)) {
            num++;
        }
        memory++;
    }

    return num;
}

s32 func_800A78DC_jp(AnmMemory* memory, s32 count) {
    AnmMemory* memory2;
    u8 var_s4 = 0xFF;
    s32 res = 0;
    s32 i;
    s32 j;

    for (i = 0; i < count; i++) {
        if (func_800A6E0C_jp(&memory->memoryPlayerId) == FALSE) {
            if (((var_s4 >> i) & 1) == 1) {
                j = i + 1;
                memory2 = memory + 1;
                for (j = i + 1; j < count; j++) {
                    if ((((var_s4 >> j) & 1) == 1) &&
                        (func_80094E90_jp(memory->unk_18.land.name, memory->unk_18.land.id, memory2->unk_18.land.name,
                                          memory2->unk_18.land.id) == TRUE)) {
                        var_s4 &= ~(1 << j);
                    }
                    memory2++;
                }
            }
            res++;
        } else {
            var_s4 &= ~(1 << i);
        }
        memory++;
    }

    return res;
}

void mNpc_ClearAnimalInfo(Animal* animal) {
    AnmHome* homeInfo = &animal->homeInfo;

    bzero(animal, sizeof(Animal));
    mNpc_ClearAnimalPersonalID(&animal->id);
    func_800A6D04_jp(animal->memories, ANIMAL_MEMORY_NUM);
    animal->unk_520 = 0;

    homeInfo->typeUnused = 0;
    homeInfo->blockX = 0xFF;
    homeInfo->blockZ = 0xFF;
    homeInfo->utX = 0xFF;
    homeInfo->utZ = 0xFF;

    func_800A6920_jp(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    func_800BA778_jp(&animal->contestQuest);
    func_80094EE0_jp(animal->previousLandName);
    animal->unk_51C = 0;
    animal->unk_522 = 0;
    animal->unk_524 = 1;
    func_800B7780_jp(animal->parentName);
}

void mNpc_ClearAnyAnimalInfo(Animal* animals, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        mNpc_ClearAnimalInfo(animals);
        animals++;
    }
}

s32 mNpc_CheckFreeAnimalInfo(Animal* animal) {
    s32 res = FALSE;

    if ((animal->homeInfo.blockX == 0xFF) && (animal->homeInfo.blockZ == 0xFF) &&
        (ACTOR_FGNAME_GET_F000(animal->id.npcId) != FGNAME_F000_E)) {
        res = TRUE;
    }
    return res;
}

s32 mNpc_GetFreeAnimalInfo(Animal* animal, s32 count) {
    s32 res = -1;
    s32 i;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == TRUE) {
            res = i;
            break;
        }
        animal++;
    }

    return res;
}

s32 mNpc_UseFreeAnimalInfo(Animal* animal, s32 count) {
    s32 idx = mNpc_GetFreeAnimalInfo(animal, count);

    if (idx != -1) {
        mNpc_ClearAnimalInfo(&animal[idx]);
    }
    return idx;
}

void mNpc_CopyAnimalInfo(Animal* dst, Animal* src) {
    mem_copy((void*)dst, (void*)src, sizeof(Animal));
}

s32 mNpc_SearchAnimalinfo(Animal* animal, u16 npcName, s32 count) {
    s32 idx;

    animal = &animal[count - 1];
    idx = count - 1;

    while (idx >= 0) {
        if (animal->id.npcId == npcName) {
            return idx;
        }
        idx--;
        animal--;
    }

    return -1;
}

Animal* func_800A7C94_jp(u16 npcName) {
    UNUSED s32 pad;
    Animal* sp18 = NULL;
    s32 temp_v0 = mNpc_SearchAnimalinfo(gCommonData.save.animals, npcName, ANIMAL_NUM_MAX);

    if (temp_v0 != -1) {
        sp18 = &gCommonData.save.animals[temp_v0];
    }
    return sp18;
}

s32 func_800A7D08_jp(AnmPersonalId* anmId) {
    Animal* animal = gCommonData.save.animals;
    s32 res = -1;
    s32 i;

    if (anmId != NULL) {
        if (mNpc_CheckFreeAnimalPersonalID(anmId) == FALSE) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (mNpc_CheckCmpAnimalPersonalID(anmId, &animal->id) == TRUE) {
                    res = i;
                    break;
                }
                animal++;
            }
        }
    }
    return res;
}

AnmPersonalId* func_800A7DA0_jp(AnmPersonalId* ids, s32 numIds, s32 arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad;
    AnmPersonalId* sp68;
    u8 sp67;
    UNUSED s32 pad1;
    s32 sp5C;
    u16 sp5A;
    s32 j;
    s32 i;
    UNUSED s32 pad2[2];
    s32 sp44;
    Animal* var_s4 = gCommonData.save.animals;
    s32 var_fp;
    s32 var_s2;

    sp68 = NULL;
    var_s2 = 0;
    sp5C = numIds;
    sp67 = gCommonData.save.nowNpcMax;
    sp5A = 0xFFFF;

    if ((arg0 == 0xFF) || (arg1 == 0xFF)) {
        arg2 = 0;
    }

    if ((ids == NULL) && (numIds != 0)) {
        numIds = 0;
    }

    for (i = 0; i < numIds; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&ids[i]) == TRUE) {
            sp5C--;
            sp5A &= ~(1 << i);
        }
    }

    if (arg2 == 1) {
        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            if (arg0 == var_s4->homeInfo.blockX) {
                if (arg1 == var_s4->homeInfo.blockZ) {
                    var_s2++;

                    for (i = 0; i < numIds; i++) {
                        if ((((sp5A >> i) & 1) == TRUE) &&
                            (mNpc_CheckCmpAnimalPersonalID(&var_s4->id, &ids[i]) == TRUE)) {
                            sp5C--;
                            sp5A &= ~(1 << i);
                            break;
                        }
                    }
                }
            }
            var_s4++;
        }
    }

    if (((sp5C + var_s2) < sp67) && (numIds < ANIMAL_NUM_MAX)) {
        var_s4 = gCommonData.save.animals;
        var_fp = fqrand() * ((sp67 - sp5C) - var_s2);

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            var_s2 = 0;
            sp44 = 1;

            if (mNpc_CheckFreeAnimalPersonalID(&var_s4->id) == 0) {
                for (i = 0; i < numIds; i++) {
                    if ((((sp5A >> i) & 1) == 1) && (mNpc_CheckCmpAnimalPersonalID(&var_s4->id, &ids[i]) == FALSE)) {
                        var_s2++;
                    }
                    if (var_s2) {}
                }

                if (var_s2 != sp5C) {
                    sp44 = 0;
                } else if ((arg2 == 1) && (arg0 == var_s4->homeInfo.blockX) && (arg1 == var_s4->homeInfo.blockZ)) {
                    if (var_fp > 0) {
                        var_fp--;
                    }
                    sp44 = 0;
                }

                if (sp44 == 1) {
                    if (var_fp == 0) {
                        sp68 = &var_s4->id;
                        break;
                    }
                    var_fp--;
                }
            }
            var_s4++;
        }
        j = 0;
    }

    return sp68;
}

AnmPersonalId* mNpc_GetOtherAnimalPersonalID(AnmPersonalId* ids, s32 numIds) {
    return func_800A7DA0_jp(ids, numIds, 0, 0, 0);
}

void func_800A80D8_jp(Animal* animal, s32 count) {
    LandInfo* landInfo = &gCommonData.save.landInfo;

    while (count) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            animal->id.landId = landInfo->landId;
            mLd_CopyLandName(animal->id.landName, landInfo->name);
        }
        count--;
        animal++;
    }
}

s32 func_800A8148_jp(u8 looks) {
    Animal* animal = gCommonData.save.animals;
    s32 i;
    s32 res = 0;

    if (looks < 6) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (looks == animal->id.looks) {
                res++;
            }
            animal++;
        }
    }
    return res;
}

s32 func_800A820C_jp(s32 arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad;
    s32 sp28;
    s32 sp24;
    s32 sp20 = FALSE;

    if ((arg0 >= 0) && (arg0 < ANIMAL_NUM_MAX)) {
        if ((mFI_Wpos2BlockNum(&sp28, &sp24, gCommonData.npcList[arg0].position) == TRUE) && (sp28 == arg1) &&
            (sp24 == arg2)) {
            sp20 = TRUE;
        }
    }
    return sp20;
}

void func_800A82C8_jp(AnmPLMail* letter, Mail* mail) {
    mem_copy(letter->body, mail->content.body, MAIL_BODY_LEN);
    mem_copy(letter->header, mail->content.header, MAIL_HEADER_LEN);
    mem_copy(letter->footer, mail->content.footer, MAIL_FOOTER_LEN);
    letter->headerBackStart = mail->content.headerBackStart;
    letter->font = mail->content.font;
    letter->present = mail->present;
    letter->paperType = mail->content.paperType;
}

void func_800A8344_jp(Mail* mail, AnmPLMail* letter, PersonalId* pid, AnmPersonalId* anmId) {
    mem_copy(mail->content.body, letter->body, MAIL_BODY_LEN);
    mem_copy(mail->content.header, letter->header, MAIL_HEADER_LEN);
    mem_copy(mail->content.footer, letter->footer, MAIL_FOOTER_LEN);

    mail->content.headerBackStart = letter->headerBackStart;
    mail->content.font = letter->font;
    mail->present = letter->present;
    mail->content.paperType = letter->paperType;

    if (pid != NULL) {
        func_800B79E0_jp(&mail->header.sender.personalId, pid);
        mail->header.sender.type = 0;
    }

    if (anmId != NULL) {
        mMl_set_mail_name_npcinfo(&mail->header.recipient, anmId);
    }
}

s32 func_800A83F0_jp(u8 c) {
    if ((c == 0x21) || (c == 0x22) || (c == 0x5F) || (c == 0x90) || (c == 0x5C) || ((c >= 0x25) && (c <= 0x40)) ||
        ((c >= 0x7F) && (c <= 0x85))) {
        return TRUE;
    }
    return FALSE;
}

s32 func_800A845C_jp(s32* arg0, u8* body) {
    UNUSED s32 pad[2];
    s32 sp3C = 0;
    u8 var_s5 = 0x20;
    s32 var_s2 = 1;
    s32 var_s6 = 0;
    s32 i;

    *arg0 = 0;

    for (i = 0; i < MAIL_BODY_LEN; i++) {
        if (*body != 0x20) {
            var_s2++;
            if (var_s5 == *body) {
                if (var_s2 >= 3) {
                    if (func_800A83F0_jp(*body) == TRUE) {
                        if (var_s2 >= 8) {
                            sp3C = 1;
                            break;
                        }
                    } else {
                        sp3C = 1;
                        break;
                    }
                }
            } else {
                var_s2 = 0;
                var_s5 = *body;
            }
            (*arg0)++;
        }
        body++;
        var_s6++;
    }

    for (i = var_s6; i < MAIL_BODY_LEN; i++) {
        if (*body != 0x20) {
            (*arg0)++;
        }
        body++;
    }

    return sp3C;
}

u8 func_800A8614_jp(s32* arg0, u8* body) {
    s32 sp24;
    s32 sp20;
    s32 temp_v0;
    u8 sp1B = 2;

    sp24 = func_8009C900_jp(&sp20, body, 0);
    temp_v0 = func_800A845C_jp(arg0, body);

    if (sp20 < 3) {
        if (*arg0 < 5) {
            sp1B = 0;
        } else if (temp_v0 == 1) {
            sp1B = 0;
        }
    } else if (sp24 >= 30) {
        sp1B = 1;
    } else if (temp_v0 == 1) {
        sp1B = 0;
    }
    return sp1B;
}

u8 func_800A86C4_jp(u8* body) {
    s32 sp1C;

    return func_800A8614_jp(&sp1C, body);
}

u8 func_800A86E8_jp(AnmMemory* memory, u8* body) {
    u8 temp_v0;

    memory->letter.date.year = gCommonData.time.rtcTime.year;
    memory->letter.date.month = gCommonData.time.rtcTime.month;
    memory->letter.date.day = gCommonData.time.rtcTime.day;

    temp_v0 = func_800A86C4_jp(body);
    if (temp_v0 < 2) {
        memory->info.passwordLetter = temp_v0;
        memory->info.sendReply = 1;
    }
    return temp_v0;
}

s32 func_800A8764_jp(Animal* animal, u8* body) {
    AnmRemail* remail;
    u8 sp1B = func_800A86C4_jp(body);

    if (sp1B < 2) {
        remail = &gCommonData.nowPrivate->remail;

        remail->date.year = gCommonData.time.rtcTime.year;
        remail->date.month = gCommonData.time.rtcTime.month;
        remail->date.day = gCommonData.time.rtcTime.day;

        remail->flags.passwordLetter = sp1B;
        remail->flags.looks = animal->id.looks;

        mNpc_GetNpcWorldNameAnm(remail->name, &animal->id);
        mLd_CopyLandName(remail->landName, func_800950D8_jp()->name);
    }
    return sp1B;
}

s32 func_800A8814_jp(Animal* animal, AnmMemory* memory, u8* body) {
    s32 res;

    if (mLd_PlayerManKindCheck() == FALSE) {
        res = func_800A86E8_jp(memory, body);
    } else {
        res = func_800A8764_jp(animal, body);
    }
    return res;
}

#ifdef NON_MATCHING
s32 func_800A8868_jp(Mail* mail) {
    AnmPersonalId sp5C;
    s32 sp58 = 0;
    UNUSED s32 pad;
    UNUSED s32 pad1;
    s32 sp4C;
    UNUSED s32 pad2;
    s32 sp44;
    s32 sp40;
    UNUSED s32 pad3;
    UNUSED s32 pad4;
    Animal* sp24 = gCommonData.save.animals;
    AnmMemory* sp20;

    if (mMl_get_npcinfo_from_mail_name(&sp5C, &mail->header.recipient) == TRUE) {
        sp4C = func_800A7D08_jp(&sp5C);
        if (sp4C != -1) {
            sp24 += sp4C;
            sp40 = func_800A7238_jp(&mail->header.sender.personalId, sp24->memories, ANIMAL_MEMORY_NUM);
            if (sp40 == -1) {
                sp40 = func_800A706C_jp(sp24->memories, ANIMAL_MEMORY_NUM);
                if (sp40 >= 0) {
                    func_800B79E0_jp(&sp24->memories[sp40].memoryPlayerId, &mail->header.sender.personalId);
                }
            }
            sp20 = &sp24->memories[sp40];
            sp20->info.exists = TRUE;
            func_800A6C84_jp(&sp24->memories[sp40].letter);
            func_800A82C8_jp(&sp24->memories[sp40].letter, mail);
            sp44 = func_800A8814_jp(sp24, &sp24->memories[sp40], mail->content.body);
            if (mEv_CheckFirstJob() == 1) {
                QuestErrand* temp_v0_5 = func_800BBBEC_jp();

                if (((temp_v0_5->base.questKind == 6) || (temp_v0_5->base.questKind == 0xA)) &&
                    ((temp_v0_5->base.progress != 0))) {
                    temp_v0_5->base.progress = 3;
                    sp20->info.sendReply = 0;
                }
            } else {
                if ((mLd_PlayerManKindCheck() == FALSE) && (func_800BB5DC_jp(6) == sp4C)) {
                    func_800BBB30_jp(&sp24->contestQuest, &mail->header.sender, mail->content.body, mail->present);
                    sp20->info.sendReply = 0;
                }

                sp4C = 3;
                if (sp44 == 0) {
                    sp4C -= 5;
                }

                if (mail->present != 0) {
                    sp4C += 3;
                }
                func_800A6DD0_jp(sp20, sp4C);
            }
            sp58 = 1;
        }
    }
    return sp58;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_npc/func_800A8868_jp.s")
#endif

void func_800A8AB4_jp(AnmRemail* remail) {
    remail->date = mTM_rtcTime_ymd_clear_code;
    func_800B7780_jp(remail->name);
    func_80094EE0_jp(remail->landName);
    remail->flags.passwordLetter = 0;
    remail->flags.looks = 0x7F;
}

void func_800A8B10_jp(u16* present) {
    func_800BFCF0_jp(0, present, 1, 0, 0, category_table1[RANDOM(4.0f) & 1], 8);
}

s32 func_800A8B84_jp(Mail* mail, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Handbill_Unk_Struct handbillInfo;
    s32 res;

    handbillInfo.unk_00 = B_80142CF0_jp;
    handbillInfo.unk_04 = HANDBILL_HEADER_LEN;
    handbillInfo.unk_08 = mail->content.body;
    handbillInfo.unk_0C = HANDBILL_BODY_LEN;
    handbillInfo.unk_10 = B_80142E38_jp;
    handbillInfo.unk_14 = HANDBILL_FOOTER_LEN;
    handbillInfo.unk_18 = arg1;
    handbillInfo.unk_1C = arg2;
    handbillInfo.unk_20 = arg3;
    handbillInfo.unk_24 = arg4;
    handbillInfo.unk_28 = arg5;

    res = func_800944B8_jp(&handbillInfo);
    if (res == TRUE) {
        mail->content.headerBackStart = handbillInfo.unk_2C;
        mem_copy(mail->content.header, B_80142CF0_jp, MAIL_HEADER_LEN);
        mem_copy(mail->content.footer, B_80142E38_jp, MAIL_FOOTER_LEN);
    }
    return res;
}

void func_800A8C48_jp(Private* private, AnmPersonalId* anmId, AnmRemail* remail) {
    s32 i;
    u8 sp40[MAIL_HEADER_LEN];

    func_80092D10_jp(0, private->playerId.playerName, PLAYER_NAME_LEN);
    if (remail == NULL) {
        mNpc_GetNpcWorldNameAnm(sp40, anmId);
        func_80092D10_jp(1, sp40, PLAYER_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(sp40, mNpc_GetOtherAnimalPersonalID(anmId, 1));
        func_80092D10_jp(2, sp40, PLAYER_NAME_LEN);
    } else {
        func_80092D10_jp(1, remail->name, PLAYER_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(sp40, mNpc_GetOtherAnimalPersonalID(NULL, 0));
        func_80092D10_jp(2, sp40, PLAYER_NAME_LEN);
        func_80092D10_jp(14, remail->landName, PLAYER_NAME_LEN);
        func_80092D10_jp(15, func_800950D8_jp()->name, PLAYER_NAME_LEN);
    }

    for (i = 0; i < ARRAY_COUNT(base_str_no); i++) {
        func_800C3F70_jp(sp40, MAIL_HEADER_LEN, base_str_no[i] + RANDOM(32));
        func_80092D10_jp(i + 3, sp40, MAIL_HEADER_LEN);
    }
}

void func_800A8DB4_jp(Mail* mail, Private* private, AnmPersonalId* anmId, AnmRemail* remail, u8 arg4) {
    s32* sp54;
    s32 sp50;
    u16 sp4E = 0;
    s32 sp48;
    s32 temp;

    if (remail == NULL) {
        sp48 = anmId->looks;
    } else {
        sp48 = remail->flags.looks;
    }
    sp54 = start_no_table[arg4];
    sp50 = RANDOM(4.0f) & 1;
    if (sp50 == 0) {
        func_800A8B10_jp(&sp4E);
    }
    func_800A8C48_jp(private, anmId, remail);
    temp = sp54[sp48];
    func_800A8B84_jp(mail, RANDOM(32.0f) + temp, RANDOM(32.0f) + temp, RANDOM(16.0f) + temp + (sp50 * 0x10),
                     RANDOM(32.0f) + temp, RANDOM(32.0f) + temp);
    mail->present = sp4E;
}

void func_800A8F30_jp(Mail* mail, Private* private, AnmPersonalId* anmId, AnmRemail* remail, u8 arg4) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;

    if (remail == NULL) {
        sp30 = anmId->looks;
    } else {
        sp30 = remail->flags.looks;
    }
    func_800A8C48_jp(private, anmId, remail);
    sp34 = mail_no[arg4] + (sp30 * 3);
    sp34 += RANDOM2(3.0f);
    func_80093F04_jp(B_80142E80_jp, &sp2C, B_80142E98_jp, mail->content.body, sp34);
    mail->content.headerBackStart = sp2C;
    mem_copy(mail->content.header, B_80142E80_jp, MAIL_HEADER_LEN);
    mem_copy(mail->content.footer, B_80142E98_jp, MAIL_FOOTER_LEN);
    mail->present = 0;
}

void func_800A9028_jp(Mail* mail, Private* private, AnmPersonalId* anmId, AnmRemail* remail, u32 arg4, u8 arg5) {
    u16 sp36;

    get_remail[arg4](mail, private, anmId, remail, arg5);
    mail->content.font = 0;
    mail->content.mailType = 0;
    func_800B79E0_jp(&mail->header.recipient.personalId, &private->playerId);
    mail->header.recipient.type = 0;
    if (remail == NULL) {
        mMl_set_mail_name_npcinfo(&mail->header.sender, anmId);
    } else {
        mPr_CopyPlayerName(mail->header.sender.personalId.playerName, remail->name);
        mLd_CopyLandName(mail->header.sender.personalId.landName, remail->landName);
        mail->header.sender.type = 1;
    }
    func_800BFCF0_jp(0, &sp36, 1, 0, 0, 1, 8);
    mail->content.paperType = (sp36 - 0x2000) & 0xFFFF;
}

s32 func_800A9110_jp(Private* private, AnmPersonalId* anmId, AnmRemail* remail, u32 arg3, u8 arg4) {
    UNUSED s32 pad;
    s32 res = FALSE;

    if (func_800B68E8_jp() < 5) {
        func_800A9028_jp(&B_80142F80_jp, private, anmId, remail, arg3, arg4);
        res = func_800B6A3C_jp(&B_80142F80_jp, 0);
    }
    return res;
}

s32 func_800A918C_jp(LBRTC_Ymd* ymd, LBRTCTime* time) {
    s32 res = FALSE;

    if ((ymd->day != 0xFF) && ((ymd->year != time->year) || (ymd->month != time->month) || (ymd->day != time->day))) {
        res = TRUE;
    }
    return res;
}

void func_800A91DC_jp(void) {
    Animal* animal = gCommonData.save.animals;
    AnmMemory* memory;
    Private* priv = gCommonData.nowPrivate;
    AnmRemail* remail = &priv->remail;
    s32 memoryIdx;
    s32 i;

    if (func_800B7914_jp(&priv->playerId) == FALSE) {
        if (mLd_PlayerManKindCheck() == 0) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                    memoryIdx = func_800A7238_jp(&priv->playerId, animal->memories, ANIMAL_MEMORY_NUM);
                    if (memoryIdx != -1) {
                        memory = &animal->memories[memoryIdx];
                        if (memory->info.sendReply &&
                            (func_800A918C_jp(&memory->letter.date, &gCommonData.time.rtcTime) == TRUE)) {
                            if (func_800A9110_jp(priv, &animal->id, NULL, memory->info.passwordLetter, 0) == TRUE) {
                                memory->info.sendReply = 0;
                            } else {
                                break;
                            }
                        }
                    }
                }
                animal++;
            }

            if (priv->remail.flags.looks != 0x7F) {
                if (func_800A9110_jp(priv, &animal->id, remail, remail->flags.passwordLetter, 1) == TRUE) {
                    func_800A8AB4_jp(remail);
                }
            }
        }
    }
}

u8 func_800A9364_jp(void) {
    u16 sp2E;

    func_800BFCF0_jp(0, &sp2E, 1, 0, 0, 1, 8);
    return (sp2E - 0x2000) & 0xFF;
}

void func_800A93AC_jp(Mail* mail, PersonalId* pid, AnmPersonalId* anmId, u16 arg3, u8 arg4, s32 arg5) {
    UNUSED s32 pad[2];
    u8 sp54[MAIL_HEADER_LEN];
    UNUSED s32 pad2[3];
    u8 sp38[MAIL_FOOTER_LEN];
    s32 headerBackStart;

    mMl_clear_mail(mail);
    func_80093F54_jp(sp54, 0x14, &headerBackStart, sp38, 0x14, mail->content.body, arg5);
    mem_copy(mail->content.header, sp54, MAIL_HEADER_LEN);
    mem_copy(mail->content.footer, sp38, MAIL_FOOTER_LEN);
    mail->content.headerBackStart = headerBackStart;
    mail->content.font = 0;
    mail->content.mailType = 0;
    func_800B79E0_jp(&mail->header.recipient.personalId, pid);
    mail->header.recipient.type = 0;
    mMl_set_mail_name_npcinfo(&mail->header.sender, anmId);
    mail->present = arg3;
    mail->content.paperType = arg4;
}

void func_800A9468_jp(u16* arg0, s32 arg1) {
    func_800BFCF0_jp(0, arg0, 1, 0, 0, category_table2[arg1], D_8010B898_jp[arg1]);
}

void func_800A94C8_jp(Mail* mail, AnmMemory* memory, Animal* animal, s32 arg3, s32 arg4) {
    u16 sp2E;
    UNUSED s32 pad[2];

    func_80092D10_jp(0, memory->memoryPlayerId.playerName, PLAYER_NAME_LEN);
    mNpc_GetNpcWorldNameAnm(B_80142F50_jp, &animal->id);
    func_80092D10_jp(6, B_80142F50_jp, PLAYER_NAME_LEN);
    func_800A9468_jp(&sp2E, arg3);
    func_800A93AC_jp(mail, &memory->memoryPlayerId, &animal->id, sp2E, func_800A9364_jp(),
                     MAIL_BODY_LEN + (arg4 * 3) + arg3);
}

s32 func_800A956C_jp(AnmMemory* memory, s32 arg1, Animal* animal, s32 arg2) {
    UNUSED s32 pad;
    Home* home;
    UNUSED s32 pad2;
    s32 sp28;
    s32 sp24 = animal->id.looks;
    s32 res = FALSE;

    home = &gCommonData.save.homes[func_80094BF4_jp(arg1)];
    if (mPr_CheckCmpPersonalID(&memory->memoryPlayerId, &home->ownerID) == TRUE) {
        sp28 = func_8009C534_jp(home->mailbox, MAIL_HEADER_LEN);
        if (sp28 != -1) {
            func_800A94C8_jp(&B_80142F80_jp, memory, animal, arg2, sp24);
            func_8009C67C_jp(&home->mailbox[sp28], &B_80142F80_jp);
            res = TRUE;
        } else if (func_800B68E8_jp() < 5) {
            func_800A94C8_jp(&B_80142F80_jp, memory, animal, arg2, sp24);
            res = func_800B6A3C_jp(&B_80142F80_jp, 0);
        }
    }
    return res;
}

void func_800A96B0_jp(s32* outIdx, u8* arg1, Animal* animal, s32 arg3) {
    s32 sp24 = func_800A75FC_jp(animal->memories, ANIMAL_MEMORY_NUM);
    s32 memoryIdx = func_800A76E4_jp(animal->memories, ANIMAL_MEMORY_NUM, ~arg3 & 1);

    if ((sp24 != -1) && (memoryIdx == sp24)) {
        *outIdx = memoryIdx;
        *arg1 = 0;
    } else if (memoryIdx != -1) {
        *outIdx = memoryIdx;
        if (animal->memories[memoryIdx].info.friendship >= 0x50) {
            *arg1 = 1;
        } else {
            *arg1 = 2;
        }
    }
}

s32 func_800A9780_jp(s32 arg0) {
    Animal* animal = gCommonData.save.animals;
    AnmMemory* memory;
    s32 sp74[ANIMAL_NUM_MAX];
    u8 sp64[ANIMAL_NUM_MAX];
    s32 temp_v0_2;
    s32 var_fp = 0;
    u8 var_s4 = 0xF;
    s32 i;
    s32 j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        sp74[i] = -1;
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            if (func_800AD154_jp(&animal->id) == D_8010B8B0_jp[arg0]) {
                func_800A96B0_jp(&sp74[i], &sp64[i], animal, D_8010B8B0_jp[arg0]);
            }
        }
        animal++;
    }

    for (i = 0; i < 3; i++) {
        animal = gCommonData.save.animals;

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            if ((sp74[j] >= 0) && (i == sp64[j])) {
                memory = &animal->memories[sp74[j]];
                temp_v0_2 = func_800B7FD4_jp(memory);
                if (((var_s4 >> temp_v0_2) & 1) == 1) {
                    if (func_800A956C_jp(memory, temp_v0_2, animal, i) == 1) {
                        sp74[j] = -1;
                        var_fp++;
                    } else {
                        var_s4 &= ~(1 << temp_v0_2);
                    }
                }
            }

            if (var_s4 == 0) {
                return var_fp;
            }

            animal++;
        }
    }

    return var_fp;
}

void func_800A992C_jp(u16* arg0) {
    s32 temp_v0 = D_8010B8B8_jp[RANDOM(ARRAY_COUNT(D_8010B8B8_jp))];

    if (temp_v0 == 0xFF) {
        func_800C297C_jp(arg0, 1);
    } else {
        func_800BFCF0_jp(0, arg0, 1, 0, 0, temp_v0, 2);
    }
}

void func_800A99B8_jp(Mail* mail, PersonalId* pid, AnmPersonalId* anmId) {
    u8 sp2C[MAIL_HEADER_LEN];
    s32 sp28 = (RANDOM(3.0f) + (anmId->looks * 3)) + 0xEA;
    u16 sp26;

    func_80092D10_jp(0, pid->playerName, PLAYER_NAME_LEN);
    mNpc_GetNpcWorldNameAnm(B_80142F58_jp, anmId);
    func_80092D10_jp(1, B_80142F58_jp, PLAYER_NAME_LEN);
    func_800A992C_jp(&sp26);
    func_80096740_jp(sp2C, sp26);
    func_80092D10_jp(2, sp2C, MAIL_HEADER_LEN);
    func_800A93AC_jp(mail, pid, anmId, sp26, func_800A9364_jp(), sp28);
}

s32 func_800A9A98_jp(PersonalId* pid, s32 playerNo, AnmPersonalId* anmId) {
    UNUSED s32 pad;
    Home* sp28;
    s32 homeIdx;
    s32 sp20;
    s32 res = FALSE;

    homeIdx = func_80094BF4_jp(playerNo);
    sp28 = &gCommonData.save.homes[homeIdx];

    if ((func_800B7914_jp(pid) == FALSE) && (mPr_CheckCmpPersonalID(pid, &sp28->ownerID) == TRUE)) {
        sp20 = func_8009C534_jp(sp28->mailbox, MAIL_HEADER_LEN);
        if (sp20 != -1) {
            func_800A99B8_jp(&B_80142F80_jp, pid, anmId);
            func_8009C67C_jp(&sp28->mailbox[sp20], &B_80142F80_jp);
            res = TRUE;
        } else if (func_800B68E8_jp() < 5) {
            func_800A99B8_jp(&B_80142F80_jp, pid, anmId);
            res = func_800B6A3C_jp(&B_80142F80_jp, 0);
        }
    }
    return res;
}

s32 func_800A9BC4_jp(UNUSED s32 arg0) {
    return FALSE;
}

s32 func_800A9BD4_jp(PersonalId* pid, s32 playerNo) {
    Animal* animal = gCommonData.save.animals;
    s32 idx;
    s32 res = FALSE;
    s32 i;

    if (pid != NULL) {
        if (func_800951E4_jp(pid->landName, pid->landId) == TRUE) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                    idx = func_800A74A0_jp(animal->memories, ANIMAL_MEMORY_NUM);
                    if ((idx != -1) && (mPr_CheckCmpPersonalID(pid, &animal->memories[idx].memoryPlayerId) != 0) &&
                        (func_800A9A98_jp(pid, playerNo, &animal->id) == 1)) {
                        res = TRUE;
                    }
                }
                animal++;
            }
        }
    }
    return res;
}

void func_800A9CD4_jp(Mail* mail, PersonalId* pid) {
    UNUSED s32 pad;
    s32 sp30;

    func_80093F04_jp(mail->content.header, &sp30, mail->content.footer, mail->content.body, 0xD7);
    mail->content.headerBackStart = sp30;
    mail->content.font = 0;
    mail->content.mailType = 1;
    func_800B79E0_jp(&mail->header.recipient.personalId, pid);
    mail->header.recipient.type = 0;
    func_800BFCF0_jp(0, &mail->present, 1, 0, 0, 0, 3);
    mail->content.paperType = 0x16;
}

s32 func_800A9D68_jp(PersonalId* pid, s32 arg1) {
    UNUSED s32 pad;
    Home* home;
    UNUSED s32 pad2;
    s32 sp20;
    s32 res = FALSE;

    if (func_800B7914_jp(pid) == 0) {
        home = &gCommonData.save.homes[func_80094BF4_jp(arg1)];
        if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
            sp20 = func_8009C534_jp(home->mailbox, MAIL_HEADER_LEN);
            if (sp20 != -1) {
                func_800A9CD4_jp(&B_80142F80_jp, pid);
                func_8009C67C_jp(&home->mailbox[sp20], &B_80142F80_jp);
                res = TRUE;
            }
        }
    }
    return res;
}

void func_800A9E54_jp(Animal* animal, u8* arg1) {
    mem_copy(animal->catchphrase, arg1, ANIMAL_CATCHPHRASE_LEN);
}

u8* func_800A9E7C_jp(Actor* actor) {
    Animal* var_a1;
    Animal* tmp;
    u8* var_v1;

    if ((actor != NULL) & (actor->part == ACTOR_PART_NPC)) {
        var_a1 = tmp = ((Npc*)actor)->animal;
    } else {
        var_a1 = NULL;
    }

    if ((actor != NULL) && (var_a1 != NULL)) {
        var_v1 = var_a1->catchphrase;
    } else {
        var_v1 = l_no_ending_npc_ending;
    }

    return var_v1;
}

void func_800A9EC8_jp(Actor* actor) {
    if ((actor != NULL) && (actor->part == ACTOR_PART_NPC)) {
        Animal* animal = ((Npc*)actor)->animal;
        Struct_D_E03000* sp30;
        u16 idx;

        if (animal != NULL) {
            sp30 = zelda_malloc(SEGMENT_ROM_SIZE(segment_00E03000));

            if (0) {}

            if (sp30 != NULL) {
                DmaMgr_RequestSyncDebug(sp30, SEGMENT_ROM_START(segment_00E03000),
                                        ALIGN16(SEGMENT_ROM_SIZE(segment_00E03000)), "../m_npc.c", 0xE25);
                idx = animal->id.npcId & 0xFFF;
                func_800C3F70_jp(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN, sp30[idx].unk_02);
                zelda_free(sp30);
            }
        }
    }
}

s32 func_800A9F9C_jp(void) {
    CommonData_unk_10170* var_a2 = gCommonData.unk_10710;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gCommonData.unk_10710); i++) {
        if (var_a2->unk_09 == 0) {
            return i;
        }
        var_a2++;
    }
    return -1;
}

s32 func_800AA028_jp(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    s32 idx = func_800A9F9C_jp();
    s32 res = FALSE;

    if (idx != -1) {
        gCommonData.unk_10710[idx].fgName = arg0;
        gCommonData.unk_10710[idx].unk_02 = arg1;
        gCommonData.unk_10710[idx].npcId = arg2;
        gCommonData.unk_10710[idx].unk_06 = arg3;
        gCommonData.unk_10710[idx].unk_08 = 0;
        gCommonData.unk_10710[idx].unk_09 = 1;
        res = TRUE;
    }
    return res;
}

void func_800AA0B8_jp(u16 fgname) {
    CommonData_unk_10170* var_a2 = gCommonData.unk_10710;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gCommonData.unk_10710); i++) {
        if ((var_a2->unk_09 == 1) && (var_a2->fgName == fgname)) {
            bzero(var_a2, sizeof(CommonData_unk_10170));
            break;
        }
        var_a2++;
    }
}

void func_800AA124_jp(void) {
    bzero(gCommonData.unk_10710, sizeof(gCommonData.unk_10710));
}

CommonData_unk_10170* func_800AA14C_jp(u16 fgName) {
    CommonData_unk_10170* ptr = gCommonData.unk_10710;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gCommonData.unk_10710); i++) {
        if (ptr->fgName == fgName) {
            return ptr;
        }
        ptr++;
    }

    return NULL;
}

s32 mNpc_GetLooks(u16 npcName) {
    u8 res = 0;

    if (ACTOR_FGNAME_GET_F000(npcName) == FGNAME_F000_E) {
        res = D_8010AF58_jp[mNpc_GET_IDX(npcName)];
    }
    return res;
}

void func_800AA218_jp(Animal* animal, u16 arg1, u8 arg2, Struct_D_E03000* arg3) {
    if (ACTOR_FGNAME_GET_F000(arg1) == FGNAME_F000_E) {
        animal->id.npcId = arg1;
        animal->id.looks = arg2;
        animal->unk_520 = arg3->unk_00;
        func_800C3F70_jp(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN, arg3->unk_02);
        animal->id.landId = gCommonData.save.landInfo.landId;
        mLd_CopyLandName(animal->id.landName, gCommonData.save.landInfo.name);
    }
}

void func_800AA29C_jp(Animal* animal, u16 arg1, Struct_D_E03000 arg2[]) {
    s32 idx = mNpc_GET_IDX(arg1);
    if (ACTOR_FGNAME_GET_F000(arg1) == FGNAME_F000_E) {
        func_800AA218_jp(animal, arg1, D_8010AF58_jp[idx], &arg2[idx]);
    }
}

void func_800AA2F8_jp(u16 arg0) {
    u8* ptr = gCommonData.save.unk_0F86C;

    if (ACTOR_FGNAME_GET_F000(arg0) == FGNAME_F000_E) {
        s32 idx = mNpc_GET_IDX(arg0);
        s32 temp_a2 = idx / 8;

        if (temp_a2 < ARRAY_COUNT(gCommonData.save.unk_0F86C)) {
            ptr += temp_a2;
            idx &= 7;
            *ptr |= 1 << idx;
        }
    }
}

s32 func_800AA35C_jp(s32 arg0) {
    s32 res = TRUE;
    u8* ptr = gCommonData.save.unk_0F86C;
    s32 temp_a1 = arg0 / 8;

    if (temp_a1 < ARRAY_COUNT(gCommonData.save.unk_0F86C)) {
        ptr += temp_a1;
        res = (*ptr >> (arg0 & 7)) & 1;
    }
    return res;
}

s32 func_800AA3A4_jp(u8 arg0) {
    s32 i;
    s32 count = 0;

    if (arg0 < 6) {
        for (i = 0; i < 0xD8; i++) {
            if ((arg0 == D_8010AF58_jp[i]) && (func_800AA35C_jp(i) == FALSE)) {
                count++;
            }
        }
    }
    return count;
}

void func_800AA438_jp(u8* arg0, Animal* animal) {
    s32 i;

    bzero(arg0, sizeof(gCommonData.save.unk_0F86C));

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            func_800AA2F8_jp(animal->id.npcId);
        }
        animal++;
    }
}

void func_800AA49C_jp(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(B_80143028_jp); i++) {
        if (func_800AA35C_jp(i) == FALSE) {
            break;
        }
    }

    if (i == ARRAY_COUNT(B_80143028_jp)) {
        func_800AA438_jp(gCommonData.save.unk_0F86C, gCommonData.save.animals);
    }
}

s32 func_800AA4FC_jp(s32 arg0, u8* arg1, s32 arg2) {
    s8 res = 1;

    if (arg0 < arg2) {
        res = arg1[arg0];
    }
    return res;
}

void func_800AA51C_jp(Animal* animal, u8 arg1, s32 count) {
    UNUSED s32 pad;
    void* sp50;
    void* sp4C;
    u8 var_s7 = 0;
    s32 i = 0;
    u8 temp_s2;

    bzero(B_80143028_jp, sizeof(B_80143028_jp));
    func_800A6810_jp(B_80143028_jp, ARRAY_COUNT(B_80143028_jp), ARRAY_COUNT(B_80143028_jp));

    if (count == 0) {
        sp50 = malloc(SEGMENT_ROM_SIZE(segment_00E03000));
        sp4C = malloc(ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)));
    } else {
        sp50 = zelda_malloc(SEGMENT_ROM_SIZE(segment_00E03000));
        sp4C = zelda_malloc(ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)));
    }

    DmaMgr_RequestSyncDebug(sp50, SEGMENT_ROM_START(segment_00E03000), SEGMENT_ROM_SIZE(segment_00E03000), "../m_npc.c",
                            4083);
    DmaMgr_RequestSyncDebug(sp4C, SEGMENT_ROM_START(segment_00E0D000), ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)),
                            "../m_npc.c", 4085);

    while (arg1) {
        if (animal == NULL) {
            break;
        }

        if (animal->id.npcId == 0) {
            s32 temp_s0 = B_80143028_jp[i];
            s32 temp_v0 = func_800AA4FC_jp(temp_s0, sp4C, ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)));

            if (temp_v0 == 0) {
                temp_s2 = D_8010AF58_jp[temp_s0];
                if (((var_s7 >> temp_s2) & 1) == 0) {
                    func_800AA29C_jp(animal, temp_s0 | 0xE000, (Struct_D_E03000*)sp50);
                    var_s7 |= (1 << temp_s2);
                    func_800AA2F8_jp(temp_s0 | 0xE000);
                    animal++;
                    arg1--;
                }
            } else if (temp_v0 == -1) {
                func_800AA2F8_jp(temp_s0 | 0xE000);
            }
        } else {
            arg1--;
            animal++;
        }
        i++;
    }

    if (count == 0) {
        free(sp50);
        free(sp4C);
    } else {
        zelda_free(sp50);
        zelda_free(sp4C);
    }
}

void mNpc_SetAnimalTitleDemo(NpcDemoNpc* demoNpc, Animal* animal, Game* game) {
    GameAlloc* alloc = NULL;
    Struct_D_E03000* var_v0;
    s32 i;

    if (game != NULL) {
        alloc = &game->alloc;
        var_v0 = gamealloc_malloc(alloc, SEGMENT_ROM_SIZE(segment_00E03000));
    } else {
        var_v0 = zelda_malloc(SEGMENT_ROM_SIZE(segment_00E03000));
    }
    DmaMgr_RequestSyncDebug(var_v0, SEGMENT_ROM_START(segment_00E03000), SEGMENT_ROM_SIZE(segment_00E03000),
                            "../m_npc.c", 0x1055);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        func_800AA29C_jp(animal, demoNpc->npcName, var_v0);
        animal->homeInfo.typeUnused = 0;
        animal->homeInfo.blockX = demoNpc->blockX;
        animal->homeInfo.blockZ = demoNpc->blockZ;
        animal->homeInfo.utX = demoNpc->utX;
        animal->homeInfo.utZ = demoNpc->utZ;

        animal++;
        demoNpc++;
    }

    if (var_v0 != NULL) {
        if (game != NULL) {
            gamealloc_free(alloc, var_v0);
        } else {
            zelda_free(var_v0);
        }
    }
}

s32 func_800AA8C4_jp(s32* arg0, s32* arg1, u16* arg2) {
    f32 sp24 = 0.0f;
    s32 rand;
    s32 res = FALSE;
    s32 i;

    for (i = 0; i < 0x100; i++) {
        if (((*arg2 >= 0x5810) && (*arg2 < 0x5825)) || (*arg2 == 0xF0EE)) {
            sp24++;
        }
        arg2++;
    }

    if (sp24 > 0.0f) {
        arg2 -= 0x100;
        rand = RANDOM(sp24);

        for (i = 0; i < 0x100; i++) {
            if (((*arg2 >= 0x5810) && (*arg2 < 0x5825)) || (*arg2 == 0xF0EE)) {
                if (rand == 0) {
                    *arg0 = i % 16;
                    *arg1 = i / 16;
                    res = TRUE;
                    break;
                } else {
                    rand--;
                }
            }
            arg2++;
        }
    }
    return res;
}

s32 func_800AA9F4_jp(s32* arg0, s32* arg1, UNK_TYPE arg2, UNK_TYPE arg3) {
    u16* temp_v0 = func_8008A33C_jp(arg2, arg3);
    s32 res = FALSE;

    if (temp_v0 != NULL) {
        res = func_800AA8C4_jp(arg0, arg1, temp_v0);
    }
    return res;
}

void func_800AAA40_jp(Struct_B_80142D08_jp* arg0, s32 count, u8* arg2) {
    Fg* fg = &gCommonData.save.fg[0][0];
    Struct_B_80142D08_jp* arg0_backup = arg0;
    u16* item;
    u8 num = 0;
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    for (i = 0; i < count; i++) {
        arg0->unk_01 = 0xFF;
        arg0->unk_02 = 0xFF;
        arg0->unk_03 = 0xFF;
        arg0->unk_04 = 0xFF;
        arg0++;
    }

    arg0 = arg0_backup;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 5; j++) {
            item = &fg->items[0][0];
            for (k = 0; k < 16; k++) {
                for (l = 0; l < 16; l++) {
                    if ((*item >= 0x5810) && (*item < 0x5825)) {
                        num++;
                        arg0->unk_01 = j + 1;
                        arg0->unk_02 = i + 1;
                        arg0->unk_03 = l;
                        arg0->unk_04 = k;
                        arg0++;
                        if (num >= count) {
                            *arg2 = num;
                            return;
                        }
                    }
                    item++;
                }
            }
            fg++;
        }
    }

    *arg2 = num;
}

void func_800AAB48_jp(Struct_B_80142D08_jp* arg0, s32 arg1, u8* arg2, u8 arg3, u8 arg4) {
    Struct_g_fdinfo_148* var_t1 = func_80087C64_jp();
    Struct_B_80142D08_jp* var_s0 = arg0;
    u8 count = 0;
    u16* var_a0;
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    for (i = 0; i < arg1; i++) {
        arg0->unk_01 = 0xFF;
        arg0->unk_02 = 0xFF;
        arg0->unk_03 = 0xFF;
        arg0->unk_04 = 0xFF;
        arg0++;
    }
    arg0 = var_s0;

    for (i = 0; i < arg4; i++) {
        for (j = 0; j < arg3; j++) {
            var_a0 = var_t1->unk_584;
            for (k = 0; k < 16; k++) {
                for (l = 0; l < 16; l++) {
                    if ((*var_a0 >= 0x5810) && (*var_a0 < 0x5825)) {
                        count++;
                        arg0->unk_01 = j;
                        arg0->unk_02 = i;
                        arg0->unk_03 = l;
                        arg0->unk_04 = k;
                        arg0++;
                        if (count >= arg1) {
                            *arg2 = count;
                            return;
                        }
                    }
                    var_a0++;
                }
            }
            var_t1++;
        }
    }

    *arg2 = count;
}

void func_800AAC88_jp(u16 npcId, s32 blockX, s32 blockZ, s32 utX, s32 utZ) {
    u16* deposit;
    s32 x;
    s32 z;
    s32 i;

    if ((blockX >= 0) && (blockX < 5) && (blockZ >= 0) && (blockZ < 6) && (utX > 0) && (utX < 0xF) && (utZ > 0) &&
        (utZ < 0xF)) {
        Fg* fg = &gCommonData.save.fg[blockZ][blockX];

        set_fg[0] = npcId + 0xFFFF7000;
        deposit = func_8008C1E0_jp(blockX + 1, blockZ + 1);

        for (i = 0; i < ARRAY_COUNT(set_fg); i++) {
            x = ut_d[i].unk_00 + utX;
            z = ut_d[i].unk_04 + utZ;

            mPB_keep_item(fg->items[z][x]);
            if (deposit != NULL) {
                func_8008C478_jp(deposit, x, z);
            }
            fg->items[z][x] = set_fg[i];
        }
    }
}

#ifdef NON_MATCHING
void func_800AADE8_jp(AnmHome* homeInfo) {
    u8 blockX = homeInfo->blockX - 1;
    u8 blockZ = homeInfo->blockZ - 1;
    u8 utX = homeInfo->utX;
    u8 utZ = homeInfo->utZ - 1;

    if ((blockX < 5) && (blockZ < 6) && (utX > 0) && (utX < 0xF) && (utZ > 0) && (utZ < 0xF)) {
        s32 val = func_800879B0_jp(homeInfo->blockX, homeInfo->blockZ);

        gCommonData.save.fg[blockZ][blockX].items[utZ][utX] = val;    // a8
        gCommonData.save.fg[blockZ][blockX].items[utZ][utX + 15] = 0; // c6
        gCommonData.save.fg[blockZ][blockX].items[utZ + 1][0] = 0;    // c8
        gCommonData.save.fg[blockZ][blockX].items[utZ + 1][1] = 0;    // ca

        gCommonData.save.fg[blockZ][blockX].items[utZ][utX - 1] = 0; // a6
        gCommonData.save.fg[blockZ][blockX].items[utZ][utX + 1] = 0; // aa

        gCommonData.save.fg[blockZ][blockX].items[utZ - 2][15] = 0; // 86
        gCommonData.save.fg[blockZ][blockX].items[utZ - 1][0] = 0;  // 88
        gCommonData.save.fg[blockZ][blockX].items[utZ - 1][1] = 0;  // 8a
    }
}
#else
void func_800AADE8_jp(AnmHome* homeInfo);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_npc/func_800AADE8_jp.s")
#endif

void func_800AAEFC_jp(Animal* animal, Struct_B_80142D08_jp* arg1, u8 arg2) {
    AnmHome* homeInfo;
    s32 i;
    s32 idx;

    if (arg2 > ARRAY_COUNT(B_80142C00_jp)) {
        arg2 = ARRAY_COUNT(B_80142C00_jp);
    }
    bzero(B_80142C00_jp, sizeof(B_80142C00_jp));
    func_800A6810_jp(B_80142C00_jp, arg2, 30);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (i >= arg2) {
            break;
        }

        homeInfo = &animal->homeInfo;
        if ((ACTOR_FGNAME_GET_F000(animal->id.npcId) == FGNAME_F000_E) && (homeInfo->blockX == 0xFF) &&
            (homeInfo->blockZ == 0xFF)) {
            idx = B_80142C00_jp[i];
            homeInfo->blockX = arg1[idx].unk_01;
            homeInfo->blockZ = arg1[idx].unk_02;
            homeInfo->utX = arg1[idx].unk_03;
            homeInfo->utZ = arg1[idx].unk_04 + 1;
            func_800AAC88_jp(animal->id.npcId, homeInfo->blockX - 1, homeInfo->blockZ - 1, homeInfo->utX,
                             arg1[idx].unk_04);
        }
        animal++;
    }
}

void func_800AB054_jp(void) {
    UNUSED s32 pad;
    u8 sp1B = 0;

    func_800AAA40_jp(B_80142D08_jp, ARRAY_COUNT(B_80142D08_jp), &sp1B);
    func_800AAEFC_jp(gCommonData.save.animals, B_80142D08_jp, sp1B);
}

void func_800AB09C_jp(void) {
    NpcList* npcList = gCommonData.npcList;
    s32 i;

    bzero(npcList, sizeof(NpcList) * ANIMAL_NUM_MAX);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        npcList->fieldName = 0xFFFF;
        func_800BA660_jp(&npcList->questInfo);
        npcList->houseData.type = 0xFF;
        npcList->houseData.palette = 0xFF;
        npcList->houseData.wallId = 0xFF;
        npcList->houseData.floorId = 0xFF;
        npcList->houseData.mainLayerId = 0xCB;
        npcList++;
    }
}

void mNpc_SetNpcList(NpcList* npcList, Animal* animal, s32 count, s32 mallocFlag) {
    NpcHouseData* houseData;
    NpcHouseData* newHouse;
    Vec3f* homePos;
    Vec3f* pos;
    s32 id;
    f32 z;
    AnmHome* homeInfo;
    f32 x;
    u32 houseDataSize;
    s32 i;
    s32 npcId;

    houseDataSize = SEGMENT_ROM_SIZE(segment_00E02000);
    if (mallocFlag == 0) {
        houseData = malloc(houseDataSize);
    } else {
        houseData = zelda_malloc(houseDataSize);
    }
    DmaMgr_RequestSyncDebug(houseData, SEGMENT_ROM_START(segment_00E02000), houseDataSize, "../m_npc.c", 0x1328);

    for (i = 0; i < count; i++) {
        homeInfo = &animal->homeInfo;
        if ((ACTOR_FGNAME_GET_F000(animal->id.npcId) == FGNAME_F000_E) && (homeInfo->blockX != 0xFF)) {
            npcId = animal->id.npcId;
            id = animal->id.npcId & 0xFFF;
            newHouse = &npcList->houseData;
            homePos = &npcList->homePosition;
            pos = &npcList->position;
            if (0) {}
            npcList->name = npcId;

            homePos->x = homeInfo->blockX * 640.0f;
            homePos->z = homeInfo->blockZ * 640.0f;
            func_80088BC0_jp(&x, &z, homeInfo->utX, homeInfo->utZ);

            homePos->x += x;
            homePos->z += z;
            homePos->y = 0.0f;

            pos->x = homePos->x;
            pos->y = homePos->y;
            pos->z = homePos->z;

            npcList->flags.unk_31 = 1;
            npcList->rewardFurniture = 0;

            newHouse->type = houseData[id].type;
            newHouse->palette = houseData[id].palette;
            newHouse->wallId = houseData[id].wallId;
            newHouse->floorId = houseData[id].floorId;
            newHouse->mainLayerId = houseData[id].mainLayerId;
            newHouse->secondaryLayerId = houseData[id].secondaryLayerId;
        }
        npcList++;
        animal++;
    }

    if (mallocFlag == 0) {
        free(houseData);
    } else {
        zelda_free(houseData);
    }
}

void mNpc_SetNpcinfo(Actor* actor, s8 npcInfoIdx) {
    if (actor->part == ACTOR_PART_NPC) {
        Npc* npc = (Npc*)actor;

        if (ACTOR_FGNAME_GET_F000(npc->actor.fgName) == FGNAME_F000_D) {
            CommonData_unk_10170* temp_v0 = func_800AA14C_jp(npc->actor.fgName);

            if (temp_v0 != NULL) {
                npcInfoIdx = mNpc_SearchAnimalinfo(gCommonData.save.animals, temp_v0->npcId, ANIMAL_NUM_MAX);
            }
        }

        if ((npcInfoIdx >= 0) && (npcInfoIdx < ANIMAL_NUM_MAX)) {
            npc->animal = &gCommonData.save.animals[npcInfoIdx];
            npc->npcList = &gCommonData.npcList[npcInfoIdx];
        } else {
            npc->animal = NULL;
            npc->npcList = NULL;
        }
    }
}

void func_800AB498_jp(FieldInfo_Unk_Struct* arg0, u8 arg1, u8 arg2) {
    s32 temp_v0;
    s32 sp38;
    u16 fieldId;
    u16 sp34;
    u8* temp_v0_3;
    UNUSED s32 pad;
    u16 sp2A;
    s32 sp24;

    if (arg0 != NULL) {
        fieldId = mFI_GetFieldId();
        sp38 = func_8008BE00_jp(arg0, 16);
        if (sp38 != -1) {
            arg0 = &arg0[sp38];
            if (mNpc_GET_TYPE(fieldId) == 0x4000) {
                sp34 = gCommonData.houseOwnerName;
                if ((sp38 < ANIMAL_NUM_MAX) && (sp34 != 0xFFFF) && (sp34 != 0)) {
                    if (func_80082CC8_jp(sp34) != 1) {
                        temp_v0 = mNpc_SearchAnimalinfo(gCommonData.save.animals, sp34, ANIMAL_NUM_MAX);
                        if (temp_v0 != -1) {
                            arg0->houseOwnerName = sp34;
                            arg0->unk_02 = 4;
                            arg0->unk_03 = 7;
                            arg0->npcId = temp_v0;
                            arg0->unk_06 = -1;
                            func_8008BC64_jp(sp38, arg1, arg2);
                        }
                    }
                }
            } else if (fieldId == 0x300A) {
                temp_v0_3 = func_8008033C_jp(0xE, 0xF);
                if (temp_v0_3 != NULL) {
                    sp24 = *temp_v0_3;
                    sp2A = gCommonData.save.animals[sp24].id.npcId;
                    func_80082BD8_jp(&sp2A, 0xE, sp24, 0);
                    arg0->houseOwnerName = sp2A;
                    arg0->unk_02 = 4;
                    arg0->unk_03 = 7;
                    arg0->npcId = sp24;
                    arg0->unk_06 = -1;
                    func_8008BC64_jp(sp38, arg1, arg2);
                }
            }
        }
    }
}

void func_800AB62C_jp(s16* arg0) {
    s32 fieldId = mFI_GetFieldId();
    u16 ownerName = gCommonData.houseOwnerName;
    s32 wallId;
    s32 floorId;
    s32 npc_idx;

    if (mNpc_GET_TYPE(fieldId) == 0x4000) {
        if ((ownerName != 0) && (ownerName != 0xFFFF)) {
            npc_idx = mNpc_SearchAnimalinfo(gCommonData.save.animals, ownerName, ANIMAL_NUM_MAX);
            wallId = gCommonData.npcList[npc_idx].houseData.wallId;
            floorId = gCommonData.npcList[npc_idx].houseData.floorId;
            *arg0 = floorId | (wallId << 8);
        label:;
            return;
        }
    }
    *arg0 = 0;
}

void func_800AB6C8_jp(Actor* actor) {
    Npc* npc = (Npc*)actor;

    if (npc->npcList != NULL) {
        s32 fieldId = mFI_GetFieldId();
        NpcList* npcList = npc->npcList;

        if ((mNpc_GET_TYPE(fieldId)) == 0) {
            xyz_t_move(&npcList->position, &npc->actor.world.pos);
            npcList->flags.unk_31 = 1;
        }
    } else {
        func_8008BD98_jp(actor);
    }
}

s32 func_800AB734_jp(Private* private) {
    Animal* animal = gCommonData.save.animals;
    s32 count = 0;
    s32 i;

    if (private != NULL) {

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if ((mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) &&
                (func_800A7238_jp(&private->playerId, animal->memories, ANIMAL_MEMORY_NUM) != -1)) {
                count++;
            }
            animal++;
        }
    }
    return count;
}

s32 func_800AB7D0_jp(Private* private) {
    s32 npcMax = gCommonData.save.nowNpcMax;

    if (func_800AB734_jp(private) >= npcMax) {
        return TRUE;
    }
    return FALSE;
}

s32 func_800AB80C_jp(u16 arg0) {
    s32 res = FALSE;

    if (((arg0 < 0x17AC) || (arg0 >= 0x1BA8)) && ((arg0 < 0x1CA8) || (arg0 >= 0x1D28)) &&
        ((arg0 < 0x1BA8) || (arg0 >= 0x1C28)) && ((arg0 < 0x1C28) || (arg0 >= 0x1CA8)) &&
        ((arg0 < 0x15B0) || (arg0 >= 0x17AC)) && ((arg0 < 0x1E3C) || (arg0 >= 0x1EA0)) &&
        ((arg0 < 0x1D28) || (arg0 >= 0x1D44))) {
        res = TRUE;
    }
    return res;
}

u16 func_800AB8A0_jp(FieldMake_Unk_Struct* arg0, NpcList* npcList, s32 count) {
    u16 layerId = npcList->houseData.mainLayerId;
    s32 idx = layerId - count;
    u16* var_s1;
    s32 i;
    s32 j;
    u8 var_s2 = 0;

    if (idx < 0) {
        idx = 0;
    }
    var_s1 = arg0->unk_000[idx] + 1;

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if ((ACTOR_FGNAME_GET_F000(*var_s1) == FGNAME_F000_1) && (func_800AB80C_jp(*var_s1) == TRUE)) {
                var_s2++;
            }
            var_s1++;
        }
        var_s1 += 6;
    }

    if (var_s2 > 0) {
        var_s2 = RANDOM(var_s2);
        var_s1 = arg0->unk_000[idx] + 1;

        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                if ((ACTOR_FGNAME_GET_F000(*var_s1) == FGNAME_F000_1) && (func_800AB80C_jp(*var_s1) == TRUE)) {
                    if (var_s2 <= 0) {
                        return *var_s1;
                    }
                    var_s2--;
                }
                var_s1++;
            }
            var_s1 += 6;
        }
    }

    return 0;
}

void func_800ABA14_jp(FieldMake_Unk_Struct* arg0, s32 count) {
    NpcList* npcList = gCommonData.npcList;
    Animal* animal = gCommonData.save.animals;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            npcList->rewardFurniture = func_800AB8A0_jp(arg0, npcList, count);
        }
        npcList++;
        animal++;
    }
}

u16 func_800ABAA8_jp(AnmPersonalId* anmId) {
    u16 res = 0;
    s32 idx = func_800A7D08_jp(anmId);

    if (idx != -1) {
        res = gCommonData.npcList[idx].rewardFurniture;
    }
    return res;
}

void func_800ABAF0_jp(void) {
    mNpc_ClearAnimalInfo(&B_80143388_jp);
}

Animal* mNpc_GetInAnimalP(void) {
    return &B_80143388_jp;
}

s32 func_800ABB24_jp(Animal* animal, s32 arg1) {
    Private* priv = gCommonData.save.private;
    s32 res = -1;
    s32 sp44 = 0;
    s32 var_s7 = 0;
    s32 var_s2;
    s32 i;
    s32 j;
    u16 var_fp = 0;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (func_800B7914_jp(&priv->playerId) == 0) {
            sp44++;
        }
        priv++;
    }

    if (sp44 > 0) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                priv = gCommonData.save.private;
                var_s2 = 0;

                for (j = 0; j != PLAYER_NUM; j++) {
                    if (func_800B7914_jp(&priv->playerId) == FALSE) {
                        if (func_800A7238_jp(&priv->playerId, animal->memories, ANIMAL_MEMORY_NUM) == -1) {
                            break;
                        }
                        var_s2++;
                    }
                    priv++;
                }

                if (arg1 == 1) {
                    if (var_s2 == sp44) {
                        var_s7++;
                        var_fp |= (1 << i);
                    }
                } else if (var_s2 > 0) {
                    var_s7++;
                    var_fp |= (1 << i);
                }
            }
            animal++;
        }
    }

    if (var_s7 > 0) {
        s32 rand = RANDOM(var_s7);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((var_fp >> i) & 1) == 1) {
                if (rand <= 0) {
                    res = i;
                    break;
                }
                rand--;
            }
        }
    }
    return res;
}

u8 func_800ABCF8_jp(Animal* animal, s32 arg1) {
    u8 count = 0;
    s32 rand = RANDOM(arg1);
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            rand--;
        }
        if (rand <= 0) {
            break;
        }
        count++;
        animal++;
    }

    return count;
}

void mNpc_SetRemoveAnimalNo(Animal* animal) {
    u8* removalIdx = &gCommonData.save.removeAnimalIdx;
    u8 nowMax = gCommonData.save.nowNpcMax;

    if ((nowMax >= 6) && (*removalIdx == 0xFF)) {
        s32 var_v1 = func_800ABB24_jp(animal, 1);

        if (var_v1 == -1) {
            var_v1 = func_800ABB24_jp(animal, 0);
            if (var_v1 == -1) {
                var_v1 = func_800ABCF8_jp(animal, nowMax);
            }
        }

        if (var_v1 != -1) {
            *removalIdx = var_v1;
        }
    }
}

s32 func_800ABE30_jp(Animal* animal1, Animal* animal2) {
    AnmMemory* sp28 = animal1->memories;
    AnmMemory* sp24 = animal2->memories;
    s32 res = 0;
    s32 temp_s0 = func_800A77F0_jp(sp28, ANIMAL_MEMORY_NUM);
    s32 temp_v0 = func_800A77F0_jp(sp24, ANIMAL_MEMORY_NUM);

    if (temp_s0 < temp_v0) {
        res = 1;
    } else if (temp_v0 == temp_s0) {
        temp_s0 = func_800A7858_jp(sp28, ANIMAL_MEMORY_NUM);
        temp_v0 = func_800A7858_jp(sp24, ANIMAL_MEMORY_NUM);
        if (temp_s0 < temp_v0) {
            res = 1;
        } else if (temp_v0 == temp_s0) {
            temp_s0 = func_800A78DC_jp(sp28, ANIMAL_MEMORY_NUM);
            temp_v0 = func_800A78DC_jp(sp24, ANIMAL_MEMORY_NUM);
            if (temp_s0 < temp_v0) {
                res = 1;
            } else if (temp_v0 == temp_s0) {
                temp_s0 = func_800A8148_jp(animal1->id.looks);
                if (func_800A8148_jp(animal2->id.looks) < temp_s0) {
                    res = 1;
                } else {
                    res = -1;
                }
            }
        }
    }

    return res;
}

s32 func_800ABF40_jp(void) {
    UNUSED s32 pad;
    Animal* animal = gCommonData.save.animals;
    Animal* foundAnimal = NULL;
    s32 temp_s1;
    s32 temp_v0;
    u16 var_s4 = 0;
    s32 var_s5 = 0;
    s32 foundIdx = -1;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++, animal++) {
        // Bug
        if ((i != (u32)&gCommonData.save.removeAnimalIdx) && (mNpc_CheckFreeAnimalInfo(animal) == FALSE)) {
            if (foundAnimal != NULL) {
                if (func_800A6B58_jp(animal) == 0) {
                    if (func_800A6B58_jp(foundAnimal) != 0) {
                        var_s5 = 1;
                        var_s4 = (1 << i);
                        foundAnimal = animal;
                        foundIdx = i;
                    } else {
                        temp_v0 = func_800ABE30_jp(animal, foundAnimal);
                        switch (temp_v0) {
                            case -1:
                                var_s5++;
                                var_s4 |= (1 << i);
                                break;
                            case 1:
                                var_s5 = 1;
                                var_s4 = (1 << i);
                                foundAnimal = animal;
                                foundIdx = i;
                                break;
                        }
                    }
                } else if (func_800A6B58_jp(foundAnimal) != 0) {
                    temp_s1 = func_800A6B6C_jp(animal);
                    temp_v0 = func_800A6B6C_jp(foundAnimal);
                    if (temp_s1 < temp_v0) {
                        var_s5 = 1;
                        var_s4 = (1 << i);
                        foundAnimal = animal;
                        foundIdx = i;
                    } else if (temp_v0 == temp_s1) {
                        temp_v0 = func_800ABE30_jp(animal, foundAnimal);
                        switch (temp_v0) {
                            case -1:
                                var_s5++;
                                var_s4 |= (1 << i);
                                break;
                            case 1:
                                var_s5 = 1;
                                var_s4 = (1 << i);
                                foundAnimal = animal;
                                foundIdx = i;
                                break;
                        }
                    }
                }
            } else {
                var_s5 = 1;
                var_s4 = (1 << i);
                foundAnimal = animal;
                foundIdx = i;
            }
        }
    }

    if (var_s5 >= 2) {
        s32 rand = RANDOM(var_s5);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((var_s5 >> i) & 1) == 1) {
                if (rand == 0) {
                    foundIdx = i;
                    break;
                } else {
                    rand--;
                }
            }
        }
    }
    return foundIdx;
}

void func_800AC1A0_jp(Struct_B_80142F70_jp* arg0) {
    mNpc_ClearAnimalPersonalID(&arg0->id);
    arg0->unk_0C = 0;
}

void func_800AC1C8_jp(void) {
    func_800AC1A0_jp(&B_80142F70_jp);
}

void func_800AC1EC_jp(Struct_B_80142F70_jp* arg0, Animal* animal) {
    Private* priv = gCommonData.save.private;
    s32 i;

    if ((animal != NULL) && (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE)) {
        mNpc_CopyAnimalPersonalID(&arg0->id, &animal->id);

        for (i = 0; i < PLAYER_NUM; i++) {
            if (func_800B7914_jp(&priv->playerId) == FALSE) {
                arg0->unk_0C |= 1 << i;
            }
            priv++;
        }
    }
}

s32 func_800AC284_jp(Mail* mail, PersonalId* pid, AnmPersonalId* anmId) {
    s32 sp24;
    s32 res = FALSE;

    if (anmId->looks < 6) {
        sp24 = (anmId->looks * 3) + 0x20E;
        sp24 += func_800BC414_jp(3);
        mNpc_GetNpcWorldNameAnm(B_80142F60_jp, anmId);
        func_80092D10_jp(0, pid->playerName, PLAYER_NAME_LEN);
        func_80092D10_jp(1, B_80142F60_jp, PLAYER_NAME_LEN);
        func_80092D10_jp(3, gCommonData.save.landInfo.name, LAND_NAME_SIZE);
        func_800A93AC_jp(mail, pid, anmId, 0, func_800A9364_jp(), sp24);
        res = TRUE;
    }
    return res;
}

s32 func_800AC358_jp(Mail* mail, Private* priv, s32 playerNo, AnmPersonalId* anmId) {
    Home* home;
    UNUSED s32 pad;
    s32 res = FALSE;

    home = &gCommonData.save.homes[func_80094BF4_jp(playerNo)];

    if ((func_800B7914_jp(&priv->playerId) == FALSE) &&
        (mPr_CheckCmpPersonalID(&priv->playerId, &home->ownerID) == TRUE)) {
        s32 sp18 = func_8009C534_jp(home->mailbox, HOME_MAILBOX_SIZE);
        if (sp18 != -1) {
            if (func_800AC284_jp(mail, &priv->playerId, anmId) == TRUE) {
                func_8009C67C_jp(&home->mailbox[sp18], mail);
                res = TRUE;
            }
        } else if ((func_800B68E8_jp() < 5) && (func_800AC284_jp(mail, &priv->playerId, anmId) == TRUE)) {
            res = func_800B6A3C_jp(mail, 0);
        }
    }
    return res;
}

void func_800AC488_jp(Struct_B_80142F70_jp* arg0) {
    Private* priv = gCommonData.save.private;
    s32 i;

    if (mNpc_CheckFreeAnimalPersonalID(&arg0->id) == FALSE) {
        for (i = 0; i < PLAYER_NUM; i++) {
            if ((((arg0->unk_0C >> i) & 1) == 1) && (func_800AC358_jp(&B_80142F80_jp, priv, i, &arg0->id) == TRUE)) {
                arg0->unk_0C &= ~(1 << i);
            }
            priv++;
        }

        if (arg0->unk_0C == 0) {
            func_800AC1A0_jp(arg0);
        }
    }
}

void mNpc_SendRegisteredGoodbyMail(void) {
    func_800AC488_jp(&B_80142F70_jp);
}

void func_800AC57C_jp(Animal* inAnimal, s32 arg1) {
    Private* priv;
    UNUSED s32 pad[4];
    s32 sp20;
    Animal* animal;
    s32 freeAnimalIdx;
    u8* removeAnimalIdx = &gCommonData.save.removeAnimalIdx;
    u8* nowMax = &gCommonData.save.nowNpcMax;
    s32 i;

    animal = gCommonData.save.animals;
    sp20 = 1;
    priv = gCommonData.nowPrivate;
    if (mLd_PlayerManKindCheck() == 0) {
        if (arg1 == 1) {
            if (*removeAnimalIdx != 0xFF) {
                animal = &gCommonData.save.animals[*removeAnimalIdx];
                animal->unk_526 = 0;
                mNpc_CopyAnimalInfo(inAnimal, animal);
                func_800AADE8_jp(&animal->homeInfo);
                mNpc_ClearAnimalInfo(animal);
                *removeAnimalIdx = 0xFF;
                (*nowMax)--;
            }
        }
    } else {
        if ((mNpc_CheckFreeAnimalInfo(inAnimal) == FALSE) && (inAnimal->unk_526 == 0)) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (inAnimal->id.npcId == animal->id.npcId) {
                    sp20 = 0;
                    break;
                }
                animal++;
            }

            if (inAnimal->id.npcId == gCommonData.save.lastRemovedAnimalId.npcId) {
                sp20 = 0;
            }
        } else {
            sp20 = 0;
        }

        if (sp20 == 1) {
            animal = gCommonData.save.animals;
            freeAnimalIdx = mNpc_GetFreeAnimalInfo(gCommonData.save.animals, ANIMAL_NUM_MAX);
            if (freeAnimalIdx == -1) {
                animal += func_800ABF40_jp();
                func_800AADE8_jp(&animal->homeInfo);
                func_800AC1EC_jp(&B_80142F70_jp, animal);
                mNpc_SendRegisteredGoodbyMail();
            } else {
                animal += freeAnimalIdx;
                func_800A6940_jp(&gCommonData.save.nowNpcMax);
            }
            mNpc_ClearAnimalInfo(animal);
            mNpc_CopyAnimalInfo(animal, inAnimal);
            animal->homeInfo.blockX = 0xFF;
            animal->homeInfo.blockZ = 0xFF;
            animal->homeInfo.utX = 0xFF;
            animal->homeInfo.utZ = 0xFF;
            mLd_CopyLandName(animal->previousLandName, gCommonData.nowPrivate->playerId.landName);
            animal->unk_51C = gCommonData.nowPrivate->playerId.landId;
            func_800BA778_jp(&animal->contestQuest);
            inAnimal->unk_526 = 1;
            priv->animalMemory.npcId = animal->id.npcId;
            mLd_CopyLandName(priv->animalMemory.landName, func_800950D8_jp()->name);
            func_800AA2F8_jp(animal->id.npcId);
        }
    }
}

s32 func_800AC804_jp(s32 blockX, s32 blockZ, u8 utX, u8 utZ) {
    s32 res = FALSE;

    if ((blockX >= 0) && (blockX < 5) && (blockZ >= 0) && (blockZ < 6) && (utX < 0x10) && (utZ < 0x10)) {
        u16 item = gCommonData.save.fg[blockZ][blockX].items[utZ][utX];

        if ((item >= 0x5810) && (item < 0x5825)) {
            res = TRUE;
        }
    }
    return res;
}

void mNpc_SetReturnAnimal(Animal* animal) {
    AnmHome* homeInfo;
    Animal* foundAnimal = NULL;
    u8* nowMax = &gCommonData.save.nowNpcMax;
    Animal* commonAnimal;
    s32 foundAnimalIdx;

    if (mLd_PlayerManKindCheck() || mNpc_CheckFreeAnimalInfo(animal)) {
        return;
    }

    if (animal->unk_526 == 0) {
        commonAnimal = gCommonData.save.animals;
        foundAnimalIdx = mNpc_SearchAnimalinfo(commonAnimal, animal->id.npcId, ANIMAL_NUM_MAX);
        if (foundAnimalIdx != -1) {
            foundAnimal = &commonAnimal[foundAnimalIdx];
            func_800AADE8_jp(&foundAnimal->homeInfo);
            (*nowMax)--;
            if (foundAnimalIdx == gCommonData.save.removeAnimalIdx) {
                gCommonData.save.removeAnimalIdx = 0xFF;
            }
        } else if ((*nowMax) >= ANIMAL_NUM_MAX) {
            foundAnimalIdx = func_800ABF40_jp();
            foundAnimal = &commonAnimal[foundAnimalIdx];
            func_800AC1EC_jp(&B_80142F70_jp, foundAnimal);
            func_800AADE8_jp(&foundAnimal->homeInfo);
            (*nowMax)--;
            if (foundAnimalIdx == gCommonData.save.removeAnimalIdx) {
                gCommonData.save.removeAnimalIdx = 0xFF;
            }
        } else {
            foundAnimalIdx = mNpc_GetFreeAnimalInfo(commonAnimal, ANIMAL_NUM_MAX);
            if (foundAnimalIdx != -1) {
                foundAnimal = &commonAnimal[foundAnimalIdx];
            }
        }

        if (foundAnimal != NULL) {
            homeInfo = &foundAnimal->homeInfo;
            mNpc_ClearAnimalInfo(foundAnimal);
            mNpc_CopyAnimalInfo(foundAnimal, animal);
            if (func_800AC804_jp(foundAnimal->homeInfo.blockX - 1, foundAnimal->homeInfo.blockZ - 1,
                                 foundAnimal->homeInfo.utX, foundAnimal->homeInfo.utZ - 1) == TRUE) {
                func_800AAC88_jp(foundAnimal->id.npcId, homeInfo->blockX - 1, homeInfo->blockZ - 1, homeInfo->utX,
                                 homeInfo->utZ - 1);
            } else {
                homeInfo->blockX = 0xFF;
                homeInfo->blockZ = 0xFF;
                homeInfo->utX = 0xFF;
                homeInfo->utZ = 0xFF;
            }
            (*nowMax)++;
            if ((*nowMax) > ANIMAL_NUM_MAX) {
                (*nowMax) = ANIMAL_NUM_MAX;
            }
        }
    } else {
        mNpc_CopyAnimalPersonalID(&gCommonData.save.lastRemovedAnimalId, &animal->id);
    }
    mNpc_ClearAnimalInfo(animal);
}

void func_800ACB24_jp(FieldInfo_Unk_Struct* arg0, u8 arg1, u8 arg2) {
    func_800AB498_jp(arg0, arg1, arg2);
}

void func_800ACB54_jp(Animal* animal, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (animal != NULL) {
            if (ACTOR_FGNAME_GET_F000(animal->id.npcId) == FGNAME_F000_E) {
                animal->id.nameId = animal->id.npcId & 0xFF;
            }
        }
        animal++;
    }
}

void func_800ACC38_jp(u8* name, u8 npcId) {
    u8 sp28[PLAYER_NAME_LEN];
    s32 id = npcId;

    if (id < 0xFF) {
        DmaMgr_RequestSyncDebug(sp28, (RomOffset)((Struct_D_E04000*)SEGMENT_ROM_START(segment_00E04000))->unk_08[id], 8,
                                "../m_npc.c", 0x1916);
        mem_copy(name, sp28, PLAYER_NAME_LEN);
    }
}

void func_800ACCAC_jp(u8* name, u16 npcId) {
    u8* var_a2 = l_no_name_npc_name;
    u8 sp24[PLAYER_NAME_LEN];

    if (name != NULL) {
        u8 id = npcId & 0xFF;

        if ((ACTOR_FGNAME_GET_F000(npcId) == FGNAME_F000_E) && (id < 0xFF)) {
            func_800ACC38_jp(sp24, id);
            var_a2 = sp24;
        }
    }
    mPr_CopyPlayerName(name, var_a2);
}

void mNpc_GetNpcWorldNameAnm(u8* name, AnmPersonalId* anmId) {
    u8* var_a2 = l_no_name_npc_name;
    u8 sp1C[PLAYER_NAME_LEN];

    if (anmId != NULL) {
        if (ACTOR_FGNAME_GET_F000(anmId->npcId) == FGNAME_F000_E) {
            func_800ACCAC_jp(sp1C, anmId->npcId);
            var_a2 = sp1C;
        }
    }
    mPr_CopyPlayerName(name, var_a2);
}

void func_800ACD74_jp(u8* arg0, u16 name) {
    s32 i;
    Struct_D_8010B510_jp* var_v0 = D_8010B510_jp;
    u8* var_a3 = l_no_name_npc_name;

    for (i = 0; i < ARRAY_COUNT(D_8010B510_jp); i++) {
        if (name == var_v0->unk_00) {
            func_800C3F70_jp(B_80142F68_jp, PLAYER_NAME_LEN, var_v0->unk_04);
            var_a3 = B_80142F68_jp;
            break;
        }
        var_v0++;
    }

    mPr_CopyPlayerName(arg0, var_a3);
}

void func_800ACDF8_jp(u8* arg0, Npc* npc) {
    u8* var_a3 = l_no_name_npc_name;
    u8 sp1C[PLAYER_NAME_LEN];

    if ((arg0 != NULL) && (npc != NULL)) {
        if (npc->actor.part == ACTOR_PART_NPC) {
            if (npc->animal != NULL) {
                mNpc_GetNpcWorldNameAnm(sp1C, &npc->animal->id);
            } else {
                func_800ACD74_jp(sp1C, npc->actor.fgName);
            }
        } else {
            func_800ACD74_jp(sp1C, npc->actor.fgName);
        }
        var_a3 = sp1C;
    }
    mPr_CopyPlayerName(arg0, var_a3);
}

void func_800ACE90_jp(u8* arg0) {
    Animal* animal = gCommonData.save.animals;
    u16 var_s3 = 0;
    s32 var_s2 = 0;
    s32 rand;
    s32 i;

    if (arg0 != NULL) {

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                var_s2++;
                var_s3 |= (1 << i);
            }
            animal++;
        }

        if (var_s2 > 0) {
            animal = gCommonData.save.animals;
            rand = RANDOM(var_s2);

            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (((var_s3 >> i) & 1) == 1) {
                    if (rand == 0) {
                        mNpc_GetNpcWorldNameAnm(arg0, &animal->id);
                        break;
                    } else {
                        rand--;
                    }
                }
                animal++;
            }
        }
    }
}

void func_800ACF84_jp(u8* arg0, Vec3f arg1) {
    UNUSED s32 pad;
    Animal* animal = gCommonData.save.animals;
    s32 blockX;
    s32 blockZ;
    s32 utX;
    s32 utZ;
    AnmHome* homeInfo;
    s32 i;

    if (func_80088780_jp(&blockX, &blockZ, &utX, &utZ, arg1) == 1) {
        utX++;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                homeInfo = &animal->homeInfo;
                if ((blockX == homeInfo->blockX) && (blockZ == homeInfo->blockZ) && (utX == homeInfo->utX) &&
                    (utZ == homeInfo->utZ)) {
                    mNpc_GetNpcWorldNameAnm(arg0, &animal->id);
                    break;
                }
            }
            animal++;
        }
    }
}

s32 func_800AD084_jp(Actor* actor) {
    u8 looks = 2;

    if ((actor != NULL) && (actor->part == ACTOR_PART_NPC)) {
        Npc* npc = (Npc*)actor;

        if (npc->animal != NULL) {
            looks = npc->animal->id.looks;
        }
    }
    return looks;
}

s32 func_800AD0B8_jp(u16 name) {
    Struct_D_8010B510_jp* var_v0 = D_8010B510_jp;
    u16 var_v1 = 0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8010B510_jp); i++) {
        if (name == var_v0->unk_00) {
            var_v1 = var_v0->unk_02;
            break;
        }
        var_v0++;
    }

    return var_v1;
}

s32 func_800AD104_jp(s32 arg0) {
    s32 var_v1 = 2;

    if ((arg0 == 0) || (arg0 == 1) || (arg0 == 5)) {
        var_v1 = 1;
    } else if ((arg0 == 2) || (arg0 == 3) || (arg0 == 4)) {
        var_v1 = 0;
    }
    return var_v1;
}

s32 func_800AD154_jp(AnmPersonalId* anmId) {
    s32 var_v1 = 2;

    if (anmId != NULL) {
        var_v1 = func_800AD104_jp(anmId->looks);
    }
    return var_v1;
}

s32 func_800AD188_jp(Actor* actor) {
    s32 var_v1;

    if ((actor != NULL) && (actor->part == ACTOR_PART_NPC)) {
        Npc* npc = (Npc*)actor;

        var_v1 = func_800AD154_jp(&npc->animal->id);
    } else {
        var_v1 = func_800AD0B8_jp(actor->fgName);
    }
    return var_v1;
}

s32 func_800AD1E0_jp(u16 name) {
    Struct_D_8010B510_jp* var_a1 = D_8010B510_jp;
    s32 var_v1 = 2;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8010B510_jp); i++) {
        if (name == var_a1->unk_00) {
            var_v1 = var_a1->unk_08;
            break;
        }
        var_a1++;
    }

    return var_v1;
}

s32 func_800AD22C_jp(Actor* actor) {
    s32 var_v1 = 2;
    u8 var_v0;

    if (actor != NULL) {
        if (actor->part == ACTOR_PART_NPC) {
            Npc* npc = (Npc*)actor;

            if (npc->animal != NULL) {
                var_v0 = npc->animal->id.looks;
                if (var_v0 >= 6) {
                    var_v0 = 2;
                }
                var_v1 = spec_table[var_v0];
            } else {
                var_v1 = func_800AD1E0_jp(npc->actor.fgName);
            }
        } else {
            var_v1 = func_800AD1E0_jp(actor->fgName);
        }
    }
    return var_v1;
}

void func_800AD2B8_jp(UNUSED UNK_TYPE arg0) {
}

void mNpc_InitNpcAllInfo(s32 mallocFlag) {
    gCommonData.save.nowNpcMax = 6;
    gCommonData.save.removeAnimalIdx = 0xFF;
    mNpc_ClearAnimalPersonalID(&gCommonData.save.lastRemovedAnimalId);
    mNpc_ClearAnyAnimalInfo(gCommonData.save.animals, ANIMAL_NUM_MAX);
    func_800AA51C_jp(gCommonData.save.animals, 6, mallocFlag);
    func_800ACB54_jp(gCommonData.save.animals, ANIMAL_NUM_MAX);
}

s32 func_800AD338_jp(void) {
    s32 sp24 = func_80084DE0_jp();
    UNUSED s32 pad;
    s32 res = FALSE;

    if ((sp24 >= 0) && (sp24 < 7)) {
        if (RANDOM(100) < npc_grow_table[sp24]) {
            res = TRUE;
        }
    }
    return res;
}

s32 func_800AD3BC_jp(void) {
    UNUSED s32 pad[3];
    s32 res = FALSE;
    u32 var_v0;

    if (gCommonData.save.nowNpcMax < ANIMAL_NUM_MAX) {
        if (func_800D51E0_jp(&mTM_rtcTime_clear_code, &gCommonData.save.unk_0F7FC, 0x7F) == TRUE) {
            lbRTC_TimeCopy(&gCommonData.save.unk_0F7FC, &gCommonData.time.rtcTime);
        } else if (func_800AD338_jp() == TRUE) {
            if (func_800D52C0_jp(&gCommonData.save.unk_0F7FC, &gCommonData.time.rtcTime) == TRUE) {
                var_v0 = func_800D5480_jp(&gCommonData.time.rtcTime, &gCommonData.save.unk_0F7FC);
            } else {
                var_v0 = func_800D5480_jp(&gCommonData.save.unk_0F7FC, &gCommonData.time.rtcTime);
            }

            if ((var_v0 >= 0x5A0) && (mLd_PlayerManKindCheck() == FALSE) &&
                (func_800AB7D0_jp(gCommonData.nowPrivate) == TRUE)) {
                res = TRUE;
            }
        }
    }
    return res;
}

u8 func_800AD4B8_jp(u8* arg0, s32* arg1) {
    s32 temp_v0;
    s32 var_s3 = 0xF;
    u8 var_s5 = 6;
    u8 i;

    *arg0 = 0;
    *arg1 = 0;

    for (i = 0; i < 6; i++) {
        if (func_800AA3A4_jp(i) > 0) {
            temp_v0 = func_800A8148_jp(i);
            if (temp_v0 < var_s3) {
                *arg0 = 0;
                *arg0 |= (1 << i);
                var_s3 = temp_v0;
                var_s5 = i;
                *arg1 = 1;
            } else if (var_s3 == temp_v0) {
                *arg0 |= 1 << i;
                (*arg1)++;
            }
        }
    }

    if ((*arg0 == 0) && (*arg1 == 0)) {
        func_800AA438_jp(gCommonData.save.unk_0F86C, gCommonData.save.animals);

        for (i = 0; i < 6; i++) {
            *arg0 |= 1 << i;
            (*arg1)++;
        }
    }

    if (*arg1 >= 2) {
        var_s5 = 6;
    }
    return var_s5;
}

s32 func_800AD614_jp(void) {
    Animal* animal = gCommonData.save.animals;
    s32 i;
    s32 var_s2 = 0;
    s32 var_s3 = 0;
    s32 res;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            switch (func_800AD154_jp(&animal->id)) {
                case 0:
                    var_s2++;
                    break;
                case 1:
                    var_s3++;
                    break;
            }
        }
        animal++;
    }

    if (var_s3 < var_s2) {
        res = FALSE;
    } else {
        res = TRUE;
    }
    return res;
}

s32 func_800AD6D4_jp(u8 arg0) {
    UNUSED s32 pad[3];
    s32 sp40;
    u8* var_s2 = D_8010AF58_jp;
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    s32 var_s1;
    s32 var_v0;

    sp40 = -1;
    var_s1 = 0;

    if (arg0 < 6) {
        bzero(B_80142E58_jp, sizeof(B_80142E58_jp));

        for (i = 0; i < ARRAY_COUNT(B_80142E58_jp); i++) {
            for (j = 0; j < 8; j++) {
                if ((arg0 == *var_s2) &&
                    (mNpc_SearchAnimalinfo(gCommonData.save.animals, ((i * 8) + j) | 0xE000, 0xF) == -1) &&
                    (func_800AA35C_jp(var_s1) == FALSE)) {
                    var_s4++;
                    B_80142E58_jp[i] |= 1 << j;
                }
                var_s1++;
                var_s2++;
                if (var_s1 >= 0xD8) {
                    break;
                }
            }

            if (var_s1 >= 0xD8) {
                break;
            }
        }
    }

    if (var_s4 > 0) {
        var_s1 = 0;
        var_v0 = RANDOM(var_s4);

        for (i = 0; i < ARRAY_COUNT(B_80142E58_jp); i++) {
            if (var_s1 >= 0xD8) {
                break;
            }

            for (j = 0; j < 8; j++) {
                if (var_s1 >= 0xD8) {
                    break;
                }
                if (((B_80142E58_jp[i] >> j) & 1) == 1) {
                    if (var_v0 <= 0) {
                        sp40 = var_s1;
                        break;
                    } else {
                        var_v0--;
                    }
                }
                var_s1++;
            }

            if (sp40 != -1) {
                break;
            }
        }
    }
    return sp40;
}

void func_800AD8C4_jp(Animal* animal, s32 arg1) {
    if ((arg1 >= 0) && (arg1 < 0xD8)) {
        Struct_D_E03000* ptr = (Struct_D_E03000*)SEGMENT_ROM_START(segment_00E03000);

        DmaMgr_RequestSyncDebug(&B_80142E78_jp, (RomOffset)&ptr[arg1], 8, "../m_npc.c", 0x1CB3);
        func_800AA218_jp(animal, arg1 | 0xE000, D_8010AF58_jp[arg1], &B_80142E78_jp);
    }
}

s32 func_800AD954_jp(u8 arg0) {
    Animal* animal = gCommonData.save.animals;
    UNUSED s32 pad;
    s32 freeAnimalIdx;
    s32 temp_v0_2;

    freeAnimalIdx = mNpc_UseFreeAnimalInfo(animal, ANIMAL_NUM_MAX);
    if (freeAnimalIdx != -1) {
        animal += freeAnimalIdx;
        temp_v0_2 = func_800AD6D4_jp(arg0);
        if (temp_v0_2 != -1) {
            func_800AD8C4_jp(animal, temp_v0_2);
            animal->unk_525 = 1;
        } else {
            freeAnimalIdx = -1;
        }
    }
    return freeAnimalIdx;
}

void func_800AD9FC_jp(void) {
    u8 sp4F;
    u8 sp4E;
    s32 sp48;
    u8 sp47;
    s32 sp40;
    s32 temp_v0_2;
    s32 var_v0;
    u8 i;

    if (func_800AD3BC_jp() == TRUE) {
        func_800AA49C_jp();
        lbRTC_TimeCopy(&gCommonData.save.unk_0F7FC, &gCommonData.time.rtcTime);
        sp4F = func_800AD4B8_jp(&sp4E, &sp48);
        if (sp4F == 6) {
            temp_v0_2 = func_800AD614_jp();
            if (temp_v0_2 != 2) {
                sp47 = sp4E;
                sp40 = sp48;

                for (i = 0; i < 6; i++) {
                    if ((((sp4E >> i) & 1) == 1) && (func_800AD104_jp(i) != temp_v0_2)) {
                        sp4E &= ~(1 << i);
                        sp48--;
                    }
                }

                if ((sp48 == 0) || (sp48 == sp40)) {
                    sp4E = sp47;
                    sp48 = sp40;
                }
            }

            var_v0 = RANDOM(sp48);
            for (i = 0; i < 6; i++) {
                if (((sp4E >> i) & 1) == 1) {
                    if (var_v0 <= 0) {
                        sp4F = i;
                        break;
                    } else {
                        var_v0--;
                    }
                }
            }
        }

        temp_v0_2 = func_800AD954_jp(sp4F);
        if ((temp_v0_2 >= 0) && (temp_v0_2 < ANIMAL_NUM_MAX)) {
            func_800ACB54_jp(&gCommonData.save.animals[temp_v0_2], 1);
            func_800A6940_jp(&gCommonData.save.nowNpcMax);
        }
    }
}

s32 func_800ADBE4_jp(u16 arg0, s32 arg1) {
    s32 res = FALSE;

    if (func_8008D7B0_jp(arg0)) {
        res = func_8007244C_jp(arg1);
    }
    return res;
}

s32 func_800ADC28_jp(u16 arg0, u32 arg1) {
    s32 res = FALSE;

    if (func_8008D7B0_jp(arg0) && ((arg1 < 3) || ((arg1 >= 4) && (arg1 < 7)) || (arg1 == 7))) {
        res = TRUE;
    }
    return res;
}

s32 func_800ADC8C_jp(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32* sp1C = func_80089538_jp(arg0, arg1);
    u16* temp_a2 = func_8008A33C_jp(arg0, arg1);
    s32 res = FALSE;

    if ((sp1C != NULL) && (temp_a2 != NULL)) {
        res = func_800ADBE4_jp(temp_a2[arg3 * 16 + arg2], sp1C[arg3 * 16 + arg2] & 0x3F);
    }
    return res;
}

#ifdef NON_MATCHING
s32 func_800ADD20_jp(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32* sp5C;
    u16* sp58;
    s32 res;
    s32 var_a0;
    s32 var_a1;
    s32 var_s5;
    s32 var_s6;
    u32 temp_v0_3;
    s32 i;
    s32 j;
    u32* temp_v1;
    u16* temp_v2;

    sp5C = func_80089538_jp(arg2, arg3);
    sp58 = func_8008A33C_jp(arg2, arg3);
    var_s5 = 0x10;
    var_s6 = 0x10;
    res = FALSE;
    if ((arg4 < 0) || (arg4 >= 10)) {
        return 0;
    }

    if ((sp58 != NULL) && (sp5C != NULL)) {
        for (i = 0; i < 16 - arg4; i++) {
            temp_v2 = &sp58[i * 16];
            temp_v1 = &sp5C[i * 16];
            for (j = 0; j < 16 - arg4; j++) {
                if (func_800ADC28_jp(temp_v2[0], temp_v1[0] & 0x3F) == 1) {
                    temp_v0_3 = (temp_v1[0] * 2) >> 0x1B;
                    if ((temp_v0_3 == ((temp_v1[0] << 6) >> 0x1B)) && (temp_v0_3 == (*(u16*)temp_v1 & 0x1F)) &&
                        (temp_v0_3 == (*((u16*)temp_v1 + 1) >> 0xB))) {

                        if (temp_v0_3 == ((temp_v1[0] << 0x15) >> 0x1B)) {
                            var_a0 = 8 - j;
                            if (var_a0 < 0) {
                                var_a0 = -var_a0;
                            }

                            var_a1 = 8 - i;
                            if (var_a1 < 0) {
                                var_a1 = -var_a1;
                            }

                            if ((var_a0 < var_s5) && (var_a1 < var_s6)) {
                                *arg0 = j;
                                *arg1 = i;
                                var_s5 = var_a0;
                                var_s6 = var_a1;
                                res = TRUE;
                            }
                        }
                    }
                }
                temp_v2++;
                temp_v1++;
            }
        }
    }
    return res;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_npc/func_800ADD20_jp.s")
#endif

s32 func_800ADEFC_jp(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_s4;
    u32* sp58;
    u16* sp54;
    s32 i;
    s32 j;
    s32 rand;
    s32 res;
    u16* var_s6 = B_80142EB8_jp;

    sp58 = func_80089538_jp(arg2, arg3);
    sp54 = func_8008A33C_jp(arg2, arg3);
    var_s4 = 0;
    res = 0;

    if ((arg4 < 0) || (arg4 >= 0xA)) {
        return FALSE;
    }

    bzero(B_80142EB8_jp, sizeof(B_80142EB8_jp));

    if ((sp54 != NULL) && (sp58 != 0)) {
        for (i = arg4; i < 16 - arg4; i++) {
            for (j = arg4; j < 16 - arg4; j++) {
                if (func_800ADBE4_jp(sp54[i * 16 + j], sp58[i * 16 + j] & 0x3F) == TRUE) {
                    *var_s6 |= 1 << j;
                    var_s4++;
                }
            }
            var_s6++;
        }

        var_s6 = B_80142EB8_jp;
    }

    if (var_s4 > 0) {
        rand = RANDOM(var_s4);

        for (i = arg4; i < 16 - arg4; i++) {
            for (j = arg4; j < 16 - arg4; j++) {
                if (((*var_s6 >> j) & 1) == 1) {
                    if (rand == 0) {
                        *arg0 = j;
                        *arg1 = i;
                        res = TRUE;
                        break;
                    } else {
                        rand--;
                    }
                }
            }
            if (res == TRUE) {
                break;
            }
            var_s6++;
        }
    }
    return res;
}

void func_800AE110_jp(s32* arg0, s32* arg1, s32 arg2, s32 arg3) {
    func_800ADEFC_jp(arg0, arg1, arg2, arg3, 1);
}

void mNpc_ClearTalkInfo(void) {
    s32 i;
    Struct_B_80142ED8_jp* ptr = B_80142ED8_jp;

    bzero(B_80142ED8_jp, sizeof(B_80142ED8_jp));

    for (i = 0; i < ANIMAL_NUM_MAX; i++, ptr++) {
        ptr->unk_03 = 1;
    }
}

void func_800AE1A0_jp(Struct_B_80142ED8_jp* arg0) {
    if (arg0->unk_00 > 0) {
        arg0->unk_00--;
    }
}

#ifdef NON_MATCHING
void func_800AE1B8_jp(u16* arg0, u16* arg1, s32 arg2) {
    *arg0 = l_npc_temper[arg2].unk_00;
    *arg1 = l_npc_temper[arg2].unk_00;
}
#else
void func_800AE1B8_jp(u16* arg0, u16* arg1, s32 arg2);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_npc/func_800AE1B8_jp.s")
#endif

s32 func_800AE1D8_jp(s32 arg0, s32 arg1) {
    s32 res = FALSE;

    if (arg0 != -1) {
        if ((B_80142ED8_jp[arg0].unk_02 < l_npc_temper[arg1].unk_03) && (B_80142ED8_jp[arg0].unk_00 > 0)) {
            B_80142ED8_jp[arg0].unk_02++;
            res = TRUE;
        }
    }
    return res;
}

s32 func_800AE23C_jp(s32 arg0, s32 arg1) {
    s32 res = FALSE;

    if (arg0 != -1 && B_80142ED8_jp[arg0].unk_02 >= l_npc_temper[arg1].unk_02) {
        res = TRUE;
    }
    return res;
}

s32 func_800AE284_jp(s32 arg0, s32 arg1) {
    s32 var_v1 = 2;

    if (arg0 != -1) {
        if (B_80142ED8_jp[arg0].unk_02 >= l_npc_temper[arg1].unk_02) {
            if (B_80142ED8_jp[arg0].unk_02 >= l_npc_temper[arg1].unk_03) {
                var_v1 = 1;
            } else {
                var_v1 = 0;
            }
        }
    }
    return var_v1;
}

s32 func_800AE2E8_jp(s32 arg0) {
    s32 res = FALSE;

    if ((arg0 != -1) && (B_80142ED8_jp[arg0].unk_03 == 1)) {
        res = TRUE;
    }
    return res;
}

void func_800AE320_jp(s32 arg0, s32 arg1) {
    UNUSED s32 pad;

    if ((arg0 >= 0) && (arg0 < ANIMAL_NUM_MAX)) {
        if (B_80142ED8_jp[arg0].unk_03 == 1) {
            func_800AE1B8_jp(&B_80142ED8_jp[arg0].unk_04, &B_80142ED8_jp[arg0].unk_06, arg1);
        }
        B_80142ED8_jp[arg0].unk_03 = 0;
    }
}

void func_800AE37C_jp(Struct_B_80142ED8_jp* arg0) {
    if (arg0 != NULL) {
        if ((arg0->unk_04 > 0) && ((arg0->unk_06 - 1000) < arg0->unk_04)) {
            arg0->unk_04--;
        }
    }
}

void func_800AE3B4_jp(void) {
    Struct_B_80142ED8_jp* var_s0;
    s32 i;

    var_s0 = B_80142ED8_jp;
    if (func_8008C0FC_jp(1) == 1) {
        for (i = 0; i < ARRAY_COUNT(B_80142ED8_jp); i++) {
            var_s0->unk_06 = var_s0->unk_04;
            var_s0++;
        }
    }

    var_s0 = B_80142ED8_jp;
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        func_800AE1A0_jp(var_s0);
        func_800AE37C_jp(var_s0);
        if ((var_s0->unk_04 == 0) && (var_s0->unk_06 != 0)) {
            var_s0->unk_02 = 0;
            var_s0->unk_03 = 1;
            var_s0->unk_06 = 0;
        }
        var_s0++;
    }
}

void func_800AE4B4_jp(s32 arg0, s32 arg1) {
    UNUSED s32 pad;
    Struct_B_80142ED8_jp* sp1C;

    if ((arg0 >= 0) && (arg0 < ANIMAL_NUM_MAX) && (arg1 >= 0) && (arg1 < 6)) {
        sp1C = &B_80142ED8_jp[arg0];
        sp1C->unk_00 = 1000;
        if (func_800AE1D8_jp(arg0, arg1) == TRUE) {
            if (func_800AE23C_jp(arg0, arg1) == TRUE) {
                func_800AE1B8_jp(&sp1C->unk_04, &sp1C->unk_06, arg1);
            }
        }
    }
}

s32 func_800AE558_jp(void) {
    u16 fieldId = mFI_GetFieldId();
    u16 houseOwnerName = gCommonData.houseOwnerName;
    s32 floorId = -1;

    if ((mNpc_GET_TYPE(fieldId) == 0x4000) && (houseOwnerName != 0) && (houseOwnerName != 0xFFFF)) {
        s32 idx = mNpc_SearchAnimalinfo(gCommonData.save.animals, houseOwnerName, ANIMAL_NUM_MAX);

        floorId = gCommonData.npcList[idx].houseData.floorId;
    }
    return floorId;
}

void func_800AE5C8_jp(void) {
    if (gCommonData.unk_10A38 != 1) {
        Animal* animal = gCommonData.save.animals;
        NpcList* npcList = gCommonData.npcList;
        s32 i;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                npcList->flags.unk_23 = TRUE;
            }
            animal++;
            npcList++;
        }
    }
}

u8 func_800AE64C_jp(NpcList* npcList) {
    u8 res = TRUE;

    if (npcList != NULL) {
        res = npcList->flags.unk_22;
    }
    return res;
}

u8 func_800AE670_jp(NpcList* npcList) {
    u8 res = TRUE;

    if (npcList != NULL) {
        res = npcList->flags.unk_21;
    }
    return res;
}

void func_800AE694_jp(NpcList* npcList) {
    if (npcList != NULL) {
        npcList->flags.unk_22 = TRUE;
    }
}

void func_800AE6B0_jp(NpcList* npcList) {
    if (npcList != NULL) {
        npcList->flags.unk_21 = TRUE;
    }
}

void func_800AE6CC_jp(void) {
    Animal* animal = gCommonData.save.animals;
    NpcList* npcList = gCommonData.npcList;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            npcList->homePosition.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(npcList->homePosition, 0.0f);
        }
        animal++;
        npcList++;
    }
}

void func_800AE76C_jp(gfxprint* print) {
    Animal* sp34 = NULL;
    Animal* sp30 = mNpc_GetInAnimalP();
    u8 sp2F = gCommonData.save.removeAnimalIdx;

    gfxprint_color(print, 200, 150, 50, 255);
    gfxprint_locate8x8(print, 3, 0xA);
    if (sp2F < ANIMAL_NUM_MAX) {
        sp34 = &gCommonData.save.animals[sp2F];
    }

    if (sp34 != NULL) {
        if (sp30 != NULL) {
            gfxprint_printf(print, "%4x %3d %3d", sp2F, sp34->id.nameId, sp30->id.nameId);
        } else {
            gfxprint_printf(print, "%4x %3d ---", sp2F, sp34->id.nameId);
        }
    } else if (sp30 != NULL) {
        gfxprint_printf(print, "%4x --- %3d", sp2F, sp30->id.nameId);
    } else {
        gfxprint_printf(print, "%4x --- ---", sp2F);
    }
}

void func_800AE898_jp(AnmPersonalId* anmId) {
    if (anmId != NULL) {
        D_8010B968_jp = func_800A7D08_jp(anmId);
    }
}

void mNpc_PrintFriendship_fdebug(gfxprint* gfxprint) {
    AnmMemory* memory;
    Private* priv;
    s32 i;
    s32 var_s2 = 3;
    s32 var_s4 = 19;

    if ((D_8010B968_jp >= 0) && (D_8010B968_jp < ANIMAL_NUM_MAX)) {
        memory = gCommonData.save.animals[D_8010B968_jp].memories;
        if (memory != NULL) {
            gfxprint_color(gfxprint, 250, 100, 170, 255);
            gfxprint_locate8x8(gfxprint, 3, 0x12);
            priv = gCommonData.nowPrivate;
            if (priv != NULL) {
                gfxprint_printf(gfxprint, "%4x ", priv->playerId.playerId);
            } else {
                gfxprint_printf(gfxprint, "**** ");
            }
            gfxprint_color(gfxprint, 50, 150, 50, 255);

            for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
                if (i == 4) {
                    var_s4++;
                    var_s2 = 3;
                }
                gfxprint_locate8x8(gfxprint, var_s2, var_s4);
                if (func_800A6E0C_jp(&memory->memoryPlayerId) == FALSE) {
                    gfxprint_printf(gfxprint, "%4x %3d ", memory->memoryPlayerId.playerId, memory->info.friendship);
                } else {
                    gfxprint_printf(gfxprint, "**** *** ");
                }
                memory++;
                var_s2 += 9;
            }
        }
    }
}
