#include "m_actor.h"
#include "m_actor_dlftbls.h"
#include "m_collision_bg.h"
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
#include "fault.h"
#include "sys_matrix.h"
#include "ovlmgr.h"
#include "69A7E0.h"
#include "6A0DE0.h"
#include "6E9650.h"
#include "unknown_structs.h"
#include "macros.h"
#include "overlays/gamestates/ovl_play/m_play.h"

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
extern ? B_801458A0_jp;
extern s32 B_801458B8_jp;
extern s32 D_80100C70_jp;
extern ? actor_dlftbls;
extern ? common_data;
extern void* debug_mode;
static ? RO_801161E8_jp;                            /* unable to generate initializer; const */
#endif

extern MtxF MtxF_clear;

extern const struct_801161E8_jp RO_801161E8_jp;

UNK_RET Actor_malloc_actor_class(Actor** actorP, ActorProfile* profile, ActorOverlay*, const struct_801161E8_jp*, s32);
// UNK_RET func_80057940_jp(ActorProfile** profileP, ActorOverlay* overlayEntry, const struct_801161E8_jp* arg2, s32 arg3, s32 arg4);

extern s32 B_801458B8_jp; // gSegments[6]?

#if 0
void func_80056380_jp(void* arg0, ? arg1) {
    if ((arg0 == NULL) || (arg0->unk_170 == 0)) {
        FaultDrawer_SetCursor(0x30, 0x18);
        FaultDrawer_Printf("ACTOR NAME is NULL");
    }
    FaultDrawer_SetCursor(0x30, 0x18);
    FaultDrawer_Printf("ACTOR NAME %08x:%s", arg0, "");
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/func_80056380_jp.s")
#endif

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

#if 0
void Actor_world_to_eye(void* arg0, f32 arg1) {
    arg0->unk_4C = (f32) (arg0->unk_2C + arg1);
    arg0->unk_48 = (f32) arg0->unk_28;
    arg0->unk_50 = (f32) arg0->unk_30;
    arg0->unk_54 = (s16) arg0->unk_34;
    arg0->unk_56 = (s16) arg0->unk_36;
    arg0->unk_58 = (s16) arg0->unk_38;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_world_to_eye.s")
#endif

#if 0
void Actor_position_move(void* arg0) {
    f32 sp18;
    f32 temp_fv0;

    temp_fv0 = game_GameFrame_2F;
    sp18 = temp_fv0;
    gamePT->unk_1C58();
    arg0->unk_28 = (f32) (arg0->unk_28 + ((arg0->unk_68 * temp_fv0) + arg0->unk_C4));
    arg0->unk_2C = (f32) (arg0->unk_2C + ((arg0->unk_6C * temp_fv0) + arg0->unk_C8));
    arg0->unk_30 = (f32) (arg0->unk_30 + ((arg0->unk_70 * temp_fv0) + arg0->unk_CC));
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_position_move.s")
#endif

#if 0
void Actor_position_speed_set(void* arg0) {
    arg0->unk_68 = (f32) (sin_s(arg0->unk_36, arg0) * arg0->unk_74);
    arg0->unk_70 = (f32) (cos_s(arg0->unk_36) * arg0->unk_74);
    chase_f(arg0 + 0x6C, arg0->unk_7C, arg0->unk_78, arg0);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_position_speed_set.s")
#endif

#if 0
void Actor_position_moveF(void* arg0) {
    Actor_position_speed_set(arg0);
    Actor_position_move(arg0);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_position_moveF.s")
#endif

#if 0
s32 Actor_player_look_direction_check(void* arg0, s16 arg1, PlayState* arg2) {
    s16 temp_v1;
    s16 var_a0;

    temp_v1 = (arg0->unk_B6 + 0x8000) - get_player_actor_withoutCheck(arg2)->unk_DE;
    var_a0 = -temp_v1;
    if (temp_v1 >= 0) {
        var_a0 = temp_v1;
    }
    return var_a0 < arg1;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_player_look_direction_check.s")
#endif

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

#if 0
s32 Actor_data_bank_dma_end_check(void* arg0, PlayState* arg1) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = (s32) (arg0->unk_6 & 0xF000) >> 0xC;
    if ((temp_v0 != 0xD) && (temp_v0 != 0xE)) {
        var_v1 = (arg1 + (arg0->unk_26 * 0x54))->unk_110 > 0;
    } else {
        var_v1 = (*(&common_data + 0x1004C))->unk_F4(arg1 + 0x110, arg0, arg0, arg1);
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_data_bank_dma_end_check.s")
#endif

void Shape_Info_init(Actor* actor, f32 arg1, s32 arg2, f32 arg3, f32 arg4) {
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

#if 0
void Actor_foot_shadow_pos_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg1 == arg2) {
        Matrix_Position(arg3, arg0 + 0x10C);
        return;
    }
    if (arg1 == arg4) {
        Matrix_Position(arg5, arg0 + 0x118);
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_foot_shadow_pos_set.s")
#endif

#if 0
void Actor_delete(void* arg0) {
    if (arg0 != NULL) {
        arg0->unk_164 = 0;
        arg0->unk_168 = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_delete.s")
#endif

#if 0
//s32 Actor_data_bank_dma_end_check(Actor*, PlayState*); /* extern */
//? Actor_world_to_eye(Actor*, ?, PosRot*);           /* extern */
//? CollisionCheck_Status_ct(f32, s8*);               /* extern */
//? Shape_Info_init(Actor*, f32, ?, f32, f32);        /* extern */
//? xyz_t_move(s8*, PosRot*);                         /* extern */

void Actor_ct(Actor* actor, PlayState* play) {
    UNK_TYPE sp34;
    s32* sp2C;                                      /* compiler-managed */
    PosRot* temp_a2;
    s32 temp_v0_2;
    s32* temp_a0;
    void* temp_v0;
    void* temp_v1;

#if 0
    temp_v0 = play + (actor->unk_026 * 0x54);
    (temp_v0 + 0x110)->unk_50 = (s16) (temp_v0->unk_160 + 1);
#endif
    if ((u8) actor->unk_000[2] == 3) {
        #if 0
        common_data.unk_1004C->unk_14(&sp34, actor->unk_6);
        #endif
        temp_a0 = &play->unk_0110;
        sp2C = temp_a0;
        #if 0
        temp_v0_2 = mSc_bank_regist_check(temp_a0, sp36);
        actor->unk_708 = temp_v0_2;
        #endif
        temp_v1 = temp_a0 + (temp_v0_2 * 0x54);
        #if 0
        temp_v1->unk_50 = (s16) (temp_v1->unk_50 + 1);
        #endif
    }
    temp_a2 = &actor->world;
    #if 0
    temp_a2->pos.x = actor->unk_C;
    temp_a2->pos.y = actor->unk_10;
    temp_a2->pos.z = actor->unk_14;
    temp_a2->unk_C = (s32) actor->unk_18;
    temp_a2->unk_10 = (s32) actor->unk_1C;
    actor->unk_03C[0xA0] = (unaligned s32) actor->unk_34;
    actor->unk_E0 = (u16) actor->world.rot.z;
    #endif
    sp2C = temp_a2;
    Actor_world_to_eye(actor, 0, temp_a2);
    xyz_t_move(actor->unk_03C, sp2C);

    actor->unk_05C.x = 0.01f;
    actor->unk_05C.y = 0.01f;
    actor->unk_05C.z = 0.01f;
    #if 0
    actor->unk_7C = -20.0f;
    actor->unk_134 = 350.0f;
    actor->unk_140 = 350.0f;
    actor->unk_F4 = 1.0f;
    actor->unk_F8 = 1.0f;
    actor->unk_B8 = 3.4028235e38f;
    actor->unk_138 = 700.0f;
    actor->unk_13C = 1000.0f;
    actor->unk_144 = 55.0f;
    #endif
    CollisionCheck_Status_ct(1.0f, &actor->unk_03C[0x88]);
    Shape_Info_init(actor, 0.0f, 0, 0.0f, 0.0f);
    if (Actor_data_bank_dma_end_check(actor, play) == 1) {
        #if 0
        B_801458B8_jp = (play + (actor->unk_026 * 0x54))->unk_114 + 0x80000000;
        #endif
        actor->init(actor, play);
        actor->init = NULL;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_ct.s")
#endif

#if 0
void Actor_dt(void* arg0, PlayState* arg1) {
    ? (*temp_v0)(void*, PlayState*, void*);
    ? (*temp_v0_2)(void*, PlayState*, void*);
    s16 temp_a0;
    s32 temp_v0_5;
    void* temp_v0_3;
    void* temp_v0_4;
    void* temp_v0_6;

    temp_v0 = arg0->unk_16C;
    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg0);
        arg0->unk_16C = NULL;
    }
    temp_v0_2 = arg0->unk_160;
    if (temp_v0_2 != NULL) {
        temp_v0_2(arg0, arg1, arg0);
        arg0->unk_160 = NULL;
    }
    temp_v0_3 = arg0->unk_150;
    if ((temp_v0_3 != NULL) && (arg0 == temp_v0_3->unk_14C)) {
        temp_v0_3->unk_14C = 0;
    }
    temp_v0_4 = arg0->unk_14C;
    if ((temp_v0_4 != NULL) && (arg0 == temp_v0_4->unk_150)) {
        temp_v0_4->unk_150 = 0;
    }
    temp_v0_5 = (s32) (arg0->unk_6 & 0xF000) >> 0xC;
    if ((temp_v0_5 == 0xD) || (temp_v0_5 == 0xE)) {
        (*(&common_data + 0x1004C))->unk_F0(arg1 + 0x110, arg0, arg0);
        return;
    }
    temp_a0 = arg0->unk_26;
    if (temp_a0 >= arg1->unk_190C) {
        temp_v0_6 = arg1 + 0x110 + (temp_a0 * 0x54);
        if (temp_v0_6->unk_50 > 0) {
            arg0->unk_26 = -1;
            temp_v0_6->unk_50 = (s16) (temp_v0_6->unk_50 - 1);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_dt.s")
#endif

#if 0
void Actor_draw(PlayState* arg0, void* arg1) {
    ? sp48;
    s32 sp44;
    struct GraphicsContext* sp40;
    ? (*temp_v0)(void*, s32, PlayState*);
    s32 temp_a0;
    s32 temp_a0_2;
    struct GraphicsContext* temp_a1;
    void* temp_v1;
    void* temp_v1_2;
    void* temp_v1_3;
    void* var_a2;

    Fault_AddClient(&sp48, func_80056380_jp, arg1, "Actor_draw");
    temp_a1 = arg0->state.gfxCtx;
    sp40 = temp_a1;
    temp_a0 = Global_light_read(arg0 + 0x1C60, temp_a1);
    if (arg1->unk_20 & 0x400000) {
        var_a2 = NULL;
    } else {
        var_a2 = arg1 + 0x28;
    }
    sp44 = temp_a0;
    func_8009B884_jp(temp_a0, arg0->unk_1C60, var_a2);
    LightsN_disp(temp_a0, arg0->state.gfxCtx);
    Matrix_softcv3_load(arg1->unk_28, arg1->unk_2C + (arg1->unk_E4 * arg1->unk_60), arg1->unk_30, arg1 + 0xDC);
    Matrix_scale(arg1->unk_5C, arg1->unk_60, arg1->unk_64, 1);
    temp_a0_2 = (arg0 + (arg1->unk_26 * 0x54))->unk_114;
    B_801458B8_jp = temp_a0_2 + 0x80000000;
    temp_v1 = sp40->unk_298;
    sp40->unk_298 = (void* ) (temp_v1 + 8);
    temp_v1->unk_4 = temp_a0_2;
    temp_v1->unk_0 = 0xDB060018;
    temp_v1_2 = sp40->unk_2A8;
    sp40->unk_2A8 = (void* ) (temp_v1_2 + 8);
    temp_v1_2->unk_4 = temp_a0_2;
    temp_v1_2->unk_0 = 0xDB060018;
    temp_v1_3 = sp40->unk_2C8;
    sp40->unk_2C8 = (void* ) (temp_v1_3 + 8);
    temp_v1_3->unk_4 = temp_a0_2;
    temp_v1_3->unk_0 = 0xDB060018;
    arg1->unk_168(arg1, arg0);
    temp_v0 = arg1->unk_E8;
    if (temp_v0 != NULL) {
        temp_v0(arg1, sp44, arg0);
    }
    Fault_RemoveClient(&sp48);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_draw.s")
#endif

#if 0
void Actor_draw_actor_no_culling_check(void* arg0) {
    Actor_draw_actor_no_culling_check2(arg0 + 0x124, arg0->unk_130);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_draw_actor_no_culling_check.s")
#endif

#if 0
? Actor_draw_actor_no_culling_check2(void* arg0, void* arg1, f32 arg2) {
    ? var_v1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fa1;

    temp_fv1 = arg0->unk_140;
    temp_fv0 = arg1->unk_8;
    var_v1 = 0;
    if ((-temp_fv1 < temp_fv0) && (temp_fv0 < (arg0->unk_13C + temp_fv1))) {
        if (arg2 < 1.0f) {
            var_fa1 = 1.0f;
        } else {
            var_fa1 = 1.0f / arg2;
        }
        if (((fabsf(arg1->unk_0) - arg0->unk_134) * var_fa1) < 1.0f) {
            temp_fv0_2 = arg1->unk_4;
            if ((((temp_fv0_2 + arg0->unk_138) * var_fa1) > -1.0f) && (((temp_fv0_2 - temp_fv1) * var_fa1) < 1.0f)) {
                var_v1 = 1;
            }
        }
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_draw_actor_no_culling_check2.s")
#endif

#if 0
void Actor_cull_check(void* arg0) {
    if (Actor_draw_actor_no_culling_check() == 1) {
        arg0->unk_20 = (s32) (arg0->unk_20 | 0x40);
        return;
    }
    arg0->unk_20 = (s32) (arg0->unk_20 & ~0x40);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_cull_check.s")
#endif

#if 0
void Actor_delete_check(void* arg0, PlayState* arg1) {
    s8 temp_v0;
    s8 temp_v1;

    if (!(arg0->unk_20 & 0x70) && (arg0->unk_6 != 0)) {
        temp_v0 = arg0->unk_8;
        if (temp_v0 >= 0) {
            temp_v1 = arg0->unk_9;
            if ((temp_v1 >= 0) && ((arg1->unk_00[0x40] != temp_v0) || (arg1->unk_00[0x41] != temp_v1))) {
                Actor_delete();
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_delete_check.s")
#endif

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

void Actor_info_call_actor(PlayState* play, ActorInfo* actorInfo) {
    s32 sp50;
    ActorInfo* sp4C;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_t1;
    s32 temp_t8;
    void* temp_s2;
    void* temp_s3;
    void* temp_v0;
    void* var_s0;
    void* var_v1;

    temp_v0 = get_player_actor_withoutCheck(play);
    func_8008E5F4_jp(subroutine_arg0, temp_v0->unk_2C, temp_v0->unk_30);
    sp50 = 0;
    sp4C = actorInfo;
    do {
        var_s0 = sp4C->unk_8;
        if (var_s0 != NULL) {
            do {
                play->state.unk_9C[1] = 0x97;
                play->state.unk_9C[0] = (s8) var_s0->unk_0;
                if (var_s0->unk_2C < -25000.0f) {
                    var_s0->unk_2C = -25000.0f;
                }
                if (var_s0->unk_15C != NULL) {
                    if (Actor_data_bank_dma_end_check(var_s0, play) == 1) {
                        B_801458A0_jp.unk_18 = (s32) ((play + (var_s0->unk_26 * 0x54))->unk_114 + 0x80000000);
                        play->state.unk_9C[1] = 0x98;
                        var_s0->unk_15C(var_s0, play);
                        play->state.unk_9C[1] = 0x99;
                        var_s0->unk_15C = NULL;
                    }
                    goto block_18;
                }
                if (Actor_data_bank_dma_end_check(var_s0, play) == 0) {
                    play->state.unk_9C[1] = 0x9A;
                    Actor_delete(var_s0);
                    play->state.unk_9C[1] = 0x9B;
                    goto block_18;
                }
                temp_s2 = var_s0 + 0x28;
                if (var_s0->unk_164 == NULL) {
                    if (var_s0->unk_B5 == 0) {
                        play->state.unk_9C[1] = 0x9C;
                        var_v1 = Actor_info_delete(&play->unk_00[0x1BD4], var_s0, play);
                        play->state.unk_9C[1] = 0x9D;
                    } else {
                        play->state.unk_9C[1] = 0x9E;
                        Actor_dt(var_s0, play);
                        play->state.unk_9C[1] = 0x9F;
                        goto block_18;
                    }
                } else {
                    play->state.unk_9C[1] = 0xA0;
                    temp_s3 = temp_v0 + 0x28;
                    xyz_t_move(var_s0 + 0x3C, temp_s2);
                    temp_fv0 = search_position_distanceXZ(temp_s2, temp_s3);
                    var_s0->unk_BC = temp_fv0;
                    var_s0->unk_C0 = (f32) (temp_v0->unk_2C - var_s0->unk_2C);
                    temp_fv1 = var_s0->unk_C0;
                    var_s0->unk_B8 = (f32) ((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
                    temp_t8 = var_s0->unk_20 & 0xFEFFFFFF;
                    var_s0->unk_B6 = search_position_angleY(temp_s2, temp_s3);
                    var_s0->unk_20 = temp_t8;
                    if ((temp_t8 & 0x50) || (var_s0->unk_2 == 3)) {
                        B_801458A0_jp.unk_18 = (s32) ((play + (var_s0->unk_26 * 0x54))->unk_114 + 0x80000000);
                        play->state.unk_9C[1] = 0xA1;
                        var_s0->unk_164(var_s0, play);
                        play->state.unk_9C[1] = 0xA2;
                    }
                    CollisionCheck_Status_Clear(var_s0 + 0xC4);
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
    play->state.unk_9C[1] = 0xA3;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_call_actor.s")
#endif

#if 0
//? Actor_cull_check(Actor*);                         /* extern */
//? Actor_delete_check(Actor*, PlayState*);           /* extern */
//? Actor_draw(PlayState*, Actor*);                   /* extern */
//? Light_list_point_draw(PlayState*);                /* extern */
//? Skin_Matrix_PrjMulVector(MtxF*, PosRot*, void*, void*); /* extern */

void Actor_info_draw_actor(PlayState* play, ActorInfo* actorInfo) {
    Actor* var_s0;
    ActorListEntry* var_s5;
    s32 (*temp_s4)(Actor*, PlayState*);
    s32 temp_v0;
    s32 var_s6;

    temp_s4 = play->unk_2208;
    var_s5 = actorInfo->actorLists;
    var_s6 = 0;
    do {
        var_s0 = var_s5->head;
        if (var_s0 != NULL) {
            do {
                Skin_Matrix_PrjMulVector(&play->unk_1E1C, &var_s0->world, var_s0 + 0x124, var_s0 + 0x130);
                Actor_cull_check(var_s0);
                var_s0->unk_B5 = 0;
                if ((temp_s4(var_s0, play) == 0) && (var_s0->unk_15C == 0) && (var_s0->unk_168 != 0)) {
                    temp_v0 = var_s0->unk_20;
                    if (temp_v0 & 0x60) {
                        if (!(temp_v0 & 0x80) && (var_s0->unk_148 == 0) && (var_s0->unk_149 == 0)) {
                            Actor_draw(play, var_s0);
                            var_s0->unk_B5 = 1;
                        }
                    } else {
                        Actor_delete_check(var_s0, play);
                    }
                }
                var_s0 = var_s0->unk_158;
            } while (var_s0 != NULL);
        }
        var_s6 += 1;
        var_s5 += 8;
    } while (var_s6 != 8);
    if (debug_mode->r[0x380] == 0) {
        Light_list_point_draw(play);
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_draw_actor.s")
#endif

#if 0
void Actor_info_part_new(ActorInfo* arg0, void* arg1, u8 arg2) {
    s8 temp_a2;
    void* temp_v0;
    void* temp_v1;

    temp_a2 = arg2 & 0xFF;
    arg1->unk_2 = temp_a2;
    temp_v0 = arg0 + (temp_a2 * 8);
    arg0->placeholder += 1;
    temp_v1 = temp_v0->unk_8;
    temp_v0->unk_4 = (s32) (temp_v0->unk_4 + 1);
    if (temp_v1 != NULL) {
        temp_v1->unk_154 = arg1;
    }
    temp_v0->unk_8 = arg1;
    arg1->unk_158 = temp_v1;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_part_new.s")
#endif

#if 0
void* Actor_info_part_delete(s8* arg0, void* arg1) {
    void* temp_v0;
    void* temp_v1;
    void* temp_v1_2;

    *arg0 = (s32) (*arg0 - 1);
    temp_v0 = arg0 + (arg1->unk_2 * 8);
    temp_v0->unk_4 = (s32) (temp_v0->unk_4 - 1);
    temp_v1_2 = arg1->unk_154;
    if (temp_v1_2 != NULL) {
        temp_v1_2->unk_158 = (void* ) arg1->unk_158;
    } else {
        (arg0 + (arg1->unk_2 * 8))->unk_8 = (void* ) arg1->unk_158;
    }
    temp_v1 = arg1->unk_158;
    if (temp_v1 != NULL) {
        temp_v1->unk_154 = (void* ) arg1->unk_154;
    }
    arg1->unk_154 = NULL;
    arg1->unk_158 = NULL;
    return temp_v1;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_part_delete.s")
#endif

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

void actor_free_check(ActorOverlay* overlayEntry, u16 arg1) {
    if ((overlayEntry->numLoaded == 0) && (overlayEntry->loadedRamAddr != NULL)) {
        switch ((arg1 & 0xF000) >> 0xC) {
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

typedef struct CommonData_unk_1004C_unk_4_unk_14_arg0 {
    /* 0x0 */ s16 unk_0;
    /* 0x0 */ s16 unk_2;
    /* 0x04 */ UNK_TYPE1 unk_04[0x5C];
} CommonData_unk_1004C_unk_4_unk_14_arg0;

// this function may be Actor_data_bank_regist_check_npc
#if 0
s32 func_80057A8C_jp(s32* arg0, ActorProfile* profile, ActorOverlay* overlayEntry, PlayState* play, u16 arg4) {
    s16 sp92;
    s16 sp90;
    s32 pad;
    s32 sp88;
    CommonData_unk_1004C_unk_4_unk_14_arg0 sp24;
    s32 temp_v0;

    sp88 = 1;
    common_data.unk_1004C->unk_14(&sp24, arg4);
    sp92 = sp24.unk_0;
    sp90 = sp24.unk_2;

    *arg0 = mSc_bank_regist_check(&play->unk_0110, sp92);
    temp_v0 = mSc_bank_regist_check(&play->unk_0110, sp90);

    if ((*arg0 < 0) || (temp_v0 < 0)) {
        if (*arg0 >= 0) {
            sp92 = 0;
        }
        if (temp_v0 >= 0) {
            sp90 = 0;
        }

        common_data.unk_1004C->unk_EC(&play->unk_0110, sp92, sp90);
        actor_free_check(overlayEntry, arg4);
        sp88 = 0;
    }
    return sp88;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/func_80057A8C_jp.s")
#endif

#if 0
s32 func_80057B70_jp(s32* arg0, void* arg1, void* arg2, s32 arg3, u16 arg4) {
    s32 sp20;
    void* sp1C;
    s32 temp_v0;
    s32 var_v1;
    void* temp_a0;

    temp_a0 = arg3 + 0x110;
    sp1C = temp_a0;
    sp20 = 1;
    temp_v0 = mSc_bank_regist_check(temp_a0, arg1->unk_A);
    var_v1 = 1;
    *arg0 = temp_v0;
    if (temp_v0 == -1) {
        func_800C6144_jp(temp_a0, arg1->unk_A);
        actor_free_check(arg2, arg4);
        var_v1 = 0;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/func_80057B70_jp.s")
#endif

s32 Actor_data_bank_regist_check(s32* arg0, ActorProfile* profile, ActorOverlay* overlayEntry, PlayState* play, u16 arg4) {
    s32 var_v1 = 1;

    if (*arg0 == -1) {
        if (profile->type == ACTORCAT_3) {
            var_v1 = func_80057A8C_jp(arg0, profile, overlayEntry, play, arg4);
        } else {
            var_v1 = func_80057B70_jp(arg0, profile, overlayEntry, play, arg4);
        }
    }
    return var_v1;
}

#if 0
s32 Actor_malloc_actor_class(void** arg0, void* arg1, void* arg2, ?* arg3, u16 arg4) {
    ? sp24;
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = (s32) (arg4 & 0xF000) >> 0xC;
    if (temp_v0 != 5) {
        if ((temp_v0 == 0xD) || (temp_v0 == 0xE)) {
            *arg0 = (*(&common_data + 0x1004C))->unk_C(arg1->unk_C, arg3, 1);
            (*(&common_data + 0x1004C))->unk_14(&sp24, arg4);
        } else {
            *arg0 = zelda_malloc(arg1->unk_C);
        }
    } else {
        *arg0 = (*(&common_data + 0x10098))->unk_C();
    }
    var_v0 = 1;
    if (*arg0 == NULL) {
        actor_free_check(arg2, arg4);
        var_v0 = 0;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_malloc_actor_class.s")
#endif

#if 0
void Actor_init_actor_class(void* arg0, void* arg1, void* arg2, PlayState* arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s16 arg8, s16 arg9, s16 argA, s8 argB, s8 argC, s16 argD, u16 argE, s16 argF) {
    mem_clear(arg1->unk_C, 0);
    arg0->unk_170 = arg2;
    arg0->unk_0 = (s16) arg1->unk_0;
    arg0->unk_20 = (s32) arg1->unk_4;
    arg0->unk_26 = (s16) arg4;
    arg0->unk_15C = (s32) arg1->unk_10;
    arg0->unk_160 = (s32) arg1->unk_14;
    arg0->unk_164 = (s32) arg1->unk_18;
    arg0->unk_168 = (s32) arg1->unk_1C;
    arg0->unk_16C = (s32) arg1->unk_20;
    arg0->unk_24 = argF;
    arg0->unk_4 = (s16) arg3->unk_E0;
    arg0->unk_C = arg5;
    arg0->unk_10 = arg6;
    arg0->unk_14 = arg7;
    arg0->unk_18 = arg8;
    arg0->unk_1A = arg9;
    arg0->unk_1C = argA;
    arg0->unk_8 = argB;
    arg0->unk_9 = argC;
    arg0->unk_A = argD;
    arg0->unk_6 = argE;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_init_actor_class.s")
#endif

Actor* Actor_info_make_actor(ActorInfo* actorInfo, PlayState* play, s16 actorId, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s8 arg9, s8 argA, s16 argB, u16 argC, s16 params, s8 argE, s32 argF) {
    u16 *new_var = &argC;
    Actor* sp68;
    ActorProfile* profile; // sp64
    ActorOverlay* temp_s0 = &actor_dlftbls[actorId];
    size_t size = (uintptr_t)temp_s0->vramEnd - (uintptr_t)temp_s0->vramStart;

    if (actorInfo->unk_00 >= 0xC9) {
        return NULL;
    }

    if (func_80057940_jp(&profile, temp_s0, &RO_801161E8_jp, size, *new_var) == 0) {
        return NULL;
    }
    if (Actor_data_bank_regist_check(&argF, profile, temp_s0, play, argC) == 0) {
        return NULL;
    }
    if (Actor_malloc_actor_class(&sp68, profile, temp_s0, &RO_801161E8_jp,  argC) == 0) {
        return NULL;
    }

    temp_s0->numLoaded += 1;
    Actor_init_actor_class(sp68, profile, temp_s0, play, argF, x, y, z, rotX, rotY, rotZ, arg9, argA, argB, argC, params);

    Actor_info_part_new(actorInfo, sp68, profile->type);

    mNpc_SetNpcinfo(sp68, argE);

    {
        s32 temp_s0_2;

        temp_s0_2 = B_801458B8_jp;
        Actor_ct(sp68, play);
        B_801458B8_jp = temp_s0_2;
    }

    return sp68;
}

#if 0
void* Actor_info_make_child_actor(void* arg1, ActorInfo* arg2, s16 arg3, s32 arg4, f32 arg5, f32 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, u16 argB, s16 argC, s32 argD) {
    void* temp_v0;

    temp_v0 = Actor_info_make_actor(arg2, (PlayState* ) arg3, (s16) arg4, arg5, arg6, (bitwise f32) arg7, (s32) arg8, (s32) arg9, -1, -1, (s32) argA, (s32) argB, (s32) argC, -1, argD);
    if (temp_v0 != NULL) {
        arg1->unk_150 = temp_v0;
        temp_v0->unk_14C = arg1;
    }
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_make_child_actor.s")
#endif

#if 0
void restore_fgdata(void* arg0, s32 arg1) {
    ? sp34;
    s32 sp30;
    u16 temp_t6;

    temp_t6 = arg0->unk_6;
    sp30 = (s32) temp_t6;
    if ((temp_t6 != 0) && (arg0->unk_A == -1) && (arg0->unk_8 >= 0) && (arg0->unk_9 >= 0)) {
        if (((s32) (temp_t6 & 0xF000) >> 0xC) == 8) {
            xyz_t_move(&sp34, arg0 + 0xC);
            if (func_8008B3E8_jp(&sp34, 0) == 1) {
                mFI_SetFG_common(arg0->unk_6, subroutine_arg1, sp34.unk_4, sp34.unk_8, 0);
            }
        } else {
            mFI_SetFG_common(unksp32, subroutine_arg1, arg0->unk_10, arg0->unk_14, 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/restore_fgdata.s")
#endif

#if 0
void restore_fgdata_one(void* arg0) {
    if ((&D_80100C70_jp)[arg0->unk_2] == 1) {
        restore_fgdata();
        return;
    }
    if (arg0->unk_3 == (u8) 1) {
        restore_fgdata();
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/restore_fgdata_one.s")
#endif

#if 0
void restore_fgdata_all(s32 arg0) {
    s32 var_s5;
    s32* var_s4;
    void* var_s0;
    void* var_s0_2;
    void* var_s3;

    var_s4 = &D_80100C70_jp;
    var_s5 = 0;
    var_s3 = arg0 + 0x1C78;
    do {
        if (*var_s4 == 1) {
            var_s0 = var_s3->unk_8;
            if (var_s0 != NULL) {
                do {
                    restore_fgdata(var_s0, arg0);
                    var_s0 = var_s0->unk_158;
                } while (var_s0 != NULL);
            }
        } else {
            var_s0_2 = var_s3->unk_8;
            if (var_s0_2 != NULL) {
                do {
                    if (var_s0_2->unk_3 == (u8) 1) {
                        restore_fgdata(var_s0_2, arg0);
                    }
                    var_s0_2 = var_s0_2->unk_158;
                } while (var_s0_2 != NULL);
            }
        }
        var_s5 += 8;
        var_s4 += 4;
        var_s3 += 8;
    } while (var_s5 != 0x40);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/restore_fgdata_all.s")
#endif

#if 0
void Actor_info_save_actor(s32 arg0) {
    ? (*temp_v0)(void*, s32);
    s32 var_s2;
    void* var_s0;
    void* var_s3;

    var_s2 = 0;
    var_s3 = arg0 + 0x1C78;
    do {
        var_s0 = var_s3->unk_8;
        if (var_s0 != NULL) {
            do {
                temp_v0 = var_s0->unk_16C;
                if (temp_v0 != NULL) {
                    temp_v0(var_s0, arg0);
                    var_s0->unk_16C = NULL;
                }
                var_s0 = var_s0->unk_158;
            } while (var_s0 != NULL);
        }
        var_s2 += 8;
        var_s3 += 8;
    } while (var_s2 != 0x40);
    restore_fgdata_all(arg0);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_save_actor.s")
#endif

#if 0
void* Actor_info_delete(s8* arg0, void* arg1, PlayState* arg2) {
    void* sp2C;
    s32 sp20;
    s32 temp_v1;
    void* temp_s1;

    sp20 = (s32) arg1->unk_6;
    temp_s1 = arg1->unk_170;
    restore_fgdata_one(arg1, arg2);
    Actor_dt(arg1, arg2);
    sp2C = Actor_info_part_delete(arg0, arg1);
    temp_v1 = (s32) (sp20 & 0xF000) >> 0xC;
    if (temp_v1 != 5) {
        if ((temp_v1 == 0xD) || (temp_v1 == 0xE)) {
            (*(&common_data + 0x1004C))->unk_10(arg1);
        } else {
            zelda_free(arg1);
        }
    } else {
        (*(&common_data + 0x10098))->unk_10(arg1);
    }
    if (temp_s1->unk_8 != 0) {
        temp_s1->unk_1E = (s8) (temp_s1->unk_1E - 1);
        actor_free_check(temp_s1, arg1->unk_6);
    }
    return sp2C;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_delete.s")
#endif

#if 0
void* Actor_info_name_search_sub(void* arg0, s16 arg1) {
    void* var_a0;

    var_a0 = arg0;
    if (var_a0 != NULL) {
loop_1:
        if (arg1 != var_a0->unk_0) {
            var_a0 = var_a0->unk_158;
            if (var_a0 != NULL) {
                goto loop_1;
            }
        }
    }
    return var_a0;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_name_search_sub.s")
#endif

#if 0
void* Actor_info_name_search(s32 arg0, s16 arg1, s32 arg2) {
    void* temp_a3;
    void* var_v0;

    temp_a3 = (arg0 + (arg2 * 8))->unk_8;
    var_v0 = NULL;
    if (temp_a3 != NULL) {
        var_v0 = Actor_info_name_search_sub(temp_a3, arg1, temp_a3);
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_name_search.s")
#endif

#if 0
void* Actor_info_fgName_search_sub(void* arg0, s32 arg1) {
    void* var_a0;

    var_a0 = arg0;
    if (var_a0 != NULL) {
loop_1:
        if ((arg1 & 0xFFFF) != var_a0->unk_6) {
            var_a0 = var_a0->unk_158;
            if (var_a0 != NULL) {
                goto loop_1;
            }
        }
    }
    return var_a0;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_fgName_search_sub.s")
#endif

#if 0
void* Actor_info_fgName_search(s32 arg0, s32 arg1, s32 arg2) {
    void* temp_a3;
    void* var_v0;

    temp_a3 = (arg0 + (arg2 * 8))->unk_8;
    var_v0 = NULL;
    if (temp_a3 != NULL) {
        var_v0 = Actor_info_fgName_search_sub(temp_a3, arg1 & 0xFFFF, temp_a3);
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_info_fgName_search.s")
#endif

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
