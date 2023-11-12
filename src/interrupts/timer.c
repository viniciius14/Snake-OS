#include "interrupts/timer.h"
#include "utils/io.h"
#include "interrupts/interrupts.h"
#include "interrupts/pic.h"

uint32_t tick = 0;

void init_timer(uint32_t freq) {

    interrupts(false);
    add_int(32, &timer_callback);
    unmaskIRQ(32);
    interrupts(true);

    uint32_t div = 1192180 / freq;

    outportb(0x43, 0x36);

    outportb(0x40, (uint8_t)(div & 0xFF));
    outportb(0x40, (uint8_t)((div >> 8) & 0xFF));
}


static void timer_callback(void) {
    tick++;
}