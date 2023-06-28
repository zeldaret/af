#include "PR/os_internal.h"
#include "controller.h"

s32 osPfsFreeBlocks(OSPfs* pfs, s32* bytes_not_used) {
    int j;
    int pages = 0;
    __OSInode inode;
    s32 ret = 0;
    u8 bank;
    int offset;

    PFS_CHECK_STATUS;
    ERRCK(__osCheckId(pfs));
    for (bank = 0; bank < pfs->banks; bank++) {
        ERRCK(__osPfsRWInode(pfs, &inode, OS_READ, bank));
        offset = ((bank > 0) ? 1 : pfs->inode_start_page);

        for (j = offset; j < ARRLEN(inode.inode_page); j++) {
            if (inode.inode_page[j].ipage == PFS_PAGE_NOT_USED) {
                pages++;
            }
        }
    }

    *bytes_not_used = pages * PFS_ONE_PAGE * BLOCKSIZE;
    return 0;
}
