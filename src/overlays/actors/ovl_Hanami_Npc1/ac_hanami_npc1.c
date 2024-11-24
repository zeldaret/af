#include "ac_hanami_npc1.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_field_info.h"

#define THIS ((Hanami_Npc1*)thisx)

void aHM1_actor_ct(Actor* thisx, Game_Play* game_play);
void aHM1_actor_dt(Actor* thisx, Game_Play* game_play);
void aHM1_actor_init(Actor* thisx, Game_Play* game_play);
void aHM1_actor_save(Actor* thisx, Game_Play* game_play);
void aHM1_actor_move(Actor* thisx, Game_Play* game_play);
void aHM1_actor_draw(Actor* thisx, Game_Play* game_play);
void aHM1_schedule_proc(Actor* thisx, Game_Play* game_play, s32 processIndex);
void aHM1_talk_request(Actor* thisx, UNK_TYPE arg1 UNUSED);
s32 aHM1_talk_init(UNK_TYPE arg0 UNUSED, UNK_TYPE arg1 UNUSED);
s32 aHM1_talk_end_chk(Actor* thisx, UNK_TYPE arg1 UNUSED);

#if 0
ActorProfile Hanami_Npc1_Profile = {
    /* */ ACTOR_HANAMI_NPC1,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Hanami_Npc1),
    /* */ aHM1_actor_ct,
    /* */ aHM1_actor_dt,
    /* */ aHM1_actor_init,
    /* */ (void*)none_proc1,
    /* */ aHM1_actor_save,
};
#endif

extern struct_809AEFA4 aHM1_ct_data;
// TODO: import data
// struct_809AEFA4 aHM1_ct_data = {
//     /* */ aHM1_actor_move,
//     /* */ aHM1_actor_draw,
//     /* */ 4,
//     /* */ aHM1_talk_request,
//     /* */ aHM1_talk_init,
//     /* */ aHM1_talk_end_chk,
//     /* */ NULL,
// };

void aHM1_actor_ct(Actor* thisx, Game_Play* game_play) {
    Hanami_Npc1* this = THIS;

    if (common_data.clip.unk_040->unk_BC(&this->actor, game_play) == 1) {
        this->unk_7C0 = aHM1_schedule_proc;
        common_data.clip.unk_040->unk_C0(&this->actor, game_play, &aHM1_ct_data);
    }
}

void aHM1_actor_save(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_C8(thisx, game_play);
}

void aHM1_actor_dt(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_C4(thisx, game_play);
}

void aHM1_actor_init(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_CC(thisx, game_play);
}

extern UNK_TYPE4 animeSeqNo[];
void aHM1_set_animation(Hanami_Npc1* this, s32 processIndex) {
    // TODO: import data
    // static UNK_TYPE4 animeSeqNo[] = { 0x0000004B, 0x0000004B };

    common_data.clip.unk_040->unk_104(&this->actor, animeSeqNo[processIndex], 0, processIndex);
}

void aHM1_actor_move(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_D0(thisx, game_play);
}

void aHM1_set_request_act(Actor* thisx) {
    Hanami_Npc1* this = THIS;

    this->unk_7D4 = 4;
    this->unk_7D5 = 0x12;
    this->unk_7D6 = 2;
}

s32 aHM1_check_moveRange(Actor* thisx, xyz_t* destination) {
    f32 posDiffX = thisx->home.pos.x - destination->x;
    f32 posDiffZ = thisx->home.pos.z - destination->z;
    f32 magnitudeSquared;
    s32 notInRange = FALSE; // TODO: double-check polarity and change to inRange if necessary 

    magnitudeSquared = (posDiffX * posDiffX) + (posDiffZ * posDiffZ);

    if (magnitudeSquared > 10000.0f) {
        notInRange = TRUE;
    }

    return notInRange;
}

s32 aHM1_check_inBlock(Actor* thisx, xyz_t* pos, s32* blockX, s32* blockZ) {
    s32 notInBlock = FALSE; // TODO: double-check polarity and change to inBlock if necessary

    mFI_Wpos2BlockNum(blockX, blockZ, *pos);

    // TODO: rename unk_008 to blockX and unk_009 to blockY in Actor struct
    if ((thisx->unk_008 != *blockX) || (thisx->unk_009 != *blockZ)) {
        notInBlock = 1;
    }

    return notInBlock;
}

extern s32 func_80088B3C_jp(f32*, f32*, s32, s32);
extern f32 offset[];

