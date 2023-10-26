OUTPUT_FORMAT("binary")
ENTRY(_start)   /* Entry point symbol in your code */
SECTIONS
{
    . = 0x7c00; /* Set the starting address to 0x1000 */
    .text :
    {
        *(.text)
    }
    /* Other sections like .data, .bss, etc. can be defined here */
}
