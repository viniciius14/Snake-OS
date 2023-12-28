#include "screen.h"

uint8_t *video_memory = (uint8_t *)0xA0000;

uint8_t v_buffer[2][SCREEN_SIZE];
uint8_t buff_idx = 0;

void init_screen() {
    /* Configure palette with 8-bit RRRGGGBB color */
    outb(PALETTE_MASK, 0xFF);
    outb(PALETTE_WRITE, 0);

    for (uint8_t i = 0; i < 255; i++) {
        outb(PALETTE_DATA, (((i >> 5) & 0x07) * (256 / 8)) / 4);
        outb(PALETTE_DATA, (((i >> 2) & 0x07) * (256 / 8)) / 4);
        outb(PALETTE_DATA, (((i >> 0) & 0x03) * (256 / 4)) / 4);
    }

    /* Set color 255 = white */
    outb(PALETTE_DATA, 0x3F);
    outb(PALETTE_DATA, 0x3F);
    outb(PALETTE_DATA, 0x3F);
}

void screen_swap(void) {
    memcpy(video_memory, &CURRENT, SCREEN_SIZE);
    SWAP();
}

void screen_clear(uint8_t color) {
    memset(video_memory, color, SCREEN_SIZE);
}

void draw_pixel(uint16_t x, uint16_t y, uint8_t color) {
    video_memory[x + (y * SCREEN_WIDTH)] = color;
}

void draw_popup(const char *msg, uint8_t color) {

}

void draw_to_buffer(uint16_t x, uint16_t y, uint8_t color) {
    CURRENT[x + y * SCREEN_WIDTH] = color;
}