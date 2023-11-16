CC=i386-elf-gcc
C_FLAGS=-DDEBUG -fno-builtin

C_FILES =$(wildcard *.c)

%.o : %.c $(C_FILES)
	$(CC) -c $(C_FILES) -o ../bin/$(notdir $(C_FILES))

all:


c: