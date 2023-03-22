SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    header_ROM_START = __romPos;
    header_VRAM = ADDR(.header);
    .header : AT(header_ROM_START) SUBALIGN(16)
    {
        header_DATA_START = .;
        header = .;
        build/asm/jp/header.o(.data);
        header_DATA_END = .;
        header_DATA_SIZE = ABSOLUTE(header_DATA_END - header_DATA_START);
    }
    __romPos += SIZEOF(.header);
    header_ROM_END = __romPos;
    header_VRAM_END = .;

    ipl3_ROM_START = __romPos;
    ipl3_VRAM = ADDR(.ipl3);
    .ipl3 : AT(ipl3_ROM_START) SUBALIGN(16)
    {
        ipl3_DATA_START = .;
        ipl3 = .;
        build/bin/jp/ipl3.o(.data);
        ipl3_DATA_END = .;
        ipl3_DATA_SIZE = ABSOLUTE(ipl3_DATA_END - ipl3_DATA_START);
    }
    __romPos += SIZEOF(.ipl3);
    ipl3_ROM_END = __romPos;
    ipl3_VRAM_END = .;

    entry_ROM_START = __romPos;
    entry_VRAM = ADDR(.entry);
    .entry 0x80025C00 : AT(entry_ROM_START) SUBALIGN(16)
    {
        entry_TEXT_START = .;
        build/asm/jp/1000.o(.text);
        entry_TEXT_END = .;
        entry_TEXT_SIZE = ABSOLUTE(entry_TEXT_END - entry_TEXT_START);
    }
    __romPos += SIZEOF(.entry);
    __romPos = ALIGN(__romPos, 16);
    entry_ROM_END = __romPos;
    entry_VRAM_END = .;

    boot_ROM_START = __romPos;
    boot_VRAM = ADDR(.boot);
    .boot entry_VRAM_END : AT(boot_ROM_START) SUBALIGN(16)
    {
        boot_TEXT_START = .;
        build/asm/jp/boot/001060.o(.text);
        build/asm/jp/libultra/sendmesg.o(.text);
        build/asm/jp/libultra/pfsfreeblocks.o(.text);
        build/asm/jp/libultra/stopthread.o(.text);
        build/asm/jp/libultra/flashreadid.o(.text);
        build/asm/jp/libultra/recvmesg.o(.text);
        build/asm/jp/libultra/setintmask.o(.text);
        build/asm/jp/libultra/getintmask.o(.text);
        build/asm/jp/libultra/scale.o(.text);
        build/asm/jp/libultra/sinf.o(.text);
        build/asm/jp/libultra/sins.o(.text);
        build/asm/jp/libultra/sptask.o(.text);
        build/asm/jp/libultra/destroythread.o(.text);
        build/asm/jp/libultra/ll.o(.text);
        build/asm/jp/libultra/exceptasm.o(.text);
        build/asm/jp/libultra/thread.o(.text);
        build/asm/jp/libultra/bzero.o(.text);
        build/asm/jp/libultra/controller.o(.text);
        build/asm/jp/boot/00AC40.o(.text);
        build/asm/jp/libultra/flashsectorerase.o(.text);
        build/asm/jp/libultra/createthread.o(.text);
        build/asm/jp/libultra/contreaddata.o(.text);
        build/asm/jp/libultra/virtualtophysical.o(.text);
        build/asm/jp/libultra/writebackdcache.o(.text);
        build/asm/jp/libultra/initialize.o(.text);
        build/asm/jp/boot/00B5D0.o(.text);
        build/asm/jp/libultra/setsr.o(.text);
        build/asm/jp/libultra/getsr.o(.text);
        build/asm/jp/boot/00B650.o(.text);
        build/asm/jp/libultra/perspective.o(.text);
        build/asm/jp/libultra/sprawdma.o(.text);
        build/asm/jp/libultra/sirawdma.o(.text);
        build/asm/jp/libultra/epilinkhandle.o(.text);
        build/asm/jp/libultra/viblack.o(.text);
        build/asm/jp/boot/00BB20.o(.text);
        build/asm/jp/libultra/getthreadid.o(.text);
        build/asm/jp/libultra/sptaskyield.o(.text);
        build/asm/jp/libultra/pfsreadwritefile.o(.text);
        build/asm/jp/libultra/pfsgetstatus.o(.text);
        build/asm/jp/boot/00C230.o(.text);
        build/asm/jp/libultra/mtxidentf.o(.text);
        build/asm/jp/libultra/visetmode.o(.text);
        build/asm/jp/libultra/flashinit.o(.text);
        build/asm/jp/libultra/lookat.o(.text);
        build/asm/jp/libultra/motor.o(.text);
        build/asm/jp/libultra/pfsallocatefile.o(.text);
        build/asm/jp/libultra/stoptimer.o(.text);
        build/asm/jp/libultra/probetlb.o(.text);
        build/asm/jp/libultra/pimgr.o(.text);
        build/asm/jp/boot/00D270.o(.text);
        build/asm/jp/libultra/devmgr.o(.text);
        build/asm/jp/libultra/pirawdma.o(.text);
        build/asm/jp/libultra/contpfs.o(.text);
        build/asm/jp/libultra/getcount.o(.text);
        build/asm/jp/boot/00E3B0.o(.text);
        build/asm/jp/libultra/mtxl2f.o(.text);
        build/asm/jp/libultra/flashreadstatus.o(.text);
        build/asm/jp/libultra/getmemsize.o(.text);
        build/asm/jp/libultra/pfssearchfile.o(.text);
        build/asm/jp/libultra/seteventmesg.o(.text);
        build/asm/jp/libultra/sqrtf.o(.text);
        build/asm/jp/libultra/afterprenmi.o(.text);
        build/asm/jp/libultra/contquery.o(.text);
        build/asm/jp/libultra/lookathil.o(.text);
        build/asm/jp/libultra/xprintf.o(.text);
        build/asm/jp/libultra/unmaptlball.o(.text);
        build/asm/jp/libultra/epidma.o(.text);
        build/asm/jp/libultra/string.o(.text);
        build/asm/jp/libultra/invaldcache.o(.text);
        build/asm/jp/libultra/invalicache.o(.text);
        build/asm/jp/libultra/createmesgqueue.o(.text);
        build/asm/jp/libultra/pfsrepairid.o(.text);
        build/asm/jp/libultra/timerintr.o(.text);
        build/asm/jp/libultra/sp.o(.text);
        build/asm/jp/libultra/si.o(.text);
        build/asm/jp/libultra/mtxident.o(.text);
        build/asm/jp/libultra/jammesg.o(.text);
        build/asm/jp/libultra/setthreadpri.o(.text);
        build/asm/jp/libultra/getthreadpri.o(.text);
        build/asm/jp/libultra/epirawread.o(.text);
        build/asm/jp/libultra/viswapbuf.o(.text);
        build/asm/jp/libultra/position.o(.text);
        build/asm/jp/libultra/epirawdma.o(.text);
        build/asm/jp/libultra/sptaskyielded.o(.text);
        build/asm/jp/libultra/bcmp.o(.text);
        build/asm/jp/libultra/gettime.o(.text);
        build/asm/jp/libultra/rotate.o(.text);
        build/asm/jp/libultra/setglobalintmask.o(.text);
        build/asm/jp/libultra/aisetfreq.o(.text);
        build/asm/jp/boot/011440.o(.text);
        build/asm/jp/libultra/normalize.o(.text);
        build/asm/jp/libultra/setcompare.o(.text);
        build/asm/jp/libultra/aigetstat.o(.text);
        build/asm/jp/libultra/bcopy.o(.text);
        build/asm/jp/libultra/resetglobalintmask.o(.text);
        build/asm/jp/libultra/pfsdeletefile.o(.text);
        build/asm/jp/libultra/ortho.o(.text);
        build/asm/jp/libultra/gbpakinit.o(.text);
        build/asm/jp/libultra/vi.o(.text);
        build/asm/jp/libultra/viswapcontext.o(.text);
        build/asm/jp/libultra/interrupt.o(.text);
        build/asm/jp/libultra/pigetcmdq.o(.text);
        build/asm/jp/libultra/cosf.o(.text);
        build/asm/jp/boot/012500.o(.text);
        build/asm/jp/libultra/visetspecial.o(.text);
        build/asm/jp/libultra/coss.o(.text);
        build/asm/jp/libultra/flashwritearray.o(.text);
        build/asm/jp/libultra/flashallerase.o(.text);
        build/asm/jp/libultra/flashclearstatus.o(.text);
        build/asm/jp/libultra/visetevent.o(.text);
        build/asm/jp/libultra/pfsisplug.o(.text);
        build/asm/jp/libultra/flashwritebuffer.o(.text);
        build/asm/jp/libultra/pfsnumfiles.o(.text);
        build/asm/jp/libultra/cartrominit.o(.text);
        build/asm/jp/libultra/us2dex.o(.text);
        build/asm/jp/libultra/pfsselectbank.o(.text);
        build/asm/jp/libultra/contsetch.o(.text);
        build/asm/jp/libultra/setfpccsr.o(.text);
        build/asm/jp/libultra/getfpccsr.o(.text);
        build/asm/jp/libultra/pfsfilestate.o(.text);
        build/asm/jp/libultra/pfsinitpak.o(.text);
        build/asm/jp/libultra/pfschecker.o(.text);
        build/asm/jp/libultra/aigetlen.o(.text);
        build/asm/jp/boot/014170.o(.text);
        build/asm/jp/libultra/maptlbrdb.o(.text);
        build/asm/jp/libultra/yieldthread.o(.text);
        build/asm/jp/boot/014270.o(.text);
        build/asm/jp/libultra/translate.o(.text);
        build/asm/jp/libultra/getcause.o(.text);
        build/asm/jp/libultra/contramwrite.o(.text);
        build/asm/jp/libultra/contramread.o(.text);
        build/asm/jp/libultra/crc.o(.text);
        build/asm/jp/libultra/epirawwrite.o(.text);
        build/asm/jp/libultra/settimer.o(.text);
        build/asm/jp/libultra/xldtob.o(.text);
        build/asm/jp/libultra/ldiv.o(.text);
        build/asm/jp/libultra/xlitob.o(.text);
        build/asm/jp/boot/015B80.o(.text);
        build/asm/jp/libultra/spsetstat.o(.text);
        build/asm/jp/libultra/spgetstat.o(.text);
        build/asm/jp/boot/015BF0.o(.text);
        build/asm/jp/libultra/vimgr.o(.text);
        build/asm/jp/boot/015F10.o(.text);
        build/asm/jp/libultra/writebackdcacheall.o(.text);
        build/asm/jp/boot/015F50.o(.text);
        build/asm/jp/libultra/mtxf2l.o(.text);
        build/asm/jp/libultra/startthread.o(.text);
        build/asm/jp/libultra/llcvt.o(.text);
        build/asm/jp/libultra/visetyscale.o(.text);
        build/asm/jp/libultra/visetxscale.o(.text);
        build/asm/jp/libultra/conteepread.o(.text);
        build/asm/jp/libultra/conteepwrite.o(.text);
        build/asm/jp/boot/016B10.o(.text);
        build/asm/jp/libultra/spsetpc.o(.text);
        build/asm/jp/libultra/flashreadarray.o(.text);
        build/asm/jp/libultra/flashgetaddr.o(.text);
        build/asm/jp/libultra/setwatchlo.o(.text);
        build/asm/jp/boot/016D60.o(.text);
        boot_TEXT_END = .;
        boot_TEXT_SIZE = ABSOLUTE(boot_TEXT_END - boot_TEXT_START);
        boot_DATA_START = .;
        boot_016F40_data = .;
        build/asm/jp/data/boot/016F40.data.o(.data);
        boot_DATA_END = .;
        boot_DATA_SIZE = ABSOLUTE(boot_DATA_END - boot_DATA_START);
    }
    boot_bss_VRAM = ADDR(.boot_bss);
    .boot_bss (NOLOAD) : SUBALIGN(16)
    {
        boot_BSS_START = .;
        build/asm/jp/data/boot/8003E940.bss.o(.bss);
        boot_BSS_END = .;
        boot_BSS_SIZE = ABSOLUTE(boot_BSS_END - boot_BSS_START);
    }
    __romPos += SIZEOF(.boot);
    __romPos = ALIGN(__romPos, 16);
    boot_ROM_END = __romPos;
    boot_VRAM_END = .;

    dmadata_ROM_START = __romPos;
    dmadata_VRAM = ADDR(.dmadata);
    .dmadata boot_VRAM_END : AT(dmadata_ROM_START) SUBALIGN(16)
    {
        dmadata_DATA_START = .;
        dmadata = .;
        build/bin/jp/dmadata.o(.data);
        dmadata_DATA_END = .;
        dmadata_DATA_SIZE = ABSOLUTE(dmadata_DATA_END - dmadata_DATA_START);
    }
    __romPos += SIZEOF(.dmadata);
    dmadata_ROM_END = __romPos;
    dmadata_VRAM_END = .;

    _27130_ROM_START = __romPos;
    _27130_VRAM = ADDR(._27130);
    ._27130 : AT(_27130_ROM_START) SUBALIGN(16)
    {
        _27130_DATA_START = .;
        _27130 = .;
        build/bin/jp/27130.o(.data);
        _27130_DATA_END = .;
        _27130_DATA_SIZE = ABSOLUTE(_27130_DATA_END - _27130_DATA_START);
    }
    __romPos += SIZEOF(._27130);
    _27130_ROM_END = __romPos;
    _27130_VRAM_END = .;

    code_ROM_START = __romPos;
    code_VRAM = ADDR(.code);
    .code 0x80051A80 : AT(code_ROM_START) SUBALIGN(16)
    {
        code_TEXT_START = .;
        build/asm/jp/code/675720.o(.text);
        code_TEXT_END = .;
        code_TEXT_SIZE = ABSOLUTE(code_TEXT_END - code_TEXT_START);
    }
    __romPos += SIZEOF(.code);
    __romPos = ALIGN(__romPos, 16);
    code_ROM_END = __romPos;
    code_VRAM_END = .;

    _73F4D0_ROM_START = __romPos;
    _73F4D0_VRAM = ADDR(._73F4D0);
    ._73F4D0 : AT(_73F4D0_ROM_START) SUBALIGN(16)
    {
        _73F4D0_DATA_START = .;
        _73F4D0 = .;
        build/bin/jp/73F4D0.o(.data);
        _73F4D0_DATA_END = .;
        _73F4D0_DATA_SIZE = ABSOLUTE(_73F4D0_DATA_END - _73F4D0_DATA_START);
    }
    __romPos += SIZEOF(._73F4D0);
    _73F4D0_ROM_END = __romPos;
    _73F4D0_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
