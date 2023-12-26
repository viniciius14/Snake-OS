#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"
#include "timer.h"

/* Ideally this dimenstions wouldn't be hardcoded */
#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   200

#define SCREEN_SIZE     (SCREEN_WIDTH * SCREEN_HEIGHT)

/* VGA control port addresses */
#define PALETTE_MASK    0x3C6
#define PALETTE_READ    0x3C7
#define PALETTE_WRITE   0x3C8
#define PALETTE_DATA    0x3C9

#define VC_BLACK        0x00
#define VC_RED          0xE0
#define VC_GREEN        0x1C
#define VC_YELLOW       0xFC
#define VC_PINK         0xE3
#define VC_CYAN         0x1F
#define VC_L_GREY       0x6D
#define VC_WHITE        0xFF

void init_screen(void);
// void screen_swap(void);
void screen_clear(uint8_t color);
void draw_pixel(uint16_t x, uint16_t y, uint8_t color);

/* Writes a popup to the screen and waits for any key to be pressed */
void draw_popup(const char *msg, uint8_t color);

#endif /* SCREEN_H */