#include "global.h"
#include "m_npc_walk.h"
#include "m_npc.h"
#include "m_common_data.h"
#include "m_npc_schedule.h"
#include "m_npc_personal_id.h"
#include "macros.h"
#include "m_field_info.h"
#include "sys_math.h"
#include "m_random_field.h"
#include "6DE300.h"

#define mNpcW_TIME_2_SEC(hour, min, sec) ((hour)*3600 + (min)*60 + (sec))
#define mNpcW_MAKE_SCHEDULE_TABLE(goal_data) \
    { goal_data, ARRAY_COUNT(goal_data) }

s32 l_goal_block[mNpcW_GOAL_BLOCK_NUM][2];
s32 l_arrive_stay_count[ANIMAL_NUM_MAX];

static u8 l_girl_time_12[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME, mNpcW_GOAL_ALONE };
static u8 l_girl_time_18_30[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME };

static mNpcW_GoalData_c l_girl_goal_data[] = {
    { NULL, 0, mNpcW_TIME_2_SEC(6, 0, 0) },
    { l_girl_time_12, ARRAY_COUNT(l_girl_time_12), mNpcW_TIME_2_SEC(12, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(13, 0, 0) },
    { l_girl_time_18_30, ARRAY_COUNT(l_girl_time_18_30), mNpcW_TIME_2_SEC(18, 30, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) }
};

static mNpcW_GoalDataTable_c l_girl_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_girl_goal_data);

static u8 l_kogirl_time_ed[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME };

static mNpcW_GoalData_c l_kogirl_goal_data[] = { { l_kogirl_time_ed, ARRAY_COUNT(l_kogirl_time_ed),
                                                   mNpcW_TIME_2_SEC(24, 0, 0) } };

static mNpcW_GoalDataTable_c l_kogirl_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_kogirl_goal_data);

static u8 l_boy_time_12[] = { mNpcW_GOAL_ALONE };
static u8 l_boy_time_19_30[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME };

static mNpcW_GoalData_c l_boy_goal_data[] = { { NULL, 0, mNpcW_TIME_2_SEC(9, 0, 0) },
                                              { l_boy_time_12, ARRAY_COUNT(l_boy_time_12), mNpcW_TIME_2_SEC(12, 0, 0) },
                                              { NULL, 0, mNpcW_TIME_2_SEC(14, 0, 0) },
                                              { l_boy_time_19_30, ARRAY_COUNT(l_boy_time_19_30),
                                                mNpcW_TIME_2_SEC(19, 30, 0) },
                                              { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) } };

static mNpcW_GoalDataTable_c l_boy_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_boy_goal_data);

static u8 l_sports_man_time_12[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME, mNpcW_GOAL_ALONE, mNpcW_GOAL_ALONE };
static u8 l_sports_man_time_23[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME, mNpcW_GOAL_HOME,
                                     mNpcW_GOAL_ALONE };

static mNpcW_GoalData_c l_sports_man_goal_data[] = {
    { NULL, 0, mNpcW_TIME_2_SEC(6, 30, 0) },
    { l_sports_man_time_12, ARRAY_COUNT(l_sports_man_time_12), mNpcW_TIME_2_SEC(12, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(12, 30, 0) },
    { l_sports_man_time_23, ARRAY_COUNT(l_sports_man_time_23), mNpcW_TIME_2_SEC(23, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) }
};

static mNpcW_GoalDataTable_c l_sports_man_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_sports_man_goal_data);

static u8 l_grim_man_time_ed[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_ALONE,
                                   mNpcW_GOAL_ALONE,  mNpcW_GOAL_ALONE,  mNpcW_GOAL_ALONE,  mNpcW_GOAL_ALONE,
                                   mNpcW_GOAL_ALONE,  mNpcW_GOAL_ALONE };

static mNpcW_GoalData_c l_grim_man_goal_data[] = { { l_grim_man_time_ed, ARRAY_COUNT(l_grim_man_time_ed),
                                                     mNpcW_TIME_2_SEC(24, 0, 0) } };

static mNpcW_GoalDataTable_c l_grim_man_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_grim_man_goal_data);

static u8 l_naniwa_lady_time_1_30[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE,
                                        mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_ALONE,
                                        mNpcW_GOAL_ALONE,  mNpcW_GOAL_ALONE };
