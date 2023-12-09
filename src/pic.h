#ifndef PIC_H
#define PIC_H

#include "utils.h"

#define PIC_1_CMD   0x20
#define PIC_1_DATA  0x21

#define PIC_2_CMD   0xA0
#define PIC_2_DATA  0xA1

#define NEW_IRQ_0   0x20 /* IRQ 0 - 7 will be mapped to interrupts 32 - 39 */
#define NEW_IRQ_8   0x28 /* IRQ 8 - 15 will be mapped to interrupts 40 - 47 */

#define PIC_EOI     0x20

/* Send end of interrupt command to signal IQR has been handled */
void send_pic_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC_2_CMD, PIC_EOI);
    }
    outb(PIC_1_CMD, PIC_EOI);
}

/* Disable PIC */
void disable_pic(void) {
    outb(PIC_2_DATA, 0xFF);
    outb(PIC_1_DATA, 0xFF);
}

/* Set IRQ mask by setting the bit in the IMR (interrupt mask register) */
void set_irq_mask(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC_1_DATA;
    } else {
        irq -= 8;
        port = PIC_2_DATA;
    }
    value = inb(port) | (1 << irq);
    outb(port, value);
}


/* Clear IRQ mask by clearing the bit in the IMR (interrupt mask register) */
void clear_irq_mask(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC_1_DATA;
    } else {
        irq -= 8;
        port = PIC_2_DATA;
    }
    value = inb(port) & ~(1 << irq);
    outb(port, value);
}


/* Remap PIC to user interrupts above first 15, to not interface withe xceptions (ISRs 0-31) */
void remap_pic(void) {
    uint8_t pic_1_mask, pic_2_mask;

    /* Save current masks */
    pic_1_mask = inb(PIC_1_DATA);
    pic_2_mask = inb(PIC_2_DATA);

    /* ICW 1 (Initialization control word) - bit 0 = send uo to ICW 4, bit 4 = initialize PIC */
    outb(PIC_1_CMD, 0x11);
    io_wait();
    outb(PIC_2_CMD, 0x11);
    io_wait();

    /* ICW 2 - Where to map the base interrupt in the IDT */
    outb(PIC_1_DATA, NEW_IRQ_0);
    io_wait();
    outb(PIC_2_DATA, NEW_IRQ_8);
    io_wait();

    /* ICW 3 - Where to map PIC2 ot the IRQ line in PIC1; MApping PIC2 to IRQ 2*/
    outb(PIC_1_CMD, 0x04);
    io_wait();
    outb(PIC_2_CMD, 0x02);
    io_wait();

    /* ICW 4 - Set x86 mode */
    outb(PIC_1_CMD, 0x01);
    io_wait();
    outb(PIC_2_CMD, 0x01);
    io_wait();

    /* Write initial masks */
    outb(PIC_1_DATA, pic_1_mask);
    outb(PIC_2_DATA, pic_2_mask);
}





#endif