#include "m_scene_ftr.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void mScn_Dma2Bank(ObjectExchangeBank* exchange, s32 id, RomOffset vrom, size_t size) {

    if (vrom != NULL) {
        DmaMgr_RequestSyncDebug(exchange->status[id + 3].unk14.vram, vrom, size, "../m_scene_ftr.c", 52);
    }
}

void mScn_KeepMyRoomBankNew(ObjectExchangeBank* exchange, s16 id, size_t size) {
    ObjectStatus* bank = exchange->status + exchange->num;

    bank->id = id;
    bank->vram = (void*)exchange->unk1800;
    bank->segment = (void*)exchange->unk1800;
    bank->size = size;

    if (exchange->num < (OBJECT_EXCHANGE_BANK_MAX - 1)) {
        exchange->unk1800 = ALIGN16(exchange->unk1800 + size);
        exchange->num++;
    }
}

void mScn_ObtainCarpetBank(Game_Play* play) {
    ObjectExchangeBank* exchange = &play->objectExchangeBank;
    s32 i;

    for (i = 0; i < 2; i++) {
        mScn_KeepMyRoomBankNew(exchange, 18, 0x2020);
    }

    for (i = 0; i < 2; i++) {
        mScn_KeepMyRoomBankNew(exchange, 19, 0x1020);
    }
}

s32 mScn_ObtainFurnitureBank(UNUSED Game_Play* play, s32 bank) {
    common_data.clip.unk_020 = bank;
}

void mScn_ObtainMyRoomBank(Game_Play* play) {
    mScn_ObtainCarpetBank(play);
}
