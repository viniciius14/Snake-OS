#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "utils.h"
#include "idt.h"
#include "pic.h"


void init_keyboard(void);

/* PIC IRQ1 interrupt handler */
void keyboard_handler(int_frame_32_t *frame);



#endif /* KEYBOARD_H */