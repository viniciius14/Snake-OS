#ifndef IDT_H
#define IDT_H

#include "utils.h"
#include "kernel_ops.h"

/* ---------------- Defines ---------------- */

#define TRAP_GATE_FLAGS     0x8F
#define INT_GATE_FLAGS      0x8E

/* ----------------- Types ----------------- */

/* Entry for the IDT (Interrupt Descriptor Table) */
struct IDT_Entry {
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t  reserved;
    uint8_t  attributes;
    uint16_t isr_high;
} PACKED;

/* IDT pointer to be passed into lidt instruction */
struct IDT_Ptr {
    uint16_t limit;
    uint32_t base;
} PACKED;

/* Interrupt frame to pass to interrupt handlers */
struct interrupt_frame {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t sp;
    uint32_t ss;
} PACKED;

/* ---------- Function prototypes ---------- */

/* Default handler that is triggered when an exception without an error code occurs */
INTERRUPT void excp_handler(struct interrupt_frame *);

/* Default handler that is triggered when an exception with an error code occurs  */
INTERRUPT void excp_handler_err(struct interrupt_frame *, uint32_t);

/* Default handler that is triggered when an interrupt occurs */
INTERRUPT void intr_handler(struct interrupt_frame *);

/* Add an ISR to the IDT */
void idt_set_descriptor(uint8_t, void *, uint8_t);

/* Initializes the interrupt descriptor table */
void init_idt(void);

#endif /* IDT_H */