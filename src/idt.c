#include "idt.h"
#include "kernel_ops.h" // TODO remove this, likely won't need it in final file

static struct idt_entry idt_list[256];
static struct idt_pointer idt_ptr;
extern void* isr_stub_table[];
static bool vectors[256];

// Default exception handler (no error code)
void default_excp_handler(registers_t *reg) {
    (void)reg; // Silence compiler warnings
    k_print("DEFAULT EXCEPTION HANDLER - NO ERROR CODE");
}

// Default exception handler (includes error code)
void default_excp_handler_err_code(registers_t *reg, uint32_t error_code) {
    (void)reg; // Silence compiler warnings

    k_print("DEFAULT EXCEPTION HANDLER - ERROR CODE: ");
    k_print_dec(error_code);
}

// Default interrupt handler
void default_int_handler(registers_t *reg) {
    (void)reg; // Silence compiler warnings
    k_print("DEFAULT INTERRUPT HANDLER");
}

void init_idt() {
    idt_ptr.base = (uintptr_t)&idt_list[0];
    idt_ptr.limit = (uint16_t)((sizeof(struct idt_entry) * 256) - 1);

    // Set up exception handlers first (ISRs 0-31)
    for (uint8_t entry = 0; entry < 32; entry++) {
        if (entry == 8  || (entry >= 10 && entry <= 14) || entry == 17 || entry == 21) {
            // Exception takes an error code
            idt_set_descriptor(entry, default_excp_handler_err_code, 0x8F);
        } else {
            // Exception does not take an error code
            idt_set_descriptor(entry, default_excp_handler, 0x8F);
        }
    }
    // Set up regular interrupts (ISRs 32-255)
    for (uint16_t entry = 32; entry < 256; entry++) {
        idt_set_descriptor(entry, default_int_handler, 0x8E);
    }
    __asm__ volatile ("lidt %0" : : "m"(idt_ptr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}

void exception_handler(void) {
    // __asm__ volatile ("cli; hlt"); // Completely hangs the computer
    k_print("Exception called");
    for(;;){}
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    struct idt_entry* descriptor = &idt_list[vector];

    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08;
    descriptor->reserved       = 0;
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
}