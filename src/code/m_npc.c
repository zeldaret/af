#include "m_npc.h"
#include "macros.h"
#include "m_lib.h"
#include "m_land.h"
#include "m_time.h"
#include "m_field_info.h"
#include "m_mail_check.h"
#include "6E30B0.h"
#include "6E7AD0.h"
#include "m_handbill.h"
#include "m_std_dma.h"
#include "6DA460.h"
#include "m_house.h"
#include "m_malloc.h"
#include "segment_symbols.h"
#include "m_item_name.h"
#include "m_name_table.h"
#include "m_police_box.h"
#include "6A5B00.h"
#include "6A83A0.h"

SpecialNpcData l_sp_actor_name[] = {
    { 0xD008, NPC_SEX_MALE, 0x0205, 2 },   { 0xD01E, NPC_SEX_MALE, 0x0205, 2 },   { 0xD03A, NPC_SEX_MALE, 0x0205, 2 },
    { 0xD03B, NPC_SEX_MALE, 0x0205, 2 },   { 0xD03C, NPC_SEX_MALE, 0x0205, 2 },   { 0xD009, NPC_SEX_MALE, 0x0205, 2 },
    { 0xD00A, NPC_SEX_MALE, 0x0205, 2 },   { 0xD00B, NPC_SEX_MALE, 0x0205, 2 },   { 0xD014, NPC_SEX_MALE, 0x0205, 2 },
    { 0xD019, NPC_SEX_MALE, 0x0205, 2 },   { 0xD015, NPC_SEX_MALE, 0x0205, 2 },   { 0xD01A, NPC_SEX_MALE, 0x0205, 2 },
    { 0xD016, NPC_SEX_MALE, 0x0205, 2 },   { 0xD01B, NPC_SEX_MALE, 0x0205, 2 },   { 0xD017, NPC_SEX_MALE, 0x0205, 2 },
    { 0xD01C, NPC_SEX_MALE, 0x0205, 2 },   { 0xD001, NPC_SEX_MALE, 0x0206, 2 },   { 0xD013, NPC_SEX_MALE, 0x0206, 2 },
    { 0xD02C, NPC_SEX_MALE, 0x0206, 2 },   { 0xD039, NPC_SEX_MALE, 0x0206, 2 },   { 0xD00C, NPC_SEX_FEMALE, 0x0207, 2 },
    { 0xD03D, NPC_SEX_FEMALE, 0x0207, 2 }, { 0xD006, NPC_SEX_MALE, 0x0208, 2 },   { 0xD000, NPC_SEX_MALE, 0x0209, 3 },
    { 0xD00F, NPC_SEX_MALE, 0x020A, 2 },   { 0xD002, NPC_SEX_MALE, 0x020B, 2 },   { 0xD007, NPC_SEX_FEMALE, 0x020C, 8 },
    { 0xD003, NPC_SEX_FEMALE, 0x020D, 4 }, { 0xD012, NPC_SEX_FEMALE, 0x020E, 4 }, { 0xD011, NPC_SEX_MALE, 0x020F, 3 },
    { 0xD00D, NPC_SEX_MALE, 0x0210, 2 },   { 0xD010, NPC_SEX_MALE, 0x0210, 3 },   { 0xD04E, NPC_SEX_MALE, 0x0210, 2 },
    { 0xD00E, NPC_SEX_MALE, 0x0211, 2 },   { 0xD025, NPC_SEX_MALE, 0x0212, 3 },   { 0xA004, NPC_SEX_OTHER, 0x0213, 2 },
    { 0xA005, NPC_SEX_OTHER, 0x0213, 2 },  { 0xA006, NPC_SEX_OTHER, 0x0213, 2 },  { 0xA007, NPC_SEX_OTHER, 0x0213, 2 },
    { 0xD018, NPC_SEX_OTHER, 0x0214, 2 },  { 0xD05D, NPC_SEX_OTHER, 0x0214, 2 },  { 0xD066, NPC_SEX_OTHER, 0x0214, 2 },
    { 0xD004, NPC_SEX_MALE, 0x0215, 2 },   { 0xD005, NPC_SEX_MALE, 0x0215, 2 },   { 0xD01D, NPC_SEX_MALE, 0x0216, 2 },
    { 0xD026, NPC_SEX_MALE, 0x0217, 2 },   { 0xD037, NPC_SEX_MALE, 0x0218, 2 },   { 0xD03E, NPC_SEX_MALE, 0x04E0, 2 },
    { 0xD065, NPC_SEX_MALE, 0x04E0, 2 },   { 0xD068, NPC_SEX_MALE, 0x04E0, 2 },   { 0xD069, NPC_SEX_MALE, 0x04E0, 2 },
    { 0xD06B, NPC_SEX_MALE, 0x04E0, 2 },   { 0xD064, NPC_SEX_MALE, 0x04E1, 2 },   { 0x800D, NPC_SEX_MALE, 0x04E2, 2 },
    { 0x800E, NPC_SEX_MALE, 0x04E2, 2 },   { 0xA008, NPC_SEX_MALE, 0x04E2, 2 },   { 0xA009, NPC_SEX_MALE, 0x04E2, 2 },
    { 0xA00A, NPC_SEX_MALE, 0x04E2, 2 },   { 0xA00B, NPC_SEX_MALE, 0x04E2, 2 },   { 0xA00C, NPC_SEX_MALE, 0x04E2, 2 },
    { 0xA00D, NPC_SEX_MALE, 0x04E2, 2 },   { 0xA00E, NPC_SEX_MALE, 0x04E2, 2 },   { 0xA00F, NPC_SEX_MALE, 0x04E2, 2 },
    { 0xA010, NPC_SEX_MALE, 0x04E2, 2 },
};
char l_no_name_npc_name[ANIMAL_NAME_LEN] = { 0xD4, 0x8E, 0xA6, 0x90, 0x85, 0x42 };
char l_no_ending_npc_ending[ANIMAL_CATCHPHRASE_LEN] = { 0xD3, 0xAF, 0x9D, 0x20 };

s32 fake_table[60];
u8 Handbillz_tmp_super[MAIL_HEADER2_LEN];
Anmhome_c reserved[60];
u8 Handbillz_tmp_ps[MAIL_FOOTER2_LEN];
u8 candidate_table[27];
static u32 bssPad;
NpcDefaultData npc_def_list;
u8 Remail_tmp_super[MAIL_HEADER2_LEN];
u8 Remail_tmp_ps[MAIL_FOOTER2_LEN];
u16 fg_flag[UT_Z_NUM];
NpcTalkInfo l_npc_talk_info[ANIMAL_NUM_MAX];
char Event_animal_name[ANIMAL_NAME_LEN];
char Birthday_animal_name[ANIMAL_NAME_LEN];
char Goodby_animal_name[ANIMAL_NAME_LEN];
char load_name[ANIMAL_NAME_LEN];
AnmGoodbyeMail l_mnpc_goodby_mail;
Mail_c l_npc_mail;
s32 fakeTable[NPC_NUM];
Animal_c l_mnpc_remove_in_animal;

void mNpc_MakeRandTable(s32* table, s32 count, s32 swapNum) {
    s32 b;
    s32 i;

    for (i = 0; i < count; i++) {
        table[i] = i;
    }

    while (swapNum--) {
        s32 temp;

        i = RANDOM(count);
        b = RANDOM(count);
        temp = table[i];

        table[i] = table[b];
        table[b] = temp;
    }
}

void mNpc_ClearBufSpace1(u8* buf, s32 size) {
    mem_clear(buf, size, 0x20);
}

void mNpc_AddNowNpcMax(u8* npcMax) {
    if (npcMax[0] < ANIMAL_NUM_MAX) {
        npcMax[0]++;
    }
}

void mNpc_SubNowNpcMax(u8* npcMax) {
    if (npcMax[0] > ANIMAL_NUM_MIN) {
        npcMax[0]--;
    }
}

void mNpc_ClearAnimalPersonalID(AnmPersonalID_c* pid) {
    pid->npcId = 0;
    pid->nameId = 0xFF;
    pid->landId = 0xFFFF;
    pid->looks = 6;
    mNPS_reset_schedule_area(pid);
    mLd_ClearLandName(pid->landName);
}

s32 mNpc_CheckFreeAnimalPersonalID(AnmPersonalID_c* pid) {
    s32 res = FALSE;

    if ((pid->npcId == 0 && pid->nameId == 0xFF) || (ACTOR_FGNAME_GET_F000(pid->npcId) != FGNAME_F000_E)) {
        res = TRUE;
    }

    return res;
}

void mNpc_CopyAnimalPersonalID(AnmPersonalID_c* dst, AnmPersonalID_c* src) {
    if ((src != NULL) && (ACTOR_FGNAME_GET_F000(src->npcId) == FGNAME_F000_E)) {
        dst->npcId = src->npcId;
        dst->nameId = src->nameId;
        dst->landId = src->landId;
        dst->looks = src->looks;
        mLd_CopyLandName(dst->landName, src->landName);
    }
}

s32 mNpc_CheckCmpAnimalPersonalID(AnmPersonalID_c* id0, AnmPersonalID_c* id1) {
    s32 res = FALSE;

    if ((id0 != NULL) && (id1 != NULL) && (id0->npcId == id1->npcId) && (id0->nameId == id1->nameId) &&
        (id0->landId == id1->landId)) {
        if (mLd_CheckCmpLandName(id0->landName, id1->landName) == TRUE) {
            res = TRUE;
        }
    }
    return res;
}

s32 mNpc_GetAnimalNum() {
    Animal_c* animal = common_data.animals;
    s32 num = 0;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            num++;
        }

        animal++;
    }

    return num;
}

s32 mNpc_CheckRemoveExp(Animal_c* animal) {
    s32 res = (animal->removeInfo >> 13) & 7;

    return res;
}

s32 mNpc_GetRemoveTime(Animal_c* animal) {
    s32 res = animal->removeInfo & 0x1FFF;

    return res;
}

void mNpc_AddRemoveTime(Animal_c* animal) {
    if ((animal->removeInfo & 0x1FFF) < 0x1FFF) {
        animal->removeInfo++;
    }
}

void mNpc_SetRemoveExp(Animal_c* animal, u16 removeExp) {
    animal->removeInfo = ((((animal->removeInfo >> 13) & 7) >> 13) | removeExp) << 13;
}

void mNpc_SetParentName(Animal_c* animal, PersonalID_c* parentId) {
    if ((parentId != NULL && mPr_NullCheckPersonalID(parentId) == FALSE) &&
        (mPr_NullCheckPlayerName(animal->parentName) == TRUE)) {
        mPr_CopyPlayerName(animal->parentName, parentId->playerName);
    }
}

void mNpc_SetParentNameAllAnimal() {
    Animal_c* animal = common_data.animals;
    PrivateInfo* priv = common_data.privateInfo;
    s32 i;

    if (priv != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            mNpc_SetParentName(animal, &priv->playerId);
            animal++;
        }
    }
}

void mNpc_ClearAnimalMail(Anmplmail_c* mail) {
    mail->font = 0xFF;
    mail->paperType = 0;
    mail->present = 0;
    mem_clear(mail->body, sizeof(mail->body), 0x20);
    mail->date.year = mTM_rtcTime_ymd_clear_code.year;
    mail->date.month = mTM_rtcTime_ymd_clear_code.month;
    mail->date.day = mTM_rtcTime_ymd_clear_code.day;
}

void mNpc_CopyAnimalMail(Anmplmail_c* dst, Anmplmail_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(Anmplmail_c));
}

void mNpc_ClearAnimalMemory(Anmmem_c* memory, s32 num) {
    for (; num != 0; num--) {
        if (memory != NULL) {
            mPr_ClearPersonalID(&memory->memoryPlayerId);
            lbRTC_TimeCopy(&memory->lastSpeakTime, &mTM_rtcTime_clear_code);
            mLd_ClearLandName(memory->land.name);
            memory->land.id = 0;
            memory->savedTownTune = 0;
            memory->friendship = 0;
            memory->letterInfo.exists = FALSE;
            memory->letterInfo.cond = 0;
            memory->letterInfo.sendReply = FALSE;
            mNpc_ClearAnimalMail(&memory->letter);
        }

        memory++;
    }
}

void mNpc_CopyAnimalMemory(Anmmem_c* dst, Anmmem_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(Anmmem_c));
}

void mNpc_AddFriendship(Anmmem_c* memory, s32 amount) {
    s32 friendship = memory->friendship + amount;

    if (memory == NULL) {
        return;
    }

    if (friendship > 127) {
        memory->friendship = 127;
    } else if (friendship < 0) {
        memory->friendship = 0;
    } else {
        memory->friendship = friendship;
    }
}

s32 mNpc_CheckFreeAnimalMemory(Anmmem_c* memory) {
    s32 res = FALSE;

    if (mPr_NullCheckPersonalID(&memory->memoryPlayerId) == TRUE) {
        res = TRUE;
    }

    return res;
}

void mNpc_RenewalAnimalMemory() {
    PrivateInfo* priv;
    Animal_c* animal = common_data.animals;
    Anmmem_c* memory;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        memory = animal->memories;

        for (j = 0; j < ANIMAL_MEMORY_NUM; j++) {
            if (mNpc_CheckFreeAnimalMemory(memory) == FALSE &&
                mLd_CheckThisLand(memory->memoryPlayerId.landName, memory->memoryPlayerId.landId) == TRUE) {
                priv = common_data.saveFilePrivateInfo;

                for (k = 0; k < PLAYER_NUM; k++) {
                    if (mPr_NullCheckPersonalID(&priv->playerId) == FALSE &&
                        mPr_CheckCmpPersonalID(&priv->playerId, &memory->memoryPlayerId) == TRUE) {
                        break;
                    }

                    priv++;
                }

                if (k == PLAYER_NUM) {
                    mNpc_ClearAnimalMemory(memory, 1);
                }
            }
            memory++;
        }
        animal++;
    }
}

s32 mNpc_GetOldAnimalMemoryIdx(Anmmem_c* memory, s32 num) {
    lbRTC_time_c oldest;
    s32 res;
    s32 i;

    lbRTC_TimeCopy(&oldest, &mTM_rtcTime_clear_code);
    res = 0;

    for (i = 0; i < num; i++) {
        if (lbRTC_IsOverTime(&oldest, &memory->lastSpeakTime) == lbRTC_LESS) {
            res = i;
            lbRTC_TimeCopy(&oldest, &memory->lastSpeakTime);
        }

        memory++;
    }

    return res;
}

s32 mNpc_GetFreeAnimalMemoryIdx(Anmmem_c* memory, s32 num) {
    s32 res = -1;
    s32 i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == TRUE) {
            res = i;
            break;
        }

        memory++;
    }

    return res;
}

s32 mNpc_ForceGetFreeAnimalMemoryIdx(Anmmem_c* memory, s32 num) {
    Anmmem_c* chosenMem = NULL;
    s32 freeId = mNpc_GetFreeAnimalMemoryIdx(memory, num);
    s32 i;

    if (freeId == -1) {
        for (i = 0; i < num; i++) {
            if (mLd_CheckThisLand(memory->memoryPlayerId.landName, memory->memoryPlayerId.landId) == 0) {
                if (chosenMem != NULL) {
                    if (chosenMem->letterInfo.exists == memory->letterInfo.exists) {
                        if (memory->friendship < chosenMem->friendship) {
                            chosenMem = memory;
                            freeId = i;
                        } else if ((chosenMem->friendship == memory->friendship) &&
                                   (lbRTC_IsOverTime(&chosenMem->lastSpeakTime, &memory->lastSpeakTime) == -1)) {
                            chosenMem = memory;
                            freeId = i;
                        }
                    } else if (memory->letterInfo.exists == FALSE) {
                        chosenMem = memory;
                        freeId = i;
                    }
                } else {
                    chosenMem = memory;
                    freeId = i;
                }
            }
            memory++;
        }
    } else {
        chosenMem = &memory[freeId];
    }
    mNpc_ClearAnimalMemory(chosenMem, 1);
    return freeId;
}

void mNpc_SetAnimalMemory_NotSetDay(PersonalID_c* pid, Anmmem_c* memory) {
    if (memory != NULL) {
        mNpc_ClearAnimalMemory(memory, 1);
        mPr_CopyPersonalID(&memory->memoryPlayerId, pid);
        memory->friendship = 1;
    }
}