static u8 l_naniwa_lady_time_13[] = { mNpcW_GOAL_HOME };
static u8 l_naniwa_lady_time_21[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME, mNpcW_GOAL_HOME,
                                      mNpcW_GOAL_ALONE };

static mNpcW_GoalData_c l_naniwa_lady_goal_data[] = {
    { l_naniwa_lady_time_1_30, ARRAY_COUNT(l_naniwa_lady_time_1_30), mNpcW_TIME_2_SEC(1, 30, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(10, 0, 0) },
    { l_naniwa_lady_time_13, ARRAY_COUNT(l_naniwa_lady_time_13), mNpcW_TIME_2_SEC(13, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(14, 0, 0) },
    { l_naniwa_lady_time_21, ARRAY_COUNT(l_naniwa_lady_time_21), mNpcW_TIME_2_SEC(21, 0, 0) },
    { NULL, 0, mNpcW_TIME_2_SEC(22, 0, 0) },
    { l_naniwa_lady_time_1_30, ARRAY_COUNT(l_naniwa_lady_time_1_30), mNpcW_TIME_2_SEC(24, 0, 0) }
};

static mNpcW_GoalDataTable_c l_naniwa_lady_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_naniwa_lady_goal_data);

static mNpcW_GoalDataTable_c* l_looks_goal_table[mNpc_LOOKS_NUM] = {
    &l_girl_goal_table,       &l_kogirl_goal_table,   &l_boy_goal_table,
    &l_sports_man_goal_table, &l_grim_man_goal_table, &l_naniwa_lady_goal_table
};

mNpcW_GoalData_c* mNpcW_GetGoalDataInfo(s32 looks, s32 now_sec) {
    mNpcW_GoalDataTable_c* table = l_looks_goal_table[looks];
    mNpcW_GoalData_c* goal_data = table->data_p;
    s32 i;

    for (i = 0; i < table->count; i++) {
        if (goal_data->end_time > now_sec) {
            break;
        }

        goal_data++;
    }

    if (i == table->count) {
        goal_data = &table->data_p[table->count - 1];
    }

    return goal_data;
}

void mNpcW_ClearNpcWalkAppear(mNpcW_appear_c* appear_info) {
    appear_info->status = mNpcW_APPEAR_STATUS_NUM;
    appear_info->way = mNpcW_APPEAR_WAY_NUM;
}

void mNpcW_ClearNpcWalkInfo(mNpcW_info_c* info, s32 count) {
    for (; count != 0 && info != NULL; count--) {
        bzero(info, sizeof(mNpcW_info_c));
        mNpc_ClearAnimalPersonalID(&info->id);
        info->idx = -1;
        info->status = mNpcW_INFO_STATUS_NUM;
        info->goal_type = mNpcW_GOAL_NUM;
        mNpcW_ClearNpcWalkAppear(&info->appear_info);

        info++;
    }
}

void mNpcW_ClearNpcWalk(mNpc_walk_c* walk) {
    bzero(walk, sizeof(mNpc_walk_c));
    mNpcW_ClearNpcWalkInfo(&walk->info[0], mNpcW_MAX);
}

s32 mNpcW_CheckFreeNpcWalkInfo(mNpcW_info_c* info) {
    s32 res = FALSE;

    if (info != NULL) {
        res = mNpc_CheckFreeAnimalPersonalID(&info->id);
    }

    return res;
}

s32 mNpcW_GetFreeNpcWalkInfoIdx(mNpcW_info_c* info, s32 num) {
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

s32 mNpcW_GetNpcWalkInfoIdx(mNpcW_info_c* info, s32 num, AnmPersonalID_c* anm_id) {
    s32 idx = -1;
    s32 i;

    if ((anm_id != NULL) && (mNpc_CheckFreeAnimalPersonalID(anm_id) == FALSE)) {
        for (i = 0; i < num; i++) {
            if (mNpc_CheckCmpAnimalPersonalID(anm_id, &info->id) == TRUE) {
                idx = i;
                break;
            }

            info++;
        }
    }

    return idx;
}

s32 func_800AF060_jp(mNpcW_info_c* info, s32 num, s32 want_idx) {
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

s32 mNpcW_DecideNpc(Animal_c* animal, u16 used) {
    s32 idx;
    u16 exist;
    u16 possible_goal;
    s32 unused;
    s32 now_sec;
    s32 i;

    exist = 0;
    possible_goal = 0;
    unused = 0;
    now_sec = common_data.time.now_sec;
    idx = -1;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            mNpcW_GoalData_c* goal_data;
            exist |= (1 << i);

            goal_data = mNpcW_GetGoalDataInfo(animal->id.looks, now_sec);
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

void mNpcW_SetNpcWalkInfo(mNpcW_info_c* info, Animal_c* animal, s32 idx) {
    mNpcW_GoalData_c* goal_data;
    s32 now_sec = common_data.time.now_sec;
    u32 index;

    mNpc_CopyAnimalPersonalID(&info->id, &animal->id);
    info->idx = idx;
    goal_data = mNpcW_GetGoalDataInfo(animal->id.looks, now_sec);

    if (goal_data->count > 0) {
        index = RANDOM(goal_data->count);
        info->goal_type = goal_data->types[index];
    } else {
        info->goal_type = mNpcW_GOAL_MY_HOME; /* Default to acre the villager's house is in */
    }
    info->status = 1;
}

s32 mNpcW_ChangeNpcWalk(mNpc_walk_c* walk, mNpcW_info_c* info) {
    s32 free_idx;
    s32 idx = -1;
    s32 i;

    mNpcW_ClearNpcWalkInfo(info, 1);
    walk->used_info_num--;
    free_idx = mNpcW_GetFreeNpcWalkInfoIdx(walk->info, mNpcW_MAX);

    if (free_idx != -1) {
        mNpcW_info_c* free_info = &walk->info[free_idx];

        mNpcW_ClearNpcWalkInfo(free_info, 1);
        idx = mNpcW_DecideNpc(common_data.save.animals, walk->used_idx_bitfield);

        if (idx == -1) {
            walk->used_idx_bitfield = 0;
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (i == walk->info[i].idx) {
                    walk->used_idx_bitfield |= (1 << i);
                }
            }

            idx = mNpcW_DecideNpc(common_data.save.animals, walk->used_idx_bitfield);
        }

        mNpcW_SetNpcWalkInfo(free_info, &common_data.save.animals[idx], idx);
        walk->used_idx_bitfield |= (1 << idx);
        mNpcW_SetGoalBlock(free_info);
    }

    return idx;
}

s32 mNpcW_GetAloneBlock(u8* goal_block_x, u8* goal_block_z) {
    Animal_c* animal = common_data.save.animals;
    mNpc_NpcList_c* npclist = common_data.npclist;
    u8 block_field[FG_BLOCK_Z_NUM + 2];
    u8 animal_count = 0;
    s32 selected;
    s32 block_x;
    s32 block_z;
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
    *goal_block_x = 0;
    *goal_block_z = 0;

    bzero(block_field, FG_BLOCK_Z_NUM + 2);
    /* Log all acres which currently have a villager in them */
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE &&
            mFI_Wpos2BlockNum(&block_x, &block_z, npclist->position) == TRUE) {
            block_field[block_z] |= (1 << block_x);
            animal_count++;
        }

        animal++;
        npclist++;
    }

    /* Select a random empty acre to go to */
    z = 1;
    selected = RANDOM(FG_BLOCK_TOTAL_NUM - animal_count);
    /* Find the random acre and set output */
    for (i = 1; i < BLOCK_Z_NUM - 3; i++) {
        for (j = 1; j < BLOCK_X_NUM - 1; j++) {
            if (((block_field[z] >> j) & 1) == 0) {
                if (selected <= 0) {
                    *goal_block_x = j;
                    *goal_block_z = i;
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

void mNpcW_GetBlockXZNumExceptHome(s32* goal_block_x, s32* goal_block_z, Animal_c* animal) {
    u8 possible_x = 0xFF;
    u8 possible_z = 0xFF;

    s32 x_num = 0;
    s32 z_num = 0;

    s32 selected_x;
    s32 selected_z;

    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            u8 home_block_x = animal->home_info.block_x - 1;
            u8 home_block_z = animal->home_info.block_z - 1;

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

    *goal_block_x = i + 1;

    for (i = 0; i < FG_BLOCK_Z_NUM; i++) {
        if (((possible_z >> i) & 1) == 1) {
            if (selected_z <= 0) {
                break;
            } else {
                selected_z--;
            }
        }
    }

    *goal_block_z = i + 1;
}

s32 mNpcW_CheckDiffBlockWalkNpcHome(s32 block_x, s32 block_z, mNpcW_info_c* info) {
    s32 res = FALSE;
    Anmhome_c* home;
    s32 i;
    s32 idx;

    for (i = 0; i < mNpcW_MAX; i++) {
        idx = info->idx;
        if (idx != -1) {
            home = &common_data.save.animals[idx].home_info;

            if (home->block_x == block_x && home->block_z == block_z) {
                break;
            }
        }

        info++;
    }

    if (i == mNpcW_MAX) {
        res = TRUE;
    }

    return res;
}

void mNpcW_SetHomeBlockSource(mNpc_walk_c* walk, Animal_c* animal) {
    Animal_c* animal_p = animal;
    u16 diff_animal_field;
    s32 diff_animal_num;
    s32 i;

    diff_animal_field = 0;
    diff_animal_num = 0;

    l_goal_block[mNpcW_GOAL_BLOCK_HOME][0] = 0;
    l_goal_block[mNpcW_GOAL_BLOCK_HOME][1] = 0;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            Anmhome_c* home = &animal->home_info;

            if (mNpcW_CheckDiffBlockWalkNpcHome(home->block_x, home->block_z, walk->info) == TRUE) {
                diff_animal_field |= (1 << i);
                diff_animal_num++;
            }
        }

        animal++;
    }

    if (diff_animal_num > 0) {
        s32 selected = RANDOM(diff_animal_num);
        Anmhome_c* home_info;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((diff_animal_field >> i) & 1) == 1) {
                if (selected == 0) {
                    break;
                } else {
                    selected--;
                }
            }
        }

        home_info = &animal_p[i].home_info;
        l_goal_block[mNpcW_GOAL_BLOCK_HOME][0] = home_info->block_x + 1;
        l_goal_block[mNpcW_GOAL_BLOCK_HOME][1] = home_info->block_z + 1;
    }

    if (l_goal_block[mNpcW_GOAL_BLOCK_HOME][0] == 0 || l_goal_block[mNpcW_GOAL_BLOCK_HOME][1] == 0) {
        mNpcW_GetBlockXZNumExceptHome(&l_goal_block[mNpcW_GOAL_BLOCK_HOME][0], &l_goal_block[mNpcW_GOAL_BLOCK_HOME][1],
                                      animal_p);
    }
}

void mNpcW_InitGoalBlockSource(mNpc_walk_c* walk, Animal_c* animal) {
    s32 shrine_x;
    s32 shrine_z;
    UNUSED s32 pad;

    mFI_BlockKind2BkNum(&shrine_x, &shrine_z, mRF_BLOCKKIND_SHRINE);

    l_goal_block[mNpcW_GOAL_BLOCK_SHRINE][0] = shrine_x;
    l_goal_block[mNpcW_GOAL_BLOCK_SHRINE][1] = shrine_z;

    mNpcW_SetHomeBlockSource(walk, animal);
}

void mNpcW_SetGoalBlock(mNpcW_info_c* info) {
    s32 idx;

    switch (info->goal_type) {
        case mNpcW_GOAL_SHRINE:
            info->goal_block_x = l_goal_block[mNpcW_GOAL_BLOCK_SHRINE][0];
            info->goal_block_z = l_goal_block[mNpcW_GOAL_BLOCK_SHRINE][1];
            break;

        case mNpcW_GOAL_HOME:
            info->goal_block_x = l_goal_block[mNpcW_GOAL_BLOCK_HOME][0];
            info->goal_block_z = l_goal_block[mNpcW_GOAL_BLOCK_HOME][1];
            break;

        case mNpcW_GOAL_ALONE:
            mNpcW_GetAloneBlock(&info->goal_block_x, &info->goal_block_z);
            break;

        case mNpcW_GOAL_MY_HOME:
            idx = info->idx;

            info->goal_block_x = common_data.save.animals[idx].home_info.block_x;
            info->goal_block_z = common_data.save.animals[idx].home_info.block_z;
            break;

        default:
            info->goal_block_x = 0;
            info->goal_block_z = 0;
            break;
    }
}

void mNpcW_InitNpcWalk(mNpc_walk_c* walk) {
    Animal_c* animals;
    mNpcW_info_c* info = walk->info;
    s32 idx;
    s32 i;

    mNpcW_ClearNpcWalk(walk);
    bzero(l_goal_block, sizeof(l_goal_block));
    bzero(l_arrive_stay_count, sizeof(l_arrive_stay_count));

    animals = common_data.save.animals;
    walk->info_max = mNpcW_GET_WALK_NUM(common_data.save.now_npc_max);

    for (i = 0; i < walk->info_max; i++) {
        idx = mNpcW_DecideNpc(animals, walk->used_idx_bitfield);

        mNpcW_SetNpcWalkInfo(info, &common_data.save.animals[idx], idx);
        walk->used_idx_bitfield |= (1 << idx);
        info++;
    }

    walk->used_info_num = walk->info_max;
    mNpcW_InitGoalBlockSource(walk, animals);
}

s32 mNpcW_GetAppearStatusWay(u8* status, u8* way, Animal_c* animal) {
    mNpc_walk_c* walk = &common_data.npc_walk;
    s32 info_idx;
    s32 res = FALSE;

    *status = mNpcW_APPEAR_STATUS_NUM;

    info_idx = mNpcW_GetNpcWalkInfoIdx(walk->info, mNpcW_MAX, &animal->id);

    if (info_idx >= 0) {
        *status = walk->info[info_idx].appear_info.status;
        *way = walk->info[info_idx].appear_info.way;
        res = TRUE;
    } else {
        *status = mNpcW_APPEAR_STATUS_0;
        *way = mNpcW_APPEAR_WAY_NUM;
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

    *status = mNpcW_INFO_STATUS_NUM;
    *goal = mNpcW_GOAL_NUM;

    if (idx >= 0 && idx < ANIMAL_NUM_MAX) {
        mNpc_walk_c* walk = &common_data.npc_walk;
        s32 info_idx = mNpcW_GetNpcWalkInfoIdx(walk->info, mNpcW_MAX, &common_data.save.animals[idx].id);

        if (info_idx >= 0) {
            res = TRUE;
            *status = walk->info[info_idx].status;
            *goal = walk->info[info_idx].goal_type;
        }
    }

    return res;
}

s32 mNpcW_GetNearGate(s32* target_ut_x, s32* target_ut_z, s32 block_x, s32 block_z, s32 ut_x, s32 ut_z) {
    u8 block_type;
    mRF_gate_c* gate;
    s32 difference;
    UNUSED s32 pad;
    s32 x;
    s32 z;
    s32 gate_count;
    s32 i;
    s32 res = FALSE;
    s32 direction;

    *target_ut_x = UT_X_NUM;
    *target_ut_z = UT_Z_NUM;

    if (ut_x >= 0 && ut_x < UT_X_NUM && ut_z >= 0 && ut_z < UT_Z_NUM) {
        block_type = mFI_BkNum2BlockType(block_x, block_z);
        x = ut_x < (UT_X_NUM / 2) ? ut_x : UT_X_NUM - ut_x;
        z = ut_z < (UT_Z_NUM / 2) ? ut_z : UT_Z_NUM - ut_z;

        if (x < z) {
            if (ut_x < (UT_X_NUM / 2)) {
                direction = mRF_DIRECT_WEST;
            } else {
                direction = mRF_DIRECT_EAST;
            }
        } else {
            if (ut_z < (UT_Z_NUM / 2)) {
                direction = mRF_DIRECT_NORTH;
            } else {
                direction = mRF_DIRECT_SOUTH;
            }
        }

        gate = mRF_BlockTypeDirect2GateData(&gate_count, block_type, direction);
        if (gate != NULL && gate_count > 0) {

            for (i = 0; i < gate_count; i++) {
                x = gate->ut1 & 0xF;
                z = gate->ut1 >> 4;

/* BUG: this is likely meant to be 'if (direction == mRF_DIRECT_WEST || direction == mRF_DIRECT_EAST)' */
#ifndef BUGFIXES
                if (direction == mRF_DIRECT_WEST || direction == mRF_DIRECT_WEST) {
#else
                if (direction == mRF_DIRECT_WEST || direction == mRF_DIRECT_EAST) {
#endif
                    difference = ut_z - z;
                    difference = ABS(difference);
                } else {
                    difference = ut_x - x;
                    difference = ABS(difference);
                }

                if (difference < UT_BASE_NUM) {
                    *target_ut_x = x;
                    *target_ut_z = z;
                    res = TRUE;
                }

                gate++;
            }
        }
    }

    return res;
}
