#include "m_npc_walk.h"
#include "m_common_data.h"
#include "m_npc.h"
#include "m_random_field.h"
#include "sys_math.h"
#include "m_field_info.h"
#include "macros.h"
#include "attributes.h"

#define mNpcW_TIME_2_SEC(hour, min, sec) ((hour)*3600 + (min)*60 + (sec))
#define mNpcW_MAKE_SCHEDULE_TABLE(goal_data) \
    { goal_data, ARRAY_COUNT(goal_data) }

s32 l_goal_block[NPCW_GOAL_BLOCK_NUM][2];
s32 l_arrive_stay_count[ANIMAL_NUM_MAX];

u8 l_girl_time_12[] = { NPCW_GOAL_SHRINE, NPCW_GOAL_HOME, NPCW_GOAL_ALONE };
u8 l_girl_time_18_30[] = { NPCW_GOAL_SHRINE, NPCW_GOAL_HOME };

NpcWalkGoalData l_girl_goal_data[] = {
    { NULL, 0, mNpcW_TIME_2_SEC(6, 0, 0) },
    { l_girl_time_12, ARRAY_COUNT(l_girl_time_12), mNpcW_TIME_2_SEC(12, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(13, 0, 0) },
    { l_girl_time_18_30, ARRAY_COUNT(l_girl_time_18_30), mNpcW_TIME_2_SEC(18, 30, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) },
};

NpcWalkGoalDataTable l_girl_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_girl_goal_data);

u8 l_kogirl_time_ed[] = { NPCW_GOAL_SHRINE, NPCW_GOAL_HOME };

NpcWalkGoalData l_kogirl_goal_data[] = { { l_kogirl_time_ed, ARRAY_COUNT(l_kogirl_time_ed),
                                           mNpcW_TIME_2_SEC(24, 0, 0) } };

NpcWalkGoalDataTable l_kogirl_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_kogirl_goal_data);

u8 l_boy_time_12[] = { NPCW_GOAL_ALONE };
u8 l_boy_time_19_30[] = { NPCW_GOAL_SHRINE, NPCW_GOAL_HOME };

NpcWalkGoalData l_boy_goal_data[] = {
    { NULL, 0, mNpcW_TIME_2_SEC(9, 0, 0) },
    { l_boy_time_12, ARRAY_COUNT(l_boy_time_12), mNpcW_TIME_2_SEC(12, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(14, 0, 0) },
    { l_boy_time_19_30, ARRAY_COUNT(l_boy_time_19_30), mNpcW_TIME_2_SEC(19, 30, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) },
};

NpcWalkGoalDataTable l_boy_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_boy_goal_data);

u8 l_sports_man_time_12[] = { NPCW_GOAL_SHRINE, NPCW_GOAL_HOME, NPCW_GOAL_ALONE, NPCW_GOAL_ALONE };
u8 l_sports_man_time_23[] = { NPCW_GOAL_SHRINE, NPCW_GOAL_SHRINE, NPCW_GOAL_HOME, NPCW_GOAL_HOME, NPCW_GOAL_ALONE };

NpcWalkGoalData l_sports_man_goal_data[] = {
    { NULL, 0, mNpcW_TIME_2_SEC(6, 30, 0) },
    { l_sports_man_time_12, ARRAY_COUNT(l_sports_man_time_12), mNpcW_TIME_2_SEC(12, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(12, 30, 0) },
    { l_sports_man_time_23, ARRAY_COUNT(l_sports_man_time_23), mNpcW_TIME_2_SEC(23, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) }
};

NpcWalkGoalDataTable l_sports_man_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_sports_man_goal_data);

u8 l_grim_man_time_ed[] = { NPCW_GOAL_SHRINE, NPCW_GOAL_SHRINE, NPCW_GOAL_SHRINE, NPCW_GOAL_ALONE, NPCW_GOAL_ALONE,
                            NPCW_GOAL_ALONE,  NPCW_GOAL_ALONE,  NPCW_GOAL_ALONE,  NPCW_GOAL_ALONE, NPCW_GOAL_ALONE };

