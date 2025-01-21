/**
 * File: voicecheckwork.c
 *
 * Checks whether or not a word can be registered in the dictionary
 */

#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"

s32 osVoiceCheckWord(u8* word) {
    s32 k;
    s32 ret = 0;
    u16 sjis;
    u16 old = '\0';

    for (k = 0; word[k] != 0; k += 2) {
        sjis = (word[k] << 8) + word[k + 1];
        if (((sjis != 'ー') && (sjis < 'ぁ')) || ((sjis > 'ん') && (sjis < 'ァ')) || (sjis == 0x837F) ||
            (sjis > 'ヶ')) {
            ret = CONT_ERR_VOICE_WORD;
        } else if ((k == 0) &&
                   ((sjis == 'ー') || (sjis == 'ん') || (sjis == 'っ') || (sjis == 'ゎ') || (sjis == 'ン') ||
                    (sjis == 'ッ') || (sjis == 'ヮ') || (sjis == 'ヵ') || (sjis == 'ヶ'))) {
            ret = CONT_ERR_VOICE_WORD;
        } else if (((sjis == 'ぁ') || (sjis == 'ァ')) && (old != 'ふ') && (old != 'フ') && (old != 'ヴ')) {
            ret = CONT_ERR_VOICE_WORD;
        } else if (((sjis == 'ぃ') || (sjis == 'ィ')) && (old != 'う') && (old != 'て') && (old != 'で') &&
                   (old != 'ふ') && (old != 'ウ') && (old != 'テ') && (old != 'デ') && (old != 'フ') && (old != 'ヴ')) {
            ret = CONT_ERR_VOICE_WORD;
        } else if (((sjis == 'ぅ') || (sjis == 'ゥ')) && (old != 'と') && (old != 'ど') && (old != 'ふ') &&
                   (old != 'ト') && (old != 'ド') && (old != 'フ') && (old != 'ヴ')) {
            ret = CONT_ERR_VOICE_WORD;
        } else if (((sjis == 'ぇ') || (sjis == 'ェ')) && (old != 'う') && (old != 'し') && (old != 'じ') &&
                   (old != 'ち') && (old != 'ぢ') && (old != 'つ') && (old != 'ふ') && (old != 'ウ') && (old != 'シ') &&
                   (old != 'ジ') && (old != 'チ') && (old != 'ヂ') && (old != 'ツ') && (old != 'フ') && (old != 'ヴ')) {
            ret = CONT_ERR_VOICE_WORD;
        } else if (((sjis == 'ぉ') || (sjis == 'ォ')) && (old != 'う') && (old != 'ふ') && (old != 'ウ') &&
                   (old != 'フ') && (old != 'ヴ')) {
            ret = CONT_ERR_VOICE_WORD;
        } else if (((sjis == 'ゃ') || (sjis == 'ゅ') || (sjis == 'ょ') || (sjis == 'ャ') || (sjis == 'ュ') ||
                    (sjis == 'ョ')) &&
                   (old != 'き') && (old != 'し') && (old != 'ち') && (old != 'に') && (old != 'ひ') && (old != 'み') &&
                   (old != 'り') && (old != 'ぎ') && (old != 'じ') && (old != 'ぢ') && (old != 'び') && (old != 'ぴ') &&
                   (old != 'キ') && (old != 'シ') && (old != 'チ') && (old != 'ニ') && (old != 'ヒ') && (old != 'ミ') &&
                   (old != 'リ') && (old != 'ギ') && (old != 'ジ') && (old != 'ヂ') && (old != 'ビ') && (old != 'ピ') &&
                   (old != 'ヴ')) {
            ret = CONT_ERR_VOICE_WORD;
        } else if ((sjis == 'ー') && ((old == 'ん') || (old == 'っ') || (old == 'ン') || (old == 'ッ'))) {
            ret = CONT_ERR_VOICE_WORD;
        } else if (((sjis == 'ん') || (sjis == 'ン')) && ((old == 'ん') || (old == 'ン'))) {
            ret = CONT_ERR_VOICE_WORD;
        } else if (((old == 'っ') || (old == 'ッ')) &&
                   ((sjis == 'ー') || (sjis == 'あ') || (sjis == 'い') || (sjis == 'う') || (sjis == 'え') ||
                    (sjis == 'お') || (sjis == 'な') || (sjis == 'に') || (sjis == 'ぬ') || (sjis == 'ね') ||
                    (sjis == 'の') || (sjis == 'ま') || (sjis == 'み') || (sjis == 'む') || (sjis == 'め') ||
                    (sjis == 'も') || (sjis == 'や') || (sjis == 'ゆ') || (sjis == 'よ') || (sjis == 'ら') ||
                    (sjis == 'り') || (sjis == 'る') || (sjis == 'れ') || (sjis == 'ろ') || (sjis == 'わ') ||
                    (sjis == 'ゐ') || (sjis == 'ゑ') || (sjis == 'を') || (sjis == 'ん') || (sjis == 'ぁ') ||
                    (sjis == 'ぃ') || (sjis == 'ぅ') || (sjis == 'ぇ') || (sjis == 'ぉ') || (sjis == 'ゃ') ||
                    (sjis == 'ゅ') || (sjis == 'ょ') || (sjis == 'っ') || (sjis == 'ゎ')

                    || (sjis == 'ア') || (sjis == 'イ') || (sjis == 'ウ') || (sjis == 'エ') || (sjis == 'オ') ||
                    (sjis == 'ナ') || (sjis == 'ニ') || (sjis == 'ヌ') || (sjis == 'ネ') || (sjis == 'ノ') ||
                    (sjis == 'マ') || (sjis == 'ミ') || (sjis == 'ム') || (sjis == 'メ') || (sjis == 'モ') ||
                    (sjis == 'ヤ') || (sjis == 'ユ') || (sjis == 'ヨ') || (sjis == 'ラ') || (sjis == 'リ') ||
                    (sjis == 'ル') || (sjis == 'レ') || (sjis == 'ロ') || (sjis == 'ワ') || (sjis == 'ヰ') ||
                    (sjis == 'ヱ') || (sjis == 'ヲ') || (sjis == 'ン') || (sjis == 'ァ') || (sjis == 'ィ') ||
                    (sjis == 'ゥ') || (sjis == 'ェ') || (sjis == 'ォ') || (sjis == 'ャ') || (sjis == 'ュ') ||
                    (sjis == 'ョ') || (sjis == 'ッ') || (sjis == 'ヮ'))) {
            ret = CONT_ERR_VOICE_WORD;
        }

        if (ret != 0) {
            return ret;
        } else {
            old = sjis;
        }
    }

    if ((sjis == 'っ') || (sjis == 'ッ')) {
        ret = CONT_ERR_VOICE_WORD;
    }

    return ret;
}
