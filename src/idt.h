#ifndef IDT_H
#define IDT_H

#include "utils.h"
#include "kernel_ops.h"

#define TRAP_GATE_FLAGS 0x8F
#define INT_GATE_FLAGS  0x8E

/* Entry for the IDT (Interrupt Descriptor Table) */
typedef struct {
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t  reserved;
    uint8_t  attributes;
    uint16_t isr_high;
} PACKED idt_entry_32_t;

/* IDT pointer to be passed into lidt instruction */
typedef struct {
    uint16_t limit;
    uint32_t base;
} PACKED idtr_32_t;

/* Interrupt frame to pass to interrupt handlers */
typedef struct {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t sp;
    uint32_t ss;
} PACKED int_frame_32_t;


INTERRUPT void default_excp_handler(int_frame_32_t *int_frame_32);

INTERRUPT void default_excp_handler_err_code(int_frame_32_t *int_frame_32, uint32_t error_code);

INTERRUPT void default_int_handler(int_frame_32_t *int_frame_32);

void idt_set_descriptor(uint8_t entry_number, void *isr, uint8_t flags);

void init_idt(void);


#endif /* IDT_H */