#ifndef SCREEN_H
#define SCREEN_H

#include "utils.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)
#define SCREEN_PITCH 320

void screen_swap();
void screen_clear(uint8_t color);
void init_screen();

#endif /* SCREEN_H */