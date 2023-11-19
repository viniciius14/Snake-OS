#ifndef INTERRUTPS_H
#define INTERRUPTS_H

#include "utils.h"

/* A struct describing an interrupt gate */
struct IDT_Entry {
    uint16_t    offset_low;     /* The address of the ISR, split between 2 fields*/
    uint16_t    selector;       /* Code selector that the ISR will use */
    uint8_t     __ignored;
    uint8_t     flags;          /* includes Type, DPL and Present */
    uint16_t    offset_high;    /* DPL -> Descriptor Privilege Level*/
} PACKED;

/* IDT Pointer */
struct IDT_Pointer {
    uint16_t    limit;      /* length of the IDT in bytes */
    uintptr_t   base;       /* address for the start of the IDT */
} PACKED;

struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, error_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

void interrupts_init(void);

void idt_init(void);

void toggle_interrupts(bool opt);

void idt_set_handler(uint8_t isr_num, uint32_t handler, uint16_t selector, uint8_t flags);

void std_isr_handler(struct registers reg);

extern void idt_flush(uint32_t addr);

// These extern directives let us access the addresses of our ASM ISR handlers.
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif /* INTERRUPTS_H */