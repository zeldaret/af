#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023 ZeldaRET
# SPDX-License-Identifier: MIT

from pathlib import Path
import rabbitizer

profiles_txt = Path("tools/profiles.txt")

n64Profiles = dict()
with profiles_txt.open() as f:
    filepath = Path()
    profileName = ""
    currentProfile = []
    for line in f:
        line = line.strip()
        if "dlabel" in line:
            profileName = line.split("dlabel ")[1]
            sPath = Path(line.split(".data.s:")[0])
            filepath = "src" / Path(*sPath.parts[3:])
        elif line == "--":
            assert profileName != ""
            assert len(currentProfile) == 9, profileName
            n64Profiles[profileName] = (filepath, currentProfile)
            currentProfile = []
            profileName = ""
        else:
            entry = line.split(".word ")[1].strip()
            currentProfile.append(entry)

def funcToDecl(func):
    if func == "NULL" or func == "none_proc1":
        return ""
    return f"void {func}(Actor* thisx, Game_Play* game_play);\n"

def funcToProf(func):
    if func == "none_proc1":
        return f"(ActorFunc){func}"
    return func

ActorIdEnum = [
            "ACTOR_PLAYER",
           "ACTOR_BG_ITEM",
           "ACTOR_SAMPLE",
           "ACTOR_FIELDM_DRAW",
           "ACTOR_FIELD_DRAW",
           "ACTOR_AIRPLANE",
           "ACTOR_ROOM_SUNSHINE",
           "ACTOR_LAMP_LIGHT",
           "ACTOR_EV_ANGLER",
           "ACTOR_BALL",
           "ACTOR_HANIWA",
           "ACTOR_MY_ROOM",
           "ACTOR_MBG",
           "ACTOR_T_TAMA",
           "ACTOR_BOX_MANAGER",
           "ACTOR_BOX_MOVE",
           "ACTOR_BOX_TRICK_01",
           "ACTOR_ARRANGE_ROOM",
           "ACTOR_ARRANGE_FURNITURE",
           "ACTOR_TRAIN_DOOR",
           "ACTOR_T_KEITAI",
           "ACTOR_HALLOWEEN_NPC",
           "ACTOR_EV_PUMPKIN",
           "ACTOR_RIDE_OFF_DEMO",
           "ACTOR_NPC_MAMEDANUKI",
           "ACTOR_HANABI_NPC0",
           "ACTOR_HANABI_NPC1",
           "ACTOR_SNOWMAN",
           "ACTOR_NPC_POST_GIRL",
           "ACTOR_NPC_ENGINEER",
           "ACTOR_NPC_MAJIN3",
           "ACTORNPC_SLEEP_OBABA",
           "ACTOR_NPC",
           "ACTOR_EFFECT_CONTROL",
           "ACTOR_NPC2",
           "ACTOR_KAMAKURA_NPC0",
           "ACTOR_NPC_POST_MAN",
           "ACTOR_SHOP_DESIGN",
           "ACTOR_QUEST_MANAGER",
           "ACTOR_MAIL_BOX",
           "ACTOR_HOUSE",
           "ACTOR_SHOP_LEVEL",
           "ACTOR_SHOP",
           "ACTOR_MY_HOUSE",
           "ACTOR_EV_ARTIST",
           "ACTOR_EV_BROKER",
           "ACTOR_EV_DESIGNER",
           "ACTOR_T_UMBRELLA",
           "ACTOR_NPC_SHOP_MASTER",
           "ACTOR_BIRTH_CONTROL",
           "ACTOR_SHOP_MANEKIN",
           "ACTOR_SHOP_INDOOR",
           "ACTOR_EVENT_MANAGER",
           "ACTOR_SHOP_GOODS",
           "ACTOR_BR_SHOP",
           "ACTOR_WEATHER",
           "ACTOR_POST_OFFICE",
           "ACTOR_NPC_GUIDE",
           "ACTOR_NPC_GUIDE2",
           "ACTOR_INSECT",
           "ACTOR_STATION",
           "ACTOR_EV_CARPET_PEDDLER",
           "ACTOR_EV_KABU_PEDDLER",
           "ACTOR_RESERVE",
           "ACTOR_HAND_OVER_ITEM",
           "ACTOR_NPC_CONV_MASTER",
           "ACTOR_NPC_SUPER_MASTER",
           "ACTOR_NPC_DEPART_MASTER",
           "ACTOR_TOOLS",
           "ACTOR_STRUCTURE",
           "ACTOR_EV_GYPSY",
           "ACTOR_NPC_POLICE",
           "ACTOR_TRAIN0",
           "ACTOR_TRAIN1",
           "ACTOR_NPC_STATION_MASTER",
           "ACTOR_EV_SANTA",
           "ACTOR_NPC_POLICE2",
           "ACTOR_POLICE_BOX",
           "ACTOR_BG_POLICE_ITEM",
           "ACTOR_BG_CHERRY_ITEM",
           "ACTOR_BG_WINTER_ITEM",
           "ACTOR_BG_XMAS_ITEM",
           "ACTOR_BG_POST_ITEM",
           "ACTOR_FALL_S",
           "ACTOR_FALL_SESW",
           "ACTOR_EV_BROKER2",
           "ACTOR_BROKER_DESIGN",
           "ACTOR_T_UTIWA",
           "ACTOR_PSNOWMAN",
           "ACTOR_MY_INDOOR",
           "ACTOR_NPC_RCN_GUIDE",
           "ACTOR_INTRO_DEMO",
           "ACTOR_SHRINE",
           "ACTOR_BUGGY",
           "ACTOR_T_HANABI",
           "ACTOR_CONVENI",
           "ACTOR_SUPER",
           "ACTOR_DEPART",
           "ACTOR_HANAMI_NPC0",
           "ACTOR_S_CAR",
           "ACTOR_HANAMI_NPC1",
           "ACTOR_NPC_P_SEL",
           "ACTOR_NPC_P_SEL2",
           "ACTOR_NPC_RCN_GUIDE2",
           "ACTOR_TRAIN_WINDOW",
           "ACTOR_NPC_MAJIN4",
           "ACTOR_KAMAKURA",
           "ACTOR_GYOEI",
           "ACTOR_NPC_MAJIN",
           "ACTOR_T_NPC_SAO",
           "ACTOR_UNSET_110",
           "ACTOR_UKI",
           "ACTOR_NPC_MAJIN2",
           "ACTOR_NORMAL_NPC",
           "ACTOR_SET_MANAGER",
           "ACTOR_SET_NPC_MANAGER",
           "ACTOR_NPC_SHOP_MASTERSP",
           "ACTOR_ROOM_SUNSHINE_POSTHOUSE",
           "ACTOR_ROOM_SUNSHINE_POLICE",
           "ACTOR_EFFECTBG",
           "ACTOR_EV_CHERRY_MANAGER",
           "ACTOR_EV_YOMISE",
           "ACTOR_TOKYOSO_NPC0",
           "ACTOR_TOKYOSO_NPC1",
           "ACTOR_GOZA",
           "ACTOR_RADIO",
           "ACTOR_YATAI",
           "ACTOR_TOKYOSO_CONTROL",
           "ACTOR_SHOP_UMBRELLA",
           "ACTOR_GTO_RELEASE",
           "ACTOR_TUKIMI",
           "ACTOR_KAMAKURA_INDOOR",
           "ACTOR_EV_MIKO",
           "ACTOR_GYO_KAGE",
           "ACTOR_MIKUJI",
           "ACTOR_HOUSE_GOKI",
           "ACTOR_T_CRACKER",
           "ACTOR_UNSET_137",
           "ACTOR_T_PISTOL",
           "ACTOR_T_FLAG",
           "ACTOR_T_TUMBLER",
           "ACTOR_TUKIMI_NPC0",
           "ACTOR_TUKIMI_NPC1",
           "ACTOR_UNSET_143",
           "ACTOR_COUNTDOWN_NPC0",
           "ACTOR_COUNTDOWN_NPC1",
           "ACTOR_TURI_NPC0",
           "ACTOR_TAISOU_NPC0",
           "ACTOR_COUNT",
           "ACTOR_GARAGARA",
           "ACTOR_TAMAIRE_NPC0",
           "ACTOR_TAMAIRE_NPC1",
           "ACTOR_HATUMODE_NPC0",
           "ACTOR_NPC_TOTAKEKE",
           "ACTOR_COUNT02",
           "ACTOR_HATUMODE_CONTROL",
           "ACTOR_TAMA",
           "ACTOR_KAGO",
           "ACTOR_TURI",
           "ACTOR_HOUSE_CLOCK",
           "ACTOR_TUNAHIKI",
           "ACTOR_TUNAHIKI_NPC0",
           "ACTOR_TUNAHIKI_NPC1",
           "ACTOR_KOINOBORI",
           "ACTOR_BEE",
           "ACTOR_NAMEPLATE",
           "ACTOR_DUMP",
           "ACTOR_ROPE",
           "ACTOR_EV_DOZAEMON",
           "ACTOR_WINDMILL",
           "ACTOR_LOTUS",
           "ACTOR_ANIMAL_LOGO",
           "ACTOR_MIKANBOX",
           "ACTOR_DOUZOU",
           "ACTOR_NPC_RTC",
           "ACTOR_TOUDAI",
           "ACTOR_NPC_RESTART",
           "ACTOR_NPC_MAJIN5",
           "ACTOR_FUUSEN",
           "ACTOR_EV_DOKUTU",
           "ACTOR_DUMMY",
           "ACTOR_UNSET_181",
           "ACTOR_UNSET_182",
           "ACTOR_UNSET_183",
           "ACTOR_UNSET_184",
           "ACTOR_UNSET_185",
           "ACTOR_UNSET_186",
           "ACTOR_UNSET_187",
           "ACTOR_UNSET_188",
           "ACTOR_UNSET_189",
           "ACTOR_UNSET_190",
           "ACTOR_UNSET_191",
           "ACTOR_UNSET_192",
           "ACTOR_UNSET_193",
           "ACTOR_UNSET_194",
           "ACTOR_UNSET_195",
           "ACTOR_UNSET_196",
           "ACTOR_UNSET_197",
           "ACTOR_UNSET_198",
           "ACTOR_UNSET_199",
           "ACTOR_UNSET_200",
]

