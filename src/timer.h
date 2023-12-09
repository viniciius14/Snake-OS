#ifndef TIMER_H
#define TIMER_H

#include "utils.h"
#include "idt.h"
#include "pic.h"
#include "kernel_ops.h"

uint32_t tick = 0;

/* PIT timer channel 0 PIC IRQ0 interrupt handler */
INTERRUPT void timer_irq0_handler(int_frame_32_t *frame) {
    k_print_dec(tick++);
    k_print("\n");

    send_pic_eoi(0);
}



#endif /* TIMER_H */