void mNpc_SetAnimalMemory(PersonalID_c* pid, Anmmem_c* memory) {
    lbRTC_time_c* rtcTime = &common_data.time.rtcTime;

    if (memory != NULL) {
        mNpc_SetAnimalMemory_NotSetDay(pid, memory);
        lbRTC_TimeCopy(&memory->lastSpeakTime, rtcTime);
    }
}

s32 mNpc_GetAnimalMemoryIdx(PersonalID_c* pid, Anmmem_c* memory, s32 num) {
    s32 res = -1;
    s32 i;

    for (i = 0; i < num; i++) {
        if (mPr_CheckCmpPersonalID(&memory->memoryPlayerId, pid) == TRUE) {
            res = i;
            break;
        }
        memory++;
    }

    return res;
}

void mNpc_SetAnimalLastTalk(Animal_c* animal) {
    PrivateInfo* priv;
    Anmmem_c* memory = NULL;
    s32 memoryIdx;

    if ((&common_data.privateInfo->playerId != NULL) && (animal != NULL)) {
        priv = common_data.privateInfo;
        memoryIdx = mNpc_GetAnimalMemoryIdx(&priv->playerId, animal->memories, ANIMAL_MEMORY_NUM);

        if (memoryIdx != -1) {
            memory = &animal->memories[memoryIdx];
        } else {
            memoryIdx = mNpc_ForceGetFreeAnimalMemoryIdx(animal->memories, ANIMAL_MEMORY_NUM);

            if (memoryIdx != -1) {
                memory = &animal->memories[memoryIdx];
                mNpc_SetAnimalMemory(&priv->playerId, memory);
            }
        }

        if (memory != NULL) {
            lbRTC_TimeCopy(&memory->lastSpeakTime, &common_data.time.rtcTime);
            mLd_CopyLandName(memory->land.name, common_data.landInfo.name);
            memory->land.id = common_data.landInfo.id;
            memory->savedTownTune = common_data.melody;
        }
    }
}

void mNpc_SetAnimalPersonalID2Memory(AnmPersonalID_c* anmId) {
    PrivateInfo* priv = priv = common_data.privateInfo;
    Animal_c* animal;
    s32 id;

    if (priv != NULL) {
        id = mNpc_SearchAnimalPersonalID(anmId);

        if (id != -1) {
            animal = &common_data.animals[id];
            id = mNpc_GetAnimalMemoryIdx(&priv->playerId, animal->memories, ANIMAL_MEMORY_NUM);

            if (id == -1) {
                id = mNpc_ForceGetFreeAnimalMemoryIdx(animal->memories, ANIMAL_MEMORY_NUM);

                if (id != -1) {
                    mNpc_SetAnimalMemory_NotSetDay(&priv->playerId, animal->memories + id);
                }
            }
        }
    }
}

s32 mNpc_GetHighestFriendshipIdx(Anmmem_c* memory, s32 num) {
    s8 max = 0;
    s32 res = -1;
    s32 i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
            if (max <= memory->friendship) {
                max = memory->friendship;
                res = i;
            }
        }
        memory++;
    }

    return res;
}

s32 mNpc_SelectBestFriend(Anmmem_c** bestFriendMem, Anmmem_c* memory, s8* bestFriendFriendShip) {
    s32 res = FALSE;
    Anmmem_c* bestFriend;

    if (memory->friendship > bestFriendFriendShip[0]) {
        bestFriendFriendShip[0] = memory->friendship;
        bestFriendMem[0] = memory;
        res = TRUE;
    } else if (memory->friendship == bestFriendFriendShip[0]) {
        bestFriend = bestFriendMem[0];

        if (bestFriend != NULL) {
            if (bestFriend->letterInfo.exists == memory->letterInfo.exists) {
                if (lbRTC_IsOverTime(&bestFriend->lastSpeakTime, &memory->lastSpeakTime) == lbRTC_LESS) {
                    bestFriendMem[0] = memory;
                    res = TRUE;
                }
            } else if (memory->letterInfo.exists == TRUE) {
                bestFriendMem[0] = memory;
                res = TRUE;
            }
        } else {
            bestFriendMem[0] = memory;
            res = TRUE;
        }
    }

    return res;
}

s32 mNpc_GetAnimalMemoryBestFriend(Anmmem_c* memory, s32 num) {

    Anmmem_c* memoryP = memory;
    Anmmem_c* best_friend = NULL;
    s8 best_friendship = 0;
    UNUSED s8 pad;
    s32 res = -1;
    s32 i;

    for (i = 0; i < num; i++) {
        if ((mNpc_CheckFreeAnimalMemory(memory) == FALSE) &&
            (mNpc_SelectBestFriend(&best_friend, memory, &best_friendship) == TRUE)) {
            res = i;
        }

        memory++;
    }

    if (res != -1 && (memoryP[res].friendship < 80)) {
        res = -1;
    }

    return res;
}

s32 mNpc_GetAnimalMemoryFriend_Land_Sex(Anmmem_c* memory, s32 num, s32 sex) {
    Anmmem_c* bestFriend = NULL;
    s8 bestFriendship = 0;
    s32 id;
    s32 res = -1;
    s32 i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
            id = mPr_GetPrivateIdx(&memory->memoryPlayerId);

            if (id != -1 && common_data.saveFilePrivateInfo[id].gender == sex &&
                mNpc_SelectBestFriend(&bestFriend, memory, &bestFriendship) == TRUE) {
                res = i;
            }
        }

        memory++;
    }

    return res;
}

s32 mNpc_GetAnimalMemoryNum(Anmmem_c* memory, s32 count) {
    s32 num = 0;
    s32 i;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
            num++;
        }

        memory++;
    }

    return num;
}

s32 mNpc_GetAnimalMemoryLetterNum(Anmmem_c* memory, s32 count) {
    s32 num = 0;
    s32 i;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE && memory->letterInfo.exists == TRUE) {
            num++;
        }

        memory++;
    }

    return num;
}

s32 mNpc_GetAnimalMemoryLandKindNum(Anmmem_c* memory, s32 count) {
    Anmmem_c* memory2;
    u8 bitfield = 0xFF;
    s32 num = 0;
    s32 i;
    s32 j;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
            if (((bitfield >> i) & 1) == 1) {
                j = i + 1;
                memory2 = memory + 1;

                for (j = i + 1; j < count; j++) {
                    if (((bitfield >> j) & 1) == 1) {
                        if (mLd_CheckCmpLand(memory->land.name, memory->land.id, memory2->land.name,
                                             memory2->land.id) == TRUE) {
                            bitfield &= ~(1 << j);
                        }
                    }

                    memory2++;
                }
            }
            num++;
        } else {
            bitfield &= ~(1 << i);
        }

        memory++;
    }
    return num;
}

void mNpc_ClearAnimalInfo(Animal_c* animal) {
    Anmhome_c* home = &animal->homeInfo;
    bzero(animal, sizeof(Animal_c));
    mNpc_ClearAnimalPersonalID(&animal->id);
    mNpc_ClearAnimalMemory(animal->memories, ANIMAL_MEMORY_NUM);
    animal->cloth = 0;
    home->typeUnused = 0;
    home->blockX = 0xFF;
    home->blockZ = 0xFF;
    home->utX = 0xFF;
    home->utZ = 0xFF;
    mNpc_ClearBufSpace1((u8*)animal->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    mQst_ClearContest(&animal->contestQuest);
    mLd_ClearLandName(animal->previousLandName);
    animal->previousLandId = 0;
    animal->removeInfo = 0;
    animal->isHome = TRUE;
    mPr_ClearPlayerName(animal->parentName);
}

void mNpc_ClearAnyAnimalInfo(Animal_c* animals, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        mNpc_ClearAnimalInfo(animals);
        animals++;
    }
}

s32 mNpc_CheckFreeAnimalInfo(Animal_c* animal) {
    s32 res = FALSE;

    if ((animal->homeInfo.blockX == 0xFF) && (animal->homeInfo.blockZ == 0xFF) &&
        (ACTOR_FGNAME_GET_F000(animal->id.npcId) != FGNAME_F000_E)) {
        res = TRUE;
    }
    return res;
}

s32 mNpc_GetFreeAnimalInfo(Animal_c* animal, s32 count) {
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

s32 mNpc_UseFreeAnimalInfo(Animal_c* animal, s32 count) {
    s32 idx = mNpc_GetFreeAnimalInfo(animal, count);

    if (idx != -1) {
        mNpc_ClearAnimalInfo(&animal[idx]);
    }
    return idx;
}

void mNpc_CopyAnimalInfo(Animal_c* dst, Animal_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(Animal_c));
}

s32 mNpc_SearchAnimalinfo(Animal_c* animal, u16 npcName, s32 count) {
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

Animal_c* mNpc_GetAnimalInfoP(u16 id) {
    UNUSED s32 pad;
    Animal_c* animal = NULL;
    s32 idx = mNpc_SearchAnimalinfo(common_data.animals, id, ANIMAL_NUM_MAX);

    if (idx != -1) {
        animal = common_data.animals + idx;
    }

    return animal;
}

s32 mNpc_SearchAnimalPersonalID(AnmPersonalID_c* id) {
    Animal_c* animal = common_data.animals;
    s32 res = -1;
    s32 i;

    if (id != NULL && !mNpc_CheckFreeAnimalPersonalID(id)) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckCmpAnimalPersonalID(id, &animal->id) == TRUE) {
                res = i;
                break;
            }
            animal++;
        }
    }

    return res;
}

AnmPersonalID_c* mNpc_GetOtherAnimalPersonalIDOtherBlock(AnmPersonalID_c* pids, s32 count, s32 blockX, s32 blockY,
                                                         s32 flag) {
    UNUSED s32 pad;
    AnmPersonalID_c* otherId;
    u8 npcMax;
    UNUSED s32 pad1;
    s32 ids;
    u16 bitfield;
    s32 j;
    s32 i;
    UNUSED s32 pad2[2];
    s32 valid;
    Animal_c* animal = common_data.animals;
    s32 tempHome;
    s32 homesInBlock;

    otherId = NULL;
    homesInBlock = 0;
    ids = count;
    npcMax = common_data.nowNpcMax;
    bitfield = 0xFFFF;

    if ((blockX == 0xFF) || (blockY == 0xFF)) {
        flag = 0;
    }

    if ((pids == NULL) && (count != 0)) {
        count = 0;
    }

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&pids[i]) == TRUE) {
            ids--;
            bitfield &= ~(1 << i);
        }
    }

    if (flag == 1) {
        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            if (blockX == animal->homeInfo.blockX) {
                if (blockY == animal->homeInfo.blockZ) {
                    homesInBlock++;

                    for (i = 0; i < count; i++) {
                        if ((((bitfield >> i) & 1) == TRUE) &&
                            (mNpc_CheckCmpAnimalPersonalID(&animal->id, &pids[i]) == TRUE)) {
                            ids--;
                            bitfield &= ~(1 << i);
                            break;
                        }
                    }
                }
            }
            animal++;
        }
    }
    if (((ids + homesInBlock) < npcMax) && (count < ANIMAL_NUM_MAX)) {
        animal = common_data.animals;
        tempHome = fqrand() * ((npcMax - ids) - homesInBlock);

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            homesInBlock = 0;
            valid = 1;

            if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == 0) {
                for (i = 0; i < count; i++) {
                    if ((((bitfield >> i) & 1) == 1) &&
                        (mNpc_CheckCmpAnimalPersonalID(&animal->id, &pids[i]) == FALSE)) {
                        homesInBlock++;
                    }
                    if (homesInBlock) {}
                }

                if (homesInBlock != ids) {
                    valid = 0;
                } else if ((flag == 1) && (blockX == animal->homeInfo.blockX) && (blockY == animal->homeInfo.blockZ)) {
                    if (tempHome > 0) {
                        tempHome--;
                    }
                    valid = 0;
                }

                if (valid == 1) {
                    if (tempHome == 0) {
                        otherId = &animal->id;
                        break;
                    }
                    tempHome--;
                }
            }
            animal++;
        }
        j = 0;
    }

    return otherId;
}

AnmPersonalID_c* mNpc_GetOtherAnimalPersonalID(AnmPersonalID_c* pids, s32 count) {
    return mNpc_GetOtherAnimalPersonalIDOtherBlock(pids, count, 0, 0, FALSE);
}

void mNpc_SetAnimalThisLand(Animal_c* animal, s32 count) {
    LandInfo* landInfo = &common_data.landInfo;

    for (; count != 0; count--) {
        if (!mNpc_CheckFreeAnimalPersonalID(&animal->id)) {
            animal->id.landId = landInfo->id;
            mLd_CopyLandName(animal->id.landName, landInfo->name);
        }

        animal++;
    }
}

s32 mNpc_GetSameLooksNum(u8 looks) {
    Animal_c* animal = common_data.animals;
    s32 i;
    s32 num = 0;

    if (looks < NPC_LOOKS_NUM) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (looks == animal->id.looks) {
                num++;
            }

            animal++;
        }
    }

    return num;
}

s32 mNpc_CheckNpcExistBlock(s32 idx, s32 checkBx, s32 checkBz) {
    UNUSED s32 pad;
    s32 bx;
    s32 bz;
    s32 res = FALSE;

    if (idx >= 0 && idx < (ANIMAL_NUM_MAX)) {
        if ((mFI_Wpos2BlockNum(&bx, &bz, common_data.npclist[idx].position) == TRUE) && (bx == checkBx) &&
            (bz == checkBz)) {
            res = TRUE;
        }
    }

    return res;
}

void mNpc_Mail2AnimalMail(Anmplmail_c* animalMail, Mail_c* mail) {
    mem_copy((u8*)animalMail->body, (u8*)mail->content.body, MAIL_BODY_LEN);
    mem_copy((u8*)animalMail->header, (u8*)mail->content.header, MAIL_HEADER_LEN);
    mem_copy((u8*)animalMail->footer, (u8*)mail->content.footer, MAIL_FOOTER_LEN);

    animalMail->headerBackStart = mail->content.headerBackStart;
    animalMail->font = mail->content.font;
    animalMail->present = mail->present;
    animalMail->paperType = mail->content.paperType;
}

void mNpc_AnimalMail2Mail(Mail_c* mail, Anmplmail_c* animal_mail, PersonalID_c* pid, AnmPersonalID_c* anmId) {
    mem_copy((u8*)mail->content.body, (u8*)animal_mail->body, MAIL_BODY_LEN);
    mem_copy((u8*)mail->content.header, (u8*)animal_mail->header, MAIL_HEADER_LEN);
    mem_copy((u8*)mail->content.footer, (u8*)animal_mail->footer, MAIL_FOOTER_LEN);

    mail->content.headerBackStart = animal_mail->headerBackStart;
    mail->content.font = animal_mail->font;
    mail->present = animal_mail->present;
    mail->content.paperType = animal_mail->paperType;

    if (pid != NULL) {
        mPr_CopyPersonalID(&mail->header.sender.personalID, pid);
        mail->header.sender.type = MAIL_NAME_TYPE_PLAYER;
    }

    if (anmId != NULL) {
        mMl_set_mail_name_npcinfo(&mail->header.recipient, anmId);
    }
}

s32 mNpc_CheckMailChar(u8 c) {
    if ((c == 0x21) || (c == 0x22) || (c == 0x5F) || (c == 0x90) || (c == 0x5C) || ((c >= 0x25) && (c <= 0x40)) ||
        ((c >= 0x7F) && (c <= 0x85))) {
        return TRUE;
    }
    return FALSE;
}

s32 mNpc_CheckNormalMail_sub(s32* num, u8* body) {
    UNUSED s32 pad[2];
    s32 consecutiveChars = 0;
    u8 lastChar = 0x20;
    s32 runningLen = 1;
    s32 contentLen = 0;
    s32 i;

    *num = 0;

    for (i = 0; i < MAIL_BODY_LEN; i++) {
        if (*body != 0x20) {
            runningLen++;
            if (lastChar == *body) {
                if (runningLen >= 3) {
                    if (mNpc_CheckMailChar(*body) == TRUE) {
                        if (runningLen >= 8) {
                            consecutiveChars = TRUE;
                            break;
                        }
                    } else {
                        consecutiveChars = TRUE;
                        break;
                    }
                }
            } else {
                runningLen = 0;
                lastChar = *body;
            }
            (*num)++;
        }
        body++;
        contentLen++;
    }

    for (i = contentLen; i < MAIL_BODY_LEN; i++) {
        if (*body != 0x20) {
            (*num)++;
        }
        body++;
    }

    return consecutiveChars;
}

