#ifndef M_NPC_SCHEDULE_H
#define M_NPC_SCHEDULE_H

#include "ultra64.h"
#include "m_npc_personal_id.h"

struct AnmPersonalID_c;

typedef enum mNPS_SCHED{
    /* 0 */ mNPS_SCHED_FIELD, /* in same acre as their home */
    /* 1 */ mNPS_SCHED_IN_HOUSE, /* inside their house */
    /* 2 */ mNPS_SCHED_SLEEP, /* asleep in their house */
    /* 3 */ mNPS_SCHED_STAND, /* standing around town?? */
    /* 4 */ mNPS_SCHED_WANDER, /* wander around town */
    /* 5 */ mNPS_SCHED_SPECIAL, /* unique schedule method for each NPC actor type */

    /* 6 */ mNPS_SCHED_TYPE_NUM
} mNPS_SCHED;

typedef struct mNPS_schedule_data_c {
    /* 0x00 */   u32 type;
    /* 0x04 */   s32 end_time;
} mNPS_schedule_data_c; // size = 0x8

typedef struct mNPS_schedule_data_table_c {
    /* 0x00 */ s32 count;
    /* 0x04 */ mNPS_schedule_data_c* sched_data;
} mNPS_schedule_data_table_c; // size = 0x8

typedef struct mNPS_schedule_c {
    /* 0x00 */ AnmPersonalID_c* id;
    /* 0x04 */ mNPS_schedule_data_table_c* data_table;
    /* 0x08 */ u8 current_type;
    /* 0x09 */ u8 forced_type;
    /* 0x0A */ u8 saved_type;
    /* 0x0C */ s32 forced_timer;
} mNPS_schedule_c; // size = 0x10

mNPS_schedule_c* mNPS_get_schedule_area(AnmPersonalID_c* anm_id);
void mNPS_set_schedule_area(AnmPersonalID_c* anm_id);
void mNPS_reset_schedule_area(AnmPersonalID_c* anm_id);
void mNPS_schedule_manager_sub0(void);
void mNPS_schedule_manager_sub(void);
void mNPS_schedule_manager(void);
void mNPS_set_all_schedule_area(void);

#endif