NpcWalkGoalData l_grim_man_goal_data[] = {
    { l_grim_man_time_ed, ARRAY_COUNT(l_grim_man_time_ed), mNpcW_TIME_2_SEC(24, 0, 0) },
};

NpcWalkGoalDataTable l_grim_man_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_grim_man_goal_data);

u8 l_naniwa_lady_time_1_30[] = { NPCW_GOAL_SHRINE, NPCW_GOAL_SHRINE, NPCW_GOAL_SHRINE, NPCW_GOAL_SHRINE,
                                 NPCW_GOAL_SHRINE, NPCW_GOAL_SHRINE, NPCW_GOAL_SHRINE, NPCW_GOAL_ALONE,
                                 NPCW_GOAL_ALONE,  NPCW_GOAL_ALONE };
u8 l_naniwa_lady_time_13[] = { NPCW_GOAL_HOME };
u8 l_naniwa_lady_time_21[] = { NPCW_GOAL_SHRINE, NPCW_GOAL_SHRINE, NPCW_GOAL_HOME, NPCW_GOAL_HOME, NPCW_GOAL_ALONE };

NpcWalkGoalData l_naniwa_lady_goal_data[] = {
    { l_naniwa_lady_time_1_30, ARRAY_COUNT(l_naniwa_lady_time_1_30), mNpcW_TIME_2_SEC(1, 30, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(10, 0, 0) },
    { l_naniwa_lady_time_13, ARRAY_COUNT(l_naniwa_lady_time_13), mNpcW_TIME_2_SEC(13, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(14, 0, 0) },
    { l_naniwa_lady_time_21, ARRAY_COUNT(l_naniwa_lady_time_21), mNpcW_TIME_2_SEC(21, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(22, 0, 0) },
    { l_naniwa_lady_time_1_30, ARRAY_COUNT(l_naniwa_lady_time_1_30), mNpcW_TIME_2_SEC(24, 0, 0) },
};

NpcWalkGoalDataTable l_naniwa_lady_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_naniwa_lady_goal_data);

NpcWalkGoalDataTable* l_looks_goal_table[NPC_LOOKS_NUM] = { &l_girl_goal_table,     &l_kogirl_goal_table,
                                                            &l_boy_goal_table,      &l_sports_man_goal_table,
                                                            &l_grim_man_goal_table, &l_naniwa_lady_goal_table };

NpcWalkGoalData* mNpcW_GetGoalDataInfo(s32 looks, s32 time) {
    NpcWalkGoalDataTable* table = l_looks_goal_table[looks];
    NpcWalkGoalData* data = table->data;
    s32 i;

    for (i = 0; i < table->count; i++) {
        if (data->time > time) {
            break;
        }

        data++;
    }

    if (i == table->count) {
        data = &table->data[table->count - 1];
    }

    return data;
}

void mNpcW_ClearNpcWalkAppear(NpcWalkAppear* info) {
    info->status = NPCW_APPEAR_STATUS_NUM;
    info->way = NPCW_APPEAR_WAY_NUM;
}
void mNpcW_ClearNpcWalkInfo(NpcWalkInfo* info, s32 count) {
    for (; count != 0 && info != NULL; count--) {
        bzero(info, sizeof(NpcWalkInfo));
        mNpc_ClearAnimalPersonalID(&info->id);
        info->idx = -1;
        info->status = NPCW_INFO_STATUS_NUM;
        info->type = NPCW_GOAL_NUM;
        mNpcW_ClearNpcWalkAppear(&info->appearInfo);

        info++;
    }
}

void mNpcW_ClearNpcWalk(NpcWalking* walk) {
    bzero(walk, sizeof(NpcWalking));
    mNpcW_ClearNpcWalkInfo(&walk->info[0], NPCW_MAX);
}

s32 mNpcW_CheckFreeNpcWalkInfo(NpcWalkInfo* info) {
    s32 res = FALSE;

    if (info != NULL) {
        res = mNpc_CheckFreeAnimalPersonalID(&info->id);
    }

    return res;
}

s32 mNpcW_GetFreeNpcWalkInfoIdx(NpcWalkInfo* info, s32 num) {
    s32 idx = -1;
    s32 i;

    for (i = 0; i < num; i++) {
        if (mNpcW_CheckFreeNpcWalkInfo(info) == TRUE) {
            idx = i;
            break;
        }

        info++;
    }

    return idx;
}

s32 mNpcW_GetNpcWalkInfoIdx(NpcWalkInfo* info, s32 num, AnmPersonalID_c* anmId) {
    s32 idx = -1;
    s32 i;

    if ((anmId != NULL) && (mNpc_CheckFreeAnimalPersonalID(anmId) == FALSE)) {
        for (i = 0; i < num; i++) {
            if (mNpc_CheckCmpAnimalPersonalID(anmId, &info->id) == TRUE) {
                idx = i;
                break;
            }

            info++;
        }
    }

    return idx;
}

s32 mNpcW_GetNpcWalkInfoIdxbyIdx(NpcWalkInfo* info, s32 num, s32 idx) {
    s32 ret = -1;
    s32 i;

    if ((idx >= 0) && (idx < ANIMAL_NUM_MAX)) {
        for (i = 0; i < num; i++) {
            if (info->idx == idx) {
                ret = i;
                break;
            }

            info++;
        }
    }

    return ret;
}

s32 mNpcW_DecideNpc(Animal_c* animal, u16 used) {
    s32 idx;
    u16 exist;
    u16 goal;
    s32 unused;
    s32 nowSec;
    s32 i;

    exist = 0;
    goal = 0;
    unused = 0;
    nowSec = common_data.time.nowSec;
    idx = -1;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            NpcWalkGoalData* data;
            exist |= (1 << i);

            data = mNpcW_GetGoalDataInfo(animal->id.looks, nowSec);
            if (data->count > 0) {
                goal |= (1 << i);

                if (((used >> i) & 1) == FALSE) {
                    unused++;
                }
            }
        }

        animal++;
    }

    if (unused > 0) {
        s32 selectedNum;
        u32 selectionField = (exist & ~used) & goal;

        selectedNum = RANDOM(unused) + 1;

        while (selectedNum != 0) {
            if ((selectionField & 1) == TRUE) {
                selectedNum--;
            }

            idx++;
            selectionField >>= 1;
        }
    }

    return idx;
}

