#include "m_choice_main.h"
#include "m_msg_main.h"
#include "game.h"
#include "m_actor.h"
#include "gfx.h"
#include "m_std_dma.h"
#include "audio.h"
#include "m_lib.h"
#include "sys_matrix.h"
#include "6B3DC0.h"

extern u32 D_D06000[];
extern u32 D_D05000[];

Choice* mChoice_Get_base_window_p() {
    return &mMsg_Get_base_window_p()->choiceWindow;
}

void mChoice_init(Choice* choice, UNUSED Game* game) {
    choice->centerX = 191.0f;
    choice->centerY = 83.0f;

    choice->textX = 104.0;
    choice->textY = 96.0f;

    choice->textColor.r = 180;
    choice->textColor.g = 150;
    choice->textColor.b = 110;
    choice->textColor.a = 255;

    choice->textScaleX = 1.0f;
    choice->textScaleY = 1.0f;

    choice->scaleX = 1.0f;
    choice->scaleY = 1.0f;

    choice->data.choiceNum = Choice_CHOICE_MAX;
    choice->selectedChoiceIdx = Choice_CHOICE0;

    choice->selectedChoiceTextColor.r = 120;
    choice->selectedChoiceTextColor.g = 50;
    choice->selectedChoiceTextColor.b = 50;
    choice->selectedChoiceTextColor.a = 255;

    choice->backgroundColor.r = 0;
    choice->backgroundColor.g = 195;
    choice->backgroundColor.b = 185;
    choice->backgroundColor.a = 255;

    choice->choiceAutomoveTimer = 0.0f;

    choice->scale = 0.0f;

    choice->mainIdx = 0;
    choice->requestedMainIdx = -1;
    choice->isWindowVisible = FALSE;
    choice->isFontVisible = FALSE;
    choice->choiceAutomoveType = Choice_AUTOMOVE_STOPPED;
    choice->choiceAutomoveTimer = 0.0f;
    choice->unk_D4 = 232.0f;
    choice->timer = 0.0f;
    choice->noBFlag = FALSE;

    choice->unk_D8 = 104.0f;
}

void mChoice_Change_request_main_index(Choice* choice, s32 idx) {
    choice->requestedMainIdx = idx;
}

s32 mChoice_check_main_index(Choice* choice) {
    return choice->mainIdx;
}

s32 mChoice_check_main_normal(Choice* choice) {
    return mChoice_check_main_index(choice) == 2;
}

void mChoice_Init_choice_data(Choice* choice) {
    choice->data.choiceNum = Choice_CHOICE0;
}

s32 mChoice_Add_choice_data(Choice* choice, char* str, s32 max_len) {
    if (str != NULL && max_len > 0 && max_len < 11) {
        s32 len;
        int idx;
        s32* t;
        char* dst;
        s32 i;

        t = &choice->data.choiceNum;
        if (choice->data.choiceNum < Choice_CHOICE_MAX) {
            idx = *t;
            len = mMsg_Get_Length_String(str, max_len);
            dst = choice->data.strings[idx];

            for (i = 0; i < len; i++) {
                *dst++ = *str++;
            }

            choice->data.stringLens[idx] = len;
            *t += 1;
            return idx;
        }
    }

    return -1;
}

void mChoice_Set_choice_data(Choice* choice, char* str0, s32 str0len, char* str1, s32 str1len, char* str2, s32 str2len,
                             char* str3, s32 str3len) {
    mChoice_Init_choice_data(choice);

    if (str0 != NULL && str0len > 0 && str0len <= Choice_CHOICE_STRING_LEN) {
        mChoice_Add_choice_data(choice, str0, str0len);
    }

    if (str1 != NULL && str1len > 0 && str1len <= Choice_CHOICE_STRING_LEN) {
        mChoice_Add_choice_data(choice, str1, str1len);
    }

    if (str2 != NULL && str2len > 0 && str2len <= Choice_CHOICE_STRING_LEN) {
        mChoice_Add_choice_data(choice, str2, str2len);
    }

    if (str3 != NULL && str3len > 0 && str3len <= Choice_CHOICE_STRING_LEN) {
        mChoice_Add_choice_data(choice, str3, str3len);
    }
}

