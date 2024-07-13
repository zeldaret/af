#include "ac_fuusen.h"
#include "m_actor_dlftbls.h"
#include "m_actor_shadow.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "libc/math.h"
#include "macros.h"
#include "m_handbill.h"
#include "m_field_info.h"
#include "m_debug_display.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "683030.h"
#include "audio.h"
#include "code_variables.h"
#include "m_name_table.h"

#include "objects/act_balloon/act_balloon.h"

#define THIS ((Fuusen*)thisx)

void aFSN_actor_ct(Actor* thisx, Game_Play* game_play);
void aFSN_actor_dt(Actor* thisx, Game_Play* game_play);
void aFSN_actor_move(Actor* thisx, Game_Play* game_play);
void aFSN_actor_draw(Actor* thisx, Game_Play* game_play);
void aFSN_setupAction(Fuusen* this, s32 processIndex, Game_Play* game_play);

ActorProfile Fuusen_Profile = {
    /* */ ACTOR_FUUSEN,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10,
    /* */ 0x0000,
    /* */ OBJECT_ACT_BALLOON,
    /* */ sizeof(Fuusen),
    /* */ aFSN_actor_ct,
    /* */ aFSN_actor_dt,
    /* */ aFSN_actor_move,
    /* */ aFSN_actor_draw,
    /* */ NULL,
};

void aFSN_actor_ct(Actor* thisx, Game_Play* game_play) {
    Fuusen* this = THIS;
    SkeletonInfoR* skeletonInfo = &this->skeletonInfo;
    xyz_t Init_Size = { 0.01f, 0.01f, 0.01f };
    f32 balloonGroundY = mCoBG_GetBalloonGroundY(&this->actor.world.pos);

    this->escapeTimer = 1000;
    cKF_SkeletonInfo_R_ct(skeletonInfo, &cKF_bs_r_act_balloon, &cKF_ba_r_act_balloon, this->jointTable,
                          this->morphTable);
    cKF_SkeletonInfo_R_init_standard_repeat(skeletonInfo, Lib_SegmentedToVirtual(&cKF_ba_r_act_balloon), NULL);
    Shape_Info_init(&this->actor, 0.0f, mAc_ActorShadowCircle, 10.0f, 10.0f);
    this->actor.shape.drawShadow = 0;
    cKF_SkeletonInfo_R_play(skeletonInfo);
    skeletonInfo->frameControl.speed = 1.0f;
    xyz_t_move(&this->actor.scale, &Init_Size);
    this->actor.world.pos.y = balloonGroundY + 200.0f;
    this->heightOffset = 110.0f;
    this->segment = game_play->objectExchangeBank.status[this->actor.unk_026].segment;
    this->actor.update = aFSN_actor_move;
    aFSN_setupAction(this, FSN_PROCESS_BIRTH, game_play);
}

void aFSN_actor_dt(Actor* thisx, UNUSED Game_Play* game_play) {
    Fuusen* this = THIS;

    if (this->shouldLookUp) {
        Balloon_look_up();
    } else {
        Balloon_kill();
    }
}