void mNpcW_SetNpcWalkInfo(NpcWalkInfo* info, Animal_c* animal, s32 idx) {
    NpcWalkGoalData* data;
    s32 nowSec = common_data.time.nowSec;
    u32 index;

    mNpc_CopyAnimalPersonalID(&info->id, &animal->id);
    info->idx = idx;
    data = mNpcW_GetGoalDataInfo(animal->id.looks, nowSec);

    if (data->count > 0) {
        index = RANDOM(data->count);
        info->type = data->types[index];
    } else {
        info->type = NPCW_GOAL_MY_HOME;
    }
    info->status = 1;
}

s32 mNpcW_ChangeNpcWalk(NpcWalking* walk, NpcWalkInfo* info) {
    s32 free_idx;
    s32 idx = -1;
    s32 i;

    mNpcW_ClearNpcWalkInfo(info, 1);
    walk->infoUse--;
    free_idx = mNpcW_GetFreeNpcWalkInfoIdx(walk->info, NPCW_MAX);

    if (free_idx != -1) {
        NpcWalkInfo* free_info = &walk->info[free_idx];

        mNpcW_ClearNpcWalkInfo(free_info, 1);
        idx = mNpcW_DecideNpc(common_data.animals, walk->idxUse);

        if (idx == -1) {
            walk->idxUse = 0;
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (i == walk->info[i].idx) {
                    walk->idxUse |= (1 << i);
                }
            }

            idx = mNpcW_DecideNpc(common_data.animals, walk->idxUse);
        }

        mNpcW_SetNpcWalkInfo(free_info, &common_data.animals[idx], idx);
        walk->idxUse |= (1 << idx);
        mNpcW_SetGoalBlock(free_info);
    }

    return idx;
}

