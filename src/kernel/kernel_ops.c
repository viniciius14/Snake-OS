#include "kernel/kernel_ops.h"
#include "utils/types.h"
#include "utils/colors.h"
#include "utils/debugger.h"

uint8_t curr_line = 0;

void k_panic(const char *message, const char* code, bool halt) {
    k_clear();

    k_print("SYSTEM ERROR\n", RED_TXT);
    k_print("Exception has ocurred.\n", WHITE_TXT);

    k_print("Message: ", WHITE_TXT);
    k_print_var(message);

    k_print("Code: ", WHITE_TXT);
    k_print_var(code);

    if(halt) {
        k_print("\n\n\nFATAL\n\n\n", RED_TXT);
        asm("cli");
        asm("halt");
    } else {
        k_print("\n\n\nNON FATAL\n\n\n", RED_TXT);
    }

#if DEBUG
    context_dump();
#endif
}

void k_print(const char *msg, color text_color) {
    char* video_memory = (char*)0xb8000;

    /* The screen is 80 characters wide */
    uint8_t i = curr_line * 80 * 2;

    while(*msg != 0) {
        video_memory[i++] = *msg;

        if(*msg == '\n') {
            curr_line++;
            k_print('\r', text_color);
        }

        msg++;
        video_memory[i++] = text_color;
    }
}

void k_print_var(const char *msg) {
    while(*msg != '\0') {
        char letter[] = {*msg, '\0'};
        k_print(letter, BLUE_TXT);
        msg++;
    }
    k_print('\n', WHITE_TXT);
}

void k_clear() {
    char* video_memory = (char*)0xb8000;
    uint8_t i = 0;

    while(i > (80 * 25 * 2)) {
        video_memory[i++] = ' ';
        video_memory[i++] = WHITE_TXT;
    }

    curr_line = 0;
}