void aFSN_birth_init(Fuusen* this, Game_Play* game_play) {
    static s32 data_index_data[16] = {
        0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 0,
    };
    static xyz_t birth_pos_data[8] = {
        { 1600.0f, 100.0f, 500.0f },  { 500.0f, 100.0f, 500.0f },   { 500.0f, 100.0f, 1600.0f },
        { 500.0f, 100.0f, 4620.0f },  { 1600.0f, 100.0f, 4620.0f }, { 3980.0f, 100.0f, 4620.0f },
        { 3980.0f, 100.0f, 1600.0f }, { 3980.0f, 100.0f, 500.0f },
    };
    static xyz_t birth_pos_random_data[8] = {
        { 1280.0f, 100.0f, 0.0f }, { 960.0f, 100.0f, 960.0f },   { 0.0f, 100.0f, 1920.0f }, { 960.0f, 100.0f, -960.0f },
        { 1280.0f, 100.0f, 0.0f }, { -960.0f, 100.0f, -960.0f }, { 0.0f, 100.0f, 1920.0f }, { -960.0f, 100.0f, 960.0f },
    };
    s16 rotVar;
    f32 rand;
    s32 randXOrZ;
    f32 balloonGroundY = mCoBG_GetBalloonGroundY(&this->actor.world.pos);
    f32 xPos;
    f32 zPos;

    this->actor.world.rot.y = mEnv_GetWindAngleS();
    rotVar = this->actor.world.rot.y & 0xF000;
    this->dataIndex = (rotVar >> 0xC) & 0xF;
    this->dataIndex = data_index_data[this->dataIndex];
    xyz_t_move(&this->actor.world.pos, &birth_pos_data[this->dataIndex]);
    this->actor.world.pos.y = (f32)(balloonGroundY + 200.0f);
    this->colorIndex = game_play->unk_1EA0 % 5;
    this->birthTimer = 10;
    randXOrZ = FSN_RAND_X;
    if ((birth_pos_random_data[this->dataIndex].x != 0.0f) && (birth_pos_random_data[this->dataIndex].z != 0.0f)) {
        randXOrZ = game_play->unk_1EA0 & 1;
    } else if (birth_pos_random_data[this->dataIndex].z != 0.0f) {
        randXOrZ = FSN_RAND_Z;
    }
    if (randXOrZ == FSN_RAND_X) {
        if (birth_pos_random_data[this->dataIndex].x != 0.0f) {
            rand = fqrand();
            xPos = fabsf(birth_pos_random_data[this->dataIndex].x);
            if (birth_pos_random_data[this->dataIndex].x > 0.0f) {
                this->actor.world.pos.x += xPos * rand;
            } else {
                this->actor.world.pos.x -= xPos * rand;
            }
        }
    } else {
        if (birth_pos_random_data[this->dataIndex].z != 0.0f) {
            rand = fqrand();
            zPos = fabsf(birth_pos_random_data[this->dataIndex].z);
            if (birth_pos_random_data[this->dataIndex].z > 0.0f) {
                this->actor.world.pos.z += zPos * rand;
            } else {
                this->actor.world.pos.z -= zPos * rand;
            }
        }
    }
}

void aFSN_moving_init(Fuusen* this, UNUSED Game_Play* game_play) {
    this->unk_1A4 = false;
}

void aFSN_wood_stop_init(Fuusen* this, UNUSED Game_Play* game_play) {
    this->escapeTimer = 9000 + 777;
    this->actor.speed = 0.0f;
    sAdo_OngenTrgStart(0x402, &this->actor.world.pos);
}

void aFSN_escape_init(Fuusen* this, Game_Play* game_play) {
    Player* player = get_player_actor_withoutCheck(game_play);
    f32 xDist = player->actor.world.pos.x - this->actor.world.pos.x;
    f32 zDist = player->actor.world.pos.z - this->actor.world.pos.z;

    this->unk_18C = 0;
    this->actor.terminalVelocity = 5.0f;
    this->actor.gravity = 0.5f;
    this->shouldLookUp = false;
    if (this->escapeTimer == 777) {
        this->unk_18C = 1;
        if (sqrtf(SQ(xDist) + SQ(zDist)) < 640.0f) {
            this->shouldLookUp = true;
        }
    }
}

Color_RGBA8 balloon_prim_data[5] = {
    { 255, 210, 200, 255 }, { 200, 230, 200, 255 }, { 255, 250, 200, 255 },
    { 220, 255, 200, 255 }, { 240, 210, 255, 255 },
};

Color_RGBA8 balloon_env_data[5] = {
    { 255, 40, 0, 255 }, { 0, 180, 255, 255 }, { 255, 200, 0, 255 }, { 100, 255, 0, 255 }, { 200, 30, 255, 255 },
};

void aFSN_birth(Actor* thisx, Game_Play* game_play) {
    Fuusen* this = THIS;
    aFSN_setupAction(this, FSN_PROCESS_MOVING, game_play);
}

