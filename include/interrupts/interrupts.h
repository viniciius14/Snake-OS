#ifndef INTERRUTPS_H
#define INTERRUPTS_H

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
extern void int_00(void);
extern void int_01(void);
extern void int_02(void);
extern void int_03(void);
extern void int_04(void);
extern void int_05(void);
extern void int_06(void);
extern void int_07(void);
extern void int_08(void);
extern void int_09(void);
extern void int_10(void);
extern void int_11(void);
extern void int_12(void);
extern void int_13(void);
extern void int_14(void);
extern void int_15(void);
extern void int_16(void);
extern void int_17(void);
extern void int_18(void);
extern void int_19(void);
extern void int_32(void);

#endif /* INTERRUPTS_H */