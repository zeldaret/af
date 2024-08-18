# Contributing

Thank you for your interest in the Animal Forest decompilation. This is a brief overview on how to contribute to the project.

## Useful Links

- [Working With Splat](docs/working_with_splat.md)
- [Extracting Assets](docs/asset_extraction.md)
- [MM decomp tutorial](https://github.com/zeldaret/mm/blob/master/docs/tutorial/contents.md) Detailed tutorial for learning in general how decomp works and how to decompile a small, simple file. Note that mm doesn't use splat, so some information doesn't apply.
- [Introduction to OOT decomp](https://github.com/zeldaret/oot/blob/master/docs/tutorial/contents.md) - Covers slightly different topics.

Most discussions happen in the `#af-decomp` channel on our [Discord Server](https://discord.zelda.deco.mp/) where you are welcome to ask if you need help getting started.

## Tips for Successful Pull Requests

- Don't bundle together multiple files worth of decompiled code into a single PR. Large PRs require a lot of effort to review, and make things difficult for everyone.
- You don't necessarily have to decompile a whole file, you can just decompile a couple of functions in a single PR if that suits your workflow better.
- Review the [Style Guide](docs/STYLE.md) and see if there's anything you can preemptively fix before code reviews.
- After a PR is opened always merge main instead of rebasing. Rebasing changes how commits are shown in PRs, making changes difficult to follow.

## Making a Pull Request

You should work on a branch on your fork separate from your copy of `main`. You can create branches from `upstream/main` so you don't have to sync your `main` branch every time.

If you haven't done so already, add the main repo as `upstream`

```bash
git remote add upstream https://github.com/zeldaret/af.git
```

Then create new branches with this:

```bash
git fetch upstream && git checkout -b new-branch-name upstream/main
```

We squash commits when merging, so your commit history does not have to be completely spotless.

### NON_EQUIVALENT

If you are working on a function but can't figure out how to tackle certain parts, or you're sure that it's not equivalent, you can wrap it in NON_EQUIVALENT.

Please make a best-effort attempt on any function you put in a PR, though. Half-finished functions aren't necessarily much use to the next decomper.

```c
// can't figure out the MULT_HI() stuff
#ifdef NON_EQUIVALENT
void func(void) {
    // ...
}
#else
#pragma GLOBAL_ASM("file/func.s")
#endif
```

### NON_MATCHING

If you are unable to 100% match a function but can verify it is equivalent in behavior, you can wrap the C code in NON_MATCHING.

 ```c
// s3/s4 swap
#ifdef NON_MATCHING
void func(void) {
    // ...
}
#else
#pragma GLOBAL_ASM("file/func.s")
#endif
```

### Format

Run the formatting script:

```bash
python3 ./tools/format.py
```

### Merge main

To make sure the PR builds correctly with the current main, you need to merge `upstream/main` before you make the PR. The simplest way to do this is to use "Sync Fork" on your branch on the GitHub website. Then sync the remote branch with your local branch using `git fetch && git pull`. This tends to break things, and requires some modifications to get your branch to correctly compile again.

If the Sync Fork method doesn't work because there are merge conflicts, you can use `git fetch upstream && git merge upstream/main` instead. Manually resolve the conflicts with your text editor, make sure it builds, and then commit the changes.

## Checklist

More detailed information can be found in the [Style Guide](docs/STYLE.md).

- [ ] Jenkins build is successful.
  - [ ] `make` builds a matching ROM.
  - [ ] `format.py` was run.
  - [ ] Any new compiler warnings that were added are required for matching. 
- [ ] Files with `NON_MATCHING` functions have equivalent behavior.
- [ ] Overlays should have macros to define access to parameters if the parameter uses bitwise access. The params should have an enum when it makes sense.
- [ ] Comments and variables have correct spelling.
- [ ] Function prototypes are in the appropriate header files. Prototypes for functions that aren't meant to be called outside of the file can be omitted.
- [ ] The following should be declared in an Actor header file. There should be nothing else in the Actor header file.
  - [ ] Main Actor struct
  - [ ] Types used in the actor struct. Specific example would be actionFunc typedefs.
  - [ ] Param field macros and/or enums.
  - [ ] For any other additional `enum`/`struct`/`define`/`function`/`global`, there needs to be evidence it is needed in another file.
  - [ ] Function prototypes.
- [ ] New variables and functions should follow standard naming conventions.
  - [ ] Constants are converted to whichever looks best in context: hexadecimal, decimal, or float
    - [ ] Rotation angles should always be in hexadecimal
    - [ ] Color values should always be in decimal.
  - [ ] Structs, unions, enums, and typedefs are `TitleCase` (`DmRavine`)
  - [ ] Variable names are `camelCase` (`actionFunc`)
    - [ ] Global variables start with `g` (`gSaveContext`)
    - [ ] Static global variables start with `s` (`sSphereInit`)
  - [ ] Macros and enum constants are `SCREAMING_SNAKE_CASE` (`DM_RAVINE_STATE_ACTIVE`)
  - [ ] Trailing commas in array and struct definitions chosen to make it look best
  
## Submitting the Pull Request

Push commits to your fork of the repository on GitHub, and then open a pull request. Name the PR something sensible, like

- `EnRecepgirl OK and documented` (if all the functions match and your documentation is fairly complete)
- `EnRecepgirl OK` (if all the functions match)
- `EnRecepgirl (n nonmatching)` (if you couldn't get one or more functions to match, but to the best of your knowledge they are equivalent code)
- `EnRecepgirl (n nonequivalent)` (if you couldn't get one or more functions to match, and do not believe the code in them has the same effect)

and so on, although these four tend to cover most cases. Feel free to add a comment describing anything interesting you had to do or issues in non-matchings.

Please also update the status of the file on the [spreadsheet](https://docs.google.com/spreadsheets/d/1IkamT3ZFhgtZAaS5HS47b2_PcLlYmEFWk2oUPDhYfI8/).
