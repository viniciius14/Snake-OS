#include "keyboard.h"

uint16_t last_key = 0;

void init_keyboard(void) {
    idt_set_descriptor(33, keyboard_handler, INT_GATE_FLAGS);
    clear_irq_mask(1);
}

void keyboard_handler(int_frame_32_t *frame) {
    uint16_t scancode = (uint16_t)inb(0x60);
    if ((scancode & 0x80) == 0x80) {
        /* Release */
        k_print("Released");
    } else {
        /* Press */
        k_print("Pressed");
        k_print((char)scancode);
    }
    send_pic_eoi(1);
}