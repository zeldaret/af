/* 0x00 */ DEFINE_GAMESTATE()


/* 0x00 */ DEFINE_GAMESTATE_INTERNAL(Setup, GAMESTATE_SETUP)
/* 0x01 */ DEFINE_GAMESTATE(MapSelect, GAMESTATE_MAP_SELECT, select)
/* 0x02 */ DEFINE_GAMESTATE(ConsoleLogo, GAMESTATE_CONSOLE_LOGO, title)
/* 0x03 */ DEFINE_GAMESTATE_INTERNAL(Play, GAMESTATE_PLAY)
/* 0x04 */ DEFINE_GAMESTATE(TitleSetup, GAMESTATE_TITLE_SETUP, opening)
/* 0x05 */ DEFINE_GAMESTATE(FileSelect, GAMESTATE_FILE_SELECT, file_choose)
/* 0x06 */ DEFINE_GAMESTATE(DayTelop, GAMESTATE_DAYTELOP, daytelop)
