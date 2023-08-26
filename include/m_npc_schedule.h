#ifndef M_NPC_SCHEDULE_H
#define M_NPC_SCHEDULE_H

#include "ultra64.h"
#include "m_npc_personal_id.h"

struct AnmPersonalId;

typedef enum NPC_SCHEDULE {
    /* 0 */ NPC_SCHEDULE_FIELD, /* in same acre as their home */
    /* 1 */ NPC_SCHEDULE_IN_HOUSE, /* inside their house */
    /* 2 */ NPC_SCHEDULE_SLEEP, /* asleep in their house */
    /* 3 */ NPC_SCHEDULE_STAND, /* standing around town?? */
    /* 4 */ NPC_SCHEDULE_WANDER, /* wander around town */
    /* 5 */ NPC_SCHEDULE_SPECIAL, /* unique schedule method for each NPC actor type */

    /* 6 */ NPC_SCHEDULE_NUM
} NPC_SCHEDULE;

typedef struct NpcScheduleData {
    /* 0x00 */ u32 type;
    /* 0x04 */ s32 endTime;
} NpcScheduleData; // size = 0x8

typedef struct NpcScheduleDataTable {
    /* 0x00 */ s32 count;
    /* 0x04 */ NpcScheduleData* schedData;
} NpcScheduleDataTable; // size = 0x8

typedef struct NpcSchedule {
    /* 0x00 */ AnmPersonalId* id;
    /* 0x04 */ NpcScheduleDataTable* dataTable;
    /* 0x08 */ u8 currentType;
    /* 0x09 */ u8 forcedType;
    /* 0x0A */ u8 savedType;
    /* 0x0C */ s32 forcedTimer;
} NpcSchedule; // size = 0x10

NpcSchedule* mNPS_get_schedule_area(AnmPersonalId* anmId);
void mNPS_set_schedule_area(AnmPersonalId* anmId);
void mNPS_reset_schedule_area(AnmPersonalId* anmId);
void mNPS_schedule_manager_sub0(void);
void mNPS_schedule_manager_sub(void);
void mNPS_schedule_manager(void);
void mNPS_set_all_schedule_area(void);

#endif
