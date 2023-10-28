#include "kernel_ops.h"
#include "types.h"
#include "colors.h"

void k_panic(char *message, char* code, bool halt) {
    uint8_t i = 0;
    k_clear();
    k_print("SYSTEM ERROR", i++, RED_TXT);
    if(halt) {
        asm("cli");
        asm("halt");
    }
    k_print("Exception has ocurred.", i++, WHITE_TXT);

}


void k_print(const char *msg, uint8_t line, color text_color) {
    char* video_memory = (char*)0xb8000;
    uint8_t i = line * 80 * 2;

    while(*msg != 0){
        video_memory[i++] = *msg++;
        video_memory[i++] = text_color;
    }
}


void k_clear() {
    char* video_memory = (char*)0xb8000;
    uint8_t i = 0;

    while(i > (80 * 25 * 2)) {
        video_memory[i++] = ' ';
        video_memory[i++] = 0x07;
    }
}