# Basic Makefile (I'd use cmake but lazy..)
NAME = ets_fun

# Add any additional source directories your project may use here
VPATH = src/

MINGW_TARGET = i686-w64-mingw32

# Toolchain executables
CC = $(MINGW_TARGET)-gcc
AS = nasm -f elf32
CXX = $(MINGW_TARGET)-g++

CXXFLAGS = -std=c++20 -Os -ffreestanding -fno-threadsafe-statics -fno-rtti -fno-exceptions -fno-ident -fno-stack-protector -fomit-frame-pointer -fno-unwind-tables -fno-asynchronous-unwind-tables -march=pentium2 -Iinclude -Isrc
LDFLAGS = -s -Wl,-entry,__start -nostartfiles -nostdlib -nodefaultlibs

BINDIR = bin
OBJDIR = obj

# Project objects
OBJS = $(OBJDIR)/main.o \
	$(OBJDIR)/syscall.o

.PHONY: all clean floppy test

all: $(BINDIR)/$(NAME).exe floppy

# Make a floppy which has our executable on it
floppy: $(BINDIR)/$(NAME).exe
	cp res/ets.img $(BINDIR)/exp1440.img
	mcopy -i $(BINDIR)/exp1440.img $(BINDIR)/$(NAME).exe ::/simple.exe

# test w/ bochs.
test: floppy
	-echo 'c' | bochs -qf res/test.bochsrc 2>/dev/null

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
