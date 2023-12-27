#ifndef KERNEL_OPS_H
#define KERNEL_OPS_H

#include "utils.h"

#define BLACK_TXT           0x00
#define BLUE_TXT            0x01
#define GREEN_TXT           0x02
#define CYAN_TXT            0x03
#define RED_TXT             0x04
#define MAGENTA_TXT         0x05
#define BROWN_TXT           0x06
#define LIGHT_GRAY_TXT      0x07
#define DARK_GRAY_TXT       0x08
#define LIGHT_BLUE_TXT      0x09
#define LIGHT_GREEN_TXT     0x0A
#define LIGHT_CYAN_TXT      0x0B
#define LIGHT_RED_TXT       0x0C
#define LIGHT_MAGENTA_TXT   0x0D
#define YELLOW_TXT          0x0E
#define WHITE_TXT           0x0F

#define BLANK   (0x20 | ((0 << 4) | (15 & 0x0F) << 8))

/* */
void move_cursor(void);
/* */
void scroll(void);

/* */
void k_put_c(char c);

/* */
void k_clear(void);

/* */
void k_print(const char *);

/* */
void k_print_hex(uint32_t);

/* */
void k_print_dec(uint32_t);

/* */
void k_panic(const char *, bool);

#endif /* KERNEL_OPS_H */