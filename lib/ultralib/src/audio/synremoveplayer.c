/*====================================================================
 * synremoveplayer.c
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
#include <os_internal.h>

void alSynRemovePlayer(ALSynth *drvr, ALPlayer *client)
{
    ALPlayer *thing;
    ALPlayer *prev = 0;

    if (drvr->head != 0)
    {
	OSIntMask mask = osSetIntMask(OS_IM_NONE);

        for (thing = drvr->head; thing != 0; thing = thing->next) {
            if (thing == client) {
		if(prev)
		    prev->next = thing->next;
		else
		    drvr->head = thing->next;

                client->next = 0;
		break;
            }
	    prev = thing;
        }

	osSetIntMask(mask);
    }
}

