#include "m_demo.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_msg_main.h"
#include "m_player_lib.h"
#include "lib/ultralib/include/ido/memory.h"
#include "libc/math.h"
#include "m_field_info.h"
#include "audio.h"
#include "67E840.h"

f32 direct_vector[DEMO_DIRECT_MAX][2] = { { -1.0f, 0.0f },      { -M_SQRT2, M_SQRT2 }, { 0.0f, 1.0f },
                                          { M_SQRT2, M_SQRT2 }, { 1.0f, 0.0f },        { M_SQRT2, -M_SQRT2 },
                                          { 0.0f, -1.0f },      { -M_SQRT2, -M_SQRT2 } };

s16 direct_back_angle[DEMO_DIRECT_MAX] = { 0x0000, 0xE000, 0xC000, 0xA000, 0x8000, 0x6000, 0x4000, 0x2000 };

DemoData demo_data;

DemoData* demo = &demo_data;

Actor* mDemo_Get_talk_actor() {
    s32 type = demo->current.type;

    if (type == DEMO_TYPE_TALK || type == DEMO_TYPE_SPEAK || type == DEMO_TYPE_REPORT) {
        return demo->current.actor;
    }

    return NULL;
}

void mDemo_Set_OrderValue(s32 type, s32 idx, u16 value) {
    if (type >= DEMO_TYPE_NONE && type < DEMO_TYPE_OUTDOOR && idx >= 0 && idx < DEMO_ORDER_VALUE_MAX) {
        demo->orderData[type][idx] = value;
    }
}

u16 mDemo_Get_OrderValue(s32 type, s32 idx) {
    if (type >= DEMO_TYPE_NONE && type < DEMO_TYPE_OUTDOOR && idx >= 0 && idx < DEMO_ORDER_VALUE_MAX) {
        return demo->orderData[type][idx];
    } else {
        return 0;
    }
}

void mDemo_Init_OrderValue() {
    s32 i;
    s32 j;

    for (i = 0; i < DEMO_ORDER_MAX; i++) {
        for (j = 0; j < DEMO_ORDER_VALUE_MAX; j++) {
            demo->orderData[i][j] = 0;
        }
    }
}

void mDemo_Set_msg_num(s32 msgNo) {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        demo->data.talk.msgNo = msgNo;
    }
}

s32 mDemo_Get_Talk_Actors(Actor** speaker, Actor** listener) {
    s32 type = demo->current.type;

    if (type == DEMO_TYPE_TALK || type == DEMO_TYPE_SPEAK || type == DEMO_TYPE_REPORT) {
        speaker[0] = demo->speaker;
        listener[0] = demo->listener;
        return TRUE;

    } else {
        speaker[0] = NULL;
        listener[0] = NULL;

        return FALSE;
    }
}

void mDemo_Set_change_player_destiny(s8 destiny) {
    demo->changePlayerDestiny = destiny;
}

s32 mDemo_Get_change_player_destiny() {
    return demo->changePlayerDestiny;
}

void mDemo_Clear_change_player_destiny() {
    mDemo_Set_change_player_destiny(-1);
}

void mDemo_Copy_change_player_destiny() {
    if (mDemo_Get_change_player_destiny() >= 0) {
        PrivateDestiny* destiny = &common_data.privateInfo->destiny;
        lbRTC_time_c* rtcTime = &common_data.time.rtcTime;

        destiny->receivedTime.sec = rtcTime->sec;
        destiny->receivedTime.min = rtcTime->min;
        destiny->receivedTime.hour = rtcTime->hour;
        destiny->receivedTime.day = rtcTime->day;
        destiny->receivedTime.weekday = rtcTime->weekday;
        destiny->receivedTime.month = rtcTime->month;
        destiny->receivedTime.year = rtcTime->year;
        destiny->type = mDemo_Get_change_player_destiny();
        mDemo_Clear_change_player_destiny();
    }
}

void mDemo_Set_use_zoom_sound(u8 useZoomSound) {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        demo->data.talk.useZoomSound = useZoomSound;
    }
}

s32 mDemo_Get_use_zoom_sound() {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        return demo->data.talk.useZoomSound;
    } else {
        return 0;
    }
}

void mDemo_Set_talk_display_name(s8 displayName) {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        demo->data.talk.displayName = displayName;
    }
}

