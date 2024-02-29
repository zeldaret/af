/*====================================================================
 * seqpdelete.c
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
#include <PR/os_version.h>
#include <libaudio.h>
#include <assert.h>
// TODO: this comes from a header
#ident "$Revision: 1.17 $"

void alSeqpDelete(ALSeqPlayer *seqp)
{
    /* sct 1/4/96 - If the sequence player isn't stopped, then you may end
       up with stuck notes.  Application should check state before calling
       this routine to be sure. */
#if BUILD_VERSION < VERSION_J
#line 31
#endif
    assert(seqp->state == AL_STOPPED);


    alSynRemovePlayer(seqp->drvr, &seqp->node);
}

