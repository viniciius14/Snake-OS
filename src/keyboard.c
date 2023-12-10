#include "keyboard.h"


// uint8_t keyboard_layout_us[] = {
//     KEY_NULL, KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
//     '-', '=', KEY_BACKSPACE, KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u',
//     'i', 'o', 'p', '[', ']', KEY_ENTER, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j',
//     'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
//     ',', '.', '/', 0, 0, 0, ' ', 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5,
//     KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, KEY_HOME, KEY_UP,
//     KEY_PAGE_UP, '-', KEY_LEFT, '5', KEY_RIGHT, '+', KEY_END, KEY_DOWN,
//     KEY_PAGE_DOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, KEY_F11, KEY_F12
// };

void init_keyboard(void) {
    idt_set_descriptor(33, keyboard_handler, INT_GATE_FLAGS);

    /* Clear out keyboard buffer */
    while(inb(0x64) & 1) inb(0x60);

    clear_irq_mask(1);
}

void keyboard_handler(int_frame_32_t *frame) {
    (void)frame;
    /* Get value being sent to port */
    uint8_t key = inb(0x60);

    /* Convert value to corresponding keyboard key */
    k_print((char *)&key);
    send_pic_eoi(1);
}


// uint8_t get_key(void) {
// }