s32 mNpcW_GetAloneBlock(u8* goalBlockX, u8* goalBlockZ) {
    Animal_c* animal = common_data.animals;
    NpcList* npcList = common_data.npclist;
    u8 block_field[FG_BLOCK_Z_NUM + 2];
    u8 count = 0;
    s32 selected;
    s32 blockX;
    s32 blockZ;
    s32 i;
    s32 j;
    s32 z;

    *goalBlockX = 0;
    *goalBlockZ = 0;

    bzero(block_field, FG_BLOCK_Z_NUM + 2);
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE &&
            mFI_Wpos2BlockNum(&blockX, &blockZ, npcList->position) == TRUE) {
            block_field[blockZ] |= (1 << blockX);
            count++;
        }

        animal++;
        npcList++;
    }

    z = 1;
    selected = RANDOM(FG_BLOCK_TOTAL_NUM - count);
    for (i = 1; i < BLOCK_Z_NUM - 3; i++) {
        for (j = 1; j < BLOCK_X_NUM - 1; j++) {
            if (((block_field[z] >> j) & 1) == 0) {
                if (selected <= 0) {
                    *goalBlockX = j;
                    *goalBlockZ = i;
                    return TRUE;
                } else {
                    selected--;
                }
            }
        }

        z++;
    }

    return FALSE;
}

void mNpcW_GetBlockXZNumExceptHome(s32* goalBlockX, s32* goalBlockZ, Animal_c* animal) {
    u8 possibleX = 0xFF;
    u8 possibleZ = 0xFF;

    s32 x = 0;
    s32 z = 0;

    s32 chosenX;
    s32 chosenZ;

    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            u8 homeX = animal->homeInfo.blockX - 1;
            u8 homeZ = animal->homeInfo.blockZ - 1;

            if (((possibleX >> homeX) & 1) == 1) {
                possibleX &= ~(1 << homeX);
                x++;
            }

            if (((possibleZ >> homeZ) & 1) == 1) {
                possibleZ &= ~(1 << homeZ);
                z++;
            }
        }

        animal++;
    }

    chosenX = RANDOM(FG_BLOCK_X_NUM - x);
    chosenZ = RANDOM(FG_BLOCK_Z_NUM - z);

    for (i = 0; i < FG_BLOCK_X_NUM; i++) {
        if (((possibleX >> i) & 1) == 1) {
            if (chosenX <= 0) {
                break;
            } else {
                chosenX--;
            }
        }
    }

    *goalBlockX = i + 1;

    for (i = 0; i < FG_BLOCK_Z_NUM; i++) {
        if (((possibleZ >> i) & 1) == 1) {
            if (chosenZ <= 0) {
                break;
            } else {
                chosenZ--;
            }
        }
    }

    *goalBlockZ = i + 1;
}

s32 mNpcW_CheckDiffBlockWalkNpcHome(s32 blockX, s32 blockZ, NpcWalkInfo* info) {
    s32 res = FALSE;
    Anmhome_c* home;
    s32 i;
    s32 idx;

    for (i = 0; i < NPCW_MAX; i++) {
        idx = info->idx;
        if (idx != -1) {
            home = &common_data.animals[idx].homeInfo;

            if (home->blockX == blockX && home->blockZ == blockZ) {
                break;
            }
        }

        info++;
    }

    if (i == NPCW_MAX) {
        res = TRUE;
    }

    return res;
}

