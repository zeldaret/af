#include "prevent_bss_reordering.h"
#include "stack.h"
#include "libu64/stackcheck.h"
#include "unk.h"

StackEntry sDmaMgrStackInfo;
u16 sNumDmaEntries;
OSMesgQueue sDmaMgrMsgQueue;
OSMesg dmaEntryMsgBufs[0x20];
OSThread sDmaMgrThread;
STACK(sDmaMgrStack, 0x500);
const char* sDmaMgrCurFileName;
UNK_TYPE sDmaMgrCurFileLine;
size_t B_800406B0_jp;
size_t B_800406B4_jp;

#include "z_std_dma.h"
#include "carthandle.h"
#include "fault.h"
#include "irqmgr.h"
#include "yaz0.h"
#include "libc/stdbool.h"
#include "m_thread.h"
#include "macros.h"
#include "attributes.h"
#include "segment_symbols.h"

size_t gDmaMgrDmaBuffSize = DMAMGR_DEFAULT_BUFSIZE;

/**
 * DMA error encountered, print error messages and bring up the crash screen.
 *
 * @param req DMA Request causing the error.
 * @param file DMA data filename associated with the operation that errored.
 * @param errorName Error name string.
 * @param errorDesc Error description string.
 *
 * This function does not return.
 */
NORETURN void DmaMgr_Error(DmaRequest* req, const char* file, const char* errorName, const char* errorDesc) {
    RomOffset vrom = req->vrom;
    void* vram = req->vram;
    size_t size = req->size;
    char buff1[80];
    char buff2[80];

    (void)(errorDesc != NULL ? errorDesc : (errorName != NULL ? errorName : "???"));
    (void)(file != NULL ? file : "???");

    if (req->filename != NULL) {
    } else if (sDmaMgrCurFileName != NULL) {
    }

    if (req->filename != NULL) {
        sprintf(buff1, "DMA ERROR: %.50s %d", req->filename, req->line);
    } else if (sDmaMgrCurFileName != NULL) {
        sprintf(buff1, "DMA ERROR: %.50s %d", sDmaMgrCurFileName, sDmaMgrCurFileLine);
    } else {
        sprintf(buff1, "DMA ERROR: %.50s", (errorName != NULL) ? errorName : "???");
    }

    sprintf(buff2, "%07X %08X %X %.50s", vrom, vram, size, (file != NULL) ? file : "???");
    fault_AddHungupAndCrashImpl(buff1, buff2);
}

/**
 * Transfer `size` bytes from physical ROM address `vrom` to `vram`.
 *
 * This function is intended for internal use only, however it is possible to use this function externally in which
 * case it behaves as a synchronous transfer, data is available as soon as this function returns.
 *
 * Transfers are divided into chunks based on the current value of `gDmaMgrDmaBuffSize` to avoid congestion of the PI
 * so that higher priority transfers can still be carried out in a timely manner. The transfers are sent in a queue to
 * the OS PI Manager which performs the transfer.
 *
 * The `vrom` address and the `size` are expected to be at least 0x2 aligned, while the destination `vram` should be 0x8
 * aligned, otherwise a fatal error will be triggered.
 *
 * @return 0 if successful, -1 if the DMA could not be queued with the PI Manager.
 */
s32 DmaMgr_DmaRomToRam(RomOffset vrom, void* vram, size_t size) {
    OSIoMesg ioMsg;
    OSMesgQueue queue;
    OSMesg msg[1];
    s32 ret;
    size_t buffSize = gDmaMgrDmaBuffSize;
    DmaRequest req;

    if (((vrom << 31) != 0) || (((u32)vram << 29) != 0) || ((size << 31) != 0)) {
        req.vrom = vrom;
        req.vram = vram;
        req.size = size;
        req.filename = "percial_DMA";
        req.line = 0;
        // "alignment error"
        DmaMgr_Error(&req, NULL, "ILLIGAL ALIGNMENT", "アライメント異常");
    }

    osInvalDCache(vram, size);
    osCreateMesgQueue(&queue, msg, ARRAY_COUNT(msg));

    if (buffSize > 0) {
        while (size > buffSize) {
            // The system avoids large DMAs as these would stall the PI for too long, potentially causing issues with
            // audio. To allow audio to continue to DMA whenever it needs to, other DMAs are split into manageable
            // chunks.

            ioMsg.hdr.pri = 0;
            ioMsg.hdr.retQueue = &queue;
            ioMsg.devAddr = vrom;
            ioMsg.dramAddr = vram;
            ioMsg.size = buffSize;
            B_800406B0_jp += buffSize;

            //! FAKE
            if (1) {}
            if (1) {}

            ret = osEPiStartDma(carthandle, &ioMsg, 0);
            if (ret != 0) {
                goto end;
            }

            osRecvMesg(&queue, NULL, OS_MESG_BLOCK);
            size -= buffSize;
            vrom += buffSize;
            vram = (void*)((uintptr_t)vram + buffSize);
        }
    }

    ioMsg.hdr.pri = 0;
    ioMsg.hdr.retQueue = &queue;
    ioMsg.devAddr = vrom;
    ioMsg.dramAddr = vram;
    ioMsg.size = size;
    B_800406B0_jp += size;

    ret = osEPiStartDma(carthandle, &ioMsg, 0);
    if (ret != 0) {
        goto end;
    }

    osRecvMesg(&queue, NULL, OS_MESG_BLOCK);
    osInvalDCache(vram, size);

end:
    return ret;
}

