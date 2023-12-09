#ifndef IDT_H
#define IDT_H

#include "utils.h"

#define TRAP_GATE_FLAGS 0x8F
#define INT_GATE_FLAGS  0x8E


typedef struct {
    uint16_t isr_address_low;
    uint16_t kernel_cs;
    uint8_t  reserved;
    uint8_t attributes;
    uint16_t isr_address_high;
} PACKED idt_entry_32_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} PACKED idtr_32_t;

idt_entry_32_t idt32[256];
idtr_32_t idtr32;

/* Interrupt frame to pass to interrupt handlers */
typedef struct {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t sp;
    uint32_t ss;
} PACKED int_frame_32_t;


/* Default exception handler with no error code */
INTERRUPT void default_excp_handler(int_frame_32_t *int_frame_32) {
    k_print("default_excp_handler was called");
}


/* Default exception handler with error code */
INTERRUPT void default_excp_handler_err_code(int_frame_32_t *int_frame_32, uint32_t error_code) {
    k_print("default_excp_handler was called with error code: ");
    k_print_dec(error_code);

}

/* Default interrupt hadnler */
INTERRUPT void default_int_handler(int_frame_32_t *int_frame_32) {
    k_print("default_excp_handler was called with error code: ");
}

/* Add an ISR to the IDT */
void set_idt_descriptor_32(uint8_t entry_number, void *isr, uint8_t flags) {
    idt_entry_32_t *descriptor = &idt32[entry_number];

    descriptor->isr_address_low  = ((uint32_t)isr >>  0) & 0xFFFF;
    descriptor->kernel_cs        = 0x08;
    descriptor->reserved         = 0;
    descriptor->attributes       = flags;
    descriptor->isr_address_high = ((uint32_t)isr >> 16) & 0xFFFF;
}

/* Setup IDT */
void init_idt_32(void) {
    idtr32.limit = (uint16_t)((sizeof(idt_entry_32_t) * 256)); // TODO do we need to remvoe the -1?
    idtr32.base  = (uintptr_t)&idt32[0];

    /* Setup exception handler ISR 0 - 31 */
    for (uint8_t entry = 0 ; entry < 32 ; entry++) {
        if(entry == 8 || (entry >= 10 && entry <= 14)|| entry == 17 || entry == 21){
            /* Exceptions with error codes */
            set_idt_descriptor_32(entry, default_excp_handler_err_code, TRAP_GATE_FLAGS);
        } else {
            /* Exceptions without error codes */
            set_idt_descriptor_32(entry, default_excp_handler, INT_GATE_FLAGS);
        }
    }

    /* Setup all other interrupts ISR 32 - 255 */
    for (uint16_t entry = 32 ; entry < 256 ; entry++) {
        set_idt_descriptor_32(entry, default_int_handler, INT_GATE_FLAGS);
    }

    __asm__ __volatile__ ("lidt %0" : : "memory"(idtr32));
}




#endif /* IDT_H */