u8 mNpc_CheckNormalMail_length(s32* len, u8* body) {
    s32 hitRate;
    s32 hitChars;
    s32 running;

    u8 rank = 2;

    hitRate = mMC_get_mail_hit_rate(&hitChars, body, NULL);
    running = mNpc_CheckNormalMail_sub(len, body);

    if (hitChars < 3) {
        if (len[0] < 5) {
            rank = 0;
        } else if (running == TRUE) {
            rank = 0;
        }
    } else if (hitRate >= 30) {
        rank = 1;
    } else if (running == TRUE) {
        rank = 0;
    }

    return rank;
}

u8 mNpc_CheckNormalMail(u8* body) {
    s32 length;

    return mNpc_CheckNormalMail_length(&length, body);
}

s32 mNpc_SetMailCondThisLand(Anmmem_c* memory, u8* body) {
    u8 cond;

    memory->letter.date.year = common_data.time.rtcTime.year;
    memory->letter.date.month = common_data.time.rtcTime.month;
    memory->letter.date.day = common_data.time.rtcTime.day;

    cond = mNpc_CheckNormalMail(body);

    if (cond < 2) {
        memory->letterInfo.cond = cond;
        memory->letterInfo.sendReply = TRUE;
    }

    return cond;
}

s32 mNpc_SetMailCondOtherLand(Animal_c* animal, u8* body) {
    Anmremail* remail;
    u8 cond = mNpc_CheckNormalMail(body);

    if (cond < 2) {
        remail = &common_data.privateInfo->remail;

        remail->date.year = common_data.time.rtcTime.year;
        remail->date.month = common_data.time.rtcTime.month;
        remail->date.day = common_data.time.rtcTime.day;
        remail->flags.cond = cond;
        remail->flags.looks = animal->id.looks;

        mNpc_GetNpcWorldNameAnm(remail->name, &animal->id);
        mLd_CopyLandName(remail->landName, mLd_GetLandName());
    }

    return cond;
}

s32 mNpc_SetRemailCond(Animal_c* animal, Anmmem_c* memory, u8* body) {
    s32 res;

    if (mLd_PlayerManKindCheck() == FALSE) {
        res = mNpc_SetMailCondThisLand(memory, body);
    } else {
        res = mNpc_SetMailCondOtherLand(animal, body);
    }

    return res;
}

s32 mNpc_SendMailtoNpc(Mail_c* mail) {
    AnmPersonalID_c anmId;
    s32 res = FALSE;
    Animal_c* animal;
    s32 fakeTemp;
    s32 anmIdx;
    Anmmem_c* memory;
    s32 cond;
    s32 memoryIdx;
    Anmplmail_c* plmail;
    Animal_c* anm;

    if (mMl_get_npcinfo_from_mail_name(&anmId, &mail->header.recipient) == TRUE) {
        anm = common_data.animals;
        anmIdx = mNpc_SearchAnimalPersonalID(&anmId);

        if (anmIdx != -1) {
            animal = &anm[anmIdx];
            memoryIdx = mNpc_GetAnimalMemoryIdx(&mail->header.sender.personalID, animal->memories, ANIMAL_MEMORY_NUM);

            if (memoryIdx == -1) {
                memoryIdx = mNpc_ForceGetFreeAnimalMemoryIdx(animal->memories, ANIMAL_MEMORY_NUM);

                if (memoryIdx >= 0) {
                    mPr_CopyPersonalID(&animal->memories[memoryIdx].memoryPlayerId, &mail->header.sender.personalID);
                }
            }

            memory = &animal->memories[memoryIdx];
            plmail = &memory->letter;
            memory->letterInfo.exists = TRUE;
            mNpc_ClearAnimalMail(plmail);
            mNpc_Mail2AnimalMail(plmail, mail);
            cond = mNpc_SetRemailCond(animal, memory, mail->content.body);
            fakeTemp = 0xFF;
            if (mEv_CheckFirstJob() == TRUE) {
                QuestErrand* firstJob = mQst_GetFirstJobData();

                if ((firstJob->base.questKind == 6 || firstJob->base.questKind == 10) && firstJob->base.progress != 0) {
                    firstJob->base.progress = 3;
                    memory->letterInfo.sendReply = FALSE;
                }
            } else {
                s32 friendship;

                if (mLd_PlayerManKindCheck() == FALSE) {
                    if (mQst_GetOccuredContestIdx(6) == anmIdx) {
                        mQst_SetReceiveLetter(&animal->contestQuest, &mail->header.sender.personalID,
                                              mail->content.body, mail->present);
                        memory->letterInfo.sendReply = FALSE;
                    }
                }

                /* FAKE! */
                friendship = (3 & fakeTemp) & fakeTemp & fakeTemp & fakeTemp & fakeTemp & fakeTemp & fakeTemp &
                             fakeTemp & fakeTemp & fakeTemp;

                if (cond == 0) {
                    friendship -= 5;
                }

                if (mail->present != 0) {
                    friendship += 3;
                }

                mNpc_AddFriendship(memory, friendship);
            }

            res = TRUE;
        }
    }

    return res;
}

void mNpc_ClearRemail(Anmremail* remail) {
    remail->date = mTM_rtcTime_ymd_clear_code;
    mPr_ClearPlayerName(remail->name);
    mLd_ClearLandName(remail->landName);
    remail->flags.cond = 0;
    remail->flags.looks = 0x7F;
}

void mNpc_GetRemailPresent(u16* present) {
    static s32 category_table[2] = { 0, 2 };

    mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, category_table[RANDOM(4) & 1], 8);
}

s32 mNpc_GetHandbillz(Mail_c* mail, s32 superNum, s32 mailANum, s32 mailBNum, s32 mailCNum, s32 psNum) {
    HandbillzInfo handbill;
    s32 res;

    handbill.superBuf = Handbillz_tmp_super;
    handbill.superBufSize = MAIL_HEADER2_LEN;
    handbill.mailBuf = mail->content.body;
    handbill.mailBufSize = MAIL_BODY_LEN;
    handbill.psBuf = Handbillz_tmp_ps;
    handbill.psBufSize = MAIL_FOOTER2_LEN;
    handbill.superNo = superNum;
    handbill.mailANo = mailANum;
    handbill.mailBNo = mailBNum;
    handbill.mailCNo = mailCNum;
    handbill.psNo = psNum;

    res = mHandbillz_load(&handbill);
    if (res == TRUE) {
        mail->content.headerBackStart = handbill.headerBackStart;
        mem_copy((u8*)mail->content.header, Handbillz_tmp_super, MAIL_HEADER_LEN);
        mem_copy((u8*)mail->content.footer, Handbillz_tmp_ps, MAIL_FOOTER_LEN);
    }

    return res;
}

void mNpc_SetRemailFreeString(PersonalID_c* pid, AnmPersonalID_c* anmId, Anmremail* remail) {
    static s32 base_str_no[11] = {
        0x314, // food
        0x334, // sports
        0x2F4, // hobby games
        0x219, // fish
        0x1E5, // insects
        0x354, // food tastes (sweet, spicy, ...)
        0x374, // feelings
        0x394, // music genres
        0x3D4, // food satisfaction feelings (delicious, stuffed, satisfying, ...)
        0x3F4, // "good" descriptors (brilliant, splendid, ...)
        0x3B4  // "bad" descriptors (unimpressive, awful, ...)
    };

    s32 i;
    char freeStr[10];

    mHandbill_Set_free_str(0, pid->playerName, PLAYER_NAME_LEN);

    if (remail == NULL) {
        mNpc_GetNpcWorldNameAnm(freeStr, anmId);
        mHandbill_Set_free_str(1, freeStr, ANIMAL_NAME_LEN);

        mNpc_GetNpcWorldNameAnm(freeStr, mNpc_GetOtherAnimalPersonalID(anmId, 1));
        mHandbill_Set_free_str(2, freeStr, ANIMAL_NAME_LEN);
    } else {
        mHandbill_Set_free_str(1, remail->name, ANIMAL_NAME_LEN); // foreign npc name
        mNpc_GetNpcWorldNameAnm(freeStr, mNpc_GetOtherAnimalPersonalID(NULL, 0));
        mHandbill_Set_free_str(2, freeStr, ANIMAL_NAME_LEN);           // random player town npc name
        mHandbill_Set_free_str(14, remail->landName, LAND_NAME_SIZE);  // foreign town name
        mHandbill_Set_free_str(15, mLd_GetLandName(), LAND_NAME_SIZE); // player town name
    }

    for (i = 0; i < ARRAY_COUNT(base_str_no); i++) {

        mString_Load_StringFromRom(freeStr, ARRAY_COUNT(freeStr), base_str_no[i] + RANDOM(32.0f));
        mHandbill_Set_free_str(3 + i, freeStr, ARRAY_COUNT(freeStr));
    }
}

void mNpc_GetRemailGoodData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anmId, Anmremail* remail, u8 foreign) {
    static s32 start_no[NPC_LOOKS_NUM] = { 0x020, 0x040, 0x000, 0x060, 0x080, 0x0A0 };

    static s32 ohter_start_no[NPC_LOOKS_NUM] = { 0x0E0, 0x100, 0x0C0, 0x120, 0x140, 0x160 };

    static s32* start_no_table[2] = { start_no, ohter_start_no };

    s32* msgTbl;
    s32 givePresent;
    u16 present = 0;
    s32 looks;
    s32 msgNo;

    if (remail == NULL) {
        looks = anmId->looks;
    } else {
        looks = remail->flags.looks;
    }

    msgTbl = start_no_table[foreign];

    givePresent = RANDOM(4) & 1;

    if (givePresent == 0) {
        mNpc_GetRemailPresent(&present);
    }

    mNpc_SetRemailFreeString(pid, anmId, remail);
    msgNo = msgTbl[looks];
    mNpc_GetHandbillz(mail, msgNo + RANDOM(32), msgNo + RANDOM(32), msgNo + RANDOM(16) + givePresent * 16,
                      msgNo + RANDOM(32), msgNo + RANDOM(32));
    mail->present = present;
}

void mNpc_GetRemailWrongData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anmId, Anmremail* remail, u8 foreign) {
    static s32 mail_no[2] = { 0xC5, 0xD8 };
    s32 msgNo;
    s32 looks;
    s32 headerBackStart;

    if (remail == NULL) {
        looks = anmId->looks;
    } else {
        looks = remail->flags.looks;
    }

    mNpc_SetRemailFreeString(pid, anmId, remail);
    msgNo = mail_no[foreign] + looks * 3;
    msgNo += RANDOM2(3.0f);
    mHandbill_Load_HandbillFromRom(Remail_tmp_super, &headerBackStart, Remail_tmp_ps, mail->content.body, msgNo);
    mail->content.headerBackStart = headerBackStart;
    mem_copy((u8*)mail->content.header, Remail_tmp_super, MAIL_HEADER_LEN);
    mem_copy((u8*)mail->content.footer, Remail_tmp_ps, MAIL_FOOTER_LEN);
    mail->present = 0;
}

typedef void (*NpcGetRemailProc)(Mail_c*, PersonalID_c*, AnmPersonalID_c*, Anmremail*, u8);

void mNpc_GetRemailData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anmId, Anmremail* remail, s32 cond,
                        u8 foreign) {
    static NpcGetRemailProc get_remail[] = {
        &mNpc_GetRemailWrongData,
        &mNpc_GetRemailGoodData,
    };

    u16 paper;

    get_remail[cond](mail, pid, anmId, remail, foreign);
    mail->content.font = 0;
    mail->content.mailType = 0;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = MAIL_NAME_TYPE_PLAYER;

    if (remail == NULL) {
        mMl_set_mail_name_npcinfo(&mail->header.sender, anmId);
    } else {
        mPr_CopyPlayerName(mail->header.sender.personalID.playerName, remail->name);
        mLd_CopyLandName(mail->header.sender.personalID.landName, remail->landName);
        mail->header.sender.type = MAIL_NAME_TYPE_NPC;
    }

    mSP_SelectRandomItem_New(NULL, &paper, 1, NULL, 0, 1, 8);
    mail->content.paperType = (paper - 0x2000) & 0xFFFF;
}

s32 mNpc_SendRemailPostOffice(PersonalID_c* pid, AnmPersonalID_c* anmId, Anmremail* remail, s32 cond, u8 foreign) {
    Mail_c* mail = &l_npc_mail;
    s32 res = FALSE;

    if (mPO_get_keep_mail_sum() < 5) {
        mNpc_GetRemailData(mail, pid, anmId, remail, cond, foreign);
        res = mPO_receipt_proc(mail, 0);
    }

    return res;
}

s32 mNpc_CheckLetterTime(lbRTC_ymd_t* letterDate, lbRTC_time_c* rtcTime) {
    s32 res = FALSE;

    if (letterDate->day != 0xFF &&
        (letterDate->year != rtcTime->year || letterDate->month != rtcTime->month || letterDate->day != rtcTime->day)) {
        res = TRUE;
    }

    return res;
}

void mNpc_Remail() {
    Animal_c* animal = common_data.animals;
    Anmremail* remail;
    PrivateInfo* priv = common_data.privateInfo;
    Anmmem_c* memory;
    lbRTC_time_c* rtcTime = &common_data.time.rtcTime;

    if (mPr_NullCheckPersonalID(&priv->playerId) == FALSE && mLd_PlayerManKindCheck() == FALSE) {
        s32 i;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                s32 memIdx = mNpc_GetAnimalMemoryIdx(&priv->playerId, animal->memories, ANIMAL_MEMORY_NUM);

                if (memIdx != -1) {
                    memory = animal->memories + memIdx;

                    if (memory->letterInfo.sendReply && mNpc_CheckLetterTime(&memory->letter.date, rtcTime) == TRUE) {
                        if (mNpc_SendRemailPostOffice(&priv->playerId, &animal->id, NULL, memory->letterInfo.cond,
                                                      FALSE) != TRUE) {
                            break;
                        }

                        memory->letterInfo.sendReply = FALSE;
                    }
                }
            }

            animal++;
        }

        remail = &priv->remail;
        if (remail->flags.looks != 0x7F &&
            mNpc_SendRemailPostOffice(&priv->playerId, &animal->id, remail, remail->flags.cond, TRUE) == TRUE) {
            mNpc_ClearRemail(remail);
        }
    }
}

u8 mNpc_GetPaperType() {
    u16 paper;

    mSP_SelectRandomItem_New(NULL, &paper, 1, NULL, 0, 1, 8);
    return (paper - 0x2000) & 0xFFFF;
}

void mNpc_LoadMailDataCommon2(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* amnId, u16 present, u8 paperType,
                              s32 mailNo) {
    u8 super[MAIL_HEADER2_LEN];
    u8 ps[MAIL_FOOTER2_LEN];
    s32 headerBackStart;

    mMl_clear_mail(mail);
    mHandbill_Load_HandbillFromRom2(super, MAIL_HEADER2_LEN, &headerBackStart, ps, MAIL_HEADER2_LEN, mail->content.body,
                                    mailNo);
    mem_copy(mail->content.header, super, MAIL_HEADER_LEN);
    mem_copy(mail->content.footer, ps, MAIL_FOOTER_LEN);
    mail->content.headerBackStart = headerBackStart;
    mail->content.font = 0;
    mail->content.mailType = 0;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = MAIL_NAME_TYPE_PLAYER;
    mMl_set_mail_name_npcinfo(&mail->header.sender, amnId);
    mail->present = present;
    mail->content.paperType = paperType;
}

void mNpc_GetEventPresent(u16* present, s32 type) {
    static s32 priority_table[3] = {
        5,
        2,
        0,
    };

    static s32 category_table[3] = {
        0,
        0,
        2,
    };

    mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, category_table[type], priority_table[type]);
}

void mNpc_GetEventMail(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anmId, s32 type, s32 looks) {
    u16 present;
    UNUSED s32 pad;

    mHandbill_Set_free_str(0, pid->playerName, PLAYER_NAME_LEN);
    mNpc_GetNpcWorldNameAnm(Event_animal_name, anmId);
    mHandbill_Set_free_str(6, Event_animal_name, ANIMAL_NAME_LEN);
    mNpc_GetEventPresent(&present, type);
    mNpc_LoadMailDataCommon2(mail, pid, anmId, present, mNpc_GetPaperType(), 0x60 + (looks * 3) + type);
}

