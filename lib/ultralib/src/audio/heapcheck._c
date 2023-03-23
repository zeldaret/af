/*====================================================================
 * heapcheck.c
 *
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

#include "synthInternals.h"
#include <libaudio.h>
#include <os_internal.h>
#include <ultraerror.h>

#ifdef AUD_PROFILE
#include <os.h>
extern u32 cnt_index, heap_num, heap_cnt, heap_max, heap_min, lastCnt[];
#endif

s32 alHeapCheck(ALHeap *hp)
{
    s32         rv = 0;
    HeapInfo    *hi;
    HeapInfo    *last = 0;
    u8          *ptr;
    
#ifdef AUD_PROFILE
    lastCnt[++cnt_index] = osGetCount();
#endif
    
#ifdef _DEBUG    
    for (ptr = hp->base; ptr < hp->cur; ptr += hi->size){

        hi = (HeapInfo *)ptr;

        if ( hi->magic != AL_HEAP_MAGIC) {
            if (last) {
                __osError(ERR_ALHEAPCORRUPT, 0);
            } else {
                __osError(ERR_ALHEAPFIRSTBLOCK, 0);
            }
            
            rv = 1;
#ifdef AUD_PROFILE
    PROFILE_AUD(heap_num, heap_cnt, heap_max, heap_min);
#endif
            return rv;
        }

        last = hi;

    }
#endif
#ifdef AUD_PROFILE
    PROFILE_AUD(heap_num, heap_cnt, heap_max, heap_min);
#endif
    return rv;
}


