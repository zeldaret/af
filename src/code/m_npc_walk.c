#include "global.h"
#include "m_npc_walk.h"
#include "m_npc.h"
#include "m_common_data.h"
#include "m_npc_schedule.h"
#include "m_npc_personal_id.h"
#include "macros.h"
#include "m_field_info.h"
#include "libc64/qrand.h"
#include "m_random_field.h"
#include "6DE300.h"

#define mNpcW_TIME_2_SEC(hour, min, sec) ((hour)*3600 + (min)*60 + (sec))
#define mNpcW_MAKE_SCHEDULE_TABLE(goal_data) \
    { goal_data, ARRAY_COUNT(goal_data) }

s32 l_goal_block[NPC_GOAL_BLOCK_NUM][2];
s32 l_arrive_stay_count[ANIMAL_NUM_MAX];

u8 l_girl_time_12[] = { NPC_GOAL_SHRINE, NPC_GOAL_HOME, NPC_GOAL_ALONE };
u8 l_girl_time_18_30[] = { NPC_GOAL_SHRINE, NPC_GOAL_HOME };

NpcGoalData l_girl_goal_data[] = { { NULL, 0, mNpcW_TIME_2_SEC(6, 0, 0) },
                                   { l_girl_time_12, ARRAY_COUNT(l_girl_time_12), mNpcW_TIME_2_SEC(12, 0, 0) },
                                   { NULL, 0, mNpcW_TIME_2_SEC(13, 0, 0) },
                                   { l_girl_time_18_30, ARRAY_COUNT(l_girl_time_18_30), mNpcW_TIME_2_SEC(18, 30, 0) },
                                   { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) } };

NpcGoalDataTable l_girl_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_girl_goal_data);

u8 l_kogirl_time_ed[] = { NPC_GOAL_SHRINE, NPC_GOAL_HOME };

NpcGoalData l_kogirl_goal_data[] = { { l_kogirl_time_ed, ARRAY_COUNT(l_kogirl_time_ed), mNpcW_TIME_2_SEC(24, 0, 0) } };

NpcGoalDataTable l_kogirl_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_kogirl_goal_data);

u8 l_boy_time_12[] = { NPC_GOAL_ALONE };
u8 l_boy_time_19_30[] = { NPC_GOAL_SHRINE, NPC_GOAL_HOME };

NpcGoalData l_boy_goal_data[] = { { NULL, 0, mNpcW_TIME_2_SEC(9, 0, 0) },
                                  { l_boy_time_12, ARRAY_COUNT(l_boy_time_12), mNpcW_TIME_2_SEC(12, 0, 0) },
                                  { NULL, 0, mNpcW_TIME_2_SEC(14, 0, 0) },
                                  { l_boy_time_19_30, ARRAY_COUNT(l_boy_time_19_30), mNpcW_TIME_2_SEC(19, 30, 0) },
                                  { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) } };

NpcGoalDataTable l_boy_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_boy_goal_data);

u8 l_sports_man_time_12[] = { NPC_GOAL_SHRINE, NPC_GOAL_HOME, NPC_GOAL_ALONE, NPC_GOAL_ALONE };
u8 l_sports_man_time_23[] = { NPC_GOAL_SHRINE, NPC_GOAL_SHRINE, NPC_GOAL_HOME, NPC_GOAL_HOME, NPC_GOAL_ALONE };

NpcGoalData l_sports_man_goal_data[] = {
    { NULL, 0, mNpcW_TIME_2_SEC(6, 30, 0) },
    { l_sports_man_time_12, ARRAY_COUNT(l_sports_man_time_12), mNpcW_TIME_2_SEC(12, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(12, 30, 0) },
    { l_sports_man_time_23, ARRAY_COUNT(l_sports_man_time_23), mNpcW_TIME_2_SEC(23, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) }
};

NpcGoalDataTable l_sports_man_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_sports_man_goal_data);

u8 l_grim_man_time_ed[] = { NPC_GOAL_SHRINE, NPC_GOAL_SHRINE, NPC_GOAL_SHRINE, NPC_GOAL_ALONE, NPC_GOAL_ALONE,
                            NPC_GOAL_ALONE,  NPC_GOAL_ALONE,  NPC_GOAL_ALONE,  NPC_GOAL_ALONE, NPC_GOAL_ALONE };

