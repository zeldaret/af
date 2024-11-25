#include "ac_house_goki.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_actor_shadow.h"
#include "src/overlays/actors/player_actor/m_player.h"
#include "m_player_lib.h"
#include "audio.h"
#include "m_cockroach.h"
#include "m_collision_bg.h"
#include "m_rcp.h"
#include "m_field_info.h"

void aHG_actor_ct(Actor* thisx, Game_Play* game_play);
void aHG_actor_dt(Actor* thisx, Game_Play* game_play);
void aHG_actor_move(Actor* thisx, Game_Play* game_play);
void aHG_actor_draw(Actor* thisx, Game_Play* game_play);

void func_80A83930_jp(House_Goki* this, Game_Play* game_play);
void func_80A83994_jp(House_Goki* this, Game_Play* game_play);
void func_80A83A00_jp(House_Goki* this, Game_Play* game_play);

void func_80A83A24_jp(House_Goki* this, Game_Play* game_play);
void func_80A83D4C_jp(House_Goki* this, Game_Play* game_play);
void func_80A8401C_jp(House_Goki* this, Game_Play* game_play);

void aHG_setup_action(House_Goki* this, s32 processIndex, Game_Play* game_play);

ActorProfile House_Goki_Profile = {
    /* */ ACTOR_HOUSE_GOKI,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10,
    /* */ 0x0000,
    /* */ OBJECT_369,
    /* */ sizeof(House_Goki),
    /* */ aHG_actor_ct,
    /* */ aHG_actor_dt,
    /* */ aHG_actor_move,
    /* */ aHG_actor_draw,
    /* */ NULL,
};

