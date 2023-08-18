#include "m_actor.h"
#include "m_actor_dlftbls.h"
#include "m_collision_bg.h"
#include "m_collision_obj.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_lights.h"
#include "m_malloc.h"
#include "m_lib.h"
#include "m_skin_matrix.h"
#include "m_player_lib.h"
#include "m_scene.h"
#include "libc/math.h"
#include "fault.h"
#include "sys_matrix.h"
#include "ovlmgr.h"
#include "gfx.h"
#include "6E9650.h"
#include "unknown_structs.h"
#include "code_variables.h"
#include "macros.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "overlays/actors/ovl_Npc/ac_npc.h"

void func_80056380_jp(void* arg0, void* arg1 UNUSED) {
    Actor* actor = arg0;
    const char* name;

    if ((actor == NULL) || (actor->overlayEntry == NULL)) {
        //! @bug this will be overriden by the next printf
        FaultDrawer_SetCursor(48, 24);
        FaultDrawer_Printf("ACTOR NAME is NULL");
    }

    FaultDrawer_SetCursor(48, 24);
    name = "";
    FaultDrawer_Printf("ACTOR NAME %08x:%s", actor, name);
}

void projection_pos_set(Game_Play* game_play, Vec3f* worldPos, Vec3f* projectedPos, f32* invW) {
    Skin_Matrix_PrjMulVector(&game_play->viewProjectionMtxF, worldPos, projectedPos, invW);

    *invW = (*invW < 1.0f) ? 1.0f : (1.0f / *invW);
}

void Actor_world_to_eye(Actor* actor, f32 arg1) {
    actor->eye.pos.x = actor->world.pos.x;
    actor->eye.pos.y = actor->world.pos.y + arg1;
    actor->eye.pos.z = actor->world.pos.z;
    actor->eye.rot.x = actor->world.rot.x;
    actor->eye.rot.y = actor->world.rot.y;
    actor->eye.rot.z = actor->world.rot.z;
}

void Actor_position_move(Actor* actor) {
    Kankyo* kankyo = &((Game_Play*)gamePT)->kankyo;
    f32 speedRate;

    speedRate = game_GameFrame_2F;

    kankyo->unk_C0(actor);

    actor->world.pos.x += actor->velocity.x * speedRate + actor->colStatus.displacement.x;
    actor->world.pos.y += actor->velocity.y * speedRate + actor->colStatus.displacement.y;
    actor->world.pos.z += actor->velocity.z * speedRate + actor->colStatus.displacement.z;
}

void Actor_position_speed_set(Actor* actor) {
    actor->velocity.x = sin_s(actor->world.rot.y) * actor->speed;
    actor->velocity.z = cos_s(actor->world.rot.y) * actor->speed;

    chase_f(&actor->velocity.y, actor->terminalVelocity, actor->gravity);
}

void Actor_position_moveF(Actor* actor) {
    Actor_position_speed_set(actor);
    Actor_position_move(actor);
}

s32 Actor_player_look_direction_check(Actor* actor, s16 maxAngleDiff, Game_Play* game_play) {
    s16 yawDiff = BINANG_ROT180(actor->yawTowardsPlayer) - get_player_actor_withoutCheck(game_play)->actor.shape.rot.y;

    return ABS(yawDiff) < maxAngleDiff;
}

void Actor_display_position_set(Game_Play* game_play, Actor* actor, s16* x, s16* y) {
    Vec3f projectedPos;
    f32 invW;

    projection_pos_set(game_play, &actor->world.pos, &projectedPos, &invW);

    // Explicit cast to avoid implicit cast from f32 to s16
    *x = (s32)PROJECTED_TO_SCREEN_X(projectedPos, invW);
    *y = (s32)PROJECTED_TO_SCREEN_Y(projectedPos, invW);
}

s32 Actor_data_bank_dma_end_check(Actor* actor, Game_Play* game_play) {
    s32 var_v1;

    switch (ACTOR_FGNAME_GET_F000(actor->fgName)) {
        case FGNAME_F000_D:
        case FGNAME_F000_E:
            var_v1 = common_data.unk_1004C->unk_F4(game_play->unk_0110, actor);
            break;

        default:
            var_v1 = game_play->unk_0110[actor->unk_026].unk_00 > 0;
            break;
    }

    return var_v1;
}

