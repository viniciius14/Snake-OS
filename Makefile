CC = i386-elf-gcc

#C_FLAGS =  -m32 -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
#C_FLAGS += -Wno-pointer-arith -Wno-unused-parameter
#C_FLAGS += -nostdlib -nostdinc -ffreestanding -fno-pie -fno-stack-protector
#C_FLAGS += -fno-builtin-function -fno-builtin

C_EXTRA_HEADERS =  $(INCLUDE_DIR)/utils/colors.h \
				   $(INCLUDE_DIR)/utils/macros.h \
				   $(INCLUDE_DIR)/utils/types.h


AS = nasm
ASM_FLAGS = bin


LD = i386-elf-ld
LD_FLAGS = text 0x1000
LD_SCRIPT = misc/linked.ld


# Directories
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

OUTPUT = Snake.bin

# Find source files
C_FILES = $(wildcard $(SRC_DIR)/**/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/**/*.asm)


# Generate object file names from source files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(C_FILES)) \
            $(patsubst $(SRC_DIR)/%.asm, $(BIN_DIR)/%.o, $(ASM_FILES))


# Build rule for specific asm file
$(BIN_DIR)/start.bin: $(SRC_DIR)/bootloader/start.asm
	@mkdir -p $(@D)
	$(AS) $< -f $(ASM_FLAGS) -o $@


# Rules to build object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(C_FLAGS) -I$(INCLUDE_DIR)/$(dir $<) -c $< -o $(BIN_DIR)/$(notdir $@)


$(BIN_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(@D)
	$(AS) $(ASM_FLAGS) -o $@ $<


all: $(OBJ_FILES)
	@echo "aaaaaaaa"
	@echo $(OBJ_FILES)
	$(LD) -T$(LD_FLAGS) -T $(LD_SCRIPT) -o $(BIN_DIR)/$(OUTPUT) $(OBJ_FILES) --oformat binary


clean:
	find . -name "*.o" -type f -exec rm {} \;
	find . -name "*.bin" -type f -exec rm {} \;
	rmdir -p $(BIN_DIR)

run:
	qemu-system-x86_64 -drive format=raw,file="$(OUTPUT)",index=0,if=floppy, -m 128M
