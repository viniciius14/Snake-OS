#ifndef IDT_H
#define IDT_H

#include "utils.h"

struct idt_entry {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} PACKED;

struct idt_pointer {
	uint16_t	limit;
	uint32_t	base;
} PACKED;

typedef struct registers {
    uint32_t ds;                  // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

void init_idt(void);
void exception_handler(void);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

#endif /* IDT_H */