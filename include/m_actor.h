#ifndef M_ACTOR_H
#define M_ACTOR_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"

struct Actor;
struct PlayState;
struct ActorEntry;
struct ActorOverlay;
struct struct_801161E8_jp;

typedef enum AllocType {
    /* 0 */ ALLOCTYPE_NORMAL,
    /* 1 */ ALLOCTYPE_ABSOLUTE,
    /* 2 */ ALLOCTYPE_PERMANENT
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

typedef void(*ActorFunc)(struct Actor* this, struct PlayState* play);

// a.k.a. ActorInit
typedef struct ActorProfile {
    /* 0x00 */ s16 id;
    /* 0x02 */ u8 type;
    /* 0x04 */ u32 flags;
    /* 0x08 */ s16 objectId;
    /* 0x0C */ u32 instanceSize;
    /* 0x10 */ ActorFunc init;
    /* 0x14 */ ActorFunc destroy;
    /* 0x18 */ ActorFunc update;
    /* 0x1C */ ActorFunc draw;
    /* 0x20 */ ActorFunc unk_20;
} ActorProfile; // size = 0x24

typedef struct PosRot {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3s rot;
} PosRot; // size = 0x14

typedef struct Actor {
    /* 0x000 */ UNK_TYPE1 unk_000[0x28];
    /* 0x028 */ PosRot world;
    /* 0x03C */ UNK_TYPE1 unk_03C[0x11C];
    /* 0x158 */ struct Actor* unk_158;
} Actor; // size >= 0x15C, size <= 0x174

typedef struct ActorListEntry {
    /* 0x0 */ UNK_TYPE1 unk_0[0x4];
    /* 0x8 */ Actor* head;
} ActorListEntry; // size >= 0xC

// a.k.a. ActorContext
typedef struct ActorInfo {
    /* 0x00 */ s32 unk_00;
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
void Actor_ct(Actor* actor, struct PlayState* Play);
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
void Actor_info_part_new(ActorInfo* actorInfo, Actor* actor, u8 arg2);
// void Actor_info_part_delete();
void Actor_free_overlay_area(struct ActorOverlay* overlayEntry);
void actor_free_check(struct ActorOverlay* overlayEntry, u16 arg1);
void Actor_get_overlay_area(struct ActorOverlay* overlayEntry, const struct struct_801161E8_jp* arg1, size_t overlaySize);
// void func_80057940_jp();
s32 func_80057A8C_jp(s32* arg0, ActorProfile* profile, struct ActorOverlay* overlayEntry, struct PlayState* play, u16 arg4);
s32 func_80057B70_jp(s32* arg0, ActorProfile* profile, struct ActorOverlay* overlayEntry, struct PlayState* play, u16 arg4);
UNK_RET Actor_data_bank_regist_check(s32* arg0, ActorProfile* profile, struct ActorOverlay* overlayEntry, struct PlayState* play, u16 arg4);
// void Actor_malloc_actor_class();
void Actor_init_actor_class(Actor* actor, ActorProfile* profile, struct ActorOverlay* overlayEntry, struct PlayState* play, s32 arg4, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s32 argB, s32 argC, s32 argD, s32 argE, s32 params);
Actor* Actor_info_make_actor(ActorInfo* actorInfo, struct PlayState* play, s16 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, s16 arg7, s16 arg8, s8 arg9, s8 argA, s16 argB, u16 argC, s16 argD, s8 argE, s32 argF);
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
