#include "interrupts/interrupts.h"
#include "kernel/fpu.h"
#include "kernel/kernel_ops.h"

void kernel_main(void) {
    // char* video_memory = (char*)0xb8000;
    // video_memory[0] = 'Q';
    // video_memory[1] = 0x07;  // Text attribute (color)
    k_clear();

    interrupts_init();
    fpu_init();
    screen_init();



    // k_panic("Oh no.", "lalala", true);

    for (;;) {}

}