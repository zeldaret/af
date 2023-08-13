#include "m_actor.h"
#include "m_actor_dlftbls.h"
#include "m_collision_bg.h"
#include "m_collision_obj.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_field_info.h"
#include "m_lights.h"
#include "m_malloc.h"
#include "m_lib.h"
#include "m_skin_matrix.h"
#include "m_player_lib.h"
#include "m_npc.h"
#include "m_scene.h"
#include "libc/math.h"
#include "fault.h"
#include "sys_matrix.h"
#include "ovlmgr.h"
#include "gfx.h"
#include "6A0DE0.h"
#include "6E9650.h"
#include "unknown_structs.h"
#include "code_variables.h"
#include "macros.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/ovl_player_actor/m_player.h"

#if 0
? CollisionCheck_Status_Clear(void*);               /* extern */
? CollisionCheck_Status_ct(f32, void*);             /* extern */
? FaultDrawer_Printf(?*, void*, ?*);                /* extern */
? FaultDrawer_SetCursor(?, ?);                      /* extern */
? Fault_AddClient(?*, void (*)(void*, ?), void*, ?*); /* extern */
? Fault_RemoveClient(?*);                           /* extern */
s32 Global_light_read(void*, struct GraphicsContext*); /* extern */
? Light_list_point_draw(PlayState*);                /* extern */
? LightsN_disp(s32, struct GraphicsContext*);       /* extern */
? Matrix_Position(s32, s32);                        /* extern */
? Matrix_copy_MtxF(s8*, ?*);                        /* extern */
? Matrix_scale(f32, f32, s32, ?);                   /* extern */
? Matrix_softcv3_load(f32, f32, s32, void*);        /* extern */
? Skin_Matrix_PrjMulVector(s8*, s32, s32, s32);     /* extern */
? actor_dlftbls_cleanup();                          /* extern */
? actor_dlftbls_init();                             /* extern */
? chase_f(void*, s32, s32, void*);                  /* extern */
f32 cos_s(s16);                                     /* extern */
s32 func_8008B3E8_jp(?*, ?);                        /* extern */
? func_8008E5F4_jp(s32, f32, s32);                  /* extern */
? func_8009B884_jp(s32, s32, void*);                /* extern */
? func_800C6144_jp(void*, s16);                     /* extern */
void* get_player_actor_withoutCheck(PlayState*);    /* extern */
f32 mCoBG_GetBgY_OnlyCenter_FromWpos2(s32, s32, s32, f32); /* extern */
s32 mEv_CheckFirstJob();                            /* extern */
? mFI_SetBearActor(PlayState*, s32, s32, s32, s32); /* extern */
? mFI_SetFG_common(u16, s32, s32, s32, s32);        /* extern */
? mNpc_SetNpcinfo(void*, s8);                       /* extern */
s32 mSc_bank_regist_check(void*, s16);              /* extern */
? mSc_regist_initial_exchange_bank(PlayState*);     /* extern */
? mem_clear(void*, s32, ?);                         /* extern */
? ovlmgr_Load(s32, s32, s32, s32, s32);             /* extern */
s16 search_position_angleY(void*, void*);           /* extern */
f32 search_position_distanceXZ(void*, void*);       /* extern */
f32 sin_s(s16, void*);                              /* extern */
? xyz_t_move(?*, void*);                            /* extern */
? zelda_free(void*, void*);                         /* extern */
void* zelda_malloc(s32, void*);                     /* extern */
void* zelda_malloc_r(s32, void*);                   /* extern */
void Actor_ct(void* arg0, PlayState* arg1);         /* static */
void Actor_cull_check(void* arg0);                  /* static */
s32 Actor_data_bank_dma_end_check(void* arg0, PlayState* arg1); /* static */
s32 Actor_data_bank_regist_check(s32* arg0, void* arg1, u16 arg4, PlayState*, s32); /* static */
void Actor_delete(void* arg0);                      /* static */
void Actor_delete_check(void* arg0, PlayState* arg1); /* static */
void Actor_display_position_set(s32 arg1, s16* arg2, s16* arg3); /* static */
void Actor_draw(PlayState* arg0, void* arg1);       /* static */
s32 Actor_draw_actor_no_culling_check(void* arg0);  /* static */
? Actor_draw_actor_no_culling_check2(void* arg0, void* arg1, f32 arg2); /* static */
void Actor_dt(void* arg0, PlayState* arg1);         /* static */
void Actor_foot_shadow_pos_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* static */
void Actor_free_overlay_area(s32 arg0);             /* static */
void Actor_get_overlay_area(void* arg0, ?* arg1, s32 arg2, u16); /* static */
void* Actor_info_delete(s8* arg0, void* arg1, PlayState* arg2); /* static */
void* Actor_info_fgName_search(s32 arg0, s32 arg1, s32 arg2); /* static */
void* Actor_info_fgName_search_sub(void* arg0, s32 arg1, void*); /* static */
void* Actor_info_make_actor(ActorInfo* arg0, PlayState* arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, s32 argE, s32 argF); /* static */
void* Actor_info_make_child_actor(void* arg1, ActorInfo* arg2, s16 arg3, s32 arg4, f32 arg5, f32 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, u16 argB, s16 argC, s32 argD); /* static */
void* Actor_info_name_search(s32 arg0, s16 arg1, s32 arg2); /* static */
void* Actor_info_name_search_sub(void* arg0, s16 arg1, void*); /* static */
void* Actor_info_part_delete(s8* arg0, void* arg1); /* static */
void Actor_info_part_new(ActorInfo* arg0, void* arg1, u8 arg2); /* static */
void Actor_info_save_actor(s32 arg0);               /* static */
void Actor_init_actor_class(void* arg0, void* arg1, void* arg2, PlayState* arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, s32 argE, s32 argF); /* static */
s32 Actor_malloc_actor_class(void** arg0, void* arg1, void* arg2, ?* arg3, s32 arg4); /* static */
s32 Actor_player_look_direction_check(void* arg0, s16 arg1, PlayState* arg2); /* static */
void Actor_position_move(void* arg0);               /* static */
void Actor_position_moveF(void* arg0);              /* static */
void Actor_position_speed_set(void* arg0);          /* static */
void Actor_world_to_eye(void* arg0, f32 arg1, void*); /* static */
f32 HiliteReflect_init(void* arg3, f32*, s32);      /* static */
f32 HiliteReflect_light_init(void* arg3);           /* static */
void* HiliteReflect_new(void* arg0, f32* arg1, void* arg2, void* arg3, void* arg4, LookAt** arg5); /* static */
f32 HiliteReflect_xlu_init(void* arg3, f32*, s32);  /* static */
void Part_Break_init(void* arg0, s32 arg1, ? arg2); /* static */
void Setpos_HiliteReflect_init(void* arg1);         /* static */
void Setpos_HiliteReflect_light_init(void* arg1);   /* static */
void Setpos_HiliteReflect_xlu_init(void* arg1);     /* static */
void Shape_Info_init(void* arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4); /* static */
void actor_free_check(void* arg0, u16 arg1);        /* static */
void func_80056380_jp(void* arg0, ? arg1);          /* static */
s32 func_80057940_jp(void** arg0, void* arg1, ?* arg2, s32 arg3, s32 arg4); /* static */
s32 func_80057A8C_jp(s32* arg0, ? arg1, void* arg2, s32 arg3, u16 arg4); /* static */
s32 func_80057B70_jp(s32* arg0, void* arg1, void* arg2, s32 arg3, u16 arg4); /* static */
void projection_pos_set(s32 arg0, f32* arg3, f32*); /* static */
void restore_fgdata(void* arg0, s32 arg1);          /* static */
void restore_fgdata_all(s32 arg0);                  /* static */
void restore_fgdata_one(void* arg0, PlayState*);    /* static */
extern Mtx B_8011B850_jp;
extern ? gSegments;
extern s32 restore_flag;
extern ? actor_dlftbls;
extern ? common_data;
extern void* debug_mode;
static ? RO_801161E8_jp;                            /* unable to generate initializer; const */
#endif

