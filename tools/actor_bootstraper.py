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

# print(n64Profiles)

filepath: Path
for name, (filepath, prof) in n64Profiles.items():
    actorId = rabbitizer.Utils.from2Complement((int(prof[0], 0) >> 16) & 0xFFFF, 16)
    part = (int(prof[0], 0) >> 8) & 0xFF
    assert (int(prof[0], 0) & 0xFF) == 0
    flags = int(prof[1], 0)
    unk_08 = rabbitizer.Utils.from2Complement((int(prof[2], 0) >> 16) & 0xFFFF, 16)
    objectId = rabbitizer.Utils.from2Complement(int(prof[2], 0) & 0xFFFF, 16)
    instanceSize = int(prof[3], 0)
    ct = prof[4] if prof[4] != "0x00000000" else "NULL"
    dt = prof[5] if prof[5] != "0x00000000" else "NULL"
    update = prof[6] if prof[6] != "0x00000000" else "NULL"
    draw = prof[7] if prof[7] != "0x00000000" else "NULL"
    save = prof[8] if prof[8] != "0x00000000" else "NULL"

    structName = name.replace("_Profile", "")

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

        f.write(f"struct {structName};\n")
        f.write('\n')

        f.write(f"typedef struct {structName} {{\n")

        offsetHex = "{0:0{1}X}".format(0, commentWidth)
        f.write(f"    /* 0x{offsetHex} */ Actor actor;\n")
        if instanceSize > 0x174:
            offsetHex = "{0:0{1}X}".format(0x174, commentWidth)
            f.write(f"    /* 0x{offsetHex} */ UNK_TYPE1 unk_{offsetHex}[0x{instanceSize - 0x174:X}];\n")

        f.write(f"}} {structName}; // size = 0x{instanceSize:X}\n")

        f.write("\n")
        f.write("#endif\n")

"""
newNamesSet = set()

for name, prof in n64Profiles.items():
    gcnProf = gcnProfiles[name]

    for i in range(4, 9):
        oldName = prof[i]
        newName = gcnProf[i]

        if newName in {"none_proc1"}:
            continue

        if oldName == "0x00000000" and newName == "0x00000000":
            continue

        assert "+" not in oldName, f"{oldName}, {newName}"
        assert newName not in newNamesSet, f"{oldName}, {newName}"
        if newName == "0x00000000":
            if oldName == "func_80A66978_jp":
                continue

        assert oldName != "0x00000000", f"{oldName}, {newName}"
        assert newName != "0x00000000", f"{oldName}, {newName}"
        # if oldName == "0x00000000" or newName == "0x00000000":
        #     print(oldName, newName)


        if oldName != newName:
            print(f'"{oldName}": "{newName}",')
            pass

        newNamesSet.add(newName)
"""
