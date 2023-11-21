#include "interrupts.h"
#include "kernel_ops.h"
#include "utils.h"
#include "pic.h"

struct IDT_Pointer      idt_pointer;
struct IDT_Entry        idt_list[256] = {0};
isr_t interrupt_handlers[256];

void interrupts_init(void) {
    idt_init();

    memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
}

void idt_init(void) {
    idt_pointer.limit = sizeof(struct IDT_Entry) * 256 - 1;
    idt_pointer.base = (uintptr_t) &idt_list;

    memset(&idt_list, 0, sizeof(struct IDT_Entry) * 256);

    // Remap the irq table.
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);

    idt_set_handler(0,  (uint32_t)isr0,  0x08, 0x8E);
    idt_set_handler(1,  (uint32_t)isr1,  0x08, 0x8E);
    idt_set_handler(2,  (uint32_t)isr2,  0x08, 0x8E);
    idt_set_handler(3,  (uint32_t)isr3,  0x08, 0x8E);
    idt_set_handler(4,  (uint32_t)isr4,  0x08, 0x8E);
    idt_set_handler(5,  (uint32_t)isr5,  0x08, 0x8E);
    idt_set_handler(6,  (uint32_t)isr6,  0x08, 0x8E);
    idt_set_handler(7,  (uint32_t)isr7,  0x08, 0x8E);
    idt_set_handler(8,  (uint32_t)isr8,  0x08, 0x8E);
    idt_set_handler(9,  (uint32_t)isr9,  0x08, 0x8E);
    idt_set_handler(10, (uint32_t)isr10, 0x08, 0x8E);
    idt_set_handler(11, (uint32_t)isr11, 0x08, 0x8E);
    idt_set_handler(12, (uint32_t)isr12, 0x08, 0x8E);
    idt_set_handler(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_set_handler(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_set_handler(15, (uint32_t)isr15, 0x08, 0x8E);
    idt_set_handler(16, (uint32_t)isr16, 0x08, 0x8E);
    idt_set_handler(17, (uint32_t)isr17, 0x08, 0x8E);
    idt_set_handler(18, (uint32_t)isr18, 0x08, 0x8E);
    idt_set_handler(19, (uint32_t)isr19, 0x08, 0x8E);
    idt_set_handler(20, (uint32_t)isr20, 0x08, 0x8E);
    idt_set_handler(21, (uint32_t)isr21, 0x08, 0x8E);
    idt_set_handler(22, (uint32_t)isr22, 0x08, 0x8E);
    idt_set_handler(23, (uint32_t)isr23, 0x08, 0x8E);
    idt_set_handler(24, (uint32_t)isr24, 0x08, 0x8E);
    idt_set_handler(25, (uint32_t)isr25, 0x08, 0x8E);
    idt_set_handler(26, (uint32_t)isr26, 0x08, 0x8E);
    idt_set_handler(27, (uint32_t)isr27, 0x08, 0x8E);
    idt_set_handler(28, (uint32_t)isr28, 0x08, 0x8E);
    idt_set_handler(29, (uint32_t)isr29, 0x08, 0x8E);
    idt_set_handler(30, (uint32_t)isr30, 0x08, 0x8E);
    idt_set_handler(31, (uint32_t)isr31, 0x08, 0x8E);
    idt_set_handler(32, (uint32_t)irq0,  0x08, 0x8E);
    idt_set_handler(33, (uint32_t)irq1,  0x08, 0x8E);
    idt_set_handler(34, (uint32_t)irq2,  0x08, 0x8E);
    idt_set_handler(35, (uint32_t)irq3,  0x08, 0x8E);
    idt_set_handler(36, (uint32_t)irq4,  0x08, 0x8E);
    idt_set_handler(37, (uint32_t)irq5,  0x08, 0x8E);
    idt_set_handler(38, (uint32_t)irq6,  0x08, 0x8E);
    idt_set_handler(39, (uint32_t)irq7,  0x08, 0x8E);
    idt_set_handler(40, (uint32_t)irq8,  0x08, 0x8E);
    idt_set_handler(41, (uint32_t)irq9,  0x08, 0x8E);
    idt_set_handler(42, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_handler(43, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_handler(44, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_handler(45, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_handler(46, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_handler(47, (uint32_t)irq15, 0x08, 0x8E);

    idt_flush((uint32_t)&idt_pointer);
}

void toggle_interrupts(bool opt) {
    if(opt == true) {
        __asm__ volatile("sti");
    } else {
        __asm__ volatile("cli");
    }
}

void idt_set_handler(uint8_t isr_num, uint32_t handler, uint16_t selector, uint8_t flags) {
    idt_list[isr_num].offset_low  = (uint16_t)(handler >> 0 ) & 0xFFFF;
    idt_list[isr_num].offset_high = (uint16_t)(handler >> 16) & 0xFFFF;
    idt_list[isr_num].__ignored = 0;
    idt_list[isr_num].selector = selector;
    idt_list[isr_num].flags = flags;
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs) {
    // k_print("recieved interrupt: \n", WHITE_TXT);
    // k_print_dec(regs.int_no);
    // monitor_put('\n');

    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}


// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs) {
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
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

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}