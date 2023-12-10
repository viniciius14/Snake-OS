#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "utils.h"
#include "idt.h"
#include "pic.h"

#define PS2_DATA_PORT   0x60

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