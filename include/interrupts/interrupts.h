#ifndef INTERRUTPS_H
#define INTERRUPTS_H

#include "utils/types.h"
#include "utils/types.h"
#include "utils/macros.h"

/* IDT Descriptor Format */
struct IDT_Descriptor {
    uint16_t    offset_low;     /* The address of the ISR, split between 2 fields*/
    uint16_t    selector;       /* Code selector that the ISR will use */
    uint8_t     __ignored;
    uint8_t     type;           /* includes Type, DPL and Present */
    uint16_t    offset_high;    /* DPL -> Descriptor Privilege Level*/
} PACKED;

/* IDT Pointer */
struct IDT_Pointer {
    uint16_t    limit;      /* length of the IDT in bytes */
    uintptr_t   base;       /* address for the start of the IDT */
} PACKED;

void interrupts_init(void);

void load_IDT(void);
void add_int(int number, void(*handler_f)());

void load_exceptions(void);

/* enables/disables software interrupts */
void interrupts(bool opt);

/* These are all assembly functions in interrupts.asm */
extern void int00(void);
extern void int01(void);
extern void int02(void);
extern void int03(void);
extern void int04(void);
extern void int05(void);
extern void int06(void);
extern void int07(void);
extern void int08(void);
extern void int09(void);
extern void int10(void);
extern void int11(void);
extern void int12(void);
extern void int13(void);
extern void int14(void);
extern void int15(void);
extern void int16(void);
extern void int17(void);
extern void int18(void);
extern void int19(void);
extern void int32(void);

#endif /* INTERRUPTS_H */