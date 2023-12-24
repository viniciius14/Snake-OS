#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"
#include "timer.h"

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   200
#define SCREEN_SIZE     (SCREEN_WIDTH * SCREEN_HEIGHT)
#define SCREEN_PITCH    320

/*
#define COLOR(_r, _g, _b)((uint8_t)( \
    (((_r) & 0x7) << 5) |       \
    (((_g) & 0x7) << 2) |       \
    (((_b) & 0x3) << 0)))
*/

/* VGA control port addresses */
#define PALETTE_MASK    0x3C6
#define PALETTE_READ    0x3C7
#define PALETTE_WRITE   0x3C8
#define PALETTE_DATA    0x3C9

#define VC_BLACK        0x00
#define VC_WHITE        0xff

void init_screen(void);
// void screen_swap(void);
void screen_clear(uint8_t color);
void draw_pixel(uint16_t x, uint16_t y, uint8_t color);

#endif /* SCREEN_H */