void mNpcW_SetHomeBlockSource(NpcWalking* walk, Animal_c* animal) {
    Animal_c* animalP = animal;
    u16 field;
    s32 num;
    s32 i;

    field = 0;
    num = 0;

    l_goal_block[NPCW_GOAL_BLOCK_HOME][0] = 0;
    l_goal_block[NPCW_GOAL_BLOCK_HOME][1] = 0;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            Anmhome_c* home = &animal->homeInfo;

            if (mNpcW_CheckDiffBlockWalkNpcHome(home->blockX, home->blockZ, walk->info) == TRUE) {
                field |= (1 << i);
                num++;
            }
        }

        animal++;
    }

    if (num > 0) {
        s32 chosen = RANDOM(num);
        Anmhome_c* homeInfo;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((field >> i) & 1) == 1) {
                if (chosen == 0) {
                    break;
                } else {
                    chosen--;
                }
            }
        }

        homeInfo = &animalP[i].homeInfo;
        l_goal_block[NPCW_GOAL_BLOCK_HOME][0] = homeInfo->blockX + 1;
        l_goal_block[NPCW_GOAL_BLOCK_HOME][1] = homeInfo->blockZ + 1;
    }

    if (l_goal_block[NPCW_GOAL_BLOCK_HOME][0] == 0 || l_goal_block[NPCW_GOAL_BLOCK_HOME][1] == 0) {
        mNpcW_GetBlockXZNumExceptHome(&l_goal_block[NPCW_GOAL_BLOCK_HOME][0], &l_goal_block[NPCW_GOAL_BLOCK_HOME][1],
                                      animalP);
    }
}

void mNpcW_InitGoalBlockSource(NpcWalking* walk, Animal_c* animal) {
    s32 shrineX;
    s32 shrineZ;
    UNUSED s32 pad;

    mFI_BlockKind2BkNum(&shrineX, &shrineZ, 4);

    l_goal_block[NPCW_GOAL_BLOCK_SHRINE][0] = shrineX;
    l_goal_block[NPCW_GOAL_BLOCK_SHRINE][1] = shrineZ;

    mNpcW_SetHomeBlockSource(walk, animal);
}
void mNpcW_SetGoalBlock(NpcWalkInfo* info) {
    s32 idx;

    switch (info->type) {
        case NPCW_GOAL_SHRINE:
            info->goalX = l_goal_block[NPCW_GOAL_BLOCK_SHRINE][0];
            info->goalZ = l_goal_block[NPCW_GOAL_BLOCK_SHRINE][1];
            break;

        case NPCW_GOAL_HOME:
            info->goalX = l_goal_block[NPCW_GOAL_BLOCK_HOME][0];
            info->goalZ = l_goal_block[NPCW_GOAL_BLOCK_HOME][1];
            break;

        case NPCW_GOAL_ALONE:
            mNpcW_GetAloneBlock(&info->goalX, &info->goalZ);
            break;

        case NPCW_GOAL_MY_HOME:
            idx = info->idx;

            info->goalX = common_data.animals[idx].homeInfo.blockX;
            info->goalZ = common_data.animals[idx].homeInfo.blockZ;
            break;

        default:
            info->goalX = 0;
            info->goalZ = 0;
            break;
    }
}

void mNpcW_InitNpcWalk(NpcWalking* walk) {
    Animal_c* animals;
    NpcWalkInfo* info = walk->info;
    s32 idx;
    s32 i;

    mNpcW_ClearNpcWalk(walk);
    bzero(l_goal_block, sizeof(l_goal_block));
    bzero(l_arrive_stay_count, sizeof(l_arrive_stay_count));

    animals = common_data.animals;
    walk->infoMax = NPCW_GET_WALK_NUM(common_data.nowNpcMax);

    for (i = 0; i < walk->infoMax; i++) {
        idx = mNpcW_DecideNpc(animals, walk->idxUse);

        mNpcW_SetNpcWalkInfo(info, &common_data.animals[idx], idx);
        walk->idxUse |= (1 << idx);
        info++;
    }

    walk->infoUse = walk->infoMax;
    mNpcW_InitGoalBlockSource(walk, animals);
}

