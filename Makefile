# Compiler and assembler
CC = gcc -elf_i386
AS=as --32

#Flags
CCFLAGS=-m32 -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CCFLAGS+=-Wno-pointer-arith -Wno-unused-parameter
CCFLAGS+=-nostdlib -nostdinc -ffreestanding -fno-pie -fno-stack-protector
CCFLAGS+=-fno-builtin-function -fno-builtin


BOOTSECT_SRCS=src/bootloader/stage0.S

BOOTSECT_OBJS=$(BOOTSECT_SRCS:.S=.o)

KERNEL_C_SRCS=$(wildcard src/*.c)
KERNEL_S_SRCS=$(filter-out $(BOOTSECT_SRCS), $(wildcard src/*.S))
KERNEL_OBJS=$(KERNEL_C_SRCS:.c=.o) $(KERNEL_S_SRCS:.S=.o)


BOOTSECT=bootsect.bin
KERNEL=kernel.bin
ISO=boot.iso

all: dirs bootsect kernel

clean:
	find . -type f -name "*.o" -exec rm {} \;
	find . -type f -name "*.iso" -exec rm {} \;
	find . -type f -name "*.elf" -exec rm {} \;
	find . -type f -name "*.bin" -exec rm {} \;
	rmdir bin

# All object files shall go to the bin directory
%.o: %.c
	$(CC) -o bin/$(notdir $@) -c $< $(CCFLAGS)

%.o: %.S
	$(AS) -o bin/$(notdir $@) -c $< $(ASFLAGS)


dirs:
	mkdir -p bin

bootsect: $(BOOTSECT_OBJS)
	$(LD) -o ./bin/$(BOOTSECT) $^ -Ttext 0x7C00 --oformat=binary

# kernel: $(KERNEL_OBJS)
# 	$(LD) -o ./bin/$(KERNEL) $^ $(LDFLAGS) -Tsrc/link.ld

# iso: dirs bootsect kernel
# 	dd if=/dev/zero of=boot.iso bs=512 count=2880
# 	dd if=./bin/$(BOOTSECT) of=boot.iso conv=notrunc bs=512 seek=0 count=1
# 	dd if=./bin/$(KERNEL) of=boot.iso conv=notrunc bs=512 seek=1 count=2048














# # Directorys
# CURRENT_DIR := $(CURDIR)






# INCLUDES = include/*.h

# # Define directories
# SRC_DIR = src

# BOOTSECT=bootsect.bin
# KERNEL=kernel.bin
# ISO=boot.iso

# # List of source files
# SOURCES = $(wildcard $(SRC_DIR)/*.c)

# # Generate corresponding object file names
# OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SOURCES))

# all: dirs compile link

# dirs:
# 	mkdir -p bin

# compile:
# # Compile source files into object files
# $(BIN_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) -o $@ -c $<

# link:
# # Link the object files to create the final executable
# $(BIN_DIR)/my_program: $(OBJECTS)
# 	$(CC) $(CFLAGS) -o $@ $^

# bootsect: $(BOOTSECT_OBJS)
# 	$(LD) -o ./bin/$(BOOTSECT) $^ -Ttext 0x7C00 --oformat=binary

# kernel: $(KERNEL_OBJS)
# 	$(LD) -o ./bin/$(KERNEL) $^ $(LDFLAGS) -Tsrc/link.ld

# iso: dirs bootsect kernel
# 	dd if=/dev/zero of=boot.iso bs=512 count=2880
# 	dd if=./bin/$(BOOTSECT) of=boot.iso conv=notrunc bs=512 seek=0 count=1
# 	dd if=./bin/$(KERNEL) of=boot.iso conv=notrunc bs=512 seek=1 count=2048

# qemu: compile link iso
# 	qemu-system-i386 -drive fromat=raw, file=boot.iso


# clean:
# 	rm -f ./**/*.o
# 	rm -f ./*.iso
# 	rm -f ./**/*.elf
# 	rm -f ./**/*.bin

