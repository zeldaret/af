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

void func_80A8409C_jp(House_Goki* this, s32 arg1, Game_Play* game_play);

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
    func_80A8409C_jp(this, 1, game_play);
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A83D4C_jp.s")

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/func_80A8409C_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/aHG_actor_move.s")
void aHG_actor_move(Actor* thisx, Game_Play* game_play) {
    House_Goki* this = (House_Goki*)thisx;
    Player* player = get_player_actor_withoutCheck(game_play);

    if (this->unk_17C != 2 && this->unk_190 != 0xFF) {
        this->unk_190 += 7;
        if (this->unk_190 >= 0x100) {
            this->unk_190 = 0xFF;
        }
        goto block_9;
    }

    if (common_data.clip.myRoomClip != NULL) {
        if (this->unk_17C != 2 && this->unk_190 == 0xFF) {
            if (common_data.clip.myRoomClip->unk_68(&this->actor.world.pos)) {
                common_data.clip.unk_090->unk_00(0x5F, this->actor.world.pos, 1, 0, game_play, 0, 0, 0);
                mCkRh_CalcCanLookGokiCount(-1);
                sAdo_OngenTrgStart(0x5B, &this->actor.world.pos);
                func_80A8409C_jp(this, 2, game_play);
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

    if (this->unk_190 == 0xFF && this->unk_17C != 2) {
        if (this->actor.colCheck.colResult.unk9 || this->actor.colCheck.colResult.unk10) {
            common_data.clip.unk_090->unk_00(0x5F, this->actor.world.pos, 1, 0, game_play, 0, 0, 0);
            mCkRh_CalcCanLookGokiCount(-1);
            sAdo_OngenTrgStart(0x5B, &this->actor.world.pos);
            func_80A8409C_jp(this, 2, game_play);
            return;
        }
    }

    if (this->unk_190 != 0xFF && this->actor.params == 2) {
        this->actor.params = 1;
    }

    if (this->unk_17C != 2) {
        if (this->actor.params == 2 ||
            (this->unk_190 == 0xFF && player->actor.speed != 0.0f && this->actor.xzDistToPlayer < 9.0f &&
             this->actor.world.pos.y == this->actor.home.pos.y)) {
            common_data.clip.unk_090->unk_00(0x5F, this->actor.world.pos, 1, 0, game_play, 0, 0, 0);
            mCkRh_CalcCanLookGokiCount(-1);
            sAdo_OngenTrgStart(0x5B, &this->actor.world.pos);
            func_80A8409C_jp(this, 2, game_play);
        }
    }
    this->unk_174(this, game_play);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_House_Goki/ac_house_goki/aHG_actor_draw.s")
