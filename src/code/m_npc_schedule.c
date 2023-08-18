#include "global.h"
#include "m_npc_schedule.h"
#include "m_common_data.h"
#include "m_npc.h"
#include "m_event.h"
#include "macros.h"

#define mNPS_TIME_2_SEC(hour, min, sec) ((hour)*3600 + (min)*60 + (sec))
#define mNPS_MAKE_SCHEDULE_TABLE(sched_data) \
    { ARRAY_COUNT(sched_data), sched_data }

static mNPS_schedule_data_c girl_schedule_dt[] = {
    { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(5, 0, 0) },   { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(6, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(12, 0, 0) },  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(13, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(18, 30, 0) }, { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(21, 0, 0) },
    { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c girl_schedule = mNPS_MAKE_SCHEDULE_TABLE(girl_schedule_dt);

static mNPS_schedule_data_c ko_girl_schedule_dt[] = {
    { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(7, 0, 0) },  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(8, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(13, 0, 0) }, { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(14, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(22, 0, 0) }, { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(23, 30, 0) },
    { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c ko_girl_schedule = mNPS_MAKE_SCHEDULE_TABLE(ko_girl_schedule_dt);

static mNPS_schedule_data_c boy_schedule_dt[] = {
    { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(8, 0, 0) },   { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(9, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(12, 0, 0) },  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(14, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(19, 30, 0) }, { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(22, 0, 0) },
    { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c boy_schedule = mNPS_MAKE_SCHEDULE_TABLE(boy_schedule_dt);

static mNPS_schedule_data_c sport_man_schedule_dt[] = {
    { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(1, 0, 0) },   { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(5, 30, 0) },
    { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(6, 30, 0) },  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(12, 0, 0) },
    { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(12, 30, 0) }, { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(23, 0, 0) },
    { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c sport_man_schedule = mNPS_MAKE_SCHEDULE_TABLE(sport_man_schedule_dt);

static mNPS_schedule_data_c grim_man_schedule_dt[] = {
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(4, 0, 0) },  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(5, 0, 0) },
    { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(10, 0, 0) }, { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(11, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(15, 0, 0) }, { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(16, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(22, 0, 0) }, { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(23, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c grim_man_schedule = mNPS_MAKE_SCHEDULE_TABLE(grim_man_schedule_dt);

static mNPS_schedule_data_c naniwa_lady_schedule_dt[] = {
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(1, 30, 0) }, { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(2, 30, 0) },
    { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(9, 0, 0) },  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(10, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(13, 0, 0) }, { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(14, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(21, 0, 0) }, { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(22, 0, 0) },
    { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c naniwa_lady_schedule = mNPS_MAKE_SCHEDULE_TABLE(naniwa_lady_schedule_dt);

static mNPS_schedule_data_table_c* mNPS_schedule[mNpc_LOOKS_NUM] = { &girl_schedule,     &ko_girl_schedule,
                                                                     &boy_schedule,      &sport_man_schedule,
                                                                     &grim_man_schedule, &naniwa_lady_schedule };

mNPS_schedule_c* mNPS_get_schedule_area(AnmPersonalID_c* anm_id) {
    mNPS_schedule_c* schedule = common_data.npc_schedules;
    s32 i;

    for (i = 0; i < SCHEDULE_NUM; i++) {
        if (schedule->id == anm_id) {
            return schedule;
        }

        schedule++;
    }

    return NULL;
}

void mNPS_set_schedule_area(AnmPersonalID_c* anm_id) {
    mNPS_schedule_c* schedule = mNPS_get_schedule_area(NULL); /* try to get an unused schedule */

    if (schedule != NULL) {
        schedule->id = anm_id;
        schedule->data_table = mNPS_schedule[anm_id->looks];
        schedule->forced_timer = 0;
    }
}

void mNPS_reset_schedule_area(AnmPersonalID_c* anm_id) {
    mNPS_schedule_c* schedule = mNPS_get_schedule_area(anm_id);

    if (schedule != NULL) {
        schedule->id = NULL;
    }
}

void mNPS_schedule_manager_sub0(void) {
    mNPS_schedule_c* schedule = common_data.npc_schedules;
    s32 i;

    /* Set all town animals to go outside in their home block */
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (schedule->id != NULL) {
            schedule->current_type = mNPS_SCHED_FIELD;
        }

        schedule++;
    }
}

void mNPS_schedule_manager_sub(void) {
    s32 now_sec = common_data.time.now_sec;
    mNPS_schedule_c* schedule = common_data.npc_schedules;
    s32 i;
    s32 j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (schedule->id != NULL) {
            mNPS_schedule_data_c* schedule_entry = schedule->data_table->sched_data;

            for (j = schedule->data_table->count; j != 0; j--) {
                if (now_sec < schedule_entry->end_time) {
                    break;
                }
                schedule_entry++;
            }

            schedule->saved_type = schedule_entry->type;
            if (schedule->forced_timer > 0) {
                schedule->current_type = schedule->forced_type;
                schedule->forced_timer--;
            } else {
                schedule->current_type = schedule->saved_type;
            }
        }
        schedule++;
    }
}

void mNPS_schedule_manager(void) {
    s32 force_outside = mEv_CheckFirstJob() == TRUE;

    if (force_outside == FALSE) {
        force_outside = mEv_check_status(mEv_EVENT_UNK_D, mEv_STATUS_ACTIVE) != FALSE;
    }

    if (force_outside == TRUE) {
        mNPS_schedule_manager_sub0();
    } else {
        mNPS_schedule_manager_sub();
    }
}

void mNPS_set_all_schedule_area(void) {
    Animal_c* animal = common_data.save.animals;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == 0) {
            mNPS_set_schedule_area(&animal->id);
        }
        animal++;
    }

    mNPS_schedule_manager();
}
