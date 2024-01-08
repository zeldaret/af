#include "ac_tools.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_common_data.h"
#include "m_scene.h"
#include "macros.h"

void aTOL_actor_ct(Actor* thisx, Game_Play* game_play);
void aTOL_actor_dt(Actor* thisx, Game_Play* game_play);

ActorProfile Tools_Profile = {
    /* */ ACTOR_TOOLS,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Actor),
    /* */ aTOL_actor_ct,
    /* */ aTOL_actor_dt,
    /* */ (void*)none_proc1,
    /* */ (void*)none_proc1,
    /* */ NULL,
};

ToolClip aTOL_clip;

void aTOL_init_clip_area(Game_Play* game_play);
void aTOL_free_clip_area(void);
void aTOL_secure_pl_umbrella_bank_area(Game_Play* game_play);
s32 aTOL_check_data_bank(ObjectExchangeBank* objectExchangeBank, ToolName toolName, ToolActor* toolActor,
                         s16 objectIndex);

void aTOL_actor_ct(Actor* thisx UNUSED, Game_Play* game_play) {
    aTOL_init_clip_area(game_play);
}

void aTOL_actor_dt(Actor* thisx UNUSED, Game_Play* game_play UNUSED) {
    aTOL_free_clip_area();
}

s32 aTOL_check_data_bank(ObjectExchangeBank* objectExchangeBank, ToolName toolName, ToolActor* toolActor,
                         s16 objectIndex) {
    s32 ret = -1;

    if ((toolActor->actor.part == ACTOR_PART_PLAYER) && (toolName <= TOOL_UMBRELLA31) &&
        (common_data.toolClip->umbrellaObjectIndex != -1)) {
        ObjectStatus* objectStatus = &objectExchangeBank->status[common_data.toolClip->umbrellaObjectIndex];
        Actor* temp_a0;

        if (ABS(objectStatus->id) != objectIndex) {
            size_t objectSize = gObjectTable[objectIndex].vromEnd - gObjectTable[objectIndex].vromStart;

            if (objectSize <= 0xC00) {
                temp_a0 = toolActor->actor.child;

                if ((temp_a0 != NULL) && (temp_a0->unk_026 == common_data.toolClip->umbrellaObjectIndex)) {
                    Actor_delete(temp_a0);
                }

                objectStatus->id = -objectIndex;
                objectStatus->vrom = gObjectTable[objectIndex].vromStart;
                objectStatus->size = objectSize;
                objectStatus->unk50 = 0;
                objectStatus->unk53 = 1;
                objectStatus->unk14 = 0;
            }
        } else {
            ret = common_data.toolClip->umbrellaObjectIndex;
        }
    } else {
        s32 temp_v0_2 = mSc_bank_regist_check(objectExchangeBank, objectIndex);

        ret = temp_v0_2;

        if (temp_v0_2 == -1) {
            func_800C6144_jp(objectExchangeBank, objectIndex);
        }
    }

    return ret;
}

ToolActor* aTOL_birth_proc(ToolName toolName, s32 arg1, ToolActor* toolActor, Game_Play* game_play, s16 params,
                           s32* arg5) {
    static s16 profile_table[] = {
        ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA,
        ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA,
        ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA,
        ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA,
        ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA,
        ACTOR_T_UMBRELLA, ACTOR_T_UMBRELLA, ACTOR_T_KEITAI,   ACTOR_T_UTIWA,    ACTOR_T_HANABI,   ACTOR_T_CRACKER,
        ACTOR_T_PISTOL,   ACTOR_T_FLAG,     ACTOR_T_TUMBLER,  ACTOR_T_NPC_SAO,  ACTOR_T_TAMA,     ACTOR_T_TAMA,
        ACTOR_T_TAMA,     ACTOR_T_TAMA,
    };
    static s16 objectTable[] = {
        OBJECT_28,  OBJECT_85,  OBJECT_72,  OBJECT_73,          OBJECT_74,          OBJECT_75,
        OBJECT_76,  OBJECT_77,  OBJECT_78,  OBJECT_79,          OBJECT_80,          OBJECT_81,
        OBJECT_82,  OBJECT_83,  OBJECT_84,  OBJECT_55,          OBJECT_56,          OBJECT_57,
        OBJECT_58,  OBJECT_59,  OBJECT_60,  OBJECT_61,          OBJECT_62,          OBJECT_63,
        OBJECT_64,  OBJECT_65,  OBJECT_66,  OBJECT_67,          OBJECT_68,          OBJECT_69,
        OBJECT_70,  OBJECT_71,  OBJECT_45,  OBJECT_TOL_UTIWA_1, OBJECT_TOL_UTIWA_1, OBJECT_TOL_CRACKER_1,
        OBJECT_16,  OBJECT_6,   OBJECT_371, OBJECT_370,         OBJECT_391,         OBJECT_391,
        OBJECT_391, OBJECT_391,
    };
    s32 pad[3] UNUSED;
    ToolActor* ret = NULL;
    s32 temp_v0 = aTOL_check_data_bank(&game_play->objectExchangeBank, toolName, toolActor, objectTable[toolName]);
    s32 pad2 UNUSED;

    if (temp_v0 != -1) {
        ret = (ToolActor*)Actor_info_make_child_actor(&game_play->actorInfo, &toolActor->actor, game_play,
                                                      profile_table[toolName], 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, 0, params,
                                                      temp_v0);
        if (ret != NULL) {
            ret->unk1BC = arg1;
            ret->toolName = toolName;
        }
    }

    if (arg5 != NULL) {
        *arg5 = temp_v0;
    }

    return ret;
}

s32 aTOL_chg_request_mode_proc(Actor* arg0, ToolActor* toolActor, s32 arg2) {
    if (arg0 != toolActor->actor.parent) {
        return 0;

    } else {
        toolActor->unk1BC = arg2;
        return 1;
    }
}

void aTOL_secure_pl_umbrella_bank_area(Game_Play* game_play) {
    s32 pad UNUSED;
    s32 sp18 = game_play->objectExchangeBank.num;

    if (mSc_secure_exchange_keep_bank(&game_play->objectExchangeBank, 0, 0xC00)) {
        common_data.toolClip->umbrellaObjectIndex = sp18;

    } else {
        common_data.toolClip->umbrellaObjectIndex = -1;
    }
}

void aTOL_init_clip_area(Game_Play* game_play) {
    if (common_data.toolClip == NULL) {
        common_data.toolClip = &aTOL_clip;
        common_data.toolClip->aTOL_birth_proc = &aTOL_birth_proc;
        common_data.toolClip->aTOL_chg_request_mode_proc = &aTOL_chg_request_mode_proc;
        aTOL_secure_pl_umbrella_bank_area(game_play);
    }
}

void aTOL_free_clip_area(void) {
    if (common_data.toolClip) {
        common_data.toolClip = NULL;
    }
}
