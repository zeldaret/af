#ifndef M_ACTOR_H
#define M_ACTOR_H

#include "ultra64.h"
#include "m_collision_obj.h"
#include "z64math.h"
#include "unk.h"

struct Actor;
struct PlayState;
struct ActorEntry;
struct ActorOverlay;
struct struct_801161E8_jp;
struct Lights;
struct GraphicsContext;

typedef enum AllocType {
    /* 0 */ ALLOCTYPE_NORMAL,
    /* 1 */ ALLOCTYPE_ABSOLUTE,
    /* 2 */ ALLOCTYPE_PERMANENT
} AllocType;

typedef enum ActorPart {
    /* 0 */ ACTOR_PART_0,
    /* 1 */ ACTOR_PART_1,
    /* 2 */ ACTOR_PART_PLAYER,
    /* 3 */ ACTOR_PART_NPC,
    /* 4 */ ACTOR_PART_4,
    /* 5 */ ACTOR_PART_5,
    /* 6 */ ACTOR_PART_6,
    /* 7 */ ACTOR_PART_7,
    /* 8 */ ACTOR_PART_MAX
} ActorPart;

typedef enum ActorFootIndex {
    /* 0 */ FOOT_LEFT,
    /* 1 */ FOOT_RIGHT,
    /* 2 */ FOOT_MAX
} ActorFootIndex;

// TODO: figure out if those values make sense as an enum or if they should be changed to defines
typedef enum FgNameF000 {
    /* 0x0 */ FGNAME_F000_0 = 0x0,
    /* 0x5 */ FGNAME_F000_5 = 0x5,
    /* 0x8 */ FGNAME_F000_8 = 0x8,
    /* 0xD */ FGNAME_F000_D = 0xD,
    /* 0xE */ FGNAME_F000_E
} FgNameF000;

typedef void (*ActorFunc)(struct Actor* this, struct PlayState* play);

// a.k.a. ActorInit
typedef struct ActorProfile {
    /* 0x00 */ s16 name;
    /* 0x02 */ u8 part;
    /* 0x04 */ u32 flags;
    /* 0x08 */ s16 objectId;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ size_t instanceSize;
    /* 0x10 */ ActorFunc ct;
    /* 0x14 */ ActorFunc dt;
    /* 0x18 */ ActorFunc update;
    /* 0x1C */ ActorFunc draw;
    /* 0x20 */ ActorFunc save;
} ActorProfile; // size = 0x24

typedef struct PosRot {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3s rot;
} PosRot; // size = 0x14

typedef void (*Shape_Info_unk_0C)(struct Actor*, struct Lights*, struct PlayState*);

typedef struct Shape_Info {
    /* 0x00 */ Vec3s rot;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Shape_Info_unk_0C unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ Vec3f* unk_24; // maybe PosRot*
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s8 unk_2C;
    /* 0x2D */ s8 unk_2D;
    /* 0x2E */ s8 unk_2E;
    /* 0x2F */ UNK_TYPE1 unk_2F[0x1];
    /* 0x30 */ Vec3f feetPos[FOOT_MAX];
} Shape_Info; // size = 0x48

typedef struct Actor {
    /* 0x000 */ s16 name;   // id
    /* 0x002 */ u8 part;    // category
    /* 0x003 */ u8 unk_003; // If set to 1 then fgdata will be restored independently of the actor's part
    /* 0x004 */ u16 unk_004;
    /* 0x006 */ u16 fgName;
    /* 0x008 */ s8 unk_008;
    /* 0x008 */ s8 unk_009;
    /* 0x008 */ s16 unk_00A;
    /* 0x00C */ PosRot home;
    /* 0x020 */ u32 flags;
    /* 0x024 */ s16 params;
    /* 0x026 */ s16 unk_026; // objBankIndex
    /* 0x028 */ PosRot world;
    /* 0x03C */ Vec3f prevPos;
    /* 0x048 */ PosRot eye; // focus
    /* 0x05C */ Vec3f scale;
    /* 0x068 */ Vec3f velocity;
    /* 0x074 */ f32 speed;
    /* 0x078 */ f32 gravity;
    /* 0x07C */ f32 terminalVelocity;
    /* 0x080 */ UNK_TYPE1 unk_080[0x34];
    /* 0x0B4 */ UNK_TYPE1 unk_0B4[0x1];
    /* 0x0B5 */ u8 isDrawn;
    /* 0x0B6 */ s16 yawTowardsPlayer;
    /* 0x0B8 */ f32 xyzDistToPlayerSq;
    /* 0x0BC */ f32 xzDistToPlayer;
    /* 0x0C0 */ f32 playerHeightRel;
    /* 0x0C4 */ CollisionCheck_Status colStatus; // made-up name
    /* 0x0DC */ Shape_Info shape;
    /* 0x124 */ Vec3f projectedPos;
    /* 0x130 */ f32 projectedW;
    /* 0x134 */ f32 uncullZoneScale;
    /* 0x138 */ f32 uncullZoneDownward;
    /* 0x13C */ f32 unk_13C;
    /* 0x140 */ f32 unk_140;
    /* 0x144 */ f32 unk_144;
    /* 0x148 */ u8 unk_148;
    /* 0x149 */ u8 unk_149;
    /* 0x14A */ UNK_TYPE1 unk_14A[0x2];
    /* 0x14C */ struct Actor* parent;
    /* 0x150 */ struct Actor* child;
    /* 0x154 */ struct Actor* prev;
    /* 0x158 */ struct Actor* next;
    /* 0x15C */ ActorFunc ct;
    /* 0x160 */ ActorFunc dt;
    /* 0x164 */ ActorFunc update;
    /* 0x168 */ ActorFunc draw;
    /* 0x16C */ ActorFunc save;
    /* 0x170 */ struct ActorOverlay* overlayEntry;
} Actor; // size = 0x174

