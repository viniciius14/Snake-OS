#include "timer.h"

uint32_t tick;

void init_timer(void) {
    idt_set_descriptor(32, timer_handler, INT_GATE_FLAGS);
    clear_irq_mask(0);
}


/* PIT timer channel 0 PIC IRQ0 interrupt handler */
INTERRUPT void timer_handler(int_frame_32_t *frame) {
    // k_print_dec(tick++);
    // k_print("\n");
    tick++;
    send_pic_eoi(0);
}