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


IDO_RECOMP_VERSION := v1.2
PIGMENT64_VERSION := 0.6.3

IDO_5_3_DIR := ido/$(DETECTED_OS)/5.3
IDO_5_3     := $(IDO_5_3_DIR)/cc

IDO_7_1_DIR := ido/$(DETECTED_OS)/7.1
IDO_7_1     := $(IDO_7_1_DIR)/cc

PIGMENT64_DIR := pigment64
PIGMENT64     := $(PIGMENT64_DIR)/pigment64

all: $(IDO_5_3) $(IDO_7_1) $(PIGMENT64)
	$(MAKE) -C fado

clean:
	$(RM) -rf $(IDO_5_3_DIR) $(IDO_7_1_DIR)

distclean: clean
	$(RM) -rf ido
	$(RM) -rf tool_archives/archives/ido-5.3-recomp-$(DETECTED_OS).tar.gz
	$(RM) -rf tool_archives/archives/ido-7.1-recomp-$(DETECTED_OS).tar.gz
	$(RM) -rf tool_archives/archives/pigment64-$(PIGMENT64_OS).tar.gz

.PHONY: all clean distclean


tool_archives/archives/ido-5.3-recomp-$(DETECTED_OS).tar.gz:
	mkdir -p $(@D)
	wget $(WGET_FLAGS) https://github.com/decompals/ido-static-recomp/releases/download/$(IDO_RECOMP_VERSION)/ido-5.3-recomp-$(DETECTED_OS).tar.gz -O $@

$(IDO_5_3): tool_archives/archives/ido-5.3-recomp-$(DETECTED_OS).tar.gz | $(IDO_5_3_DIR)
	tar xzf $< -C $(IDO_5_3_DIR)

tool_archives/archives/ido-7.1-recomp-$(DETECTED_OS).tar.gz:
	mkdir -p $(@D)
	wget $(WGET_FLAGS) https://github.com/decompals/ido-static-recomp/releases/download/$(IDO_RECOMP_VERSION)/ido-7.1-recomp-$(DETECTED_OS).tar.gz -O $@

$(IDO_7_1): tool_archives/archives/ido-7.1-recomp-$(DETECTED_OS).tar.gz | $(IDO_7_1_DIR)
	tar xzf $< -C $(IDO_7_1_DIR)

tool_archives/archives/pigment64-$(PIGMENT64_OS).tar.gz:
	mkdir -p $(@D)
	wget $(WGET_FLAGS) https://github.com/decompals/pigment64/releases/download/$(PIGMENT64_VERSION)/pigment64-$(PIGMENT64_OS).tar.gz -O $@

$(PIGMENT64): tool_archives/archives/pigment64-$(PIGMENT64_OS).tar.gz | $(PIGMENT64_DIR)
	tar xzf $< -C $(PIGMENT64_DIR)

$(IDO_5_3_DIR):
	mkdir -p $@

$(IDO_7_1_DIR):
	mkdir -p $@

$(PIGMENT64_DIR):
	mkdir -p $@
