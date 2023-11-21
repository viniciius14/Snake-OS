#include "timer.h"
#include "interrupts.h"
#include "kernel_ops.h"

uint32_t tick = 0;

void init_timer(uint32_t freq) {
    register_interrupt_handler(32, &timer_callback);

    uint32_t div = 1192180 / freq;

    outportb(0x43, 0x36);

    outportb(0x40, (uint8_t)(div & 0xFF));
    outportb(0x40, (uint8_t)((div >> 8) & 0xFF));
}

void timer_callback(struct registers regs) {
    tick++;
    k_print("tick\n", WHITE_TXT);
    (void)regs;
}

