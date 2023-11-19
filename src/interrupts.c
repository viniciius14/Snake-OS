#include "interrupts.h"
#include "kernel_ops.h"
#include "utils.h"

struct IDT_Pointer      idt_pointer;
struct IDT_Entry        idt_list[256] = {0};

void interrupts_init(void) {
    /* Disable interrupts */
    // toggle_interrupts(false);
    k_print("Aoggled interrupts\n", WHITE_TXT);
    // idt_init();
    // k_print("Finished idt_init()\n", WHITE_TXT);

    /* Enable interrupts */
    // toggle_interrupts(true);
}

void idt_init() {
    idt_pointer.limit = sizeof(struct IDT_Entry) * 256 - 1;
    idt_pointer.base = (uintptr_t) &idt_list;

    memset(&idt_list, 0, sizeof(struct IDT_Entry) * 256);
    k_print("Sucess memset\n", WHITE_TXT);

    idt_set_handler( 0, (uint32_t)isr0 , 0x08, 0x8E);
    idt_set_handler( 1, (uint32_t)isr1 , 0x08, 0x8E);
    idt_set_handler( 2, (uint32_t)isr2 , 0x08, 0x8E);
    idt_set_handler( 3, (uint32_t)isr3 , 0x08, 0x8E);
    idt_set_handler( 4, (uint32_t)isr4 , 0x08, 0x8E);
    idt_set_handler( 5, (uint32_t)isr5 , 0x08, 0x8E);
    idt_set_handler( 6, (uint32_t)isr6 , 0x08, 0x8E);
    idt_set_handler( 7, (uint32_t)isr7 , 0x08, 0x8E);
    idt_set_handler( 8, (uint32_t)isr8 , 0x08, 0x8E);
    idt_set_handler( 9, (uint32_t)isr9 , 0x08, 0x8E);
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

    k_print("idt_set_handlers\n", WHITE_TXT);

    idt_flush((uint32_t)&idt_pointer);
    k_print("idt_flush\n", WHITE_TXT);
}

void toggle_interrupts(bool opt) {
    if(opt == true) {
        __asm__ volatile("sti");
    } else {
        __asm__ volatile("cli");
    }
}

void idt_set_handler(uint8_t isr_num, uint32_t handler, uint16_t selector, uint8_t flags) {
    idt_list[isr_num].offset_low  = (handler >> 0 ) & 0xFFFF;
    idt_list[isr_num].offset_high = (handler >> 16) & 0xFFFF;

    idt_list[isr_num].selector = selector;
    idt_list[isr_num].flags = flags;
}

void std_isr_handler(struct registers reg) {
    k_print("recieved interrupt: who cares", WHITE_TXT);
}