/**
 * Callback function to facilitate audio DMA. Audio DMA does not use the request queue as audio data is often needed
 * very soon after the request is sent, requiring a higher priority method for enqueueing a DMA on the OS PI command
 * queue.
 *
 * @param pihandle Cartridge ROM PI Handle.
 * @param mb IO Message describing the transfer.
 * @param direction Read or write. (Only read is allowed)
 * @return 0 if the IO Message was successfully put on the OS PI command queue, < 0 otherwise
 */
s32 DmaMgr_AudioDmaHandler(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction) {
    s32 ret = osEPiStartDma(pihandle, mb, direction);

    B_800406B0_jp += mb->size;
    B_800406B4_jp += mb->size;

    return ret;
}

DmaEntry* DmaMgr_FindDmaEntry(RomOffset vrom) {
    DmaEntry* entry;

    for (entry = dma_rom_ad; entry->vromEnd != 0; entry++) {
        if ((vrom >= entry->vromStart) && (vrom < entry->vromEnd)) {
            return entry;
        }
    }
    return NULL;
}

RomOffset DmaMgr_TranslateVromToRom(RomOffset vrom) {
    DmaEntry* entry = DmaMgr_FindDmaEntry(vrom);

    if (entry != NULL) {
        if (entry->romEnd == 0) {
            return (entry->romStart + vrom) - entry->vromStart;
        }

        if (vrom == entry->vromStart) {
            return entry->romStart;
        }

        return -1;
    }

    return -1;
}

s32 DmaMgr_FindDmaIndex(RomOffset vrom) {
    DmaEntry* entry = DmaMgr_FindDmaEntry(vrom);

    if (entry != NULL) {
        return entry - dma_rom_ad;
    }
    return -1;
}

const char* func_80026814_jp(UNUSED s32 arg0) {
    return "??";
}

void DmaMgr_ProcessRequest(DmaRequest* req) {
    RomOffset vrom = req->vrom;
    void* vram = req->vram;
    size_t size = req->size;
    RomOffset romStart;
    size_t romSize;
    DmaEntry* entry;
    s32 index = DmaMgr_FindDmaIndex(vrom);

    if ((index >= 0) && (index < sNumDmaEntries)) {
        entry = &dma_rom_ad[index];

        if (entry->romEnd == 0) {
            // romEnd of 0 indicates that the file is uncompressed. Files that are stored uncompressed can have only
            // part of their content loaded into RAM, so DMA only the requested region.

            if (entry->vromEnd < (vrom + size)) {
                // Error, vrom + size ends up in a different file than it started in

                // "DMA transfers cannot cross segment boundaries"
                DmaMgr_Error(req, "", "Segment Alignment Error",
                             "セグメント境界をまたがってＤＭＡ転送することはできません");
            }
            DmaMgr_DmaRomToRam((entry->romStart + vrom) - entry->vromStart, vram, size);
        } else {
            // File is compressed. Files that are stored compressed must be loaded into RAM all at once.

            romSize = entry->romEnd - entry->romStart;
            romStart = entry->romStart;
            if (vrom != entry->vromStart) {
                // "DMA transfer cannot be performed from the middle of a compressed segment"
                DmaMgr_Error(req, "", "Can't Transfer Segment",
                             "圧縮されたセグメントの途中からはＤＭＡ転送することはできません");
            }

            if (size != (entry->vromEnd - entry->vromStart)) {
                // Error, only part of the file was requested

                // "It is not possible to DMA only part of a compressed segment"
                DmaMgr_Error(req, "", "Can't Transfer Segment",
                             "圧縮されたセグメントの一部だけをＤＭＡ転送することはできません");
            }

            // Reduce the thread priority and decompress the file, the decompression routine handles the DMA in chunks.
            // Restores the thread priority when done.
            osSetThreadPri(NULL, M_PRIORITY_DMAMGR_LOW);
            Yaz0_Decompress(romStart, vram, romSize);
            osSetThreadPri(NULL, M_PRIORITY_DMAMGR);
        }
    } else {
        // "Corresponding data does not exist"
        DmaMgr_Error(req, NULL, "DATA DON'T EXIST", "該当するデータが存在しません");
    }
}