s32 mDemo_Get_talk_display_name() {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        return demo->data.talk.displayName;
    } else {
        return 0;
    }
}

void mDemo_Set_talk_change_player(u8 changePlayer) {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        demo->data.talk.changePlayer = changePlayer;
    }
}

s32 mDemo_Get_talk_change_player() {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        return demo->data.talk.changePlayer;
    } else {
        return 0;
    }
}

void mDemo_Set_talk_return_demo_wait(u8 returnDemoWait) {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        demo->data.talk.returnDemoWait = returnDemoWait;
    }
}

s32 mDemo_Get_talk_return_demo_wait() {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        return demo->data.talk.returnDemoWait;
    } else {
        return 0;
    }
}

void mDemo_Set_talk_turn(u8 turn) {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        demo->data.talk.turn = turn;
    }
}

s32 mDemo_Get_talk_turn() {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        return demo->data.talk.turn;
    } else {
        return 0;
    }
}

void mDemo_Set_talk_window_color(Color_RGBA8* windowColor) {
    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {

        demo->data.talk.windowColor = *windowColor;
    } else if (demo->current.type == DEMO_TYPE_EVENTMSG) {

        demo->data.emsg.windowColor = *windowColor;
    }
}

Color_RGBA8* mDemo_Get_talk_window_color_p() {

    if (demo->current.type == DEMO_TYPE_TALK || demo->current.type == DEMO_TYPE_SPEAK ||
        demo->current.type == DEMO_TYPE_REPORT) {
        return &demo->data.talk.windowColor;
    } else {
        return NULL;
    }
}

void mDemo_Set_camera(u8 cameraType) {
    demo->cameraType = cameraType;
}

s32 mDemo_Get_camera() {
    return demo->cameraType;
}

s32 mDemo_CheckDemoType() {
    s32 demoType;

    if (mDemo_CheckDemo()) {
        demoType = demo->current.type;
    } else {
        demoType = DEMO_TYPE_NONE;
    }

    return demoType;
}

s32 change_camera(s32 cameraType) {
    Player* player = get_player_actor_withoutCheck((Game_Play*)gamePT);
    Camera2* camera = &((Game_Play*)gamePT)->camera;

    if (cameraType == camera->unk60) {
        return FALSE;
    }

    switch (cameraType) {
        case 3:
            Camera2_request_main_talk(((Game_Play*)gamePT), &player->actor, demo->current.actor, DEMO_CAMERA_PRIORITY);
            break;
        case 5:
            Camera2_request_main_item(((Game_Play*)gamePT), 0, DEMO_CAMERA_PRIORITY);
            break;
        case 7: {
            Camera2_request_main_door(((Game_Play*)gamePT), &player->actor,
                                      demo->current.type == DEMO_TYPE_OUTDOOR ? 0 : 1, DEMO_CAMERA_PRIORITY);
        } break;
        case 6: {
            s_xyz angle;
            f32 dist;
            if (demo->current.type == DEMO_TYPE_EVENTMSG) {

                Camera2_main_Simple_AngleDistStd(((Game_Play*)gamePT), &angle, &dist);
                Camera2_request_main_simple(((Game_Play*)gamePT), &player->actor.world.pos, &angle, dist, 0,
                                            DEMO_CAMERA_PRIORITY);
            }
            break;
        }
        case 9:
            if (demo->current.actor->name == 0x79) {
                Camera2_request_main_listen_front_low_talk(((Game_Play*)gamePT), &player->actor, demo->current.actor,
                                                           DEMO_CAMERA_PRIORITY);
            }
            break;
        case 8:
            if (demo->current.actor->name == 0x2E) {
                Camera2_request_main_simple_kirin(((Game_Play*)gamePT), &demo->current.actor->world.pos,
                                                  DEMO_CAMERA_PRIORITY - 1);
            }
            break;
        case 1:
            Camera2_request_main_normal((Game_Play*)gamePT, 0, DEMO_CAMERA_PRIORITY - 1);
            break;
        case 12:
            break;
    }

    return TRUE;
}

