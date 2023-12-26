#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "utils.h"
#include "idt.h"
#include "pic.h"

#define PS2_DATA_PORT   0x60

#define KEY_NULL        0xFF
#define KEY_ENTER       '\n'
#define KEY_BACKSPACE   0x08
#define KEY_TAB         0x09

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

typedef struct {
    uint8_t key;
    bool    shift;
    bool    ctrl;
} PACKED key_info_t;



void init_keyboard(void);

/* PIC IRQ1 interrupt handler */
INTERRUPT void keyboard_handler(int_frame_32_t *frame);


uint8_t get_key(void);

#endif /* KEYBOARD_H */