void aFSN_moving(Actor* thisx, Game_Play* game_play) {
    static Vec2s senkou_check_data[3] = {
        { -1, -2500 },
        { 0, 0 },
        { 0, 2500 },
    };
    Fuusen* this = THIS;
    f32 balloonGroundY = mCoBG_GetBalloonGroundY(&this->actor.world.pos) + this->heightOffset;
    UNUSED UNK_TYPE1 pad[0x4];
    u16* unitFG;
    xyz_t screenPos;
    f32 distX;
    f32 distY;
    f32 distZ;
    s32 i;
    s16 yRot;

    if (this->escapeTimer > 0) {
        this->escapeTimer--;
    } else {
        if ((this->actor.world.pos.x <= 660.0f) || (this->actor.world.pos.x >= 3820.0f) ||
            (this->actor.world.pos.z <= 660.0f) || (this->actor.world.pos.z >= 4460.0f)) {
            this->escapeTimer = 777;
            aFSN_setupAction(this, FSN_PROCESS_ESCAPE, game_play);
            return;
        } else if ((this->actor.world.pos.x <= 2440.0f) && (this->actor.world.pos.x >= 2040.0f) &&
                   (this->actor.world.pos.z <= 960.0f) && (this->actor.world.pos.z >= 800.0f)) {
            this->escapeTimer = 777;
            aFSN_setupAction(this, FSN_PROCESS_ESCAPE, game_play);
            return;
        }
    }
    this->windPower = mEnv_GetWindPowerF();
    this->heightAmplitudeCounter += 500;
    this->actor.speed = this->windPower * 0.5f + 1.0f;
    add_calc(&this->actor.world.pos.y, (sin_s(this->heightAmplitudeCounter) * 10.0f) + balloonGroundY, 0.3f, 1.0f,
             0.0f);
    Game_play_Projection_Trans(game_play, &this->actor.world.pos, &screenPos);
    if (!(screenPos.x < -40.0f) && !(screenPos.x > 360.0f) && !(screenPos.y < -40.0f) && !(screenPos.y > 280.0f)) {
        mCoBG_BgCheckControll(NULL, &this->actor, 12.0f, 0, 0, 0, 0);
        if (this->actor.colCheck.colResult.hitWall & 1 || this->actor.colCheck.colResult.unk1 & 1) {
            this->heightOffset += 0.01f;
            if (this->heightOffset >= 300.0f) {
                this->heightOffset = 300.0f;
            }
        } else {
            if (this->heightOffset > 110.0f) {
                this->heightOffset -= 0.01f;
            }
        }
        unitFG = mFI_GetUnitFG(this->actor.world.pos);
        if ((unitFG != NULL) && ((*unitFG == TREE) || (*unitFG == TREE_APPLE_NOFRUIT_0) ||
                                 (*unitFG == TREE_ORANGE_NOFRUIT_0) || (*unitFG == TREE_PEACH_NOFRUIT_0) ||
                                 (*unitFG == TREE_PEAR_NOFRUIT_0) || (*unitFG == TREE_CHERRY_NOFRUIT_0) ||
                                 (*unitFG == TREE_APPLE_NOFRUIT_1) || (*unitFG == TREE_ORANGE_NOFRUIT_1) ||
                                 (*unitFG == TREE_PEACH_NOFRUIT_1) || (*unitFG == TREE_PEAR_NOFRUIT_1) ||
                                 (*unitFG == TREE_CHERRY_NOFRUIT_1) || (*unitFG == TREE_APPLE_NOFRUIT_2) ||
                                 (*unitFG == TREE_ORANGE_NOFRUIT_2) || (*unitFG == TREE_PEACH_NOFRUIT_2) ||
                                 (*unitFG == TREE_PEAR_NOFRUIT_2) || (*unitFG == TREE_CHERRY_NOFRUIT_2))) {
            mFI_Wpos2UtCenterWpos(&screenPos, this->actor.world.pos);
            screenPos.x -= 2.5f;
            screenPos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(this->actor.world.pos, 0.0f) + 97.5f;
            screenPos.z += 7.5f;
            distX = screenPos.x - this->actor.world.pos.x;
            distY = screenPos.y - this->actor.world.pos.y;
            distZ = screenPos.z - this->actor.world.pos.z;
            if ((sqrtf(SQ(distX) + SQ(distZ)) < 15.0f) && (sqrtf(SQ(distY)) < 15.0f)) {
                aFSN_setupAction(this, FSN_PROCESS_WOOD_STOP, game_play);
            }
        } else {
            if (!this->unk_1A4) {
            // FAKE
            dummy_label:
                for (i = 0; i < ARRAY_COUNT(senkou_check_data); i++) {
                    xyz_t_move(&screenPos, &this->actor.world.pos);
                    yRot = senkou_check_data[i].z + this->actor.world.rot.y;
                    screenPos.x += sin_s(yRot) * 80.0f;
                    screenPos.z += cos_s(yRot) * 80.0f;
                    unitFG = mFI_GetUnitFG(screenPos);
                    if ((unitFG != NULL) && ((*unitFG == TREE) || (*unitFG == TREE_APPLE_NOFRUIT_0) ||
                                             (*unitFG == TREE_ORANGE_NOFRUIT_0) || (*unitFG == TREE_PEACH_NOFRUIT_0) ||
                                             (*unitFG == TREE_PEAR_NOFRUIT_0) || (*unitFG == TREE_CHERRY_NOFRUIT_0) ||
                                             (*unitFG == TREE_APPLE_NOFRUIT_1) || (*unitFG == TREE_ORANGE_NOFRUIT_1) ||
                                             (*unitFG == TREE_PEACH_NOFRUIT_1) || (*unitFG == TREE_PEAR_NOFRUIT_1) ||
                                             (*unitFG == TREE_CHERRY_NOFRUIT_1) || (*unitFG == TREE_APPLE_NOFRUIT_2) ||
                                             (*unitFG == TREE_ORANGE_NOFRUIT_2) || (*unitFG == TREE_PEACH_NOFRUIT_2) ||
                                             (*unitFG == TREE_PEAR_NOFRUIT_2) || (*unitFG == TREE_CHERRY_NOFRUIT_2))) {
                        this->actor.world.rot.y = yRot;
                        this->unk_1A4 = true;
                        break;
                    }
                }
            }
            if (!this->unk_1A4) {
                this->actor.world.rot.y = mEnv_GetWindAngleS();
            }
        }
    }
}

