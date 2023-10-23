CC = gcc
CFLAGS =-std=c11 -g -Wall -D_FORTIFY_SOURCE=2 -O2 -Wextra -Wpedantic -Wstrict-aliasing
ASM=x86_64-elf-gcc

# Directorys
CURRENT_DIR := $(CURDIR)
SOURCE = src/*.c
BINARIES = /bin
INCLUDES = include/*.h

# Define directories
SRC_DIR = src
BIN_DIR = bin

# List of source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Generate corresponding object file names
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SOURCES))

all: $(BIN_DIR)/my_program

# Compile source files into object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Link the object files to create the final executable
$(BIN_DIR)/my_program: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^


clean:
	find . -name '*.o' -exec rm -f {} +
	find . -name '*.' -exec rm -f {} +