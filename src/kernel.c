#include "utils.h"
#include "kernel_ops.h"
#include "idt.h"
#include "pic.h"

void kernel_main(void) {
    k_print("Test");
    /* Setup interrups */
    init_idt_32();
    /* Mask off all hwardware interrupts (disable PIC) */
    disable_pic();
    /* Remap PIC */
    remap_pic();
/*
    set_idt_descriptor_32(32, timer_handler, INT_GATE_FLAGS);
    set_idt_descriptor_32(33, keyboard_handler, INT_GATE_FLAGS);
*/

    for (;;) {}
}
