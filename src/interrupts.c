#include "interrupts.h"
#include "kernel_ops.h"
#include "pic.h"

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;
isr_t interrupt_handlers[256];

void init_idt(void) {
    idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_ptr.base  = (uintptr_t)&idt_entries[0];

    memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    // // Remap the irq table.
    // outportb(0x20, 0x11);
    // outportb(0xA0, 0x11);
    // outportb(0x21, 0x20);
    // outportb(0xA1, 0x28);
    // outportb(0x21, 0x04);
    // outportb(0xA1, 0x02);
    // outportb(0x21, 0x01);
    // outportb(0xA1, 0x01);
    // outportb(0x21, 0x00);
    // outportb(0xA1, 0x00);

    // idt_set_gate(0,  (uint32_t)isr0,  0x08, 0x8E);
    // idt_set_gate(1,  (uint32_t)isr1,  0x08, 0x8E);
    // idt_set_gate(2,  (uint32_t)isr2,  0x08, 0x8E);
    // idt_set_gate(3,  (uint32_t)isr3,  0x08, 0x8E);
    // idt_set_gate(4,  (uint32_t)isr4,  0x08, 0x8E);
    // idt_set_gate(5,  (uint32_t)isr5,  0x08, 0x8E);
    // idt_set_gate(6,  (uint32_t)isr6,  0x08, 0x8E);
    // idt_set_gate(7,  (uint32_t)isr7,  0x08, 0x8E);
    // idt_set_gate(8,  (uint32_t)isr8,  0x08, 0x8E);
    // idt_set_gate(9,  (uint32_t)isr9,  0x08, 0x8E);
    // idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    // idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    // idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    // idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    // idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    // idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    // idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    // idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    // idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    // idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    // idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    // idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    // idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    // idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    // idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    // idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    // idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    // idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    // idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    // idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    // idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    // idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
    // idt_set_gate(32, (uint32_t)irq0,  0x08, 0x8E);
    // idt_set_gate(33, (uint32_t)irq1,  0x08, 0x8E);
    // idt_set_gate(34, (uint32_t)irq2,  0x08, 0x8E);
    // idt_set_gate(35, (uint32_t)irq3,  0x08, 0x8E);
    // idt_set_gate(36, (uint32_t)irq4,  0x08, 0x8E);
    // idt_set_gate(37, (uint32_t)irq5,  0x08, 0x8E);
    // idt_set_gate(38, (uint32_t)irq6,  0x08, 0x8E);
    // idt_set_gate(39, (uint32_t)irq7,  0x08, 0x8E);
    // idt_set_gate(40, (uint32_t)irq8,  0x08, 0x8E);
    // idt_set_gate(41, (uint32_t)irq9,  0x08, 0x8E);
    // idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
    // idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
    // idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
    // idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
    // idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
    // idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);

    idt_load((uintptr_t)&idt_ptr);

    // memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_lo = (uint16_t)(base & 0xFFFF);
    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags   = flags;
    idt_entries[num].base_hi = (uint16_t)((base >> 16) & 0xFFFF);
}

// static void irq_set_mask(size_t i) {
//     u16 port = i < 8 ? PIC1_DATA : PIC2_DATA;
//     u8 value = inportb(port) | (1 << i);
//     outportb(port, value);
// }

static void irq_clear_mask(size_t i) {
    uint16_t port = i < 8 ? (0x20 + 1) : (0xA0 + 1);
    uint8_t value = inportb(port) & ~(1 << i);
    outportb(port, value);
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
    __asm__ volatile ("cli");
    interrupt_handlers[n] = handler;
    irq_clear_mask(n);
    __asm__ volatile ("cli");

    // irq_clear_mask(n);
    // unmaskIRQ(n);
    // asm("sti");
}

void isr_handler(registers_t regs) {
    k_print("recieved interrupt: ");
    k_print_dec(regs.int_no);
    k_print(" \n");

    if(interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

void irq_handler(registers_t regs) {

    if (regs.int_no >= 40) {
        // Send reset signal to slave.
        outportb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outportb(0x20, 0x20);

    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}