# Working with Splat

## What is Splat?

The base of this project is the Doubutsu no Mori rom, which is a 25mb chunk of data. We need to split this file into separate files in order to work on them. Because this is copyrighted data it can't be added to the repo, so we need a system where contributors can bring their own rom and extract the files outside of the repo. To accomplish this we use splat. 

Splat only handles file extraction. It generates linker scripts, but it doesn't do any of the building.

## Overview of Configuration Files:

`yamls/jp/header.yaml`

The main configuration file for splat. Most of the time you can ignore this.

`yamls/jp/boot.yaml`  
`yamls/jp/code.yaml`  
`yamls/jp/overlays.yaml`

These yaml files are responsible for defining each file from the rom. Currently we don't have a complete definition of every file, so these files are constantly being updated as we learn more.

`animalforest.jp.yaml`

This is an automatically generated file that combines the other yaml files. you shouldn't edit this file, as changes will just be overwritten when it gets generated again.

`linkerscripts/jp/symbol_addrs_boot.txt`  
`linkerscripts/jp/symbol_addrs_code.txt`  
`linkerscripts/jp/symbol_addrs_overlays.txt`

By default functions will be named function_XXXXXXXX_jp, data will be named D_XXXXXXXX_jp and bss will be named B_XXXXXXXX_jp. These can be renamed by defining them in these files.

## Starting work on a file (boot or code)

Make sure you have the appropriate baserom.z64 setup. see the [readme](../README.md) for more details.

The first step is to have splat extract everything. This is done with `make extract -j`. Because all the file splits haven't been determined yet, it's possible the file you want to work on is not split correctly.

When splat is extracting it will mention possible file splits in the console output. One easy way to check is writing the output to a text file that you can ctrl-f through.

```bash
make extract -j > output.txt
```

Open the appropriate yaml for the file you want to start working on, either `yamls/jp/boot.yaml` or `yamls/jp/code.yaml`.

When code gets compiled, it produces multiple sections of data that gets linked into the rom.

### .text
The mips assembly instructions.  
splat type: `asm`

### .data
Stores variables that have been initialized.  
splat type `data`

### .rodata
"Read Only Data", such as constants, strings, floats, or jump tables.  
splat type `rodata`

### .bss
"Block Starting Symbol", stores variables that have been declared but are uninitialized.  
splat type: `bss`

In these yaml files, entries are organized by their order in the rom file, where all the text sections are grouped, then data, rodata, and finally bss. 

Data is defined by listing the uncompressed rom address, the type of data, and the output file. For example:

```yaml
- [0x675720, asm, code/c_keyframe]
```

The end of the file is defined by the next definition's start address. So if splat told us about a possible file split when we extracted files earlier, you can define this split by making a new definition below your file. Because we don't know what that file is called, you can just set the file name to the rom address of where it starts.

To start working on a file, there are two things you should change. Change the type of the text section of your file from `asm` to `c`. If your file has a rodata section, you want to change the `rodata` type to `.rodata`

This period tells splat that it should not extract that data, only add it to the linker script. The rodata section will be properly generated when we compile our c file, so we don't want to extract it from the rom. 

Note: This is true of the data section and bss section as well, but those can be more troublesome to properly transfer to your c file, so it's easier to transfer at the end when all the functions are matching.

Save the yaml file. Every time you make a change to a yaml file, you need to use `make extract -j` to extract everything again.

When extracting, splat checks if the c file already exists. in our case it doesn't, so splat will generate a new one with each function's assembly included by a #pragma statement. Run `make diff-init -j` to build the rom, and generate the `expected/build` folder. Everything is now set up to start decompiling functions. 

## Importing data and bss

The data section that was extracted from the rom can be found in `<file_name>.data.s`.

To start out with you can copy the hexadecimal numbers into your c file and format the data as an array of s32s. For example:

```c
s32 D_80AAC084_jp[] = {0x01000100, 0x00010100, 0x01000000, 0x01010001, 0x01000100};
```

If you know the proper type for this data, you can define it as that and split the hexadecimal numbers accordingly.

Once you have copied over all the data, edit `boot.yaml` or `code.yaml` depending on your file. you want to change your file's `data` definition to `.data` so splat will no longer extract it. Save the file, and run `make extract -j` and `make -j`. We're checking to see if the rom matches after building. If it doesn't, it's likely that something about the data you imported is incorrect. `python3 tools/first_diff.py` and `vbindiff` can be helpful for diagnosing problems.

Importing bss is similar. Declare the bss variable in your C file, in the yaml change `bss` to `.bss`, and extract and build again to make sure the rom matches. With bss you have to make sure it gets ordered correctly, and unfortunately some files can be uncooperative. Sometimes hacks are required, like using `prevent_bss_reordering.h`.

## Renaming Functions and Symbols.

Open `linkerscripts/jp/symbol_addrs_boot.txt` or `linkerscripts/jp/symbol_addrs_code.txt` depending on your file. Every function and symbol has a definition already, so search for the default func_XXXXXXXX or D_XXXXXXXX, and replace it with your new name.

For data, sometimes it will get extracted incorrectly, splitting up data or adding padding at the end. You should manually remove unnecessary definitions. 

Save the file. Like the yaml files, after editing these you need to run `make extract -j` again. Because your C file already exists, splat will not generate a new one. You will need to manually rename everything in your C and header file.

## Actors and Overlays

Because the n64 has a very small amount of ram, the game's code isn't entirely loaded into memory at once. Instead, certain files get loaded when they're needed, and unloaded when they aren't. These files are called overlays. Every actor is an overlay, but not every overlays is an actor.

Because an overlay doesn't know what arbitrary spot in ram it will be loaded into, there's a system that remaps the virtual ram addresses to physical ram addresses. This is handled by the .reloc section of the file.

Because of virtual ram, `yamls/jp/overlays.yaml` is set up a little bit different from the others. Each file has it's own definition, and the text, data, rodata, and bss are defined as subsegments. This allows for manually specifying the virtual ram address of each file with the `vram` argument.

For the purpose of decompiling overlays, editing the subsegment definitions is the same as code and boot files. You should not have to change the reloc file definitions.

## Extracting Assembly for Matched Functions.
Let's say you want to revisit a function that was already matched. Splat only extracts the asm of functions defined by the #pragma statement in c files, so it won't automatically extract it. However you can pass an argument to splat to tell it to extract every function's asm. This can be done using a makefile variable when you extract.

```bash
make extract -j --FULL_DISASM=1
```