s32 mNpc_SendEventPresentMail(PersonalID_c* pid, s32 playerNo, AnmPersonalID_c* anmId, s32 type) {
    UNUSED s32 pad;
    mHm_hs_c* home;
    UNUSED s32 pad2;
    s32 freeIdx;
    s32 looks;
    s32 res;

    looks = anmId->looks;
    res = FALSE;

    home = &common_data.homes[mHS_get_arrange_idx(playerNo)];

    if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {

        freeIdx = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);

        if (freeIdx != -1) {
            mNpc_GetEventMail(&l_npc_mail, pid, anmId, type, looks);
            mMl_copy_mail(home->mailbox + freeIdx, &l_npc_mail);
            res = TRUE;
        } else if (mPO_get_keep_mail_sum() < 5) {
            mNpc_GetEventMail(&l_npc_mail, pid, anmId, type, looks);
            res = mPO_receipt_proc(&l_npc_mail, 0);
        }
    }

    return res;
}

void mNpc_SendEventPresentMailSex(s32* selected, u8* type, Animal_c* animal, NpcSex sex) {
    s32 bestFriendIdx = mNpc_GetAnimalMemoryBestFriend(animal->memories, ANIMAL_MEMORY_NUM);
    s32 otherSexBestFriend = mNpc_GetAnimalMemoryFriend_Land_Sex(animal->memories, ANIMAL_MEMORY_NUM, (~sex) & 1);

    if (bestFriendIdx != -1 && otherSexBestFriend == bestFriendIdx) {
        selected[0] = otherSexBestFriend;
        type[0] = 0;
    } else if (otherSexBestFriend != -1) {
        selected[0] = otherSexBestFriend;

        if (animal->memories[otherSexBestFriend].friendship >= 80) {
            type[0] = 1;
        } else {
            type[0] = 2;
        }
    }
}

s32 mNpc_SendEventPresentMail_common(NpcSex sexType) {
    static NpcSex sex[] = { NPC_SEX_FEMALE, NPC_SEX_MALE };

    Animal_c* animal = common_data.animals;
    PersonalID_c* pid;
    s32 otherSexBestFriends[ANIMAL_NUM_MAX];
    u8 types[ANIMAL_NUM_MAX];
    s32 playerNo;
    s32 sent = 0;
    u8 bitfield = 0xF;
    s32 i;
    s32 j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        otherSexBestFriends[i] = -1;

        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            if (mNpc_GetAnimalSex(animal) == sex[sexType]) {
                mNpc_SendEventPresentMailSex(&otherSexBestFriends[i], &types[i], animal, sex[sexType]);
            }
        }

        animal++;
    }

    for (i = 0; i < 3; i++) {
        animal = common_data.animals;

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            if (otherSexBestFriends[j] >= 0 && types[j] == i) {
                pid = &animal->memories[otherSexBestFriends[j]].memoryPlayerId;
                playerNo = mPr_GetPrivateIdx(pid);

                if (((bitfield >> playerNo) & 1) == 1) {
                    if (mNpc_SendEventPresentMail(pid, playerNo, &animal->id, i) == TRUE) {
                        otherSexBestFriends[j] = -1;
                        sent++;
                    } else {
                        bitfield &= ~(1 << playerNo); // remove player from bitfield because they can't receive letters
                    }
                }
            }

            if (bitfield == 0) {
                return sent; // all players cannot receive any further mail
            }

            animal++;
        }
    }
    return sent;
}

void mNpc_GetBirthdayPresent(u16* present) {
    static u8 category_table[5] = { 0, 0, 2, 2, 0xFF };

    s32 selected = category_table[RANDOM(ARRAY_COUNT(category_table))];

    if (selected == 0xFF) {
        mSP_RandomUmbSelect(present, 1);
    } else {
        mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, selected, 2);
    }
}

void mNpc_GetBirthdayCard(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anmId) {
    char itemName[10];
    s32 mailNo = 0xEA + anmId->looks * 3 + RANDOM(3);
    u16 present;

    mHandbill_Set_free_str(0, pid->playerName, PLAYER_NAME_LEN);
    mNpc_GetNpcWorldNameAnm(Birthday_animal_name, anmId);
    mHandbill_Set_free_str(1, Birthday_animal_name, ANIMAL_NAME_LEN);
    mNpc_GetBirthdayPresent(&present);
    mIN_copy_name_str(itemName, present);
    mHandbill_Set_free_str(2, itemName, 10);
    mNpc_LoadMailDataCommon2(mail, pid, anmId, present, mNpc_GetPaperType(), mailNo);
}

s32 mNpc_SendBirthdayCard(PersonalID_c* pid, s32 playerNo, AnmPersonalID_c* anm_id) {
    UNUSED s32 pad;
    mHm_hs_c* home;
    UNUSED s32 pad2;
    s32 freeIdx;
    s32 res = FALSE;

    home = &common_data.homes[mHS_get_arrange_idx(playerNo)];

    if (mPr_NullCheckPersonalID(pid) == FALSE && mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
        freeIdx = mMl_chk_mail_free_space(home->mailbox, 10);

        if (freeIdx != -1) {
            mNpc_GetBirthdayCard(&l_npc_mail, pid, anm_id);
            mMl_copy_mail(home->mailbox + freeIdx, &l_npc_mail);
            res = TRUE;
        } else if (mPO_get_keep_mail_sum() < 5) {
            mNpc_GetBirthdayCard(&l_npc_mail, pid, anm_id);
            res = mPO_receipt_proc(&l_npc_mail, 0);
        }
    }

    return res;
}

s32 mNpc_SendEventBirthdayCard(UNUSED PersonalID_c* pid) {
    return FALSE;
}

s32 mNpc_SendEventBirthdayCard2(PersonalID_c* pid, s32 playerNo) {
    Animal_c* animal = common_data.animals;
    s32 res = FALSE;
    s32 idx;
    s32 i;

    if (pid != NULL && mLd_CheckThisLand(pid->landName, pid->landId) == TRUE) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                idx = mNpc_GetHighestFriendshipIdx(animal->memories, ANIMAL_MEMORY_NUM);
                if ((idx != -1) && (mPr_CheckCmpPersonalID(pid, &animal->memories[idx].memoryPlayerId) != 0) &&
                    (mNpc_SendBirthdayCard(pid, playerNo, &animal->id) == 1)) {
                    res = TRUE;
                }
            }

            animal++;
        }
    }

    return res;
}

void mNpc_GetXmasCardData(Mail_c* mail, PersonalID_c* pid) {
    UNUSED UNUSED s32 pad;
    s32 headerBackStart;

    mHandbill_Load_HandbillFromRom(mail->content.header, &headerBackStart, mail->content.footer, mail->content.body,
                                   0xD7);
    mail->content.headerBackStart = headerBackStart;
    mail->content.font = 0;
    mail->content.mailType = 1;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = MAIL_NAME_TYPE_PLAYER;
    mSP_SelectRandomItem_New(NULL, &mail->present, 1, NULL, 0, 0, 3);
    mail->content.paperType = 22;
}

s32 mNpc_SendEventXmasCard(PersonalID_c* pid, s32 playerNo) {
    UNUSED s32 pad;
    mHm_hs_c* home;
    UNUSED s32 pad2;
    s32 freeSpace;
    s32 res = FALSE;

    if (mPr_NullCheckPersonalID(pid) == FALSE) {
        home = &common_data.homes[mHS_get_arrange_idx(playerNo)];

        if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
            freeSpace = mMl_chk_mail_free_space(home->mailbox, 10);

            if (freeSpace != -1) {
                mNpc_GetXmasCardData(&l_npc_mail, pid);
                mMl_copy_mail(home->mailbox + freeSpace, &l_npc_mail);
                res = TRUE;
            }
        }
    }

    return res;
}

void mNpc_SetWordEnding(Animal_c* animal, char* catchphrase) {
    mem_copy((u8*)animal->catchphrase, (u8*)catchphrase, ANIMAL_CATCHPHRASE_LEN);
}

char* mNpc_GetWordEnding(Actor* actor) {
    Animal_c* animalInfo;
    Animal_c* temp;
    char* wordEnding;

    if ((actor != NULL) & (actor->part == ACTOR_PART_NPC)) {
        animalInfo = temp = ((Npc*)actor)->npcInfo.animal;
    } else {
        animalInfo = NULL;
    }

    if ((actor != NULL) && (animalInfo != NULL)) {
        wordEnding = animalInfo->catchphrase;
    } else {
        wordEnding = l_no_ending_npc_ending;
    }

    return wordEnding;
}

void mNpc_ResetWordEnding(Actor* actor) {
    if (actor != NULL && actor->part == ACTOR_PART_NPC) {
        Animal_c* animal = ((Npc*)actor)->npcInfo.animal;
        NpcDefaultData* list;
        u16 idx;

        if (animal != NULL) {

            list = zelda_malloc(SEGMENT_ROM_SIZE(segment_00E03000));

            if (0) {}

            if (list != NULL) {
                DmaMgr_RequestSyncDebug(list, SEGMENT_ROM_START(segment_00E03000),
                                        ALIGN16(SEGMENT_ROM_SIZE(segment_00E03000)), "../m_npc.c", 0xE25);
                idx = animal->id.npcId & 0xFFF;
                mString_Load_StringFromRom(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN, list[idx].catchphraseIdx);
                zelda_free(list);
            }
        }
    }
}

s32 mNpc_GetFreeEventNpcIdx() {
    NpcEvent* npcEvent = common_data.npcEvent;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(common_data.npcEvent); i++) {
        if (npcEvent->use == FALSE) {
            return i;
        }

        npcEvent++;
    }

    return -1;
}

s32 mNpc_RegistEventNpc(u16 eventId, u16 textureId, u16 npcId, u16 clothId) {
    s32 freeIdx = mNpc_GetFreeEventNpcIdx();
    s32 res = FALSE;

    if (freeIdx != -1) {
        NpcEvent* npcEvent = &common_data.npcEvent[freeIdx];

        npcEvent->eventId = eventId;
        npcEvent->textureId = textureId;
        npcEvent->npcId = npcId;
        npcEvent->clothId = clothId;
        npcEvent->exists = FALSE;
        npcEvent->use = TRUE;

        res = TRUE;
    }

    return res;
}

void mNpc_UnRegistEventNpc(u16 eventId) {
    NpcEvent* savedNpc = common_data.npcEvent;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(common_data.npcEvent); i++) {
        if ((savedNpc->use == TRUE) && (savedNpc->eventId == eventId)) {
            bzero(savedNpc, sizeof(NpcEvent));
            break;
        }

        savedNpc++;
    }
}

void mNpc_ClearEventNpc() {
    bzero(common_data.npcEvent, sizeof(common_data.npcEvent));
}

NpcEvent* mNpc_GetSameEventNpc(u16 eventId) {
    NpcEvent* npcEvent = common_data.npcEvent;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(common_data.npcEvent); i++) {
        if (npcEvent->eventId == eventId) {
            return npcEvent;
        }

        npcEvent++;
    }

    return NULL;
}

u8 mNpc_GetLooks(u16 npcId) {
    u8 looks = NPC_LOOKS_GIRL;

    if (ACTOR_FGNAME_GET_F000(npcId) == FGNAME_F000_E) {
        looks = npc_looks_table[npcId & 0xFFF];
    }

    return looks;
}

void mNpc_SetDefAnimalInfo(Animal_c* animal, u16 npcId, u8 looks, NpcDefaultData* defaultData) {
    if (ACTOR_FGNAME_GET_F000(npcId) == FGNAME_F000_E) {
        animal->id.npcId = npcId;
        animal->id.looks = looks;
        animal->cloth = defaultData->cloth;
        mString_Load_StringFromRom(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN, defaultData->catchphraseIdx);
        animal->id.landId = common_data.landInfo.id;
        mLd_CopyLandName(animal->id.landName, common_data.landInfo.name);
    }
}

void mNpc_SetDefAnimal(Animal_c* animal, u16 npcId, NpcDefaultData* defaultData) {
    s32 idx = npcId & 0xFFF;

    if (ACTOR_FGNAME_GET_F000(npcId) == FGNAME_F000_E) {
        mNpc_SetDefAnimalInfo(animal, npcId, npc_looks_table[idx], &defaultData[idx]);
    }
}

void mNpc_SetHaveAppeared(u16 npcId) {
    u8* usedTable = common_data.npcUsedTable;

    if (ACTOR_FGNAME_GET_F000(npcId) == FGNAME_F000_E) {
        s32 idx = npcId & 0xFFF;
        s32 i = idx / 8;

        if (i < ARRAY_COUNT(common_data.npcUsedTable)) {
            usedTable += i;
            idx &= 7;
            *usedTable |= 1 << idx;
        }
    }
}

s32 mNpc_GetHaveAppeared_idx(s32 idx) {
    s32 res = TRUE;
    u8* usedTable = common_data.npcUsedTable;
    s32 i = idx / 8;

    if (i < ARRAY_COUNT(common_data.npcUsedTable)) {
        usedTable += i;
        res = (*usedTable >> (idx & 7)) & 1;
    }

    return res;
}

s32 mNpc_GetLooks2NotHaveAppearedNum(u8 id) {
    s32 i;
    s32 count = 0;

    if (id < 6) {
        for (i = 0; i < NPC_NUM; i++) {
            if ((id == npc_looks_table[i]) && (mNpc_GetHaveAppeared_idx(i) == FALSE)) {
                count++;
            }
        }
    }

    return count;
}

void mNpc_ResetHaveAppeared_common(u8* npcUsedTable, Animal_c* animal) {
    s32 i;

    bzero(npcUsedTable, sizeof(common_data.npcUsedTable));
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            mNpc_SetHaveAppeared(animal->id.npcId);
        }

        animal++;
    }
}

void mNpc_ResetHaveAppeared() {
    s32 i;

    for (i = 0; i < NPC_NUM; i++) {
        if (mNpc_GetHaveAppeared_idx(i) == FALSE) {
            break;
        }
    }

    if (i == NPC_NUM) {
        mNpc_ResetHaveAppeared_common(common_data.npcUsedTable, common_data.animals);
    }
}

s32 mNpc_GetDefGrowPermission(s32 idx, s8* growList, s32 count) {
    s32 res = 1;

    if (idx < count) {
        res = growList[idx];
    }

    return res;
}

void mNpc_DecideLivingNpcMax(Animal_c* animal, u8 count, s32 mallocFlag) {
    UNUSED s32 pad;
    NpcDefaultData* defList;
    s8* growList;
    u8 bitfield = 0;
    s32 i = 0;
    u8 looks;

    bzero(fakeTable, sizeof(fakeTable));
    mNpc_MakeRandTable(fakeTable, ARRAY_COUNT(fakeTable), ARRAY_COUNT(fakeTable));

    if (mallocFlag == 0) {
        defList = malloc(SEGMENT_ROM_SIZE(segment_00E03000));
        growList = malloc(ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)));
    } else {
        defList = zelda_malloc(SEGMENT_ROM_SIZE(segment_00E03000));
        growList = zelda_malloc(ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)));
    }

    DmaMgr_RequestSyncDebug(defList, SEGMENT_ROM_START(segment_00E03000), SEGMENT_ROM_SIZE(segment_00E03000),
                            "../m_npc.c", 4083);
    DmaMgr_RequestSyncDebug(growList, SEGMENT_ROM_START(segment_00E0D000), ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)),
                            "../m_npc.c", 4085);

    while (count) {
        if (animal == NULL) {
            break;
        }

        if (animal->id.npcId == 0) {
            s32 idx = fakeTable[i];
            s32 growPerm = mNpc_GetDefGrowPermission(idx, growList, ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)));

            if (growPerm == 0) {
                looks = npc_looks_table[idx];
                if (((bitfield >> looks) & 1) == 0) {
                    mNpc_SetDefAnimal(animal, idx | 0xE000, defList);
                    bitfield |= (1 << looks);
                    mNpc_SetHaveAppeared(idx | 0xE000);
                    animal++;
                    count--;
                }
            } else if (growPerm == -1) {
                mNpc_SetHaveAppeared(idx | 0xE000);
            }
        } else {
            count--;
            animal++;
        }
        i++;
    }

    if (mallocFlag == 0) {
        free(defList);
        free(growList);
    } else {
        zelda_free(defList);
        zelda_free(growList);
    }
}

