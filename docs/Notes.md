# Notes File For Snake OS

## Makefile

### Readers Notes for when the repo goes public

Meant to be ran on Linux

The current structure is setup in such a way that it's expected that for every .c file in source there needs to be a .h file in include (when a .h file makes sense of course)

The new command to run everything
nasm "src/bootloader/start.asm" -f bin -o "src/bootloader/start.bin"


i386-elf-gcc -ffreestanding -m32 -g -I include/interrupts/ -I include/kernel/ -I include/utils/ -c "src/kernel/kernel.c" -o "src/kernel/kernel.o"



i386-elf-ld -o "semi_complete.bin" -T "misc/linker.ld" -Tt
ext 0x1000 src/kernel/kernel_entry.o src/kernel/kernel.o --oformat binary




&& cat "src/bootloader/start.bin" "semi_complete.bin" > "complete.bin" && qemu-system-x86_64 -drive format=raw,file="complete.bin",index=0,if=floppy, -m 128M
