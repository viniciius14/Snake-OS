#include "utils.h"
#include "kernel_ops.h"
#include "idt.h"
#include "pic.h"
#include "fpu.h"
#include "timer.h"
#include "keyboard.h"

void kernel_main(void) {
    k_print("Test\n");

    /* Setup interrups */
    init_idt();
    init_fpu();
    /* Mask off all hardware interrupts (disable PIC) */
    disable_pic();

    /* Remap PIC */
    remap_pic();

    /* Add PIT interrupt handler */
    init_timer();

    init_keyboard();

    __asm__ __volatile__ ("sti");

    for (;;) {}
}
