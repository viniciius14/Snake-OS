#ifndef FONT_H
#define FONT_H

#include "utils.h"
#include "screen.h"


/* */
void print_char(char, uint32_t, uint32_t, uint8_t);

/* */
void print_string(char *, uint32_t, uint32_t, uint8_t);

/* */
void int_to_string(uint16_t, char*);


#endif /* FONT_H */