OUTPUT_FORMAT("binary")
TARGET(elf32-i386)
ENTRY(_start)
SECTIONS
{
    . = 0x1000;    /* set starting address */

    .text ALIGN(4K) : { *(.text) }
    .rodata ALIGN(4K) : { *(.rodata) }
    .data ALIGN(4K) : { *(.data) }
    .bss ALIGN(4K) : { *(.bss) }

    end = .;
}