void Shape_Info_init(Actor* actor, f32 arg1, Shape_Info_unk_0C arg2, f32 arg3, f32 arg4) {
    actor->shape.unk_08 = arg1;
    actor->shape.unk_0C = arg2;
    actor->shape.unk_10 = arg3;
    actor->shape.unk_14 = arg4;
    actor->shape.unk_2C = 1;
    actor->shape.unk_20 = 0;
    actor->shape.unk_18 = 1.0f;
    actor->shape.unk_1C = 1.0f;
    actor->shape.unk_2E = 0;
    actor->shape.unk_24 = &actor->world.pos;
    actor->shape.unk_28 = -1;
    actor->shape.unk_2D = 0;
}

void Actor_foot_shadow_pos_set(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex,
                               Vec3f* rightFootPos) {
    if (limbIndex == leftFootIndex) {
        Matrix_Position(leftFootPos, &actor->shape.feetPos[FOOT_LEFT]);
    } else if (limbIndex == rightFootIndex) {
        Matrix_Position(rightFootPos, &actor->shape.feetPos[FOOT_RIGHT]);
    }
}

void Actor_delete(Actor* actor) {
    if (actor != NULL) {
        actor->update = NULL;
        actor->draw = NULL;
    }
}

void Actor_ct(Actor* actor, Game_Play* game_play) {
    s32 pad[2] UNUSED;
    Game_Play_unk_0110* temp;
    Npc* npc;
    CommonData_unk_1004C_unk_14_arg0 sp34;
    Game_Play_unk_0110* temp_a0;

    temp_a0 = game_play->unk_0110;

    temp = temp_a0;
    temp += actor->unk_026;
    temp->unk_50++;

    if (actor->part == ACTOR_PART_NPC) {
        npc = (Npc*)actor;

        common_data.unk_1004C->unk_14(&sp34, npc->actor.fgName);
        npc->unk_708 = mSc_bank_regist_check(temp_a0, sp34.unk_02);
        temp_a0[npc->unk_708].unk_50++;
    }

    actor->world = actor->home;
    actor->shape.rot = actor->world.rot;

    Actor_world_to_eye(actor, 0.0f);
    xyz_t_move(&actor->prevPos, &actor->world.pos);

    actor->scale.x = 0.01f;
    actor->scale.y = 0.01f;
    actor->scale.z = 0.01f;

    actor->terminalVelocity = -20.0f;
    actor->xyzDistToPlayerSq = FLT_MAX;

    actor->uncullZoneScale = 350.0f;
    actor->uncullZoneDownward = 700.0f;

    actor->shape.unk_18 = 1.0f;
    actor->shape.unk_1C = 1.0f;

    actor->unk_13C = 1000.0f;
    actor->unk_140 = 350.0f;
    actor->unk_144 = 55.0f;

    CollisionCheck_Status_ct(&actor->colStatus);
    Shape_Info_init(actor, 0.0f, NULL, 0.0f, 0.0f);

    if (Actor_data_bank_dma_end_check(actor, game_play) == 1) {
        gSegments[6] = (uintptr_t)OS_K0_TO_PHYSICAL(temp_a0[actor->unk_026].segment);
        actor->ct(actor, game_play);
        actor->ct = NULL;
    }
}

#ifdef NON_MATCHING
void Actor_dt(Actor* actor, Game_Play* game_play) {
    Game_Play_unk_0110* temp_v0_6;
    s32 new_var;

    if (actor->save != NULL) {
        actor->save(actor, game_play);
        actor->save = NULL;
    }

    if (actor->dt != NULL) {
        actor->dt(actor, game_play);
        actor->dt = NULL;
    }

    if ((actor->child != NULL) && (actor == actor->child->parent)) {
        actor->child->parent = NULL;
    }

    if ((actor->parent != NULL) && (actor == actor->parent->child)) {
        actor->parent->child = NULL;
    }

    temp_v0_6 = game_play->unk_0110;
    if (0) {}

    switch ((actor->fgName & 0xF000) >> 0xC) {
        case 0xD:
        case 0xE:
            common_data.unk_1004C->unk_F0(temp_v0_6, actor);
            break;

        default:
            new_var = game_play->unk_190C;

            if (actor->unk_026 >= new_var) {
                temp_v0_6 = &temp_v0_6[(void)0, actor->unk_026];
                if (temp_v0_6->unk_50 > 0) {
                    actor->unk_026 = -1;
                    temp_v0_6->unk_50--;
                }
            }
            break;
    }
}
#else
void Actor_dt(Actor* actor, struct Game_Play* game_play);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/Actor_dt.s")
#endif

