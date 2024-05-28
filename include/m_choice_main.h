#ifndef M_CHOICE_MAIN_H
#define M_CHOICE_MAIN_H

#include "ultra64.h"
#include "color.h"

struct Game;
struct Actor;

#define Choice_CHOICE_STRING_LEN 10

typedef enum Choice_CHOICE {
    Choice_CHOICE0,
    Choice_CHOICE1,
    Choice_CHOICE2,
    Choice_CHOICE3,
    Choice_CHOICE_MAX,
} Choice_CHOICE;

typedef enum Choice_AUTOMOVETYPE {
    Choice_AUTOMOVE_STOPPED,
    Choice_AUTOMOVE_INCREMENT_WAIT,
    Choice_AUTOMOVE_INCREMENT,
    Choice_AUTOMOVE_DECREMENT_WAIT,
    Choice_AUTOMOVE_DECREMENT,
    Choice_AUTOMOVE_MAX
} Choice_AUTOMOVETYPE;

typedef struct ChoiceData {
    /* 0x00 */ char strings[Choice_CHOICE_MAX][Choice_CHOICE_STRING_LEN];
    /* 0x28 */ s32 stringLens[Choice_CHOICE_MAX];
    /* 0x38 */ char determinationString[Choice_CHOICE_STRING_LEN];
    /* 0x44 */ s32 determinationLenght;
    /* 0x48 */ s32 choiceNum;
    /* 0x4C */ s32 selectedChoiceIdx;
} ChoiceData; // size = 0x50

typedef struct Choice {
    /* 0x00 */f32 centerX;
    /* 0x04 */f32 centerY;

    /* Initial XY position */
    /* 0x08 */ f32 centerXBegin;
    /* 0x0C */ f32 centerYBegin;

    /* Target XY position */
    /* 0x10 */ f32 centerXTarget;
    /* 0x14 */ f32 centerYTarget;

    /* Text settings */
    /* 0x18 */ Color_RGBA8 textColor;
    /* 0x1C */ f32 textScaleX;
    /* 0x20 */ f32 textScaleY;
    /* 0x24 */ f32 textX;
    /* 0x28 */ f32 textY;

    /* Window scaling XY */
    /* 0x2C */ f32 scaleX;
    /* 0x30 */ f32 scaleY;

    /* Text related data */
    /* 0x34 */ ChoiceData data;

    /* 0x84 */ s32 selectedChoiceIdx;
    /* 0x88 */ Color_RGBA8 selectedChoiceTextColor;

    /* 0x8C */ Color_RGBA8 backgroundColor;

    /* 0x90 */ f32 unk_D4;
    /* 0x94 */ f32 unk_D8;

    /* 0x98 */ f32 scale;  // total choice window scaling percentage

    /* 0x9C */ s32 mainIdx;
    /* 0xA0 */ s32 requestedMainIdx;

    /* 0xA4 */ s32 isWindowVisible;
    /* 0xA8 */ s32 isFontVisible;

    /* 0xAC */ s32 choiceAutomoveType;
    /* 0xB0 */ f32 choiceAutomoveTimer;

    /* 0xB4 */ f32 timer;

    /* 0xB8 */ u8 noBFlag;      // can't press B to select last option
    /* 0xB9 */ u8 noCloseFlag;  // pressing B won't auto-cancel the choice selection?
} Choice; // size = 0xBC


Choice* mChoice_Get_base_window_p();
void mChoice_init(Choice* choice,  struct Game* game);
void mChoice_Change_request_main_index(Choice* choice, s32 idx);
s32 mChoice_check_main_index(Choice* choice);
s32 mChoice_check_main_normal(Choice* choice);
void mChoice_Init_choice_data(Choice* choice);
s32 mChoice_Add_choice_data(Choice* choice, char* str, s32 max_len);
void mChoice_Set_choice_data(Choice* choice, char* str0, s32 str0len, char* str1, s32 str1len, char* str2, s32 str2len,
                             char* str3, s32 str3len);
