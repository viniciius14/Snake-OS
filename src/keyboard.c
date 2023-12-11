#include "keyboard.h"
/*
uint8_t keyboard_layout_pt[] = {
    0, KEY_ESC,
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', KEY_OEM6, KEY_BACKSPACE,
    KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '+', KEY_OEM1, KEY_ENTER,
    KEY_LCTRL, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', KEY_OEM3, KEY_OEM7, '~',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', KEY_R_SHIFT,
    '*', KEY_L_ALT, ' ', KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_NUM_LOCK,
    KEY_SCROLL_LOCK, '7','8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
    KEY_PRT_SC, 0, '<', KEY_F11, KEY_F12
};
*/
void init_keyboard(void) {
    idt_set_descriptor(33, keyboard_handler, INT_GATE_FLAGS);
    /* Clear out keyboard buffer */
    while(inb(0x64) & 1) {
        inb(0x60);
    }
    clear_irq_mask(1);
}

void keyboard_handler(int_frame_32_t *frame) {
    (void)frame;
    /* Get value being sent to port */
    uint8_t key = inb(0x60);
    k_print_hex(key);
    /* Convert value to corresponding keyboard key */
    //key = keyboard_layout_pt[key];
    //k_print((char *)&key);
    send_pic_eoi(1);
}
