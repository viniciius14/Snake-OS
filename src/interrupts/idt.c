#include "interrupts.h"

struct IDT_Pointer      idt_pointer;
struct IDT_Descriptor   idt_list[256];

void idt_init() {
    idt_pointer.limit = 256 * sizeof(struct IDT_Descriptor) - 1;
    idt_pointer.base = (uintptr_t) &idt_pointer;

    memset(&idt_list[0], 0, sizeof(struct IDT_Descriptor) * 256);

    struct IDT_Pointer *idt = &idt_pointer;

    asm volatile("lidt (%0) ": :"p" (idt));
}

/* set descriptor number'th elements settings' to dpl and to be handled by handler_f */
void add_int(int number, void(*handler_f)(), uint32_t dpl) {
    uint16_t selector = 0x08;
    uint16_t settings = 0;
    uint32_t offset = (uintptr_t)handler_f;

    /* get CS selector */
    asm volatile("movw %%cs,%0" :"=g"(selector));

    switch(dpl) {
        case 0:
            settings = 0x8E00;  /* 1000111000000000 = present, ring0, int_gate */
            break;
        default:
            settings = 0xEE00;  /* 1110111000000000 = present, ring3, int_gate */
            break;
    }

    idt_list[number].offset_low     = (offset & 0xFFFF);
    idt_list[number].selector       = selector;
    idt_list[number].__ignored      = 0;
    idt_list[number].type           = (settings >> 8);
    idt_list[number].offset_high    = (offset >> 16);
}