s32 set_speak_default() {
    Player* player;

    demo->data.talk.msgNo = 0;
    demo->data.talk.turn = FALSE;
    demo->data.talk.displayName = TRUE;
    demo->data.talk.changePlayer = TRUE;
    demo->data.talk.returnDemoWait = FALSE;
    demo->data.talk.useZoomSound = TRUE;
    demo->data.talk.windowColor.r = DEMO_WINDOW_COLOR_R;
    demo->data.talk.windowColor.g = DEMO_WINDOW_COLOR_G;
    demo->data.talk.windowColor.b = DEMO_WINDOW_COLOR_B;
    demo->data.talk.windowColor.a = DEMO_WINDOW_COLOR_A;
    demo->cameraType = 3;
    mDemo_Unset_SpeakerAble();
    mDemo_Unset_ListenAble();

    player = get_player_actor_withoutCheck((Game_Play*)gamePT);
    demo->speaker = &player->actor;
    demo->listener = demo->current.actor;
    return TRUE;
}

s32 set_report_default() {
    Player* player;

    demo->data.talk.msgNo = 0;
    demo->data.talk.turn = FALSE;
    demo->data.talk.displayName = FALSE;
    demo->data.talk.changePlayer = FALSE;
    demo->data.talk.returnDemoWait = FALSE;
    demo->data.talk.useZoomSound = TRUE;
    demo->data.talk.windowColor.r = DEMO_WINDOW_COLOR_R;
    demo->data.talk.windowColor.g = DEMO_WINDOW_COLOR_G;
    demo->data.talk.windowColor.b = DEMO_WINDOW_COLOR_B;
    demo->data.talk.windowColor.a = DEMO_WINDOW_COLOR_A;
    demo->cameraType = 1;
    mDemo_Set_SpeakerAble();
    mDemo_Unset_ListenAble();

    player = get_player_actor_withoutCheck((Game_Play*)gamePT);
    demo->speaker = &player->actor;
    demo->listener = demo->current.actor;
    return TRUE;
}

s32 set_talk_default() {
    Player* player;

    demo->data.talk.msgNo = 0;
    demo->data.talk.turn = TRUE;
    demo->data.talk.displayName = TRUE;
    demo->data.talk.changePlayer = TRUE;
    demo->data.talk.returnDemoWait = FALSE;
    demo->data.talk.useZoomSound = TRUE;
    demo->data.talk.windowColor.r = DEMO_WINDOW_COLOR_R;
    demo->data.talk.windowColor.g = DEMO_WINDOW_COLOR_G;
    demo->data.talk.windowColor.b = DEMO_WINDOW_COLOR_B;
    demo->data.talk.windowColor.a = DEMO_WINDOW_COLOR_A;
    demo->cameraType = 3;
    mDemo_Unset_SpeakerAble();
    mDemo_Unset_ListenAble();

    player = get_player_actor_withoutCheck((Game_Play*)gamePT);
    demo->speaker = &player->actor;
    demo->listener = demo->current.actor;
    return TRUE;
}

s32 wait_talk_start() {
    Player* player = get_player_actor_withoutCheck((Game_Play*)gamePT);

    if (demo->data.talk.changePlayer) {
        if (mPlib_request_main_talk_type1((Game_Play*)gamePT, demo->current.actor, demo->data.talk.turn, FALSE) ==
            FALSE) {
            return FALSE;
        }
    } else {
        mDemo_Set_SpeakerAble();
    }

    if (mDemo_Check_SpeakerAble() && mDemo_Check_ListenAble()) {
        MessageWindow* window = mMsg_Get_base_window_p();

        mDemo_Init_OrderValue();

        if (mMsg_Check_main_index(window, 1) == FALSE) {
            player->actor.flags |= ACTOR_FLAG_40000000;
            demo->current.actor->flags |= ACTOR_FLAG_40000000;
            demo->data.talk.actorSavedMass = demo->current.actor->colStatus.mass;
            demo->current.actor->colStatus.mass = MASS_IMMOVABLE;
            mMsg_request_main_appear(window, demo->current.actor, demo->data.talk.displayName,
                                     &demo->data.talk.windowColor, demo->data.talk.msgNo, DEMO_MSG_PRIORITY);

            if (demo->data.talk.useZoomSound) {
                u16 arg0;

                if (demo->cameraType == 3) {
                    arg0 = 0x14;
                } else {
                    arg0 = 4;
                }

                sAdo_SysTrgStart(arg0);
            }

            if (FI_GET_TYPE(mFI_GetFieldId()) != 0x5000 && demo->data.talk.msgNo != 0x07DD &&
                demo->data.talk.msgNo != 0x0949 && demo->data.talk.msgNo != 0x0965 && demo->data.talk.msgNo != 0x07DE) {
                mBGMPsComp_volume_talk_start();
            }

            return TRUE;
        }
    }

    return FALSE;
}

