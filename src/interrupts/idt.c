#include "idt.h"

struct IDT_Pointer      idt_pt;
struct IDT_Descriptor   idt_descriptor[256];

void idt_init() {

    idt_pt.limit = 256 * (sizeof(struct IDT_Descriptor) - 1);
    idt_pt.base = (uintptr_t) &idt_pt;

    memset(&idt_descriptor[0], 0, sizeof(struct IDT_Descriptor) * 256);

    struct IDT_Pointer *idt = &IDTR;

    asm volatile("LIDT (%0) ": :"p" (idt));
}