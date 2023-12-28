#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"
#include "timer.h"

/* ---------------- Defines ---------------- */

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

/* ---------- Function prototypes ---------- */

/* */
void init_screen(void);

/* */
void screen_clear(uint8_t);

/* */
void draw_pixel(uint16_t, uint16_t, uint8_t);

#endif /* SCREEN_H */