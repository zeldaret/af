/**
 * File: voicecountsyllables.c
 */

#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"

// The VRU can store only 880 semisyllables of words in its dictionary.
// Use this function to determine the semisyllable count before adding a word with osVoiceSetWord,
// to properly see whether it will fit.

void osVoiceCountSyllables(u8* data, u32* syllable) {
    s32 k;
    u16 sjis;
    u16 old;

    old = 0;
    *syllable = 1;
    for (k = 0; data[k] != 0; k += 2) {
        sjis = (data[k] << 8) + data[k + 1];
        if ((sjis == 'あ') || (sjis == 'い') || (sjis == 'う') || (sjis == 'え') || (sjis == 'お') || (sjis == 'ア') ||
            (sjis == 'イ') || (sjis == 'ウ') || (sjis == 'エ') || (sjis == 'オ')) {
            if (k == 0) {
                *syllable += 2;
            } else {
                *syllable += 1;
            }
        } else if ((sjis == 'か') || (sjis == 'き') || (sjis == 'く') || (sjis == 'け') || (sjis == 'こ') ||
                   (sjis == 'た') || (sjis == 'ち') || (sjis == 'つ') || (sjis == 'て') || (sjis == 'と') ||
                   (sjis == 'ぱ') || (sjis == 'ぴ') || (sjis == 'ぷ') || (sjis == 'ぺ') || (sjis == 'ぽ') ||
                   (sjis == 'カ') || (sjis == 'キ') || (sjis == 'ク') || (sjis == 'ケ') || (sjis == 'コ') ||
                   (sjis == 'タ') || (sjis == 'チ') || (sjis == 'ツ') || (sjis == 'テ') || (sjis == 'ト') ||
                   (sjis == 'パ') || (sjis == 'ピ') || (sjis == 'プ') || (sjis == 'ペ') || (sjis == 'ポ')) {
            if (k == 0) {
                *syllable += 2;
            } else if ((old == 'っ') || (old == 'ッ')) {
                *syllable += 2;
            } else {
                *syllable += 3;
            }
        } else if ((sjis == 'ぁ') || (sjis == 'ぃ') || (sjis == 'ぅ') || (sjis == 'ぇ') || (sjis == 'ぉ') ||
                   (sjis == 'ゃ') || (sjis == 'ゅ') || (sjis == 'ょ') || (sjis == 'ゎ')

                   || (sjis == 'ァ') || (sjis == 'ィ') || (sjis == 'ゥ') || (sjis == 'ェ') || (sjis == 'ォ') ||
                   (sjis == 'ャ') || (sjis == 'ュ') || (sjis == 'ョ') || (sjis == 'ヮ') || (sjis == 'ヵ') ||
                   (sjis == 'ヶ')) {
            if ((old == 'あ') || (old == 'い') || (old == 'う') || (old == 'え') || (old == 'お') || (old == 'ア') ||
                (old == 'イ') || (old == 'ウ') || (old == 'エ') || (old == 'オ')) {
                *syllable += 1;
            }
        } else if ((sjis == 'ん') || (sjis == 'ー') || (sjis == 'っ') || (sjis == 'ン') || (sjis == 'ッ')) {
            *syllable += 1;
        } else {
            *syllable += 2;
        }
        old = sjis;
    }
}
