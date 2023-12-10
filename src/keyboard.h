#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "utils.h"
#include "idt.h"
#include "pic.h"

#define PS2_DATA_PORT   0x60

#define KEY_ENTER       '\n'
#define KEY_ESC         0x01
#define KEY_OEM6        0x0D
#define KEY_OEM1        0x1B
#define KEY_BACKSPACE   0x0E
#define KEY_TAB         0x0F
#define KEY_LCTRL       0x1D
#define KEY_OEM3        0x27
#define KEY_OEM7        0x28
#define KEY_LSHIFT      0x2A
#define KEY_R_SHIFT     0x37
#define KEY_L_ALT       0x38
#define KEY_F6          0x40
#define KEY_F7          0x41
#define KEY_F8          0x42
#define KEY_F9          0x43
#define KEY_F10         0x44
#define KEY_NUM_LOCK    0x45
#define KEY_SCROLL_LOCK 0x46
#define KEY_PRT_SC      0x54
#define KEY_F11         0x57
#define KEY_F12         0x58


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