#ifndef TIMER_H
#define TIMER_H

#include "utils.h"
#include "interrupts.h"

#define TIMER_TPS 363

void init_timer(uint32_t freq);
void timer_callback(registers_t regs);

#endif /* TIMER_H */