s32 mChoice_Get_MaxStringDotWidth(Choice* choice) {
    s32 i;
    s32 choiceNum = choice->data.choiceNum;
    s32 maxWidth = 0;

    for (i = 0; i < choiceNum; i++) {
        char* str = choice->data.strings[i];
        s32 len = choice->data.stringLens[i];
        s32 width = mFont_GetStringWidth(str, len, 0);

        if (width > maxWidth) {
            maxWidth = width;
        }
    }

    return maxWidth;
}

s32 mChoice_Get_MaxStringDotHeight(Choice* choice) {
    return choice->data.choiceNum * 16;
}

void mChoice_Set_DisplayScaleAndDisplayPos(Choice* choice) {
    f32 dotW = ((f32)mChoice_Get_MaxStringDotWidth(choice) - 24) / 96;
    f32 dotH = ((f32)mChoice_Get_MaxStringDotHeight(choice) - 32) / 32;

    {
        f32 scaleX = (0.5833334f * dotW);
        f32 scaleY = (0.3142857f * dotH);

        choice->scaleX = 0.41666666f + scaleX;
        choice->scaleY = 0.6857143f + scaleY;
    }

    {
        f32 t0 = (-48.0f * dotW);
        f32 t1 = (-20.057144f * dotH);

        choice->textX = 152.0f + t0;
        choice->textY = 105.0f + t1;
    }

    {
        f32 t0 = (-35.0f * dotW);
        f32 t1 = (20.057144f * dotH);

        choice->centerX = 242.0f;
        choice->centerY = 169.0f;
        choice->centerXBegin = choice->centerX;
        choice->centerYBegin = choice->centerY;
        choice->centerXTarget = choice->centerX + t0;
        choice->centerYTarget = choice->centerY + t1;
    }
}

s32 mChoice_Get_ChoseNum(Choice* choice) {
    return choice->data.selectedChoiceIdx;
}

void mChoice_Clear_ChoseNum(Choice* choice) {
    choice->data.selectedChoiceIdx = -1;
}

void mChoice_check_ct(UNUSED Choice* choice, UNUSED Game* game) {
}
void mChoice_Get_StringDataAddressAndSize(s32 idx, u32** addr, u32* size) {
    s32 sizeCalc;
    s32 temp0;
    s32 temp1;
    u32 vram[3];

    if (idx >= 0 && idx < 460) {
        u32 vrom;
        if (idx & 1) {
            temp0 = idx - 1;

            DmaMgr_RequestSyncDebug(vram, (uintptr_t)&D_D06000[temp0], 8, "../m_choice_main.c", 454);
            vrom = vram[0];
            sizeCalc = vram[1] - vrom;
        } else if (idx == 0) {
            DmaMgr_RequestSyncDebug(vram, (uintptr_t)&D_D06000[0], 8, "../m_choice_main.c", 461);
            vrom = 0;
            sizeCalc = vram[0];
        } else {
            temp1 = idx - 2;

            DmaMgr_RequestSyncDebug(vram, (uintptr_t)&D_D06000[temp1], 16, "../m_choice_main.c", 467);
            vrom = vram[1];
            sizeCalc = vram[2] - vrom;
        }

        if (sizeCalc < 11) {
            *addr = (u32*)((uintptr_t)vrom + (uintptr_t)&D_D05000);
            *size = sizeCalc;
        } else {
            *addr = NULL;
            *size = NULL;
        }
    } else {
        *addr = NULL;
        *size = NULL;
    }
}

s32 mChoice_Put_String_PLAYER_NAME(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopyPlayerName(data, idx, maxSize);
}

s32 mChoice_Put_String_TALK_NAME(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mMsg_CopyTalkName(actor, data, idx, maxSize);
}

s32 mChoice_Put_String_TAIL(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mMsg_CopyTail(actor, data, idx, maxSize);
}

s32 mChoice_Put_String_YEAR(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopyYear(data, idx, maxSize);
}

s32 mChoice_Put_String_MONTH(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopyMonth(data, idx, maxSize);
}

s32 mChoice_Put_String_WEEK(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopyWeek(data, idx, maxSize);
}

s32 mChoice_Put_String_DAY(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopyDay(data, idx, maxSize);
}

s32 mChoice_Put_String_HOUR(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopyHour(data, idx, maxSize);
}

s32 mChoice_Put_String_MIN(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopyMin(data, idx, maxSize);
}

s32 mChoice_Put_String_SEC(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopySec(data, idx, maxSize);
}

