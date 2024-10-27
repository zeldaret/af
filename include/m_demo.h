#ifndef M_DEMO_H
#define M_DEMO_H

#include "ultra64.h"
#include "color.h"
#include "m_scene.h"

struct Actor;
struct Game_Play;

#define DEMO_ORDER_VALUE_MAX 10
#define DEMO_REQUEST_MAX 32

#define DEMO_MSG_PRIORITY 5
#define DEMO_CAMERA_PRIORITY 6

#define DEMO_WINDOW_COLOR_R 235
#define DEMO_WINDOW_COLOR_G 255
#define DEMO_WINDOW_COLOR_B 235
#define DEMO_WINDOW_COLOR_A 255

typedef enum DemoState {
    DEMO_STATE_WAIT,
    DEMO_STATE_READY,
    DEMO_STATE_RUN,
    DEMO_STATE_STOP = 9,

    DEMO_STATE_MAX
} DemoState;

typedef enum DemoDirection {
    DEMO_DIRECT_N,
    DEMO_DIRECT_NE,
    DEMO_DIRECT_E,
    DEMO_DIRECT_SE,
    DEMO_DIRECT_S,
    DEMO_DIRECT_SW,
    DEMO_DIRECT_W,
    DEMO_DIRECT_NW,

    DEMO_DIRECT_MAX
} DemoDirection;

typedef enum DemoType {
    DEMO_TYPE_NONE,
    DEMO_TYPE_SCROLL,
    DEMO_TYPE_EXITSCENE,
    DEMO_TYPE_DOOR,
    DEMO_TYPE_4,
    DEMO_TYPE_SCROLL2,
    DEMO_TYPE_DOOR2,
    DEMO_TYPE_TALK,
    DEMO_TYPE_SPEAK,
    DEMO_TYPE_REPORT,
    DEMO_TYPE_OUTDOOR,
    DEMO_TYPE_B,
    DEMO_TYPE_EVENTMSG,
    DEMO_TYPE_D,
    DEMO_TYPE_MAX
} DemoType; 

typedef enum DemoOrderType {
    DEMO_ORDER_PLAYER,
    DEMO_ORDER_1,
    DEMO_ORDER_2,
    DEMO_ORDER_3,
    DEMO_ORDER_NPC0,
    DEMO_ORDER_NPC1,
    DEMO_ORDER_NPC2,
    DEMO_ORDER_7,
    DEMO_ORDER_8,
    DEMO_ORDER_QUEST,

    DEMO_ORDER_MAX
} DemoOrderType;

typedef void (*DemoRequestFunc)(struct Actor*);

typedef struct DemoClip {
    void* demoActor;
    s32 type;
} DemoClip;

typedef enum DemoClipType {
    DEMO_CLIP_TYPE_NONE,
    DEMO_CLIP_TYPE_INTRO_DEMO,
    DEMO_CLIP_TYPE_RIDE_OFF_DEMO,
    DEMO_CLIP_TYPE_PRESENT_DEMO,
    DEMO_CLIP_TYPE_BOAT_DEMO,
    DEMO_CLIP_TYPE_RESET_DEMO,

    DEMO_CLIP_TYPE_MAX
} DemoClipType;

typedef struct DemoRequest {
    struct Actor* actor;
    s32 type;
    DemoRequestFunc proc;
    f32 talkWeight;
} DemoRequest;

typedef struct DemoDoorData {
    s32 type;
    struct houseInfo{
        f32 size;
        s32 direct;
    } houseInfo;
} DemoDoorData;

typedef struct DemoEMsgData {
    s32 msgNo;
    Color_RGBA8 windowColor;
    s32 msgDelayTimer;
    s32 sceneDelayTimer;
    DoorData doorData;
    UNK_TYPE1 unk_24[0x4];
} DemoEMsgData;

typedef struct DemoTalkData {
    s32 msgNo;
    s32 turn;
    s32 useZoomSound;
    s32 displayName;
    s32 changePlayer;
    s32 returnDemoWait;
    Color_RGBA8 windowColor;
    u8 actorSavedMass;
} DemoTalkData;