void Actor_draw(Game_Play* game_play, Actor* actor) {
    FaultClient faultClient;
    Lights* light;

    Fault_AddClient(&faultClient, func_80056380_jp, actor, "Actor_draw");

    //! FAKE
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}

    OPEN_DISPS(game_play->state.gfxCtx);

    light = Global_light_read(&game_play->lightCtx, game_play->state.gfxCtx);
    LightsN_list_check(light, game_play->lightCtx.listHead,
                       (actor->flags & ACTOR_FLAG_400000) ? NULL : &actor->world.pos);
    LightsN_disp(light, game_play->state.gfxCtx);

    Matrix_softcv3_load(actor->world.pos.x, actor->world.pos.y + actor->shape.unk_08 * actor->scale.y,
                        actor->world.pos.z, &actor->shape.rot);
    Matrix_scale(actor->scale.x, actor->scale.y, actor->scale.z, MTXMODE_APPLY);

    {
        void* segment = game_play->unk_0110[(void)0, actor->unk_026].segment;

        gSegments[6] = (uintptr_t)OS_PHYSICAL_TO_K0(segment);

        gSPSegment(POLY_OPA_DISP++, 0x06, segment);
        gSPSegment(POLY_XLU_DISP++, 0x06, segment);
        gSPSegment(UNK_2C0_DISP++, 0x06, segment);
    }

    actor->draw(actor, game_play);

    if (actor->shape.unk_0C != NULL) {
        actor->shape.unk_0C(actor, light, game_play);
    }

    CLOSE_DISPS(game_play->state.gfxCtx);

    Fault_RemoveClient(&faultClient);
}

s32 Actor_draw_actor_no_culling_check(Actor* actor) {
    return Actor_draw_actor_no_culling_check2(actor, &actor->projectedPos, actor->projectedW);
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

        if (((fabsf(arg1->x) - actor->uncullZoneScale) * var_fa1) < 1.0f) {
            if (((arg1->y + actor->uncullZoneDownward) * var_fa1) > -1.0f) {
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
        actor->flags |= ACTOR_FLAG_40;
    } else {
        actor->flags &= ~ACTOR_FLAG_40;
    }
}

void Actor_delete_check(Actor* actor, Game_Play* game_play) {
    if ((actor->flags & (ACTOR_FLAG_40 | ACTOR_FLAG_20 | ACTOR_FLAG_10)) || (actor->fgName == 0)) {
        return;
    }

    if ((actor->unk_008 < 0) || (actor->unk_009 < 0)) {
        return;
    }

    if ((actor->unk_008 == game_play->unk_00E4) && (actor->unk_009 == game_play->unk_00E5)) {
        return;
    }

    Actor_delete(actor);
}

void Actor_info_ct(Game_Play* play2, ActorInfo* actorInfo, ActorEntry* actorEntry) {
    Game_Play* game_play = play2;
    Actor* temp_v0;
    ActorOverlay* var_v0;
    ActorEntry* var_s0_2;
    s16* var_s0;
    s32 var_s1;

    bzero(actorInfo, sizeof(ActorInfo));

    actor_dlftbls_init();
    Matrix_copy_MtxF(&game_play->billboardMtxF, &MtxF_clear);
    Matrix_copy_MtxF(&game_play->viewProjectionMtxF, &MtxF_clear);

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
        Actor_info_make_actor(actorInfo, game_play, common_data.unk_107B6, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1, 0, -1,
                              -1, -1);
    }
    common_data.unk_107B6 = 0xC9;

label:

    temp_v0 = Actor_info_make_actor(actorInfo, game_play, actorEntry->id, actorEntry->pos.x, actorEntry->pos.y,
                                    actorEntry->pos.z, actorEntry->rot.x, actorEntry->rot.y, actorEntry->rot.z, -1, -1,
                                    -1, 0, actorEntry->params, -1, -1);
    if (temp_v0 != NULL) {
        temp_v0->world.pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(temp_v0->world.pos, 0.0f);
        mFI_SetBearActor(game_play, temp_v0->world.pos, 0);
    }

    if (common_data.unk_1014E != 0) {
        Actor_info_make_actor(actorInfo, game_play, common_data.unk_1014E, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1, 0, -1,
                              -1, -1);
    }

    if (game_play->unk_1EA6 != 0) {
        var_s0 = game_play->unk_1EB0;

        for (var_s1 = 0; var_s1 < game_play->unk_1EA6; var_s1++) {
            Actor_info_make_actor(&game_play->actorInfo, game_play, *var_s0, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1, 0,
                                  -1, -1, -1);
            var_s0 += 1;
        }
        game_play->unk_1EA6 = 0;
    }

    mSc_regist_initial_exchange_bank(game_play);

    if (game_play->unk_1EA5 != 0) {
        var_s0_2 = game_play->unk_1EAC;
        for (var_s1 = 0; var_s1 < game_play->unk_1EA5; var_s1++) {
            Actor_info_make_actor(&game_play->actorInfo, game_play, var_s0_2->id, var_s0_2->pos.x, var_s0_2->pos.y,
                                  var_s0_2->pos.z, var_s0_2->rot.x, var_s0_2->rot.y, var_s0_2->rot.z, -1, -1, -1, 0,
                                  var_s0_2->params, -1, -1);
            var_s0_2 += 1;
        }
        game_play->unk_1EA5 = 0;
    }
}

