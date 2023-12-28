#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "utils.h"
#include "idt.h"
#include "pic.h"

/* ---------------- Defines ---------------- */

#define PS2_DATA_PORT   0x60

#define KEY_NULL        0x00
#define KEY_ENTER       '\n'
#define KEY_BACKSPACE   0x08
#define KEY_TAB         0x09

/* ---------- Function prototypes ---------- */

/* Initializes the interrupt for the keyboard and clears it's buffer */
void init_keyboard(void);

/* PIC IRQ1 interrupt handler */
INTERRUPT void keyboard_handler(struct interrupt_frame *frame);

#endif /* KEYBOARD_H */