s32 wait_talk_end() {
    if (mMsg_Check_main_hide(mMsg_Get_base_window_p()) || demo->state == DEMO_STATE_STOP) {
        if (demo->data.talk.changePlayer) {
            mPlib_request_main_talk_end_type1((Game_Play*)gamePT, demo->data.talk.returnDemoWait);
        }

        demo->current.actor->colStatus.mass = demo->data.talk.actorSavedMass;
        mDemo_Copy_change_player_destiny();

        if (FI_GET_TYPE(mFI_GetFieldId()) != 0x5000) {
            mBGMPsComp_volume_talk_end();
        }

        return TRUE;
    }

    return FALSE;
}

s32 wait_scroll_start() {
    return TRUE;
}

s32 set_door_default() {
    demo->data.door.type = DEMO_TYPE_NONE;
    demo->data.door.houseInfo.size = 80.0f;
    demo->data.door.houseInfo.direct = DEMO_DIRECT_S;
    demo->cameraType = 1;
    return TRUE;
}

s32 wait_door_start() {
    Player* player = get_player_actor_withoutCheck((Game_Play*)gamePT);
    xyz_t pos;
    Actor* actor = (Actor*)(get_player_actor_withoutCheck((Game_Play*)gamePT)->unk_122C((Game_Play*)gamePT));
    s16 backAngle;
    f32 sizeAdjust;

    if (demo->current.actor == actor) {
        return TRUE;
    } else {
        sizeAdjust = demo->data.door.houseInfo.size / 2.0f + 20.0f;

        pos.x = demo->current.actor->world.pos.x + sizeAdjust * direct_vector[demo->data.door.houseInfo.direct][1];
        pos.y = demo->current.actor->world.pos.y;
        pos.z = demo->current.actor->world.pos.z + sizeAdjust * direct_vector[demo->data.door.houseInfo.direct][0];

        backAngle = direct_back_angle[demo->data.door.houseInfo.direct];
        player->actor.flags |= ACTOR_FLAG_40000000;
        demo->current.actor->flags |= ACTOR_FLAG_40000000;

        mPlib_request_main_door_type1((Game_Play*)gamePT, &pos, backAngle, demo->data.door.type, demo->current.actor);
        mPlib_strength_request_main_door_priority((Game_Play*)gamePT);
    }

    return FALSE;
}

s32 mDemo_Set_house_info(f32 size, s32 direct) {
    if (demo->current.type == DEMO_TYPE_DOOR || demo->current.type == DEMO_TYPE_DOOR2) {
        demo->data.door.houseInfo.size = size;
        demo->data.door.houseInfo.direct = direct;
        return TRUE;
    }

    return FALSE;
}

s32 wait_door2_start() {
    Player* player = get_player_actor_withoutCheck((Game_Play*)gamePT);
    xyz_t pos;
    Actor* actor = (Actor*)get_player_actor_withoutCheck((Game_Play*)gamePT)->unk_122C((Game_Play*)gamePT);
    s16 backAngle;
    f32 sizeAdjust;

    if (demo->current.actor == actor) {
        return TRUE;
    } else {
        sizeAdjust = demo->data.door.houseInfo.size / 2.0f + 20.0f;

        pos.x = demo->current.actor->world.pos.x + sizeAdjust * direct_vector[demo->data.door.houseInfo.direct][1];
        pos.y = demo->current.actor->world.pos.y;
        pos.z = demo->current.actor->world.pos.z + sizeAdjust * direct_vector[demo->data.door.houseInfo.direct][0];

        backAngle = direct_back_angle[demo->data.door.houseInfo.direct];
        player->actor.flags |= ACTOR_FLAG_40000000;
        demo->current.actor->flags |= ACTOR_FLAG_40000000;

        mPlib_request_main_door_type2((Game_Play*)gamePT, &pos, backAngle, demo->data.door.type, demo->current.actor);
        mPlib_strength_request_main_door_priority((Game_Play*)gamePT);
    }

    return FALSE;
}

