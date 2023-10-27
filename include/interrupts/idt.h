#ifndef IDT_H
#define IDT_H

#include "types.h"


/* IDT Descriptor Format */
struct IDT_Descriptor {
    uint16_t    offset_low;
    uint16_t    selector;
    uint8_t     __ignored;
    uint8_t     type;       /* includes Type, DPL and Present */
    uint16_t    offset_high;
}PACKED;

/* IDT Pointer */
struct IDT_Pointer {
    uint16_t    limit;      /* length of the IDT in bytes */
    uintptr_t   base;       /* address for the start of the IDT */
}PACKED;


#endif /* IDT_H */