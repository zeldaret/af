#include "ac_hanami_npc0.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_demo.h"
#include "macros.h"
#include "overlays/actors/ovl_Tools/ac_tools.h"
#include "audio.h"

#define THIS ((Hanami_Npc0*)thisx)

void aHM0_actor_ct(Actor* thisx, Game_Play* game_play);
void aHM0_actor_dt(Actor* thisx, Game_Play* game_play);
void aHM0_actor_init(Actor* thisx, Game_Play* game_play);
void aHM0_actor_save(Actor* thisx, Game_Play* game_play);
void aHM0_actor_move(void);
void aHM0_schedule_proc(Hanami_Npc0* this, Game_Play* game_play, s32 index);
void aHM0_talk_request(Actor* thisx, UNK_TYPE arg1 UNUSED);
s32 aHM0_talk_init(UNK_TYPE arg0 UNUSED, UNK_TYPE arg1 UNUSED);
s32 aHM0_talk_end_chk(Actor* thisx, UNK_TYPE arg1 UNUSED);
void aHM0_actor_draw(void);

ActorProfile Hanami_Npc0_Profile = {
    /* */ ACTOR_HANAMI_NPC0,
    /* */ ACTOR_PART_NPC,
    /* */ 0,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Hanami_Npc0),
    /* */ aHM0_actor_ct,
    /* */ aHM0_actor_dt,
    /* */ aHM0_actor_init,
    /* */ (void*)none_proc1,
    /* */ aHM0_actor_save,
};

struct_809AEFA4 aHM0_ct_data = {
    /* */ aHM0_actor_move,
    /* */ aHM0_actor_draw,
    /* */ 4,
    /* */ aHM0_talk_request,
    /* */ aHM0_talk_init,
    /* */ aHM0_talk_end_chk,
    /* */ NULL,
};

void aHM0_actor_ct(Actor* thisx, Game_Play* game_play) {
    Hanami_Npc0* this = THIS;

    if (common_data.clip.unk_040->unk_BC(thisx, game_play) == 1) {
        this->unk_7C0 = &aHM0_schedule_proc;
        common_data.clip.unk_040->unk_C0(thisx, game_play, &aHM0_ct_data);
    }
}

void aHM0_actor_save(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_C8(thisx, game_play);
}

void aHM0_actor_dt(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_C4(thisx, game_play);
}

void aHM0_actor_init(Actor* thisx, Game_Play* game_play) {
    common_data.clip.unk_040->unk_CC(thisx, game_play);
}

void aHM0_set_animation(Actor* thisx, s32 index) {
    static UNK_TYPE4 D_809DEB00_jp[] = { 0x00000048, 0x0000004A, 0x00000049 };

    common_data.clip.unk_040->unk_104(thisx, D_809DEB00_jp[index], 0, index);
}

void aHM0_actor_move(void) {
    common_data.clip.unk_040->unk_D0();
}

void aHM0_set_request_act(Actor* thisx) {
    Hanami_Npc0* this = THIS;

    this->unk_7D4 = 4;
    this->unk_7D5 = 0x12;
    this->unk_7D6 = 2;
}

void aHM0_make_tumbler(Actor* thisx, Game_Play* game_play) {
    Hanami_Npc0* this = THIS;
    ToolActor* tool;

    if (((this->unk_940 & 1) == 1) && (this->unk_860 == 0)) {
        // TODO: resolve warning, possibly by having Hanami_Npc0 struct start with ToolActor
        tool = common_data.clip.toolClip->aTOL_birth_proc(TOOL_TUMBLER, 3, this, game_play, -1, 0);
        if (tool != 0) {
            this->unk_860 = tool;
        }
    }
}

void aHM0_wait(Actor* thisx) {
    Hanami_Npc0* this = THIS;

    if (this->unk_188 == 2) {
        if (this->unk_72B == 0) {
            this->unk_7C6 = 0xFF;
        } else {
            this->unk_72B--;
        }
    }
}

void aHM0_merry(Actor* thisx) {
    Hanami_Npc0* this = THIS;

    if (this->unk_188 == 2) {
        if (this->unk_72B == 0) {
            this->unk_7C6 = 0xFF;
        } else {
            this->unk_72B--;
        }
    }

    // TODO: resolve warning by either casting &this->actor to (s32) or by changing signatures of both
    // sAdo_OngenPos and Na_OngenPos
    sAdo_OngenPos(&this->actor, this->unk_944, &this->actor.world.pos);
}

void aHM0_drink(Actor* thisx) {
    Hanami_Npc0* this = THIS;

    if (this->unk_188 == 1) {
        this->unk_7C6 = 0xFF;
    }
}

void aHM0_setupAction(Hanami_Npc0* this, s32 processIndex) {
    static Hanami_Npc0_unk_93C process[] = { aHM0_wait, aHM0_merry, aHM0_drink };
    static UNK_TYPE anm_loop_base[] = { 0x00000001, 0x00000002, 0x00000001 };
    static f32 anm_loop_rnd[] = { 2.0f, 3.0f, 1.0f };
    static u8 clap_se_no[] = { 0x2F, 0x31, 0x32, 0x33 };

    this->unk_7C6 = 0;
    this->unk_938 = processIndex;
    this->unk_93C = process[processIndex];
    this->unk_72B = (u8)(anm_loop_base[processIndex] + ((s32)(fqrand() * anm_loop_rnd[processIndex])));
    aHM0_set_animation(&this->actor, processIndex);

    if (processIndex == 1) {
        this->unk_944 = (u8)clap_se_no[(s32)(fqrand() * 4.0f)];
    }
}