s32 mChoice_Put_String_FREE(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor, s32 freeIdx) {
    return mMsg_CopyFree(mMsg_Get_base_window_p(), freeIdx, data, idx, maxSize);
}

s32 mChoice_Put_String_FREE0(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 0);
}

s32 mChoice_Put_String_FREE1(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 1);
}

s32 mChoice_Put_String_FREE2(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 2);
}

s32 mChoice_Put_String_FREE3(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 3);
}

s32 mChoice_Put_String_FREE4(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 4);
}

s32 mChoice_Put_String_FREE5(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 5);
}

s32 mChoice_Put_String_FREE6(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 6);
}

s32 mChoice_Put_String_FREE7(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 7);
}

s32 mChoice_Put_String_FREE8(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 8);
}

s32 mChoice_Put_String_FREE9(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 9);
}

s32 mChoice_Put_String_FREE10(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 10);
}

s32 mChoice_Put_String_FREE11(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 11);
}

s32 mChoice_Put_String_FREE12(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 12);
}

s32 mChoice_Put_String_FREE13(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 13);
}

s32 mChoice_Put_String_FREE14(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 14);
}

s32 mChoice_Put_String_FREE15(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 15);
}

s32 mChoice_Put_String_FREE16(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 16);
}

s32 mChoice_Put_String_FREE17(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 17);
}

s32 mChoice_Put_String_FREE18(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 18);
}

s32 mChoice_Put_String_FREE19(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_FREE(data, idx, maxSize, actor, 19);
}

s32 mChoice_Put_String_DETERMINATION(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopyDetermination(mMsg_Get_base_window_p(), data, idx, maxSize);
}

s32 mChoice_Put_String_COUNTRY_NAME(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopyCountryName(data, idx, maxSize);
}

s32 mChoice_Put_String_RAMDOM_NUMBER2(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor) {
    return mMsg_CopyRamdomNumber2(data, idx, maxSize);
}

s32 mChoice_Put_String_ITEM(char* data, s32 idx, s32 maxSize, UNUSED Actor* actor, s32 itemIdx) {
    return mMsg_CopyItem(mMsg_Get_base_window_p(), itemIdx, data, idx, maxSize);
}

s32 mChoice_Put_String_ITEM0(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_ITEM(data, idx, maxSize, actor, 0);
}

s32 mChoice_Put_String_ITEM1(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_ITEM(data, idx, maxSize, actor, 1);
}

s32 mChoice_Put_String_ITEM2(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_ITEM(data, idx, maxSize, actor, 2);
}

s32 mChoice_Put_String_ITEM3(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_ITEM(data, idx, maxSize, actor, 3);
}

s32 mChoice_Put_String_ITEM4(char* data, s32 idx, s32 maxSize, Actor* actor) {
    return mChoice_Put_String_ITEM(data, idx, maxSize, actor, 4);
}

typedef s32 (*ChoicePutStringProc)(char*, s32, s32, Actor*);

s32 mChoice_Put_String(char* data, s32 idx, s32 maxSize, Actor* actor) {
    static ChoicePutStringProc proc[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &mChoice_Put_String_PLAYER_NAME,
        &mChoice_Put_String_TALK_NAME,
        &mChoice_Put_String_TAIL,
        &mChoice_Put_String_YEAR,
        &mChoice_Put_String_MONTH,
        &mChoice_Put_String_WEEK,
        &mChoice_Put_String_DAY,
        &mChoice_Put_String_HOUR,
        &mChoice_Put_String_MIN,
        &mChoice_Put_String_SEC,
        &mChoice_Put_String_FREE0,
        &mChoice_Put_String_FREE1,
        &mChoice_Put_String_FREE2,
        &mChoice_Put_String_FREE3,
        &mChoice_Put_String_FREE4,
        &mChoice_Put_String_FREE5,
        &mChoice_Put_String_FREE6,
        &mChoice_Put_String_FREE7,
        &mChoice_Put_String_FREE8,
        &mChoice_Put_String_FREE9,
        &mChoice_Put_String_DETERMINATION,
        &mChoice_Put_String_COUNTRY_NAME,
        &mChoice_Put_String_RAMDOM_NUMBER2,
        &mChoice_Put_String_ITEM0,
        &mChoice_Put_String_ITEM1,
        &mChoice_Put_String_ITEM2,
        &mChoice_Put_String_ITEM3,
        &mChoice_Put_String_ITEM4,
        &mChoice_Put_String_FREE10,
        &mChoice_Put_String_FREE11,
        &mChoice_Put_String_FREE12,
        &mChoice_Put_String_FREE13,
        &mChoice_Put_String_FREE14,
        &mChoice_Put_String_FREE15,
        &mChoice_Put_String_FREE16,
        &mChoice_Put_String_FREE17,
        &mChoice_Put_String_FREE18,
        &mChoice_Put_String_FREE19,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };

    s32 type = data[idx + 1];

    if (type >= 0 && type < 97 && proc[type] != NULL) {
        return (*proc[type])(data, idx, maxSize, actor);
    }

    return maxSize;
}

