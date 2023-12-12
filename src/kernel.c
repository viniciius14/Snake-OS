#include "utils.h"
#include "kernel_ops.h"
#include "idt.h"
#include "pic.h"
#include "fpu.h"
#include "timer.h"
#include "keyboard.h"
#include "screen.h"

void kernel_main(void) {
    k_print("Test\n");

    /* Setup interrups */
    init_idt();

    /* Initialize floating point unit */
    init_fpu();

    /* Mask off all hardware interrupts (disable PIC) */
    disable_pic();
    /* Remap PIC */
    remap_pic();
    __asm__ __volatile__ ("sti");

    /* Add PIC IRQ0 handler */
    init_timer();

    /* Add PIC IRQ1 handler */
    init_keyboard();

    init_screen();


    for (;;) {}
}
