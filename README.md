# Animal Forest [![Build Status][jenkins-badge]][jenkins] ![Code jp Progress] [![Discord Channel][discord-badge]][discord]

[jenkins]: https://jenkins.deco.mp/job/AF/job/main
[jenkins-badge]: https://img.shields.io/jenkins/build?jobUrl=https%3A%2F%2Fjenkins.deco.mp%2Fjob%2FAF%2Fjob%2Fmain

[Code jp Progress]: https://img.shields.io/endpoint?label=Code%20jp&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fanimalforest%2Fjp%2Fcode%2F%3Fmode%3Dshield%26measure%3Dall

[discord]: https://discord.zelda64.dev
[discord-badge]: https://img.shields.io/discord/688807550715560050?color=%237289DA&logo=discord&logoColor=%23FFFFFF

This is a work-in-progress decompilation project for the Nintendo 64 game *Animal Forest*, also known as どうぶつの森 (*Doubutsu no Mori*).
There is a decompilation project for the GameCube versions (*Animal Crossing*, etc.) [here](https://github.com/Prakxo/ac-decomp/).

```diff
- WARNING! -

This repository is a work in progress, and while it can be used to make certain changes, it's 
still constantly evolving. If you wish to use it for modding purposes in its current state,
please be aware that the codebase could drastically change at any time. Also note that some
parts of the ROM may not be 'shiftable' yet, so modifying them could currently be difficult.
```

**Note:** this project is *not* a port, to PC or any other platform.
It takes a Nintendo 64 rom, extracts assets from it, and combines them with C code we reverse-engineered from the rom, to produce an identical rom.
It is explicitly a non-goal for this project to be used as basis for a port, or to be used for any commercial purpose.

## Setup

### Linux

#### 1. Install build dependencies

The build process has the following package requirements:

* make
* git
* build-essential
* clang
* binutils-mips-linux-gnu
* python3
* pip3

Under Debian / Ubuntu (which we recommend using), you can install them with the following commands:

```bash
sudo apt update
sudo apt install make git build-essential clang binutils-mips-linux-gnu python3 python3-pip
```

#### 2. Install python dependencies

The build process has a few python packages required that are located in `requirements.txt`.

To install them simply run in a terminal:

```bash
python3 -m pip install -U -r requirements.txt
```

#### 3. Prepare a base ROM

Copy your ROM to inside the root of this new project directory, and rename the file of the baserom to reflect the version of ROM you are using. ex: `baserom.jp.z64`

#### 4. Make and Build the ROM

To start the extraction/build process, run the following command:

```bash
make setup
make extract
make lib
make
```

## Note about licensing

The contents of the `src` and `include` folders are, as far as possible, licensed under CC0.

Other folders and files in the repository are CC0 unless they specify another license.

The licensing of this repository does not cover subrepos, namely:

* `tools/asm-differ`
* `tools/asm-processor`
* `tools/fado`
* `lib/ultralib`
* `tools/z64compress`
