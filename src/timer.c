#include "timer.h"

/* Not checking for an overflow on the tick variable because for the
current ~18 ticks/s you would need to be with this on for 66k+ hours */

uint32_t tick;

void init_timer(void) {
    idt_set_descriptor(32, timer_handler, INT_GATE_FLAGS);
    clear_irq_mask(0);
}


/* PIT timer channel 0 PIC IRQ0 interrupt handler */
INTERRUPT void timer_handler(int_frame_32_t *frame) {
    (void)frame;
    tick++;
    send_pic_eoi(0);
}

void sleep(uint16_t time) {
    uint32_t curr = tick;
    while (tick < (curr + time)) {
        /* Do nothing */
    }
}