NpcGoalData l_grim_man_goal_data[] = { { l_grim_man_time_ed, ARRAY_COUNT(l_grim_man_time_ed),
                                         mNpcW_TIME_2_SEC(24, 0, 0) } };

NpcGoalDataTable l_grim_man_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_grim_man_goal_data);

u8 l_naniwa_lady_time_1_30[] = { NPC_GOAL_SHRINE, NPC_GOAL_SHRINE, NPC_GOAL_SHRINE, NPC_GOAL_SHRINE, NPC_GOAL_SHRINE,
                                 NPC_GOAL_SHRINE, NPC_GOAL_SHRINE, NPC_GOAL_ALONE,  NPC_GOAL_ALONE,  NPC_GOAL_ALONE };
u8 l_naniwa_lady_time_13[] = { NPC_GOAL_HOME };
u8 l_naniwa_lady_time_21[] = { NPC_GOAL_SHRINE, NPC_GOAL_SHRINE, NPC_GOAL_HOME, NPC_GOAL_HOME, NPC_GOAL_ALONE };

NpcGoalData l_naniwa_lady_goal_data[] = {
    { l_naniwa_lady_time_1_30, ARRAY_COUNT(l_naniwa_lady_time_1_30), mNpcW_TIME_2_SEC(1, 30, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(10, 0, 0) },
    { l_naniwa_lady_time_13, ARRAY_COUNT(l_naniwa_lady_time_13), mNpcW_TIME_2_SEC(13, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(14, 0, 0) },
    { l_naniwa_lady_time_21, ARRAY_COUNT(l_naniwa_lady_time_21), mNpcW_TIME_2_SEC(21, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(22, 0, 0) },
    { l_naniwa_lady_time_1_30, ARRAY_COUNT(l_naniwa_lady_time_1_30), mNpcW_TIME_2_SEC(24, 0, 0) }
};

NpcGoalDataTable l_naniwa_lady_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_naniwa_lady_goal_data);

NpcGoalDataTable* l_looks_goal_table[NPC_LOOKS_NUM] = { &l_girl_goal_table,     &l_kogirl_goal_table,
                                                        &l_boy_goal_table,      &l_sports_man_goal_table,
                                                        &l_grim_man_goal_table, &l_naniwa_lady_goal_table };

NpcGoalData* mNpcW_GetGoalDataInfo(s32 looks, s32 nowSec) {
    NpcGoalDataTable* table = l_looks_goal_table[looks];
    NpcGoalData* goal_data = table->data;
    s32 i;

    for (i = 0; i < table->count; i++) {
        if (goal_data->endTime > nowSec) {
            break;
        }

        goal_data++;
    }

    if (i == table->count) {
        goal_data = &table->data[table->count - 1];
    }

    return goal_data;
}

void mNpcW_ClearNpcWalkAppear(NpcAppear* appearInfo) {
    appearInfo->status = NPC_APPEAR_STATUS_NUM;
    appearInfo->way = NPC_APPEAR_WAY_NUM;
}

void mNpcW_ClearNpcWalkInfo(NpcInfo* info, s32 count) {
    for (; count != 0 && info != NULL; count--) {
        bzero(info, sizeof(NpcInfo));
        mNpc_ClearAnimalPersonalID(&info->id);
        info->idx = -1;
        info->status = NPC_INFO_STATUS_NUM;
        info->goalType = NPC_GOAL_NUM;
        mNpcW_ClearNpcWalkAppear(&info->appearInfo);

        info++;
    }
}

void mNpcW_ClearNpcWalk(NpcWalk* walk) {
    bzero(walk, sizeof(NpcWalk));
    mNpcW_ClearNpcWalkInfo(&walk->info[0], NPC_MAX);
}

s32 mNpcW_CheckFreeNpcWalkInfo(NpcInfo* info) {
    s32 res = FALSE;

    if (info != NULL) {
        res = mNpc_CheckFreeAnimalPersonalID(&info->id);
    }

    return res;
}

s32 mNpcW_GetFreeNpcWalkInfoIdx(NpcInfo* info, s32 num) {
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

s32 mNpcW_GetNpcWalkInfoIdx(NpcInfo* info, s32 num, AnmPersonalId* anmId) {
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

s32 func_800AF060_jp(NpcInfo* info, s32 num, s32 want_idx) {
    s32 idx = -1;
    s32 i;

    if ((want_idx >= 0) && (want_idx < ANIMAL_NUM_MAX)) {
        for (i = 0; i < num; i++) {
            if (info->idx == want_idx) {
                idx = i;
                break;
            }

            info++;
        }
    }

    return idx;
}

s32 mNpcW_DecideNpc(Animal* animal, u16 used) {
    s32 idx;
    u16 exist;
    u16 possible_goal;
    s32 unused;
    s32 nowSec;
    s32 i;

    exist = 0;
    possible_goal = 0;
    unused = 0;
    nowSec = gCommonData.time.nowSec;
    idx = -1;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            NpcGoalData* goal_data;
            exist |= (1 << i);

            goal_data = mNpcW_GetGoalDataInfo(animal->id.looks, nowSec);
            if (goal_data->count > 0) {
                possible_goal |= (1 << i);

                if (((used >> i) & 1) == FALSE) {
                    unused++;
                }
            }
        }

        animal++;
    }

    if (unused > 0) {
        s32 selected_num;
        u32 selection_field =
            (exist & ~used) & possible_goal; /* clear the possible bitfield to only include unused existing villagers */

        selected_num = RANDOM(unused) + 1;

        while (selected_num != 0) {
            if ((selection_field & 1) == TRUE) {
                selected_num--;
            }

            idx++;
            selection_field >>= 1;
        }
    }

    return idx;
}

void mNpcW_SetNpcWalkInfo(NpcInfo* info, Animal* animal, s32 idx) {
    NpcGoalData* goal_data;
    s32 nowSec = gCommonData.time.nowSec;
    u32 index;

    mNpc_CopyAnimalPersonalID(&info->id, &animal->id);
    info->idx = idx;
    goal_data = mNpcW_GetGoalDataInfo(animal->id.looks, nowSec);

    if (goal_data->count > 0) {
        index = RANDOM(goal_data->count);
        info->goalType = goal_data->types[index];
    } else {
        info->goalType = NPC_GOAL_MY_HOME; /* Default to acre the villager's house is in */
    }
    info->status = 1;
}

s32 mNpcW_ChangeNpcWalk(NpcWalk* walk, NpcInfo* info) {
    s32 free_idx;
    s32 idx = -1;
    s32 i;

    mNpcW_ClearNpcWalkInfo(info, 1);
    walk->usedInfoNum--;
    free_idx = mNpcW_GetFreeNpcWalkInfoIdx(walk->info, NPC_MAX);

    if (free_idx != -1) {
        NpcInfo* free_info = &walk->info[free_idx];

        mNpcW_ClearNpcWalkInfo(free_info, 1);
        idx = mNpcW_DecideNpc(gCommonData.save.animals, walk->usedIdxBitfield);

        if (idx == -1) {
            walk->usedIdxBitfield = 0;
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (i == walk->info[i].idx) {
                    walk->usedIdxBitfield |= (1 << i);
                }
            }

            idx = mNpcW_DecideNpc(gCommonData.save.animals, walk->usedIdxBitfield);
        }

        mNpcW_SetNpcWalkInfo(free_info, &gCommonData.save.animals[idx], idx);
        walk->usedIdxBitfield |= (1 << idx);
        mNpcW_SetGoalBlock(free_info);
    }

    return idx;
}

s32 mNpcW_GetAloneBlock(u8* goalBlockX, u8* goalBlockZ) {
    Animal* animal = gCommonData.save.animals;
    NpcList* npcList = gCommonData.npcList;
    u8 block_field[FG_BLOCK_Z_NUM + 2];
    u8 animal_count = 0;
    s32 selected;
    s32 blockX;
    s32 blockZ;
    s32 i;
    s32 j;
    s32 z;

    //   0 1 2 3 4 5 6
    // Q x - - - - - -
    // A - - - - - - -
    // B - - - - - - -
    // C - - - - - - -
    // D - - - - - - -
    // E - - - - - - -
    // F - - - - - - -
    // Z - - - - - - -

    /* Default goal block is Q-0 */
    *goalBlockX = 0;
    *goalBlockZ = 0;

    bzero(block_field, FG_BLOCK_Z_NUM + 2);
    /* Log all acres which currently have a villager in them */
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE &&
            mFI_Wpos2BlockNum(&blockX, &blockZ, npcList->position) == TRUE) {
            block_field[blockZ] |= (1 << blockX);
            animal_count++;
        }

        animal++;
        npcList++;
    }

    /* Select a random empty acre to go to */
    z = 1;
    selected = RANDOM(FG_BLOCK_TOTAL_NUM - animal_count);
    /* Find the random acre and set output */
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