typedef struct Part_Break_unk_00 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x40];
} Part_Break_unk_00; // size = 0x40

typedef struct Part_Break {
    /* 0x00 */ Part_Break_unk_00* unk_00;
    /* 0x04 */ u16* unk_04;
    /* 0x08 */ UNK_TYPE1 unk_08[0x4];
    /* 0x0C */ s32* unk_0C;
    /* 0x10 */ s32 unk_10;
} Part_Break; // size >= 0x14

typedef struct ActorListEntry {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ Actor* head;
} ActorListEntry; // size = 0x8

// a.k.a. ActorContext
typedef struct ActorInfo {
    /* 0x00 */ s32 unk_00;
    /* 0x00 */ ActorListEntry actorLists[ACTOR_PART_MAX];
} ActorInfo; // size = 0x44

// 
#define ACTOR_FLAG_1             (1 << 0)
// 
#define ACTOR_FLAG_2             (1 << 1)
// 
#define ACTOR_FLAG_4             (1 << 2)
// 
#define ACTOR_FLAG_8             (1 << 3)
// 
#define ACTOR_FLAG_10            (1 << 4)
// 
#define ACTOR_FLAG_20            (1 << 5)
// 
#define ACTOR_FLAG_40            (1 << 6)
// 
#define ACTOR_FLAG_80            (1 << 7)
// 
#define ACTOR_FLAG_100           (1 << 8)
// 
#define ACTOR_FLAG_200           (1 << 9)
// 
#define ACTOR_FLAG_400           (1 << 10)
// 
#define ACTOR_FLAG_800           (1 << 11)
// 
#define ACTOR_FLAG_1000          (1 << 12)
// 
#define ACTOR_FLAG_2000          (1 << 13)
// 
#define ACTOR_FLAG_4000          (1 << 14)
// 
#define ACTOR_FLAG_8000          (1 << 15)
// 
#define ACTOR_FLAG_10000         (1 << 16)
// 
#define ACTOR_FLAG_20000         (1 << 17)
// 
#define ACTOR_FLAG_40000         (1 << 18)
// 
#define ACTOR_FLAG_80000         (1 << 19)
// 
#define ACTOR_FLAG_100000        (1 << 20)
// 
#define ACTOR_FLAG_200000        (1 << 21)
// 
#define ACTOR_FLAG_400000        (1 << 22)
// 
#define ACTOR_FLAG_800000        (1 << 23)
// 
#define ACTOR_FLAG_1000000       (1 << 24)
// 
#define ACTOR_FLAG_2000000       (1 << 25)
// 
#define ACTOR_FLAG_4000000       (1 << 26)
// 
#define ACTOR_FLAG_8000000       (1 << 27)
// 
#define ACTOR_FLAG_10000000      (1 << 28)
// 
#define ACTOR_FLAG_20000000      (1 << 29)
// 
#define ACTOR_FLAG_40000000      (1 << 30)
// 
#define ACTOR_FLAG_80000000      (1 << 31)

#define ACTOR_FGNAME_GET_F000(fgName) (((fgName) & 0xF000) >> 12)

