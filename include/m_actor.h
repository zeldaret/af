#ifndef M_ACTOR_H
#define M_ACTOR_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"

struct PlayState;
struct ActorEntry;

typedef enum AllocType {
    /* 0 */ ALLOCTYPE_NORMAL
} AllocType;

typedef enum ActorType {
    /* 0 */ ACTORCAT_0,
    /* 1 */ ACTORCAT_1,
    /* 2 */ ACTORCAT_2,
    /* 3 */ ACTORCAT_3,
    /* 4 */ ACTORCAT_4,
    /* 5 */ ACTORCAT_5,
    /* 6 */ ACTORCAT_6,
    /* 7 */ ACTORCAT_7,
    /* 8 */ ACTORCAT_MAX
} ActorType;

// a.k.a. ActorInit
struct ActorProfile;

typedef struct PosRot {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3s rot;
} PosRot; // size = 0x14

typedef struct Actor {
    /* 0x000 */ UNK_TYPE1 unk_000[0x28];
    /* 0x028 */ PosRot world;
} Actor; // size >= 0x3C

typedef struct ActorListEntry {
    /* 0x0 */ UNK_TYPE1 unk_0[0x4];
    /* 0x8 */ Actor* head;
} ActorListEntry; // size >= 0xC

// a.k.a. ActorContext
typedef struct ActorInfo {
    /* 0x00 */ UNK_TYPE1 unk_0[0x4];
    /* 0x00 */ ActorListEntry actorLists[ACTORCAT_MAX];
} ActorInfo; // size = 0x44

// void func_80056380_jp();
// void projection_pos_set();
// void Actor_world_to_eye();
// void Actor_position_move();
// void Actor_position_speed_set();
// void Actor_position_moveF();
// void Actor_player_look_direction_check();
// void Actor_display_position_set();
// void Actor_data_bank_dma_end_check();
// void Shape_Info_init();
// void Actor_foot_shadow_pos_set();
// void Actor_delete();
// void Actor_ct();
// void Actor_dt();
// void Actor_draw();
// void Actor_draw_actor_no_culling_check();
// void Actor_draw_actor_no_culling_check2();
// void Actor_cull_check();
// void Actor_delete_check();
void Actor_info_ct(struct PlayState *play, ActorInfo *actorInfo, struct ActorEntry *actorEntry);
void Actor_info_dt(ActorInfo *actorInfo, struct PlayState *play);
// void Actor_info_call_actor(struct PlayState *play, ??);
void Actor_info_draw_actor(struct PlayState *play, ActorInfo *actorInfo);
// void Actor_info_part_new();
// void Actor_info_part_delete();
// void Actor_free_overlay_area();
// void actor_free_check();
// void Actor_get_overlay_area();
// void func_80057940_jp();
// void func_80057A8C_jp();
// void func_80057B70_jp();
// void Actor_data_bank_regist_check();
// void Actor_malloc_actor_class();
// void Actor_init_actor_class();
Actor* Actor_info_make_actor(ActorInfo* actorInfo, struct PlayState* play, s16 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, s32 argE, s32 argF);
// void Actor_info_make_child_actor();
// void restore_fgdata();
// void restore_fgdata_one();
// void restore_fgdata_all();
// void Actor_info_save_actor();
Actor* Actor_info_delete(ActorInfo* actorInfo, Actor* actor, struct PlayState* play);
// void Actor_info_name_search_sub();
// void Actor_info_name_search();
// void Actor_info_fgName_search_sub();
// void Actor_info_fgName_search();
// void Part_Break_init();
// void HiliteReflect_new();
// void HiliteReflect_init();
// void HiliteReflect_xlu_init();
// void HiliteReflect_light_init();
// void Setpos_HiliteReflect_init();
// void Setpos_HiliteReflect_xlu_init();
// void Setpos_HiliteReflect_light_init();

#endif