void aFSN_wood_stop(Actor* thisx, Game_Play* game_play) {
    Fuusen* this = THIS;
    xyz_t pos;
    xyz_t posCopy;
    f32 distX;
    f32 distZ;

    this->escapeTimer--;
    if (this->escapeTimer <= 777) {
        this->escapeTimer = 777;
        aFSN_setupAction(this, FSN_PROCESS_ESCAPE, game_play);
    } else {
        mFI_Wpos2UtCenterWpos(&pos, this->actor.world.pos);
        xyz_t_move(&posCopy, &pos);
        pos.x -= 2.5f;
        pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(this->actor.world.pos, 0.0f) + 97.5f;
        pos.z += 7.5f;
        distX = this->actor.world.pos.x - pos.x;
        distZ = this->actor.world.pos.z - pos.z;
        if (sqrtf(SQ(distX) + SQ(distZ)) > 2.0f) {
            add_calc(&this->actor.world.pos.x, pos.x, 0.3f, 1.0f, 0.0f);
            add_calc(&this->actor.world.pos.y, pos.y, 0.3f, 1.0f, 0.0f);
            add_calc(&this->actor.world.pos.z, pos.z, 0.3f, 1.0f, 0.0f);
        } else if (mPlib_Check_tree_shaken_big(&posCopy)) {
            this->actor.shape.rot.z = 0;
            aFSN_setupAction(this, FSN_PROCESS_ESCAPE, game_play);
        } else if (mPlib_Check_tree_shaken_little(&posCopy)) {
            if (!(this->unk_18C & 2)) {
                this->actor.shape.rot.z = 500;
            } else {
                this->actor.shape.rot.z = 0;
            }
            this->unk_18C++;
        } else {
            this->actor.shape.rot.z = 0;
            this->unk_18C = 0;
        }
    }
}

void aFSN_escape(Actor* thisx, UNUSED Game_Play* game_play) {
    Fuusen* this = THIS;
    f32 balloonGroundY = mCoBG_GetBalloonGroundY(&this->actor.world.pos);

    if (this->unk_18C == 0) {
        xyz_t pos;
        s32 utX;
        s32 utZ;

        mFI_Wpos2UtCenterWpos(&pos, this->actor.world.pos);
        if ((common_data.clip.unk_074 != NULL) && (common_data.clip.unk_074->unk_38 != 0) &&
            mFI_Wpos2UtNum(&utX, &utZ, pos)) {
            common_data.clip.unk_074->unk_30(9500, utX, utZ, 1);
            this->unk_18C = 1;
        }
    }
    if (this->unk_18C == 1) {
        if (this->actor.world.pos.y > (balloonGroundY + 500.0f)) {
            Actor_delete(&this->actor);
        }
    }
}

void aFSN_setupAction(Fuusen* this, s32 processIndex, Game_Play* game_play) {
    static FuusenInitFunc init_proc[4] = {
        aFSN_birth_init,
        aFSN_moving_init,
        aFSN_wood_stop_init,
        aFSN_escape_init,
    };

    static FuusenActionFunc act_proc[4] = {
        aFSN_birth,
        aFSN_moving,
        aFSN_wood_stop,
        aFSN_escape,
    };

    this->processNum = processIndex;
    this->process = act_proc[processIndex];
    init_proc[processIndex](this, game_play);
}

// Original name unknown.
void func_80AADF10_jp(Fuusen* this, Game_Play* game_play) {
    UNUSED UNK_TYPE1 pad[0x4];
    void* segment;

    segment = game_play->objectExchangeBank.status[this->actor.unk_026].segment;
    if (this->segment != segment) {
        SkeletonInfoR* skeletonInfo = &this->skeletonInfo;
        skeletonInfo->skeleton = Lib_SegmentedToVirtual(&cKF_bs_r_act_balloon);
        skeletonInfo->animation = Lib_SegmentedToVirtual(&cKF_ba_r_act_balloon);
        this->segment = segment;
    }
}

