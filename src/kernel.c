#include "utils.h"
#include "kernel_ops.h"
#include "idt.h"
#include "pic.h"
#include "timer.h"
#include "keyboard.h"

void kernel_main(void) {
    k_print("Test\n");

    /* Setup interrups */
    init_idt();

    /* Mask off all hardware interrupts (disable PIC) */
    disable_pic();

    /* Remap PIC */
    remap_pic();

    /* Add PIT interrupt handler */
    init_timer();

    init_keyboard();
    k_print("keyboard initialized\n");

    __asm__ __volatile__ ("sti");

    for (;;) {}
}
