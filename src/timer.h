#ifndef TIMER_H
#define TIMER_H

#include "utils.h"
#include "idt.h"
#include "pic.h"
#include "kernel_ops.h"


void init_timer(void);

/* PIT timer channel 0 PIC IRQ0 interrupt handler */
INTERRUPT void timer_handler(int_frame_32_t *frame);


#endif /* TIMER_H */