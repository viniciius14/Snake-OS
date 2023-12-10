#include "idt.h"

idt_entry_32_t idt32[256];
idtr_32_t idtr32;

/* Default exception handler with no error code */
void default_excp_handler(int_frame_32_t *int_frame_32) {
    k_print("default_excp_handler was called");
}


/* Default exception handler with error code */
void default_excp_handler_err_code(int_frame_32_t *int_frame_32, uint32_t error_code) {
    k_print("default_excp_handler_err_code was called with error code: ");
    k_print_dec(error_code);

}

/* Default interrupt hadnler */
void default_int_handler(int_frame_32_t *int_frame_32) {
    k_print("default_int_handler was called! ");
}

/* Add an ISR to the IDT */
void idt_set_descriptor(uint8_t entry_number, void *isr, uint8_t flags) {
    idt_entry_32_t *descriptor = &idt32[entry_number];

    descriptor->isr_low    = ((uint32_t)isr >>  0) & 0xFFFF;
    descriptor->kernel_cs  = 0x08;
    descriptor->reserved   = 0;
    descriptor->attributes = flags;
    descriptor->isr_high   = ((uint32_t)isr >> 16) & 0xFFFF;
}

/* Setup IDT */
void init_idt(void) {
    idtr32.limit = (uint16_t)((sizeof(idt_entry_32_t) * 256) - 1);
    idtr32.base  = (uintptr_t)&idt32[0];

    /* Setup exception handler ISR 0 - 31 */
    for (uint8_t entry = 0 ; entry < 32 ; entry++) {
        if (entry == 8 || (entry >= 10 && entry <= 14)|| entry == 17 || entry == 21) {
            /* Exceptions with error codes */
            idt_set_descriptor(entry, default_excp_handler_err_code, TRAP_GATE_FLAGS);
        } else {
            /* Exceptions without error codes */
            idt_set_descriptor(entry, default_excp_handler, INT_GATE_FLAGS);
        }
    }

    /* Setup all other interrupts ISR 32 - 255 */
    for (uint16_t entry = 32 ; entry < 256 ; entry++) {
        idt_set_descriptor(entry, default_int_handler, INT_GATE_FLAGS);
    }

    __asm__ __volatile__ ("lidt %0" : : "memory"(idtr32));
}