void aHM1_revise_moveRange(Actor* thisx) {
    // TODO: import data
    // static f32 offset[] = { 0.0f, 319.0f };
    s32 mask = 0;

    if (aHM1_check_moveRange(thisx, &thisx->world.pos) == TRUE) {
        s16 searchAngle = search_position_angleY(&thisx->home.pos, &thisx->world.pos);
        thisx->world.pos.x = (sin_s(searchAngle) * 100.0f) + thisx->home.pos.x;
        thisx->world.pos.z = (cos_s(searchAngle) * 100.0f) + thisx->home.pos.z;
        mask = 3;
    } else {
        s32 blockX;
        s32 blockZ;
        f32 worldPosX;
        f32 worldPosZ;

        if (aHM1_check_inBlock(thisx, &thisx->world.pos, &blockX, &blockZ) == TRUE) {
            s32 hanamiBlock;
            s32 offsetIndex;

            func_80088B3C_jp(&worldPosX, &worldPosZ, thisx->unk_008, thisx->unk_009);

            //! FAKE
            if (hanamiBlock) {}

            hanamiBlock = thisx->unk_008;
            offsetIndex = hanamiBlock < blockX;

            if (blockX != hanamiBlock) {
                thisx->world.pos.x = offset[offsetIndex] + worldPosX;
            }

            hanamiBlock = thisx->unk_009;
            offsetIndex = hanamiBlock < blockZ;

            if (blockZ != hanamiBlock) {
                thisx->world.pos.z = offset[offsetIndex] + worldPosZ;
            }
            mask = 3;
        }
    }

    // The usual top-of-function actor cast had to be omitted in order to get the stack to match
    THIS->unk_910 = (u8)(THIS->unk_910 | mask);
}

void aHM1_turn(Actor* thisx) {
    Hanami_Npc1* this = THIS;

    if (chase_angle(&thisx->shape.rot.y, this->unk_8DC, 0x800) == 1) {
        this->unk_93C = 1;
        this->unk_7C6 = 0xFF;
    }

    thisx->world.rot.y = thisx->shape.rot.y;
}

void aHM1_walk(Actor* thisx) {
    Hanami_Npc1* this = THIS;

    aHM1_revise_moveRange(thisx);

    if (this->unk_910 != 0) {
        this->unk_7C6 = 0xFF;
    } else if (this->unk_8CC >= 0x1F) {
        this->unk_7C6 = 0xFF;
    }

    chase_angle(&thisx->shape.rot.y, this->unk_8DC, 0x400);
    thisx->world.rot.y = thisx->shape.rot.y;
}

// TODO: Once you determine how processIndex is derived when calling, see if
// there's a more specific and appropriate name for it
void aHM1_set_spd_info(Hanami_Npc1* this, s32 processIndex) {
    if (processIndex == 1) {
        this->unk_8B4 = 0.1f;
        this->unk_8B8 = 0.1f;
        this->unk_8B0 = 1.0f;
        return;
    }

    this->actor.speed = 0.0f;
    this->unk_8B0 = 0.0f;
    this->unk_8B4 = 0.0f;
    this->unk_8B8 = 0.0f;
}


extern Hanami_Npc1_unk_940 process[];

void aHM1_setupAction(Hanami_Npc1* this, s32 processIndex) {
    // TODO: import data
    // static Hanami_Npc1_unk_940 process[] = { aHM1_turn, aHM1_walk };

    this->unk_7C6 = 0;
    this->unk_938 = processIndex;
    this->unk_940 = process[processIndex];
    aHM1_set_animation(this, processIndex);
    aHM1_set_spd_info(this, processIndex);
}

void aHM1_act_chg_data_proc(Hanami_Npc1* this, Game_Play* game_play UNUSED) {
    this->unk_7C9 = 1;
}

void aHM1_act_init_proc(Hanami_Npc1* this, Game_Play* game_play UNUSED) {
    aHM1_setupAction(this, 1);
}

void aHM1_act_main_proc(Hanami_Npc1* this, Game_Play* game_play UNUSED) {
    this->unk_940(&this->actor);
}

extern Hanami_Npc1ActionFunc act_proc[];

void aHM1_act_proc(Actor* thisx, Game_Play* game_play, s32 processIndex) {
    // TODO: import data
    // static Hanami_Npc1ActionFunc act_proc[] = { aHM1_act_init_proc, aHM1_act_chg_data_proc, aHM1_act_main_proc };
    Hanami_Npc1* this = THIS;

    (*act_proc[processIndex])(this, game_play);
}