void mChoice_Change_ControlCode(char* data, s32 maxSize, Actor* actor) {
    s32 idx;
    s32 newSize;

    newSize = maxSize;
    idx = 0;

    for (idx = 0; idx < newSize;) {
        char* src;
        char code;

        src = &data[idx];
        code = *src;
        if (code == 0x7F) {
            newSize = mChoice_Put_String(data, idx, newSize, actor);
        } else {
            idx++;
        };
    };
}

void mChoice_Load_ChoseStringFromRom(UNUSED s32 unused, char* str, s32 idx, Actor* actor) {
    if (idx >= 0 && idx < 460) {
        u32* addr;
        u32 size;

        mChoice_Get_StringDataAddressAndSize(idx, &addr, &size);

        if (size == 0) {
            mem_clear((u8*)str, Choice_CHOICE_STRING_LEN, ' ');
        } else if (addr != NULL) {
            char vram[29];
            s32 alignedSize = ((u32)addr & ~7);
            s32 ofs = (u32)addr - alignedSize;

            DmaMgr_RequestSyncDebug(&vram, alignedSize, ALIGN8(ofs + size), "../m_choice_main.c", 1168);

            {
                s32 len;
                char* dst;
                char* src;
                s32 i;

                if (size < Choice_CHOICE_STRING_LEN) {
                    len = size;
                } else {
                    len = Choice_CHOICE_STRING_LEN;
                }

                dst = str;
                src = (char*)&vram[ofs];

                for (i = 0; i < len; i++) {
                    *dst++ = *src++;
                }

                for (; i < Choice_CHOICE_STRING_LEN; i++) {
                    *dst++ = ' ';
                }

                mChoice_Change_ControlCode(str, Choice_CHOICE_STRING_LEN, actor);
            }
        }
    }
}
void mChoice_no_b_set(Choice* choice) {
    choice->noBFlag = TRUE;
}

void mChoice_sound_SENTAKU_KETTEI() {
    sAdo_SysTrgStart(0xD);
}

void mChoice_sound_SENTAKU_OPEN() {
    sAdo_SysTrgStart(0xC);
}

void mChoice_sound_CURSOL() {
    sAdo_SysTrgStart(1);
}

void mChoice_Main_Hide(Choice* choice, Game* game) {
    mChoice_MainSetup(choice, game);
}

void mChoice_MainSetup_Hide(Choice* choice, Game* game) {
    mChoice_init(choice, game);
}

s32 mChoice_Main_Appear_SetScale(Choice* choice, UNUSED Game* game) {
    f32 max = 5.1f;

    if (choice->timer < max) {
        f32 scale;

        choice->timer += 1.0f;
        scale = get_percent_forAccelBrake(choice->timer, 0.0f, max, 0.0f, 0.0f);
        choice->scale = scale;
        choice->centerX = choice->centerXBegin + scale * (choice->centerXTarget - choice->centerXBegin);
        choice->centerY = choice->centerYBegin + scale * (choice->centerYTarget - choice->centerYBegin);
        return FALSE;
    } else {
        choice->timer = 0.0f;
        choice->scale = 1.0f;
        choice->centerX = choice->centerXTarget;
        choice->centerY = choice->centerYTarget;
        return TRUE;
    }
}

void mChoice_request_main_index_fromAppear(Choice* choice, UNUSED Game* game, s32 flag) {
    if (flag) {
        mChoice_Change_request_main_index(choice, 2);
    }
}

void mChoice_Main_Appear(Choice* choice, Game* game) {
    s32 flag = mChoice_Main_Appear_SetScale(choice, game);

    mChoice_request_main_index_fromAppear(choice, game, flag);
    mChoice_MainSetup(choice, game);
}

