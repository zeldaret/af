#include "global.h"
#include "m_npc_schedule.h"
#include "m_common_data.h"
#include "m_npc.h"
#include "m_event.h"
#include "macros.h"

#define NPC_SCHEDULE_TIME_2_SEC(hour, min, sec) ((hour)*3600 + (min)*60 + (sec))
#define NPC_SCHEDULE_MAKE_SCHEDULE_TABLE(schedData) \
    { ARRAY_COUNT(schedData), schedData }

NpcScheduleData girl_schedule_dt[] = { { NPC_SCHEDULE_SLEEP, NPC_SCHEDULE_TIME_2_SEC(5, 0, 0) },
                                       { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(6, 0, 0) },
                                       { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(12, 0, 0) },
                                       { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(13, 0, 0) },
                                       { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(18, 30, 0) },
                                       { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(21, 0, 0) },
                                       { NPC_SCHEDULE_SLEEP, NPC_SCHEDULE_TIME_2_SEC(24, 0, 0) } };

NpcScheduleDataTable girl_schedule = NPC_SCHEDULE_MAKE_SCHEDULE_TABLE(girl_schedule_dt);

NpcScheduleData ko_girl_schedule_dt[] = { { NPC_SCHEDULE_SLEEP, NPC_SCHEDULE_TIME_2_SEC(7, 0, 0) },
                                          { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(8, 0, 0) },
                                          { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(13, 0, 0) },
                                          { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(14, 0, 0) },
                                          { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(22, 0, 0) },
                                          { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(23, 30, 0) },
                                          { NPC_SCHEDULE_SLEEP, NPC_SCHEDULE_TIME_2_SEC(24, 0, 0) } };

NpcScheduleDataTable ko_girl_schedule = NPC_SCHEDULE_MAKE_SCHEDULE_TABLE(ko_girl_schedule_dt);

NpcScheduleData boy_schedule_dt[] = { { NPC_SCHEDULE_SLEEP, NPC_SCHEDULE_TIME_2_SEC(8, 0, 0) },
                                      { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(9, 0, 0) },
                                      { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(12, 0, 0) },
                                      { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(14, 0, 0) },
                                      { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(19, 30, 0) },
                                      { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(22, 0, 0) },
                                      { NPC_SCHEDULE_SLEEP, NPC_SCHEDULE_TIME_2_SEC(24, 0, 0) } };

NpcScheduleDataTable boy_schedule = NPC_SCHEDULE_MAKE_SCHEDULE_TABLE(boy_schedule_dt);

NpcScheduleData sport_man_schedule_dt[] = { { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(1, 0, 0) },
                                            { NPC_SCHEDULE_SLEEP, NPC_SCHEDULE_TIME_2_SEC(5, 30, 0) },
                                            { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(6, 30, 0) },
                                            { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(12, 0, 0) },
                                            { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(12, 30, 0) },
                                            { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(23, 0, 0) },
                                            { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(24, 0, 0) } };

NpcScheduleDataTable sport_man_schedule = NPC_SCHEDULE_MAKE_SCHEDULE_TABLE(sport_man_schedule_dt);

NpcScheduleData grim_man_schedule_dt[] = { { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(4, 0, 0) },
                                           { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(5, 0, 0) },
                                           { NPC_SCHEDULE_SLEEP, NPC_SCHEDULE_TIME_2_SEC(10, 0, 0) },
                                           { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(11, 0, 0) },
                                           { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(15, 0, 0) },
                                           { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(16, 0, 0) },
                                           { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(22, 0, 0) },
                                           { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(23, 0, 0) },
                                           { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(24, 0, 0) } };

NpcScheduleDataTable grim_man_schedule = NPC_SCHEDULE_MAKE_SCHEDULE_TABLE(grim_man_schedule_dt);

NpcScheduleData naniwa_lady_schedule_dt[] = { { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(1, 30, 0) },
                                              { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(2, 30, 0) },
                                              { NPC_SCHEDULE_SLEEP, NPC_SCHEDULE_TIME_2_SEC(9, 0, 0) },
                                              { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(10, 0, 0) },
                                              { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(13, 0, 0) },
                                              { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(14, 0, 0) },
                                              { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(21, 0, 0) },
                                              { NPC_SCHEDULE_IN_HOUSE, NPC_SCHEDULE_TIME_2_SEC(22, 0, 0) },
                                              { NPC_SCHEDULE_FIELD, NPC_SCHEDULE_TIME_2_SEC(24, 0, 0) } };

NpcScheduleDataTable naniwa_lady_schedule = NPC_SCHEDULE_MAKE_SCHEDULE_TABLE(naniwa_lady_schedule_dt);

NpcScheduleDataTable* mNPS_schedule[NPC_LOOKS_NUM] = {
    &girl_schedule, &ko_girl_schedule, &boy_schedule, &sport_man_schedule, &grim_man_schedule, &naniwa_lady_schedule,
};

NpcSchedule* mNPS_get_schedule_area(AnmPersonalId* anmId) {
    NpcSchedule* schedule = gCommonData.npcSchedules;
    s32 i;

    for (i = 0; i < SCHEDULE_NUM; i++) {
        if (schedule->id == anmId) {
            return schedule;
        }

        schedule++;
    }

    return NULL;
}

void mNPS_set_schedule_area(AnmPersonalId* anmId) {
    NpcSchedule* schedule = mNPS_get_schedule_area(NULL); /* try to get an unused schedule */

    if (schedule != NULL) {
        schedule->id = anmId;
        schedule->dataTable = mNPS_schedule[anmId->looks];
        schedule->forcedTimer = 0;
    }
}

void mNPS_reset_schedule_area(AnmPersonalId* anmId) {
    NpcSchedule* schedule = mNPS_get_schedule_area(anmId);

    if (schedule != NULL) {
        schedule->id = NULL;
    }
}

void mNPS_schedule_manager_sub0(void) {
    NpcSchedule* schedule = gCommonData.npcSchedules;
    s32 i;

    /* Set all town animals to go outside in their home block */
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (schedule->id != NULL) {
            schedule->currentType = NPC_SCHEDULE_FIELD;
        }

        schedule++;
    }
}

void mNPS_schedule_manager_sub(void) {
    s32 nowSec = gCommonData.time.nowSec;
    NpcSchedule* schedule = gCommonData.npcSchedules;
    s32 i;
    s32 j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (schedule->id != NULL) {
            NpcScheduleData* schedule_entry = schedule->dataTable->schedData;

            for (j = schedule->dataTable->count; j != 0; j--) {
                if (nowSec < schedule_entry->endTime) {
                    break;
                }
                schedule_entry++;
            }

            schedule->savedType = schedule_entry->type;
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
    s32 force_outside = mEv_CheckFirstJob() == TRUE;

    if (force_outside == FALSE) {
        force_outside = mEv_check_status(EventStatus_13, EVENT_STATUS_ACTIVE) != FALSE;
    }

    if (force_outside == TRUE) {
        mNPS_schedule_manager_sub0();
    } else {
        mNPS_schedule_manager_sub();
    }
}

void mNPS_set_all_schedule_area(void) {
    Animal* animal = gCommonData.save.animals;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            mNPS_set_schedule_area(&animal->id);
        }
        animal++;
    }

    mNPS_schedule_manager();
}
