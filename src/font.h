#ifndef FONT_H
#define FONT_H

#include "utils.h"
#include "screen.h"

/* ---------- Function prototypes ---------- */

/* Prints input character to x and y position according to our font_table */
void print_char(char, uint16_t, uint16_t, uint8_t);

/* Calls print_char for every element of given string */
void print_string(char *, uint16_t, uint16_t, uint8_t);

/* Convert an unsigned integer into a printable string */
void int_to_string(uint16_t, char*);

#endif /* FONT_H */