void mNpcW_GetBlockXZNumExceptHome(s32* goalBlockX, s32* goalBlockZ, Animal* animal) {
    u8 possible_x = 0xFF;
    u8 possible_z = 0xFF;

    s32 x_num = 0;
    s32 z_num = 0;

    s32 selected_x;
    s32 selected_z;

    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            u8 home_block_x = animal->homeInfo.blockX - 1;
            u8 home_block_z = animal->homeInfo.blockZ - 1;

            if (((possible_x >> home_block_x) & 1) == 1) {
                possible_x &= ~(1 << home_block_x);
                x_num++;
            }

            if (((possible_z >> home_block_z) & 1) == 1) {
                possible_z &= ~(1 << home_block_z);
                z_num++;
            }
        }

        animal++;
    }

    selected_x = RANDOM(FG_BLOCK_X_NUM - x_num);
    selected_z = RANDOM(FG_BLOCK_Z_NUM - z_num);

    for (i = 0; i < FG_BLOCK_X_NUM; i++) {
        if (((possible_x >> i) & 1) == 1) {
            if (selected_x <= 0) {
                break;
            } else {
                selected_x--;
            }
        }
    }

    *goalBlockX = i + 1;

    for (i = 0; i < FG_BLOCK_Z_NUM; i++) {
        if (((possible_z >> i) & 1) == 1) {
            if (selected_z <= 0) {
                break;
            } else {
                selected_z--;
            }
        }
    }

    *goalBlockZ = i + 1;
}

