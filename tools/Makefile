WARNINGS_CHECK ?= 0

UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	DETECTED_OS  := windows
	PIGMENT64_OS := x86_64-pc-windows-gnu
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS  := linux
	PIGMENT64_OS := x86_64-unknown-linux-musl
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS  := macos
	PIGMENT64_OS := x86_64-apple-darwin
endif


WGET_FLAGS  ?=
ifneq ($(WARNINGS_CHECK), 0)
    WGET_FLAGS += --quiet
endif



IDO_5_3_DIR := ido/$(DETECTED_OS)/5.3
IDO_5_3     := $(IDO_5_3_DIR)/cc

IDO_7_1_DIR := ido/$(DETECTED_OS)/7.1
IDO_7_1     := $(IDO_7_1_DIR)/cc

PIGMENT64_DIR := pigment64
PIGMENT64     := $(PIGMENT64_DIR)/pigment64

all: $(IDO_5_3) $(IDO_7_1) $(PIGMENT64)
	$(MAKE) -C fado
	$(MAKE) -C z64compress

clean:
	$(RM) -rf $(IDO_5_3_DIR) $(IDO_7_1_DIR)

distclean: clean
	$(RM) -rf ido

.PHONY: all clean distclean


$(IDO_5_3): | $(IDO_5_3_DIR)
	wget $(WGET_FLAGS) https://github.com/decompals/ido-static-recomp/releases/latest/download/ido-5.3-recomp-$(DETECTED_OS).tar.gz
	tar xf ido-5.3-recomp-$(DETECTED_OS).tar.gz -C $(IDO_5_3_DIR)
	$(RM) ido-5.3-recomp-$(DETECTED_OS).tar.gz

$(IDO_7_1): | $(IDO_7_1_DIR)
	wget $(WGET_FLAGS) https://github.com/decompals/ido-static-recomp/releases/latest/download/ido-7.1-recomp-$(DETECTED_OS).tar.gz
	tar xf ido-7.1-recomp-$(DETECTED_OS).tar.gz -C $(IDO_7_1_DIR)
	$(RM) ido-7.1-recomp-$(DETECTED_OS).tar.gz

$(PIGMENT64): | $(PIGMENT64_DIR)
	wget $(WGET_FLAGS) https://github.com/decompals/pigment64/releases/download/0.3.0/pigment64_0.3.0_$(PIGMENT64_OS).tar.gz
	tar xf pigment64_0.3.0_$(PIGMENT64_OS).tar.gz -C $(PIGMENT64_DIR)
	$(RM) pigment64_0.3.0_$(PIGMENT64_OS).tar.gz

$(IDO_5_3_DIR):
	mkdir -p $@

$(IDO_7_1_DIR):
	mkdir -p $@

$(PIGMENT64_DIR):
	mkdir -p $@

distclean: clean
