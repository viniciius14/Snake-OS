#include "timer.h"


/* Not checking for an overflow on the ticks variable because for the
current ~18 ticks/s you would need to be with this on for 66k+ hours */
volatile uint32_t ticks;
static uint32_t seed = 12;

void init_timer(void) {
    idt_set_descriptor(32, timer_handler, INT_GATE_FLAGS);
    clear_irq_mask(0);
}


/* PIT timer channel 0 PIC IRQ0 interrupt handler */
INTERRUPT void timer_handler(int_frame_32_t *frame) {
    (void)frame;
    ticks++;
    send_pic_eoi(0);
}

void sleep(uint16_t time) {
    uint32_t curr = ticks;
    while (ticks <= (curr + time)) {
        /* Do nothing */
        ASM("nop");
    }
}

uint32_t rand(void) {
    uint32_t curr_tick = ticks;
    seed = seed * 1103515245 + curr_tick;
    return (seed / 65536) % 9999;
}