void mNpc_SetAnimalTitleDemo(DemoNpc* demo, Animal_c* animal, Game* game) {
    GameAlloc* alloc = NULL;
    NpcDefaultData* defList;
    s32 i;

    if (game != NULL) {
        alloc = &game->alloc;
        defList = gamealloc_malloc(alloc, SEGMENT_ROM_SIZE(segment_00E03000));
    } else {
        defList = zelda_malloc(SEGMENT_ROM_SIZE(segment_00E03000));
    }

    DmaMgr_RequestSyncDebug(defList, SEGMENT_ROM_START(segment_00E03000), SEGMENT_ROM_SIZE(segment_00E03000),
                            "../m_npc.c", 0x1055);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        mNpc_SetDefAnimal(animal, demo->npcName, defList);
        animal->homeInfo.typeUnused = 0;
        animal->homeInfo.blockX = demo->blockX;
        animal->homeInfo.blockZ = demo->blockZ;
        animal->homeInfo.utX = demo->utX;
        animal->homeInfo.utZ = demo->utZ;

        animal++;
        demo++;
    }

    if (defList != NULL) {
        if (game != NULL) {
            gamealloc_free(alloc, defList);
        } else {
            zelda_free(defList);
        }
    }
}

s32 mNpc_GetReservedUtNum(s32* utX, s32* utZ, u16* item) {
    f32 reserveNum = 0.0f;
    s32 rand;
    s32 res = FALSE;
    s32 i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if ((*item >= 0x5810 && *item < 0x5825) || *item == 0xF0EE) {
            reserveNum++;
        }

        item++;
    }

    if (reserveNum > 0.0f) {
        item -= UT_TOTAL_NUM;
        rand = RANDOM(reserveNum);

        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if ((*item >= 0x5810 && *item < 0x5825) || *item == 0xF0EE) {
                if (rand == 0) {
                    *utX = i % UT_Z_NUM;
                    *utZ = i / UT_X_NUM;
                    res = TRUE;

                    break;
                } else {
                    rand--;
                }
            }

            item++;
        }
    }

    return res;
}

s32 mNpc_BlockNum2ReservedUtNum(s32* utX, s32* utZ, s32 bx, s32 bz) {
    u16* items = mFI_BkNumtoUtFGTop(bx, bz);
    s32 res = FALSE;

    if (items != NULL) {
        res = mNpc_GetReservedUtNum(utX, utZ, items);
    }

    return res;
}

void mNpc_MakeReservedListBeforeFieldct(Anmhome_c* reserved, s32 reservedNum, u8* reservedCount) {
    Foreground* fg = &common_data.foreground[0][0];
    Anmhome_c* reservedp = reserved;
    u16* item;
    u8 num = 0;
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    for (i = 0; i < reservedNum; i++) {
        reserved->blockX = -1;
        reserved->blockZ = -1;
        reserved->utX = -1;
        reserved->utZ = -1;
        reserved++;
    }

    reserved = reservedp;
    for (i = 0; i < FG_BLOCK_Z_NUM; i++) {
        for (j = 0; j < FG_BLOCK_X_NUM; j++) {
            item = &fg->items[0][0];

            for (k = 0; k < UT_Z_NUM; k++) {
                for (l = 0; l < UT_X_NUM; l++) {
                    if ((*item >= 0x5810) && (*item < 0x5825)) {
                        num++;
                        reserved->blockX = j + 1;
                        reserved->blockZ = i + 1;
                        reserved->utX = l;
                        reserved->utZ = k;
                        reserved++;
                        if (num >= reservedNum) {
                            *reservedCount = num;
                            return;
                        }
                    }

                    item++;
                }
            }

            fg++;
        }
    }

    *reservedCount = num;
}

void mNpc_MakeReservedListAfterFieldct(Anmhome_c* reserved, s32 reservedNum, u8* reserved_count, u8 bxMax, u8 bzMax) {
    FieldMakeBlockInfo* blockInfo = mFI_GetBlockTopP();
    Anmhome_c* reservedp = reserved;
    u16* item;
    u8 num = 0;
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    for (i = 0; i < reservedNum; i++) {
        reserved->blockX = -1;
        reserved->blockZ = -1;
        reserved->utX = -1;
        reserved->utZ = -1;
        reserved++;
    }

    reserved = reservedp;
    for (i = 0; i < bzMax; i++) {
        for (j = 0; j < bxMax; j++) {
            item = blockInfo->fgInfo.itemsPtr;

            for (k = 0; k < UT_Z_NUM; k++) {
                for (l = 0; l < UT_X_NUM; l++) {
                    if (((*item >= 0x5810) && (*item < 0x5825))) {
                        num++;
                        reserved->blockX = j;
                        reserved->blockZ = i;
                        reserved->utX = l;
                        reserved->utZ = k;
                        reserved++;
                        if (num >= reservedNum) {
                            *reserved_count = num;
                            return;
                        }
                    }

                    item++;
                }
            }

            blockInfo++;
        }
    }

    *reserved_count = num;
}

void mNpc_BuildHouseBeforeFieldct(u16 npcId, s32 bx, s32 bz, s32 utX, s32 utZ) {
    static s32 ut_d[9][2] = { { 0, 0 }, { -1, 1 },  { 0, 1 },  { 1, 1 }, { -1, 0 },
                              { 1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 } };

    static u16 set_fg[9] = {
        0, 0xA012, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    };

    u16* deposit;
    Foreground* fg;
    s32 x;
    s32 z;
    s32 i;
    u16 house = npcId - 0x10000 + 0x7000; // this shifts it to the house range 0x50XX

    if (bx >= 0 && bx < FG_BLOCK_X_NUM && bz >= 0 && bz < FG_BLOCK_Z_NUM && utX > 0 && utX < (UT_X_NUM - 1) &&
        utZ > 0 && utZ < (UT_Z_NUM - 1)) {
        set_fg[0] = house;
        fg = &common_data.foreground[bz][bx];

        deposit = mFI_GetDepositP(bx + 1, bz + 1);

        for (i = 0; i < ARRAY_COUNT(set_fg); i++) {
            x = ut_d[i][0] + utX;
            z = ut_d[i][1] + utZ;

            mPB_keep_item(fg->items[z][x]);
            if (deposit != NULL) {
                mFI_BlockDepositOFF(deposit, x, z);
            }

            fg->items[z][x] = set_fg[i];
        }
    }
}

void mNpc_DestroyHouse(Anmhome_c* home) {
    u8 bx = home->blockX - 1;
    u8 bz = home->blockZ - 1;
    u8 utX = home->utX;
    u8 utZ = home->utZ - 1;

    if (bx < FG_BLOCK_X_NUM && bz < FG_BLOCK_Z_NUM && utX > 0 && utX < (UT_X_NUM - 1) && utZ > 0 &&
        utZ < (UT_Z_NUM - 1)) {
        u16 reserveNo = mFM_GetReseveName(home->blockX, home->blockZ);

        common_data.foreground[bz][bx].items[utZ][utX] = reserveNo;
        common_data.foreground[bz][bx].items[utZ + 1][utX - 1] = 0;
        common_data.foreground[bz][bx].items[utZ + 1][utX] = 0;
        common_data.foreground[bz][bx].items[utZ + 1][utX + 1] = 0;
        common_data.foreground[bz][bx].items[utZ][utX - 1] = 0;
        common_data.foreground[bz][bx].items[utZ][utX + 1] = 0;
        common_data.foreground[bz][bx].items[utZ - 1][utX - 1] = 0;
        common_data.foreground[bz][bx].items[utZ - 1][utX] = 0;
        common_data.foreground[bz][bx].items[utZ - 1][utX + 1] = 0;
    }
}

void mNpc_SetNpcHome(Animal_c* animal, Anmhome_c* reserved, u8 reserved_num) {
    Anmhome_c* homeInfo;
    s32 i;
    s32 idx;

    if (reserved_num > ARRAY_COUNT(fake_table)) {
        reserved_num = ARRAY_COUNT(fake_table);
    }

    bzero(fake_table, sizeof(fake_table));
    mNpc_MakeRandTable(fake_table, reserved_num, ARRAY_COUNT(fake_table) / 2);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (i >= reserved_num) {
            break;
        }

        homeInfo = &animal->homeInfo;
        if ((ACTOR_FGNAME_GET_F000(animal->id.npcId) == FGNAME_F000_E) && homeInfo->blockX == 0xFF &&
            homeInfo->blockZ == 0xFF) {
            idx = fake_table[i];

            homeInfo->blockX = reserved[idx].blockX;
            homeInfo->blockZ = reserved[idx].blockZ;
            homeInfo->utX = reserved[idx].utX;
            homeInfo->utZ = reserved[idx].utZ + 1;
            mNpc_BuildHouseBeforeFieldct(animal->id.npcId, homeInfo->blockX - 1, homeInfo->blockZ - 1, homeInfo->utX,
                                         reserved[idx].utZ);
        }
        animal++;
    }
}

void mNpc_InitNpcData() {
    UNUSED s32 pad;
    u8 reservedNum = 0;

    mNpc_MakeReservedListBeforeFieldct(reserved, ARRAY_COUNT(reserved), &reservedNum);
    mNpc_SetNpcHome(common_data.animals, reserved, reservedNum);
}

void mNpc_InitNpcList() {
    NpcList* npclist = common_data.npclist;
    s32 i;

    if (npclist != NULL) {
        bzero(npclist, ANIMAL_NUM_MAX * sizeof(NpcList));

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            npclist->fieldName = 0xFFFF;
            mQst_ClearQuestInfo(&npclist->questInfo);
            npclist->houseData.type = 0xFF;
            npclist->houseData.palette = 0xFF;
            npclist->houseData.wallId = 0xFF;
            npclist->houseData.floorId = 0xFF;
            npclist->houseData.mainLayerId = 203;

            npclist++;
        }
    }
}

void mNpc_SetNpcList(NpcList* npclist, Animal_c* animal, s32 count, s32 mallocFlag) {
    NpcHouseData* houseData;
    NpcHouseData* newHouseData;
    xyz_t* homePos;
    xyz_t* pos;
    s32 houseId;
    f32 z;
    Anmhome_c* homeInfo;
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
        if ((ACTOR_FGNAME_GET_F000(animal->id.npcId) == FGNAME_F000_E) && homeInfo->blockX != 0xFF) {
            npcId = animal->id.npcId;
            houseId = animal->id.npcId & 0xFFF;
            newHouseData = &npclist->houseData;
            homePos = &npclist->homePosition;
            pos = &npclist->position;
            if (0) {}
            npclist->name = npcId;

            homePos->x = homeInfo->blockX * 640.0f;
            homePos->z = homeInfo->blockZ * 640.0f;
            mFI_UtNum2PosXZInBk(&x, &z, homeInfo->utX, homeInfo->utZ);

            homePos->x += x;
            homePos->z += z;
            homePos->y = 0.0f;

            pos->x = homePos->x;
            pos->y = homePos->y;
            pos->z = homePos->z;

            npclist->appearFlag = TRUE;
            npclist->rewardFurniture = 0;

            newHouseData->type = houseData[houseId].type;
            newHouseData->palette = houseData[houseId].palette;
            newHouseData->wallId = houseData[houseId].wallId;
            newHouseData->floorId = houseData[houseId].floorId;
            newHouseData->mainLayerId = houseData[houseId].mainLayerId;
            newHouseData->secondaryLayerId = houseData[houseId].secondaryLayerId;
        }

        npclist++;
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
        u16 npcId = actor->fgName;

        if (ACTOR_FGNAME_GET_F000(npc->actor.fgName) == FGNAME_F000_D) {
            NpcEvent* eventNpc = mNpc_GetSameEventNpc(npcId);

            if (eventNpc != NULL) {
                npcInfoIdx = mNpc_SearchAnimalinfo(common_data.animals, eventNpc->npcId, ANIMAL_NUM_MAX);
            }
        }

        if (npcInfoIdx >= 0 && npcInfoIdx < ANIMAL_NUM_MAX) {
            npc->npcInfo.animal = &common_data.animals[npcInfoIdx];
            npc->npcInfo.list = &common_data.npclist[npcInfoIdx];
        } else {
            npc->npcInfo.animal = NULL;
            npc->npcInfo.list = NULL;
        }
    }
}

void mNpc_AddNpc_inNpcRoom(FieldMakeMoveActor* moveActor, u8 bx, u8 bz) {
    s32 animalId;
    s32 idx;
    u16 fieldId;
    u16 houseOwnerId;
    u8* animalIdInField;
    UNUSED s32 pad;
    u16 currentNpc;
    s32 npcId;

    if (moveActor != NULL) {
        fieldId = mFI_GetFieldId();
        idx = func_8008BE00_jp(moveActor, 16);
        if (idx != -1) {
            moveActor = &moveActor[idx];
            if ((fieldId & 0xF000) == 0x4000) {
                houseOwnerId = common_data.houseOwnerName;
                if ((idx < ANIMAL_NUM_MAX) && (houseOwnerId != 0xFFFF) && (houseOwnerId != 0)) {
                    if (mEvNM_CheckJointEvent(houseOwnerId) != 1) {
                        animalId = mNpc_SearchAnimalinfo(common_data.animals, houseOwnerId, ANIMAL_NUM_MAX);
                        if (animalId != -1) {
                            moveActor->nameId = houseOwnerId;
                            moveActor->utX = 4;
                            moveActor->utZ = 7;
                            moveActor->npcId = animalId;
                            moveActor->arg = -1;
                            mFI_SetMoveActorBitData_ON(idx, bx, bz);
                        }
                    }
                }
            } else if (fieldId == 0x300A) {
                animalIdInField = func_8008033C_jp(0xE, 0xF);
                if (animalIdInField != NULL) {
                    npcId = *animalIdInField;
                    currentNpc = common_data.animals[npcId].id.npcId;
                    func_80082BD8_jp(&currentNpc, 0xE, npcId, 0);
                    moveActor->nameId = currentNpc;
                    moveActor->utX = 4;
                    moveActor->utZ = 7;
                    moveActor->npcId = npcId;
                    moveActor->arg = -1;
                    mFI_SetMoveActorBitData_ON(idx, bx, bz);
                }
            }
        }
    }
}

void mNpc_RenewalNpcRoom(s16* wallFloor) {
    s32 fieldId = mFI_GetFieldId();
    u16 ownerName = common_data.houseOwnerName;
    s32 wallId;
    s32 floorId;
    s32 npcIdx;

    if ((fieldId & 0xF000) == 0x4000) {
        if ((ownerName != 0) && (ownerName != 0xFFFF)) {
            npcIdx = mNpc_SearchAnimalinfo(common_data.animals, ownerName, ANIMAL_NUM_MAX);
            wallId = common_data.npclist[npcIdx].houseData.wallId;
            floorId = common_data.npclist[npcIdx].houseData.floorId;
            *wallFloor = floorId | (wallId << 8);
            { UNUSED s32 scopedTemp; }
            return;
        }
    }
    *wallFloor = 0;
}

void mNpc_RenewalSetNpc(Actor* actor) {
    Npc* npc = (Npc*)actor;

    if (npc->npcInfo.list != NULL) {
        s32 fieldId = mFI_GetFieldId();
        NpcList* npcList = npc->npcInfo.list;

        if ((fieldId & 0xF000) == 0) {
            xyz_t_move(&npcList->position, &npc->actor.world.pos);
            npcList->appearFlag = TRUE;
        }
    } else {
        mFI_MyMoveActorBitData_ON(actor);
    }
}

s32 mNpc_GetFriendAnimalNum(PersonalID_c* pid) {
    Animal_c* animal = common_data.animals;
    s32 num = 0;
    s32 i;

    if (pid != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE &&
                mNpc_GetAnimalMemoryIdx(pid, animal->memories, ANIMAL_MEMORY_NUM) != -1) {
                num++;
            }

            animal++;
        }
    }

    return num;
}

s32 mNpc_CheckFriendAllAnimal(PersonalID_c* pid) {
    s32 nowNpcMax = common_data.nowNpcMax;
    s32 friendNum = mNpc_GetFriendAnimalNum(pid);

    if (nowNpcMax <= friendNum) {
        return TRUE;
    }

    return FALSE;
}

s32 mNpc_CheckSelectFurniture(u16 item) {
    s32 res = FALSE;

    if (((item < 0x17AC) || (item >= 0x1BA8)) && ((item < 0x1CA8) || (item >= 0x1D28)) &&
        ((item < 0x1BA8) || (item >= 0x1C28)) && ((item < 0x1C28) || (item >= 0x1CA8)) &&
        ((item < 0x15B0) || (item >= 0x17AC)) && ((item < 0x1E3C) || (item >= 0x1EA0)) &&
        ((item < 0x1D28) || (item >= 0x1D44))) {
        res = TRUE;
    }
    return res;
}

