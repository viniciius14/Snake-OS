#include "kernel_ops.h"

char* video_memory = (char*)0xb8000;
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
        __asm__ __volatile__("cli");
        __asm__ __volatile__("hlt");
    } else {
        k_print("\n\n\nNON FATAL\n\n\n", RED_TXT);
    }

#if DEBUG
    context_dump();
#endif
}

void k_print(const char *msg, color text_color) {
    /* The screen is 80 characters wide */
    uint8_t i = curr_line * 80 * 2;

    while(*msg != 0) {
        video_memory[i++] = *msg;

        if(*msg == '\n') {
            curr_line++;
            char ret = '\r';
            k_print(&ret, text_color);
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
    char nl = '\n';
    k_print(&nl, WHITE_TXT);
}

void k_print_register(const char* msg, const void *reg_addr, size_t num_bytes, color text_color) {
    k_print(msg, text_color);

    for (size_t byte = 0; byte < num_bytes; byte++) {
        // Extract each byte from the register address
        uint8_t current_byte = *((const uint8_t *)reg_addr + byte);

        /* Convert the byte to a two-digit hexadecimal string */
        char hex_string[3];
        hex_string[0] = "0123456789ABCDEF"[current_byte >> 4];
        hex_string[1] = "0123456789ABCDEF"[current_byte & 0x0F];
        hex_string[2] = '\0';

        /* Print the two-digit hexadecimal string */
        k_print(hex_string, text_color);

        /* Print a space between bytes for better readability */
        if (byte < num_bytes - 1) {
            k_print(" ", text_color);
        }
    }

    k_print("\n", WHITE_TXT);
}

void k_clear() {
    uint16_t i = 0;

    while(i < (80 * 25 * 2)) {
        video_memory[i++] = ' ';
        video_memory[i++] = WHITE_TXT;
    }

    curr_line = 0;
}

void fpu_init() {
    size_t t;

    __asm__ __volatile__("clts");
    __asm__ __volatile__("mov %%cr0, %0" : "=r"(t));
    t &= ~(1 << 2);
    t |= (1 << 1);
    __asm__ __volatile__("mov %0, %%cr0" :: "r"(t));
    __asm__ __volatile__("mov %%cr4, %0" : "=r"(t));
    t |= 3 << 9;
    __asm__ __volatile__("mov %0, %%cr4" :: "r"(t));
    __asm__ __volatile__("fninit");
}
