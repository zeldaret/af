# Animal Forest Decompilation Style Guide

In general, documented files are a good place to look to understand this project's style.

## Original Names
A large amount of the original names for functions, data, bss, and objects are present in the linker map files found in Doubutsu no Mori +, Animal Crossing, and Doubutsu no Mori e+. Because of this, this project aims to use the original names if known. These take priority over all code style guidelines.

These .map files can be found pinned in the `#af-decomp` channel in our discord.

Some functions were present in DnM and removed in DnM+. You can choose a name for these, but they should match the same style as the other functions in the file, and be accompanied with a comment  
```c
// Original name unknown.
```

Notably local variables, structs, struct members, enums, and macros are not in the linker map files. Sometimes these can be deduced from function names, debug strings, or Ocarina of Time / Majora's Mask. These original names should be used as well.

If you are simply decompiling a file and are not entirely sure what the function's name should be, or what a struct should be called, It is preferable to leave functions unnamed, or use unk_struct_XXX for structs, unk_XXX for struct members, etc. If something is named incorrectly it can be confusing to correct in the future.

## Types

Use the types from `ultratypes.h`, not the standard C types: i.e. `u8`,`s8`,`s16`,`u16`,`s32`,`u32`,`f32` rather than `char`, `short`, `int`, `float` and their `signed`/`unsigned` varieties.

## Naming

Names are "big-endian": the most significant/largest part of the system goes first, e.g. `DM_RAVINE_STATE_ACTIVE` rather than `DM_RAVINE_ACTIVE_STATE`.