u16 mNpc_DecideNpcFurniture(FieldMakeFGData** data, NpcList* npcList, s32 count) {
    u16 layerId = npcList->houseData.mainLayerId;
    s32 idx = layerId - count;
    u16* fgItems;
    s32 i;
    s32 j;
    u8 num = 0;

    if (idx < 0) {
        idx = 0;
    }
    fgItems = data[idx]->items[0];

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if ((ACTOR_FGNAME_GET_F000(*fgItems) == FGNAME_F000_1) && (mNpc_CheckSelectFurniture(*fgItems) == TRUE)) {
                num++;
            }
            fgItems++;
        }
        fgItems += UT_X_NUM - 10;
    }

    if (num > 0) {
        num = RANDOM(num);
        fgItems = data[idx]->items[0];

        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                if ((ACTOR_FGNAME_GET_F000(*fgItems) == FGNAME_F000_1) &&
                    (mNpc_CheckSelectFurniture(*fgItems) == TRUE)) {
                    if (num <= 0) {
                        return *fgItems;
                    }
                    num--;
                }
                fgItems++;
            }
            fgItems += UT_X_NUM - 10;
        }
    }

    return 0;
}

void mNpc_SetNpcFurnitureRandom(FieldMakeFGData** data, s32 base) {
    NpcList* npclist = common_data.npclist;
    Animal_c* animal = common_data.animals;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            npclist->rewardFurniture = mNpc_DecideNpcFurniture(data, npclist, base);
        }

        npclist++;
        animal++;
    }
}

u16 mNpc_GetNpcFurniture(AnmPersonalID_c* anmId) {
    u16 furniture = 0;
    s32 idx = mNpc_SearchAnimalPersonalID(anmId);

    if (idx != -1) {
        furniture = common_data.npclist[idx].rewardFurniture;
    }
    return furniture;
}

void mNpc_ClearInAnimal() {
    mNpc_ClearAnimalInfo(&l_mnpc_remove_in_animal);
}

Animal_c* mNpc_GetInAnimalP() {
    return &l_mnpc_remove_in_animal;
}

s32 mNpc_DecideRemoveAnimalNo_Friend(Animal_c* animal, s32 metFlag) {
    PrivateInfo* priv = common_data.saveFilePrivateInfo;
    s32 res = -1;
    s32 playerNumber = 0;
    s32 possibleNum = 0;
    s32 met;
    s32 i;
    s32 j;
    u16 bitfield = 0;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (mPr_NullCheckPersonalID(&priv->playerId) == FALSE) {
            playerNumber++;
        }
        priv++;
    }

    if (playerNumber > 0) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                priv = common_data.saveFilePrivateInfo;
                met = 0;

                for (j = 0; j < PLAYER_NUM; j++) {
                    if (mPr_NullCheckPersonalID(&priv->playerId) == FALSE) {
                        if (mNpc_GetAnimalMemoryIdx(&priv->playerId, animal->memories, ANIMAL_MEMORY_NUM) == -1) {
                            break;
                        }

                        met++;
                    }

                    priv++;
                }

                if (metFlag == TRUE) {
                    if (met == playerNumber) {
                        possibleNum++;
                        bitfield |= (1 << i);
                    }
                } else if (met > 0) {
                    possibleNum++;
                    bitfield |= (1 << i);
                }
            }

            animal++;
        }
    }

    if (possibleNum > 0) {
        s32 selected = RANDOM(possibleNum);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((bitfield >> i) & 1) == 1) {
                if (selected <= 0) {
                    res = i;
                    break;
                } else {
                    selected--;
                }
            }
        }
    }

    return res;
}

u8 mNpc_DecideRemoveAnimalNo(Animal_c* animal, s32 max) {
    u8 count = 0;
    s32 selected = RANDOM(max);
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            selected--;
        }
        if (selected <= 0) {
            break;
        }
        count++;
        animal++;
    }

    return count;
}

void mNpc_SetRemoveAnimalNo(Animal_c* animal) {
    u8* removalIdx = &common_data.removeAnimalIdx;
    u8 nowMax = common_data.nowNpcMax;

    if ((nowMax >= 6) && (*removalIdx == 0xFF)) {
        s32 removeNo = mNpc_DecideRemoveAnimalNo_Friend(animal, TRUE);

        if (removeNo == -1) {
            removeNo = mNpc_DecideRemoveAnimalNo_Friend(animal, FALSE);
            if (removeNo == -1) {
                removeNo = mNpc_DecideRemoveAnimalNo(animal, nowMax);
            }
        }

        if (removeNo != -1) {
            *removalIdx = removeNo;
        }
    }
}

s32 mNpc_CheckGoodbyAnimalMemoryNum(Animal_c* a0, Animal_c* a1) {
    Anmmem_c* memories0 = a0->memories;
    Anmmem_c* memories1 = a1->memories;
    s32 res = 0;
    s32 res0;
    s32 res1;

    res0 = mNpc_GetAnimalMemoryNum(memories0, ANIMAL_MEMORY_NUM);
    res1 = mNpc_GetAnimalMemoryNum(memories1, ANIMAL_MEMORY_NUM);

    if (res1 > res0) {
        res = 1;
    } else if (res1 == res0) {
        res0 = mNpc_GetAnimalMemoryLetterNum(memories0, ANIMAL_MEMORY_NUM);
        res1 = mNpc_GetAnimalMemoryLetterNum(memories1, ANIMAL_MEMORY_NUM);

        if (res1 > res0) {
            res = 1;
        } else if (res1 == res0) {
            res0 = mNpc_GetAnimalMemoryLandKindNum(memories0, ANIMAL_MEMORY_NUM);
            res1 = mNpc_GetAnimalMemoryLandKindNum(memories1, ANIMAL_MEMORY_NUM);

            if (res1 > res0) {
                res = 1;
            } else if (res1 == res0) {
                res0 = mNpc_GetSameLooksNum(a0->id.looks);
                res1 = mNpc_GetSameLooksNum(a1->id.looks);

                if (res1 < res0) {
                    res = 1;
                } else {
                    res = -1;
                }
            }
        }
    }

    return res;
}

s32 mNpc_GetGoodbyAnimalIdx() {
    UNUSED s32 pad;
    Animal_c* animal = common_data.animals;
    Animal_c* otherAnimal = NULL;
    s32 res0;
    s32 res1;
    u16 bitfield = 0;
    s32 candidate = 0;
    s32 goodbyeIdx = -1;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++, animal++) {
        if ((i != (u32)&common_data.removeAnimalIdx) && (mNpc_CheckFreeAnimalInfo(animal) == FALSE)) {
            if (otherAnimal != NULL) {
                if (mNpc_CheckRemoveExp(animal) == 0) {
                    if (mNpc_CheckRemoveExp(otherAnimal) != 0) {
                        candidate = 1;
                        bitfield = (1 << i);
                        otherAnimal = animal;
                        goodbyeIdx = i;
                    } else {
                        res1 = mNpc_CheckGoodbyAnimalMemoryNum(animal, otherAnimal);
                        switch (res1) {
                            case -1:
                                candidate++;
                                bitfield |= (1 << i);
                                break;
                            case 1:
                                candidate = 1;
                                bitfield = (1 << i);
                                otherAnimal = animal;
                                goodbyeIdx = i;
                                break;
                        }
                    }
                } else if (mNpc_CheckRemoveExp(otherAnimal) != 0) {
                    res0 = mNpc_GetRemoveTime(animal);
                    res1 = mNpc_GetRemoveTime(otherAnimal);
                    if (res0 < res1) {
                        candidate = 1;
                        bitfield = (1 << i);
                        otherAnimal = animal;
                        goodbyeIdx = i;
                    } else if (res1 == res0) {
                        res1 = mNpc_CheckGoodbyAnimalMemoryNum(animal, otherAnimal);
                        switch (res1) {
                            case -1:
                                candidate++;
                                bitfield |= (1 << i);
                                break;
                            case 1:
                                candidate = 1;
                                bitfield = (1 << i);
                                otherAnimal = animal;
                                goodbyeIdx = i;
                                break;
                        }
                    }
                }
            } else {
                candidate = 1;
                bitfield = (1 << i);
                otherAnimal = animal;
                goodbyeIdx = i;
            }
        }
    }

    if (candidate >= 2) {
        s32 rand = RANDOM(candidate);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((candidate >> i) & 1) == 1) {
                if (rand == 0) {
                    goodbyeIdx = i;
                    break;
                } else {
                    rand--;
                }
            }
        }
    }
    return goodbyeIdx;
}

void mNpc_ClearGoodbyMail(AnmGoodbyeMail* mail) {
    mNpc_ClearAnimalPersonalID(&mail->id);
    mail->deliverTo = 0;
}

void mNpc_FirstClearGoodbyMail() {
    mNpc_ClearGoodbyMail(&l_mnpc_goodby_mail);
}

void mNpc_SetGoodbyAnimalMail(AnmGoodbyeMail* mail, Animal_c* animal) {
    PrivateInfo* priv = common_data.saveFilePrivateInfo;
    s32 i;

    if ((animal != NULL) && (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE)) {
        mNpc_CopyAnimalPersonalID(&mail->id, &animal->id);

        for (i = 0; i < PLAYER_NUM; i++) {
            if (mPr_NullCheckPersonalID(&priv->playerId) == FALSE) {
                mail->deliverTo |= 1 << i;
            }
            priv++;
        }
    }
}

s32 mNpc_SetGoodbyMailData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    s32 mailNo;
    s32 res = FALSE;

    if (anm_id->looks < NPC_LOOKS_NUM) {
        mailNo = (anm_id->looks * 3) + 0x20E;
        mailNo += mQst_GetRandom(3);
        mNpc_GetNpcWorldNameAnm(Goodby_animal_name, anm_id);
        mHandbill_Set_free_str(0, pid->playerName, PLAYER_NAME_LEN);
        mHandbill_Set_free_str(1, Goodby_animal_name, ANIMAL_NAME_LEN);
        mHandbill_Set_free_str(3, common_data.landInfo.name, LAND_NAME_SIZE);
        mNpc_LoadMailDataCommon2(mail, pid, anm_id, 0, mNpc_GetPaperType(), mailNo);
        res = TRUE;
    }

    return res;
}

s32 mNpc_SendGoodbyAnimalMailOne(Mail_c* mail, PrivateInfo* priv, s32 playerNo, AnmPersonalID_c* anmId) {
    mHm_hs_c* home;
    UNUSED s32 pad;
    s32 res = FALSE;

    home = &common_data.homes[mHS_get_arrange_idx(playerNo)];

    if ((mPr_NullCheckPersonalID(&priv->playerId) == FALSE) &&
        (mPr_CheckCmpPersonalID(&priv->playerId, &home->ownerID) == TRUE)) {
        s32 freeSpace = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);
        if (freeSpace != -1) {
            if (mNpc_SetGoodbyMailData(mail, &priv->playerId, anmId) == TRUE) {
                mMl_copy_mail(&home->mailbox[freeSpace], mail);
                res = TRUE;
            }
        } else if ((mPO_get_keep_mail_sum() < 5) && (mNpc_SetGoodbyMailData(mail, &priv->playerId, anmId) == TRUE)) {
            res = mPO_receipt_proc(mail, 0);
        }
    }
    return res;
}

void mNpc_SendGoodbyAnimalMail(AnmGoodbyeMail* mail) {
    PrivateInfo* priv = common_data.saveFilePrivateInfo;
    s32 i;

    if (mNpc_CheckFreeAnimalPersonalID(&mail->id) == FALSE) {
        for (i = 0; i < PLAYER_NUM; i++) {
            if ((((mail->deliverTo >> i) & 1) == 1) &&
                (mNpc_SendGoodbyAnimalMailOne(&l_npc_mail, priv, i, &mail->id) == TRUE)) {
                mail->deliverTo &= ~(1 << i);
            }
            priv++;
        }

        if (mail->deliverTo == 0) {
            mNpc_ClearGoodbyMail(mail);
        }
    }
}

void mNpc_SendRegisteredGoodbyMail() {
    mNpc_SendGoodbyAnimalMail(&l_mnpc_goodby_mail);
}

void mNpc_GetRemoveAnimal(Animal_c* transferAnimal, s32 movingOut) {
    PrivateInfo* priv;
    UNUSED s32 pad[4];
    s32 newAnimal;
    Animal_c* animal;
    s32 freeAnimalIdx;
    u8* removeAnimalIdx = &common_data.removeAnimalIdx;
    u8* nowMax = &common_data.nowNpcMax;
    s32 i;

    animal = common_data.animals;
    newAnimal = TRUE;
    priv = common_data.privateInfo;
    if (mLd_PlayerManKindCheck() == 0) {
        if (movingOut == 1) {
            if (*removeAnimalIdx != 0xFF) {
                animal = &common_data.animals[*removeAnimalIdx];
                animal->isMoving = FALSE;
                mNpc_CopyAnimalInfo(transferAnimal, animal);
                mNpc_DestroyHouse(&animal->homeInfo);
                mNpc_ClearAnimalInfo(animal);
                *removeAnimalIdx = 0xFF;
                (*nowMax)--;
            }
        }
    } else {
        if ((mNpc_CheckFreeAnimalInfo(transferAnimal) == FALSE) && (transferAnimal->isMoving == 0)) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (transferAnimal->id.npcId == animal->id.npcId) {
                    newAnimal = 0;
                    break;
                }
                animal++;
            }

            if (transferAnimal->id.npcId == common_data.lastRemovedAnimalId.npcId) {
                newAnimal = FALSE;
            }
        } else {
            newAnimal = FALSE;
        }

        if (newAnimal == TRUE) {
            animal = common_data.animals;
            freeAnimalIdx = mNpc_GetFreeAnimalInfo(common_data.animals, ANIMAL_NUM_MAX);
            if (freeAnimalIdx == -1) {
                animal += mNpc_GetGoodbyAnimalIdx();
                mNpc_DestroyHouse(&animal->homeInfo);
                mNpc_SetGoodbyAnimalMail(&l_mnpc_goodby_mail, animal);
                mNpc_SendRegisteredGoodbyMail();
            } else {
                animal += freeAnimalIdx;
                mNpc_AddNowNpcMax(&common_data.nowNpcMax);
            }
            mNpc_ClearAnimalInfo(animal);
            mNpc_CopyAnimalInfo(animal, transferAnimal);
            animal->homeInfo.blockX = 0xFF;
            animal->homeInfo.blockZ = 0xFF;
            animal->homeInfo.utX = 0xFF;
            animal->homeInfo.utZ = 0xFF;
            mLd_CopyLandName(animal->previousLandName, common_data.privateInfo->playerId.landName);
            animal->previousLandId = common_data.privateInfo->playerId.landId;
            mQst_ClearContest(&animal->contestQuest);
            transferAnimal->isMoving = 1;
            priv->animalMemory.npcId = animal->id.npcId;
            mLd_CopyLandName(priv->animalMemory.landName, mLd_GetLandName());
            mNpc_SetHaveAppeared(animal->id.npcId);
        }
    }
}

s32 mNpc_CheckBuildHouse(s32 blockX, s32 blockZ, u8 utX, u8 utZ) {
    s32 res = FALSE;

    if ((blockX >= 0) && (blockX < 5) && (blockZ >= 0) && (blockZ < 6) && (utX < 0x10) && (utZ < 0x10)) {
        u16 item = common_data.foreground[blockZ][blockX].items[utZ][utX];

        if ((item >= 0x5810) && (item < 0x5825)) {
            res = TRUE;
        }
    }
    return res;
}

