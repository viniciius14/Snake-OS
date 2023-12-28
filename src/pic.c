#include "pic.h"

void send_pic_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC_2_CMD, PIC_EOI);
    }
    outb(PIC_1_CMD, PIC_EOI);
}

void disable_pic(void) {
    outb(PIC_2_DATA, 0xFF);
    outb(PIC_1_DATA, 0xFF);
}

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

    /* ICW 3 - Where to map PIC2 ot the IRQ line in PIC1; Mapping PIC2 to IRQ 2*/
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

    STI();
}