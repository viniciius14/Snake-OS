#ifndef IDT_H
#define IDT_H

#include "types.h"

/* IDT Descriptor Format */
struct IDT_Descriptor {
    uint16_t    offset_low;     /* The address of the ISR, split between 2 fields*/
    uint16_t    selector;       /* Code selector that the ISR will use */
    uint8_t     __ignored;
    uint8_t     type;           /* includes Type, DPL and Present */
    uint16_t    offset_high;    /* DPL -> Descriptor Privilege Level*/
}PACKED;

/* IDT Pointer */
struct IDT_Pointer {
    uint16_t    limit;      /* length of the IDT in bytes */
    uintptr_t   base;       /* address for the start of the IDT */
}PACKED;


void idt_init(void);
void add_int(int number, void(*handler_f)(), uint32_t dpl);

#endif /* IDT_H */