#include "interrupts.h"
#include "kernel_ops.h"

void kernel_main(void) {
    // char* video_memory = (char*)0xb8000;
    // video_memory[0] = 'Q';
    // video_memory[1] = 0x07;  // Text attribute (color)

    interrupts_init();
    k_clear();

    // fpu_init();
    //screen_init();

    k_print("Hello, world!\n", WHITE_TXT);

    asm volatile("int $0x3");
    asm volatile("int $0x4");

    // k_panic("Oh no.", "lalala", true);

    for (;;) {}

}