s16 get_title_no_for_event(s16 event) {
    switch (event) {
        case 11:
            return 0;
        case 12:
            return 1;
        case 8:
            return 2;
        case 10:
            return 3;
        case 7:
            return 4;
        case 9:
            return 5;
        case 16:
            return 6;
        case 22:
            return 7;
        case 21:
            return 8;
        case 6:
            return 9;
        case 3:
            return 0xA;
        case 2:
        case 20:
            return 0xB;
        case 13:
            return 0xC;
        case 5:
            return 0xD;
        default:
            return -1;
    }
}

s32 set_emsg_default() {
    s16 id = common_data.unk_107E2;
    s16 flags = common_data.unk_107E4;
    s16 titleNo;

    memcpy(&demo->data.emsg.doorData, &common_data.eventDoorData, sizeof(DoorData));

    if (flags == 1) {
        demo->data.emsg.msgNo = 0x1743;
    } else {
        demo->data.emsg.msgNo = 0x1799;
    }

    titleNo = get_title_no_for_event(id);

    if (titleNo >= 0) {
        demo->data.emsg.msgNo += titleNo;
    }
    demo->data.emsg.windowColor.r = DEMO_WINDOW_COLOR_R;
    demo->data.emsg.windowColor.g = DEMO_WINDOW_COLOR_G;
    demo->data.emsg.windowColor.b = DEMO_WINDOW_COLOR_B;
    demo->data.emsg.windowColor.a = DEMO_WINDOW_COLOR_A;
    demo->cameraType = 6;
    demo->data.emsg.msgDelayTimer = 0;
    demo->data.emsg.sceneDelayTimer = 30;

    return TRUE;
}

s32 wait_emsg_start() {
    MessageWindow* window = mMsg_Get_base_window_p();

    if (demo->data.emsg.msgDelayTimer <= 0) {
        if (demo->data.emsg.msgNo != 0) {
            mMsg_request_main_appear(window, NULL, FALSE, &demo->data.emsg.windowColor, demo->data.emsg.msgNo,
                                     DEMO_MSG_PRIORITY);
        }

        common_data.unk_107E4 = 2;
        return TRUE;
    } else {
        demo->data.emsg.msgDelayTimer--;
    }

    return FALSE;
}

s32 wait_emsg_end() {
    Game_Play* play = (Game_Play*)gamePT;
    MessageWindow* window = mMsg_Get_base_window_p();

    if (mMsg_Check_main_hide(window)) {
        demo->data.emsg.sceneDelayTimer--;
    }

    if (demo->data.emsg.sceneDelayTimer <= 0 || demo->state == DEMO_STATE_STOP) {
        if (goto_other_scene(play, &demo->data.emsg.doorData, FALSE)) {
            play->unk_1EE1 = demo->data.emsg.doorData.wipeType;
            play->unk_1EE0 = 11;
            common_data.unk_1014B = demo->data.emsg.doorData.wipeType;
            mBGMForce_inform_end();

            return TRUE;
        } else {
            return FALSE;
        }
    }

    return FALSE;
}

f32 weight_of_talk_position(Actor* actor) {
    f32 distY;
    f32 distFact;
    Player* player = get_player_actor_withoutCheck((Game_Play*)gamePT);
    s16 diffY = (player->actor.shape.rot.y - actor->yawTowardsPlayer);
    f32 angleFactor;

    distY = player->actor.world.pos.y - actor->world.pos.y;
    if (distY < 0.0f) {
        distY = -distY;
    }

    if (diffY < 0) {
        diffY = diffY - 0x8000;
    } else {
        diffY = -diffY - 0x8000;
    }

    if (actor->xzDistToPlayer <= actor->unk_144 && distY <= 33.0f && diffY <= 12530) {
        angleFactor = (1.0f - (actor->xzDistToPlayer / 55.0f));

        distFact = angleFactor;

        if (distFact < 0.0f) {
            distFact = 0.0f;
        }

        angleFactor = 1.0f - ((f32)diffY / 12530.0f);
        return SQ(angleFactor) * 0.6f + SQ(distFact) * 0.4f;
    } else {
        return -99.0f;
    }
}

s32 allways_true() {
    return TRUE;
}

s32 allways_false() {
    return FALSE;
}