void mChoice_MainSetup_Appear(Choice* choice, UNUSED Game* game) {
    choice->scale = 0.0f;
    choice->mainIdx = 1;
    choice->requestedMainIdx = -1;
    choice->isWindowVisible = TRUE;
    choice->timer = 0.0f;
    mChoice_Clear_ChoseNum(choice);
    mChoice_sound_SENTAKU_OPEN();
    mChoice_Set_DisplayScaleAndDisplayPos(choice);
}

void mChoice_determimation_set(Choice* choice) {
    ChoiceData* choiceData = &choice->data;
    s32 idx = choice->selectedChoiceIdx;

    bcopy(choiceData->strings[idx], choiceData->determinationString, Choice_CHOICE_STRING_LEN);
    choiceData->determinationLenght = choiceData->stringLens[idx];
    choiceData->selectedChoiceIdx = idx;
}

s32 mChoice_Main_Normal_SetChoice(Choice* choice, UNUSED Game* game) {
    s32 res = FALSE;

    if (chkTrigger(A_BUTTON)) {
        mChoice_determimation_set(choice);
        res = TRUE;
    } else if (choice->noBFlag && chkTrigger(B_BUTTON)) {
        choice->selectedChoiceIdx = choice->data.choiceNum - 1;
        mChoice_determimation_set(choice);
        res = TRUE;
    } else {
        f32 percent = gamePT->controller.adjustedY;
        s32* choiceAutomove = &choice->choiceAutomoveType;
        f32* choiceAutomoveTimer = &choice->choiceAutomoveTimer;
        s32* selectedIdx = &choice->selectedChoiceIdx;
        s32 sfx = FALSE;

        switch (*choiceAutomove) {
            case Choice_AUTOMOVE_INCREMENT_WAIT: {
                if (percent < 0.0f || chkButton(D_CBUTTONS)) {
                    (*choiceAutomoveTimer) += 1.0f;

                    if (*choiceAutomoveTimer >= 9.0f) {
                        *choiceAutomoveTimer = 0.0f;
                        *choiceAutomove = Choice_AUTOMOVE_INCREMENT;
                        (*selectedIdx)++;
                        sfx = TRUE;
                    }
                } else {
                    *choiceAutomove = Choice_AUTOMOVE_STOPPED;
                    *choiceAutomoveTimer = 0.0f;
                }

                break;
            }

            case Choice_AUTOMOVE_INCREMENT: {
                if (percent < 0.0f || chkButton(D_CBUTTONS)) {
                    (*choiceAutomoveTimer) += 1.0f;

                    if (*choiceAutomoveTimer >= 4.5f) {
                        *choiceAutomoveTimer = 0.0f;
                        (*selectedIdx)++;
                        sfx = TRUE;
                    }
                } else {
                    *choiceAutomove = Choice_AUTOMOVE_STOPPED;
                    *choiceAutomoveTimer = 0.0f;
                }

                break;
            }

            case Choice_AUTOMOVE_DECREMENT_WAIT: {
                if (percent > 0.0f || chkButton(U_CBUTTONS)) {
                    (*choiceAutomoveTimer) += 1.0f;

                    if (*choiceAutomoveTimer >= 9.0f) {
                        *choiceAutomoveTimer = 0.0f;
                        *choiceAutomove = Choice_AUTOMOVE_DECREMENT;
                        (*selectedIdx)--;
                        sfx = TRUE;
                    }
                } else {
                    *choiceAutomove = Choice_AUTOMOVE_STOPPED;
                    *choiceAutomoveTimer = 0.0f;
                }

                break;
            }

            case Choice_AUTOMOVE_DECREMENT: {
                if (percent > 0.0f || chkButton(U_CBUTTONS)) {
                    (*choiceAutomoveTimer) += 1.0f;

                    if (*choiceAutomoveTimer >= 4.5f) {
                        *choiceAutomoveTimer = 0.0f;
                        (*selectedIdx)--;
                        sfx = TRUE;
                    }
                } else {
                    *choiceAutomove = Choice_AUTOMOVE_STOPPED;
                    *choiceAutomoveTimer = 0.0f;
                }

                break;
            }

            default: {
                if (percent > 0.0f || chkTrigger(U_CBUTTONS)) {
                    *choiceAutomove = Choice_AUTOMOVE_DECREMENT_WAIT;
                    *choiceAutomoveTimer = 0.0f;
                    (*selectedIdx)--;
                    sfx = TRUE;
                } else if (percent < 0.0f || chkTrigger(D_CBUTTONS)) {
                    *choiceAutomove = Choice_AUTOMOVE_INCREMENT_WAIT;
                    *choiceAutomoveTimer = 0.0f;
                    (*selectedIdx)++;
                    sfx = TRUE;
                }

                break;
            }
        }

        if ((*selectedIdx) < 0) {
            *selectedIdx = 0;
        } else if ((*selectedIdx) >= choice->data.choiceNum) {
            *selectedIdx = choice->data.choiceNum - 1;
        } else {
            if (sfx) {
                mChoice_sound_CURSOL();
            }
        }
    }

    return res;
}

