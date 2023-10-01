#ifndef M_NPC_SCHEDULE_H
#define M_NPC_SCHEDULE_H

#include "ultra64.h"
#include "m_npc.h"

typedef enum NpsScheduleType{
    /* 0 */ NPS_SCHEDULE_FIELD, /* in same acre as their home */
    /* 1 */ NPS_SCHEDULE_IN_HOUSE, /* inside their house */
    /* 2 */ NPS_SCHEDULE_SLEEP, /* asleep in their house */
    /* 3 */ NPS_SCHEDULE_STAND, /* standing around town?? */
    /* 4 */ NPS_SCHEDULE_WANDER, /* wander around town */
    /* 5 */ NPS_SCHEDULE_SPECIAL, /* unique schedule method for each NPC actor type */
    /* 6 */ NPS_SCHEDULE_TYPE_NUM
} NpsScheduleType;

typedef struct NpsScheduleData {
    /* 0x00 */ NpsScheduleType type;
    /* 0x04 */ s32 endTime;
} NpsScheduleData; // size = 0x8

typedef struct NpsScheduleDataTable {
    /* 0x00 */ s32 count;
    /* 0x04 */ NpsScheduleData* scheduleData;
} NpsScheduleDataTable; // size = 0x8

typedef struct NpsSchedule{
    /* 0x00 */ AnmPersonalID_c* id;
    /* 0x04 */ NpsScheduleDataTable* dataTable;
    /* 0x08 */ u8 currentType;
    /* 0x09 */ u8 forcedType;
    /* 0x0A */ u8 savedType;
    /* 0x0C */ s32 forcedTimer;
}NpsSchedule; // size = 0x10



NpsSchedule* mNPS_get_schedule_area(AnmPersonalID_c* id);
void mNPS_set_schedule_area(AnmPersonalID_c* id);
void mNPS_reset_schedule_area(AnmPersonalID_c* id);
void mNPS_schedule_manager_sub0(void);
void mNPS_schedule_manager_sub(void);
void mNPS_schedule_manager(void);
void mNPS_set_all_schedule_area(void);

#endif