s32 mNpcW_CheckDiffBlockWalkNpcHome(s32 blockX, s32 blockZ, NpcInfo* info) {
    s32 res = FALSE;
    AnmHome* home;
    s32 i;
    s32 idx;

    for (i = 0; i < NPC_MAX; i++) {
        idx = info->idx;
        if (idx != -1) {
            home = &gCommonData.save.animals[idx].homeInfo;

            if (home->blockX == blockX && home->blockZ == blockZ) {
                break;
            }
        }

        info++;
    }

    if (i == NPC_MAX) {
        res = TRUE;
    }

    return res;
}

void mNpcW_SetHomeBlockSource(NpcWalk* walk, Animal* animal) {
    Animal* animal_p = animal;
    u16 diff_animal_field;
    s32 diff_animal_num;
    s32 i;

    diff_animal_field = 0;
    diff_animal_num = 0;

    l_goal_block[NPC_GOAL_BLOCK_HOME][0] = 0;
    l_goal_block[NPC_GOAL_BLOCK_HOME][1] = 0;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            AnmHome* home = &animal->homeInfo;

            if (mNpcW_CheckDiffBlockWalkNpcHome(home->blockX, home->blockZ, walk->info) == TRUE) {
                diff_animal_field |= (1 << i);
                diff_animal_num++;
            }
        }

        animal++;
    }

    if (diff_animal_num > 0) {
        s32 selected = RANDOM(diff_animal_num);
        AnmHome* homeInfo;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((diff_animal_field >> i) & 1) == 1) {
                if (selected == 0) {
                    break;
                } else {
                    selected--;
                }
            }
        }

        homeInfo = &animal_p[i].homeInfo;
        l_goal_block[NPC_GOAL_BLOCK_HOME][0] = homeInfo->blockX + 1;
        l_goal_block[NPC_GOAL_BLOCK_HOME][1] = homeInfo->blockZ + 1;
    }

    if (l_goal_block[NPC_GOAL_BLOCK_HOME][0] == 0 || l_goal_block[NPC_GOAL_BLOCK_HOME][1] == 0) {
        mNpcW_GetBlockXZNumExceptHome(&l_goal_block[NPC_GOAL_BLOCK_HOME][0], &l_goal_block[NPC_GOAL_BLOCK_HOME][1],
                                      animal_p);
    }
}

