#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"
#include "timer.h"

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   200
#define SCREEN_SIZE     (SCREEN_WIDTH * SCREEN_HEIGHT)
#define SCREEN_PITCH    320

/* VGA control port addresses */
#define PALETTE_MASK    0x3C6
#define PALETTE_READ    0x3C7
#define PALETTE_WRITE   0x3C8
#define PALETTE_DATA    0x3C9


void screen_swap();
void screen_clear(uint8_t color);
void init_screen();

void draw_pixel(uint8_t x, uint8_t y, uint8_t color);

#endif /* SCREEN_H */