We always write our enums and structs as `typedef`s. (Usually one can't use an enum typedef as a function argument since enum typedefs are implicitly `s32`.)

| Type                 | Style                   | Example                 |
| -------------------- | ----------------------- | ----------------------- |
| Local variables      | camelCase               | `yawToPlayer`           |
| Global variables     | gCamelCase              | `gSaveContext`          |
| Static variables     | sCamelCase              | `sZeroVec`              |
| Struct members       | camelCase               | `actionFunc`            |
| Struct names         | PascalCase              | `EnFirefly`             |
| Enum types           | PascalCase              | `EnFireflyMainType`     |
| Enum values          | SCREAMING_SNAKE_CASE    | `AT_ON`                 |
| Defines/macros       | SCREAMING_SNAKE_CASE    | `SCREEN_WIDTH`,`ABS(x)` |

## Formatting

Before submitting a pull request, your files should be formatted with clang-format. If they aren't, Jenkins will politely remind you by failing the build.

You can run clang-format with this python script:

```bash
python3 ./tools/format.py
```

If you have some arrays or struct definitions in your file, check that they have not been obnoxiously padded out: you can usually get a better format without a final comma for short things.

Some important things that clang-format won't fix:

- Files should use Linux line endings (LF).
- Blank line between declarations and code:

  ```c
  s32 var;
  
  func();
  ```

- Combine declarations and definitions if possible:

  ```c
  s32 var = 0;
  
  func();
  ```

  instead of

  ```c
  s32 var;
  
  var = 0;
  func();
  ```

- Blank lines between switch cases if they're long (use your judgement).

## Numbers

### Decimal

- Timers
- Colors and alpha
- Usually array accesses and sizes

### Hexadecimal

- Angles (for now; the code itself is very inconsistent with round hex, round dec, and degrees)
- Addresses
- Bitmasks (i.e. `& 0x80` etc.)
- Struct offset comments

Numbers below `10`/`0xA` do not need the `0x` if by themselves in code.

### Booleans

If a function returns only `0` or `1`, and is used as a boolean (i.e. in conditionals), replace the returns by `false` and `true`.

### Floats

Floats usually need an `f` on the end to match, or IDO will use doubles. Our floats are always of the form `1.0f`, even when the decimal part is zero.

## Conditionals/Loops

- Spacing out conditional or loop blocks from surrounding code often makes them easier to read.
- Avoid assigning or mutating variables in conditionals if possible (including `++`/`--`), avoid side effects in the loop increment slot (i.e. incrementing/assigning to loop variables is fine, something like `*a = b++` is not).
- We *always* use `{}` on conditional/loop blocks, even if they're one line (clang-tidy will enforce this).
- When conditions are `&&`d or `||`d together, use brackets around each that includes an arithmetic comparison or bitwise operator (i.e. not `!var` or `func()`, but ones with `==` or `&` etc.)
- Flag checks or functions that return booleans do not need the `== 0`/`!= 0`.
  
## Arrays

- It's better to not hardcode array sizes (easier to mod)
- Use `sizeof` or `ARRAY_COUNT`/`ARRAY_COUNTU` where it makes sense, e.g. in loops that are using an array.
- clang-format sometimes does weird things to array formatting. Experiment with and without a comma after the last element and see which looks better.

## game_play2

In some particular instances, IDO requires the function argument `game_play` to be cast to a second variable of the same type to match. In these particular instances, the function argument should be renamed to `game_play2` and than this `game_play2` just assigned to a stack variable called `game_play`. This cast should occur before the actor `THIS` cast is made. For example:

```c
void aTOU_actor_init(Actor* thisx, Game_Play* game_play2) {
    Game_Play* game_play = game_play2;
    Structure* this = THIS;
```

In other places the cast is actually not explicitly needed, but a stack `pad` variable is still needed. For this there should just be a stack variable called `pad` of type `s32` before the actor `THIS` cast. For example:

```c
void aTOU_actor_ct(Actor* thisx, Game_Play* game_play) {
    s32 pad;
    Structure* this = THIS;
    s32 type = (common_data.time.season == WINTER);
```

## Documentation and Comments

Documentation includes:

- Naming functions
- Naming struct variables
- Naming data
- Naming local variables
- Describing the general purpose of the file
- Describing any unusual, interesting or strange features of how the file or parts of its content work
- Labelling and explaining bugs
- Making enums or defines for significant numbers for the file, like actor params values.
- Naming the contents of the asset file(s) the file may use (for an actor, the object(s) it uses)

If you are not sure what something does, it is better to leave it unnamed than name it wrongly. It is fine to make a note of something you are not sure about when PRing, it means the reviewers will pay special attention to it.

We use comments for:

- Top of file: a short description of the system.
- For function descriptions, we use multiline comments,

  ```c
  /**
   * A brief description of what the function does.
   *
   * More details if needed.
   */
  ```

  These are *optional*: if you think the code is clear enough, you do not need to put a comment. You can use Doxygen formatting if you think it adds something, but it is also not required.
- If something in a function is strange, or unintuitive, do leave a comment explaining what's going on. We use `//` for this.
- We also use `//` for temporary comments above a function. Feel free to use `TODO:` in these if appropriate.
- A bug should be commented with an `//! @bug Bug description` above the code that causes the bug.
- For "fake matches", awful code that exists only to make the function's assembly match, mark these with `//! FAKE`

## What goes where

### Functions

All functions should go in the main C file in the same order as the assembly (the latter is required to match anyway). (We may make exceptions for particularly large files with a particular organizational structure, but we ask that you check on Discord first before doing this)

### Prototypes

Actors:
- Only make prototypes that are necessary. Because actors are usually self contained, prototypes should be placed in the main C file, unless they are used by something outside of the file, where they should be placed in the header.

Other files (boot, code, etc):
- Prototypes should be placed in the header. You can omit functions that shouldn't be used outside the file.

### Data

- If in doubt, leave all the data at the top of the file. Reviewers will decide for you.
- Data must go in the same order as in the assembly files, but is only constrained by other data, not functions or rodata.
- Do not use `static` on data outside functions, since `static` data is left out of the mapfile and this makes debugging harder. Only use static when necessary to match.
- *This is even more true of bss, where we have trouble with IDO unpredictably reordering it in certain files.*
- For small arrays or simple data that is used in only one function, we usually inline it, if it fits in the ordering.
- Generally data that is only used by the draw functions is put down near them: this is one of the few consistencies in ordering of actors' functions.

### Enums and defines

- Actors that bitpack params should have macros made for each access or write that is made. An undocumented example from Majora's Mask, `z_en_dg.h`

  ```c
  #define ENDG_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)
  #define ENDG_GET_3E0(thisx) (((thisx)->params & 0x3E0) >> 5)
  ```

  and a documented example from Majora's Mask, `z_en_firefly.h`

  ```c
  #define KEESE_INVISIBLE (1 << 0xF)
  #define KEESE_GET_MAIN_TYPE(thisx) ((thisx)->params & 0x7FFF)
  ```

- In a similar manner, actors that use `home.rot.(x|y|z)` like params should also macros made for accesses and writes. (See, e.g. `z_obj_bean.h` from Majora's Mask.)
- Stuff that only the actor itself will use goes in the C file unless needed in the header.
- Anything actor-specific that might be used by another file goes in the header, in particular params access macros.
- Anything that is expected to have widespread use should go in the appropriate header file. eg z64_math.h, gfx.h, macros.h

### Objects

Use the original names. If the object isn't in the linker map you can match the pattern other objects use:

Vertices
- obj_romtrain_door_v

Display Lists
- obj_romtrain_door_model

Skeletons
- cKF_je_r_obj_romtrain_door_tbl
- cKF_bs_r_obj_romtrain_door

Animations
- cKF_ckcb_r_obj_romtrain_door_tbl
- cKF_kn_obj_romtrain_door_tbl
- cKF_c_obj_romtrain_door_tbl
- cKF_ds_obj_romtrain_door_tbl
- cKF_ba_r_obj_romtrain_door

Textures
- obj_romtrain_door_pal
- obj_romtrain_door_tex_txt

## Above all else

*All of the above is subservient to matching.* Sometimes IDO cares about newlines, for example.

If you are not sure about any of the above, please ask in Discord.