void DmaMgr_ThreadEntry(UNUSED void* arg) {
    OSMesg msg;
    DmaRequest* req;

    while (true) {
        // Wait for DMA Requests to arrive from other threads
        osRecvMesg(&sDmaMgrMsgQueue, &msg, OS_MESG_BLOCK);

        if (msg == NULL) {
            break;
        }
        req = msg;

        // Process the DMA request
        DmaMgr_ProcessRequest(req);

        // Notify the sender that the request has been processed
        if (req->mq != NULL) {
            osSendMesg(req->mq, req->msg, OS_MESG_NOBLOCK);
        }
    }
}

/**
 * Submits a DMA request to the DMA manager. For internal use only.
 *
 * @param req DMA request, filled out internally.
 * @param vram Location in DRAM for data to be written.
 * @param vrom Virtual ROM location for data to be read.
 * @param size Transfer size.
 * @param mq Message queue to notify with `msg` once the transfer is complete.
 * @param msg Message to send to `mq` once the transfer is complete.
 */
s32 DmaMgr_SendRequest(DmaRequest* req, void* vram, RomOffset vrom, size_t size, UNUSED s32 arg4, OSMesgQueue* mq,
                       OSMesg arg6) {
    if (ResetStatus >= 2) {
        return -2;
    }

    req->vrom = vrom;
    req->vram = vram;
    req->size = size;
    req->unk_14 = 0;
    req->mq = mq;
    req->msg = arg6;

    if ((vram == NULL) || (osMemSize < (OS_K0_TO_PHYSICAL(vram) + size)) || (vrom % 2 != 0) || (vrom > 0x04000000) ||
        (size == 0) || (size % 2 != 0)) {
        DmaMgr_Error(req, NULL, "ILLIGAL DMA-FUNCTION CALL", "パラメータ異常です");
    }

    osSendMesg(&sDmaMgrMsgQueue, req, OS_MESG_BLOCK);
    return 0;
}

/**
 * Submit a synchronous DMA request. This will block the current thread until the requested transfer is complete. Data
 * is immediately available as soon as this function returns.
 *
 * @param vram Location in RAM for data to be written.
 * @param vrom Virtual ROM location for data to be read.
 * @param size Transfer size.
 */
s32 DmaMgr_RequestSync(void* vram, RomOffset vrom, size_t size) {
    DmaRequest req;
    OSMesgQueue mq;
    OSMesg msg[1];
    s32 ret;

    osCreateMesgQueue(&mq, msg, ARRAY_COUNT(msg));
    ret = DmaMgr_SendRequest(&req, vram, vrom, size, 0, &mq, NULL);
    if (ret == -1) {
        return ret;
    }

    osRecvMesg(&mq, NULL, OS_MESG_BLOCK);

    return 0;
}

/**
 * Synchronous DMA Request that calculates the size of the segment automatically.
 *
 * @see DmaMgr_RequestSync
 */
s32 DmaMgr_RequestSyncNoSize(void* vram, RomOffset vrom) {
    DmaEntry* entry = DmaMgr_FindDmaEntry(vrom);

    return DmaMgr_RequestSync(vram, vrom, entry->vromEnd - entry->vromStart);
}

/**
 * Returns the uncompressed size for a given segment.
 */
size_t DmaMgr_GetSegmentSize(RomOffset vrom) {
    DmaEntry* entry = DmaMgr_FindDmaEntry(vrom);

    return entry->vromEnd - entry->vromStart;
}