void Actor_info_dt(ActorInfo* actorInfo, Game_Play* game_play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(actorInfo->actorLists); i++) {
        Actor* actor = actorInfo->actorLists[i].head;

        while (actor != NULL) {
            Actor_info_delete(actorInfo, actor, game_play);
            actor = actorInfo->actorLists[i].head;
        }
    }

    actor_dlftbls_cleanup();
}

void Actor_info_call_actor(Game_Play* game_play, ActorInfo* actorInfo) {
    s32 pad[1] UNUSED;
    ActorPart part;
    Player* player;

    player = get_player_actor_withoutCheck(game_play);
    func_8008E5F4_jp(player->actor.world.pos);

    for (part = 0; part < ACTOR_PART_MAX; part++) {
        Actor* actor;
        Actor* next;

        for (actor = actorInfo->actorLists[part].head; actor != NULL; actor = next) {
            game_play->state.unk_9C = actor->name;
            game_play->state.unk_9D = 0x97;

            if (actor->world.pos.y < -25000.0f) {
                actor->world.pos.y = -25000.0f;
            }

            if (actor->ct != NULL) {
                if (Actor_data_bank_dma_end_check(actor, game_play) == 1) {
                    gSegments[6] = (uintptr_t)OS_K0_TO_PHYSICAL(game_play->unk_0110[actor->unk_026].segment);

                    game_play->state.unk_9D = 0x98;
                    actor->ct(actor, game_play);
                    game_play->state.unk_9D = 0x99;
                    actor->ct = NULL;
                }
                next = actor->next;
            } else if (Actor_data_bank_dma_end_check(actor, game_play) == 0) {
                game_play->state.unk_9D = 0x9A;
                Actor_delete(actor);
                game_play->state.unk_9D = 0x9B;
                next = actor->next;
            } else if (actor->update == NULL) {
                if (!actor->isDrawn) {
                    game_play->state.unk_9D = 0x9C;
                    next = Actor_info_delete(&game_play->actorInfo, actor, game_play);
                    game_play->state.unk_9D = 0x9D;
                } else {
                    game_play->state.unk_9D = 0x9E;
                    Actor_dt(actor, game_play);
                    game_play->state.unk_9D = 0x9F;
                    next = actor->next;
                }
            } else {
                game_play->state.unk_9D = 0xA0;
                xyz_t_move(&actor->prevPos, &actor->world.pos);

                actor->xzDistToPlayer = search_position_distanceXZ(&actor->world.pos, &player->actor.world.pos);
                actor->playerHeightRel = player->actor.world.pos.y - actor->world.pos.y;

                actor->xyzDistToPlayerSq = SQ(actor->xzDistToPlayer) + SQ(actor->playerHeightRel);
                actor->yawTowardsPlayer = search_position_angleY(&actor->world.pos, &player->actor.world.pos);

                actor->flags &= ~ACTOR_FLAG_1000000;
                if ((actor->flags & (ACTOR_FLAG_40 | ACTOR_FLAG_10)) || (actor->part == ACTOR_PART_NPC)) {
                    gSegments[6] = (uintptr_t)OS_K0_TO_PHYSICAL(game_play->unk_0110[actor->unk_026].segment);
                    game_play->state.unk_9D = 0xA1;
                    actor->update(actor, game_play);
                    game_play->state.unk_9D = 0xA2;
                }

                CollisionCheck_Status_Clear(&actor->colStatus);
                next = actor->next;
            }
        }
    }

    game_play->state.unk_9D = 0xA3;
}