ObjectEnum = [
            "OBJECT_UNSET_0",
            "OBJECT_UNSET_1",
            "OBJECT_UNSET_2",
            "GAMEPLAY_KEEP",
            "OBJECT_4",
            "OBJECT_5",
            "OBJECT_6",
            "OBJECT_7",
            "OBJECT_8",
            "OBJECT_9",
            "OBJECT_UNSET_10",
            "OBJECT_11",
            "OBJECT_12",
            "OBJECT_13",
            "OBJECT_14",
            "OBJECT_15",
            "OBJECT_16",
            "OBJECT_17",
            "OBJECT_18",
            "OBJECT_19",
            "OBJECT_20",
            "OBJECT_21",
            "OBJECT_22",
            "OBJECT_23",
            "OBJECT_24",
            "OBJECT_25",
            "OBJECT_26",
            "OBJECT_27",
            "OBJECT_28",
            "OBJECT_29",
            "OBJECT_30",
            "OBJECT_31",
            "OBJECT_32",
            "OBJECT_33",
            "OBJECT_34",
            "OBJECT_35",
            "OBJECT_36",
            "OBJECT_37",
            "OBJECT_38",
            "OBJECT_39",
            "OBJECT_40",
            "OBJECT_41",
            "OBJECT_42",
            "OBJECT_43",
            "OBJECT_44",
            "OBJECT_45",
            "OBJECT_46",
            "OBJECT_47",
            "OBJECT_48",
            "OBJECT_49",
            "OBJECT_50",
            "OBJECT_51",
            "OBJECT_52",
            "OBJECT_53",
            "OBJECT_54",
            "OBJECT_55",
            "OBJECT_56",
            "OBJECT_57",
            "OBJECT_58",
            "OBJECT_59",
            "OBJECT_60",
            "OBJECT_61",
            "OBJECT_62",
            "OBJECT_63",
            "OBJECT_64",
            "OBJECT_65",
            "OBJECT_66",
            "OBJECT_67",
            "OBJECT_68",
            "OBJECT_69",
            "OBJECT_70",
            "OBJECT_71",
            "OBJECT_72",
            "OBJECT_73",
            "OBJECT_74",
            "OBJECT_75",
            "OBJECT_76",
            "OBJECT_77",
            "OBJECT_78",
            "OBJECT_79",
            "OBJECT_80",
            "OBJECT_81",
            "OBJECT_82",
            "OBJECT_83",
            "OBJECT_84",
            "OBJECT_85",
            "OBJECT_86",
            "OBJECT_87",
            "OBJECT_88",
            "OBJECT_89",
            "OBJECT_90",
            "OBJECT_91",
            "OBJECT_92",
            "OBJECT_93",
            "OBJECT_94",
            "OBJECT_95",
            "OBJECT_96",
            "OBJECT_97",
            "OBJECT_98",
            "OBJECT_99",
            "OBJECT_UNSET_100",
            "OBJECT_101",
            "OBJECT_102",
            "OBJECT_103",
            "OBJECT_104",
            "OBJECT_105",
            "OBJECT_106",
            "OBJECT_107",
            "OBJECT_108",
            "OBJECT_109",
            "OBJECT_110",
            "OBJECT_111",
            "OBJECT_112",
            "OBJECT_113",
            "OBJECT_114",
            "OBJECT_115",
            "OBJECT_116",
            "OBJECT_117",
            "OBJECT_118",
            "OBJECT_119",
            "OBJECT_120",
            "OBJECT_121",
            "OBJECT_122",
            "OBJECT_123",
            "OBJECT_124",
            "OBJECT_125",
            "OBJECT_126",
            "OBJECT_127",
            "OBJECT_128",
            "OBJECT_129",
            "OBJECT_130",
            "OBJECT_131",
            "OBJECT_132",
            "OBJECT_133",
            "OBJECT_134",
            "OBJECT_135",
            "OBJECT_136",
            "OBJECT_137",
            "OBJECT_138",
            "OBJECT_139",
            "OBJECT_140",
            "OBJECT_141",
            "OBJECT_142",
            "OBJECT_143",
            "OBJECT_144",
            "OBJECT_145",
            "OBJECT_146",
            "OBJECT_UNSET_147",
            "OBJECT_148",
            "OBJECT_149",
            "OBJECT_150",
            "OBJECT_151",
            "OBJECT_152",
            "OBJECT_153",
            "OBJECT_154",
            "OBJECT_155",
            "OBJECT_156",
            "OBJECT_157",
            "OBJECT_158",
            "OBJECT_159",
            "OBJECT_160",
            "OBJECT_161",
            "OBJECT_162",
            "OBJECT_163",
            "OBJECT_164",
            "OBJECT_165",
            "OBJECT_166",
            "OBJECT_167",
            "OBJECT_168",
            "OBJECT_169",
            "OBJECT_170",
            "OBJECT_171",
            "OBJECT_172",
            "OBJECT_173",
            "OBJECT_174",
            "OBJECT_175",
            "OBJECT_176",
            "OBJECT_177",
            "OBJECT_178",
            "OBJECT_179",
            "OBJECT_180",
            "OBJECT_181",
            "OBJECT_182",
            "OBJECT_183",
            "OBJECT_184",
            "OBJECT_185",
            "OBJECT_186",
            "OBJECT_187",
            "OBJECT_188",
            "OBJECT_189",
            "OBJECT_190",
            "OBJECT_191",
            "OBJECT_192",
            "OBJECT_193",
            "OBJECT_194",
            "OBJECT_195",
            "OBJECT_196",
            "OBJECT_197",
            "OBJECT_198",
            "OBJECT_199",
            "OBJECT_200",
            "OBJECT_201",
            "OBJECT_202",
            "OBJECT_203",
            "OBJECT_204",
            "OBJECT_205",
            "OBJECT_206",
            "OBJECT_207",
            "OBJECT_208",
            "OBJECT_209",
            "OBJECT_210",
            "OBJECT_211",
            "OBJECT_212",
            "OBJECT_213",
            "OBJECT_214",
            "OBJECT_215",
            "OBJECT_216",
            "OBJECT_217",
            "OBJECT_218",
            "OBJECT_219",
            "OBJECT_220",
            "OBJECT_221",
            "OBJECT_222",
            "OBJECT_223",
            "OBJECT_224",
            "OBJECT_225",
            "OBJECT_226",
            "OBJECT_227",
            "OBJECT_228",
            "OBJECT_229",
            "OBJECT_230",
            "OBJECT_231",
            "OBJECT_232",
            "OBJECT_233",
            "OBJECT_234",
            "OBJECT_235",
            "OBJECT_236",
            "OBJECT_237",
            "OBJECT_238",
            "OBJECT_239",
            "OBJECT_240",
            "OBJECT_241",
            "OBJECT_242",
            "OBJECT_243",
            "OBJECT_244",
            "OBJECT_245",
            "OBJECT_246",
            "OBJECT_247",
            "OBJECT_248",
            "OBJECT_249",
            "OBJECT_250",
            "OBJECT_251",
            "OBJECT_252",
            "OBJECT_253",
            "OBJECT_254",
            "OBJECT_255",
            "OBJECT_256",
            "OBJECT_257",
            "OBJECT_258",
            "OBJECT_259",
            "OBJECT_260",
            "OBJECT_261",
            "OBJECT_262",
            "OBJECT_263",
            "OBJECT_264",
            "OBJECT_265",
            "OBJECT_266",
            "OBJECT_267",
            "OBJECT_268",
            "OBJECT_269",
            "OBJECT_270",
            "OBJECT_271",
            "OBJECT_272",
            "OBJECT_273",
            "OBJECT_274",
            "OBJECT_275",
            "OBJECT_276",
            "OBJECT_277",
            "OBJECT_278",
            "OBJECT_279",
            "OBJECT_280",
            "OBJECT_281",
            "OBJECT_282",
            "OBJECT_283",
            "OBJECT_284",
            "OBJECT_285",
            "OBJECT_286",
            "OBJECT_287",
            "OBJECT_288",
            "OBJECT_289",
            "OBJECT_290",
            "OBJECT_291",
            "OBJECT_292",
            "OBJECT_293",
            "OBJECT_294",
            "OBJECT_295",
            "OBJECT_296",
            "OBJECT_297",
            "OBJECT_298",
            "OBJECT_299",
            "OBJECT_300",
            "OBJECT_301",
            "OBJECT_302",
            "OBJECT_303",
            "OBJECT_304",
            "OBJECT_305",
            "OBJECT_306",
            "OBJECT_307",
            "OBJECT_308",
            "OBJECT_309",
            "OBJECT_310",
            "OBJECT_311",
            "OBJECT_312",
            "OBJECT_313",
            "OBJECT_314",
            "OBJECT_315",
            "OBJECT_316",
            "OBJECT_317",
            "OBJECT_318",
            "OBJECT_319",
            "OBJECT_320",
            "OBJECT_321",
            "OBJECT_322",
            "OBJECT_323",
            "OBJECT_324",
            "OBJECT_325",
            "OBJECT_326",
            "OBJECT_327",
            "OBJECT_328",
            "OBJECT_329",
            "OBJECT_330",
            "OBJECT_331",
            "OBJECT_332",
            "OBJECT_333",
            "OBJECT_334",
            "OBJECT_335",
            "OBJECT_336",
            "OBJECT_337",
            "OBJECT_338",
            "OBJECT_339",
            "OBJECT_340",
            "OBJECT_341",
            "OBJECT_342",
            "OBJECT_343",
            "OBJECT_344",
            "OBJECT_345",
            "OBJECT_346",
            "OBJECT_347",
            "OBJECT_348",
            "OBJECT_349",
            "OBJECT_350",
            "OBJECT_351",
            "OBJECT_352",
            "OBJECT_353",
            "OBJECT_354",
            "OBJECT_355",
            "OBJECT_356",
            "OBJECT_357",
            "OBJECT_358",
            "OBJECT_359",
            "OBJECT_360",
            "OBJECT_361",
            "OBJECT_362",
            "OBJECT_363",
            "OBJECT_364",
            "OBJECT_365",
            "OBJECT_366",
            "OBJECT_367",
            "OBJECT_368",
            "OBJECT_369",
            "OBJECT_370",
            "OBJECT_371",
            "OBJECT_372",
            "OBJECT_373",
            "OBJECT_374",
            "OBJECT_375",
            "OBJECT_376",
            "OBJECT_377",
            "OBJECT_378",
            "OBJECT_379",
            "OBJECT_380",
            "OBJECT_381",
            "OBJECT_382",
            "OBJECT_383",
            "OBJECT_384",
            "OBJECT_385",
            "OBJECT_386",
            "OBJECT_387",
            "OBJECT_388",
            "OBJECT_389",
            "OBJECT_390",
            "OBJECT_391",
            "OBJECT_392",
            "OBJECT_UNSET_393",
            "OBJECT_394",
            "OBJECT_395",
            "OBJECT_396",
            "OBJECT_397",
            "OBJECT_398",
            "OBJECT_399",
            "OBJECT_400",
            "OBJECT_UNSET_401",
            "OBJECT_UNSET_402",
            "OBJECT_UNSET_403",
            "OBJECT_UNSET_404",
            "OBJECT_UNSET_405",
            "OBJECT_UNSET_406",
            "OBJECT_UNSET_407",
            "OBJECT_UNSET_408",
            "OBJECT_UNSET_409",
]

