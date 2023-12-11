#include "kernel_ops.h"



uint16_t *video_memory = (uint16_t *)0xB8000;

uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

void move_cursor(void) {
    uint16_t cursorPosition = cursor_y * 80 + cursor_x;
    outb(0x03D4, 14);
    outb(0x03D5, cursorPosition >> 8);
    outb(0x03D4, 15);
    outb(0x03D5, cursorPosition);
}

void scroll(void) {

    if (cursor_y >= 25) {
        int i;
        for (i = (0 * 80) ; i < (24 * 80) ; i++) {
            video_memory[i] = video_memory[i+80];
        }
        for (i = (24 * 80) ; i < (25 * 80) ; i++) {
            video_memory[i] = BLANK;
        }
        cursor_y = 24;
    }
}

/*
 This function doesn't support going back to the last character
 after deleting a line beggining.
*/
void k_put_c(char c) {
    uint8_t backColour = BLACK_TXT;
    uint8_t foreColour = WHITE_TXT;

    uint8_t  attributeByte = (backColour << 4) | (foreColour & 0x0F);

    uint16_t attribute = attributeByte << 8;
    uint16_t *location;

    /* If the character is a backspace go back 1 position */
    if (c == 0x08) {
        if (!cursor_x && cursor_y > 0) {
            cursor_x = 80;
            cursor_y--;
        } else if (!cursor_x && !cursor_y) {
            return;
        }
        cursor_x--;
        k_put_c(' ');
        cursor_x--;
    }
    /* If the character is a tab go to the next position divisible by 4 */
    else if (c == 0x09) {
        cursor_x = (cursor_x + 4) & ~(4-1);
    }
    /* If character is a return reset position */
    else if (c == '\r') {
        cursor_x = 0;
    }
    /* If character is a new line reset x position and increment y position */
    else if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    }
    /* Handle any other printable character */
    else if(c >= ' ') {
        location = video_memory + (cursor_y * 80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }
    /* Check if we need to write into a new line since screen boundary has been reached */
    if (cursor_x > 80) {
        cursor_x = 0;
        cursor_y ++;
    }
    scroll();
    move_cursor();
}

void k_clear(void) {
    uint8_t attributeByte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attributeByte << 8);

    uint32_t i;
    for (i = 0; i < (80 * 25) ; i++) {
        video_memory[i] = blank;
    }
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

void k_print(const char *c) {
    uint32_t i = 0;
    while (c[i]) {
        k_put_c(c[i++]);
    }
}

void k_print_hex(uint32_t n) {
    int32_t tmp;
    char noZeroes = 1;
    int i;

    k_print("0x");
    for (i = 28; i > 0 ; i -= 4) {
        tmp = (n >> i) & 0x0F;
        if (tmp == 0 && noZeroes != 0) {
            continue;
        }
        if (tmp >= 0x0A) {
            noZeroes = 0;
            char send = tmp - 0x0A + 'a';
            k_print(&send);
        } else {
            noZeroes = 0;
            char send = tmp + '0';
            k_print(&send);
        }
    }

    tmp = n & 0x0F;

    if (tmp >= 0x0A) {
        char send = tmp - 0x0A + 'a';
        k_print(&send);
    } else {
        char send = tmp + '0';
        k_print(&send);
    }
}

void k_print_dec(uint32_t n) {
    if (n == 0) {
        char zero = '0';
        k_print(&zero);
        return;
    }

    int32_t acc = n, i = 0, j = 0;
    char c[32], c2[32];

    while (acc > 0) {
        c[i] = '0' + (acc % 10);
        acc /= 10;
        i++;
    }

    c[i] = 0;
    c2[i--] = 0;

    while(i >= 0){
        c2[i--] = c[j++];
    }

    k_print(c2);
}

void k_panic(const char *message, const char* code, bool halt) {
    k_clear();

    k_print("SYSTEM ERROR\n");
    k_print("Exception has ocurred.\n");

    k_print("Message: ");
    k_print(message);
    k_print("Code: ");
    k_print(code);

    if(halt) {
        //CTX_DMP(); // TBD implement
        k_print("\n\n\nFATAL\n\n\n");
        __asm__ __volatile__("cli");
        __asm__ __volatile__("hlt");
    } else {
        k_print("\n\n\nNON FATAL\n\n\n");
    }
}


/* Sets n bytes of memory to value starting at address dst */
void memset(void *dst, uint8_t value, size_t n) {
    uint8_t *d = dst;
    while (n-- > 0) {
        *(d++) = value;
    }
}

/* Copies n bytes of memory from src to dst */
void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *d = dst;
    const uint8_t *s = src;

    while (n-- > 0) {
        *(d++) = *(s++);
    }
    return dst;
}

/* Moves n bytes from src to dst */
void *memmove(void *dst, const void *src, size_t n) {
    if (src > dst) {
        return memcpy(dst, src, n);
    }

    uint8_t *d = dst;
    const uint8_t *s = src;

    for (size_t i = n ; i > 0 ; i--) {
        d[i - 1] = s[i - 1];
    }

    return dst;
}
