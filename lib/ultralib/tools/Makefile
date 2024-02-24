
.PHONY: all clean distclean

# GCC
GCC_DIR   := gcc
AR        := $(GCC_DIR)/ar
GCC-2.7.2 := $(GCC_DIR)/gcc
STRIP-2.7 := $(GCC_DIR)/strip-2.7

# IDO
IDO_DIR   := ido
IDO-5.3   := $(IDO_DIR)/cc

all: $(AR) $(GCC-2.7.2) $(STRIP-2.7) $(IDO-5.3)

$(AR): | $(GCC_DIR)
	wget https://github.com/decompals/mips-binutils-2.6/releases/download/main/binutils-2.6-linux.tar.gz
	tar xf binutils-2.6-linux.tar.gz -C $(GCC_DIR)
	$(RM) binutils-2.6-linux.tar.gz

$(GCC-2.7.2): | $(GCC_DIR)
	wget https://github.com/decompals/mips-gcc-2.7.2/releases/download/main/gcc-2.7.2-linux.tar.gz
	tar xf gcc-2.7.2-linux.tar.gz -C $(GCC_DIR)
	$(RM) gcc-2.7.2-linux.tar.gz

$(STRIP-2.7): | $(GCC_DIR)
	wget https://github.com/decompals/mips-binutils-2.7/releases/download/release/binutils-2.7.tar.gz
	tar xf binutils-2.7.tar.gz -C $(GCC_DIR)
	$(RM) binutils-2.7.tar.gz

$(GCC_DIR):
	mkdir -p $@

$(IDO-5.3): | $(IDO_DIR)
	wget https://github.com/decompals/ido-static-recomp/releases/latest/download/ido-5.3-recomp-linux.tar.gz
	tar xf ido-5.3-recomp-linux.tar.gz -C $(IDO_DIR)
	$(RM) ido-5.3-recomp-linux.tar.gz

$(IDO_DIR):
	mkdir -p $@

clean:
	$(RM) -rf $(GCC_DIR)
	$(RM) -rf $(IDO_DIR)

distclean: clean