void aHM1_think_main_proc(Hanami_Npc1* this, Game_Play* game_play UNUSED) {
    s16 modRotY;
    s32 modRotYAbsValue;
    f32 randS16AsFloat;
    s32 processIndex;

    if (this->unk_7C6 == 0xFF) {
        if (this->unk_7C5 == 0x12) {
            if (this->unk_93C != -1) {
                processIndex = this->unk_93C;
            } else {
                randS16AsFloat = (fqrand() - 0.5f) * 65536.0f;
                modRotY = ((s16)randS16AsFloat) - this->actor.shape.rot.y;
                this->unk_8DC = randS16AsFloat;

                if (modRotY >= 0) {
                    modRotYAbsValue = modRotY;
                } else {
                    modRotYAbsValue = -modRotY;
                }

                if (modRotYAbsValue >= 0x6001) {
                    processIndex = 0;
                } else {

                    if (!(this->unk_910 & 3)) {
                        processIndex = 1;
                    } else {
                        processIndex = 0;
                    }
                }
            }

            this->unk_8CC = 0;
            aHM1_setupAction(this, processIndex);
        }

        this->unk_93C = -1;
        this->unk_80C = 3;
        aHM1_set_request_act(&this->actor);
    }
}

void aHM1_think_init_proc(Hanami_Npc1* this, Game_Play* game_play UNUSED) {
    this->unk_7A8 = 0;
    this->unk_7D0 = aHM1_act_proc;
    aHM1_set_request_act(&this->actor);
}

extern Hanami_Npc1ActionFunc think_proc[];

void aHM1_think_proc(Actor* thisx, Game_Play* game_play, s32 processIndex) {
    // TODO: import data
    // static Hanami_Npc1ActionFunc think_proc[] = { aHM1_think_init_proc, aHM1_think_main_proc };
    Hanami_Npc1* this = THIS;

    (*think_proc[processIndex])(this, game_play);
}

extern s16 def_angle[];

void aHM1_schedule_init_proc(Hanami_Npc1* this, Game_Play* game_play) {
    // TODO: import data
    // static s16 def_angle[] = {0x2000, 0x2000, 0xE000, 0xC000, 0x0000, 0xE000, 0xE000};

    this->unk_7A4 = aHM1_think_proc;
    this->unk_7FD = 0;
    this->unk_8AC = -1;
    this->unk_93C = -1;
    this->unk_80C = 3;
    this->actor.colStatus.mass = MASS_HEAVY;

    {
        s32 angleIndex = mFI_GetPuleIdx();
        s16 tempAngle = def_angle[angleIndex];

        this->actor.shape.rot.y = tempAngle;
        this->actor.world.rot.y = tempAngle;
        this->unk_8DC = tempAngle;
    }

    common_data.clip.unk_040->unk_110(&this->actor, game_play, 8, 0);
}

void aHM1_schedule_main_proc(Hanami_Npc1* this, Game_Play* game_play) {
    if (common_data.clip.unk_040->unk_110(&this->actor, game_play, -1, 1) == 0) {
        common_data.clip.unk_040->unk_110(&this->actor, game_play, -1, 2);
    }
}

extern Hanami_Npc1ActionFunc sche_proc[];

void aHM1_schedule_proc(Actor* thisx, Game_Play* game_play, s32 processIndex) {
    // TODO: import data
    // static Hanami_Npc1ActionFunc sche_proc[] = { aHM1_schedule_init_proc, aHM1_schedule_main_proc };
    Hanami_Npc1* this = THIS;

    (*sche_proc[processIndex])(this, game_play);
}

extern u32 msg_base[];

void aHM1_set_talk_info(Actor* thisx) {
    // TODO: import data
    // static u32 msg_base[] = { 0x00001939, 0x00001948, 0x0000192A, 0x00001957, 0x00001966, 0x00001975 };
    enum NpcLooks looks = mNpc_GetNpcLooks(thisx);

    mDemo_Set_msg_num(msg_base[looks] + ((s32)(fqrand() * 3.0f)));
}

void aHM1_talk_request(Actor* thisx, UNK_TYPE arg1 UNUSED) {
    mDemo_Request(7, thisx, aHM1_set_talk_info);
}

// NOTE: return type is different from function of same suffix as found in
// ac_kamakura_npc0.c and ac_npc_engineer.c (both are void)
s32 aHM1_talk_init(UNK_TYPE arg0 UNUSED, UNK_TYPE arg1 UNUSED) {
    mDemo_Set_ListenAble();

    return 1;
}

s32 aHM1_talk_end_chk(Actor* thisx, UNK_TYPE arg1 UNUSED) {
    s32 result = FALSE;

    if (!mDemo_Check(7, thisx)) {
        result = TRUE;
    }

    return result;
}

void aHM1_actor_draw(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_E4(thisx, game_play);
}