void Actor_info_draw_actor(Game_Play* game_play, ActorInfo* actorInfo) {
    Game_Play_unk_2208 temp_s4 = game_play->unk_2208;
    ActorListEntry* actorEntry = actorInfo->actorLists;
    ActorPart part = 0;

    if (1) {}

    for (; part < ACTOR_PART_MAX; part++, actorEntry++) {
        Actor* actor;

        for (actor = actorEntry->head; actor != NULL; actor = actor->next) {
            s32 temp;

            Skin_Matrix_PrjMulVector(&game_play->viewProjectionMtxF, &actor->world.pos, &actor->projectedPos,
                                     &actor->projectedW);
            Actor_cull_check(actor);

            temp = temp_s4(actor, game_play);
            actor->isDrawn = false;

            if (temp != 0) {
                continue;
            }

            if ((actor->ct != NULL) || (actor->draw == NULL)) {
                continue;
            }

            if (actor->flags & (ACTOR_FLAG_40 | ACTOR_FLAG_20)) {
                if (!(actor->flags & ACTOR_FLAG_80) && (actor->unk_148 == 0) && (actor->unk_149 == 0)) {
                    Actor_draw(game_play, actor);
                    actor->isDrawn = true;
                }
            } else {
                Actor_delete_check(actor, game_play);
            }
        }
    }

    if (debug_mode->r[0x380] == 0) {
        Light_list_point_draw(game_play);
    }
}

void Actor_info_part_new(ActorInfo* actorInfo, Actor* actor, u8 category) {
    Actor* temp_v1;

    actor->part = category;

    actorInfo->unk_00++;

    actorInfo->actorLists[category].unk_0++;
    temp_v1 = actorInfo->actorLists[category].head;
    if (temp_v1 != NULL) {
        temp_v1->prev = actor;
    }

    actorInfo->actorLists[category].head = actor;
    actor->next = temp_v1;
}