/**
 * Returns the ovl reloc vrom start for a given segment.
 */
RomOffset DmaMgr_GetOvlStart(RomOffset vrom) {
    DmaEntry* entry = DmaMgr_FindDmaEntry(vrom);

    return entry[1].vromStart;
}

/**
 * Searches for the rom offsets of the ovl reloc segment for a given segment.
 *
 * The values will be stored in the pointers passed as parameters. If no segment matches the given vrom then the
 * parameters will be left untouched.
 *
 * @param vromStart The vrom start of the segment.
 * @param[out] vromEnd The vrom end for the given segment.
 * @param[out] ovlStart The vrom start for the ovl reloc segment.
 * @param[out] ovlEnd The vrom end for the ovl reloc segment.
 * @return s32 0 if the given segment is found, -1 otherwise.
 */
s32 DmaMgr_GetOvlOffsets(RomOffset vromStart, RomOffset* vromEnd, RomOffset* ovlStart, RomOffset* ovlEnd) {
    DmaEntry* entry = DmaMgr_FindDmaEntry(vromStart);

    if (entry != NULL) {
        *vromEnd = entry[0].vromEnd;
        *ovlStart = entry[1].vromStart;
        *ovlEnd = entry[1].vromEnd;
        return 0;
    }
    return -1;
}

void DmaMgr_Init(void) {
    // DMA the dma data table to RAM
    DmaMgr_DmaRomToRam(SEGMENT_ROM_START(dmadata), SEGMENT_VRAM_START(dmadata), SEGMENT_ROM_SIZE(dmadata));

    {
        DmaEntry* entry = dma_rom_ad;
        s32 count = 0;

        for (; entry->vromEnd != 0; entry++) {
            count++;
        }

        sNumDmaEntries = count;
    }

    osCreateMesgQueue(&sDmaMgrMsgQueue, dmaEntryMsgBufs, ARRAY_COUNT(dmaEntryMsgBufs));
    StackCheck_Init(&sDmaMgrStackInfo, sDmaMgrStack, STACK_TOP(sDmaMgrStack), 0, 0x100, "dmamgr");
    osCreateThread(&sDmaMgrThread, M_THREAD_ID_DMAMGR, DmaMgr_ThreadEntry, NULL, STACK_TOP(sDmaMgrStack),
                   M_PRIORITY_DMAMGR);
    osStartThread(&sDmaMgrThread);
}

void DmaMgr_Stop(void) {
    osSendMesg(&sDmaMgrMsgQueue, NULL, OS_MESG_BLOCK);
}

/**
 * Submit an asynchronous DMA request. Unlike other DMA requests, this will not block the current thread. Data arrival
 * is not immediate however, ensure that the request has completed by awaiting a message sent to `mq` when the DMA
 * operation has completed.
 *
 * @param req DMA request structure, filled out internally.
 * @param vram Location in DRAM for data to be written.
 * @param vrom Virtual ROM location for data to be read.
 * @param size Transfer size.
 * @param mq Message queue to notify with `msg` once the transfer is complete.
 * @param msg Message to send to `queue` once the transfer is complete.
 * @param file Debug filename of caller.
 * @param line Debug line number of caller.
 * @return 0
 */
void DmaMgr_RequestAsync(DmaRequest* req, void* vram, RomOffset vrom, size_t size, s32 arg4, OSMesgQueue* mq,
                         OSMesg msg, const char* filename, s32 line) {
    req->filename = filename;
    req->line = line;
    DmaMgr_SendRequest(req, vram, vrom, size, arg4, mq, msg);
}

/**
 * Synchronous DMA Request with source file and line info for debugging.
 *
 * @see DmaMgr_RequestSync
 */
s32 DmaMgr_RequestSyncDebug(void* vram, RomOffset vrom, size_t size, const char* filename, s32 line) {
    DmaRequest req;
    s32 ret;
    OSMesgQueue mq;
    OSMesg msg[1];
    UNUSED s32 pad;

    req.filename = filename;
    req.line = line;

    osCreateMesgQueue(&mq, msg, ARRAY_COUNT(msg));

    ret = DmaMgr_SendRequest(&req, vram, vrom, size, 0, &mq, NULL);
    if (ret == -1) {
        return ret;
    }

    osRecvMesg(&mq, NULL, OS_MESG_BLOCK);
    return 0;
}
