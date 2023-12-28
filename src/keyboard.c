#include "keyboard.h"

uint8_t key;

uint8_t keyboard_layout_pt[58] = {
    KEY_NULL, KEY_NULL, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    KEY_NULL, KEY_NULL, KEY_BACKSPACE, KEY_TAB,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    KEY_NULL, KEY_NULL, '\n', KEY_NULL,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL,
    'z', 'x', 'c', 'v', 'b', 'n', 'm',
    KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL,
    ' '
};

void init_keyboard(void) {
    idt_set_descriptor(33, keyboard_handler, INT_GATE_FLAGS);

    /* Clear out keyboard buffer */
    while (inb(0x64) & 1) {
        inb(0x60);
    }
    clear_irq_mask(1);
}

void keyboard_handler(struct interrupt_frame *frame) {
    (void)frame;

    /* Get scan code that was sent to the port */
    uint8_t temp_key = inb(PS2_DATA_PORT);

    /* Check if it's not a key release */
    if (!(temp_key & 0x80)) {
        /* Convert value to corresponding keyboard key */
        key = temp_key > 0x39 ? keyboard_layout_pt[0] : keyboard_layout_pt[temp_key];
    }

    send_pic_eoi(1);
}