s32 scroll_check() {
    return mPlib_check_request_main_wade_priority((Game_Play*)gamePT);
}

s32 scroll2_check() {
    return mPlib_check_request_main_demo_wade_priority((Game_Play*)gamePT);
}

s32 scroll3_check() {
    return mPlib_check_request_main_demo_geton_boat_wade_priority((Game_Play*)gamePT);
}

s32 door_check() {
    return mPlib_check_request_main_door_type1_priority((Game_Play*)gamePT);
}

s32 outdoor_check() {
    return mPlib_check_request_main_outdoor_priority((Game_Play*)gamePT);
}

s32 talk_check() {
    return mPlib_check_request_main_talk_type1_priority((Game_Play*)gamePT) != FALSE;
}

s32 speak_check() {
    return mPlib_check_request_main_speak_type1_priority((Game_Play*)gamePT) != FALSE;
}

typedef s32 (*DemoFunc)(void);

s32 choice_demo() {
    static DemoFunc check_func[] = { allways_true,  scroll_check, allways_true, scroll3_check, allways_true,
                                     scroll2_check, door_check,   talk_check,   speak_check,   allways_true,
                                     outdoor_check, allways_true, allways_true, allways_true };
    static DemoFunc default_set_func[] = { allways_true,      allways_true,       allways_true,     set_door_default,
                                           allways_true,      allways_true,       set_door_default, set_talk_default,
                                           set_speak_default, set_report_default, allways_true,     allways_true,
                                           set_emsg_default,  allways_true };
    f32 maxTalkWeight = 0.0f;
    DemoRequest* req;
    s32 idx = -1;
    s32 i = 0;

    for (; i < demo->requestId; i++) {
        s32 type;

        req = &demo->request[i];
        type = req->type;

        if (mEv_CheckTitleDemo() != 0 && type != DEMO_TYPE_SCROLL &&
            ((mEv_CheckTitleDemo() != -9 || type != DEMO_TYPE_SPEAK || req->actor == NULL ||
              req->actor->name != 0x99))) {
            continue;
        }

        if (type >= demo->priorityType && (*check_func[type])() != FALSE) {
            if (type == DEMO_TYPE_TALK) {
                if (chkTrigger(A_BUTTON) && req->talkWeight > maxTalkWeight) {
                    maxTalkWeight = req->talkWeight;
                    idx = i;
                }
            } else {
                idx = i;
                break;
            }
        }
    }

    if (idx != -1) {
        memcpy(&demo->current, &demo->request[idx], sizeof(DemoRequest));
        default_set_func[demo->current.type]();

        if (demo->current.proc != NULL) {
            demo->current.proc(demo->current.actor);
        }

        demo->state = 1;
    }

    return idx;
}

void emsg_set(UNUSED Actor* actor) {
    static Color_RGBA8 win_color = { 175, 255, 255, 255 };

    mDemo_Set_talk_window_color(&win_color);
}

void init_demo() {
    s32 initialType = common_data.startDemoRequest.type;

    memset(&demo->current, 0, sizeof(DemoRequest));
    demo->state = DEMO_STATE_WAIT;
    demo->requestId = 0;
    demo->priorityType = 0;
    demo->cameraType = 1;
    demo->keepCameraType = 0;

    switch (initialType) {
        case DEMO_TYPE_EVENTMSG:
            mDemo_Request(initialType, NULL, &emsg_set);
            common_data.startDemoRequest.type = DEMO_TYPE_NONE;
            break;
    }
}

DemoFunc wait_start[] = { allways_true,      wait_scroll_start, allways_true,    wait_door_start, allways_true,
                          wait_scroll_start, wait_door2_start,  wait_talk_start, wait_talk_start, wait_talk_start,
                          allways_true,      allways_true,      wait_emsg_start, allways_true };

DemoFunc wait_end[] = { allways_false, allways_false, allways_false, allways_false, allways_false,
                        allways_false, allways_false, wait_talk_end, wait_talk_end, wait_talk_end,
                        allways_false, allways_false, wait_emsg_end, allways_false };

void run_demo() {
    if (demo->state == DEMO_STATE_READY) {
        if (wait_start[demo->current.type]()) {
            change_camera(demo->cameraType);
            demo->state = DEMO_STATE_RUN;
        }
    } else if (demo->state == DEMO_STATE_RUN && wait_end[demo->current.type]()) {
        demo->state = DEMO_STATE_STOP;
    }
}

