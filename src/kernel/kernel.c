#include "idt.h"


void kernel_main() {
    char* video_memory = (char*)0xb8000;
    video_memory[0] = 'Q';
    video_memory[1] = 0x07;  // Text attribute (color)
    for (;;) {}



}