void aFSN_actor_move(Actor* thisx, Game_Play* game_play) {
    Fuusen* this = THIS;
    UNUSED UNK_TYPE1 pad[0x8];

    func_80AADF10_jp(this, game_play);
    if (this->birthTimer == 0) {
        Actor_position_moveF(&this->actor);
    } else if (this->birthTimer > 0) {
        this->birthTimer--;
    }
    if (fuusen_DEBUG_mode_flag != 0) {
        Player* player = get_player_actor_withoutCheck(game_play);
        Debug_Display_new((sin_s(this->actor.yawTowardsPlayer + 0x8000) * 30.0f) + player->actor.world.pos.x,
                          player->actor.world.pos.y + 60.0f,
                          (cos_s(this->actor.yawTowardsPlayer + 0x8000) * 30.0f) + player->actor.world.pos.z, 0,
                          this->actor.yawTowardsPlayer + 0x8000, 0, 1.0f, 1.0f, 1.0f, 250, 100, 120, 128, 4,
                          game_play->state.gfxCtx);
    }
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
    this->process(&this->actor, game_play);
    fuusen_DEBUG_mode_flag = 0;
}

// Original name unknown.
Gfx* func_80AAE10C_jp(u8 red, u8 blue, u8 green, u8 alpha, Game_Play* game_play) {
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    Gfx* gfx = GRAPH_ALLOC(gfxCtx, 1);

    if (gfx) {
        gDPSetPrimColor(gfx, 0, 255, red, blue, green, alpha);
        gSPEndDisplayList(gfx + 1);
        return gfx;
    }
    return NULL;
}

extern Gfx present_DL_mode[];
extern Vtx present_DL_vtx[];

void aFSN_actor_draw(Actor* thisx, Game_Play* game_play) {
    static xyz_t offset0 = { 0.0f, 0.0f, 0.0f };
    Fuusen* this = THIS;
    s32 mtxIndex = game_play->state.frameCounter & 1;
    UNUSED UNK_TYPE1 pad[0x8];
    s16 objBankIndex;
    void* segment;
    Gfx* balloonGfx;

    objBankIndex = this->actor.unk_026;
    segment = game_play->objectExchangeBank.status[objBankIndex].segment;
    balloonGfx =
        func_80AAE10C_jp(balloon_prim_data[this->colorIndex].r, balloon_prim_data[this->colorIndex].g,
                         balloon_prim_data[this->colorIndex].b, balloon_prim_data[this->colorIndex].a, game_play);
    if ((balloonGfx != NULL) &&
        (!Camera2_CheckCullingMode() ||
         !Camera2_CheckEnterCullingArea(this->actor.world.pos.x, this->actor.world.pos.z, 60.0f))) {
        func_80AADF10_jp(this, game_play);
        Matrix_push();
        if ((this->processNum != FSN_PROCESS_ESCAPE) || (this->escapeTimer == 777) ||
            ((this->processNum == FSN_PROCESS_ESCAPE) && (this->unk_18C == 0))) {
            _texture_z_light_fog_prim(game_play->state.gfxCtx);
            OPEN_POLY_OPA_DISP(game_play->state.gfxCtx);
            Matrix_translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0);
            Matrix_scale(0.01f, 0.01f, 0.01f, 1);
            Matrix_RotateX(this->actor.shape.rot.x, MTXMODE_APPLY);
            Matrix_RotateZ(this->actor.shape.rot.z, MTXMODE_APPLY);
            Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
            gSPMatrix(__polyOpa++, _Matrix_to_Mtx_new(game_play->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(__polyOpa++, present_DL_mode);
            gSPDisplayList(__polyOpa++, present_DL_vtx);
            CLOSE_POLY_OPA_DISP(game_play->state.gfxCtx);
        }
        OPEN_DISPS(game_play->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x06, segment);
        gSPSegment(POLY_OPA_DISP++, 0x08, balloonGfx);
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, balloon_env_data[this->colorIndex].r, balloon_env_data[this->colorIndex].g,
                       balloon_env_data[this->colorIndex].b, balloon_env_data[this->colorIndex].a);
        CLOSE_DISPS(game_play->state.gfxCtx);
        Setpos_HiliteReflect_init(&this->actor.world.pos, game_play);
        cKF_Si3_draw_R_SV(game_play, &this->skeletonInfo, this->mtx[mtxIndex], NULL, NULL, &this->actor);
        mAc_ActorShadowDraw_ShadowDrawFlagOn(&this->actor, game_play, 0, offset0, 170.0f);
        Matrix_pull();
    }
}
