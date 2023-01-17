#
# Makefile for etsfun
#
# (C) 2023 modeco80 <lily.modeco80@protonmail.ch>.
#
# SPDX-License-Identifier: MIT
#

NAME = ets_fun

# Toolchain executables
CC = i686-w64-mingw32-gcc
AS = nasm -f elf32
CXX = i686-w64-mingw32-g++

CXXFLAGS = -std=c++20 -Os -ffreestanding -fno-threadsafe-statics -fno-rtti -fno-exceptions -fno-ident -fno-stack-protector -fomit-frame-pointer -fno-unwind-tables -fno-asynchronous-unwind-tables -march=pentium2
LDFLAGS = -s -Wl,-entry,__start -Wl,--disable-runtime-pseudo-reloc -Wl,--file-alignment,0 -Wl,--section-alignment,0 -nostartfiles -nostdlib -nodefaultlibs

BINDIR = bin
OBJDIR = obj

# Project objects
OBJS = $(OBJDIR)/main.o \
	$(OBJDIR)/svccall.o

VPATH = src/

.PHONY: all clean floppy test

all: $(BINDIR)/$(NAME).exe floppy

# Make a floppy which has our executable on it
floppy: $(BINDIR)/$(NAME).exe
	@echo "Making floppy"
	cp res/ets.img $(BINDIR)/exp1440.img
	mcopy -i $(BINDIR)/exp1440.img $(BINDIR)/$(NAME).exe ::/simple.exe

# test w/ bochs.
test: floppy
	-bochs -qf res/test.bochsrc 2>/dev/null

# dir rules
$(BINDIR)/:
	@mkdir -p $(BINDIR)

$(OBJDIR)/:
	@mkdir -p $(OBJDIR)

$(BINDIR)/$(NAME).exe: $(BINDIR)/ $(OBJDIR)/ $(OBJS)
	@echo "LD $@"
	@$(CXX) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.cpp
	@echo "CXX $<"
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJDIR)/%.o: %.asm
	@echo "NASM $<"
	@$(AS) $< -o $@

clean:
	rm -rf $(BINDIR)/ $(OBJDIR)/