ActorPartEnum = [
    "ACTOR_PART_0",
    "ACTOR_PART_1",
    "ACTOR_PART_PLAYER",
    "ACTOR_PART_NPC",
    "ACTOR_PART_4",
    "ACTOR_PART_5",
    "ACTOR_PART_6",
    "ACTOR_PART_7",
]

ActorFlags = {
    (1 << 0): "ACTOR_FLAG_1",
    (1 << 1): "ACTOR_FLAG_2",
    (1 << 2): "ACTOR_FLAG_4",
    (1 << 3): "ACTOR_FLAG_8",
    (1 << 4): "ACTOR_FLAG_10",
    (1 << 5): "ACTOR_FLAG_20",
    (1 << 6): "ACTOR_FLAG_40",
    (1 << 7): "ACTOR_FLAG_80",
    (1 << 8): "ACTOR_FLAG_100",
    (1 << 9): "ACTOR_FLAG_200",
    (1 << 10): "ACTOR_FLAG_400",
    (1 << 11): "ACTOR_FLAG_800",
    (1 << 12): "ACTOR_FLAG_1000",
    (1 << 13): "ACTOR_FLAG_2000",
    (1 << 14): "ACTOR_FLAG_4000",
    (1 << 15): "ACTOR_FLAG_8000",
    (1 << 16): "ACTOR_FLAG_10000",
    (1 << 17): "ACTOR_FLAG_20000",
    (1 << 18): "ACTOR_FLAG_40000",
    (1 << 19): "ACTOR_FLAG_80000",
    (1 << 20): "ACTOR_FLAG_100000",
    (1 << 21): "ACTOR_FLAG_200000",
    (1 << 22): "ACTOR_FLAG_400000",
    (1 << 23): "ACTOR_FLAG_800000",
    (1 << 24): "ACTOR_FLAG_1000000",
    (1 << 25): "ACTOR_FLAG_2000000",
    (1 << 26): "ACTOR_FLAG_4000000",
    (1 << 27): "ACTOR_FLAG_8000000",
    (1 << 28): "ACTOR_FLAG_10000000",
    (1 << 29): "ACTOR_FLAG_20000000",
    (1 << 30): "ACTOR_FLAG_40000000",
    (1 << 31): "ACTOR_FLAG_80000000",
}