void mChoice_request_main_index_fromNormal(Choice* choice, UNUSED Game* game, s32 flag) {
    if (flag) {
        mChoice_Change_request_main_index(choice, 3);
    }
}

void mChoice_Main_Normal(Choice* choice, Game* game) {
    s32 flag = mChoice_Main_Normal_SetChoice(choice, game);

    mChoice_request_main_index_fromNormal(choice, game, flag);
    mChoice_MainSetup(choice, game);
}

void mChoice_MainSetup_Normal(Choice* choice, UNUSED Game* game) {
    choice->scale = 1.0f;
    choice->timer = 0.0f;
    choice->requestedMainIdx = -1;
    choice->mainIdx = 2;
    choice->isFontVisible = TRUE;
}

s32 mChoice_Main_Disappear_SetScale(Choice* choice, UNUSED Game* game) {
    f32 max = 5.1f;

    if (choice->timer < max) {
        f32 scale;

        choice->timer += 1.0f;
        scale = 1.0f - get_percent_forAccelBrake(choice->timer, 0.0f, max, 0.0f, 0.0f);
        choice->scale = scale;
        choice->centerX = choice->centerXBegin + scale * (choice->centerXTarget - choice->centerXBegin);
        choice->centerY = choice->centerYBegin + scale * (choice->centerYTarget - choice->centerYBegin);
        return FALSE;
    } else {
        choice->timer = 0.0f;
        choice->scale = 0.0f;
        choice->centerX = choice->centerXBegin;
        choice->centerY = choice->centerYBegin;
        return TRUE;
    }
}

void mChoice_request_main_index_fromDisappear(Choice* choice, UNUSED Game* game, s32 flag) {
    if (flag) {
        mChoice_Change_request_main_index(choice, 0);
    }
}
void mChoice_Main_Disappear(Choice* choice, Game* game) {
    s32 flag = mChoice_Main_Disappear_SetScale(choice, game);

    mChoice_request_main_index_fromDisappear(choice, game, flag);
    mChoice_MainSetup(choice, game);
}

void mChoice_MainSetup_Disappear(Choice* choice, UNUSED Game* game) {
    mChoice_sound_SENTAKU_KETTEI();
    choice->mainIdx = 3;
    choice->requestedMainIdx = -1;
    choice->isWindowVisible = TRUE;
    choice->isFontVisible = FALSE;
    choice->scale = 1.0f;
    choice->timer = 0.0f;
}

typedef void (*ChoiceMainProc)(Choice*, Game*);

void mChoice_MainSetup(Choice* choice, Game* game) {
    static ChoiceMainProc proc[] = {
        &mChoice_MainSetup_Hide,
        &mChoice_MainSetup_Appear,
        &mChoice_MainSetup_Normal,
        &mChoice_MainSetup_Disappear,
    };

    s32 index = choice->requestedMainIdx;

    if (index < 0) {
        return;
    } else if (index < 0 || index >= 4 || proc[index] == NULL) {
        return;
    }

    (*proc[index])(choice, game);
}

void mChoice_Main(Choice* choice, Game* game) {
    static ChoiceMainProc proc[] = {
        &mChoice_Main_Hide,
        &mChoice_Main_Appear,
        &mChoice_Main_Normal,
        &mChoice_Main_Disappear,
    };

    s32 index = choice->mainIdx;

    if (index < 0 || index >= 4 || proc[index] == NULL) {
        return;
    }

    (*proc[index])(choice, game);
}