typedef struct DemoData { 
    struct Actor* speaker;
    struct Actor* listener;
    s32 isAbleSpeaker;
    s32 isAbleListener;
    u16 orderData[DEMO_ORDER_MAX][DEMO_ORDER_VALUE_MAX];
    s8 changePlayerDestiny;
    s32 state;
    DemoRequest current;
    DemoRequest request[DEMO_REQUEST_MAX];
    s32 requestId;
    s32 priorityType;
    s32 cameraType;
    s32 keepCameraType;

    union {
        DemoDoorData door;
        DemoEMsgData emsg;
        DemoTalkData talk;
    } data;
} DemoData;

extern DemoData* demo;

struct Actor* mDemo_Get_talk_actor(void);
void mDemo_Set_OrderValue(s32 type, s32 idx, u16 value);
u16 mDemo_Get_OrderValue(s32 type, s32 idx);
void mDemo_Init_OrderValue(void);
void mDemo_Set_msg_num(s32 msgNo);
s32 mDemo_Get_Talk_Actors(struct Actor** speaker, struct Actor** listener);
void mDemo_Set_change_player_destiny(s8 destiny);
s32 mDemo_Get_change_player_destiny(void);
void mDemo_Clear_change_player_destiny(void);
void mDemo_Copy_change_player_destiny(void);
void mDemo_Set_use_zoom_sound(u8 useZoomSound);
s32 mDemo_Get_use_zoom_sound(void);
void mDemo_Set_talk_display_name(s8 displayName);
s32 mDemo_Get_talk_display_name(void);
void mDemo_Set_talk_change_player(u8 changePlayer);
s32 mDemo_Get_talk_change_player(void);
void mDemo_Set_talk_return_demo_wait(u8 returnDemoWait);
s32 mDemo_Get_talk_return_demo_wait(void);
void mDemo_Set_talk_turn(u8 turn);
s32 mDemo_Get_talk_turn(void);
void mDemo_Set_talk_window_color(Color_RGBA8* windowColor);
Color_RGBA8* mDemo_Get_talk_window_color_p(void);
void mDemo_Set_camera(u8 cameraType);
s32 mDemo_Get_camera(void);
s32 mDemo_CheckDemoType(void);
s32 change_camera(s32 cameraType);
s32 set_speak_default(void);
s32 set_report_default(void);
s32 set_talk_default(void);
s32 wait_talk_start(void);
s32 wait_talk_end(void);
s32 wait_scroll_start(void);
s32 set_door_default(void);
s32 wait_door_start(void);
s32 mDemo_Set_house_info(f32 size, s32 direct);
s32 wait_door2_start(void);
s16 get_title_no_for_event(s16 event);
s32 set_emsg_default(void);
s32 wait_emsg_start(void);
s32 wait_emsg_end(void);
f32 weight_of_talk_position(struct Actor* actor);
s32 allways_true(void);
s32 allways_false(void);
s32 scroll_check(void);
s32 scroll2_check(void);
s32 scroll3_check(void);
s32 door_check(void);
s32 outdoor_check(void);
s32 talk_check(void);
s32 speak_check(void);
s32 choice_demo(void);
void emsg_set(struct Actor* actor);
void init_demo(void);
void run_demo(void);
void main_proc(void);
void mDemo_stock_clear(void);
s32 mDemo_Request(s32 type, struct Actor* actor, DemoRequestFunc request);
s32 mDemo_Check(s32 type, struct Actor* actor);
s32 mDemo_Start(struct Actor* actor);
s32 mDemo_Check_and_Go(s32 type, struct Actor* actor);
s32 mDemo_End(struct Actor* actor);
void mDemo_Main(struct Game_Play* play);
void mDemo_Init(struct Game_Play* play);
s32 mDemo_CheckDemo(void);
s32 mDemo_CheckDemo4Event(void);
void mDemo_Set_SpeakerAble(void);
void mDemo_Set_ListenAble(void);
void mDemo_Unset_SpeakerAble(void);
void mDemo_Unset_ListenAble(void);
s32 mDemo_Check_SpeakerAble(void);
s32 mDemo_Check_ListenAble(void);
int mDemo_Check_DiffAngle_forTalk(s16 diffAngle);
void mDemo_KeepCamera(s32 cameraType);



#endif