s32 mChoice_Get_MaxStringDotWidth(Choice* choice);
s32 mChoice_Get_MaxStringDotHeight(Choice* choice);
void mChoice_Set_DisplayScaleAndDisplayPos(Choice* choice);
s32 mChoice_Get_ChoseNum(Choice* choice);
void mChoice_Clear_ChoseNum(Choice* choice);
void mChoice_check_ct( Choice* choice,  struct Game* game);
void mChoice_Get_StringDataAddressAndSize(s32 idx, u32** addr, u32* size);
s32 mChoice_Put_String_PLAYER_NAME(char* data, s32 idx, s32 maxSize,  struct Actor* actor);
s32 mChoice_Put_String_TALK_NAME(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_TAIL(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_YEAR(char* data, s32 idx, s32 maxSize,  struct Actor* actor);
s32 mChoice_Put_String_MONTH(char* data, s32 idx, s32 maxSize,  struct Actor* actor);
s32 mChoice_Put_String_WEEK(char* data, s32 idx, s32 maxSize,  struct Actor* actor);
s32 mChoice_Put_String_DAY(char* data, s32 idx, s32 maxSize,  struct Actor* actor);
s32 mChoice_Put_String_HOUR(char* data, s32 idx, s32 maxSize,  struct Actor* actor);
s32 mChoice_Put_String_MIN(char* data, s32 idx, s32 maxSize,  struct Actor* actor);
s32 mChoice_Put_String_SEC(char* data, s32 idx, s32 maxSize,  struct Actor* actor);
s32 mChoice_Put_String_FREE(char* data, s32 idx, s32 maxSize,  struct Actor* actor, s32 freeIdx);
s32 mChoice_Put_String_FREE0(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE1(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE2(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE3(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE4(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE5(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE6(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE7(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE8(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE9(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE10(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE11(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE12(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE13(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE14(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE15(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE16(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE17(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE18(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_FREE19(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_DETERMINATION(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_COUNTRY_NAME(char* data, s32 idx, s32 maxSize,  struct Actor* actor);
s32 mChoice_Put_String_RAMDOM_NUMBER2(char* data, s32 idx, s32 maxSize,  struct Actor* actor);
s32 mChoice_Put_String_ITEM(char* data, s32 idx, s32 maxSize,  struct Actor* actor, s32 itemIdx);
s32 mChoice_Put_String_ITEM0(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_ITEM1(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_ITEM2(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_ITEM3(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String_ITEM4(char* data, s32 idx, s32 maxSize, struct Actor* actor);
s32 mChoice_Put_String(char* data, s32 idx, s32 maxSize, struct Actor* actor);
void mChoice_Change_ControlCode(char* data, s32 maxSize, struct Actor* actor);
void mChoice_Load_ChoseStringFromRom(s32 , char* str, s32 idx, struct Actor* actor);
void mChoice_no_b_set(Choice* choice);
void mChoice_sound_SENTAKU_KETTEI(void);
void mChoice_sound_SENTAKU_OPEN(void);
void mChoice_sound_CURSOL(void);
void mChoice_Main_Hide(Choice* choice, struct Game* game);
void mChoice_MainSetup_Hide(Choice* choice, struct Game* game);
s32 mChoice_Main_Appear_SetScale(Choice* choice, struct Game* game);
void mChoice_request_main_index_fromAppear(Choice* choice, struct Game* game, s32 flag);
void mChoice_Main_Appear(Choice* choice, struct Game* game);
void mChoice_MainSetup_Appear(Choice* choice, struct Game* game);
void mChoice_determimation_set(Choice* choice);
s32 mChoice_Main_Normal_SetChoice(Choice* choice, struct Game* game);
void mChoice_request_main_index_fromNormal(Choice* choice, struct Game* game, s32 flag);
void mChoice_Main_Normal(Choice* choice, struct Game* game);
void mChoice_MainSetup_Normal(Choice* choice, struct Game* game);
s32 mChoice_Main_Disappear_SetScale(Choice* choice, struct Game* game);
void mChoice_request_main_index_fromDisappear(Choice* choice, struct Game* game, s32 flag);
void mChoice_Main_Disappear(Choice* choice, struct Game* game);
void mChoice_MainSetup_Disappear(Choice* choice, struct Game* game);
void mChoice_MainSetup(Choice* choice, struct Game* game);
void mChoice_Main(Choice* choice, struct Game* game);
void mChoice_SetMatrix(Choice* choice, struct Game* game, s32 type);
void mChoice_SetMatrixDisplay(Choice* choice, struct Game* game, s32 type);
void mChoice_UnSetMatrix(void);
void mChoice_UnSetMatrixDisplay(struct Game* game, s32 type);
void mChoice_DrawWindowBody(Choice* choice, struct Game* game, s32 type);
void mChoice_DrawFont(Choice* choice, struct Game* game, s32 type);
void mChoice_Draw(Choice* choice, struct Game* game, s32 mode);
void mChoice_ct(Choice* choice, struct Game* game);
void mChoice_dt(Choice* choice, struct Game* game);

#endif