Actor* Actor_info_part_delete(ActorInfo* actorInfo, Actor* actor) {
    Actor* newHead;

    actorInfo->unk_00--;

    actorInfo->actorLists[actor->part].unk_0--;

    if (actor->prev != NULL) {
        actor->prev->next = actor->next;
    } else {
        actorInfo->actorLists[actor->part].head = actor->next;
    }

    newHead = actor->next;
    if (newHead != NULL) {
        newHead->prev = actor->prev;
    }

    actor->prev = NULL;
    actor->next = NULL;

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
        switch (ACTOR_FGNAME_GET_F000(fgName)) {
            case FGNAME_F000_D:
            case FGNAME_F000_E:
                common_data.unk_1004C->unk_08();
                break;

            case FGNAME_F000_5:
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

s32 func_80057940_jp(ActorProfile** profileP, ActorOverlay* overlayEntry, const struct_801161E8_jp* arg2,
                     size_t overlaySize, u16 fgName) {
    if (overlayEntry->vramStart == NULL) {
        *profileP = overlayEntry->profile;
    } else {
        if (overlayEntry->loadedRamAddr == NULL) {
            switch (ACTOR_FGNAME_GET_F000(fgName)) {
                case FGNAME_F000_D:
                case FGNAME_F000_E:
                    if (common_data.unk_1004C != NULL) {
                        common_data.unk_1004C->unk_04(overlayEntry, arg2, overlaySize, fgName);
                    } else {
                        overlayEntry->loadedRamAddr = NULL;
                    }
                    break;

                case FGNAME_F000_5:
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

            ovlmgr_Load(overlayEntry->vromStart, overlayEntry->vromEnd, overlayEntry->vramStart, overlayEntry->vramEnd,
                        overlayEntry->loadedRamAddr);
            overlayEntry->numLoaded = 0;
        }

        *profileP = (void*)(uintptr_t)((overlayEntry->profile != NULL)
                                           ? (void*)((uintptr_t)overlayEntry->profile -
                                                     (intptr_t)((uintptr_t)overlayEntry->vramStart -
                                                                (uintptr_t)overlayEntry->loadedRamAddr))
                                           : NULL);
    }

    return 1;
}

// this function may be Actor_data_bank_regist_check_npc
s32 func_80057A8C_jp(s32* arg0, ActorProfile* profile UNUSED, ActorOverlay* overlayEntry, Game_Play* game_play,
                     u16 fgName) {
    s32 pad UNUSED;
    s16 sp92;
    s16 sp90;
    s32 temp_v0;
    s32 ret;

    ret = 1;

    {
        CommonData_unk_1004C_unk_14_arg0 sp24;

        common_data.unk_1004C->unk_14(&sp24, fgName);

        sp92 = sp24.unk_00;
        sp90 = sp24.unk_02;
    }

    *arg0 = mSc_bank_regist_check(game_play->unk_0110, sp92);
    temp_v0 = mSc_bank_regist_check(game_play->unk_0110, sp90);

    if ((*arg0 < 0) || (temp_v0 < 0)) {
        if (*arg0 >= 0) {
            sp92 = 0;
        }
        if (temp_v0 >= 0) {
            sp90 = 0;
        }
        common_data.unk_1004C->unk_EC(game_play->unk_0110, sp92, sp90);
        actor_free_check(overlayEntry, fgName);
        ret = 0;
    }
    return ret;
}

s32 func_80057B70_jp(s32* arg0, ActorProfile* profile, ActorOverlay* overlayEntry, Game_Play* game_play, u16 fgName) {
    s32 pad UNUSED;
    s32 ret = 1;

    *arg0 = mSc_bank_regist_check(game_play->unk_0110, profile->objectId);

    if (*arg0 == -1) {
        func_800C6144_jp(game_play->unk_0110, profile->objectId);
        actor_free_check(overlayEntry, fgName);
        ret = 0;
    }

    return ret;
}

s32 Actor_data_bank_regist_check(s32* arg0, ActorProfile* profile, ActorOverlay* overlayEntry, Game_Play* game_play,
                                 u16 fgName) {
    s32 var_v1 = 1;

    if (*arg0 == -1) {
        if (profile->part == ACTOR_PART_NPC) {
            var_v1 = func_80057A8C_jp(arg0, profile, overlayEntry, game_play, fgName);
        } else {
            var_v1 = func_80057B70_jp(arg0, profile, overlayEntry, game_play, fgName);
        }
    }
    return var_v1;
}

s32 Actor_malloc_actor_class(Actor** actorP, ActorProfile* profile, ActorOverlay* overlayEntry,
                             const struct_801161E8_jp* arg3, u16 fgName) {
    CommonData_unk_1004C_unk_14_arg0 sp24;

    switch (ACTOR_FGNAME_GET_F000(fgName)) {
        case FGNAME_F000_D:
        case FGNAME_F000_E:
            *actorP = common_data.unk_1004C->unk_0C(profile->instanceSize, arg3, 1);

            //! FAKE
            if ((profile != NULL) && (profile != NULL) && (profile != NULL)) {}

            common_data.unk_1004C->unk_14(&sp24, fgName);
            break;

        case FGNAME_F000_5:
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

void Actor_init_actor_class(Actor* actor, ActorProfile* profile, ActorOverlay* overlayEntry, Game_Play* game_play,
                            s32 arg4, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s8 argB, s8 argC, s16 argD,
                            u16 fgName, s16 params) {
    mem_clear(actor, profile->instanceSize, 0);

    actor->overlayEntry = overlayEntry;

    actor->name = profile->name;
    actor->flags = profile->flags;

    actor->unk_026 = arg4;

    actor->ct = profile->ct;
    actor->dt = profile->dt;
    actor->update = profile->update;
    actor->draw = profile->draw;
    actor->save = profile->save;

    actor->params = params;

    actor->unk_004 = game_play->unk_00E0;

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

extern const struct_801161E8_jp RO_801161E8_jp;
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_actor/RO_801161E8_jp.s")

Actor* Actor_info_make_actor(ActorInfo* actorInfo, Game_Play* game_play, s16 actorId, f32 x, f32 y, f32 z, s16 rotX,
                             s16 rotY, s16 rotZ, s8 arg9, s8 argA, s16 argB, u16 fgName, s16 params, s8 argE,
                             s32 argF) {
    u16* new_var = &fgName;
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
    if (Actor_data_bank_regist_check(&argF, profile, temp_s0, game_play, fgName) == 0) {
        return NULL;
    }
    if (Actor_malloc_actor_class(&sp68, profile, temp_s0, &RO_801161E8_jp, fgName) == 0) {
        return NULL;
    }

    temp_s0->numLoaded++;
    Actor_init_actor_class(sp68, profile, temp_s0, game_play, argF, x, y, z, rotX, rotY, rotZ, arg9, argA, argB, fgName,
                           params);

    Actor_info_part_new(actorInfo, sp68, profile->part);

    mNpc_SetNpcinfo(sp68, argE);

    {
        uintptr_t segmentTemp;

        segmentTemp = gSegments[6];
        Actor_ct(sp68, game_play);
        gSegments[6] = segmentTemp;
    }

    return sp68;
}

Actor* Actor_info_make_child_actor(ActorInfo* actorInfo, Actor* arg1, Game_Play* game_play, s16 actorId, f32 x, f32 y,
                                   f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 argA, u16 fgName, s16 params, s32 argD) {
    Actor* temp_v0 = Actor_info_make_actor(actorInfo, game_play, actorId, x, y, z, rotX, rotY, rotZ, -1, -1, argA,
                                           fgName, params, -1, argD);

    if (temp_v0 != NULL) {
        arg1->child = temp_v0;
        temp_v0->parent = arg1;
    }

    return temp_v0;
}

void restore_fgdata(Actor* actor, Game_Play* game_play UNUSED) {
    Vec3f sp34;

    if ((actor->fgName == 0) || (actor->unk_00A != -1)) {
        return;
    }

    if ((actor->unk_008 < 0) || (actor->unk_009 < 0)) {
        return;
    }

    switch (ACTOR_FGNAME_GET_F000(actor->fgName)) {
        case FGNAME_F000_8:
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

s32 restore_flag[ACTOR_PART_MAX] = {
    1, // ACTOR_PART_0
    1, // ACTOR_PART_1
    0, // ACTOR_PART_PLAYER
    0, // ACTOR_PART_NPC
    0, // ACTOR_PART_4
    0, // ACTOR_PART_5
    0, // ACTOR_PART_6
    0, // ACTOR_PART_7
};

void restore_fgdata_one(Actor* actor, Game_Play* game_play) {
    if (restore_flag[actor->part] == 1) {
        restore_fgdata(actor, game_play);
    } else if (actor->unk_003 == 1) {
        restore_fgdata(actor, game_play);
    }
}

void restore_fgdata_all(Game_Play* game_play) {
    ActorInfo* actorInfo = &game_play->actorInfo;
    ActorPart part;

    for (part = 0; part < ACTOR_PART_MAX; part++) {
        Actor* actor;

        if (restore_flag[part] == 1) {
            for (actor = actorInfo->actorLists[part].head; actor != NULL; actor = actor->next) {
                restore_fgdata(actor, game_play);
            }
        } else {
            for (actor = actorInfo->actorLists[part].head; actor != NULL; actor = actor->next) {
                if (actor->unk_003 == 1) {
                    restore_fgdata(actor, game_play);
                }
            }
        }
    }
}

void Actor_info_save_actor(Game_Play* game_play) {
    ActorInfo* actorInfo = &game_play->actorInfo;
    ActorPart part;

    for (part = 0; part < ACTOR_PART_MAX; part++) {
        Actor* actor;

        for (actor = actorInfo->actorLists[part].head; actor != NULL; actor = actor->next) {
            if (actor->save != NULL) {
                actor->save(actor, game_play);
                actor->save = NULL;
            }
        }
    }

    restore_fgdata_all(game_play);
}

Actor* Actor_info_delete(ActorInfo* actorInfo, Actor* actor, Game_Play* game_play) {
    Actor* newHead;
    s32 pad UNUSED;
    ActorOverlay* overlayEntry;
    s32 fgName = actor->fgName;

    overlayEntry = actor->overlayEntry;

    restore_fgdata_one(actor, game_play);
    Actor_dt(actor, game_play);

    newHead = Actor_info_part_delete(actorInfo, actor);

    switch (ACTOR_FGNAME_GET_F000(fgName)) {
        case FGNAME_F000_D:
        case FGNAME_F000_E:
            common_data.unk_1004C->unk_10(actor);
            break;

        case FGNAME_F000_5:
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

Actor* Actor_info_name_search_sub(Actor* actor, s16 name) {
    for (; actor != NULL; actor = actor->next) {
        if (name == actor->name) {
            break;
        }
    }
    return actor;
}

Actor* Actor_info_name_search(ActorInfo* actorInfo, s16 name, ActorPart part) {
    Actor* head = actorInfo->actorLists[part].head;

    if (head != NULL) {
        return Actor_info_name_search_sub(head, name);
    }
    return NULL;
}

Actor* Actor_info_fgName_search_sub(Actor* actor, u16 fgName) {
    for (; actor != NULL; actor = actor->next) {
        if (actor->fgName == fgName) {
            break;
        }
    }

    return actor;
}

Actor* Actor_info_fgName_search(ActorInfo* actorInfo, u16 fgName, ActorPart part) {
    Actor* head = actorInfo->actorLists[part].head;

    if (head != NULL) {
        return Actor_info_fgName_search_sub(head, fgName);
    }
    return NULL;
}

// unused
void Part_Break_init(Part_Break* partBreak, s32 count, s32 arg2 UNUSED) {
    size_t matricesSize;
    size_t dListsSize;
    size_t objectIdsSize;

    matricesSize = (count + 1) * sizeof(MtxF);
    partBreak->matrices = zelda_malloc(matricesSize);
    if (partBreak->matrices == NULL) {
        goto cleanup;
    }

    dListsSize = (count + 1) * sizeof(Gfx*);
    partBreak->dLists = zelda_malloc(dListsSize);
    if (partBreak->dLists == NULL) {
        goto cleanup;
    }

    objectIdsSize = (count + 1) * sizeof(s16);
    partBreak->objectIds = zelda_malloc(objectIdsSize);
    if (partBreak->objectIds == NULL) {
        goto cleanup;
    }

    mem_clear(partBreak->matrices, matricesSize, 0);
    mem_clear(partBreak->dLists, dListsSize, 0);
    mem_clear(partBreak->objectIds, objectIdsSize, 0);

    partBreak->val = 1;
    return;

cleanup:
    if (partBreak->matrices != NULL) {
        zelda_free(partBreak->matrices);
    }
    if (partBreak->dLists != NULL) {
        zelda_free(partBreak->dLists);
    }
    if (partBreak->objectIds != NULL) {
        zelda_free(partBreak->objectIds);
    }
}

Mtx B_8011B850_jp;

Gfx* HiliteReflect_new(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx, Gfx* gfx, Hilite** hilite) {
    LookAt* sp64 = GRAPH_ALLOC(gfxCtx, sizeof(LookAt));
    f32 var_fa1 = ((eye->x == object->x) && (eye->z == object->z)) ? (eye->x + 0.001f) : eye->x;

    *hilite = GRAPH_ALLOC(gfxCtx, sizeof(Hilite));

    guLookAtHilite(&B_8011B850_jp, sp64, *hilite, var_fa1, eye->y, eye->z, object->x, object->y, object->z, 0.0f, 1.0f,
                   0.0f, lightDir->x, lightDir->y, lightDir->z, lightDir->x, lightDir->y, lightDir->z, 0x10, 0x10);

    gSPLookAt(gfx++, sp64);

    gDPPipeSync(gfx++);
    gDPSetHilite1Tile(gfx++, 1, *hilite, 0x10, 0x10);

    return gfx;
}

Hilite* HiliteReflect_init(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx) {
    Hilite* hilite;

    OPEN_DISPS(gfxCtx);

    POLY_OPA_DISP = HiliteReflect_new(object, eye, lightDir, gfxCtx, POLY_OPA_DISP, &hilite);

    CLOSE_DISPS(gfxCtx);

    return hilite;
}

Hilite* HiliteReflect_xlu_init(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx) {
    Hilite* hilite;

    OPEN_DISPS(gfxCtx);

    POLY_XLU_DISP = HiliteReflect_new(object, eye, lightDir, gfxCtx, POLY_XLU_DISP, &hilite);

    CLOSE_DISPS(gfxCtx);

    return hilite;
}

Hilite* HiliteReflect_light_init(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx) {
    Hilite* hilite;

    OPEN_DISPS(gfxCtx);

    LIGHT_DISP = HiliteReflect_new(object, eye, lightDir, gfxCtx, LIGHT_DISP, &hilite);

    CLOSE_DISPS(gfxCtx);

    return hilite;
}

Hilite* Setpos_HiliteReflect_init(Vec3f* object, Game_Play* game_play) {
    Vec3f sp24;

    sp24.x = game_play->kankyo.unk_02;
    sp24.y = game_play->kankyo.unk_03;
    sp24.z = game_play->kankyo.unk_04;
    return HiliteReflect_init(object, &game_play->unk_1938.unk_028, &sp24, game_play->state.gfxCtx);
}

Hilite* Setpos_HiliteReflect_xlu_init(Vec3f* object, Game_Play* game_play) {
    Vec3f sp24;

    sp24.x = game_play->kankyo.unk_02;
    sp24.y = game_play->kankyo.unk_03;
    sp24.z = game_play->kankyo.unk_04;
    return HiliteReflect_xlu_init(object, &game_play->unk_1938.unk_028, &sp24, game_play->state.gfxCtx);
}

Hilite* Setpos_HiliteReflect_light_init(Vec3f* object, Game_Play* game_play) {
    Vec3f sp24;

    sp24.x = game_play->kankyo.unk_02;
    sp24.y = game_play->kankyo.unk_03;
    sp24.z = game_play->kankyo.unk_04;
    return HiliteReflect_xlu_init(object, &game_play->unk_1938.unk_028, &sp24, game_play->state.gfxCtx);
}
