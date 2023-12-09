#include "utils.h"
#include "kernel_ops.h"
#include "idt.h"
#include "pic.h"
#include "timer.h"

void kernel_main(void) {
    k_print("Test\n");
    /* Setup interrups */
    init_idt_32();
    /* Mask off all hwardware interrupts (disable PIC) */
    disable_pic();
    /* Remap PIC */
    k_print("Timer ticked: ");

    remap_pic();
    set_idt_descriptor_32(32, timer_irq0_handler, INT_GATE_FLAGS);
    clear_irq_mask(0);
/*
    set_idt_descriptor_32(33, keyboard_handler, INT_GATE_FLAGS);

    Enblae PIC iqr interrupts after setign their descriptors
    clear_irq_mask(1);

    after this we can enable interrupts with sti
*/
    __asm__ __volatile__ ("sti");

    for (;;) {}
}
