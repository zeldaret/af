UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	DETECTED_OS := windows
	DOWNLOAD_OS := windows-latest
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS := linux
	DOWNLOAD_OS := ubuntu-20.04
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS := macos
	DOWNLOAD_OS := macos-latest
endif


IDO_5_3_DIR := ido/$(DETECTED_OS)/5.3
IDO_5_3     := $(IDO_5_3_DIR)/cc

IDO_7_1_DIR := ido/$(DETECTED_OS)/7.1
IDO_7_1     := $(IDO_7_1_DIR)/cc

all: $(IDO_5_3) $(IDO_7_1)

clean:
	$(RM) -rf $(IDO_5_3_DIR) $(IDO_7_1_DIR)

distclean: clean
	$(RM) -rf ido

.PHONY: all clean distclean


$(IDO_5_3): | $(IDO_5_3_DIR)
	wget https://github.com/decompals/ido-static-recomp/releases/latest/download/ido-5.3-recomp-$(DOWNLOAD_OS).tar.gz
	tar xf ido-5.3-recomp-$(DOWNLOAD_OS).tar.gz -C $(IDO_5_3_DIR)
	$(RM) ido-5.3-recomp-$(DOWNLOAD_OS).tar.gz

$(IDO_7_1): | $(IDO_7_1_DIR)
	wget https://github.com/decompals/ido-static-recomp/releases/latest/download/ido-7.1-recomp-$(DOWNLOAD_OS).tar.gz
	tar xf ido-7.1-recomp-$(DOWNLOAD_OS).tar.gz -C $(IDO_7_1_DIR)
	$(RM) ido-7.1-recomp-$(DOWNLOAD_OS).tar.gz

$(IDO_5_3_DIR):
	mkdir -p $@

$(IDO_7_1_DIR):
	mkdir -p $@

distclean: clean
