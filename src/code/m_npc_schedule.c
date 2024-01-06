#include "m_npc_schedule.h"
#include "m_common_data.h"
#include "m_npc.h"
#include "m_event.h"
#include "macros.h"

#define NPS_TIME_2_SEC(hour, min, sec) ((hour)*3600 + (min)*60 + (sec))
#define NPS_MAKE_SCHEDULE_TABLE(scheduleData) \
    { ARRAY_COUNT(scheduleData), scheduleData }

NpsScheduleData girl_schedule_dt[] = {
    { NPS_SCHEDULE_SLEEP, NPS_TIME_2_SEC(5, 0, 0) },   { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(6, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(12, 0, 0) },  { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(13, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(18, 30, 0) }, { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(21, 0, 0) },
    { NPS_SCHEDULE_SLEEP, NPS_TIME_2_SEC(24, 0, 0) },
};

NpsScheduleDataTable girl_schedule = NPS_MAKE_SCHEDULE_TABLE(girl_schedule_dt);

NpsScheduleData ko_girl_schedule_dt[] = {
    { NPS_SCHEDULE_SLEEP, NPS_TIME_2_SEC(7, 0, 0) },  { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(8, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(13, 0, 0) }, { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(14, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(22, 0, 0) }, { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(23, 30, 0) },
    { NPS_SCHEDULE_SLEEP, NPS_TIME_2_SEC(24, 0, 0) },
};

NpsScheduleDataTable ko_girl_schedule = NPS_MAKE_SCHEDULE_TABLE(ko_girl_schedule_dt);

NpsScheduleData boy_schedule_dt[] = {
    { NPS_SCHEDULE_SLEEP, NPS_TIME_2_SEC(8, 0, 0) },   { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(9, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(12, 0, 0) },  { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(14, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(19, 30, 0) }, { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(22, 0, 0) },
    { NPS_SCHEDULE_SLEEP, NPS_TIME_2_SEC(24, 0, 0) },
};

NpsScheduleDataTable boy_schedule = NPS_MAKE_SCHEDULE_TABLE(boy_schedule_dt);

NpsScheduleData sport_man_schedule_dt[] = {
    { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(1, 0, 0) },   { NPS_SCHEDULE_SLEEP, NPS_TIME_2_SEC(5, 30, 0) },
    { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(6, 30, 0) },  { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(12, 0, 0) },
    { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(12, 30, 0) }, { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(23, 0, 0) },
    { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(24, 0, 0) },
};

NpsScheduleDataTable sport_man_schedule = NPS_MAKE_SCHEDULE_TABLE(sport_man_schedule_dt);

NpsScheduleData grim_man_schedule_dt[] = {
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(4, 0, 0) },  { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(5, 0, 0) },
    { NPS_SCHEDULE_SLEEP, NPS_TIME_2_SEC(10, 0, 0) }, { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(11, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(15, 0, 0) }, { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(16, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(22, 0, 0) }, { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(23, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(24, 0, 0) },
};

NpsScheduleDataTable grim_man_schedule = NPS_MAKE_SCHEDULE_TABLE(grim_man_schedule_dt);

NpsScheduleData naniwa_lady_schedule_dt[] = {
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(1, 30, 0) }, { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(2, 30, 0) },
    { NPS_SCHEDULE_SLEEP, NPS_TIME_2_SEC(9, 0, 0) },  { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(10, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(13, 0, 0) }, { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(14, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(21, 0, 0) }, { NPS_SCHEDULE_IN_HOUSE, NPS_TIME_2_SEC(22, 0, 0) },
    { NPS_SCHEDULE_FIELD, NPS_TIME_2_SEC(24, 0, 0) },
};

NpsScheduleDataTable naniwa_lady_schedule = NPS_MAKE_SCHEDULE_TABLE(naniwa_lady_schedule_dt);

NpsScheduleDataTable* mNPS_schedule[NPC_LOOKS_NUM] = { &girl_schedule,      &ko_girl_schedule,  &boy_schedule,
                                                       &sport_man_schedule, &grim_man_schedule, &naniwa_lady_schedule };

NpsSchedule* mNPS_get_schedule_area(AnmPersonalID_c* id) {
    NpsSchedule* schedule = common_data.npcSchedule;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (schedule->id == id) {
            return schedule;
        }

        schedule++;
    }

    return NULL;
}

void mNPS_set_schedule_area(AnmPersonalID_c* id) {
    NpsSchedule* schedule = mNPS_get_schedule_area(NULL);

    if (schedule != NULL) {
        schedule->id = id;
        schedule->dataTable = mNPS_schedule[id->looks];
        schedule->forcedTimer = 0;
    }
}

void mNPS_reset_schedule_area(AnmPersonalID_c* id) {
    NpsSchedule* schedule = mNPS_get_schedule_area(id);

    if (schedule != NULL) {
        schedule->id = NULL;
    }
}

void mNPS_schedule_manager_sub0(void) {
    NpsSchedule* schedule = common_data.npcSchedule;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (schedule->id != NULL) {
            schedule->currentType = NPS_SCHEDULE_FIELD;
        }

        schedule++;
    }
}

void mNPS_schedule_manager_sub(void) {
    s32 sec = common_data.time.nowSec;
    NpsSchedule* schedule = common_data.npcSchedule;
    NpsScheduleData* entry;
    s32 i;
    s32 j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (schedule->id != NULL) {
            entry = schedule->dataTable->scheduleData;

            for (j = schedule->dataTable->count; j != 0; j--) {
                if (sec < entry->endTime) {
                    break;
                }
                entry++;
            }

            schedule->savedType = entry->type;
            if (schedule->forcedTimer > 0) {
                schedule->currentType = schedule->forcedType;
                schedule->forcedTimer--;
            } else {
                schedule->currentType = schedule->savedType;
            }
        }
        schedule++;
    }
}

void mNPS_schedule_manager(void) {
    s32 outside = mEv_CheckFirstJob() == TRUE;

    if (outside == FALSE) {
        outside = mEv_check_status(0xD, 1) != FALSE;
    }

    (outside == TRUE) ? mNPS_schedule_manager_sub0() : mNPS_schedule_manager_sub();
}

void mNPS_set_all_schedule_area(void) {
    Animal_c* animal = common_data.animals;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == 0) {
            mNPS_set_schedule_area(&animal->id);
        }
        animal++;
    }

    mNPS_schedule_manager();
}
