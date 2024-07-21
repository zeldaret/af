#include "m_mail_check.h"
#include "segment_symbols.h"
#include "game.h"
#include "ovlmgr.h"
#include "m_malloc.h"

typedef s32 (*MailCheckOvlUnkFunc)(s32* len, u8* str);

extern s32 mMck_check_key_hit(s32* len, u8* str);

s32 mMC_get_mail_hit_rate(s32* len, u8* str, Game* game) {
    void* buf;
    MailCheckOvlUnkFunc func;
    s32 ret;

    if (game != NULL) {
        buf = gamealloc_malloc(&game->alloc, SEGMENT_VRAM_SIZE(m_mail_check_ovl));
    } else {
        buf = zelda_malloc(SEGMENT_VRAM_SIZE(m_mail_check_ovl));
    }

    ovlmgr_Load(SEGMENT_ROM_START(m_mail_check_ovl), SEGMENT_ROM_END(m_mail_check_ovl),
                SEGMENT_VRAM_START(m_mail_check_ovl), SEGMENT_VRAM_END(m_mail_check_ovl), buf);
    func = (MailCheckOvlUnkFunc)SEGMENT_VRAM_RESOLVE_ADDR(m_mail_check_ovl, buf, mMck_check_key_hit);

    ret = func(len, str);

    if (game != NULL) {
        gamealloc_free(&game->alloc, buf);
    } else {
        zelda_free(buf);
    }

    return ret;
}