void aHM0_act_chg_data_proc(Hanami_Npc0* this, Game_Play* game_play UNUSED) {
    this->unk_7C9 = 1;
}

void aHM0_act_init_proc(Hanami_Npc0* this, Game_Play* game_play UNUSED) {
    aHM0_setupAction(this, 0);
}

void aHM0_act_main_proc(Hanami_Npc0* this, Game_Play* game_play UNUSED) {
    this->unk_93C(&this->actor);
}

void aHM0_act_proc(Actor* thisx, Game_Play* game_play, s32 processIndex) {
    // TODO: confirm whether this is appropriate function type
    // act_proc
    static Hanami_Npc0ActionFunc act_proc[] = { aHM0_act_init_proc, aHM0_act_chg_data_proc, aHM0_act_main_proc };
    Hanami_Npc0* this = THIS;

    (*act_proc[processIndex])(this, game_play);
}

void aHM0_think_main_proc(Hanami_Npc0* this, Game_Play* game_play UNUSED) {
    static UNK_TYPE action[] = { 0x00000000, 0x00000001, 0x00000002 };

    if (this->unk_7C6 == 0xFF) {
        if (this->unk_7C5 == 0x12) {
            s32 processIndex = ((s32)(2.0f * fqrand())) << (this->unk_940 & 1);

            aHM0_setupAction(this, action[processIndex]);
        }
        this->unk_80C = 0x137;
        this->unk_911 = 1;
        aHM0_set_request_act(&this->actor);
    }
}

void aHM0_think_init_proc(Hanami_Npc0* this, Game_Play* game_play UNUSED) {
    this->unk_7A8 = 0;
    this->unk_7D0 = aHM0_act_proc;
    aHM0_set_request_act(&this->actor);
}

// TODO: verify signatures of this and of functions in array
void aHM0_think_proc(Actor* thisx, Game_Play* game_play, s32 processIndex) {
    static Hanami_Npc0ActionFunc think_proc[] = { aHM0_think_init_proc, aHM0_think_main_proc };
    Hanami_Npc0* this = THIS;

    (*think_proc[processIndex])(this, game_play);
}

void aHM0_schedule_init_proc(Hanami_Npc0* this, Game_Play* game_play) {
    static s16 def_angle[4] = { 0x2000, 0xC000, 0xE000, 0x4000 };
    s32 angleIndex = this->actor.fgName + 0xFFFF2FCE;

    this->unk_7A4 = &aHM0_think_proc;
    this->unk_7FD = 0;
    this->unk_8AC = -1;
    this->unk_92B = 1;
    this->unk_92C = 0x48;
    this->unk_940 = angleIndex;
    this->unk_80C = 0x137;
    this->unk_911 = 1;
    this->actor.colStatus.mass = MASS_HEAVY;
    {
        s16 tempAngle = def_angle[angleIndex];

        this->actor.shape.rot.y = tempAngle;
        this->actor.world.rot.y = tempAngle;
        this->unk_8DC = tempAngle;
    }
    common_data.clip.unk_040->unk_110(&this->actor, game_play, 8, 0);
}

void aHM0_schedule_main_proc(Hanami_Npc0* this, Game_Play* game_play) {
    if (common_data.clip.unk_040->unk_110(&this->actor, game_play, -1, 1) == 0) {
        common_data.clip.unk_040->unk_110(&this->actor, game_play, -1, 2);
    }

    aHM0_make_tumbler(&this->actor, game_play);
}

void aHM0_schedule_proc(Hanami_Npc0* this, Game_Play* game_play, s32 processIndex) {
    static Hanami_Npc0ActionFunc sche_proc[] = { aHM0_schedule_init_proc, aHM0_schedule_main_proc };

    (*sche_proc[processIndex])(this, game_play);
}

void aHM0_set_talk_info(Actor* thisx) {
    static u32 msg_base[] = { 0x0000192D, 0x0000193C, 0x0000191E, 0x0000194B, 0x0000195A, 0x00001969 };
    Hanami_Npc0* this = THIS;
    enum NpcLooks looks = mNpc_GetNpcLooks(thisx);

    mDemo_Set_msg_num(msg_base[looks] + ((s32)(fqrand() * 3.0f)) + (this->unk_940 * 3));
}

void aHM0_talk_request(Actor* thisx, UNK_TYPE arg1 UNUSED) {
    mDemo_Request(7, thisx, aHM0_set_talk_info);
}

// NOTE: return type is different from function of same suffix as found in
// ac_kamakura_npc0.c and ac_npc_engineer.c (both are void)
s32 aHM0_talk_init(UNK_TYPE arg0 UNUSED, UNK_TYPE arg1 UNUSED) {
    mDemo_Set_ListenAble();

    return 1;
}

s32 aHM0_talk_end_chk(Actor* thisx, UNK_TYPE arg1 UNUSED) {
    s32 result = FALSE;

    if (!mDemo_Check(7, thisx)) {
        result = TRUE;
    }

    return result;
}

// TODO: decide whether to use signature (Actor* thisx , Game_Play* game_play)
// This still matches if given that signature and both arguments are passed to
// unk_E4, or if given a signature of (Actor*) and passed that argument, but
// it does not match if one or both arguments are omitted in either case.
void aHM0_actor_draw(void) {
    common_data.clip.unk_040->unk_E4();
}