static House_GokiActionFunc init_process[] = { func_80A83930_jp, func_80A83994_jp, func_80A83A00_jp };
static House_GokiActionFunc process[] = { func_80A83A24_jp, func_80A83D4C_jp, func_80A8401C_jp };
static s32 D_80A845DC_jp[] = { 0x060000C0, 0x06000188 };

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/aHG_actor_ct.s")
void aHG_actor_ct(Actor* thisx, Game_Play* game_play) {
    House_Goki* this = (House_Goki*)thisx;
    this->unk_190 = 0x1E;
    if (this->actor.params <= 0) {
        this->actor.params = 0;
        this->unk_190 = 0xFF;
    }
    this->actor.scale.x = 0.01f;
    this->actor.scale.y = 0.01f;
    this->actor.scale.z = 0.01f;
    Shape_Info_init(&this->actor, 0, mAc_ActorShadowCircle, 6.0f, 6.0f);
    xyz_t_move(&this->actor.home.pos, &this->actor.world.pos);
    this->actor.update = aHG_actor_move;
    this->actor.gravity = -2.0f;
    aHG_setup_action(this, 1, game_play);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83770_jp.s")
void aHG_actor_dt(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83780_jp.s")
void func_80A83780_jp(House_Goki* this) {
    this->unk_198 += 1.0f;
    if (this->unk_198 >= 2.0f) {
        this->unk_198 -= 2.0f;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A837C4_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83930_jp.s")
void func_80A83930_jp(House_Goki* this, Game_Play* game_play UNUSED) {
    this->unk_180 = (s32)fqrand() * 20 + 20;
    this->unk_184 = 0;
    this->unk_188 = 0;
    this->unk_195 = 0;
    this->unk_198 = 0.0f;
    this->actor.speed = 8.0f;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83994_jp.s")
void func_80A83994_jp(House_Goki* this, Game_Play* game_play UNUSED) {
    this->actor.speed = 0.0f;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer + 0x8000;
    this->unk_198 = 0.0f;
    this->unk_188 = 0;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_180 = (s32)fqrand() * 20 + 20;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83A00_jp.s")
void func_80A83A00_jp(House_Goki* this, Game_Play* game_play UNUSED) {
    this->unk_188 = 0xFF;
    this->unk_180 = 40;
    this->actor.speed = 0.0f;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83A24_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83D4C_jp.s")
void func_80A83D4C_jp(House_Goki* this, Game_Play* game_play) {
    Player* player = get_player_actor_withoutCheck(game_play);
    u16* unitFG;
    UNUSED s32 pad[2];
    xyz_t pos;

    if (this->unk_194 == 0 || (player->actor.speed != 0.0f && this->actor.xzDistToPlayer < 60.0f)) {
        this->unk_194 = 1;
        aHG_setup_action(this, 0, game_play);
        return;
    }

    if (this->actor.speed != 0.0f) {
        sAdo_OngenPos((uintptr_t)this, 0x28, &this->actor.world.pos);
        if ((this->actor.colCheck.colResult.hitWall & 2) || (this->actor.colCheck.colResult.unk1 & 2) ||
            (this->actor.colCheck.colResult.hitWall & 4) || (this->actor.colCheck.colResult.unk1 & 4) ||
            (this->actor.colCheck.colResult.hitWall & 8) || (this->actor.colCheck.colResult.unk1 & 8)) {
            if (this->unk_188 == 0) {
                this->actor.shape.rot.y += 0x8000;
                this->actor.world.rot.y = this->actor.shape.rot.y;
                this->unk_188 = 1;
            }
        } else {
            unitFG = mFI_GetUnitFG(this->actor.world.pos);
            if ((unitFG != NULL) && (*unitFG == 0x1F3F)) {
                this->unk_188 = 0;
                this->unk_180 = (s32)(fqrand() * 5.0f) + 5;
                this->actor.shape.rot.y = -0x8000;
                this->actor.world.rot.y = this->actor.shape.rot.y;
            } else {
                this->unk_188 = 0;
            }
        }
    }

    if (this->unk_180 > 0) {
        this->unk_180 -= 1;
        return;
    }

    this->unk_180 = (s32)(fqrand() * 5.0f) + 5;
    this->actor.speed = 0;
    if (((game_play->unk_1EA0 % 100) < 0x15) && !(fqrand() < 0.5f)) {
        if (!(this->actor.xzDistToPlayer < 60.0f)) {
            xyz_t_move(&pos, &this->actor.world.pos);
            pos.x += 80.0f - (fqrand() * 160.0f);
            pos.z += 80.0f - (fqrand() * 160.0f);
            this->actor.shape.rot.y = search_position_angleY(&this->actor.world.pos, &pos);
            this->unk_195 = 0;
            this->actor.world.rot.y = this->actor.shape.rot.y;
            this->actor.speed = 4;
        }
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A8401C_jp.s")
void func_80A8401C_jp(House_Goki* this, Game_Play* game_play UNUSED) {
    this->unk_190 = this->unk_188;

    this->unk_180 -= 1;
    if ((this->unk_180 & 2) == 0) {
        this->unk_190 = 0;
    }

    this->unk_188 -= 5;
    if (this->unk_188 < 0) {
        this->unk_188 = 0;
    }

    this->actor.shape.shadowAlphaRate = (f32)this->unk_188 * 0.0015f;
    if (this->unk_180 <= 0) {
        Actor_delete(&this->actor);
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A8409C_jp.s")
void aHG_setup_action(House_Goki* this, s32 processIndex, Game_Play* game_play) {
    this->processIndex = processIndex;
    this->process = process[processIndex];
    init_process[processIndex](this, game_play);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/aHG_actor_move.s")
void aHG_actor_move(Actor* thisx, Game_Play* game_play) {
    House_Goki* this = (House_Goki*)thisx;
    Player* player = get_player_actor_withoutCheck(game_play);

    if (this->processIndex != 2 && this->unk_190 != 0xFF) {
        this->unk_190 += 7;
        if (this->unk_190 >= 0x100) {
            this->unk_190 = 0xFF;
        }
        goto block_9;
    }

    if (common_data.clip.myRoomClip != NULL) {
        if (this->processIndex != 2 && this->unk_190 == 0xFF) {
            if (common_data.clip.myRoomClip->unk_68(&this->actor.world.pos)) {
                common_data.clip.unk_090->unk_00(0x5F, this->actor.world.pos, 1, 0, game_play, 0, 0, 0);
                mCkRh_CalcCanLookGokiCount(-1);
                sAdo_OngenTrgStart(0x5B, &this->actor.world.pos);
                aHG_setup_action(this, 2, game_play);
                return;
            }
        }
    }

block_9:
    this->actor.velocity.x = sin_s(this->actor.world.rot.y) * this->actor.speed;
    this->actor.velocity.z = cos_s(this->actor.world.rot.y) * this->actor.speed;
    this->actor.velocity.y += this->actor.gravity;
    Actor_position_move(&this->actor);
    func_80076778_jp(0, &this->actor, 15.0f, 0.0f, 0, 0);
    if (this->actor.world.pos.y < this->actor.home.pos.y) {
        this->actor.world.pos.y = this->actor.home.pos.y;
    }

    if (this->unk_190 == 0xFF && this->processIndex != 2) {
        if (this->actor.colCheck.colResult.unk9 || this->actor.colCheck.colResult.unk10) {
            common_data.clip.unk_090->unk_00(0x5F, this->actor.world.pos, 1, 0, game_play, 0, 0, 0);
            mCkRh_CalcCanLookGokiCount(-1);
            sAdo_OngenTrgStart(0x5B, &this->actor.world.pos);
            aHG_setup_action(this, 2, game_play);
            return;
        }
    }

    if (this->unk_190 != 0xFF && this->actor.params == 2) {
        this->actor.params = 1;
    }

    if (this->processIndex != 2) {
        if (this->actor.params == 2 ||
            (this->unk_190 == 0xFF && player->actor.speed != 0.0f && this->actor.xzDistToPlayer < 9.0f &&
             this->actor.world.pos.y == this->actor.home.pos.y)) {
            common_data.clip.unk_090->unk_00(0x5F, this->actor.world.pos, 1, 0, game_play, 0, 0, 0);
            mCkRh_CalcCanLookGokiCount(-1);
            sAdo_OngenTrgStart(0x5B, &this->actor.world.pos);
            aHG_setup_action(this, 2, game_play);
        }
    }
    this->process(this, game_play);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/aHG_actor_draw.s")
void aHG_actor_draw(Actor* thisx, Game_Play* game_play) {
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    House_Goki* this = (House_Goki*)thisx;

    Matrix_push();
    _texture_z_light_fog_prim_xlu(gfxCtx);
    Matrix_translate(this->actor.world.pos.x, this->actor.world.pos.y + 2.0f, this->actor.world.pos.z, 0U);
    Matrix_scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1U);
    Matrix_RotateX(this->actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);

    OPEN_POLY_XLU_DISP(gfxCtx);
    gSPMatrix(__polyXlu++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetEnvColor(__polyXlu++, 0xFF, 0xFF, 0xFF, this->unk_190);
    gSPDisplayList(__polyXlu++, (s32)D_80A845DC_jp[(s32)this->unk_198]);
    CLOSE_POLY_XLU_DISP(sp3C);

    Matrix_pull();
}
