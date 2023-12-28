#include "idt.h"

struct IDT_Entry idt32[256];
struct IDT_Ptr idt_pt;

void excp_handler(struct interrupt_frame *frame) {
    (void)frame;
    k_print("excp_handler was called\n");
}

void excp_handler_err(struct interrupt_frame *frame, uint32_t error_code) {
    (void)frame;
    k_print("excp_handler_err was called with error code: ");
    k_print_dec(error_code);
    k_print(" \n");
}

void intr_handler(struct interrupt_frame *frame) {
    (void)frame;
    k_print("intr_handler was called!\n");
}

void idt_set_descriptor(uint8_t entry_number, void *isr, uint8_t flags) {
    struct IDT_Entry *descriptor = &idt32[entry_number];

    descriptor->isr_low    = ((uint32_t)isr >>  0) & 0xFFFF;
    descriptor->kernel_cs  = 0x08;
    descriptor->reserved   = 0;
    descriptor->attributes = flags;
    descriptor->isr_high   = ((uint32_t)isr >> 16) & 0xFFFF;
}

void init_idt(void) {
    idt_pt.limit = (uint16_t)((sizeof(struct IDT_Entry) * 256) - 1);
    idt_pt.base  = (uintptr_t)&idt32[0];

    /* Setup exception handler ISR 0 - 31 */
    for (uint8_t entry = 0 ; entry < 32 ; entry++) {
        if (entry == 8 || (entry >= 10 && entry <= 14)|| entry == 17 || entry == 21) {
            /* Exceptions with error codes */
            idt_set_descriptor(entry, excp_handler_err, TRAP_GATE_FLAGS);
        } else {
            /* Exceptions without error codes */
            idt_set_descriptor(entry, excp_handler, INT_GATE_FLAGS);
        }
    }

    /* Setup all other interrupts ISRs 32 - 255 */
    for (uint16_t entry = 32 ; entry < 256 ; entry++) {
        idt_set_descriptor(entry, intr_handler, INT_GATE_FLAGS);
    }

    ASM ("lidt %0" : : "memory"(idt_pt));
}