void mNpc_SetReturnAnimal(Animal_c* returnAnimal) {
    Anmhome_c* homeInfo;
    Animal_c* foundAnimal = NULL;
    u8* nowMax = &common_data.nowNpcMax;
    Animal_c* animal;
    s32 foundAnimalIdx;

    if (mLd_PlayerManKindCheck() == FALSE && mNpc_CheckFreeAnimalInfo(returnAnimal) == FALSE) {
        if (returnAnimal->isMoving == 0) {
            animal = common_data.animals;
            foundAnimalIdx = mNpc_SearchAnimalinfo(animal, returnAnimal->id.npcId, ANIMAL_NUM_MAX);
            if (foundAnimalIdx != -1) {
                foundAnimal = &animal[foundAnimalIdx];
                mNpc_DestroyHouse(&foundAnimal->homeInfo);
                (*nowMax)--;
                if (common_data.removeAnimalIdx == foundAnimalIdx) {
                    common_data.removeAnimalIdx = 0xFF;
                }
            } else if ((*nowMax) >= ANIMAL_NUM_MAX) {
                foundAnimalIdx = mNpc_GetGoodbyAnimalIdx();
                foundAnimal = &animal[foundAnimalIdx];
                mNpc_SetGoodbyAnimalMail(&l_mnpc_goodby_mail, foundAnimal);
                mNpc_DestroyHouse(&foundAnimal->homeInfo);
                (*nowMax)--;
                if (foundAnimalIdx == common_data.removeAnimalIdx) {
                    common_data.removeAnimalIdx = 0xFF;
                }
            } else {
                foundAnimalIdx = mNpc_GetFreeAnimalInfo(animal, ANIMAL_NUM_MAX);
                if (foundAnimalIdx != -1) {
                    foundAnimal = &animal[foundAnimalIdx];
                }
            }

            if (foundAnimal != NULL) {
                homeInfo = &foundAnimal->homeInfo;
                mNpc_ClearAnimalInfo(foundAnimal);
                mNpc_CopyAnimalInfo(foundAnimal, returnAnimal);
                if (mNpc_CheckBuildHouse(foundAnimal->homeInfo.blockX - 1, foundAnimal->homeInfo.blockZ - 1,
                                         foundAnimal->homeInfo.utX, foundAnimal->homeInfo.utZ - 1) == TRUE) {
                    mNpc_BuildHouseBeforeFieldct(foundAnimal->id.npcId, homeInfo->blockX - 1, homeInfo->blockZ - 1,
                                                 homeInfo->utX, homeInfo->utZ - 1);
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
            mNpc_CopyAnimalPersonalID(&common_data.lastRemovedAnimalId, &returnAnimal->id);
        }
        mNpc_ClearAnimalInfo(returnAnimal);
    }
}

void mNpc_AddActor_inBlock(FieldMakeMoveActor* moveActor, u8 bx, u8 bz) {
    mNpc_AddNpc_inNpcRoom(moveActor, bx, bz);
}

void mNpc_SetNpcNameID(Animal_c* animal, s32 count) {
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

void mNpc_LoadNpcNameString(char* name, u8 npcId) {
    char npcName[ANIMAL_NAME_LEN];
    s32 offset;

    if (npcId < 0xFF) {
        offset = npcId * ANIMAL_NAME_LEN;
        DmaMgr_RequestSyncDebug(npcName, (offset + 8) + SEGMENT_ROM_START(segment_00E04000), 8, "../m_npc.c", 0x1916);
        mem_copy((u8*)name, (u8*)npcName, ANIMAL_NAME_LEN);
    }
}

void mNpc_GetNpcWorldNameTableNo(char* name, u16 npcId) {
    char* worldName = l_no_name_npc_name;
    char npcName[PLAYER_NAME_LEN];

    if (name != NULL) {
        u8 id = npcId & 0xFF;

        if ((ACTOR_FGNAME_GET_F000(npcId) == FGNAME_F000_E) && (id < 0xFF)) {
            mNpc_LoadNpcNameString(npcName, id);
            worldName = npcName;
        }
    }
    mPr_CopyPlayerName(name, worldName);
}

void mNpc_GetNpcWorldNameAnm(char* name, AnmPersonalID_c* anmId) {
    char* worldName = l_no_name_npc_name;
    char npcName[PLAYER_NAME_LEN];

    if (anmId != NULL) {
        if (ACTOR_FGNAME_GET_F000(anmId->npcId) == FGNAME_F000_E) {
            mNpc_GetNpcWorldNameTableNo(npcName, anmId->npcId);
            worldName = npcName;
        }
    }
    mPr_CopyPlayerName(name, worldName);
}

void mNpc_GetNpcWorldNameP(char* name, u16 npcId) {
    s32 i;
    SpecialNpcData* sp = l_sp_actor_name;
    char* worldName = l_no_name_npc_name;

    for (i = 0; i < ARRAY_COUNT(l_sp_actor_name); i++) {
        if (npcId == sp->specialNpcId) {
            mString_Load_StringFromRom(load_name, PLAYER_NAME_LEN, sp->nameStringNumber);
            worldName = load_name;
            break;
        }
        sp++;
    }
    mPr_CopyPlayerName(name, worldName);
}

void mNpc_GetNpcWorldName(char* name, Npc* npc) {
    char* worldName = l_no_name_npc_name;
    char npcName[PLAYER_NAME_LEN];

    if ((name != NULL) && (npc != NULL)) {
        if (npc->actor.part == ACTOR_PART_NPC) {
            if (npc->npcInfo.animal != NULL) {
                mNpc_GetNpcWorldNameAnm(npcName, &npc->npcInfo.animal->id);
            } else {
                mNpc_GetNpcWorldNameP(npcName, npc->actor.fgName);
            }
        } else {
            mNpc_GetNpcWorldNameP(npcName, npc->actor.fgName);
        }
        worldName = npcName;
    }
    mPr_CopyPlayerName(name, worldName);
}

void mNpc_GetRandomAnimalName(char* dst) {
    Animal_c* animal = common_data.animals;
    u16 bitfield = 0;
    s32 num = 0;
    s32 select;
    s32 i;

    if (dst != NULL) {

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                num++;
                bitfield |= (1 << i);
            }
            animal++;
        }

        if (num > 0) {
            animal = common_data.animals;
            select = RANDOM(num);

            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (((bitfield >> i) & 1) == 1) {
                    if (select == 0) {
                        mNpc_GetNpcWorldNameAnm(dst, &animal->id);
                        break;
                    } else {
                        select--;
                    }
                }
                animal++;
            }
        }
    }
}

void mNpc_GetAnimalPlateName(char* dst, xyz_t wpos) {
    UNUSED s32 pad;
    Animal_c* animal = common_data.animals;
    s32 bx;
    s32 bz;
    s32 utX;
    s32 utZ;
    s32 i;
    Anmhome_c* home;

    if (mFI_Wpos2BkandUtNuminBlock(&bx, &bz, &utX, &utZ, wpos) == TRUE) {

        utX++;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                home = &animal->homeInfo;

                if (home->blockX == bx && home->blockZ == bz && home->utX == utX && home->utZ == utZ) {
                    mNpc_GetNpcWorldNameAnm(dst, &animal->id);
                    break;
                }
            }

            animal++;
        }
    }
}

NpcLooks mNpc_GetNpcLooks(Actor* actor) {
    NpcLooks looks = NPC_LOOKS_BOY;

    if (actor != NULL && actor->part == ACTOR_PART_NPC) {
        Npc* npc = (Npc*)actor;

        if (npc->npcInfo.animal != NULL) {
            looks = npc->npcInfo.animal->id.looks;
        }
    }

    return looks;
}

NpcSex mNpc_GetActorSex(u16 npcId) {
    SpecialNpcData* spInfo = l_sp_actor_name;
    NpcSex sex = NPC_SEX_MALE;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(l_sp_actor_name); i++) {
        if (npcId == spInfo->specialNpcId) {
            sex = spInfo->sex;
            break;
        }

        spInfo++;
    }

    return sex;
}

NpcSex mNpc_GetLooks2Sex(NpcLooks looks) {
    NpcSex sex = NPC_SEX_OTHER;

    if (looks == NPC_LOOKS_GIRL || looks == NPC_LOOKS_KO_GIRL || looks == NPC_LOOKS_NANIWA_LADY) {
        sex = NPC_SEX_FEMALE;
    } else if (looks == NPC_LOOKS_BOY || looks == NPC_LOOKS_SPORT_MAN || looks == NPC_LOOKS_GRIM_MAN) {
        sex = NPC_SEX_MALE;
    }

    return sex;
}

NpcSex mNpc_GetAnimalSex(Animal_c* animal) {
    NpcSex sex = NPC_SEX_OTHER;

    if (animal != NULL) {
        sex = mNpc_GetLooks2Sex(animal->id.looks);
    }

    return sex;
}

NpcSex mNpc_GetNpcSex(Actor* actor) {
    NpcSex sex;

    if (actor != NULL && actor->part == ACTOR_PART_NPC) {
        Npc* npc = (Npc*)actor;

        sex = mNpc_GetAnimalSex(npc->npcInfo.animal);
    } else {
        sex = mNpc_GetActorSex(actor->fgName);
    }

    return sex;
}

s32 mNpc_GetNpcSoundSpecNotAnimal(u16 npcId) {
    SpecialNpcData* spInfo = l_sp_actor_name;
    s32 soundSpec = 2;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(l_sp_actor_name); i++) {
        if (npcId == spInfo->specialNpcId) {
            soundSpec = spInfo->soundId;
            break;
        }

        spInfo++;
    }

    return soundSpec;
}

s32 mNpc_GetNpcSoundSpec(Actor* actor) {
    static s32 spec_table[NPC_LOOKS_NUM] = { 4, 4, 2, 2, 3, 4 };

    s32 soundSpec = 2;
    u8 looks;

    if (actor != NULL) {
        if (actor->part == ACTOR_PART_NPC) {
            Npc* npc = (Npc*)actor;

            if (npc->npcInfo.animal != NULL) {
                looks = npc->npcInfo.animal->id.looks;

                if (looks >= NPC_LOOKS_NUM) {
                    looks = NPC_LOOKS_BOY;
                }

                soundSpec = spec_table[looks];
            } else {
                soundSpec = mNpc_GetNpcSoundSpecNotAnimal(actor->fgName);
            }
        } else {
            soundSpec = mNpc_GetNpcSoundSpecNotAnimal(actor->fgName);
        }
    }

    return soundSpec;
}

void mNpc_GetMsg(UNUSED s32 arg) {
}

void mNpc_InitNpcAllInfo(s32 mallocFlag) {
    common_data.nowNpcMax = NPC_LOOKS_NUM;
    common_data.removeAnimalIdx = 0xFF;
    mNpc_ClearAnimalPersonalID(&common_data.lastRemovedAnimalId);
    mNpc_ClearAnyAnimalInfo(common_data.animals, ANIMAL_NUM_MAX);
    mNpc_DecideLivingNpcMax(common_data.animals, NPC_LOOKS_NUM, mallocFlag);
    mNpc_SetNpcNameID(common_data.animals, ANIMAL_NUM_MAX);
}

s32 mNpc_CheckGrowFieldRank() {
    static s32 npc_grow_prob[7] = { 40, 50, 60, 70, 80, 90, 100 };

    s32 rank = mFAs_GetFieldRank();
    UNUSED s32 pad;
    s32 res = FALSE;

    if (rank >= 0 && rank < 7) {
        if (RANDOM(100) < npc_grow_prob[rank]) {
            res = TRUE;
        }
    }

    return res;
}

s32 mNpc_CheckGrow() {
    UNUSED s32 pad;
    lbRTC_time_c* rtcTime = &common_data.time.rtcTime;
    lbRTC_time_c* lastGrowTime = &common_data.lastGrowTime;
    s32 res = FALSE;

    if (common_data.nowNpcMax < ANIMAL_NUM_MAX) {
        if (lbRTC_IsEqualTime(&mTM_rtcTime_clear_code, lastGrowTime, lbRTC_CHECK_ALL) == TRUE) {
            lbRTC_TimeCopy(lastGrowTime, rtcTime);
        } else if (mNpc_CheckGrowFieldRank() == TRUE) {
            u32 interval;

            if (lbRTC_IsOverTime(lastGrowTime, rtcTime) == lbRTC_OVER) {
                interval = lbRTC_IntervalTime(rtcTime, lastGrowTime);
            } else {
                interval = lbRTC_IntervalTime(lastGrowTime, rtcTime);
            }

            if (interval >= (lbRTC_HOURS_PER_DAY * lbRTC_MINUTES_PER_HOUR) && mLd_PlayerManKindCheck() == FALSE &&
                mNpc_CheckFriendAllAnimal(&common_data.privateInfo->playerId) == TRUE) {
                res = TRUE;
            }
        }
    }

    return res;
}

u8 mNpc_GetMinLooks(u8* bitfield, s32* minLooksNum) {
    s32 minLooksAnimal = ANIMAL_NUM_MAX;
    u8 minLooks = NPC_LOOKS_NUM;
    u8 i;

    bitfield[0] = 0;
    minLooksNum[0] = 0;

    for (i = 0; i < NPC_LOOKS_NUM; i++) {
        s32 notAppearedNum = mNpc_GetLooks2NotHaveAppearedNum(i);

        if (notAppearedNum > 0) {
            s32 sameLooksNum = mNpc_GetSameLooksNum(i);

            if (minLooksAnimal > sameLooksNum) {
                minLooksAnimal = sameLooksNum;
                minLooks = i;
                bitfield[0] = 0;
                bitfield[0] |= (1 << i);
                minLooksNum[0] = 1;
            } else if (minLooksAnimal == sameLooksNum) {
                bitfield[0] |= (1 << i);
                minLooksNum[0]++;
            }
        }
    }

    if (bitfield[0] == 0 && minLooksNum[0] == 0) {
        mNpc_ResetHaveAppeared_common(common_data.npcUsedTable, common_data.animals);

        for (i = 0; i < NPC_LOOKS_NUM; i++) {
            bitfield[0] |= (1 << i);
            minLooksNum[0]++;
        }
    }

    if (minLooksNum[0] > 1) {
        minLooks = NPC_LOOKS_NUM;
    }

    return minLooks;
}

NpcSex mNpc_GetMinSex() {
    Animal_c* animal = common_data.animals;
    s32 males = 0;
    s32 females = 0;
    NpcSex res;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            switch (mNpc_GetAnimalSex(animal)) {
                case NPC_SEX_MALE:
                    males++;
                    break;
                case NPC_SEX_FEMALE:
                    females++;
                    break;
                default:
                    break;
            }
        }

        animal++;
    }

    if (females < males) {
        res = NPC_SEX_MALE;
    } else {
        res = NPC_SEX_FEMALE;
    }

    return res;
}

s32 mNpc_GrowLooksNpcIdx(u8 looks) {
    u8* looks_table = npc_looks_table;
    s32 npc_idx;
    s32 candidates;
    s32 res;
    s32 i;
    s32 j;
    s32 selected;

    candidates = 0;
    res = -1;
    npc_idx = 0;

    if (looks < NPC_LOOKS_NUM) {
        bzero(candidate_table, sizeof(candidate_table));

        for (i = 0; i < ARRAY_COUNT(candidate_table); i++) {
            for (j = 0; j < 8; j++) {
                if (looks == *looks_table) {
                    if ((mNpc_SearchAnimalinfo(common_data.animals, ((i * 8) + j) | 0xE000, ANIMAL_NUM_MAX) == -1) &&
                        (mNpc_GetHaveAppeared_idx(npc_idx) == FALSE)) {
                        candidates++;
                        candidate_table[i] |= 1 << j;
                    }
                }

                npc_idx++;
                looks_table++;

                if (npc_idx >= NPC_NUM) {
                    break;
                }
            }

            if (npc_idx >= NPC_NUM) {
                break;
            }
        }
    }

    if (candidates > 0) {
        selected = RANDOM(candidates);
        npc_idx = 0;

        for (i = 0; i < ARRAY_COUNT(candidate_table); i++) {
            if (npc_idx >= NPC_NUM) {
                break;
            }

            for (j = 0; j < 8; j++) {
                if (npc_idx >= NPC_NUM) {
                    break;
                }

                if (((candidate_table[i] >> j) & 1) == 1) {
                    if (selected <= 0) {
                        res = npc_idx;
                        break;
                    } else {
                        selected--;
                    }
                }

                npc_idx++;
            }

            if (res != -1) {
                break;
            }
        }
    }

    return res;
}

void mNpc_SetAnimalInfoNpcIdx(Animal_c* animal, s32 idx) {
    u32 offset;

    if (idx >= 0 && idx < NPC_NUM) {
        offset = idx * 6;
        DmaMgr_RequestSyncDebug(&npc_def_list, (offset + SEGMENT_ROM_START(segment_00E03000)), 8, "../m_npc.c", 0x1CB3);
        mNpc_SetDefAnimalInfo(animal, idx | 0xE000, npc_looks_table[idx], &npc_def_list);
    }
}

s32 mNpc_SetGrowNpc(u8 looks) {
    Animal_c* animal = common_data.animals;
    UNUSED s32 pad;
    s32 idx;
    s32 npcIdx;

    idx = mNpc_UseFreeAnimalInfo(animal, ANIMAL_NUM_MAX);
    if (idx != -1) {
        animal += idx;
        npcIdx = mNpc_GrowLooksNpcIdx(looks);

        if (npcIdx != -1) {
            mNpc_SetAnimalInfoNpcIdx(animal, npcIdx);
            animal->movedIn = TRUE;
        } else {
            idx = -1;
        }
    }

    return idx;
}

