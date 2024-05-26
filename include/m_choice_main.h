#ifndef M_CHOICE_MAIN_H
#define M_CHOICE_MAIN_H

#include "ultra64.h"
#include "color.h"

#define Choice_CHOICE_STRING_LEN 10

typedef enum Choice_CHOICE {
    Choice_CHOICE0,
    Choice_CHOICE1,
    Choice_CHOICE2,
    Choice_CHOICE3,
    Choice_CHOICE_MAX,
};

typedef enum Choice_AUTOMOVETYPE {
    Choice_AUTOMOVE_STOPPED,
    Choice_AUTOMOVE_INCREMENT_WAIT,
    Choice_AUTOMOVE_INCREMENT,
    Choice_AUTOMOVE_DECREMENT_WAIT,
    Choice_AUTOMOVE_DECREMENT,
    Choice_AUTOMOVE_MAX
};

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


// void func_80065040_jp();
// void func_80065064_jp();
// void func_80065158_jp();
// void func_80065164_jp();
// void func_80065170_jp();
// void func_80065198_jp();
// void func_800651A4_jp();
// void func_80065278_jp();
// void func_80065348_jp();
// void func_800653CC_jp();
// void func_800653DC_jp();
// void func_800654FC_jp();
// void func_80065508_jp();
// void func_80065518_jp();
// void func_80065528_jp();
// void func_80065668_jp();
// void func_8006568C_jp();
// void func_800656C8_jp();
// void func_80065704_jp();
// void func_80065728_jp();
// void func_8006574C_jp();
// void func_80065770_jp();
// void func_80065794_jp();
// void func_800657B8_jp();
// void func_800657DC_jp();
// void func_80065800_jp();
// void func_8006584C_jp();
// void func_8006586C_jp();
// void func_80065890_jp();
// void func_800658B4_jp();
// void func_800658D8_jp();
// void func_800658FC_jp();
// void func_80065920_jp();
// void func_80065944_jp();
// void func_80065968_jp();
// void func_8006598C_jp();
// void func_800659B0_jp();
// void func_800659D4_jp();
// void func_800659F8_jp();
// void func_80065A1C_jp();
// void func_80065A40_jp();
// void func_80065A64_jp();
// void func_80065A88_jp();
// void func_80065AAC_jp();
// void func_80065AD0_jp();
// void func_80065AF4_jp();
// void func_80065B18_jp();
// void func_80065B5C_jp();
// void func_80065B80_jp();
// void func_80065BA4_jp();
// void func_80065BF0_jp();
// void func_80065C10_jp();
// void func_80065C34_jp();
// void func_80065C58_jp();
// void func_80065C7C_jp();
// void func_80065CA0_jp();
// void func_80065CF8_jp();
// void func_80065D90_jp();
// void func_80065EE8_jp();
// void func_80065EF8_jp();
// void func_80065F18_jp();
// void func_80065F38_jp();
// void func_80065F58_jp();
// void func_80065F78_jp();
// void func_80065F98_jp();
// void func_80066068_jp();
// void func_80066094_jp();
// void func_800660DC_jp();
// void func_80066130_jp();
// void func_80066194_jp();
// void func_800665C0_jp();
// void func_800665EC_jp();
// void func_80066634_jp();
// void func_8006666C_jp();
// void func_80066740_jp();
// void func_8006676C_jp();
// void func_800667B4_jp();
// void func_8006680C_jp();
// void func_8006685C_jp();
// void func_800668A4_jp();
// void func_800669A4_jp();
// void func_80066A60_jp();
// void func_80066A80_jp();
// void func_80066B18_jp();
// void func_80066BB0_jp();
// void func_80066D4C_jp();
// void func_80066DFC_jp();
// void func_80066E34_jp();

#endif
