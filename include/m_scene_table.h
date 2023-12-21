#ifndef M_SCENE_TABLE_H
#define M_SCENE_TABLE_H

#include "ultra64.h"
#include "z64math.h"

typedef enum SceneTable {
    /* 00 */ SCENE_TEST1,
    /* 01 */ SCENE_TEST2,
    /* 02 */ SCENE_TEST3,
    /* 03 */ SCENE_WATER_TEST,
    /* 04 */ SCENE_FOOTPRINT_TEST,
    /* 05 */ SCENE_NPC_TEST,
    /* 06 */ SCENE_NPC_HOUSE, /* npc house interior */
    /* 07 */ SCENE_FG, /* outdoors/FG */
    /* 08 */ SCENE_RANDOM_NPC_TEST,
    /* 09 */ SCENE_SHOP0, /* nook's cranny */
    /* 10 */ SCENE_BG_TEST_NO_RIVER,
    /* 11 */ SCENE_BG_TEST_RIVER,
    /* 12 */ SCENE_BROKER_SHOP, /* crazy redd's tent */
    /* 13 */ SCENE_FIELD_TOOL_INSIDE,
    /* 14 */ SCENE_POST_OFFICE, /* post office */
    /* 15 */ SCENE_START_DEMO, /* after player select */
    /* 16 */ SCENE_START_DEMO2, /*  */
    /* 17 */ SCENE_POLICE_BOX,
    /* 18 */ SCENE_BUGGY,
    /* 19 */ SCENE_PLAYERSELECT,
    /* 20 */ SCENE_MY_ROOM_S,
    /* 21 */ SCENE_MY_ROOM_M,
    /* 22 */ SCENE_MY_ROOM_L,
    /* 23 */ SCENE_CONVENI, /* nook 'n' go */
    /* 24 */ SCENE_SUPER, /* nookway */
    /* 25 */ SCENE_DEPART, /* nookington's 1st floor */
    /* 26 */ SCENE_TEST5,
    /* 27 */ SCENE_PLAYERSELECT_2,
    /* 28 */ SCENE_PLAYERSELECT_3,
    /* 29 */ SCENE_DEPART_2, /* nookington's 2nd floor */
    /* 30 */ SCENE_EVENT_ANNOUNCEMENT,
    /* 31 */ SCENE_KAMAKURA,
    /* 32 */ SCENE_FIELD_TOOL,
    /* 33 */ SCENE_TITLE_DEMO, /* title screen demo */
    /* 34 */ SCENE_PLAYERSELECT_SAVE,
    /* 35 */ SCENE_NUM
} SceneTable;
extern Struct_8010EAA0 scene_data_status[];

#endif
