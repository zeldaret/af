
.PHONY: all clean distclean
GCC_DIR   := gcc
AR        := $(GCC_DIR)/ar
GCC-2.7.2 := $(GCC_DIR)/gcc
STRIP-2.7 := $(GCC_DIR)/strip-2.7

all: $(AR) $(GCC-2.7.2) $(STRIP-2.7)

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

clean:
distclean: clean
	$(RM) -rf $(GCC_DIR)