void main_proc() {
    Player* player = get_player_actor_withoutCheck((Game_Play*)gamePT);

    if (demo->state == DEMO_STATE_STOP) {
        player->actor.flags &= ~ACTOR_FLAG_40000000;

        if (demo->current.actor != NULL) {
            demo->current.actor->flags &= ~ACTOR_FLAG_40000000;
        }

        demo->cameraType = 1;
        if (demo->keepCameraType != 0 && demo->current.actor != NULL) {
            change_camera(demo->keepCameraType);
        } else {
            change_camera(demo->cameraType);
        }

        demo->keepCameraType = 0;
        memset(&demo->current, 0, sizeof(DemoRequest));
        demo->state = DEMO_STATE_WAIT;
    }

    if (demo->state == DEMO_STATE_WAIT) {
        choice_demo();
    }

    if (demo->state != DEMO_STATE_WAIT) {
        run_demo();
    }
}

void mDemo_stock_clear() {
    demo->requestId = 0;
    demo->priorityType = DEMO_TYPE_NONE;
}

s32 mDemo_Request(s32 type, Actor* actor, DemoRequestFunc request) {
    f32 weight = 1.0f;
    DemoRequest* req;
    s32 requestId = demo->requestId;

    if (requestId < DEMO_REQUEST_MAX) {
        if (type >= demo->priorityType) {
            req = &demo->request[requestId];

            if (type == DEMO_TYPE_TALK) {
                weight = weight_of_talk_position(actor);

                if (weight < 0.0f) {
                    return FALSE;
                }
            } else if (type == DEMO_TYPE_SPEAK &&
                       mPlib_Check_able_force_speak_label((Game_Play*)gamePT, actor) == FALSE) {
                return FALSE;
            }

            demo->priorityType = type;

            req->type = demo->priorityType;
            req->actor = actor;
            req->proc = request;
            req->talkWeight = weight;

            demo->requestId++;
        }

        return TRUE;
    }

    return FALSE;
}

s32 mDemo_Check(s32 type, Actor* actor) {
    if (type == demo->current.type && actor == demo->current.actor) {
        return TRUE;
    }

    return FALSE;
}

s32 mDemo_Start(UNUSED Actor* actor) {
    return FALSE;
}

s32 mDemo_Check_and_Go(s32 type, Actor* actor) {
    if (mDemo_Check(type, actor) != FALSE) {
        return mDemo_Start(actor);
    }

    return FALSE;
}

s32 mDemo_End(Actor* actor) {
    if (actor == demo->current.actor) {
        demo->state = DEMO_STATE_STOP;
        return TRUE;
    }

    return FALSE;
}

void mDemo_Main(UNUSED Game_Play* play) {
    main_proc();
}

void mDemo_Init(UNUSED Game_Play* play) {
    demo->speaker = NULL;
    demo->listener = NULL;
    mDemo_Unset_SpeakerAble();
    mDemo_Unset_ListenAble();
    mDemo_Init_OrderValue();
    mDemo_Clear_change_player_destiny();
    init_demo();
}

s32 mDemo_CheckDemo() {
    return demo->state != DEMO_STATE_WAIT;
}

s32 mDemo_CheckDemo4Event() {
    switch (mDemo_CheckDemoType()) {
        case DEMO_TYPE_NONE:
        case DEMO_TYPE_EVENTMSG:
            return FALSE;
    }

    return TRUE;
}

void mDemo_Set_SpeakerAble() {
    demo->isAbleSpeaker = TRUE;
}

void mDemo_Set_ListenAble() {
    demo->isAbleListener = TRUE;
}

void mDemo_Unset_SpeakerAble() {
    demo->isAbleSpeaker = FALSE;
}

void mDemo_Unset_ListenAble() {
    demo->isAbleListener = FALSE;
}

s32 mDemo_Check_SpeakerAble() {
    return demo->isAbleSpeaker;
}

s32 mDemo_Check_ListenAble() {
    return demo->isAbleListener;
}

int mDemo_Check_DiffAngle_forTalk(s16 diffAngle) {
    return diffAngle > -5000 && diffAngle < 5000;
}

void mDemo_KeepCamera(s32 cameraType) {
    demo->keepCameraType = cameraType;
}
