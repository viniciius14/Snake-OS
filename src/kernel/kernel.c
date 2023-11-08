#include "interrupts.h"
#include "kernel_ops.h"
#include "idt.h"

void kernel_main(void) {
    // char* video_memory = (char*)0xb8000;
    // video_memory[0] = 'Q';
    // video_memory[1] = 0x07;  // Text attribute (color)

    interrupts(true);
    k_clear();
    idt_init();
    fpu_init();

    k_panic("Oh no.", "lalala", true);

    for (;;) {}
    
}