void mChoice_SetMatrix(Choice* choice, Game* game, s32 type) {
    GraphicsContext* graph = game->gfxCtx;
    f32 scale = choice->scale;
    f32 x = (choice->centerX - 160.0f) * 16.0f;
    f32 y = (-choice->centerY + 120.0f) * 16.0f;

    Matrix_push();
    Matrix_translate(x, y, 0.0f, 1);
    Matrix_scale(scale, scale, 1.0f, 1);

    OPEN_DISPS(graph);

    if (type == 1) {
        gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    } else {
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }

    CLOSE_DISPS(graph);
}

void mChoice_SetMatrixDisplay(Choice* choice, Game* game, s32 type) {
    GraphicsContext* graph = game->gfxCtx;
    f32 scaleX = choice->scaleX;
    f32 scaleY = choice->scaleY;

    Matrix_push();
    Matrix_scale(scaleX, scaleY, 1.0f, 1);

    OPEN_DISPS(graph);

    if (type == 1) {
        gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    } else {
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }

    CLOSE_DISPS(graph);
}

void mChoice_UnSetMatrix() {
    Matrix_pull();
}

void mChoice_UnSetMatrixDisplay(Game* game, s32 type) {
    GraphicsContext* graph = game->gfxCtx;

    Matrix_pull();

    OPEN_DISPS(graph);

    if (type == 1) {
        gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    } else {
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }

    CLOSE_DISPS(graph);
}

extern Vtx con_sentaku2_v[];
#include "assets/jp/code/m_choice_main/con_sentaku2_v.vtx.inc.c"

u8 con_waku_swaku3_tex[] = {
#include "assets/jp/code/m_choice_main/con_waku_swaku3_tex.i4.inc.c"
};

Gfx con_sentaku2_modelT[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetPrimColor(0, 255, 255, 255, 155, 255),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock_4b(con_waku_swaku3_tex, G_IM_FMT_I, 128, 64, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(con_sentaku2_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx mChoice_init_disp[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

void mChoice_DrawWindowBody(UNUSED Choice* choice, Game* game, s32 type) {
    GraphicsContext* graph = game->gfxCtx;

    OPEN_DISPS(graph);

    if (type == 1) {
        gSPDisplayList(FONT_DISP++, mChoice_init_disp);
        gSPDisplayList(FONT_DISP++, con_sentaku2_modelT);
    } else {
        gSPDisplayList(POLY_OPA_DISP++, mChoice_init_disp);
        gSPDisplayList(POLY_OPA_DISP++, con_sentaku2_modelT);
    }

    CLOSE_DISPS(graph);
}

void mChoice_DrawFont(Choice* choice, Game* game, s32 type) {
    s32 i;
    s32 choice_num;
    f32 x;
    f32 y;
    s32 selected_idx;

    x = choice->textX;
    y = choice->textY;
    choice_num = choice->data.choiceNum;
    selected_idx = choice->selectedChoiceIdx;

    for (i = 0; i < choice_num; i++) {
        s32 r;
        s32 g;
        s32 b;
        if (i == selected_idx) {
            r = choice->selectedChoiceTextColor.r;
            g = choice->selectedChoiceTextColor.g;
            b = choice->selectedChoiceTextColor.b;
            mFont_SetMarkChar(game, 4, x - 16.0f, y, choice->backgroundColor.r, choice->backgroundColor.g,
                              choice->backgroundColor.b, 255, FALSE, 1.0f, 1.0f, type);
        } else {
            r = choice->textColor.r;
            g = choice->textColor.g;
            b = choice->textColor.b;
        }

        mFont_SetLineStrings_AndSpace(game, choice->data.strings[i], choice->data.stringLens[i], x, y, r, g, b, 255,
                                      FALSE, FALSE, 0, 1.0f, 1.0f, type);

        y += 16.0f;
    }
}

void mChoice_Draw(Choice* choice, Game* game, s32 mode) {
    if (choice->isWindowVisible) {
        mFont_SetMatrix(game->gfxCtx, mode);
        mChoice_SetMatrix(choice, game, mode);
        mChoice_SetMatrixDisplay(choice, game, mode);
        mChoice_DrawWindowBody(choice, game, mode);
        mChoice_UnSetMatrixDisplay(game, mode);
        mChoice_DrawFont(choice, game, mode);
        mChoice_UnSetMatrix();
        mFont_UnSetMatrix(game->gfxCtx, mode);
    }
}

void mChoice_ct(Choice* choice, Game* game) {
    mChoice_check_ct(choice, game);
    mChoice_init(choice, game);
}

void mChoice_dt(UNUSED Choice* choice, UNUSED Game* game) {
}
