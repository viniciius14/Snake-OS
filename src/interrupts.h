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
extern void isr0 (void);
extern void isr1 (void);
extern void isr2 (void);
extern void isr3 (void);
extern void isr4 (void);
extern void isr5 (void);
extern void isr6 (void);
extern void isr7 (void);
extern void isr8 (void);
extern void isr9 (void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

#endif /* INTERRUPTS_H */