#ifndef FONT_H
#define FONT_H

#include "utils.h"
#include "screen.h"

void print_char(char c, uint32_t x, uint32_t y, uint8_t color);
void print_string(char *s, uint32_t x, uint32_t y, uint8_t color);


#endif /* FONT_H */