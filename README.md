# Animal Forest

## Setup

### Linux

#### 1. Install build dependencies

The build process has the following package requirements:

* make
* git
* build-essential
* binutils-mips-linux-gnu
* python3
* pip3

Under Debian / Ubuntu (which we recommend using), you can install them with the following commands:

```bash
sudo apt update
sudo apt install make git build-essential binutils-mips-linux-gnu python3 python3-pip
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
make
```