void mNpc_Grow() {
    u8 minLooks;
    u8 minLooksBitfield;
    s32 minLooksNum;
    u8 bitfieldSave;
    s32 looksSave;
    NpcSex minSex;
    s32 selected;
    s32 growIdx;
    u8 looks;

    if (mNpc_CheckGrow() == TRUE) {
        mNpc_ResetHaveAppeared();
        lbRTC_TimeCopy(&common_data.lastGrowTime, &common_data.time.rtcTime);

        minLooks = mNpc_GetMinLooks(&minLooksBitfield, &minLooksNum);

        /* Multiple personalities are tied for minimum */
        if (minLooks == NPC_LOOKS_NUM) {
            minSex = mNpc_GetMinSex();
            if (minSex != NPC_SEX_OTHER) {
                bitfieldSave = minLooksBitfield;
                looksSave = minLooksNum;

                /* Clear any tied minimum personalities which are of the greater sex */
                for (looks = 0; looks < NPC_LOOKS_NUM; looks++) {
                    if (((minLooksBitfield >> looks) & 1) == 1 && mNpc_GetLooks2Sex(looks) != minSex) {
                        minLooksBitfield &= ~(1 << looks);
                        minLooksNum--;
                    }
                }

                if (minLooksNum == 0 || minLooksNum == looksSave) {
                    /* Either all personalities were cleared or none were, so restore the prior state */
                    minLooksBitfield = bitfieldSave;
                    minLooksNum = looksSave;
                }
            }

            selected = RANDOM(minLooksNum);

            for (looks = 0; looks < NPC_LOOKS_NUM; looks++) {
                if (((minLooksBitfield >> looks) & 1) == 1) {
                    if (selected <= 0) {
                        minLooks = looks;
                        break;
                    } else {
                        selected--;
                    }
                }
            }
        }

        growIdx = mNpc_SetGrowNpc(minLooks);

        if (growIdx >= 0 && growIdx < ANIMAL_NUM_MAX) {
            mNpc_SetNpcNameID(&common_data.animals[growIdx], 1);
            mNpc_AddNowNpcMax(&common_data.nowNpcMax);
        }
    }
}

s32 mNpc_CheckNpcSet_fgcol(u16 arg0, u32 arg1) {
    s32 res = FALSE;

    if (func_8008D7B0_jp(arg0)) {
        res = func_8007244C_jp(arg1);
    }

    return res;
}

s32 mNpc_CheckNpcSet_fgcol_hard(u16 arg0, u32 arg1) {
    s32 res = FALSE;

    if (func_8008D7B0_jp(arg0) && (arg1 <= 2 || (arg1 >= 4 && arg1 <= 6) || arg1 == 7)) {
        res = TRUE;
    }

    return res;
}

s32 mNpc_CheckNpcSet(s32 bx, s32 bz, s32 ut_x, s32 ut_z) {
    mCoBG_unkStructUnion* collision = mFI_GetBkNum2ColTop(bx, bz);
    u16* items = mFI_BkNumtoUtFGTop(bx, bz);
    s32 res = FALSE;

    if (collision != NULL && items != NULL) {
        res = mNpc_CheckNpcSet_fgcol(items[ut_z * UT_X_NUM + ut_x], collision[ut_z * UT_X_NUM + ut_x].data.unk6);
    }

    return res;
}

s32 mNpc_GetMakeUtNuminBlock_hard_area(s32* utX, s32* utZ, s32 bx, s32 bz, s32 restrictArea) {
    mCoBG_unkStructUnion* col;
    u16* items;
    s32 nowUtX;
    s32 nowUtZ;
    s32 minUtX;
    s32 minUtZ;
    s32 idx;
    s32 res;
    s32 i;
    s32 j;

    col = mFI_GetBkNum2ColTop(bx, bz);
    items = mFI_BkNumtoUtFGTop(bx, bz);
    minUtX = UT_X_NUM;
    minUtZ = UT_Z_NUM;
    res = FALSE;

    if (restrictArea < 0 || restrictArea > 9) {
        return FALSE;
    }

    if (items != NULL && col != NULL) {
        for (i = restrictArea; i < UT_Z_NUM - restrictArea; i++) {
            for (j = restrictArea; j < UT_X_NUM - restrictArea; j++) {
                idx = i * UT_X_NUM + j;
                if (mNpc_CheckNpcSet_fgcol_hard(items[idx], col[idx].data.unk6) == TRUE) {
                    if (col[idx].data.unk1 == col[idx].data.unk2 && col[idx].data.unk1 == col[idx].data.unk3 &&
                        col[idx].data.unk1 == col[idx].data.unk4 && col[idx].data.unk1 == col[idx].data.unk5) {
                        nowUtX = 8 - j;
                        nowUtZ = 8 - i;

                        nowUtX = ABS(nowUtX);
                        nowUtZ = ABS(nowUtZ);

                        if (minUtX > nowUtX && minUtZ > nowUtZ) {
                            *utX = j;
                            *utZ = i;
                            minUtX = nowUtX;
                            minUtZ = nowUtZ;
                            res = TRUE;
                        }
                    }
                }
            }
        }
    }

    return res;
}

s32 mNpc_GetMakeUtNuminBlock_area(s32* utX, s32* utZ, s32 bx, s32 bz, s32 restrictArea) {
    s32 candidates;
    mCoBG_unkStructUnion* col;
    u16* fgTop;
    s32 i;
    s32 j;
    s32 rand;
    s32 res;

    u16* fgPtr = fg_flag;

    col = mFI_GetBkNum2ColTop(bx, bz);
    fgTop = mFI_BkNumtoUtFGTop(bx, bz);
    candidates = 0;
    res = FALSE;

    if (restrictArea < 0 || restrictArea > 9) {
        return FALSE;
    }

    bzero(fg_flag, sizeof(fg_flag));

    if (fgTop != NULL && col != NULL) {
        for (i = restrictArea; i < UT_Z_NUM - restrictArea; i++) {
            for (j = restrictArea; j < UT_X_NUM - restrictArea; j++) {
                if (mNpc_CheckNpcSet_fgcol(fgTop[i * UT_X_NUM + j], col[i * UT_X_NUM + j].data.unk6) == TRUE) {
                    *fgPtr |= 1 << j;
                    candidates++;
                }
            }

            fgPtr++;
        }
    }

    fgPtr = fg_flag;
    if (candidates > 0) {
        rand = RANDOM(candidates);

        for (i = restrictArea; i < UT_Z_NUM - restrictArea; i++) {
            for (j = restrictArea; j < UT_X_NUM - restrictArea; j++) {
                if (((*fgPtr >> j) & 1) == 1) {
                    if (rand == 0) {
                        *utX = j;
                        *utZ = i;
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

            fgPtr++;
        }
    }

    return res;
}

s32 mNpc_GetMakeUtNuminBlock(s32* utX, s32* utZ, s32 bx, s32 bz) {
    return mNpc_GetMakeUtNuminBlock_area(utX, utZ, bx, bz, 1);
}

void mNpc_ClearTalkInfo() {
    NpcTalkInfo* talkInfo = l_npc_talk_info;
    s32 i;

    bzero(talkInfo, sizeof(l_npc_talk_info));

    for (i = 0; i < ARRAY_COUNT(l_npc_talk_info); i++) {
        talkInfo->questRequest = TRUE;
        talkInfo++;
    }
}

void mNpc_TimerCountDown(NpcTalkInfo* talkInfo) {
    if (talkInfo->timer > 0) {
        talkInfo->timer--;
    }
}

NpcTemper l_npc_temper[NPC_FEEL_NUM] = { { 4000, 12, 15 }, { 3000, 10, 13 }, { 4000, 12, 15 },
                                         { 4000, 10, 13 }, { 5000, 9, 12 },  { 5000, 9, 12 } };

void mNpc_SetUnlockTimer(u16* unlockTimer, u16* resetTimer, s32 feel) {
    unlockTimer[0] = l_npc_temper[feel].unlockTimer;
    resetTimer[0] = unlockTimer[0];
}

s32 mNpc_CountTalkNum(s32 animalIdx, s32 feel) {
    s32 res = FALSE;

    if (animalIdx != -1) {
        NpcTalkInfo* talkInfo = &l_npc_talk_info[animalIdx];

        if (talkInfo->talkNum < l_npc_temper[feel].talkNumMax && talkInfo->timer > 0) {
            talkInfo->talkNum++;
            res = TRUE;
        }
    }

    return res;
}

s32 mNpc_CheckOverImpatient(s32 animalIdx, s32 feel) {
    s32 res = FALSE;

    if (animalIdx != -1) {
        NpcTalkInfo* talkInfo = &l_npc_talk_info[animalIdx];

        if (talkInfo->talkNum >= l_npc_temper[feel].overImpatientNum) {
            res = TRUE;
        }
    }

    return res;
}

s32 mNpc_GetOverImpatient(s32 animalIdx, s32 feel) {
    s32 patience = NPC_PATIENCE_NORMAL;

    if (animalIdx != -1) {
        NpcTalkInfo* talkInfo = &l_npc_talk_info[animalIdx];

        if (talkInfo->talkNum >= l_npc_temper[feel].overImpatientNum) {
            if (talkInfo->talkNum >= l_npc_temper[feel].talkNumMax) {
                patience = NPC_PATIENCE_ANNOYED;
            } else {
                patience = NPC_PATIENCE_MILDLY_ANNOYED;
            }
        }
    }

    return patience;
}

s32 mNpc_CheckQuestRequest(s32 animalIdx) {
    s32 res = FALSE;

    if (animalIdx != -1) {
        NpcTalkInfo* talkInfo = &l_npc_talk_info[animalIdx];

        if (talkInfo->questRequest == TRUE) {
            res = TRUE;
        }
    }

    return res;
}

void mNpc_SetQuestRequestOFF(s32 animalIdx, s32 feel) {
    NpcTalkInfo* talkInfo = &l_npc_talk_info[animalIdx];

    if (animalIdx >= 0 && animalIdx < ARRAY_COUNT(l_npc_talk_info)) {
        if (talkInfo->questRequest == TRUE) {
            mNpc_SetUnlockTimer(&talkInfo->unlockTimer, &talkInfo->resetTimer, feel);
        }

        talkInfo->questRequest = FALSE;
    }
}

void mNpc_UnlockTimerCountDown(NpcTalkInfo* talkInfo) {
    if (talkInfo != NULL && talkInfo->unlockTimer > 0 && talkInfo->unlockTimer > (talkInfo->resetTimer - 1000)) {
        talkInfo->unlockTimer--;
    }
}

void mNpc_TalkInfoMove() {
    NpcTalkInfo* talkInfo = l_npc_talk_info;
    s32 i;

    if (mFI_CheckPlayerWade(1) == TRUE) {
        for (i = 0; i < ARRAY_COUNT(l_npc_talk_info); i++) {
            talkInfo->resetTimer = talkInfo->unlockTimer;
            talkInfo++;
        }
    }

    talkInfo = l_npc_talk_info;
    for (i = 0; i < ARRAY_COUNT(l_npc_talk_info); i++) {
        mNpc_TimerCountDown(talkInfo);
        mNpc_UnlockTimerCountDown(talkInfo);

        if (talkInfo->unlockTimer == 0 && talkInfo->resetTimer != 0) {
            talkInfo->talkNum = 0;
            talkInfo->questRequest = TRUE;
            talkInfo->resetTimer = 0;
        }

        talkInfo++;
    }
}

void mNpc_TalkEndMove(s32 animalIdx, s32 feel) {
    UNUSED s32 pad;
    if (animalIdx >= 0 && animalIdx < ARRAY_COUNT(l_npc_talk_info) && feel >= 0 && feel < NPC_FEEL_NUM) {
        NpcTalkInfo* talkInfo = &l_npc_talk_info[animalIdx];
        talkInfo->timer = 1000;

        if (mNpc_CountTalkNum(animalIdx, feel) == TRUE && mNpc_CheckOverImpatient(animalIdx, feel) == TRUE) {
            mNpc_SetUnlockTimer(&talkInfo->unlockTimer, &talkInfo->resetTimer, feel);
        }
    }
}

s32 mNpc_GetNpcFloorNo() {
    u16 field_id = mFI_GetFieldId();
    u16 owner_name = common_data.houseOwnerName;
    s32 floor_no = -1;

    if (((field_id & 0xF000) == 0x4000) && (owner_name != 0) && (owner_name != 0xFFFF)) {
        s32 idx = mNpc_SearchAnimalinfo(common_data.animals, owner_name, ANIMAL_NUM_MAX);

        floor_no = common_data.npclist[idx].houseData.floorId;
    }

    return floor_no;
}

void mNpc_SetTalkBee() {
    if (common_data.beeStingFlag != TRUE) {
        Animal_c* animal = common_data.animals;
        NpcList* npclist = common_data.npclist;
        s32 i;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                npclist->flags.beeSting = TRUE;
            }

            animal++;
            npclist++;
        }
    }
}

u8 mNpc_GetFishCompleteTalk(NpcList* npclist) {
    u8 res = TRUE;

    if (npclist != NULL) {
        res = npclist->flags.fishComplete;
    }

    return res;
}

u8 mNpc_GetInsectCompleteTalk(NpcList* npclist) {
    u8 res = TRUE;

    if (npclist != NULL) {
        res = npclist->flags.insectComplete;
    }

    return res;
}

void mNpc_SetFishCompleteTalk(NpcList* npclist) {
    if (npclist != NULL) {
        npclist->flags.fishComplete = TRUE;
    }
}

void mNpc_SetInsectCompleteTalk(NpcList* npclist) {
    if (npclist != NULL) {
        npclist->flags.insectComplete = TRUE;
    }
}

void mNpc_SetNpcHomeYpos() {
    Animal_c* animal = common_data.animals;
    NpcList* npclist = common_data.npclist;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            npclist->homePosition.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(npclist->homePosition, 0.0f);
        }

        animal++;
        npclist++;
    }
}

void mNpc_PrintRemoveInfo(gfxprint* gfxprint) {
    Animal_c* remove_anm = NULL;
    Animal_c* in_anm = mNpc_GetInAnimalP();
    u8 removeAnimalIdx = common_data.removeAnimalIdx;

    gfxprint_color(gfxprint, 200, 150, 50, 255);
    gfxprint_locate8x8(gfxprint, 3, 10);

    if (removeAnimalIdx < ANIMAL_NUM_MAX) {
        remove_anm = &common_data.animals[removeAnimalIdx];
    }

    if (remove_anm != NULL) {
        if (in_anm != NULL) {
            gfxprint_printf(gfxprint, "%4x %3d %3d", removeAnimalIdx, remove_anm->id.nameId, in_anm->id.nameId);
        } else {
            gfxprint_printf(gfxprint, "%4x %3d ---", removeAnimalIdx, remove_anm->id.nameId);
        }
    } else if (in_anm != NULL) {
        gfxprint_printf(gfxprint, "%4x --- %3d", removeAnimalIdx, in_anm->id.nameId);
    } else {
        gfxprint_printf(gfxprint, "%4x --- ---", removeAnimalIdx);
    }
}

s32 l_mnpc_animal_idx = -1;

void mNpc_SetTalkAnimalIdx_fdebug(AnmPersonalID_c* anm_id) {
    if (anm_id != NULL) {
        l_mnpc_animal_idx = mNpc_SearchAnimalPersonalID(anm_id);
    }
}

void mNpc_PrintFriendship_fdebug(gfxprint* gfxprint) {
    Anmmem_c* memory;
    PrivateInfo* priv;
    int x = 3;
    int y = 19;
    int i;

    if (l_mnpc_animal_idx >= 0 && l_mnpc_animal_idx < ANIMAL_NUM_MAX) {
        memory = common_data.animals[l_mnpc_animal_idx].memories;

        if (memory != NULL) {
            gfxprint_color(gfxprint, 250, 100, 170, 255);
            gfxprint_locate8x8(gfxprint, 3, 18);
            priv = common_data.privateInfo;

            if (priv != NULL) {
                gfxprint_printf(gfxprint, "%4x ", priv->playerId.playerId);
            } else {
                gfxprint_printf(gfxprint, "**** ");
            }

            gfxprint_color(gfxprint, 50, 150, 50, 255);

            for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
                if (i == 4) {
                    y++;
                    x = 3;
                }

                gfxprint_locate8x8(gfxprint, x, y);
                if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
                    gfxprint_printf(gfxprint, "%4x %3d ", memory->memoryPlayerId.playerId, memory->friendship);
                } else {
                    gfxprint_printf(gfxprint, "**** *** ");
                }

                memory++;
                x += 9;
            }
        }
    }
}