extern s32 restore_flag[ACTORCAT_MAX];
extern MtxF MtxF_clear;

extern const struct_801161E8_jp RO_801161E8_jp;

// UNK_RET func_80057940_jp(ActorProfile** profileP, ActorOverlay* overlayEntry, const struct_801161E8_jp* arg2, s32 arg3, s32 arg4);

void func_80056380_jp(void* arg0, void* arg1 UNUSED) {
    Actor* actor = arg0;
    const char* name;

    if ((actor == NULL) || (actor->overlayEntry == NULL)) {
        //! @bug this will be overriden by the next printf
        FaultDrawer_SetCursor(0x30, 0x18);
        FaultDrawer_Printf("ACTOR NAME is NULL");
    }

    FaultDrawer_SetCursor(0x30, 0x18);
    name = "";
    FaultDrawer_Printf("ACTOR NAME %08x:%s", actor, name);
}

#if 0
void projection_pos_set(s32 arg0, f32* arg3) {
    f32 temp_fv0;

    Skin_Matrix_PrjMulVector(arg0 + 0x1E1C);
    temp_fv0 = *arg3;
    if (temp_fv0 < 1.0f) {
        *arg3 = 1.0f;
        return;
    }
    *arg3 = 1.0f / temp_fv0;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/projection_pos_set.s")
#endif

void Actor_world_to_eye(Actor* actor, f32 arg1) {
    actor->eye.pos.x = actor->world.pos.x;
    actor->eye.pos.y = actor->world.pos.y + arg1;
    actor->eye.pos.z = actor->world.pos.z;
    actor->eye.rot.x = actor->world.rot.x;
    actor->eye.rot.y = actor->world.rot.y;
    actor->eye.rot.z = actor->world.rot.z;
}

void Actor_position_move(Actor* actor) {
    Kankyo* kankyo = &((PlayState *)gamePT)->kankyo;
    f32 speedRate;

    speedRate = game_GameFrame_2F;

    kankyo->unk_C0(actor);

    actor->world.pos.x += actor->unk_068 * speedRate + actor->unk_0C4.unk_00;
    actor->world.pos.y += actor->unk_06C * speedRate + actor->unk_0C4.unk_04;
    actor->world.pos.z += actor->unk_070 * speedRate + actor->unk_0C4.unk_08;
}

void Actor_position_speed_set(Actor* actor) {
    actor->unk_068 = sin_s(actor->world.rot.y) * actor->unk_074;
    actor->unk_070 = cos_s(actor->world.rot.y) * actor->unk_074;
    chase_f(&actor->unk_06C, actor->unk_07C, actor->unk_078);
}

void Actor_position_moveF(Actor* actor) {
    Actor_position_speed_set(actor);
    Actor_position_move(actor);
}

s32 Actor_player_look_direction_check(Actor* actor, s16 maxAngleDiff, PlayState* play) {
    s16 yawDiff = BINANG_ROT180(actor->unk_0B6) - get_player_actor_withoutCheck(play)->actor.unk_0DC.y;

    return ABS(yawDiff) < maxAngleDiff;
}

#if 0
void Actor_display_position_set(s32 arg1, s16* arg2, s16* arg3) {
    f32 sp1C;
    f32 sp18;

    projection_pos_set(arg1 + 0x28, &sp1C, &sp18);
    *arg2 = (s16) (s32) ((sp1C * sp18 * 160.0f) + 160.0f);
    *arg3 = (s16) (s32) ((sp20 * sp18 * -120.0f) + 120.0f);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_display_position_set.s")
#endif

s32 Actor_data_bank_dma_end_check(Actor* actor, PlayState* play) {
    s32 var_v1;

    switch ((actor->fgName & 0xF000) >> 0xC) {
        case 0xD:
        case 0xE:
            var_v1 = common_data.unk_1004C->unk_F4(play->unk_0110, actor);
            break;

        default:
            var_v1 = play->unk_0110[actor->unk_026].unk_00 > 0;
            break;
    }

    return var_v1;
}

void Shape_Info_init(Actor* actor, f32 arg1, Actor_unk_0E8 arg2, f32 arg3, f32 arg4) {
    actor->unk_0E4 = arg1;
    actor->unk_0E8 = arg2;
    actor->unk_0EC = arg3;
    actor->unk_0F0 = arg4;
    actor->unk_108 = 1;
    actor->unk_0FC = 0;
    actor->unk_0F4 = 1.0f;
    actor->unk_0F8 = 1.0f;
    actor->unk_10A = 0;
    actor->unk_100 = &actor->world.pos;
    actor->unk_104 = -1;
    actor->unk_109 = 0;
}

void Actor_foot_shadow_pos_set(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex, Vec3f* rightFootPos) {
    if (limbIndex == leftFootIndex) {
        Matrix_Position(leftFootPos, &actor->feetPos[FOOT_LEFT]);
    } else if (limbIndex == rightFootIndex) {
        Matrix_Position(rightFootPos, &actor->feetPos[FOOT_RIGHT]);
    }
}

void Actor_delete(Actor* actor) {
    if (actor != NULL) {
        actor->update = NULL;
        actor->draw = NULL;
    }
}

void Actor_ct(Actor* actor, PlayState* play) {
    s32 pad[2] UNUSED;
    PlayState_unk_0110* temp;
    Npc* npc;
    CommonData_unk_1004C_unk_14_arg0 sp34;
    PlayState_unk_0110* temp_a0;

    temp_a0 = play->unk_0110;

    temp = temp_a0;
    temp += actor->unk_026;
    temp->unk_50++;

    if (actor->category == ACTORCAT_NPC) {
        npc = (Npc*)actor;

        common_data.unk_1004C->unk_14(&sp34, npc->actor.fgName);
        npc->unk_708 = mSc_bank_regist_check(temp_a0, sp34.unk_02);
        temp_a0[npc->unk_708].unk_50++;
    }

    actor->world = actor->home;
    actor->unk_0DC = actor->world.rot;

    Actor_world_to_eye(actor, 0.0f);
    xyz_t_move(&actor->unk_03C, &actor->world.pos);

    actor->unk_05C.x = 0.01f;
    actor->unk_05C.y = 0.01f;
    actor->unk_05C.z = 0.01f;

    actor->unk_07C = -20.0f;
    actor->unk_0B8 = FLT_MAX;

    actor->unk_134 = 350.0f;
    actor->unk_138 = 700.0f;

    actor->unk_0F4 = 1.0f;
    actor->unk_0F8 = 1.0f;

    actor->unk_13C = 1000.0f;
    actor->unk_140 = 350.0f;
    actor->unk_144 = 55.0f;

    CollisionCheck_Status_ct(&actor->unk_0C4);
    Shape_Info_init(actor, 0.0f, NULL, 0.0f, 0.0f);

    if (Actor_data_bank_dma_end_check(actor, play) == 1) {
        gSegments[6] = (uintptr_t)OS_PHYSICAL_TO_K0(temp_a0[actor->unk_026].unk_04);
        actor->init(actor, play);
        actor->init = NULL;
    }
}

#ifdef NON_EQUIVALENT
void Actor_dt(Actor* actor, PlayState* play) {
    if (actor->unk_16C != NULL) {
        actor->unk_16C(actor, play);
        actor->unk_16C = NULL;
    }

    if (actor->destroy != NULL) {
        actor->destroy(actor, play);
        actor->destroy = NULL;
    }

    if ((actor->unk_150 != NULL) && (actor == actor->unk_150->unk_14C)) {
        actor->unk_150->unk_14C = NULL;
    }

    if ((actor->unk_14C != NULL) && (actor == actor->unk_14C->unk_150)) {
        actor->unk_14C->unk_150 = NULL;
    }

    switch ((actor->fgName & 0xF000) >> 0xC) {
        case 0xD:
        case 0xE:
            common_data.unk_1004C->unk_F0(&play->unk_0110, actor);
            break;

        default:
            if (actor->unk_026 >= play->unk_190C) {
                PlayState_unk_0110* temp_v0_6;

                temp_v0_6 = &play->unk_0110[actor->unk_026];
                if (temp_v0_6->unk_50 > 0) {
                    actor->unk_026 = -1;
                    temp_v0_6->unk_50--;
                }
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_dt.s")
#endif

#ifdef NON_EQUIVALENT
// s32 Global_light_read(s8*, struct GraphicsContext*); /* extern */
// ? LightsN_disp(UNK_TYPE4, struct GraphicsContext*);       /* extern */
void func_8009B884_jp(UNK_TYPE4, UNK_TYPE4, Vec3f*);              /* extern */

void Actor_draw(PlayState* play, Actor* actor) {
    FaultClient sp48;
    UNK_TYPE4 temp_a0; // sp44
    s32 temp_a0_2;

    Fault_AddClient(&sp48, func_80056380_jp, actor, "Actor_draw");

    OPEN_DISPS(play->state.gfxCtx);

    temp_a0 = Global_light_read(&play->unk_1910[0x350], play->state.gfxCtx);

    func_8009B884_jp(temp_a0, play->unk_1C60, (actor->flags & 0x400000) ? NULL : &actor->world.pos);

    LightsN_disp(temp_a0, play->state.gfxCtx);
    Matrix_softcv3_load(actor->world.pos.x, actor->world.pos.y + (actor->unk_0E4 * actor->unk_05C.y), actor->world.pos.z, &actor->unk_0DC);
    Matrix_scale(actor->unk_05C.x, actor->unk_05C.y, actor->unk_05C.z, MTXMODE_APPLY);

    temp_a0_2 = play->unk_0110[actor->unk_026].unk_04;

    gSegments[6] = (uintptr_t)OS_PHYSICAL_TO_K0(temp_a0_2);

    gSPSegment(POLY_OPA_DISP++, 0x06, temp_a0_2);
    gSPSegment(POLY_XLU_DISP++, 0x06, temp_a0_2);
    gSPSegment(UNK_2C0_DISP++, 0x06, temp_a0_2);

    actor->draw(actor, play);

    if (actor->unk_0E8 != NULL) {
        actor->unk_0E8(actor, temp_a0, play);
    }

    CLOSE_DISPS(play->state.gfxCtx);

    Fault_RemoveClient(&sp48);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_draw.s")
#endif

s32 Actor_draw_actor_no_culling_check(Actor* actor) {
    return Actor_draw_actor_no_culling_check2(actor, &actor->unk_124, actor->unk_130);
}

s32 Actor_draw_actor_no_culling_check2(Actor* actor, Vec3f* arg1, f32 arg2) {
    s32 ret = 0;

    if ((-actor->unk_140 < arg1->z) && (arg1->z < (actor->unk_13C + actor->unk_140))) {
        f32 var_fa1;

        if (arg2 < 1.0f) {
            var_fa1 = 1.0f;
        } else {
            var_fa1 = 1.0f / arg2;
        }

        if (((fabsf(arg1->x) - actor->unk_134) * var_fa1) < 1.0f) {
            if (((arg1->y + actor->unk_138) * var_fa1) > -1.0f) {
                if (((arg1->y - actor->unk_140) * var_fa1) < 1.0f) {
                    ret = 1;
                }
            }
        }
    }

    return ret;
}

void Actor_cull_check(Actor* actor) {
    if (Actor_draw_actor_no_culling_check(actor) == 1) {
        actor->flags |= 0x40;
    } else {
        actor->flags &= ~0x40;
    }
}

void Actor_delete_check(Actor* actor, PlayState* play) {
    if ((actor->flags & (0x40 | 0x20 | 0x10)) || (actor->fgName == 0)) {
        return;
    }

    if ((actor->unk_008 < 0) || (actor->unk_009 < 0)) {
        return;
    }

    if ((actor->unk_008 == play->unk_00E4) && (actor->unk_009 == play->unk_00E5)) {
        return;
    }

    Actor_delete(actor);
}

void Actor_info_ct(PlayState* play2, ActorInfo* actorInfo, ActorEntry* actorEntry) {
    PlayState* play = play2;
    Actor* temp_v0;
    ActorOverlay* var_v0;
    ActorEntry* var_s0_2;
    s16* var_s0;
    s32 var_s1;

    bzero(actorInfo, sizeof(ActorInfo));

    actor_dlftbls_init();
    Matrix_copy_MtxF(&play->unk_1E5C, &MtxF_clear);
    Matrix_copy_MtxF(&play->unk_1E1C, &MtxF_clear);

    var_v0 = actor_dlftbls;
    for (var_s1 = 0; var_s1 < 0xC9; var_s1++) {
        var_v0->loadedRamAddr = NULL;
        var_v0->numLoaded = 0;
        var_v0++;
    }

    if (mEv_CheckFirstJob() == 1) {
        common_data.unk_107B6 = 0x5B;
    }

    if (common_data.unk_107B6 != 0xC9) {
        Actor_info_make_actor(actorInfo, play, common_data.unk_107B6, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1, 0, -1, -1, -1);
    }
    common_data.unk_107B6 = 0xC9;

label:

    temp_v0 = Actor_info_make_actor(actorInfo, play, actorEntry->id, actorEntry->pos.x, actorEntry->pos.y, actorEntry->pos.z, actorEntry->rot.x, actorEntry->rot.y, actorEntry->rot.z, -1, -1, -1, 0, actorEntry->params, -1, -1);
    if (temp_v0 != NULL) {
        temp_v0->world.pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(temp_v0->world.pos, 0.0f);
        mFI_SetBearActor(play, temp_v0->world.pos, 0);
    }

    if (common_data.unk_1014E != 0) {
        Actor_info_make_actor(actorInfo, play, common_data.unk_1014E, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1, 0, -1, -1, -1);
    }

    if (play->unk_1EA6 != 0) {
        var_s0 = play->unk_1EB0;

        for (var_s1 = 0; var_s1 < play->unk_1EA6; var_s1++) {
            Actor_info_make_actor(&play->actorInfo, play, *var_s0, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1, 0, -1, -1, -1);
            var_s0 += 1;
        }
        play->unk_1EA6 = 0;
    }

    mSc_regist_initial_exchange_bank(play);

    if (play->unk_1EA5 != 0) {
        var_s0_2 = play->unk_1EAC;
        for (var_s1 = 0; var_s1 < play->unk_1EA5; var_s1++) {
            Actor_info_make_actor(&play->actorInfo, play, var_s0_2->id, var_s0_2->pos.x, var_s0_2->pos.y, var_s0_2->pos.z, var_s0_2->rot.x, var_s0_2->rot.y, var_s0_2->rot.z, -1, -1, -1, 0, var_s0_2->params, -1, -1);
            var_s0_2 += 1;
        }
        play->unk_1EA5 = 0;
    }
}

void Actor_info_dt(ActorInfo* actorInfo, PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(actorInfo->actorLists); i++) {
        Actor* actor = actorInfo->actorLists[i].head;

        while (actor != NULL) {
            Actor_info_delete(actorInfo, actor, play);
            actor = actorInfo->actorLists[i].head;
        }
    }

    actor_dlftbls_cleanup();
}

#if 0
? CollisionCheck_Status_Clear(s8*);                 /* extern */
? func_8008E5F4_jp(s32, f32, s32);                  /* extern */
void* get_player_actor_withoutCheck(PlayState*);    /* extern */
s16 search_position_angleY(PosRot*, void*);         /* extern */
f32 search_position_distanceXZ(PosRot*, void*);     /* extern */
extern ? gSegments;

void Actor_info_call_actor(PlayState* arg0, void* arg1) {
    s32 sp50;
    void* sp4C;
    Actor* var_s0;
    Actor* var_v1;
    PosRot* temp_s2;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_t1;
    u32 temp_t8;
    void* temp_s3;
    void* temp_v0;

    temp_v0 = get_player_actor_withoutCheck(arg0);
    func_8008E5F4_jp(subroutine_arg0, temp_v0->unk_2C, temp_v0->unk_30);
    sp50 = 0;
    sp4C = arg1;
    do {
        var_s0 = sp4C->unk_8;
        if (var_s0 != NULL) {
            do {
                arg0->state.unk_9C[1] = 0x97;
                arg0->state.unk_9C[0] = (s8) var_s0->id;
                if (var_s0->world.pos.y < -25000.0f) {
                    var_s0->world.pos.y = -25000.0f;
                }
                if (var_s0->init != NULL) {
                    if (Actor_data_bank_dma_end_check(var_s0, arg0) == 1) {
                        gSegments.unk_18 = (void* ) (arg0->unk_0110[var_s0->unk_026].unk_04 + 0x80000000);
                        arg0->state.unk_9C[1] = 0x98;
                        var_s0->init(var_s0, arg0);
                        arg0->state.unk_9C[1] = 0x99;
                        var_s0->init = NULL;
                    }
                    goto block_18;
                }
                if (Actor_data_bank_dma_end_check(var_s0, arg0) == 0) {
                    arg0->state.unk_9C[1] = 0x9A;
                    Actor_delete(var_s0);
                    arg0->state.unk_9C[1] = 0x9B;
                    goto block_18;
                }
                temp_s2 = &var_s0->world;
                if (var_s0->update == NULL) {
                    if (var_s0->unk_0B5 == 0) {
                        arg0->state.unk_9C[1] = 0x9C;
                        var_v1 = Actor_info_delete(&arg0->actorInfo, var_s0, arg0);
                        arg0->state.unk_9C[1] = 0x9D;
                    } else {
                        arg0->state.unk_9C[1] = 0x9E;
                        Actor_dt(var_s0, arg0);
                        arg0->state.unk_9C[1] = 0x9F;
                        goto block_18;
                    }
                } else {
                    arg0->state.unk_9C[1] = 0xA0;
                    temp_s3 = temp_v0 + 0x28;
                    xyz_t_move((Vec3f* ) var_s0->unk_03C, &temp_s2->pos);
                    temp_fv0 = search_position_distanceXZ(temp_s2, temp_s3);
                    var_s0->unk_BC = temp_fv0;
                    var_s0->unk_C0 = (f32) (temp_v0->unk_2C - var_s0->world.pos.y);
                    temp_fv1 = var_s0->unk_C0;
                    var_s0->unk_B8 = (f32) ((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
                    temp_t8 = var_s0->flags & 0xFEFFFFFF;
                    var_s0->unk_B6 = search_position_angleY(temp_s2, temp_s3);
                    var_s0->flags = temp_t8;
                    if ((temp_t8 & 0x50) || (var_s0->category == 3)) {
                        gSegments.unk_18 = (void* ) (arg0->unk_0110[var_s0->unk_026].unk_04 + 0x80000000);
                        arg0->state.unk_9C[1] = 0xA1;
                        var_s0->update(var_s0, arg0);
                        arg0->state.unk_9C[1] = 0xA2;
                    }
                    CollisionCheck_Status_Clear(&var_s0->unk_0B8[0xC]);
block_18:
                    var_v1 = var_s0->unk_158;
                }
                var_s0 = var_v1;
            } while (var_v1 != NULL);
        }
        temp_t1 = sp50 + 8;
        sp4C += 8;
        sp50 = temp_t1;
    } while (temp_t1 != 0x40);
    arg0->state.unk_9C[1] = 0xA3;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_call_actor.s")
#endif

void Actor_info_draw_actor(PlayState* play, ActorInfo* actorInfo) {
    PlayState_unk_2208 temp_s4 = play->unk_2208;
    ActorListEntry* actorEntry = actorInfo->actorLists;
    ActorType cat = 0;

    if (1) {}

    for (; cat < ACTORCAT_MAX; cat++, actorEntry++) {
        Actor* actor;

        for (actor = actorEntry->head; actor != NULL; actor = actor->unk_158) {
            s32 temp;

            Skin_Matrix_PrjMulVector(&play->unk_1E1C, &actor->world.pos, &actor->unk_124, &actor->unk_130);
            Actor_cull_check(actor);

            temp = temp_s4(actor, play);
            actor->unk_0B5 = 0;

            if (temp != 0) {
                continue;
            }

            if ((actor->init != NULL) || (actor->draw == NULL)) {
                continue;
            }

            if (actor->flags & (0x40 | 0x20)) {
                if (!(actor->flags & 0x80) && (actor->unk_148 == 0) && (actor->unk_149 == 0)) {
                    Actor_draw(play, actor);
                    actor->unk_0B5 = 1;
                }
            } else {
                Actor_delete_check(actor, play);
            }
        }
    }

    if (debug_mode->r[0x380] == 0) {
        Light_list_point_draw(play);
    }
}

void Actor_info_part_new(ActorInfo* actorInfo, Actor* actor, u8 category) {
    Actor* temp_v1;

    actor->category = category;

    actorInfo->unk_00++;

    actorInfo->actorLists[category].unk_0++;
    temp_v1 = actorInfo->actorLists[category].head;
    if (temp_v1 != NULL) {
        temp_v1->unk_154 = actor;
    }

    actorInfo->actorLists[category].head = actor;
    actor->unk_158 = temp_v1;
}

Actor* Actor_info_part_delete(ActorInfo* actorInfo, Actor* actor) {
    Actor* newHead;

    actorInfo->unk_00--;

    actorInfo->actorLists[actor->category].unk_0--;

    if (actor->unk_154 != NULL) {
        actor->unk_154->unk_158 = actor->unk_158;
    } else {
        actorInfo->actorLists[actor->category].head = actor->unk_158;
    }

    newHead = actor->unk_158;
    if (newHead != NULL) {
        newHead->unk_154 = actor->unk_154;
    }

    actor->unk_154 = NULL;
    actor->unk_158 = NULL;

    return newHead;
}

void Actor_free_overlay_area(ActorOverlay* overlayEntry) {
    if (!(overlayEntry->allocType & ALLOCTYPE_PERMANENT)) {
        if (overlayEntry->allocType & ALLOCTYPE_ABSOLUTE) {
            overlayEntry->loadedRamAddr = NULL;
        } else {
            zelda_free(overlayEntry->loadedRamAddr);
            overlayEntry->loadedRamAddr = NULL;
        }
    }
}

void actor_free_check(ActorOverlay* overlayEntry, u16 fgName) {
    if ((overlayEntry->numLoaded == 0) && (overlayEntry->loadedRamAddr != NULL)) {
        switch ((fgName & 0xF000) >> 0xC) {
            case 0xD:
            case 0xE:
                common_data.unk_1004C->unk_08();
                break;

            case 0x5:
                common_data.unk_10098->unk_08();
                break;

            default:
                Actor_free_overlay_area(overlayEntry);
                break;
        }
    }
}

void Actor_get_overlay_area(ActorOverlay* overlayEntry, const struct_801161E8_jp* arg1 UNUSED, size_t overlaySize) {
    if (overlayEntry->allocType & ALLOCTYPE_PERMANENT) {
        overlayEntry->loadedRamAddr = zelda_malloc_r(overlaySize);
    } else {
        overlayEntry->loadedRamAddr = zelda_malloc(overlaySize);
    }
}

s32 func_80057940_jp(ActorProfile** profileP, ActorOverlay* overlayEntry, const struct_801161E8_jp* arg2, size_t overlaySize, u16 arg4) {
    if (overlayEntry->vramStart == NULL) {
        *profileP = overlayEntry->profile;
    } else {
        if (overlayEntry->loadedRamAddr == NULL) {
            switch ((arg4 & 0xF000) >> 0xC) {
                case 0xD:
                case 0xE:
                    if (common_data.unk_1004C != NULL) {
                        common_data.unk_1004C->unk_04(overlayEntry, arg2, overlaySize, arg4);
                    } else {
                        overlayEntry->loadedRamAddr = NULL;
                    }
                    break;

                case 5:
                    if (common_data.unk_10098 != NULL) {
                        common_data.unk_10098->unk_4(overlayEntry, overlaySize);
                    }
                    break;

                default:
                    Actor_get_overlay_area(overlayEntry, arg2, overlaySize);
                    break;
            }

            if (overlayEntry->loadedRamAddr == NULL) {
                return 0;
            }

            ovlmgr_Load((void* ) overlayEntry->vromStart, (s32) overlayEntry->vromEnd, overlayEntry->vramStart, overlayEntry->vramEnd, overlayEntry->loadedRamAddr);
            overlayEntry->numLoaded = 0;
        }

        *profileP = (void*)(uintptr_t) ( (overlayEntry->profile != NULL) ? (void*) ((uintptr_t)overlayEntry->profile - (intptr_t)((uintptr_t)overlayEntry->vramStart - (uintptr_t)overlayEntry->loadedRamAddr)) : NULL );
    }

    return 1;
}

// this function may be Actor_data_bank_regist_check_npc
#if 0
s32 func_80057A8C_jp(s32* arg0, ActorProfile* profile, ActorOverlay* overlayEntry, PlayState* play, u16 arg4) {
    s16 sp92;
    s16 sp90;
    s32 sp88;
    CommonData_unk_1004C_unk_14_arg0 sp24;
    PlayState_unk_0110* sp20;
    PlayState_unk_0110* temp_a0;
    s32 temp_v0;
    s32 temp_v1;

    sp88 = 1;
    common_data.unk_1004C->unk_14(&sp24, arg4);
    sp92 = (s16) sp24;
    sp90 = sp24.unk_02;
    temp_a0 = play->unk_0110;
    sp20 = temp_a0;
    *arg0 = mSc_bank_regist_check(temp_a0, (s16) sp24);
    temp_v0 = mSc_bank_regist_check(temp_a0, sp90);
    temp_v1 = *arg0;
    if ((temp_v1 < 0) || (temp_v0 < 0)) {
        if (temp_v1 >= 0) {
            sp92 = 0;
        }
        if (temp_v0 >= 0) {
            sp90 = 0;
        }
        common_data.unk_1004C->unk_EC(sp20, sp92, sp90);
        actor_free_check(overlayEntry, arg4);
        sp88 = 0;
    }
    return sp88;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/func_80057A8C_jp.s")
#endif

s32 func_80057B70_jp(s32* arg0, ActorProfile* profile, ActorOverlay* overlayEntry, PlayState* play, u16 fgName) {
    s32 pad UNUSED;
    s32 ret = 1;

    *arg0 = mSc_bank_regist_check(play->unk_0110, profile->unk_0A);

    if (*arg0 == -1) {
        func_800C6144_jp(play->unk_0110, profile->unk_0A);
        actor_free_check(overlayEntry, fgName);
        ret = 0;
    }

    return ret;
}

s32 Actor_data_bank_regist_check(s32* arg0, ActorProfile* profile, ActorOverlay* overlayEntry, PlayState* play, u16 fgName) {
    s32 var_v1 = 1;

    if (*arg0 == -1) {
        if (profile->type == ACTORCAT_NPC) {
            var_v1 = func_80057A8C_jp(arg0, profile, overlayEntry, play, fgName);
        } else {
            var_v1 = func_80057B70_jp(arg0, profile, overlayEntry, play, fgName);
        }
    }
    return var_v1;
}

s32 Actor_malloc_actor_class(Actor** actorP, ActorProfile* profile, ActorOverlay* overlayEntry, const struct_801161E8_jp* arg3, u16 fgName) {
    CommonData_unk_1004C_unk_14_arg0 sp24;

    switch ((fgName & 0xF000) >> 0xC) {
        case 0xD:
        case 0xE:
            *actorP = common_data.unk_1004C->unk_0C(profile->instanceSize, arg3, 1);

            //! FAKE
            if ((profile != NULL) && (profile != NULL) && (profile != NULL)) {}

            common_data.unk_1004C->unk_14(&sp24, fgName);
            break;

        case 0x5:
            *actorP = common_data.unk_10098->unk_0C();
            break;

        default:
            *actorP = zelda_malloc(profile->instanceSize);
            break;
    }

    if (*actorP == NULL) {
        actor_free_check(overlayEntry, fgName);
        return 0;
    }
    return 1;
}

void Actor_init_actor_class(Actor* actor, ActorProfile* profile, ActorOverlay* overlayEntry, PlayState* play, s32 arg4, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s8 argB, s8 argC, s16 argD, u16 fgName, s16 params) {
    mem_clear(actor, profile->instanceSize, 0);

    actor->overlayEntry = overlayEntry;

    actor->id = profile->id;
    actor->flags = profile->flags;

    actor->unk_026 = arg4;

    actor->init = profile->init;
    actor->destroy = profile->destroy;
    actor->update = profile->update;
    actor->draw = profile->draw;
    actor->unk_16C = profile->unk_20;

    actor->params = params;

    actor->unk_004 = play->unk_00E0;

    actor->home.pos.x = x;
    actor->home.pos.y = y;
    actor->home.pos.z = z;
    actor->home.rot.x = rotX;
    actor->home.rot.y = rotY;
    actor->home.rot.z = rotZ;

    actor->unk_008 = argB;
    actor->unk_009 = argC;
    actor->unk_00A = argD;
    actor->fgName = fgName;
}

Actor* Actor_info_make_actor(ActorInfo* actorInfo, PlayState* play, s16 actorId, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s8 arg9, s8 argA, s16 argB, u16 fgName, s16 params, s8 argE, s32 argF) {
    u16 *new_var = &fgName;
    Actor* sp68;
    ActorProfile* profile;
    ActorOverlay* temp_s0 = &actor_dlftbls[actorId];
    size_t size = (uintptr_t)temp_s0->vramEnd - (uintptr_t)temp_s0->vramStart;

    if (actorInfo->unk_00 >= 0xC9) {
        return NULL;
    }

    if (func_80057940_jp(&profile, temp_s0, &RO_801161E8_jp, size, *new_var) == 0) {
        return NULL;
    }
    if (Actor_data_bank_regist_check(&argF, profile, temp_s0, play, fgName) == 0) {
        return NULL;
    }
    if (Actor_malloc_actor_class(&sp68, profile, temp_s0, &RO_801161E8_jp,  fgName) == 0) {
        return NULL;
    }

    temp_s0->numLoaded++;
    Actor_init_actor_class(sp68, profile, temp_s0, play, argF, x, y, z, rotX, rotY, rotZ, arg9, argA, argB, fgName, params);

    Actor_info_part_new(actorInfo, sp68, profile->type);

    mNpc_SetNpcinfo(sp68, argE);

    {
        s32 temp_s0_2;

        temp_s0_2 = gSegments[6];
        Actor_ct(sp68, play);
        gSegments[6] = temp_s0_2;
    }

    return sp68;
}

Actor* Actor_info_make_child_actor(ActorInfo* actorInfo, Actor* arg1, PlayState* play, s16 actorId, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 argA, u16 fgName, s16 params, s32 argD) {
    Actor* temp_v0 = Actor_info_make_actor(actorInfo, play, actorId, x, y, z, rotX, rotY, rotZ, -1, -1, argA, fgName, params, -1, argD);

    if (temp_v0 != NULL) {
        arg1->unk_150 = temp_v0;
        temp_v0->unk_14C = arg1;
    }

    return temp_v0;
}

void restore_fgdata(Actor* actor, PlayState* play UNUSED) {
    Vec3f sp34;

    if ((actor->fgName == 0) || (actor->unk_00A != -1)) {
        return;
    }

    if ((actor->unk_008 < 0) || (actor->unk_009 < 0)) {
        return;
    }

    switch ((actor->fgName & 0xF000) >> 0xC) {
        case 8:
            xyz_t_move(&sp34, &actor->home.pos);
            if (func_8008B3E8_jp(&sp34, 0) == 1) {
                mFI_SetFG_common(actor->fgName, sp34, 0);
            }
            break;

        default:
            mFI_SetFG_common(actor->fgName, actor->home.pos, 0);
            break;
    }
}

void restore_fgdata_one(Actor* actor, PlayState* play) {
    if (restore_flag[actor->category] == 1) {
        restore_fgdata(actor, play);
    } else if (actor->unk_003 == 1) {
        restore_fgdata(actor, play);
    }
}

void restore_fgdata_all(PlayState* play) {
    ActorInfo* actorInfo = &play->actorInfo;
    ActorType cat;

    for (cat = 0; cat < ACTORCAT_MAX; cat++) {
        Actor* actor;

        if (restore_flag[cat] == 1) {
            for (actor = actorInfo->actorLists[cat].head; actor != NULL; actor = actor->unk_158) {
                restore_fgdata(actor, play);
            }
        } else {
            for (actor = actorInfo->actorLists[cat].head; actor != NULL; actor = actor->unk_158) {
                if (actor->unk_003 == 1) {
                    restore_fgdata(actor, play);
                }
            }
        }
    }
}

void Actor_info_save_actor(PlayState* play) {
    ActorInfo* actorInfo = &play->actorInfo;
    ActorType cat;

    for (cat = 0; cat < ACTORCAT_MAX; cat++) {
        Actor* actor;

        for (actor = actorInfo->actorLists[cat].head; actor != NULL; actor = actor->unk_158) {
            if (actor->unk_16C != NULL) {
                actor->unk_16C(actor, play);
                actor->unk_16C = NULL;
            }
        }
    }

    restore_fgdata_all(play);
}

Actor* Actor_info_delete(ActorInfo* actorInfo, Actor* actor, PlayState* play) {
    Actor* newHead;
    s32 pad UNUSED;
    ActorOverlay* overlayEntry;
    s32 fgName = actor->fgName;

    overlayEntry = actor->overlayEntry;

    restore_fgdata_one(actor, play);
    Actor_dt(actor, play);

    newHead = Actor_info_part_delete(actorInfo, actor);

    switch ((fgName & 0xF000) >> 0xC) {
        case 0xD:
        case 0xE:
            common_data.unk_1004C->unk_10(actor);
            break;

        case 5:
            common_data.unk_10098->unk_10(actor);
            break;

        default:
            zelda_free(actor);
            break;
    }

    if (overlayEntry->vramStart != NULL) {
        overlayEntry->numLoaded--;
        actor_free_check(overlayEntry, actor->fgName);
    }

    return newHead;
}

Actor* Actor_info_name_search_sub(Actor* actor, s16 id) {
    for (; actor != NULL; actor = actor->unk_158) {
        if (id == actor->id) {
            break;
        }
    }
    return actor;
}

Actor* Actor_info_name_search(ActorInfo* actorInfo, s16 id, ActorType cat) {
    Actor* head = actorInfo->actorLists[cat].head;

    if (head != NULL) {
        return Actor_info_name_search_sub(head, id);
    }
    return NULL;
}

Actor* Actor_info_fgName_search_sub(Actor* actor, u16 fgName) {
    for (; actor != NULL; actor = actor->unk_158) {
        if (actor->fgName == fgName) {
            break;
        }
    }

    return actor;
}

Actor* Actor_info_fgName_search(ActorInfo* actorInfo, u16 fgName, ActorType cat) {
    Actor* head = actorInfo->actorLists[cat].head;

    if (head != NULL) {
        return Actor_info_fgName_search_sub(head, fgName);
    }
    return NULL;
}

#if 0
void Part_Break_init(void* arg0, s32 arg1, ? arg2) {
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    void* temp_a0_4;
    void* temp_a0_5;
    void* temp_a0_6;
    void* temp_v0;
    void* temp_v0_2;
    void* temp_v0_3;

    temp_a0 = (arg1 << 6) + 0x40;
    sp28 = temp_a0;
    temp_v0 = zelda_malloc(temp_a0);
    arg0->unk_0 = temp_v0;
    if (temp_v0 != NULL) {
        temp_a0_2 = (arg1 * 4) + 4;
        sp24 = temp_a0_2;
        temp_v0_2 = zelda_malloc(temp_a0_2);
        arg0->unk_C = temp_v0_2;
        if (temp_v0_2 != NULL) {
            temp_a0_3 = (arg1 * 2) + 2;
            sp20 = temp_a0_3;
            temp_v0_3 = zelda_malloc(temp_a0_3);
            arg0->unk_4 = temp_v0_3;
            if (temp_v0_3 != NULL) {
                mem_clear(arg0->unk_0, sp28, 0);
                mem_clear(arg0->unk_C, sp24, 0);
                mem_clear(arg0->unk_4, sp20, 0);
                arg0->unk_10 = 1;
                return;
            }
        }
    }
    temp_a0_4 = arg0->unk_0;
    if (temp_a0_4 != NULL) {
        zelda_free(temp_a0_4);
    }
    temp_a0_5 = arg0->unk_C;
    if (temp_a0_5 != NULL) {
        zelda_free(temp_a0_5);
    }
    temp_a0_6 = arg0->unk_4;
    if (temp_a0_6 != NULL) {
        zelda_free(temp_a0_6);
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Part_Break_init.s")
#endif

#if 0
void* HiliteReflect_new(void* arg0, f32* arg1, void* arg2, void* arg3, void* arg4, LookAt** arg5) {
    LookAt* sp64;
    LookAt* temp_a2;
    LookAt* temp_s0;
    LookAt* temp_v0;
    LookAt* temp_v0_2;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fa1;
    void* temp_v1;
    void* temp_v1_2;
    void* temp_v1_3;

    temp_s0 = arg3->unk_29C - 0x20;
    arg3->unk_29C = temp_s0;
    sp64 = temp_s0;
    temp_fv0 = arg1->unk_0;
    if ((arg0->unk_0 == temp_fv0) && (arg0->unk_8 == arg1->unk_8)) {
        var_fa1 = temp_fv0 + 0.001f;
    } else {
        var_fa1 = temp_fv0;
    }
    temp_a2 = arg3->unk_29C - 0x10;
    arg3->unk_29C = temp_a2;
    *arg5 = temp_a2;
    temp_fv0_2 = arg2->unk_0;
    temp_fv1 = arg2->unk_4;
    temp_fa0 = arg2->unk_8;
    guLookAtHilite(&B_8011B850_jp, sp64, (Hilite* ) temp_a2, var_fa1, arg1->unk_4, arg1->unk_8, arg0->unk_0, arg0->unk_4, arg0->unk_8, 0.0f, 1.0f, 0.0f, temp_fv0_2, temp_fv1, temp_fa0, temp_fv0_2, temp_fv1, temp_fa0, 0x10, 0x10);
    arg4->unk_0 = 0xDC08000A;
    arg4->unk_4 = sp64;
    temp_v1_2 = arg4 + 8;
    temp_v1_2->unk_4 = &sp64->l[1];
    temp_v1_2->unk_0 = 0xDC08030A;
    temp_v1_3 = temp_v1_2 + 8;
    temp_v1_3->unk_0 = 0xE7000000;
    temp_v1_3->unk_4 = 0;
    temp_v1 = temp_v1_3 + 8;
    temp_v0 = *arg5;
    temp_v1->unk_0 = (s32) ((temp_v0->unk_4 & 0xFFF) | 0xF2000000 | ((temp_v0->unk_0 & 0xFFF) << 0xC));
    temp_v0_2 = *arg5;
    temp_v1->unk_4 = (s32) (((temp_v0_2->unk_4 + 0x3C) & 0xFFF) | 0x01000000 | (((temp_v0_2->unk_0 + 0x3C) & 0xFFF) << 0xC));
    return temp_v1 + 8;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/HiliteReflect_new.s")
#endif

#if 0
f32 HiliteReflect_init(void* arg3) {
    f32 sp2C;

    arg3->unk_298 = HiliteReflect_new(arg3->unk_298, &sp2C);
    return sp2C;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/HiliteReflect_init.s")
#endif

#if 0
f32 HiliteReflect_xlu_init(void* arg3) {
    f32 sp2C;

    arg3->unk_2A8 = HiliteReflect_new(arg3->unk_2A8, &sp2C);
    return sp2C;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/HiliteReflect_xlu_init.s")
#endif

#if 0
f32 HiliteReflect_light_init(void* arg3) {
    f32 sp2C;

    arg3->unk_2D8 = HiliteReflect_new(arg3->unk_2D8, &sp2C);
    return sp2C;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/HiliteReflect_light_init.s")
#endif

#if 0
void Setpos_HiliteReflect_init(void* arg1) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    sp24 = (f32) arg1->unk_1B9A;
    sp28 = (f32) arg1->unk_1B9B;
    sp2C = (f32) arg1->unk_1B9C;
    HiliteReflect_init(arg1 + 0x1960, &sp24, arg1->unk_0);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Setpos_HiliteReflect_init.s")
#endif

#if 0
void Setpos_HiliteReflect_xlu_init(void* arg1) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    sp24 = (f32) arg1->unk_1B9A;
    sp28 = (f32) arg1->unk_1B9B;
    sp2C = (f32) arg1->unk_1B9C;
    HiliteReflect_xlu_init(arg1 + 0x1960, &sp24, arg1->unk_0);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Setpos_HiliteReflect_xlu_init.s")
#endif

#if 0
void Setpos_HiliteReflect_light_init(void* arg1) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    sp24 = (f32) arg1->unk_1B9A;
    sp28 = (f32) arg1->unk_1B9B;
    sp2C = (f32) arg1->unk_1B9C;
    HiliteReflect_xlu_init(arg1 + 0x1960, &sp24, arg1->unk_0);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Setpos_HiliteReflect_light_init.s")
#endif

#if 0
dlabel RO_801161E8_jp
.word 0x00000000
.word 0x00000000
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/RO_801161E8_jp.s")
#endif
