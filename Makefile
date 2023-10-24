CC = gcc
AS = as
CFLAGS = -Wall
ASFLAGS =

SRC_DIR = src
BIN_DIR = bin

# Use find to locate all .c and .S files in src and subdirectories
C_FILES = $(shell find $(SRC_DIR) -name '*.c')
S_FILES = $(shell find $(SRC_DIR) -name '*.S')

# Create object file names for .c and .S files in bin directory
C_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(C_FILES))
S_OBJ_FILES = $(patsubst $(SRC_DIR)/%.S, $(BIN_DIR)/%.o, $(S_FILES))

# Target for the final binary
TARGET = my_program

# Targets
all: dirs $(TARGET)

# Build .c source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build .S assembly source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.S
	$(AS) $(ASFLAGS) $< -o $(BIN_DIR)/$(notdir $@)

# Link all object files into the final binary
$(TARGET): $(C_OBJ_FILES) $(S_OBJ_FILES)
	$(CC) $(C_OBJ_FILES) $(BIN_DIR)/$(notdir $(S_OBJ_FILES)) -o $(BIN_DIR)/$@

dirs:
	mkdir -p bin

clean:
	rm -f $(BIN_DIR)/*.o
	rm -f $(BIN_DIR)/*.iso
	rm -f $(BIN_DIR)/*.elf
	rm -f $(BIN_DIR)/*.bin
	rm -f $(BIN_DIR)/$(TARGET)
	rmdir $(BIN_DIR)

.PHONY: all clean