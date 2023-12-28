#include "utils.h"
#include "kernel_ops.h"
#include "idt.h"
#include "pic.h"
#include "timer.h"
#include "keyboard.h"
#include "screen.h"
#include "font.h"
#include "snake.h"

extern uint8_t *video_memory;
extern uint32_t ticks;

void kernel_main(void) {
    /* Setup interrups */
    init_idt();

    /* Mask off all hardware interrupts (disable PIC) */
    disable_pic();
    /* Remap PIC */
    remap_pic();

    /* Add PIC IRQ0 handler */
    init_timer();

    /* Add PIC IRQ1 handler */
    init_keyboard();

    /* Initialize the color palette */
    init_screen();

    /* Initialize the game and it's loop */
    init_game();

    for (;;) {}
}
