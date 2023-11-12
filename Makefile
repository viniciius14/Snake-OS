CC =i386-elf-gcc

C_FLAGS =-Wall -ffreestanding -m32 -g
C_INCLUDE =include/

AS =nasm
ASM_FLAGS =elf

C_FLAGS =-m32 -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
C_FLAGS +=-Wno-pointer-arith -Wno-unused-parameter
C_FLAGS +=-nostdlib -nostdinc -ffreestanding -fno-pie -fno-stack-protector
C_FLAGS +=-fno-builtin-function -fno-builtin

LD =i386-elf-ld
LD_FLAGS =text 0x1000
LD_SCRIPT =misc/linker.ld


# Dirs
SRC_DIR =src
BIN_DIR =bin
INCLUDE_DIR =include
OUTPUT =Snake.bin


START =src/bootloader/start.asm
ASM_FILES =$(wildcard $(SRC_DIR)/**/*.asm)
C_FILES =$(wildcard $(SRC_DIR)/**/*.c)


START_FILE =$(patsubst $(SRC_DIR)/%.asm, $(BIN_DIR)/%.bin, $(START))

OBJ_FILES =$(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(C_FILES))\
			$(patsubst $(SRC_DIR)/%.asm, $(BIN_DIR)/%.o, $(ASM_FILES))

# Rules to build object files
$(START_FILE) : $(START)
	$(AS) -f bin $< -o $(BIN_DIR)/$(notdir $@)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.asm
	if [ "$<" != "$(START)" ]; then \
		$(AS) -f $(ASM_FLAGS) $< -o $(BIN_DIR)/$(notdir $@); \
	fi

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(C_FLAGS) -I$(INCLUDE_DIR) -c $< -o $(BIN_DIR)/$(notdir $@)


all: dirs $(START_FILE) $(OBJ_FILES)
	$(LD) -T$(LD_FLAGS) -T $(LD_SCRIPT) -c $(BIN_DIR)/$(notdir $(OBJ_FILES)) -o $(BIN_DIR)/$(OUTPUT) --oformat binary
	@cat $(BIN_DIR)/$(START_FILE) $(BIN_DIR)/$(OUTPUT) > $(BIN_DIR)/$(OUTPUT)

dirs:
	@mkdir -p bin

clean:
	find . -name "*.o" -type f -exec rm {} \;
	find . -name "*.bin" -type f -exec rm {} \;
	rmdir $(BIN_DIR)

run:
	qemu-system-x86_64 -drive format=raw,file="$(BIN_DIR)/$(OUTPUT)",index=0,if=floppy, -m 128M
