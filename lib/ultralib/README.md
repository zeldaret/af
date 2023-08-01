# ultralib

Reverse engineering of libultra

## Compatibility

Currently this repo supports building the following versions:

| IDO / GCC  | `libultra.a` / `libgultra.a` | `libultra_d.a` / `libgultra_d.a` | `libultra_rom.a` / `libgultra_rom.a` |
| -          | :-: | :-: | :-: |
| 2.0E       | :x: / N/A | :x: / N/A | :x: / N/A |
| 2.0F       | :x: / N/A | :x: / N/A | :x: / N/A |
| 2.0G       | :x: / N/A | :x: / N/A | :x: / N/A |
| 2.0H       | :x: / :x: | :x: / :x: | :x: / :x: |
| 2.0I       | :x: / :x: | :x: / :x: | :x: / :x: |
| 2.0I_patch | :x: / :x: | :x: / :x: | :x: / :x: |
| 2.0J       | :x: / :x: | :x: / :x: | :x: / :x: |
| 2.0K       | :x: / :x: | :x: / :x: | :x: / :x: |
| 2.0L       | :heavy_check_mark: / :heavy_check_mark: | :x: / :heavy_check_mark: | :heavy_check_mark: / :heavy_check_mark: |
| ique_v1.5  | :x: | :x: | :x: |

## Preparation

After cloning the repo, put a copy of the target archive on the root of this directory.

## Build dependencies

The build process requires the following packages:

- build-essential
- python3
- binutils-mips-linux-gnu (libultra* only)

Under Debian / Ubunutu you can install them with the following commands:

```bash
sudo apt update
sudo apt install build-essential python3
```

If building any libultra you can install binutils-mips-linux-gnu with:

```bash
sudo apt install binutils-mips-linux-gnu
```

## Building

- `make setup`
- `make`