s32 mNpcW_GetAppearStatusWay(u8* status, u8* way, Animal_c* animal) {
    NpcWalking* walk = &common_data.npcWalk;
    s32 infoIdx;
    s32 res = FALSE;

    *status = NPCW_APPEAR_STATUS_NUM;

    infoIdx = mNpcW_GetNpcWalkInfoIdx(walk->info, NPCW_MAX, &animal->id);

    if (infoIdx >= 0) {
        *status = walk->info[infoIdx].appearInfo.status;
        *way = walk->info[infoIdx].appearInfo.way;
        res = TRUE;
    } else {
        *status = NPCW_APPEAR_STATUS_0;
        *way = NPCW_APPEAR_WAY_NUM;
    }

    return res;
}

s32* mNpcW_GetArriveStayCountP(s32 idx) {
    if (idx >= 0 && idx < ANIMAL_NUM_MAX) {
        return &l_arrive_stay_count[idx];
    }

    return NULL;
}

s32 mNpcW_GetWalkInfoStatusGoalAnimalIdx(s32* status, s32* goal, s32 idx) {
    s32 res = FALSE;

    *status = NPCW_INFO_STATUS_NUM;
    *goal = NPCW_GOAL_NUM;

    if (idx >= 0 && idx < ANIMAL_NUM_MAX) {
        NpcWalking* walk = &common_data.npcWalk;
        s32 info_idx = mNpcW_GetNpcWalkInfoIdx(walk->info, NPCW_MAX, &common_data.animals[idx].id);

        if (info_idx >= 0) {
            res = TRUE;
            *status = walk->info[info_idx].status;
            *goal = walk->info[info_idx].type;
        }
    }

    return res;
}

s32 mNpcW_GetNearGate(s32* targetUtX, s32* targetUtZ, s32 blockX, s32 blockZ, s32 utX, s32 utZ) {
    u8 blockType;
    RandomFieldGate* gate;
    s32 difference;
    UNUSED s32 pad;
    s32 x;
    s32 z;
    s32 gateCount;
    s32 i;
    s32 res = FALSE;
    s32 direction;

    *targetUtX = UT_X_NUM;
    *targetUtZ = UT_Z_NUM;

    if (utX >= 0 && utX < UT_X_NUM && utZ >= 0 && utZ < UT_Z_NUM) {
        blockType = mFI_BkNum2BlockType(blockX, blockZ);
        x = utX < (UT_X_NUM / 2) ? utX : UT_X_NUM - utX;
        z = utZ < (UT_Z_NUM / 2) ? utZ : UT_Z_NUM - utZ;

        if (x < z) {
            if (utX < (UT_X_NUM / 2)) {
                direction = RANDOM_FIELD_DIRECT_WEST;
            } else {
                direction = RANDOM_FIELD_DIRECT_EAST;
            }
        } else {
            if (utZ < (UT_Z_NUM / 2)) {
                direction = RANDOM_FIELD_DIRECT_NORTH;
            } else {
                direction = RANDOM_FIELD_DIRECT_SOUTH;
            }
        }

        gate = mRF_BlockTypeDirect2GateData(&gateCount, blockType, direction);
        if (gate != NULL && gateCount > 0) {

            for (i = 0; i < gateCount; i++) {
                x = gate->ut1 & 0xF;
                z = gate->ut1 >> 4;

                if (direction == RANDOM_FIELD_DIRECT_WEST || direction == RANDOM_FIELD_DIRECT_WEST) {
                    difference = utZ - z;
                    difference = ABS(difference);
                } else {
                    difference = utX - x;
                    difference = ABS(difference);
                }

                if (difference < UT_BASE_NUM) {
                    *targetUtX = x;
                    *targetUtZ = z;
                    res = TRUE;
                }

                gate++;
            }
        }
    }

    return res;
}
