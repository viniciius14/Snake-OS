#ifndef TIMER_H
#define TIMER_H

#include "utils/types.h"

#define TIMER_TPS 363

void init_timer(uint32_t freq);
static void timer_callback(register regs);

#endif /* TIMER_H */