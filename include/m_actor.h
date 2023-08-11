#ifndef M_ACTOR_H
#define M_ACTOR_H

#include "ultra64.h"

struct PlayState;
struct ActorEntry;

typedef enum AllocType {
    /* 0 */ ALLOCTYPE_NORMAL
} AllocType;

// a.k.a. ActorInit
struct ActorProfile;

typedef struct Actor {
    /*  */ s32 placeholder;
} Actor; // size >= ?

// a.k.a. ActorContext
typedef struct ActorInfo {
    /*  */ s32 placeholder;
} ActorInfo; // size >= ?

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
void Actor_info_call_actor(struct PlayState *play, ActorInfo *actorInfo);
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
// void Actor_info_make_actor();
// void Actor_info_make_child_actor();
// void restore_fgdata();
// void restore_fgdata_one();
// void restore_fgdata_all();
// void Actor_info_save_actor();
// void Actor_info_delete();
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
