// #include "interrupts.h"
#include "kernel_ops.h"
#include "utils.h"


void kernel_main(void) {
    char* video_memory = (char*)0xb8000;

    video_memory[0] = 'Q';
    video_memory[1] = 0x07;  // Text attribute (color)~
    video_memory[2] = 'Q';
    video_memory[3] = 0x07;  // Text attribute (color)
    video_memory[4] = 'Q';
    video_memory[5] = 0x07;  // Text attribute (color)
    video_memory[6] = 'Q';
    video_memory[7] = 0x07;  // Text attribute (color)

    k_print("Hello, world!", WHITE_TXT);

    // interrupts_init();
    // k_clear();

    // fpu_init();
    //screen_init();


    // asm volatile("int $0x3");
    // asm volatile("int $0x4");

    // k_panic("Oh no.", "lalala", true);

    for (;;) {}
}