def getOredFlags(flags: int):
    if flags == 0:
        return "0"

    flagList = []
    for i in range(32):
        currentFlag = 1 << i
        if flags & currentFlag:
            flagList.append(ActorFlags[currentFlag])
    return " | ".join(flagList)

filepath: Path
for profName, (filepath, prof) in n64Profiles.items():
    actorId = rabbitizer.Utils.from2Complement((int(prof[0], 0) >> 16) & 0xFFFF, 16)
    part = (int(prof[0], 0) >> 8) & 0xFF
    assert (int(prof[0], 0) & 0xFF) == 0
    flags = int(prof[1], 0)
    unk_08 = (int(prof[2], 0) >> 16) & 0xFFFF
    objectId = rabbitizer.Utils.from2Complement(int(prof[2], 0) & 0xFFFF, 16)
    instanceSize = int(prof[3], 0)
    ct = prof[4] if prof[4] != "0x00000000" else "NULL"
    dt = prof[5] if prof[5] != "0x00000000" else "NULL"
    update = prof[6] if prof[6] != "0x00000000" else "NULL"
    draw = prof[7] if prof[7] != "0x00000000" else "NULL"
    save = prof[8] if prof[8] != "0x00000000" else "NULL"

    structName = profName.replace("_Profile", "")

    commentWidth = 3
    if instanceSize >= 0x1000:
        commentWidth = 4
    if instanceSize >= 0x10000:
        commentWidth = 5
    if instanceSize >= 0x100000:
        commentWidth = 6

    filename = filepath.name

    header = filepath.with_suffix(".h")
    with header.open("w") as f:
        f.write(f"#ifndef {filename.upper()}_H\n")
        f.write(f"#define {filename.upper()}_H\n")
        f.write("\n")

        f.write('#include "ultra64.h"\n')
        f.write('#include "m_actor.h"\n')
        f.write('#include "unk.h"\n')
        f.write('\n')

        f.write(f"struct Game_Play;\n")
        f.write(f"struct {structName};\n")
        f.write('\n')

        f.write(f"typedef void (*{structName}ActionFunc)(struct {structName}*, struct Game_Play*);\n")
        f.write("\n")

        f.write(f"typedef struct {structName} {{\n")

        offsetHex = "{0:0{1}X}".format(0, commentWidth)
        f.write(f"    /* 0x{offsetHex} */ Actor actor;\n")
        if instanceSize > 0x174:
            offsetHex = "{0:0{1}X}".format(0x174, commentWidth)
            f.write(f"    /* 0x{offsetHex} */ UNK_TYPE1 unk_{offsetHex}[0x{instanceSize - 0x174:X}];\n")

        f.write(f"}} {structName}; // size = 0x{instanceSize:X}\n")

        f.write("\n")
        f.write("#endif\n")


    cFileLines = []
    cFile = filepath.with_suffix(".c")
    with cFile.open("r") as f:
        for line in f:
            if "#pragma GLOBAL_ASM(" in line:
                cFileLines.append(line)

    extraIncludes = ""
    if "none_proc1" in {ct, dt, update, draw, save}:
        extraIncludes += '#include "m_lib.h"\n'

    with cFile.open("w") as f:
        f.write(f'#include "{header.name}"\n')
        f.write(extraIncludes)
        f.write(f'#include "overlays/gamestates/ovl_play/m_play.h"\n')
        f.write("\n")

        f.write(funcToDecl(ct))
        f.write(funcToDecl(dt))
        f.write(funcToDecl(update))
        f.write(funcToDecl(draw))
        f.write(funcToDecl(save))
        f.write("\n")

        f.write("#if 0\n")
        f.write(f"ActorProfile {profName} = {{\n")
        f.write(f"    /* */ {ActorIdEnum[actorId]},\n")
        f.write(f"    /* */ {ActorPartEnum[part]},\n")
        f.write(f"    /* */ {getOredFlags(flags)},\n")
        f.write(f"    /* */ 0x{unk_08:04X},\n")
        f.write(f"    /* */ {ObjectEnum[objectId]},\n")
        f.write(f"    /* */ sizeof({structName}),\n")
        f.write(f"    /* */ {funcToProf(ct)},\n")
        f.write(f"    /* */ {funcToProf(dt)},\n")
        f.write(f"    /* */ {funcToProf(update)},\n")
        f.write(f"    /* */ {funcToProf(draw)},\n")
        f.write(f"    /* */ {funcToProf(save)},\n")
        f.write("};\n")
        f.write("#endif\n")

        for line in cFileLines:
            f.write(f"\n{line}")