void mNpcW_InitGoalBlockSource(NpcWalk* walk, Animal* animal) {
    s32 shrine_x;
    s32 shrine_z;
    UNUSED s32 pad;

    mFI_BlockKind2BkNum(&shrine_x, &shrine_z, RANDOM_FIELD_BLOCKKIND_SHRINE);

    l_goal_block[NPC_GOAL_BLOCK_SHRINE][0] = shrine_x;
    l_goal_block[NPC_GOAL_BLOCK_SHRINE][1] = shrine_z;

    mNpcW_SetHomeBlockSource(walk, animal);
}

void mNpcW_SetGoalBlock(NpcInfo* info) {
    s32 idx;

    switch (info->goalType) {
        case NPC_GOAL_SHRINE:
            info->goalBlockX = l_goal_block[NPC_GOAL_BLOCK_SHRINE][0];
            info->goalBlockZ = l_goal_block[NPC_GOAL_BLOCK_SHRINE][1];
            break;

        case NPC_GOAL_HOME:
            info->goalBlockX = l_goal_block[NPC_GOAL_BLOCK_HOME][0];
            info->goalBlockZ = l_goal_block[NPC_GOAL_BLOCK_HOME][1];
            break;

        case NPC_GOAL_ALONE:
            mNpcW_GetAloneBlock(&info->goalBlockX, &info->goalBlockZ);
            break;

        case NPC_GOAL_MY_HOME:
            idx = info->idx;

            info->goalBlockX = gCommonData.save.animals[idx].homeInfo.blockX;
            info->goalBlockZ = gCommonData.save.animals[idx].homeInfo.blockZ;
            break;

        default:
            info->goalBlockX = 0;
            info->goalBlockZ = 0;
            break;
    }
}

void mNpcW_InitNpcWalk(NpcWalk* walk) {
    Animal* animals;
    NpcInfo* info = walk->info;
    s32 idx;
    s32 i;

    mNpcW_ClearNpcWalk(walk);
    bzero(l_goal_block, sizeof(l_goal_block));
    bzero(l_arrive_stay_count, sizeof(l_arrive_stay_count));

    animals = gCommonData.save.animals;
    walk->infoMax = NPC_GET_WALK_NUM(gCommonData.save.nowNpcMax);

    for (i = 0; i < walk->infoMax; i++) {
        idx = mNpcW_DecideNpc(animals, walk->usedIdxBitfield);

        mNpcW_SetNpcWalkInfo(info, &gCommonData.save.animals[idx], idx);
        walk->usedIdxBitfield |= (1 << idx);
        info++;
    }

    walk->usedInfoNum = walk->infoMax;
    mNpcW_InitGoalBlockSource(walk, animals);
}

s32 mNpcW_GetAppearStatusWay(u8* status, u8* way, Animal* animal) {
    NpcWalk* walk = &gCommonData.npcWalk;
    s32 info_idx;
    s32 res = FALSE;

    *status = NPC_APPEAR_STATUS_NUM;

    info_idx = mNpcW_GetNpcWalkInfoIdx(walk->info, NPC_MAX, &animal->id);

    if (info_idx >= 0) {
        *status = walk->info[info_idx].appearInfo.status;
        *way = walk->info[info_idx].appearInfo.way;
        res = TRUE;
    } else {
        *status = NPC_APPEAR_STATUS_0;
        *way = NPC_APPEAR_WAY_NUM;
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

    *status = NPC_INFO_STATUS_NUM;
    *goal = NPC_GOAL_NUM;

    if (idx >= 0 && idx < ANIMAL_NUM_MAX) {
        NpcWalk* walk = &gCommonData.npcWalk;
        s32 info_idx = mNpcW_GetNpcWalkInfoIdx(walk->info, NPC_MAX, &gCommonData.save.animals[idx].id);

        if (info_idx >= 0) {
            res = TRUE;
            *status = walk->info[info_idx].status;
            *goal = walk->info[info_idx].goalType;
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
