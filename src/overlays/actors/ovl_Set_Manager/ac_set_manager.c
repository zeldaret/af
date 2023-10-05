#include "ac_set_manager.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "m_player_lib.h"
#include "m_field_info.h"
#include "ovlmgr.h"
#include "attributes.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"

// Fish and Insect overlay managers
#include "overlays/managers/ovl__00821B40/ovl__00821B40.h"
#include "overlays/managers/ovl__008253C0/ovl__008253C0.h"

void aSetMgr_ct(Actor* thisx, Game_Play* game_play);
void aSetMgr_dt(Actor* thisx, Game_Play* game_play);
void aSetMgr_move(Actor* thisx, Game_Play* play);

s32 aSetMgr_check_player_wade_end(void);
s32 aSetMgr_check_player_wade_start(void);

SetMgrOvlInfo proc_table[SETMGR_OVERLAY_MAX] = {
    SETMGR_OVERLAY(ovl__00821B40, func_8092A030_jp, func_8092AF0C_jp), // Fish
    SETMGR_OVERLAY(ovl__008253C0, func_8092DBC0_jp, func_8092ECAC_jp), // Insect
};

s32 aSetMgr_get_player_block(s32* bx, s32* bz, Game_Play* play) {
    s32 res = FALSE;
    Player* player = get_player_actor_withoutCheck(play);

    if (player != NULL) {
        xyz_t temp;
        temp = player->actor.world.pos;
        res = mFI_Wpos2BlockNum(bx, bz, temp);
    }

    return res;
}

s32 aSetMgr_renewal_player_next_pos(s32* next_bx, s32* next_bz) {
    xyz_t endpos = { 0.0f, 0.0f, 0.0f };
    s32 endPosRes;

    endPosRes = GET_CURRENT_PLAYER_ACTOR()->getEndPos(gamePT, &endpos);

    return mFI_Wpos2BlockNum(next_bx, next_bz, endpos) | endPosRes;
}

void aSetMgr_renewal_player_pos(Game_Play* play, SetMgrPlayerPos* playerPos) {
    s32 bx;
    s32 bz;
    s32 pad UNUSED;

    playerPos->prevBx = playerPos->curBx;
    playerPos->prevBz = playerPos->curBz;

    if (aSetMgr_get_player_block(&bx, &bz, play) == TRUE) {
        playerPos->curBx = bx;
        playerPos->curBz = bz;
    }
}

s32 aSetMgr_check_player_wade_start() {
    return mFI_CheckPlayerWade(1);
}

s32 aSetMgr_check_player_wade_end() {
    return mFI_CheckPlayerWade(3);
}

void aSetMgr_clear_set_ovl(SetMgrOvl* ovl) {
    bzero(ovl->buf, SETMGR_OVERLAY_BUFFER_SIZE);
    ovl->ovlProc = NULL;
}

s32 aSetMgr_ovl(SetMgrOvl* ovl, s32 type) {
    s32 pad UNUSED;
    SetMgrOvlInfo* mgrType = &proc_table[type];

    ovlmgr_Load(mgrType->vromStart, mgrType->vromEnd, mgrType->vramStart, mgrType->vramEnd, &ovl->buf);

    ovl->ovlProc = (void*)(&ovl->buf[(uintptr_t)mgrType->ovlTypeEnd] - (uintptr_t)mgrType->vramStart);

    return 1;
}

void aSetMgr_clear_keep(SetMgrKeep* keep) {
    bzero(keep, sizeof(SetMgrKeep));
}

s32 aSetMgr_move_check_set(Game_Play* play UNUSED, Set_Manager* setmgr) {
    s32 move = FALSE;

    aSetMgr_renewal_player_pos(play, &setmgr->playerPos);
    if (aSetMgr_check_player_wade_start() == TRUE) {
        aSetMgr_renewal_player_next_pos(&setmgr->playerPos.nextBx, &setmgr->playerPos.nextBz);
        setmgr->nextMove = 1;
        move = TRUE;
    }

    return move;
}

s32 aSetMgr_move_check_wait(Game_Play* play UNUSED, Set_Manager* set_manager) {
    s32 timer;
    s32 res = FALSE;

    if (set_manager->nextMove == SETMGR_MOVE_CHECK_WAIT) {
        if (set_manager->timer == 0) {
            timer = 0;
        } else {
            timer = --set_manager->timer;
        }

        if (timer == 0) {
            set_manager->nextMove = SETMGR_MOVE_SET;
            set_manager->timer = SETMGR_TIMER;
            res = TRUE;
        }
    }
    return res;
}

s32 aSetMgr_move_set(Game_Play* play UNUSED, Set_Manager* set_manager) {
    s32 pad UNUSED;
    s32 res = FALSE;

    if (aSetMgr_ovl(&set_manager->setOverlay, set_manager->setOvlType) == TRUE &&
        set_manager->setOverlay.ovlProc != NULL) {
        s32 requiredScopedTemp UNUSED;

        set_manager->setOverlay.ovlProc(set_manager, play);
        set_manager->setOvlType++;
    } else {
        set_manager->setOvlType++;
    }

    if (set_manager->setOvlType >= SETMGR_OVERLAY_MAX) {
        set_manager->nextMove = SETMGR_MOVE_CHECK_SET;
        set_manager->setOvlType = SETMGR_OVERLAY_START;
        res = TRUE;
    }

    if (aSetMgr_check_player_wade_end() == TRUE) {
        set_manager->nextMove = SETMGR_MOVE_CHECK_SET;
        set_manager->setOvlType = SETMGR_OVERLAY_START;
        res = TRUE;
    }

    return res;
}

SetManagerMoveProc move[] = { aSetMgr_move_check_set, aSetMgr_move_check_wait, aSetMgr_move_set };

void aSetMgr_move(Actor* thisx, Game_Play* play) {
    Set_Manager* setManager = (Set_Manager*)thisx;
    u8 proc = setManager->moveProc;

    if ((move[proc])(play, setManager) == TRUE) {
        setManager->moveProc = setManager->nextMove;
    }
}

void aSetMgr_ct(Actor* thisx, Game_Play* game UNUSED) {
    Set_Manager* setManager = (Set_Manager*)thisx;

    setManager->moveProc = SETMGR_MOVE_CHECK_SET;
    setManager->nextMove = SETMGR_MOVE_CHECK_SET;
    setManager->setOvlType = SETMGR_OVERLAY_START;

    aSetMgr_clear_set_ovl(&setManager->setOverlay);

    setManager->playerPos.nextBx = 0;
    setManager->playerPos.nextBz = 0;
    setManager->playerPos.curBx = 0;
    setManager->playerPos.curBz = 0;
    setManager->playerPos.prevBx = 0;
    setManager->playerPos.prevBz = 0;

    setManager->timer = SETMGR_TIMER;

    aSetMgr_clear_keep(&setManager->keep);
}

void aSetMgr_dt(Actor* thisx UNUSED, Game_Play* play UNUSED) {
}

ActorProfile Set_Manager_Profile = {
    /* */ ACTOR_SET_MANAGER,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Set_Manager),
    /* */ aSetMgr_ct,
    /* */ aSetMgr_dt,
    /* */ aSetMgr_move,
    /* */ (void*)none_proc1,
    /* */ NULL,
};
