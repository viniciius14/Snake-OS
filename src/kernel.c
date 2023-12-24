#include "utils.h"
#include "kernel_ops.h"
#include "idt.h"
#include "pic.h"
#include "fpu.h"
#include "timer.h"
#include "keyboard.h"
#include "screen.h"
#include "font.h"
#include "snake.h"

extern uint8_t *video_memory;
extern uint32_t tick;

void kernel_main(void) {
    /* Setup interrups */
    init_idt();

    /* Initialize floating point unit */
    init_fpu();

    /* Mask off all hardware interrupts (disable PIC) */
    disable_pic();
    /* Remap PIC */
    remap_pic();

    /* Add PIC IRQ0 handler */
    init_timer();

    /* Add PIC IRQ1 handler */
    init_keyboard();

    init_screen();

    // memset(video_memory, 255, 320 * 200 - 1);


    // for(uint32_t i = 0 ; i != SCREEN_WIDTH * 3 ; i++) {
    //     draw_pixel(i - 320  * i % SCREEN_HEIGHT, i % SCREEN_HEIGHT, 255);
    // }
    game_init();
    

    for (;;) {}
}