void func_80056380_jp(void* arg0, void* arg1);
void projection_pos_set(struct PlayState* play, Vec3f* worldPos, Vec3f* projectedPos, f32* invW);
void Actor_world_to_eye(Actor* actor, f32 arg1);
void Actor_position_move(Actor* actor);
void Actor_position_speed_set(Actor* actor);
void Actor_position_moveF(Actor* actor);
s32 Actor_player_look_direction_check(Actor* actor, s16 maxAngleDiff, struct PlayState* play);
void Actor_display_position_set(struct PlayState* play, Actor* actor, s16* x, s16* y);
s32 Actor_data_bank_dma_end_check(Actor* actor, struct PlayState* play);
void Shape_Info_init(Actor* actor, f32 arg1, Shape_Info_unk_0C arg2, f32 arg3, f32 arg4);
void Actor_foot_shadow_pos_set(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex, Vec3f* rightFootPos);
void Actor_delete(Actor* actor);
void Actor_ct(Actor* actor, struct PlayState* play);
void Actor_dt(Actor* actor, struct PlayState* play);
void Actor_draw(struct PlayState* play, Actor* actor);
s32 Actor_draw_actor_no_culling_check(Actor* actor);
s32 Actor_draw_actor_no_culling_check2(Actor* actor, Vec3f* arg1, f32 arg2);
void Actor_cull_check(Actor* actor);
void Actor_delete_check(Actor* actor, struct PlayState* play);
void Actor_info_ct(struct PlayState* play2, ActorInfo* actorInfo, struct ActorEntry* actorEntry);
void Actor_info_dt(ActorInfo* actorInfo, struct PlayState* play);
void Actor_info_call_actor(struct PlayState* play, ActorInfo* actorInfo);
void Actor_info_draw_actor(struct PlayState* play, ActorInfo* actorInfo);
void Actor_info_part_new(ActorInfo* actorInfo, Actor* actor, u8 category);
Actor* Actor_info_part_delete(ActorInfo* actorInfo, Actor* actor);
void Actor_free_overlay_area(struct ActorOverlay* overlayEntry);
void actor_free_check(struct ActorOverlay* overlayEntry, u16 fgName);
void Actor_get_overlay_area(struct ActorOverlay* overlayEntry, const struct struct_801161E8_jp* arg1, size_t overlaySize);
s32 func_80057940_jp(ActorProfile** profileP, struct ActorOverlay* overlayEntry, const struct struct_801161E8_jp* arg2, size_t overlaySize, u16 arg4);
s32 func_80057A8C_jp(s32* arg0, ActorProfile* profile, struct ActorOverlay* overlayEntry, struct PlayState* play, u16 fgName);
s32 func_80057B70_jp(s32* arg0, ActorProfile* profile, struct ActorOverlay* overlayEntry, struct PlayState* play, u16 fgName);
UNK_RET Actor_data_bank_regist_check(s32* arg0, ActorProfile* profile, struct ActorOverlay* overlayEntry, struct PlayState* play, u16 arg4);
s32 Actor_malloc_actor_class(Actor** actorP, ActorProfile* profile, struct ActorOverlay* overlayEntry, const struct struct_801161E8_jp* arg3, u16 fgName);
void Actor_init_actor_class(Actor* actor, ActorProfile* profile, struct ActorOverlay* overlayEntry, struct PlayState* play, s32 arg4, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s8 argB, s8 argC, s16 argD, u16 fgName, s16 params);
Actor* Actor_info_make_actor(ActorInfo* actorInfo, struct PlayState* play, s16 actorId, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s8 arg9, s8 argA, s16 argB, u16 fgName, s16 params, s8 argE, s32 argF);
Actor* Actor_info_make_child_actor(ActorInfo* actorInfo, Actor* arg1, struct PlayState* play, s16 actorId, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 argA, u16 fgName, s16 params, s32 argD);
void restore_fgdata(Actor* actor, struct PlayState* play);
void restore_fgdata_one(Actor* actor, struct PlayState* play);
void restore_fgdata_all(struct PlayState* play);
void Actor_info_save_actor(struct PlayState* play);
Actor* Actor_info_delete(ActorInfo* actorInfo, Actor* actor, struct PlayState* play);
Actor* Actor_info_name_search_sub(Actor* actor, s16 name);
Actor* Actor_info_name_search(ActorInfo* actorInfo, s16 name, ActorPart part);
Actor* Actor_info_fgName_search_sub(Actor* actor, u16 fgName);
Actor* Actor_info_fgName_search(ActorInfo* actorInfo, u16 fgName, ActorPart part);
void Part_Break_init(Part_Break* partBreak, s32 arg1, UNK_TYPE arg2);
Gfx* HiliteReflect_new(Vec3f* object, Vec3f* eye, Vec3f* lightDir, struct GraphicsContext* gfxCtx, Gfx* gfx, Hilite** hilite);
Hilite* HiliteReflect_init(Vec3f* object, Vec3f* eye, Vec3f* lightDir, struct GraphicsContext* gfxCtx);
Hilite* HiliteReflect_xlu_init(Vec3f* object, Vec3f* eye, Vec3f* lightDir, struct GraphicsContext* gfxCtx);
Hilite* HiliteReflect_light_init(Vec3f* object, Vec3f* eye, Vec3f* lightDir, struct GraphicsContext* gfxCtx);
Hilite* Setpos_HiliteReflect_init(Vec3f* object, struct PlayState* play);
Hilite* Setpos_HiliteReflect_xlu_init(Vec3f* object, struct PlayState* play);
Hilite* Setpos_HiliteReflect_light_init(Vec3f* object, struct PlayState* play);

#endif
